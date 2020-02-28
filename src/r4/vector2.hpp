#pragma once

#include <iostream>

#include <utki/debug.hpp>
#include <utki/math.hpp>

namespace r4{

template <class T> class vector3;

/**
 * @brief Two-dimensional vector class.
 */
template <class T> class vector2{
public:
	typedef T value_type;

	/**
	 * @brief 0th vector component.
	 */
	T x;

	/**
	 * @brief 1th vector component.
	 */
	T y;

	/**
	 * @brief Get number of vector components.
     * @return Number of vector components.
     */
	size_t size()const{
		return 2;
	}

	/**
	 * @brief default constructor.
	 * It does not initialize vector components.
	 * Their values are undefined right after construction.
	 */
	constexpr vector2()noexcept :
			x(0), y(0) //TODO: remove initialization list when C++14 is supported by all compilers
	{}

	/**
	 * @brief Create vector with given values.
	 * Creates a vector with all components initialized to a given value.
	 * @param xy - value to assign to all components of the vector.
	 */
	constexpr vector2(T xy)noexcept :
			x(xy), y(xy)
	{}

	/**
	 * @brief Create vector with given values.
	 * @param x - x component of the vector.
	 * @param y - y component of the vector.
	 */
	constexpr vector2(T x, T y)noexcept :
			x(x), y(y)
	{}

	/**
	 * @brief Create vector2 from vector3
	 * Creates a 2 dimensional vector and initializes its x and y components
	 * from x and y of given 3 dimensional vector.
	 * @param vec - 3 dimensional vector to copy x and y from.
	 */
	vector2(const vector3<T>& vec)noexcept;

	//TODO: doxygen
	template <class TT> explicit vector2(const vector2<TT>& v) :
			x(T(v.x)),
			y(T(v.y))
	{}

	/**
	 * @brief Access vector components.
	 * @param i - index of the component, can be 0 or 1.
	 */
	T& operator[](unsigned i)noexcept{
		ASSERT(i < 2)
		ASSERT( &((&this->x)[0]) == &this->x)
		ASSERT( &((&this->x)[1]) == &this->y)
		return (&this->x)[i];
	}

	/**
	 * @brief Access vector components.
	 * @param i - index of the component, can be 0 or 1.
	 */
	const T& operator[](unsigned i)const noexcept{
		ASSERT(i < 2)
		ASSERT( &((&this->x)[0]) == &this->x)
		ASSERT( &((&this->x)[1]) == &this->y)
		return (&this->x)[i];
	}

	/**
	 * @brief Assign value of given vector3 object.
	 * Note, the z component of given vector3 is ignored.
	 * @param vec - reference to the vector3 object to assign value from.
	 * @return reference to this vector2 object.
	 */
	vector2& operator=(const vector3<T>& vec)noexcept;

	/**
	 * @brief Add vector2 and vector3.
	 * Note, the z component of given vector3 is ignored.
	 * @param vec - reference to the vector3 object to add.
	 * @return instance of the resulting vector2.
	 */
	vector2 operator+(const vector3<T>& vec)const noexcept;

	/**
	 * @brief Add and assign.
	 * Adds given vector2 and this vector2 and assigns the result to this vector2.
	 * @param vec - reference to the vector2 object to add.
	 * @return reference to this vector2 object.
	 */
	vector2& operator+=(const vector2& vec)noexcept{
		this->x += vec.x;
		this->y += vec.y;
		return (*this);
	}

	/**
	 * @brief Add two vector2 vectors.
	 * @param vec - reference to the vector2 object to add.
	 * @return instance of the resulting vector2.
	 */
	vector2 operator+(const vector2& vec)const noexcept{
		return (vector2(*this) += vec);
	}

	/**
	 * @brief Subtract vector and assign.
	 * Subtracts given vector from this one and assigns result back to this vector.
     * @param vec - vector to subtract from this one.
     * @return Reference to this vector object.
     */
	vector2& operator-=(const vector2& vec)noexcept{
		this->x -= vec.x;
		this->y -= vec.y;
		return (*this);
	}

	/**
	 * @brief Subtract vector.
     * @param vec - vector to subtract from this one.
     * @return Vector resulting from subtraction of given vector from this vector.
     */
	vector2 operator-(const vector2& vec)const noexcept{
		return (vector2(*this) -= vec);
	}

	/**
	 * @brief Subtract vector.
	 * Subtracts 3d vector from this 2d vector. 3rd component of subtracted vector is ignored, i.e.
	 * (this.x, this.y) - (x, y, z) = (this.x - x, this.y -y).
     * @param vec - vector to subtract from this one.
     * @return Resulting two-dimensional vector.
     */
	vector2 operator-(const vector3<T>& vec)const noexcept;

	/**
	 * @brief Unary minus.
	 * @return Vector resulting from negating this vector.
	 */
	vector2 operator-()const noexcept{
		return vector2(-this->x, -this->y);
	}

	/**
	 * @brief Multiply by scalar and assign.
	 * Multiplies this vector by scalar and assigns the result back to this vector.
     * @param num - scalar to multiply by.
     * @return Reference to this vector object.
     */
	vector2& operator*=(T num)noexcept{
		this->x *= num;
		this->y *= num;
		return (*this);
	}

	/**
	 * @brief Multiply by scalar.
	 * @param num - scalar to multiply by.
	 * @return Vector resulting from multiplication of this vector by given scalar.
	 */
	vector2 operator*(T num)const noexcept{
		return (vector2(*this) *= num);
	}

	/**
	 * @brief Multiply scalar by vector.
     * @param num - scalar to multiply.
     * @param vec - vector to multiply by.
     * @return Vector resulting from multiplication of given scalar by given vector.
     */
	friend vector2 operator*(T num, const vector2& vec)noexcept{
		return vec * num;
	}

	/**
	 * @brief Divide by scalar and assign.
	 * Divides this vector by scalar and assigns the result back to this vector.
     * @param num - scalar to divide by.
     * @return Reference to this vector object.
     */
	vector2& operator/=(T num)noexcept{
		ASSERT(num != 0)
		this->x /= num;
		this->y /= num;
		return (*this);
	}

	/**
	 * @brief Divide by scalar.
	 * @param num - scalar to divide this vector by.
	 * @return Vector resulting from dividing this vector by given scalar.
	 */
	vector2 operator/(T num)const noexcept{
		ASSERT(num != 0)
		return (vector2(*this) /= num);
	}

	/**
	 * @brief Dot product.
	 * Dot product of this vector and a given vector.
	 * @return Dot product of two vectors (x1 * x2 + y1 * y2).
	 */
	T operator*(const vector2& vec)const noexcept{
		return (this->x * vec.x + this->y * vec.y);
	}

	/**
	 * @brief Check if this vector equals to the given vector.
	 * @param vec - vector to compare to.
	 * @return true if corresponding components of both vectors are equal.
	 * @return false otherwise.
	 */
	bool operator==(const vector2& vec)const noexcept{
		return this->x == vec.x && this->y == vec.y;
	}

	/**
	 * @brief Check if this vector is not equal to the given vector.
	 * This is a logical NOT of result from operator==().
	 * @param vec - vector to compare to.
	 * @return true if any of corresponding components of two vectors are not equal.
	 * @return false otherwise.
	 */
	bool operator!=(const vector2& vec)const noexcept{
		return !this->operator==(vec);
	}

	/**
	 * @brief Component-wise multiplication.
	 * Performs component-wise multiplication of two vectors.
	 * Resulting vector is (x1 * x2, y1 * y2).
	 * The result of such operation is also vector.
     * @param vec - vector to multiply by.
     * @return Vector resulting from component-wise multiplication.
     */
	vector2 comp_multiplied(const vector2& vec)const noexcept{
		return vector2(
				this->x * vec.x,
				this->y * vec.y
			);
	}

	/**
	 * @brief Component-wise multiplication.
	 * Performs component-wise multiplication of this vector by another given vector.
	 * See CompMul() for details.
     * @param vec - vector to multiply by.
     * @return reference to this vector2 instance.
     */
	vector2& comp_multiply(const vector2& vec)noexcept{
		this->x *= vec.x;
		this->y *= vec.y;
		return *this;
	}

	/**
	 * @brief Component-wise division.
	 * Performs component-wise division of two vectors.
	 * Resulting vector is (x1 / x2, y1 / y2).
	 * The result of such operation is also vector.
     * @param v - vector to divide by.
     * @return Vector resulting from component-wise division.
     */
	vector2 comp_divided(const vector2& v)const noexcept{
		return vector2(
				this->x / v.x,
				this->y / v.y
			);
	}

	/**
	 * @brief Component-wise division.
	 * Performs component-wise division of this vector by another given vector.
	 * See CompDiv() for details.
     * @param v - vector to divide by.
     * @return reference to this vector2 instance.
     */
	vector2& comp_divide(const vector2& v)noexcept{
		this->x /= v.x;
		this->y /= v.y;
		return *this;
	}

	/**
	 * @brief Check if both vector components are zero.
	 * @return true if both vector components are zero.
	 * @return false otherwise.
	 */
	bool is_zero()const noexcept{
		return this->x == 0 && this->y == 0;
	}

	/**
	 * @brief Check if both vector components are positive or zero.
	 * @return true if both vector components are positive or zero.
	 * @return false otherwise.
	 */
	bool is_positive_or_zero()const noexcept{
		return this->x >= 0 && this->y >= 0;
	}

	/**
	 * @brief Check if both vector components are positive.
	 * @return true if both vector components are positive.
     * @return false otherwise.
     */
	bool is_positive()const noexcept{
		return this->x > 0 && this->y > 0;
	}

	/**
	 * @brief Check if both vector components are negative.
	 * @return true if both vector components are negative.
     * @return false otherwise.
     */
	bool is_negative()const noexcept{
		return this->x < 0 && this->y < 0;
	}

	/**
	 * @brief Negate this vector.
     * @return Reference to this vector object.
     */
	vector2& negate()noexcept{
		// NOTE: this should be faster than (*this) = -(*this);
		this->x = -this->x;
		this->y = -this->y;
		return (*this);
	}

	/**
	 * @brief Absolute vector value.
     * @return vector2 holding absolute values of this vector's components.
     */
	vector2 abs()const noexcept{
		return vector2(
				std::abs(this->x),
				std::abs(this->y)
			);
	}

	/**
	 * @brief Calculate power 2 of vector norm.
	 * @return Power 2 of this vector norm.
	 */
	T norm_pow2()noexcept{
		return utki::pow2(this->x) + utki::pow2(this->y);
	}

	/**
	 * @brief Calculate norm of the vector.
	 * @return norm of this vector.
	 */
	T norm()noexcept{
		return T(std::sqrt(this->norm_pow2()));
	}

	/**
	 * @brief Normalize this vector.
	 * If the norm of vector is 0 then the result is vector (1, 0).
	 * @return Reference to this vector object.
	 */
	vector2& normalize()noexcept{
		T mag = this->norm();
		if(mag == 0){
			this->x = 1;
			this->y = 0;
			return *this;
		}
		return (*this) /= this->norm();
	}

	/**
	 * @brief Set both vector components to given value.
	 * @param val - value to set vector components to.
	 * @return Reference to this vector object.
	 */
	vector2& set(T val)noexcept{
		this->x = val;
		this->y = val;
		return (*this);
	}

	/**
	 * @brief Rotate vector.
	 * Rotate this vector around (0, 0, 1) axis. Direction of the rotation is
	 * determined by right-hand rule.
     * @param angle - angle of rotation in radians.
     * @return Reference to this vector object.
     */
	vector2& rotate(T angle)noexcept{
		T cosa = std::cos(angle);
		T sina = std::sin(angle);
		T tmp = this->x * cosa - this->y * sina;
		this->y = this->y * cosa + this->x * sina;
		this->x = tmp;
		return (*this);
	}

	/**
	 * @brief Rotation of vector.
	 * Calculate vector resulting from rotation this vector around (0, 0, 1) axis.
	 * Direction of the rotation is determined by right-hand rule.
	 * @param angle - angle of rotation in radians.
	 * @return Vector resulting from rotation of this vector.
	 */
	vector2 rotated(T angle)const noexcept{
		return vector2(*this).rotate(angle);
	}

	vector2& round()noexcept{
		this->x = std::round(this->x);
		this->y = std::round(this->y);
		return *this;
	}

	vector2 rounded()const noexcept{
		return vector2(*this).round();
	}

	/**
	 * @brief Convert to vector2 with different type of component.
	 * Convert this vector2 to a vector2 whose component type is different from T.
	 * Components are converted using constructor of target type passing the source
	 * component as argument of the target type constructor.
     * @return converted vector2.
     */
	template <class TS> vector2<TS> to()const noexcept{
		return vector2<TS>(TS(this->x), TS(this->y));
	}

	friend std::ostream& operator<<(std::ostream& s, const vector2<T>& vec){
		s << "(" << vec.x << ", " << vec.y << ")";
		return s;
	}
};

}

#include "vector3.hpp"

namespace r4{

template <class T> vector2<T>::vector2(const vector3<T>& vec)noexcept{
	this->operator=(vec);
}

template <class T> vector2<T>& vector2<T>::operator=(const vector3<T>& vec)noexcept{
	this->x = vec.x;
	this->y = vec.y;
	return (*this);
}

template <class T> vector2<T> vector2<T>::operator+(const vector3<T>& vec)const noexcept{
	return vector2<T>(
				this->x + vec.x,
				this->y + vec.y
			);
}

template <class T> vector2<T> vector2<T>::operator-(const vector3<T>& vec)const noexcept{
	return vector2<T>(
				this->x - vec.x,
				this->y - vec.y
			);
}

typedef vector2<bool> vec2b;
static_assert(sizeof(vec2b) == sizeof(bool) * 2, "size mismatch");

typedef vector2<int> vec2i;
static_assert(sizeof(vec2i) == sizeof(int) * 2, "size mismatch");

typedef vector2<unsigned> vec2ui;
static_assert(sizeof(vec2ui) == sizeof(unsigned) * 2, "size mismatch");

typedef vector2<float> vec2f;
static_assert(sizeof(vec2f) == sizeof(float) * 2, "size mismatch");

typedef vector2<double> vec2d;
static_assert(sizeof(vec2d) == sizeof(double) * 2, "size mismatch");

}
