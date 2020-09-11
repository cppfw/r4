#pragma once

#include <iostream>
#include <array>

#include <utki/debug.hpp>
#include <utki/math.hpp>

namespace r4{

template <class T> class vector2;
template <class T> class vector4;
template <class T> class matrix4;
template <class T> class quaternion;

/**
 * @brief Three-dimensional vector.
 */
template <typename T> class vector3 : public std::array<T, 3>{
	typedef std::array<T, 3> base_type;
public:
	/**
	 * @brief First vector component.
	 */
	T& x()noexcept{
		return this->operator[](0);
	}

	/**
	 * @brief First vector component.
	 */
	const T& x()const noexcept{
		return this->operator[](0);
	}

	/**
	 * @brief Second vector component.
	 */
	T& y(){
		return this->operator[](1);
	}

	/**
	 * @brief Second vector component.
	 */
	const T& y()const noexcept{
		return this->operator[](1);
	}

	/**
	 * @brief Third vector component.
     */
	T& z(){
		return this->operator[](2);
	}

	/**
	 * @brief Third vector component.
     */
	const T& z()const noexcept{
		return this->operator[](2);
	}

	/**
	 * @brief Default constructor.
	 * Default constructor does not initialize vector components to any values.
	 */
	vector3() = default;

	/**
	 * @brief Constructor.
	 * Initializes vector components to given values.
     * @param x - value for first vector component.
     * @param y - value for second vector component.
     * @param z - value for third vector component.
     */
	vector3(T x, T y, T z)noexcept :
			std::array<T, 3>{{x, y, z}}
	{}

	/**
	 * @brief Constructor.
	 * Initializes all vector components to a given value.
     * @param num - value to initialize all vector components with.
     */
	vector3(T num)noexcept :
			vector3{num, num, num}
	{}

	/**
	 * @brief Constructor.
	 * Initializes components to a given values.
	 * @param vec - 2d vector to use for initialization of first two vector components.
	 * @param z - value to use for initialization of 3rd vector component.
	 */
	vector3(const vector2<T>& vec, T z = 0)noexcept;

	/**
	 * @brief Constructor.
	 * Initializes components to a given values.
	 * @param vec - 4d vector to use for initialization, the w-value of the vector is ignored.
	 */
	vector3(const vector4<T>& vec)noexcept;

	// TODO: doxygen
	template <typename TT> vector3<TT> to()noexcept{
		return vector3<TT>{
				TT(this->x()),
				TT(this->y()),
				TT(this->z())
			};
	}

	/**
	 * @brief Assign from 2d vector.
	 * Assigns first 2 components of this vector from components of given 2d vector.
	 * Third component of this vector is assigned a value of 0.
	 * @param vec - 2d vector to assign first two components from.
	 * @return Reference to this vector object.
	 */
	vector3& operator=(const vector2<T>& vec)noexcept;

	/**
	 * @brief Assign a number.
	 * Sets all 3 components of this vector to a given number.
     * @param num - number to use for assignment.
     * @return Reference to this vector object.
     */
	vector3& operator=(T num)noexcept{
		this->x = num;
		this->y = num;
		this->z = num;
		return (*this);
	}

	/**
	 * @brief Set all vector components to given value.
	 * @param val - value to set vector components to.
	 * @return Reference to this vector object.
	 */
	vector3& set(T val)noexcept{
		this->x = val;
		this->y = val;
		this->z = val;
		return (*this);
	}

	/**
	 * @brief Add and assign.
	 * Adds corresponding components of a given vector to first two components of this vector and assigns
	 * the result back to this vector components.
	 * @param vec - 2d vector to use for addition.
	 * @return Reference to this vector object.
	 */
	vector3& operator+=(const vector2<T>& vec)noexcept;

	/**
	 * @brief Add and assign.
	 * Adds given vector to this vector and assigns result back to this vector.
	 * @param vec - vector to add.
	 * @return Reference to this vector object.
	 */
	vector3& operator+=(const vector3& vec)noexcept{
		this->x += vec.x;
		this->y += vec.y;
		this->z += vec.z;
		return (*this);
	}

	/**
	 * @brief Add vector.
	 * Adds this vector and given vector.
	 * @param vec - vector to add.
	 * @return Vector resulting from vector addition.
	 */
	vector3 operator+(const vector3& vec)const noexcept{
		return (vector3(*this) += vec);
	}

	/**
	 * @brief Subtract and assign.
	 * Subtracts given vector from this vector and assigns result back to this vector.
	 * @param vec - vector to subtract.
	 * @return Reference to this vector object.
	 */
	vector3& operator-=(const vector3& vec)noexcept{
		this->x -= vec.x;
		this->y -= vec.y;
		this->z -= vec.z;
		return *this;
	}

	/**
	 * @brief Subtract vector.
	 * Subtracts given vector from this vector.
	 * @param vec - vector to subtract.
	 * @return Vector resulting from vector subtraction.
	 */
	vector3 operator-(const vector3& vec)const noexcept{
		return (vector3(*this) -= vec);
	}

	/**
	 * @brief Unary minus.
     * @return Negated vector.
     */
	vector3 operator-()const noexcept{
		return vector3(*this).negate();
	}

	/**
	 * @brief Multiply by scalar and assign.
	 * Multiplies this vector by scalar and assigns result back to this vector.
     * @param num - scalar to multiply by.
     * @return Reference to this vector object.
     */
	vector3& operator*=(T num)noexcept{
		this->x *= num;
		this->y *= num;
		this->z *= num;
		return (*this);
	}

	/**
	 * @brief Multiply by scalar.
	 * Multiplies this vector by scalar.
     * @param num - scalar to multiply by.
     * @return Vector resulting from multiplication of this vector by scalar.
     */
	vector3 operator*(T num)const noexcept{
		return (vector3(*this) *= num);
	}

	/**
	 * @brief Multiply scalar by vector.
	 * @param num - scalar to multiply.
	 * @param vec - vector to multiply by.
	 * @return Vector resulting from multiplication of given scalar by given vector.
	 */
	friend vector3 operator*(T num, const vector3& vec)noexcept{
		return vec * num;
	}

	/**
	 * @brief Divide by scalar and assign.
	 * Divide this vector by scalar and assign result back to this vector.
	 * @param num - scalar to divide by.
	 * @return Reference to this vector object.
	 */
	vector3& operator/=(T num)noexcept{
		ASSERT(num != 0)
		this->x /= num;
		this->y /= num;
		this->z /= num;
		return (*this);
	}

	/**
	 * @brief Divide by scalar.
	 * Divide this vector by scalar.
	 * @param num - scalar to divide by.
	 * @return Vector resulting from division of this vector by scalars.
	 */
	vector3 operator/(T num)noexcept{
		ASSERT_INFO(num != 0, "vector3::operator/(): division by 0")
		return (vector3(*this) /= num);
	}

	/**
	 * @brief Dot product.
     * @param vec -vector to multiply by.
     * @return Dot product of this vector and given vector.
     */
	T operator*(const vector3& vec)const noexcept{
		return this->x() * vec.x()
				+ this->y() * vec.y()
				+ this->z() * vec.z();
	}

	// TODO: rename to comp_mul
	/**
	 * @brief Component-wise multiplication.
	 * Performs component-wise multiplication of two vectors.
	 * The result of such operation is also a vector.
     * @param vec - vector to multiply by.
     * @return Vector resulting from component-wise multiplication.
     */
	vector3 comp_multiplied(const vector3& vec)const noexcept{
		return vector3(
				this->x * vec.x,
				this->y * vec.y,
				this->z * vec.z
			);
	}

	// TODO: add cross() method

	/**
	 * @brief Cross product.
     * @param vec - vector to multiply by.
     * @return Vector resulting from the cross product.
     */
	vector3 operator%(const vector3& vec)const noexcept{
		return vector3(
				this->y * vec.z - this->z * vec.y,
				this->z * vec.x - this->x * vec.z,
				this->x * vec.y - this->y * vec.x
			);
	}

	/**
	 * @brief Check if all components of this vector are zero.
     * @return true if all components of this vector are zero.
	 * @return false otherwise.
     */
	bool is_zero()const noexcept{
		return (this->x == 0 && this->y == 0 && this->z == 0);
	}

	/**
	 * @brief Negate this vector.
	 * Negates this vector.
	 * @return Reference to this vector object.
	 */
	vector3& negate()noexcept{
		this->x = -this->x;
		this->y = -this->y;
		this->z = -this->z;
		return (*this);
	}

	/**
	 * @brief Calculate power 2 of vector norm.
	 * @return Power 2 of this vector norm.
	 */
	T norm_pow2()const noexcept{
		return utki::pow2(this->x) + utki::pow2(this->y) + utki::pow2(this->z);
	}

	/**
	 * @brief Calculate vector norm.
	 * @return Vector norm.
	 */
	T norm()const noexcept{
		return std::sqrt(this->norm_pow2());
	}

	/**
	 * @brief Normalize this vector.
	 * Normalizes this vector.
	 * If norm is 0 then the result is vector (1, 0, 0).
	 * @return Reference to this vector object.
	 */
	vector3& normalize()noexcept{
		T mag = this->norm();
		if(mag == 0){
			this->x = 1;
			this->y = 0;
			this->z = 0;
			return *this;
		}

		return (*this) /= this->norm();
	}

	/**
	 * @brief Project this vector onto a given vector.
     * @param vec - vector to project onto, it does not have to be normalized.
     * @return Reference to this vector object.
     */
	vector3& project(const vector3& vec)noexcept{
		ASSERT(this->norm_pow2() != 0)
		(*this) = vec * (vec * (*this)) / vec.norm_pow2();
		return (*this);
	}

	/**
	 * @brief Rotate this vector.
	 * Rotate this vector with unit quaternion.
	 * @param q - quaternion which defines the rotation.
	 * @return Reference to this vector object.
	 */
	vector3<T>& rotate(const quaternion<T>& q)noexcept;

	friend std::ostream& operator<<(std::ostream& s, const vector3<T>& vec){
		s << "(" << vec.x() << ", " << vec.y() << ", " << vec.z() << ")";
		return s;
	}
};

}

#include "vector2.hpp"
#include "vector4.hpp"
#include "quaternion.hpp"
#include "matrix4.hpp"

namespace r4{

template <class T> vector3<T>::vector3(const vector2<T>& vec, T z)noexcept :
		std::array<T, 3>{{vec[0], vec[1], z}}
{}

template <class T> vector3<T>::vector3(const vector4<T>& vec)noexcept :
		std::array<T, 3>{{vec[0], vec[1], vec[2]}}
{}

template <class T> vector3<T>& vector3<T>::operator=(const vector2<T>& vec)noexcept{
	this->x = vec.x;
	this->y = vec.y;
	this->z = 0;
	return (*this);
}

template <class T> vector3<T>& vector3<T>::operator+=(const vector2<T>& vec)noexcept{
	this->x += vec.x;
	this->y += vec.y;
	return (*this);
}

template <class T> vector3<T>& vector3<T>::rotate(const quaternion<T>& q)noexcept{
	*this = q.to_matrix4() * (*this);
	return *this;
}

typedef vector3<float> vec3f;
static_assert(sizeof(vec3f) == sizeof(float) * 3, "size mismatch");

typedef vector3<double> vec3d;
static_assert(sizeof(vec3d) == sizeof(double) * 3, "size mismatch");

}
