/*
The MIT License (MIT)

Copyright (c) 2015-2022 Ivan Gagis <igagis@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/* ================ LICENSE END ================ */

#pragma once

#include <iostream>
#include <array>

#include <cmath>

#include <utki/debug.hpp>

#include "vector.hpp"

namespace r4{

template <class T, size_t R, size_t C> class matrix;

/**
 * @brief quaternion template class.
 */
template <typename T> class quaternion{
public:
	/**
	 * @brief Vector component of the quaternion.
	 */
	r4::vector<T, 3> v;

	/**
	 * @brief Scalar component of the quaternion.
	 */
	T s;

	/**
	 * @brief x component.
	 * Synonym of this->v.x().
	 */
	T& x()noexcept{
		return this->v.x();
	}

	/**
	 * @brief x component.
	 * Synonym of this->v.x().
	 */
	const T& x()const noexcept{
		return this->v.x();
	}

	/**
	 * @brief y component.
	 * Synonym of this->v.y().
	 */
	T& y()noexcept{
		return this->v.y();
	}

	/**
	 * @brief y component.
	 * Synonym of this->v.y().
	 */
	const T& y()const noexcept{
		return this->v.y();
	}

	/**
	 * @brief z component.
	 * Synonym of this->v.z().
	 */
	T& z()noexcept{
		return this->v.z();
	}

	/**
	 * @brief z component.
	 * Synonym of this->v.z().
	 */
	const T& z()const noexcept{
		return this->v.z();
	}

	/**
	 * @brief w component.
	 * Synonym of this->v.w().
	 */
	T& w()noexcept{
		return this->s;
	}

	/**
	 * @brief w component.
	 * Synonym of this->v.w().
	 */
	const T& w()const noexcept{
		return this->s;
	}

	/**
	 * @brief Create quaternion with given vector and scalar parts.
	 * @param vec - vector part of the quaternion.
	 * @param scalar - scalar part of the quaternion.
	 */
	constexpr quaternion(const vector<T, 3>& vec, T scalar)noexcept :
		v(vec),
		s(scalar)
	{}

	/**
	 * @brief Create quaternion with given components.
	 * @param x - x component.
	 * @param y - y component.
	 * @param z - z component.
	 * @param w - w component.
	 */
	constexpr quaternion(T x, T y, T z, T w)noexcept :
		v(x, y, z),
		s(w)
	{}

	/**
	 * @brief Construct rotation quaternion.
	 * Constructs a quaternion representing rotation (unit quaternion).
	 * Rotation is given by 3 dimensional vector, whose direction defines the
	 * axis about which rotation is done and its norm defines the angle of
	 * rotation in radians.
	 * @param rot - vector which defines the rotation.
	 */
	constexpr quaternion(const vector<T, 3>& rot)noexcept;

	/**
	 * @brief Default constructor.
	 * Note, that it does not initialize quaternion components,
	 * right after creation the components are undefined.
	 */
	constexpr quaternion() = default;

	/**
	 * @brief Convert to quaternion with different type of component.
	 * Convert this quaternion to a quaternion whose component type is different from T.
	 * Components are converted using constructor of target type passing the source
	 * component as argument of the target type constructor.
	 * @return converted quaternion.
	 */
	template <typename TT> quaternion<TT> to()noexcept{
		return quaternion<TT>{
			this->v.template to<TT>(),
			TT(this->s)
		};
	}

	/**
	 * @brief Operator equals.
	 * 
	 * @param q - quaternion to compare to for equality.
	 * @return true if all componentes of this quaternion are same as of given quaternion.
	 * @return false otherwise.
	 */
	bool operator==(const quaternion& q)const noexcept{
		return this->v == q.v && this->s == q.s;
	}

	/**
	 * @brief Complex conjugate of this quaternion.
	 * Note, complex conjugate of quaternion (x, y, z, w) is (-x, -y, -z, w).
	 * @return quaternion instance which is a complex conjugate of this quaternion.
	 */
	quaternion operator!()const noexcept{
		return quaternion(-this->v, this->s);
	}

	/**
	 * @brief Negation of this quaternion.
	 * 
	 * @return negated quaternion.
	 */
	quaternion operator-()const noexcept{
		return quaternion(-this->v, -this->s);
	}

	/**
	 * @brief Add quaternion and assign.
	 * Adds specified quaternion to this quaternion.
	 * @param q - quaternion to add to this quaternion.
	 * @return Reference to this quaternion object.
	 */
	quaternion& operator+=(const quaternion& q)noexcept{
		this->v += q.v;
		this->s += q.s;
		return *this;
	}

	/**
	 * @brief Addition of quaternions.
	 * Calculates sum of this quaternion and another specified quaternion.
	 * @param q - quaternion to add to this one.
	 * @return A quaternion object representing sum of quaternions.
	 */
	quaternion operator+(const quaternion& q)const noexcept{
		return (quaternion(*this) += q);
	}

	/**
	 * @brief Subtraction of quaternions.
	 * 
	 * @param q - quaternion to subtract from this one.
	 * @return result of subtraction of this quaternion and given quaternion.
	 */
	quaternion operator-(const quaternion& q)const noexcept{
		return this->operator+(-q);
	}

	/**
	 * @brief Multiply by scalar and assign.
	 * Multiplies this quaternion by scalar and assigns the result to this quaternion instance.
	 * @param s - scalar value to multiply by.
	 * @return reference to this quaternion instance.
	 */
	quaternion& operator*=(T s)noexcept{
		this->v *= s;
		this->s *= s;
		return *this;
	}

	/**
	 * @brief Multiply by scalar.
	 * @param s - scalar value to multiply by.
	 * @return resulting quaternion instance.
	 */
	quaternion operator*(T s)const noexcept{
		return (quaternion(*this) *= s);
	}

	/**
	 * @brief Multiply scalar by quaternion.
	 * @param num - scalar to multiply.
	 * @param quat - quaternion to multiply by.
	 * @return quaternion resulting from multiplication of given scalar by given quaternion.
	 */
	friend quaternion operator*(T num, const quaternion& quat)noexcept{
		return quat * num;
	}

	/**
	 * @brief Divide by scalar and assign.
	 * Divide this quaternion by scalar and assigns the result to this quaternion instance.
	 * @param s - scalar value to divide by.
	 * @return reference to this quaternion instance.
	 */
	quaternion& operator/=(T s)noexcept{
		this->v /= s;
		this->s /= s;
		return *this;
	}

	/**
	 * @brief Divide by scalar.
	 * @param s - scalar value to divide by.
	 * @return resulting quaternion instance.
	 */
	quaternion operator/(T s)const noexcept{
		return (quaternion(*this) /= s);
	}

	/**
	 * @brief Dot product of quaternions.
	 * Dot product of two quaternions (x1, y1, z1, w1) and
	 * (x2, y2, z2, w2) is a scalar calculated as follows
	 * x1 * x2 + y1 * y2 + z1 * z2 + w1 * w2
	 * @return result of the dot product.
	 */
	T dot(const quaternion& q)const noexcept{
		return this->v * q.v + this->s * q.s;
	}

	/**
	 * @brief Multiply by quaternion and assign.
	 * Multiplies this quaternion by another quaternion from the right
	 * (quaternions multiplication is not associative) and assigns the
	 * result to this quaternion instance.
	 * @param q - quaternion to multiply by.
	 * @return reference to this quaternion instance.
	 */
	quaternion& operator*=(const quaternion& q)noexcept{
		return this->operator=(this->operator*(q));
	}

	// TODO: remove deprecated stuff
	quaternion& operator%=(const quaternion& q)noexcept{
		LOG([](auto& o){o << "quaternion::operator%=() is DEPRECATED!, use quaternion::operator*=() instead!\n";});
		return this->operator*=(q);
	}

	/**
	 * @brief Multiply by quaternion.
	 * Multiplies this quaternion by another quaternion from the right
	 * (quaternions multiplication is not associative).
	 * @param q - quaternion to multiply by.
	 * @return resulting quaternion instance.
	 */
	quaternion operator*(const quaternion& q)const noexcept{
		return quaternion(
			this->s * q.v + q.s * this->v + this->v % q.v,
			this->s * q.s - this->v * q.v
		);
	}

	// TODO: remove deprecated stuff
	quaternion operator%(const quaternion& q)const noexcept{
		LOG([](auto& o){o << "quaternion::operator%() is DEPRECATED!, use quaternion::operator*() instead!\n";});
		return this->operator*(q);
	}

	/**
	 * @brief Initialize with identity quaternion.
	 * Note, identity quaternion is (0, 0, 0, 1).
	 * It is a unit quaternion representing no rotation.
	 * @return reference to this quaternion instance.
	 */
	quaternion& set_identity()noexcept{
		this->v.set(T(0));
		this->s = T(1);
		return *this;
	}

	/**
	 * @brief Complex conjugate this quaternion.
	 * Note, complex conjugate of quaternion (x, y, z, w) is (-x, -y, -z, w).
	 * @return reference to this quaternion instance.
	 */
	quaternion& conjugate()noexcept{
		return this->operator=(this->operator!());
	}

	/**
	 * @brief Negate this quaternion.
	 * Note, negating quaternion means changing the sign of its every component.
	 * @return reference to this quaternion instance.
	 */
	quaternion& negate()noexcept{
		this->v.negate();
		this->s = -this->s;
		return *this;
	}

	/**
	 * @brief Calculate power 2 of quaternion norm.
	 * @return power 2 of norm.
	 */
	T norm_pow2()const noexcept{
		return this->dot(*this);
	}

	/**
	 * @brief Calculate quaternion norm.
	 * @return quaternion norm.
	 */
	T norm()const noexcept{
		using std::sqrt;
		return T(sqrt(this->norm_pow2()));
	}

	/**
	 * @brief Normalize quaternion.
	 * Note, after normalization, the quaternion becomes a unit quaternion.
	 * If it is a quaternion of zero norm, then the result is undefined.
	 * @return reference to this quaternion instance.
	 */
	quaternion& normalize()noexcept{
		return (*this) /= this->norm();
	}

	/**
	 * @brief Inverse quaternion.
	 * 
	 * q^-1 = !q / q.norm_pow2()
	 * 
	 * @return inverted quaternion.
	 */
	quaternion inv()const noexcept{
		return this->operator!() / this->norm_pow2();
	}

	/**
	 * @brief Invert this quaternion.
	 * 
	 * @return reference to this quaternion.
	 */
	quaternion& invert()noexcept{
		return this->operator=(this->inv());
	}

	/**
	 * @brief Initialize rotation.
	 * Initializes this quaternion to a unit quaternion defining a rotation.
	 * A rotation is given by normalized axis vector and angle. Direction of rotation is determined by right-hand rule.
	 * @param axisX - X component of rotation axis.
	 * @param axisY - Y component of rotation axis.
	 * @param axisZ - Z component of rotation axis.
	 * @param angle - rotation angle.
	 * @return Reference to this quaternion object.
	 */
	quaternion& set_rotation(T axisX, T axisY, T axisZ, T angle)noexcept{
		return this->set_rotation(decltype(this->v)(axisX, axisY, axisZ), angle);
	}

	/**
	 * @brief Initialize rotation.
	 * Initializes this quaternion to a unit quaternion defining a rotation.
	 * A rotation is given by normalized axis vector and angle. Direction of rotation is determined by right-hand rule.
	 * @param axis - rotation axis, a normalized vector.
	 * @param angle - rotation angle.
	 * @return Reference to this quaternion object.
	 */
	quaternion& set_rotation(const vector<T, 3>& axis, T angle)noexcept;

	/**
	 * @brief Initialize rotation.
	 * Initializes this quaternion to a unit quaternion defining a rotation.
	 * A rotation is given by rotation vector, where the norm of the vector
	 * is a rotation angle in radians and vector direction defines the rotation axis.
	 * Direction of rotation is determined by right-hand rule.
	 * @param rot - rotation vector.
	 * @return Reference to this quaternion object.
	 */
	quaternion& set_rotation(const vector<T, 3>& rot)noexcept;

	/**
	 * @brief Convert this quaternion to 4x4 matrix.
	 * Assuming that this quaternion is a unit quaternion, converts this quaternion
	 * to a rotation matrix.
	 * @return Rotation matrix.
	 */
	template <size_t S>
	matrix<std::enable_if_t<S == 3 || S == 4, T>, S, S> to_matrix()const noexcept;

	/**
	 * @brief Spherical linear interpolation.
	 * Calculates spherical linear interpolation (SLERP) between two quaternions,
	 * the first quaternion is this one and the second is passed as argument.
	 * The result of SLERP is quaternion itself.
	 * SLERP(q1, q2, t) = q1 * sin((1 - t) * alpha) / sin(alpha) + q2 * sin(t * alpha) / sin(alpha),
	 * where cos(alpha) = (q1, q2) (dot product of unit quaternions q1 and q2).
	 * quaternions q1 and q2 are assumed to be unit quaternions and the resulting quaternion is also a unit quaternion.
	 * @param quat - quaternion to interpolate to.
	 * @param t - interpolation parameter, value from [0 : 1].
	 * @return Resulting quaternion of SLERP(this, quat, t).
	 */
	quaternion slerp(const quaternion& quat, T t)const noexcept{
		// Since quaternions are normalized the cosine of the angle alpha
		// between quaternions is equal to their dot product.
		T cos_alpha = this->dot(quat);

		T sign;

		// If the dot product is less than 0, the angle alpha between quaternions
		// is greater than 90 degrees. Then we negate second quaternion to make alpha
		// to be less than 90 degrees. It is possible since normalized quaternions
		// q and -q represent the same rotation.
		if(cos_alpha < T(0)){
			// Negate the second quaternion and the result of the dot product (i.e. cos(alpha))
			sign = -1;
			cos_alpha = -cos_alpha;
		}else{
			sign = 1;
		}

		// Interpolation done by the following general formula:
		// RESULT = this * sc1(t) + quat * sc2(t).
		// Where sc1, sc2 called interpolation scales.
		T sc1, sc2;

		// Check if the angle alpha between the 2 quaternions is big enough
		// to make SLERP. If alpha is small then we do a simple linear
		// interpolation between quaternions instead of SLERP!
		// It is also used to avoid divide by zero since sin(0) is 0.
		const T small_angle_cosine_threshold = T(0.99);
		if(cos_alpha < small_angle_cosine_threshold){
			using std::acos;
			using std::sin;

			// Get the angle alpha between the 2 quaternions, and then store the sin(alpha)
			T alpha = T(acos(cos_alpha));
			T sin_alpha = T(sin(alpha));

			// Calculate the scales for q1 and q2, according to the angle and it's sine value
			sc1 = T(sin((1 - t) * alpha)) / sin_alpha;
			sc2 = T(sin(t * alpha)) / sin_alpha;
		}else{
			sc1 = (1 - t);
			sc2 = t;
		}

		// Calculate the x, y, z and w values for the interpolated quaternion.
		return (*this) * sc1 + quat * (sc2 * sign);
	}

	/**
	 * @brief Vector rotation delta.
	 * If V is initial vector and K is rotated vector, then this
	 * function returns D = K - V.
	 * Add the delta D to initial vector V to get rotated vector K = V + D.
	 * @param vec - vector to rotate.
	 * @return delta vector between initial and rotated vectors.
	 */
	vector3<T> rotation_delta(const vector3<T> &vec) const{
		// assuming unit quaternion here
		return (this->v.cross(vec) * this->s + this->v * vec * this->v - this->v.norm_pow2() * vec) * 2;
	}

	friend std::ostream& operator<<(std::ostream& s, const quaternion<T>& quat){
		s << "(" << quat.x() << " " << quat.y() << " " << quat.z() << " " << quat.w() << ")";
		return s;
	}
};

}

#include "matrix.hpp"

namespace r4{

template <class T> constexpr quaternion<T>::quaternion(const vector<T, 3>& rot)noexcept{
	this->set_rotation(rot);
}

template <class T> quaternion<T>& quaternion<T>::set_rotation(const vector<T, 3>& rot)noexcept{
	T mag = rot.norm();
	if(mag != 0){
		this->set_rotation(rot / mag, mag);
	}else{
		this->set_identity();
	}
	return *this;
}

template <class T> quaternion<T>& quaternion<T>::set_rotation(const vector<T, 3>& axis, T angle)noexcept{
	using std::sin;
	using std::cos;
	this->s = T(cos(angle / 2));
	this->v = axis * T(sin(angle / 2));
	return *this;
}

template <class T>
template <size_t S>
matrix<std::enable_if_t<S == 3 || S == 4, T>, S, S> quaternion<T>::to_matrix()const noexcept{
	return matrix<T, S, S>(*this);
}

static_assert(sizeof(quaternion<float>) == sizeof(float) * 4, "size mismatch");
static_assert(sizeof(quaternion<double>) == sizeof(double) * 4, "size mismatch");

}
