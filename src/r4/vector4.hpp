#pragma once

#include <iostream>
#include <array>

#include <utki/debug.hpp>
#include <utki/math.hpp>

namespace r4{

template <class T> class vector2;
template <class T> class vector3;

/**
 * @brief Four-dimensional vector.
 */
template <class T> class vector4 : public std::array<T, 4>{
	typedef std::array<T, 4> base_type;
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
	T& y()noexcept{
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
	T& z()noexcept{
		return this->operator[](2);
	}

	/**
	 * @brief Third vector component.
     */
	const T& z()const noexcept{
		return this->operator[](2);
	}

	/**
	 * @brief Fourth vector component.
     */
	T& w()noexcept{
		return this->operator[](3);
	}

	/**
	 * @brief Fourth vector component.
     */
	const T& w()const noexcept{
		return this->operator[](3);
	}

	/**
	 * @brief Default constructor.
	 * Default constructor does not initialize vector components to any values.
	 */
	constexpr vector4() = default;

	/**
	 * @brief Constructor.
	 * Initializes vector components to given values.
     * @param x - value for first vector component.
     * @param y - value for second vector component.
     * @param z - value for third vector component.
     * @param w - value for fourth vector component.
     */
	constexpr vector4(T x, T y, T z, T w)noexcept :
			base_type{{x, y, z, w}}
	{}

	/**
	 * @brief Constructor.
	 * Initializes all vector components to a given value.
     * @param num - value to initialize all vector components with.
     */
	constexpr vector4(T num)noexcept :
			vector4(num, num, num, num)
	{}

	/**
	 * @brief Constructor.
	 * Initializes first three vector components to the same given value and fourth component to another given value.
     * @param num - value to use for initialization of first three vector components.
     * @param w - value to use for initialization of fourth vector component.
     */
	constexpr vector4(T num, T w)noexcept :
			vector4(num, num, num, w)
	{}

	/**
	 * @brief Constructor.
	 * Initializes components to a given values.
	 * @param vec - 2d vector to use for initialization of first two vector components.
	 * @param z - value to use for initialization of 3rd vector component.
	 * @param w - value to use for initialization of 4th vector component.
	 */
	constexpr vector4(const vector2<T>& vec, T z = 0, T w = 1)noexcept;

	/**
	 * @brief Constructor.
	 * Initializes components to a given values.
	 * @param vec - 23 vector to use for initialization of first three vector components.
	 * @param w - value to use for initialization of 4th vector component.
	 */
	constexpr vector4(const vector3<T>& vec, T w = 1)noexcept;

	/**
	 * @brief Convert to vector4 with different type of component.
	 * Convert this vector4 to a vector4 whose component type is different from T.
	 * Components are converted using constructor of target type passing the source
	 * component as argument of the target type constructor.
	 * @return converted vector4.
	 */
	template <typename TT> vector4<TT> to()noexcept{
		return vector4<TT>{
				TT(this->x()),
				TT(this->y()),
				TT(this->z()),
				TT(this->w())
			};
	}

	/**
	 * @brief Assign from 3d vector.
	 * Assigns first 3 components of this vector from components of given 3d vector.
	 * Fourth component of this vector is assigned a value of 1.
	 * @param vec - 3d vector to assign first three components from.
	 * @return Reference to this vector object.
	 */
	vector4& operator=(const vector3<T>& vec)noexcept;

	/**
	 * @brief Assign from 2d vector.
	 * Assigns first 2 components of this vector from components of given 2d vector.
	 * Third component of this vector is assigned a value of 0.
	 * Fourth component of this vector is assigned a value of 1.
	 * @param vec - 2d vector to assign first two components from.
	 * @return Reference to this vector object.
	 */
	vector4& operator=(const vector2<T>& vec)noexcept;

	/**
	 * @brief Assign a number.
	 * Sets all 4 components of this vector to a given number.
     * @param num - number to use for assignment.
     * @return Reference to this vector object.
     */
	vector4& operator=(T num)noexcept{
		this->set(num);
		return *this;
	}

	/**
	 * @brief Set all vector components to given value.
	 * @param val - value to set vector components to.
	 * @return Reference to this vector object.
	 */
	vector4& set(T val)noexcept{
		this->x() = val;
		this->y() = val;
		this->z() = val;
		this->w() = val;
		return *this;
	}

	/**
	 * @brief Add and assign.
	 * Adds corresponding components of a given vector to first two components of this vector and assigns
	 * the result back to this vector components.
	 * @param vec - 2d vector to use for addition.
	 * @return Reference to this vector object.
	 */
	vector4& operator+=(const vector2<T>& vec)noexcept;

	/**
	 * @brief Add and assign.
	 * Adds corresponding components of a given vector to first three components of this vector and assigns
	 * the result back to this vector components.
	 * @param vec - 3d vector to use for addition.
	 * @return Reference to this vector object.
	 */
	vector4& operator+=(const vector3<T>& vec)noexcept;

	/**
	 * @brief Add and assign.
	 * Adds given vector to this vector and assigns result back to this vector.
	 * @param vec - vector to add.
	 * @return Reference to this vector object.
	 */
	vector4& operator+=(const vector4& vec)noexcept{
		this->x() += vec.x();
		this->y() += vec.y();
		this->z() += vec.z();
		this->w() += vec.w();
		return *this;
	}

	/**
	 * @brief Add vector.
	 * Adds this vector and given vector.
	 * @param vec - vector to add.
	 * @return Vector resulting from vector addition.
	 */
	vector4 operator+(const vector4& vec)const noexcept{
		return (vector4(*this) += vec);
	}

	/**
	 * @brief Subtract and assign.
	 * Subtracts given vector from this vector and assigns result back to this vector.
	 * @param vec - vector to subtract.
	 * @return Reference to this vector object.
	 */
	vector4& operator-=(const vector4& vec)noexcept{
		this->x() -= vec.x();
		this->y() -= vec.y();
		this->z() -= vec.z();
		this->w() -= vec.w();
		return *this;
	}

	/**
	 * @brief Subtract vector.
	 * Subtracts given vector from this vector.
	 * @param vec - vector to subtract.
	 * @return Vector resulting from vector subtraction.
	 */
	vector4 operator-(const vector4& vec)const noexcept{
		return (vector4(*this) -= vec);
	}

	/**
	 * @brief Unary minus.
     * @return Negated vector.
     */
	vector4 operator-()const noexcept{
		return vector4(*this).negate();
	}

	/**
	 * @brief Multiply by scalar and assign.
	 * Multiplies this vector by scalar and assigns result back to this vector.
     * @param num - scalar to multiply by.
     * @return Reference to this vector object.
     */
	vector4& operator*=(T num)noexcept{
		this->x() *= num;
		this->y() *= num;
		this->z() *= num;
		this->w() *= num;
		return *this;
	}

	/**
	 * @brief Multiply by scalar.
	 * Multiplies this vector by scalar.
     * @param num - scalar to multiply by.
     * @return Vector resulting from multiplication of this vector by scalar.
     */
	vector4 operator*(T num)const noexcept{
		return (vector4(*this) *= num);
	}

	/**
	 * @brief Multiply scalar by vector.
	 * @param num - scalar to multiply.
	 * @param vec - vector to multiply by.
	 * @return Vector resulting from multiplication of given scalar by given vector.
	 */
	friend vector4 operator*(T num, const vector4& vec)noexcept{
		return vec * num;
	}

	/**
	 * @brief Divide by scalar and assign.
	 * Divide this vector by scalar and assign result back to this vector.
	 * @param num - scalar to divide by.
	 * @return Reference to this vector object.
	 */
	vector4& operator/=(T num)noexcept{
		ASSERT_INFO(num != 0, "vector4::operator/=(): division by 0")
		this->x() /= num;
		this->y() /= num;
		this->z() /= num;
		this->w() /= num;
		return *this;
	}

	/**
	 * @brief Divide by scalar.
	 * Divide this vector by scalar.
	 * @param num - scalar to divide by.
	 * @return Vector resulting from division of this vector by scalars.
	 */
	vector4 operator/(T num)noexcept{
		ASSERT_INFO(num != 0, "vector4::operator/(): division by 0")
		return (vector4(*this) /= num);
	}

	/**
	 * @brief Dot product.
     * @param vec -vector to multiply by.
     * @return Dot product of this vector and given vector.
     */
	T operator*(const vector4& vec)const noexcept{
		return this->x() * vec.x()
				+ this->y() * vec.y()
				+ this->z() * vec.z()
				+ this->w() * vec.w();
	}

	/**
	 * @brief Cross product.
	 * First three components of the resulting 4d vector is a result of cross
	 * product between two 3d vectors formed from first 3 components of initial 4d vectors.
	 * The forth component is a simple multiplication of 4th components of initial vectors.
     * @param vec - vector to multiply by.
     * @return Four-dimensional vector resulting from the cross product.
     */
	vector4 operator%(const vector4& vec)const noexcept{
		return vector4(
				this->y() * vec.z() - this->z() * vec.y(),
				this->z() * vec.x() - this->x() * vec.z(),
				this->x() * vec.y() - this->y() * vec.x(),
				this->w() * vec.w()
			);
	}

	/**
	 * @brief Negate this vector.
	 * Negates this vector.
	 * @return Reference to this vector object.
	 */
	vector4& negate()noexcept{
		this->x() = -this->x();
		this->y() = -this->y();
		this->z() = -this->z();
		this->w() = -this->w();
		return *this;
	}

	/**
	 * @brief Calculate power 2 of vector norm.
	 * @return Power 2 of this vector norm.
	 */
	T norm_pow2()const noexcept{
		return utki::pow2(this->x())
				+ utki::pow2(this->y())
				+ utki::pow2(this->z())
				+ utki::pow2(this->w());
	}

	/**
	 * @brief Calculate vector norm.
	 * @return Vector norm.
	 */
	T norm()const noexcept{
		return sqrt(this->norm_pow2());
	}

	/**
	 * @brief Normalize this vector.
	 * Normalizes this vector.
	 * If norm is 0 then the result is vector (1, 0, 0, 0).
	 * @return Reference to this vector object.
	 */
	vector4& normalize()noexcept{
		T mag = this->norm();
		if(mag == 0){
			this->x() = 1;
			this->y() = 0;
			this->z() = 0;
			this->w() = 0;
			return *this;
		}

		return (*this) /= this->norm();
	}

	friend std::ostream& operator<<(std::ostream& s, const vector4<T>& vec){
		s << "(" << vec.x() << ", " << vec.y() << ", " << vec.z() << ", " << vec.w() << ")";
		return s;
	}
};

}

#include "vector2.hpp"
#include "vector3.hpp"

namespace r4{

template <class T> constexpr vector4<T>::vector4(const vector2<T>& vec, T z, T w)noexcept :
		vector4(vec.x(), vec.y(), z, w)
{}

template <class T> constexpr vector4<T>::vector4(const vector3<T>& vec, T w)noexcept :
		vector4(vec.x(), vec.y(), vec.z(), w)
{}

template <class T> vector4<T>& vector4<T>::operator=(const vector3<T>& vec)noexcept{
	this->x() = vec.x();
	this->y() = vec.y();
	this->z() = vec.z();
	this->w() = 1;
	return *this;
}

template <class T> vector4<T>& vector4<T>::operator=(const vector2<T>& vec)noexcept{
	this->x() = vec.x();
	this->y() = vec.y();
	this->z() = 0;
	this->w() = 1;
	return *this;
}

template <class T> vector4<T>& vector4<T>::operator+=(const vector2<T>& vec)noexcept{
	this->x() += vec.x();
	this->y() += vec.y();
	return *this;
}

template <class T> vector4<T>& vector4<T>::operator+=(const vector3<T>& vec)noexcept{
	this->x() += vec.x();
	this->y() += vec.y();
	this->z() += vec.z();
	return *this;
}

typedef vector4<float> vec4f;
static_assert(sizeof(vec4f) == sizeof(float) * 4, "size mismatch");

typedef vector4<double> vec4d;
static_assert(sizeof(vec4d) == sizeof(double) * 4, "size mismatch");

}
