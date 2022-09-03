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

#include <array>

#include <utki/math.hpp>

#include "quaternion.hpp"

// Under Windows and MSVC compiler there are 'min' and 'max' macros defined for some reason, get rid of them.
#ifdef min
#	undef min
#endif
#ifdef max
#	undef max
#endif

namespace r4{

template <class T, size_t S> class vector :
	// it's ok to inherit std::array<T> because T cannot be polymorphic, this is checked by static_assert
	public std::array<T, S>
{
	static_assert(!std::is_polymorphic<T>::value, "Template type parameter must not be a polymorphic type");

	static_assert(S > 0, "vector size template parameter S must be above zero");

	typedef std::array<T, S> base_type;
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
	 * @brief First vector component.
	 */
	T& r()noexcept{
		return this->operator[](0);
	}

	/**
	 * @brief First vector component.
	 */
	const T& r()const noexcept{
		return this->operator[](0);
	}

	/**
	 * @brief Second vector component.
	 */
	template <typename E = T>
	std::enable_if_t<(S > 1), E&> y()noexcept{
		return this->operator[](1);
	}

	/**
	 * @brief Second vector component.
	 */
	template <typename E = T>
	std::enable_if_t<(S > 1), const E&> y()const noexcept{
		return this->operator[](1);
	}

	/**
	 * @brief Second vector component.
	 */
	template <typename E = T>
	std::enable_if_t<(S > 1), E&> g()noexcept{
		return this->operator[](1);
	}

	/**
	 * @brief Second vector component.
	 */
	template <typename E = T>
	std::enable_if_t<(S > 1), const E&> g()const noexcept{
		return this->operator[](1);
	}

	/**
	 * @brief Third vector component.
	 */
	template <typename E = T>
	std::enable_if_t<(S > 2), E&> z()noexcept{
		return this->operator[](2);
	}

	/**
	 * @brief Third vector component.
	 */
	template <typename E = T>
	std::enable_if_t<(S > 2), const E&> z()const noexcept{
		return this->operator[](2);
	}

	/**
	 * @brief Third vector component.
	 */
	template <typename E = T>
	std::enable_if_t<(S > 2), E&> b()noexcept{
		return this->operator[](2);
	}

	/**
	 * @brief Third vector component.
	 */
	template <typename E = T>
	std::enable_if_t<(S > 2), const E&> b()const noexcept{
		return this->operator[](2);
	}

	/**
	 * @brief Fourth vector component.
	 */
	template <typename E = T>
	std::enable_if_t<(S > 3), E&> w()noexcept{
		return this->operator[](3);
	}

	/**
	 * @brief Fourth vector component.
	 */
	template <typename E = T>
	std::enable_if_t<(S > 3), const E&> w()const noexcept{
		return this->operator[](3);
	}

	/**
	 * @brief Fourth vector component.
	 */
	template <typename E = T>
	std::enable_if_t<(S > 3), E&> a()noexcept{
		return this->operator[](3);
	}

	/**
	 * @brief Fourth vector component.
	 */
	template <typename E = T>
	std::enable_if_t<(S > 3), const E&> a()const noexcept{
		return this->operator[](3);
	}

	/**
	 * @brief Default constructor.
	 * Default constructor does not initialize vector components to any values.
	 */
	constexpr vector() = default;

	/**
	 * @brief Constructor.
	 * Initializes vector components to given values.
	 * @param v - parameter pack with initializing values.
	 */
	template <typename... A, std::enable_if_t<sizeof...(A) == S, bool> = true>
	constexpr explicit vector(A... v)noexcept :
			base_type{T(v)...}
	{
		static_assert(sizeof...(v) == S, "number of constructor arguments is not equal to vector size");
	}

private:
	template <size_t... I>
	constexpr vector(std::initializer_list<T> vals, std::index_sequence<I...>)noexcept :
			base_type{ *std::next(vals.begin(), I)... }
	{}
public:
	/**
	 * @brief Construct initialized vector.
	 * Creates a vector and initializes its components by the given values.
	 * @param vals - initializer list of numbers to set as components of the vector.
	 */
	constexpr vector(std::initializer_list<T> vals) :
			vector(
					[&vals](){
						if(vals.size() == S){
							return vals;
						}
						std::cerr << "wrong number of elements in initializer list of vector(std::initializer_list), expected "
								<< S << ", got " << vals.size() << std::endl;
						std::abort();
					}(),
					std::make_index_sequence<S>()
				)
	{}

	/**
	 * @brief Constructor.
	 * Initializes all vector components to a given value.
	 * @param num - value to initialize all vector compone with.
	 */
	constexpr vector(T num)noexcept{
		for(auto& c : *this){
			c = num;
		}
	}

	/**
	 * @brief Constructor.
	 * Defined only for 4 component vector.
	 * Initializes first three vector components to the same given value and fourth component to another given value.
	 * @param num - value to use for initialization of first three vector components.
	 * @param w - value to use for initialization of fourth vector component.
	 */
	template <typename E = T> constexpr vector(std::enable_if_t<S == 4, E> num, T w)noexcept{
		for(size_t i = 0; i != S - 1; ++i){
			this->operator[](i) = num;
		}
		this->operator[](S - 1) = w;
	}

	/**
	 * @brief Constructor.
	 * Defined only for 3 component vector.
	 * Initializes components to a given values.
	 * @param vec - 2d vector to use for initialization of first two vector components.
	 * @param z - value to use for initialization of 3rd vector component.
	 */
	template <typename E = T> constexpr vector(const vector<T, 2>& vec, std::enable_if_t<S == 3, E> z = 0)noexcept :
			vector(vec.x(), vec.y(), z)
	{}

	/**
	 * @brief Constructor.
	 * Initializes components to a given values.
	 * @param vec - 4d vector to use for initialization of first two vector components.
	 */
	template <size_t SS> constexpr vector(const vector<T, SS>& vec)noexcept{
		this->operator=(vec);
	}

	/**
	 * @brief Constructor.
	 * Defined only for 4 component vector.
	 * Initializes components to a given values.
	 * @param vec - 2d vector to use for initialization of first two vector components.
	 * @param z - value to use for initialization of 3rd vector component.
	 * @param w - value to use for initialization of 4th vector component.
	 */
	template <typename E = T> constexpr vector(const vector<T, 2>& vec, std::enable_if_t<S == 4, E> z = 0, T w = 1)noexcept :
			vector(vec.x(), vec.y(), z, w)
	{}

	/**
	 * @brief Constructor.
	 * Defined only for 4 component vector.
	 * Initializes components to a given values.
	 * @param vec - 23 vector to use for initialization of first three vector components.
	 * @param w - value to use for initialization of 4th vector component.
	 */
	template <typename E = T> constexpr vector(const vector<T, 3>& vec, std::enable_if_t<S == 4, E> w = 1)noexcept :
			vector(vec.x(), vec.y(), vec.z(), w)
	{}

	/**
	 * @brief Convert to vector with different type of component.
	 * Convert this vector to a vector whose component type is different from T.
	 * Components are converted using constructor of target type passing the source
	 * component as argument of the target type constructor.
	 * @return converted vector.
	 */
	template <typename TT> vector<TT, S> to()const noexcept{
		vector<TT, S> ret;
		for(size_t i = 0; i != S; ++i){
			ret[i] = TT(this->operator[](i));
		}
		return ret;
	}

	/**
	 * @brief Assign from another vector.
	 * TODO:
	 * @param vec - 2d vector to assign first two components from.
	 * @return Reference to this vector object.
	 */
	template <size_t SS> vector& operator=(const vector<T, SS>& vec)noexcept{
		if constexpr (SS >= S){
			for(size_t i = 0; i != S; ++i){
				this->operator[](i) = vec[i];
			}
		}else if constexpr (S < 4 || SS >= 4){
			static_assert(SS < S, "");
			size_t i = 0;
			for(; i != SS; ++i){
				this->operator[](i) = vec[i];
			}
			for(; i != S; ++i){
				this->operator[](i) = T(0);
			}
		}else{
			static_assert(SS < 4, "");
			static_assert(S >= 4, "");
			size_t i = 0;
			for(; i != SS; ++i){
				this->operator[](i) = vec[i];
			}
			for(; i != 4; ++i){
				this->operator[](i) = T(0);
			}
			this->operator[](3) = T(1);
			for(; i != S; ++i){
				this->operator[](i) = T(0);
			}
		}
		return *this;
	}

	/**
	 * @brief Assign a number.
	 * Sets all 4 components of this vector to a given number.
	 * @param num - number to use for assignment.
	 * @return Reference to this vector object.
	 */
	vector& operator=(T num)noexcept{
		this->set(num);
		return *this;
	}

	/**
	 * @brief Set vector components to given values.
	 * @param a - parameter pack of values to set the vector to.
	 * @return Reference to this vector object.
	 */
	template <typename... A> vector& set(A... a)noexcept{
		this->base_type::operator=(base_type{T(a)...});
		return *this;
	}

	/**
	 * @brief Set all vector components to given value.
	 * @param val - value to set vector components to.
	 * @return Reference to this vector object.
	 */
	vector& set(T val)noexcept{
		for(auto& c : *this){
			c = val;
		}
		return *this;
	}

	/**
	 * @brief Add and assign.
	 * TODO:
	 * @param vec - vector to use for addition.
	 * @return Reference to this vector object.
	 */
	template <size_t SS> vector& operator+=(const vector<T, SS>& vec)noexcept{
		if constexpr (SS >= S){
			for(size_t i = 0; i != S; ++i){
				this->operator[](i) += vec[i];
			}
		}else if constexpr (S < 4 || SS >= 4){
			static_assert(SS < S, "");
			for(size_t i = 0; i != SS; ++i){
				this->operator[](i) += vec[i];
			}
		}else{
			static_assert(SS < 4, "");
			static_assert(S >= 4, "");
			for(size_t i = 0; i != SS; ++i){
				this->operator[](i) += vec[i];
			}
			this->operator[](3) += T(1);
		}
		return *this;
	}

	/**
	 * @brief Add vector.
	 * Adds this vector and given vector.
	 * @param vec - vector to add.
	 * @return Vector resulting from vector addition.
	 */
	vector operator+(const vector& vec)const noexcept{
		return (vector(*this) += vec);
	}

	/**
	 * @brief Add and assign.
	 * Adds this vector and given number.
	 * @param number - number to use for addition.
	 * @return Reference to this vector object.
	 */
	vector& operator+=(T number)noexcept{
		for(size_t i = 0; i != S; ++i){
			this->operator[](i) += number;
		}
		return *this;
	}

	/**
	 * @brief Add vector.
	 * Adds this vector and given number.
	 * @param number - number to use for addition.
	 * @return Vector resulting from vector and number addition.
	 */
	vector operator+(T number) noexcept{
		return (vector(*this) += number);
	}	

	/**
	 * @brief Subtract and assign.
	 * Subtracts given vector from this vector and assigns result back to this vector.
	 * @param vec - vector to subtract.
	 * @return Reference to this vector object.
	 */
	template <size_t SS> vector& operator-=(const vector<T, SS>& vec)noexcept{
		if constexpr (SS >= S){
			for(size_t i = 0; i != S; ++i){
				this->operator[](i) -= vec[i];
			}
		}else if constexpr (S < 4 || SS >= 4){
			static_assert(SS < S, "");
			for(size_t i = 0; i != SS; ++i){
				this->operator[](i) -= vec[i];
			}
		}else{
			static_assert(SS < 4, "");
			static_assert(S >= 4, "");
			for(size_t i = 0; i != SS; ++i){
				this->operator[](i) -= vec[i];
			}
			this->operator[](3) -= T(1);
		}
		return *this;
	}

	/**
	 * @brief Subtract vector.
	 * Subtracts given vector from this vector.
	 * @param vec - vector to subtract.
	 * @return Vector resulting from vector subtraction.
	 */
	vector operator-(const vector& vec)const noexcept{
		return (vector(*this) -= vec);
	}
	
	/**
	 * @brief Subtract and assign.
	 * Subtracts given number from this vector and assigns result back to this vector.
	 * @param number - number to subtract.
	 * @return Reference to this vector object.
	 */
	vector& operator-=(T number)noexcept{
		for(size_t i = 0; i != S; ++i){
			this->operator[](i) -= number;
		}
		return *this;
	}

	/**
	 * @brief Subtract vector.
	 * Subtracts given number from this vector.
	 * @param number - number to subtract.
	 * @return Vector resulting from number subtraction.
	 */
	vector operator-(T number)noexcept{
		return (vector(*this) -= number);
	}	

	/**
	 * @brief Unary minus.
	 * @return Negated vector.
	 */
	vector operator-()const noexcept{
		return vector(*this).negate();
	}

	/**
	 * @brief Multiply by scalar and assign.
	 * Multiplies this vector by scalar and assigns result back to this vector.
	 * @param num - scalar to multiply by.
	 * @return Reference to this vector object.
	 */
	vector& operator*=(T num)noexcept{
		for(auto& c : *this){
			c *= num;
		}
		return *this;
	}

	/**
	 * @brief Multiply by scalar.
	 * Multiplies this vector by scalar.
	 * @param num - scalar to multiply by.
	 * @return Vector resulting from multiplication of this vector by scalar.
	 */
	vector operator*(T num)const noexcept{
		return (vector(*this) *= num);
	}

	/**
	 * @brief Divide by scalar.
	 * Divides this vector by scalar.
	 * @param num - scalar to divide by.
	 * @return Vector resulting from division of this vector by scalar.
	 */
	vector operator/(T num)const noexcept{
		return vector(*this) /= num;
	}

	/**
	 * @brief Multiply scalar by vector.
	 * @param num - scalar to multiply.
	 * @param vec - vector to multiply by.
	 * @return Vector resulting from multiplication of given scalar by given vector.
	 */
	friend vector operator*(T num, const vector& vec)noexcept{
		return vec * num;
	}

	/**
	 * @brief Divide by scalar and assign.
	 * Divide this vector by scalar and assign result back to this vector.
	 * @param num - scalar to divide by.
	 * @return Reference to this vector object.
	 */
	vector& operator/=(T num)noexcept{
		ASSERT_INFO(num != 0, "vector::operator/=(): division by 0")
		for(auto& c : *this){
			c /= num;
		}
		return *this;
	}

	/**
	 * @brief Divide by scalar.
	 * Divide this vector by scalar.
	 * @param num - scalar to divide by.
	 * @return Vector resulting from division of this vector by scalars.
	 */
	vector operator/(T num)noexcept{
		ASSERT_INFO(num != 0, "vector::operator/(): division by 0")
		return (vector(*this) /= num);
	}

	/**
	 * @brief Dot product.
	 * @param vec -vector to multiply by.
	 * @return Dot product of this vector and given vector.
	 */
	T operator*(const vector& vec)const noexcept{
		T res = 0;
		for(size_t i = 0; i != S; ++i){
			res += this->operator[](i) * vec[i];
		}
		return res;
	}

	/**
	 * @brief Cross product.
	 * First three components of the resulting 4d vector is a result of cross
	 * product between two 3d vectors formed from first 3 components of initial 4d vectors.
	 * The forth component is a simple multiplication of 4th components of initial vectors.
	 * @param vec - vector to multiply by.
	 * @return Four-dimensional vector resulting from the cross product.
	 */
	template <typename E = vector> std::enable_if_t<S >= 3, E> operator%(const vector& vec)const noexcept{
		static_assert(S >= 3, "cross product makes no sense for vectors with less than 3 components");
		if constexpr (S == 3){
			return vector{
					this->y() * vec.z() - this->z() * vec.y(),
					this->z() * vec.x() - this->x() * vec.z(),
					this->x() * vec.y() - this->y() * vec.x()
				};
		}else{
			return vector{
				this->y() * vec.z() - this->z() * vec.y(),
				this->z() * vec.x() - this->x() * vec.z(),
				this->x() * vec.y() - this->y() * vec.x(),
				this->w() * vec.w()
			};
		}
	}

	/**
	 * @brief Component-wise multiplication.
	 * Performs component-wise multiplication of two vectors.
	 * The result of such operation is also a vector.
	 * @param vec - vector to multiply by.
	 * @return Vector resulting from component-wise multiplication.
	 */
	vector comp_mul(const vector& vec)const noexcept{
		vector res;
		for(size_t i = 0; i != S; ++i){
			res[i] = this->operator[](i) * vec[i];
		}
		return res;
	}

	/**
	 * @brief Component-wise multiplication.
	 * Performs component-wise multiplication of this vector by given vector.
	 * The result of such operation is also a vector and is stored in this vector.
	 * @param vec - vector to multiply by.
	 * @return reference to this vector.
	 */
	vector& comp_multiply(const vector& vec)noexcept{
		for(size_t i = 0; i != S; ++i){
			this->operator[](i) *= vec[i];
		}
		return *this;
	}

	/**
	 * @brief Component-wise division.
	 * Performs component-wise division of two vectors.
	 * Resulting vector is (x1 / x2, y1 / y2, z1 / z2, w1 / w2).
	 * The result of such operation is also vector.
	 * @param v - vector to divide by.
	 * @return Vector resulting from component-wise division.
	 */
	vector comp_div(const vector& v)const noexcept{
		vector res;
		for(size_t i = 0; i != S; ++i){
			res[i] = this->operator[](i) / v[i];
		}
		return res;
	}

	/**
	 * @brief Component-wise division.
	 * Performs component-wise division of this vector by another given vector.
	 * See comp_div() for details.
	 * @param v - vector to divide by.
	 * @return reference to this vector instance.
	 */
	vector& comp_divide(const vector& v)noexcept{
		for(size_t i = 0; i != S; ++i){
			this->operator[](i) /= v[i];
		}
		return *this;
	}

	/**
	 * @brief Negate this vector.
	 * Negates this vector.
	 * @return Reference to this vector object.
	 */
	vector& negate()noexcept{
		for(auto& c : *this){
			c = -c;
		}
		return *this;
	}

	/**
	 * @brief Calculate power 2 of vector norm.
	 * @return Power 2 of this vector norm.
	 */
	T norm_pow2()const noexcept{
		T res = 0;
		for(size_t i = 0; i != S; ++i){
			res += utki::pow2(this->operator[](i));
		}
		return res;
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
	vector& normalize()noexcept{
		T mag = this->norm();
		if(mag == 0){
			this->x() = 1;
			for(auto i = std::next(this->begin()); i != this->end(); ++i){
				*i = T(0);
			}
			return *this;
		}

		return (*this) /= this->norm();
	}

	/**
	 * @brief Calculate normalized vector.
	 * @return normalized vector.
	 */
	vector normed()const noexcept{
		return vector(*this).normalize();
	}

	/**
	 * @brief Rotate vector.
	 * Defined only for 2 component vector.
	 * Rotate this vector around (0, 0, 1) axis. Direction of the rotation is
	 * determined by right-hand rule. I.e. positive angle rotation is from X-axis to Y-axis.
	 * @param angle - angle of rotation in radians.
	 * @return Reference to this vector object.
	 */
	template <typename E = T> vector& rotate(std::enable_if_t<S == 2, E> angle)noexcept{
		using std::sin;
		using std::cos;
		T cosa = cos(angle);
		T sina = sin(angle);
		T tmp = this->x() * cosa - this->y() * sina;
		this->y() = this->y() * cosa + this->x() * sina;
		this->x() = tmp;
		return *this;
	}

	/**
	 * @brief Rotation of vector.
	 * Defined only for 2 component vector.
	 * Calculate vector resulting from rotation of this vector around (0, 0, 1) axis.
	 * Direction of the rotation is determined by right-hand rule.
	 * @param angle - angle of rotation in radians.
	 * @return Vector resulting from rotation of this vector.
	 */
	template <typename E = T> vector rot(std::enable_if_t<S == 2, E> angle)const noexcept{
		return vector(*this).rotate(angle);
	}

	/**
	 * @brief Round vector components.
	 * @param v - vector to round.
	 * @return rounded vector.
	 */
	friend vector round(const vector& v)noexcept{
		using std::round;
		vector ret;
		for(size_t i = 0; i != S; ++i){
			ret[i] = round(v[i]);
		}
		return ret;
	}

	/**
	 * @brief Ceil vector components.
	 * @param v - vector to ceil.
	 * @return ceiled vector.
	 */
	friend vector ceil(const vector& v)noexcept{
		using std::ceil;
		vector ret;
		for(size_t i = 0; i != S; ++i){
			ret[i] = ceil(v[i]);
		}
		return ret;
	}

	/**
	 * @brief Floor vector components.
	 * @param v - vector to floor.
	 * @return floored vector.
	 */
	friend vector floor(const vector& v)noexcept{
		using std::floor;
		vector ret;
		for(size_t i = 0; i != S; ++i){
			ret[i] = floor(v[i]);
		}
		return ret;
	}

	/**
	 * @brief Snap each vector component to 0.
	 * For each component, set it to 0 if its absolute value does not exceed the given threshold.
	 * @param threshold - the snapping threshold.
	 * @return reference to this vector.
	 */
	vector& snap_to_zero(T threshold)noexcept{
		for(auto& c : *this){
			using std::abs;
			if(abs(c) <= threshold){
				c = 0;
			}
		}
		return *this;
	}

	/**
	 * @brief Check if all vector components are zero.
	 * @return true if all vector components are zero.
	 * @return false otherwise.
	 */
	bool is_zero()const noexcept{
		for(auto& c : *this){
			if(c != 0){
				return false;
			}
		}
		return true;
	}

	/**
	 * @brief Check if all vector components are not zero.
	 * @return true if all vector components are not zero.
	 * @return false otherwise.
	 */
	bool is_not_zero()const noexcept{
		for(auto& c : *this){
			if(c == 0){
				return false;
			}
		}
		return true;
	}

	/**
	 * @brief Check if all vector components are positive or zero.
	 * @return true if all vector components are positive or zero.
	 * @return false otherwise.
	 */
	bool is_positive_or_zero()const noexcept{
		for(auto& c : *this){
			if(c < 0){
				return false;
			}
		}
		return true;
	}

	/**
	 * @brief Check if all vector components are positive.
	 * @return true if all vector components are positive.
	 * @return false otherwise.
	 */
	bool is_positive()const noexcept{
		for(auto& c : *this){
			if(c <= 0){
				return false;
			}
		}
		return true;
	}

	/**
	 * @brief Check if all vector components are negative.
	 * @return true if all vector components are negative.
	 * @return false otherwise.
	 */
	bool is_negative()const noexcept{
		for(auto& c : *this){
			if(c >= 0){
				return false;
			}
		}
		return true;
	}

	/**
	 * @brief Absolute vector value.
	 * @param v - vector to take absolute value of.
	 * @return vector holding absolute values of this vector's components.
	 */
	friend vector abs(const vector& v)noexcept{
		using std::abs;
		vector ret;
		for(size_t i = 0; i != S; ++i){
			ret[i] = abs(v[i]);
		}
		return ret;
	}

	/**
	 * @brief Project this vector onto a given vector.
	 * @param vec - vector to project onto, it does not have to be normalized.
	 * @return Reference to this vector object.
	 */
	vector& project(const vector& vec)noexcept{
		ASSERT(this->norm_pow2() != 0)
		(*this) = vec * (vec * (*this)) / vec.norm_pow2();
		return *this;
	}

	/**
	 * @brief Rotate this vector.
	 * Rotate this vector with unit quaternion.
	 * @param q - quaternion which defines the rotation.
	 * @return Reference to this vector object.
	 */
	template <typename E = T> vector& rotate(const quaternion<std::enable_if_t<S == 3 || S == 4, E>>& q)noexcept;

	/**
	 * @brief Get component-wise minimum of two vectors.
	 * @param va - first vector.
	 * @param vb - second vector.
	 * @return vector whose components are component-wise minimum of initial vectors.
	 */
	friend vector min(const vector& va, const vector& vb)noexcept{
		using std::min;
		vector ret;
		for(size_t i = 0; i != S; ++i){
			ret[i] = min(va[i], vb[i]);
		}
		return ret;
	}

	/**
	 * @brief Get component-wise maximum of two vectors.
	 * @param va - first vector.
	 * @param vb - second vector.
	 * @return vector whose components are component-wise maximum of initial vectors.
	 */
	friend vector max(const vector& va, const vector& vb)noexcept{
		using std::max;
		vector ret;
		for(size_t i = 0; i != S; ++i){
			ret[i] = max(va[i], vb[i]);
		}
		return ret;
	}

	friend std::ostream& operator<<(std::ostream& s, const vector<T, S>& vec){
		static_assert(S >= 1, "");
		s << vec.x();
		for(auto i = std::next(vec.begin()); i != vec.end(); ++i){
			s << " " << (*i);
		}
		return s;
	}
};

template <typename TT> using vector2 = vector<TT, 2>;
template <typename TT> using vector3 = vector<TT, 3>;
template <typename TT> using vector4 = vector<TT, 4>;

static_assert(sizeof(vector<float, 4>) == sizeof(float) * 4, "size mismatch");
static_assert(sizeof(vector<double, 4>) == sizeof(double) * 4, "size mismatch");

}

#include "matrix.hpp"

namespace r4{

template <class T, size_t S>
template <typename E>
vector<T, S>& vector<T, S>::rotate(const quaternion<std::enable_if_t<S == 3 || S == 4, E>>& q)noexcept{
	*this = q.template to_matrix<S>() * (*this);
	return *this;
}

}
