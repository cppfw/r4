/*
The MIT License (MIT)

Copyright (c) 2015-2024 Ivan Gagis <igagis@gmail.com>

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

#include <utki/debug.hpp>
#include <utki/math.hpp>

// Under Windows and MSVC compiler there are 'min' and 'max' macros defined for some reason, get rid of them.
#ifdef min
#	undef min
#endif
#ifdef max
#	undef max
#endif

#ifdef assert
#	undef assert
#endif

namespace r4 {

template <class component_type>
class quaternion;

template <class component_type, size_t dimension>
class vector :
	// it's ok to inherit std::array<component_type> because r4::vector only defines methods
	// and doesn't define any new member variables (checked by static_assert after the
	// class declaration), so it is ok that std::array has non-virtual destructor
	public std::array<component_type, dimension>
{
	static_assert(dimension > 0, "vector size template parameter dimension must be above zero");

public:
	using base_type = std::array<component_type, dimension>;

	/**
	 * @brief First vector component.
	 */
	component_type& x() noexcept
	{
		return this->operator[](0);
	}

	/**
	 * @brief First vector component.
	 */
	const component_type& x() const noexcept
	{
		return this->operator[](0);
	}

	/**
	 * @brief First vector component.
	 */
	component_type& r() noexcept
	{
		return this->operator[](0);
	}

	/**
	 * @brief First vector component.
	 */
	const component_type& r() const noexcept
	{
		return this->operator[](0);
	}

	/**
	 * @brief Second vector component.
	 */
	template <typename enable_type = component_type>
	std::enable_if_t<(dimension > 1), enable_type&> y() noexcept
	{
		return this->operator[](1);
	}

	/**
	 * @brief Second vector component.
	 */
	template <typename enable_type = component_type>
	std::enable_if_t<(dimension > 1), const enable_type&> y() const noexcept
	{
		return this->operator[](1);
	}

	/**
	 * @brief Second vector component.
	 */
	template <typename enable_type = component_type>
	std::enable_if_t<(dimension > 1), enable_type&> g() noexcept
	{
		return this->operator[](1);
	}

	/**
	 * @brief Second vector component.
	 */
	template <typename enable_type = component_type>
	std::enable_if_t<(dimension > 1), const enable_type&> g() const noexcept
	{
		return this->operator[](1);
	}

	/**
	 * @brief Third vector component.
	 */
	template <typename enable_type = component_type>
	std::enable_if_t<(dimension > 2), enable_type&> z() noexcept
	{
		return this->operator[](2);
	}

	/**
	 * @brief Third vector component.
	 */
	template <typename enable_type = component_type>
	std::enable_if_t<(dimension > 2), const enable_type&> z() const noexcept
	{
		return this->operator[](2);
	}

	/**
	 * @brief Third vector component.
	 */
	template <typename enable_type = component_type>
	std::enable_if_t<(dimension > 2), enable_type&> b() noexcept
	{
		return this->operator[](2);
	}

	/**
	 * @brief Third vector component.
	 */
	template <typename enable_type = component_type>
	std::enable_if_t<(dimension > 2), const enable_type&> b() const noexcept
	{
		return this->operator[](2);
	}

	/**
	 * @brief Fourth vector component.
	 */
	template <typename enable_type = component_type>
	std::enable_if_t<(dimension > 3), enable_type&> w() noexcept
	{
		return this->operator[](3);
	}

	/**
	 * @brief Fourth vector component.
	 */
	template <typename enable_type = component_type>
	std::enable_if_t<(dimension > 3), const enable_type&> w() const noexcept
	{
		return this->operator[](3);
	}

	/**
	 * @brief Fourth vector component.
	 */
	template <typename enable_type = component_type>
	std::enable_if_t<(dimension > 3), enable_type&> a() noexcept
	{
		return this->operator[](3);
	}

	/**
	 * @brief Fourth vector component.
	 */
	template <typename enable_type = component_type>
	std::enable_if_t<(dimension > 3), const enable_type&> a() const noexcept
	{
		return this->operator[](3);
	}

	/**
	 * @brief Default constructor.
	 * Default constructor does not initialize vector components to any values.
	 */
	// NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
	constexpr vector() = default;

	/**
	 * @brief Constructor.
	 * Initializes vector components to given values.
	 * @param v - parameter pack with initializing values.
	 */
	template <
		typename... arguments_type, //
		std::enable_if_t<
			sizeof...(arguments_type) == dimension, //
			bool> = true>
	constexpr explicit vector(arguments_type... v) noexcept :
		base_type{component_type(v)...}
	{
		static_assert(sizeof...(v) == dimension, "number of constructor arguments is not equal to vector size");
	}

private:
	template <size_t... indices>
	constexpr vector(
		std::initializer_list<component_type> vals, //
		std::index_sequence<indices...>
	) noexcept :
		base_type{*std::next(std::cbegin(vals), indices)...}
	{}

public:
	/**
	 * @brief Construct initialized vector.
	 * Creates a vector and initializes its components by the given values.
	 * @param vals - initializer list of numbers to set as components of the vector.
	 */
	constexpr vector(std::initializer_list<component_type> vals) :
		vector(
			[&vals]() {
				if (vals.size() == dimension) {
					return vals;
				}
				utki::assert(
					false,
					[&](auto& o) {
						o << "wrong number of elements in initializer list of vector(std::initializer_list), expected "
						  << dimension << ", got " << vals.size() << std::endl;
					},
					SL
				);
				return std::initializer_list<component_type>();
			}(),
			std::make_index_sequence<dimension>()
		)
	{}

	/**
	 * @brief Constructor.
	 * Initializes all vector components to a given value.
	 * @param num - value to initialize all vector compone with.
	 */
	constexpr vector(component_type num) noexcept
	{
		this->comp_operation([&num](const auto&) {
			return num;
		});
	}

	/**
	 * @brief Constructor.
	 * Defined only for 4 component vector.
	 * Initializes first three vector components to the same given value and fourth component to another given value.
	 * @param num - value to use for initialization of first three vector components.
	 * @param w - value to use for initialization of fourth vector component.
	 */
	template <typename enable_type = component_type>
	constexpr vector(std::enable_if_t<dimension == 4, enable_type> num, component_type w) noexcept
	{
		std::for_each_n(this->begin(), dimension - 1, [&num](auto& a) {
			a = num;
		});
		this->back() = w;
	}

	/**
	 * @brief Constructor.
	 * Defined only for 3 component vector.
	 * Initializes components to a given values.
	 * @param vec - 2d vector to use for initialization of first two vector components.
	 * @param z - value to use for initialization of 3rd vector component.
	 */
	template <typename enable_type = component_type>
	constexpr vector(const vector<component_type, 2>& vec, std::enable_if_t<dimension == 3, enable_type> z = 0) noexcept
		:
		vector(vec.x(), vec.y(), z)
	{}

	/**
	 * @brief Constructor.
	 * Initializes components to a given values.
	 * In case the given vector has lower dimension than this one the rest of the components will be initialized to 0.
	 * @param vec - vector to use for initialization of vector components.
	 */
	template <size_t another_dimension>
	constexpr vector(const vector<component_type, another_dimension>& vec) noexcept
	{
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
	template <typename enable_type = component_type>
	constexpr vector(
		const vector<component_type, 2>& vec,
		std::enable_if_t<dimension == 4, enable_type> z = 0,
		component_type w = 0
	) noexcept :
		vector(vec.x(), vec.y(), z, w)
	{}

	/**
	 * @brief Constructor.
	 * Defined only for 4 component vector.
	 * Initializes components to a given values.
	 * @param vec - 3d vector to use for initialization of first three vector components.
	 * @param w - value to use for initialization of 4th vector component.
	 */
	template <typename enable_type = component_type>
	constexpr vector(const vector<component_type, 3>& vec, std::enable_if_t<dimension == 4, enable_type> w = 0) noexcept
		:
		vector(vec.x(), vec.y(), vec.z(), w)
	{}

	/**
	 * @brief Convert to vector with different type of component.
	 * Convert this vector to a vector whose component type is different from component_type.
	 * Components are converted using constructor of target type passing the source
	 * component as argument of the target type constructor.
	 * @return converted vector.
	 */
	template <typename another_component_type>
	vector<another_component_type, dimension> to() const noexcept
	{
		vector<another_component_type, dimension> ret;
		std::transform(this->begin(), this->end(), ret.begin(), [](const auto& a) {
			return another_component_type(a);
		});
		return ret;
	}

	/**
	 * @brief Unary component-wise operation.
	 * Perform unary operation on each component of the vector.
	 * @param op - unary operation to perform on each component of the vector.
	 * @return Resulting vector.
	 */
	template <typename unary_operation_type>
	auto comp_op(unary_operation_type op) const //
		-> vector<
			decltype(op(std::declval<component_type>())), //
			dimension>
	{
		vector<
			decltype(op(std::declval<component_type>())), //
			dimension>
			res{};
		std::transform(
			this->begin(), //
			this->end(),
			res.begin(),
			op
		);
		return res;
	}

	/**
	 * @brief Binary component-wise operation.
	 * Perform binary operation on each component of two vectors.
	 * @param vec - second vector.
	 * @param op - binary operation to perform on each component of two vectors.
	 * @return Resulting vector.
	 */
	template <typename binary_operation_type>
	auto comp_op(
		const vector& vec, //
		binary_operation_type op
	) const
		-> vector<
			decltype(op(
				std::declval<component_type>(), //
				std::declval<component_type>()
			)), //
			dimension>
	{
		vector<
			decltype(op(
				std::declval<component_type>(), //
				std::declval<component_type>()
			)), //
			dimension>
			res{};
		std::transform(
			this->begin(), //
			this->end(),
			vec.begin(),
			res.begin(),
			op
		);
		return res;
	}

	/**
	 * @brief Unary component-wise operation.
	 * Perform unary operation on each component of the vector.
	 * The result is saved into this vector.
	 * @param op - unary operation to perform on each component of the vector.
	 * @return Reference to this vector.
	 */
	template <typename unary_operation_type>
	vector& comp_operation(unary_operation_type op)
	{
		std::transform(
			this->begin(), //
			this->end(),
			this->begin(),
			op
		);
		return *this;
	}

	/**
	 * @brief Binary component-wise operation.
	 * Perform binary operation on each component of two vectors.
	 * The result is saved into this vector.
	 * @param vec - second vector.
	 * @param op - binary operation to perform on each component of two vectors.
	 * @return Reference to this vector.
	 */
	template <typename binary_operation_type>
	vector& comp_operation(const vector& vec, binary_operation_type op)
	{
		std::transform(this->begin(), this->end(), vec.begin(), this->begin(), op);
		return *this;
	}

	/**
	 * @brief Assign from another vector.
	 * TODO:
	 * @param vec - 2d vector to assign first two components from.
	 * @return Reference to this vector object.
	 */
	template <size_t another_dimension>
	vector& operator=(const vector<component_type, another_dimension>& vec) noexcept
	{
		if constexpr (another_dimension >= dimension) {
			std::transform( //
				this->begin(),
				this->end(),
				vec.begin(),
				this->begin(),
				[](const auto& a, const auto& b) {
					return b;
				}
			);
		} else {
			static_assert(
				another_dimension < dimension,
				"dimension of another vector cannot be greater than of this vector"
			);
			auto i = std::transform( //
				vec.begin(),
				vec.end(),
				this->begin(),
				this->begin(),
				[](const auto& a, const auto& b) {
					return a;
				}
			);
			std::transform(i, this->end(), i, [](const auto&) {
				return component_type(0);
			});
		}
		return *this;
	}

	/**
	 * @brief Assign a number.
	 * Sets all 4 components of this vector to a given number.
	 * @param num - number to use for assignment.
	 * @return Reference to this vector object.
	 */
	vector& operator=(component_type num) noexcept
	{
		this->set(num);
		return *this;
	}

	/**
	 * @brief Set vector components to given values.
	 * @param a - parameter pack of values to set the vector to.
	 * @return Reference to this vector object.
	 */
	template <typename... arguments_type>
	// enable this method only if number of arguments passed is same as the vector dimension
	std::enable_if_t<sizeof...(arguments_type) == dimension, vector&> //
	set(arguments_type... a) noexcept
	{
		this->base_type::operator=(base_type{component_type(a)...});
		return *this;
	}

	/**
	 * @brief Set all vector components to given value.
	 * @param val - value to set vector components to.
	 * @return Reference to this vector object.
	 */
	vector& set(component_type val) noexcept
	{
		return this->comp_operation([&val](const auto&) {
			return val;
		});
		return *this;
	}

	/**
	 * @brief Add and assign.
	 * TODO:
	 * @param vec - vector to use for addition.
	 * @return Reference to this vector object.
	 */
	template <size_t another_dimension>
	vector& operator+=(const vector<component_type, another_dimension>& vec) noexcept
	{
		if constexpr (another_dimension >= dimension) {
			std::transform( //
				this->begin(),
				this->end(),
				vec.begin(),
				this->begin(),
				[](const auto& a, const auto& b) {
					return a + b;
				}
			);
		} else {
			static_assert(
				another_dimension < dimension,
				"dimension of another vector cannot be greater than of this vector"
			);
			std::transform( //
				vec.begin(),
				vec.end(),
				this->begin(),
				this->begin(),
				[](const auto& a, const auto& b) {
					return a + b;
				}
			);
		}
		return *this;
	}

	/**
	 * @brief Add vector.
	 * Adds this vector and given vector.
	 * @param vec - vector to add.
	 * @return Vector resulting from vector addition.
	 */
	vector operator+(const vector& vec) const noexcept
	{
		return this->comp_op(
			vec, //
			std::plus<component_type>()
		);
	}

	/**
	 * @brief Add and assign.
	 * Adds this vector and given number.
	 * @param number - number to use for addition.
	 * @return Reference to this vector object.
	 */
	vector& operator+=(component_type number) noexcept
	{
		return this->comp_operation([&number](auto& a) {
			return a + number;
		});
	}

	/**
	 * @brief Add vector.
	 * Adds this vector and given number.
	 * @param number - number to use for addition.
	 * @return Vector resulting from vector and number addition.
	 */
	vector operator+(component_type number) noexcept
	{
		return (vector(*this) += number);
	}

	/**
	 * @brief Subtract and assign.
	 * Subtracts given vector from this vector and assigns result back to this vector.
	 * @param vec - vector to subtract.
	 * @return Reference to this vector object.
	 */
	template <size_t another_dimension>
	vector& operator-=(const vector<component_type, another_dimension>& vec) noexcept
	{
		(*this) += -vec;
		return *this;
	}

	/**
	 * @brief Subtract vector.
	 * Subtracts given vector from this vector.
	 * @param vec - vector to subtract.
	 * @return Vector resulting from vector subtraction.
	 */
	vector operator-(const vector& vec) const noexcept
	{
		return this->comp_op(
			vec, //
			std::minus<component_type>()
		);
	}

	/**
	 * @brief Subtract and assign.
	 * Subtracts given number from this vector and assigns result back to this vector.
	 * @param number - number to subtract.
	 * @return Reference to this vector object.
	 */
	vector& operator-=(component_type number) noexcept
	{
		(*this) += -number;
		return *this;
	}

	/**
	 * @brief Subtract vector.
	 * Subtracts given number from this vector.
	 * @param number - number to subtract.
	 * @return Vector resulting from number subtraction.
	 */
	vector operator-(component_type number) noexcept
	{
		return (vector(*this) -= number);
	}

	/**
	 * @brief Multiply by scalar and assign.
	 * Multiplies this vector by scalar and assigns result back to this vector.
	 * @param num - scalar to multiply by.
	 * @return Reference to this vector object.
	 */
	vector& operator*=(component_type num) noexcept
	{
		return this->comp_operation([&num](auto& a) {
			return a * num;
		});
	}

	/**
	 * @brief Multiply by scalar.
	 * Multiplies this vector by scalar.
	 * @param num - scalar to multiply by.
	 * @return Vector resulting from multiplication of this vector by scalar.
	 */
	vector operator*(component_type num) const noexcept
	{
		return (vector(*this) *= num);
	}

	/**
	 * @brief Divide by scalar.
	 * Divides this vector by scalar.
	 * @param num - scalar to divide by.
	 * @return Vector resulting from division of this vector by scalar.
	 */
	vector operator/(component_type num) const noexcept
	{
		return vector(*this) /= num;
	}

	/**
	 * @brief Multiply scalar by vector.
	 * @param num - scalar to multiply.
	 * @param vec - vector to multiply by.
	 * @return Vector resulting from multiplication of given scalar by given vector.
	 */
	friend vector operator*(component_type num, const vector& vec) noexcept
	{
		return vec * num;
	}

	/**
	 * @brief Divide by scalar and assign.
	 * Divide this vector by scalar and assign result back to this vector.
	 * @param num - scalar to divide by.
	 * @return Reference to this vector object.
	 */
	vector& operator/=(component_type num) noexcept
	{
		ASSERT(num != 0, [&](auto& o) {
			o << "vector::operator/=(): division by 0";
		})
		return this->comp_operation([&num](auto& a) {
			return a / num;
		});
	}

	/**
	 * @brief Dot product.
	 * @param vec - vector to multiply by.
	 * @return Dot product of this vector and given vector.
	 */
	component_type dot(const vector& vec) const noexcept
	{
		component_type res = 0;

		this->comp_op(
			vec, //
			[&res](const auto& a, const auto& b) {
				res += a * b;
				return component_type();
			}
		);

		return res;
	}

	/**
	 * @brief Dot product.
	 * Deprecated, use vector::dot(vector) function.
	 * @param vec - vector to multiply by.
	 * @return Dot product of this vector and given vector.
	 */
	component_type operator*(const vector& vec) const noexcept
	{
		return this->dot(vec);
	}

	/**
	 * @brief Cross product.
	 * For 4d vectors, first three components of the resulting 4d vector is a result of cross
	 * product between two 3d vectors formed from first 3 components of initial 4d vectors.
	 * The forth component is a simple multiplication of 4th components of initial vectors.
	 * @param vec - vector to multiply by.
	 * @return Cross product of this vector by given vector.
	 */
	template <typename enable_type = std::conditional_t<dimension == 2, typename base_type::value_type, vector>>
	std::enable_if_t<dimension == 2 || dimension == 3 || dimension == 4, enable_type> //
	cross(const vector& vec) const noexcept
	{
		if constexpr (dimension == 2) {
			return this->x() * vec.y() - this->y() * vec.x();
		} else if constexpr (dimension == 3) {
			return vector{
				this->y() * vec.z() - this->z() * vec.y(),
				this->z() * vec.x() - this->x() * vec.z(),
				this->x() * vec.y() - this->y() * vec.x()
			};
		} else {
			static_assert(dimension == 4, "cross product makes no sense for non 3d (4d) vectors");
			return vector{
				this->y() * vec.z() - this->z() * vec.y(),
				this->z() * vec.x() - this->x() * vec.z(),
				this->x() * vec.y() - this->y() * vec.x(),
				this->w() * vec.w()
			};
		}
	}

	/**
	 * @brief Cross product.
	 * First three components of the resulting 4d vector is a result of cross
	 * product between two 3d vectors formed from first 3 components of initial 4d vectors.
	 * The forth component is a simple multiplication of 4th components of initial vectors.
	 * @param vec - vector to multiply by.
	 * @return Cross product of this vector by given vector.
	 */
	template <typename enable_type = vector>
	// TODO: remove deprecated stuff
	[[deprecated("use cross()")]] std::enable_if_t<dimension >= 3, enable_type> operator%(
		const vector& vec
	) const noexcept
	{
		return this->cross(vec);
	}

	/**
	 * @brief Component-wise multiplication.
	 * Performs component-wise multiplication of two vectors.
	 * The result of such operation is also a vector.
	 * @param vec - vector to multiply by.
	 * @return Vector resulting from component-wise multiplication.
	 */
	vector comp_mul(const vector& vec) const noexcept
	{
		return this->comp_op(vec, std::multiplies<component_type>());
	}

	/**
	 * @brief Component-wise multiplication.
	 * Performs component-wise multiplication of this vector by given vector.
	 * The result of such operation is also a vector and is stored in this vector.
	 * @param vec - vector to multiply by.
	 * @return reference to this vector.
	 */
	vector& comp_multiply(const vector& vec) noexcept
	{
		return this->comp_operation(vec, std::multiplies<component_type>());
	}

	/**
	 * @brief Component-wise division.
	 * Performs component-wise division of two vectors.
	 * Resulting vector is (x1 / x2, y1 / y2, z1 / z2, w1 / w2).
	 * The result of such operation is also vector.
	 * @param v - vector to divide by.
	 * @return Vector resulting from component-wise division.
	 */
	vector comp_div(const vector& v) const noexcept
	{
		return this->comp_op(v, std::divides<component_type>());
	}

	/**
	 * @brief Component-wise division.
	 * Performs component-wise division of this vector by another given vector.
	 * See comp_div() for details.
	 * @param v - vector to divide by.
	 * @return reference to this vector instance.
	 */
	vector& comp_divide(const vector& v) noexcept
	{
		return this->comp_operation(v, std::divides<component_type>());
	}

private:
	// MSVC compiler doesn't allow negating unsigned types,
	// this is why we cannot use std::negate and introduce our own
	// negation functor
	struct negate_functor {
		component_type operator()(component_type a) const
		{
			if constexpr (std::is_signed_v<component_type>) {
				return -a;
			} else {
				return (~a + component_type(1));
			}
		}
	};

public:
	/**
	 * @brief Unary minus.
	 * @return Negated vector.
	 */
	vector operator-() const noexcept
	{
		return this->comp_op(negate_functor());
	}

	/**
	 * @brief Negate this vector.
	 * Negates this vector.
	 * @return Reference to this vector object.
	 */
	vector& negate() noexcept
	{
		return this->comp_operation(negate_functor());
	}

	/**
	 * @brief Calculate power 2 of the vector's norm.
	 * @return This vector's norm to the power of 2.
	 */
	component_type norm_pow2() const noexcept
	{
		component_type res = 0;

		for (const auto& e : *this) {
			res += utki::pow2(e);
		}

		return res;
	}

	/**
	 * @brief Calculate vector norm.
	 * @return Vector norm.
	 */
	component_type norm() const noexcept
	{
		return component_type(sqrt(this->norm_pow2()));
	}

	/**
	 * @brief Normalize this vector.
	 * Normalizes this vector.
	 * If norm is 0 then the result is vector (1, 0, 0, 0).
	 * @return Reference to this vector object.
	 */
	vector& normalize() noexcept
	{
		component_type mag = this->norm();
		ASSERT(mag >= component_type(0))
		if (mag != component_type(0)) {
			return (*this) /= mag;
		}

		this->x() = 1;
		std::for_each(std::next(this->begin()), this->end(), [](const auto&) {
			return component_type(0);
		});
		return *this;
	}

	/**
	 * @brief Calculate normalized vector.
	 * @return normalized vector.
	 */
	vector normed() const noexcept
	{
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
	template <typename enable_type = component_type>
	vector& rotate(std::enable_if_t<dimension == 2, enable_type> angle) noexcept
	{
		using std::sin;
		using std::cos;
		component_type cosa = cos(angle);
		component_type sina = sin(angle);
		component_type tmp = this->x() * cosa - this->y() * sina;
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
	template <typename enable_type = component_type>
	vector rot(std::enable_if_t<dimension == 2, enable_type> angle) const noexcept
	{
		return vector(*this).rotate(angle);
	}

	/**
	 * @brief Round vector components.
	 * @param v - vector to round.
	 * @return rounded vector.
	 */
	friend vector round(const vector& v) noexcept
	{
		return v.comp_op([](const auto& a) {
			using std::round;
			return component_type(round(a));
		});
	}

	/**
	 * @brief Ceil vector components.
	 * @param v - vector to ceil.
	 * @return ceiled vector.
	 */
	friend vector ceil(const vector& v) noexcept
	{
		return v.comp_op([](const auto& a) {
			using std::ceil;
			return component_type(ceil(a));
		});
	}

	/**
	 * @brief Floor vector components.
	 * @param v - vector to floor.
	 * @return floored vector.
	 */
	friend vector floor(const vector& v) noexcept
	{
		return v.comp_op([](const auto& a) {
			using std::floor;
			return component_type(floor(a));
		});
	}

	/**
	 * @brief Snap each vector component to 0.
	 * For each component, set it to 0 if its absolute value does not exceed the given threshold.
	 * @param threshold - the snapping threshold.
	 * @return reference to this vector.
	 */
	vector& snap_to_zero(component_type threshold) noexcept
	{
		return this->comp_operation([&threshold](const auto& a) {
			using std::abs;
			if (abs(a) <= threshold) {
				return component_type(0);
			}
			return a;
		});
	}

	/**
	 * @brief Check if all vector components are zero.
	 * @return true if all vector components are zero.
	 * @return false otherwise.
	 */
	bool is_zero() const noexcept
	{
		for (const auto& c : *this) {
			if (c != 0) {
				return false;
			}
		}
		return true;
	}

	/**
	 * @brief Check if any of the vector components is zero.
	 * @return true if at least one component of the vector is zero.
	 * @return false otherwise.
	 */
	bool is_any_zero() const noexcept
	{
		for (const auto& c : *this) {
			if (c == 0) {
				return true;
			}
		}
		return false;
	}

	/**
	 * @brief Check if all vector components are not zero.
	 * @return true if all vector components are not zero.
	 * @return false otherwise.
	 */
	bool is_not_zero() const noexcept
	{
		for (auto& c : *this) {
			if (c == 0) {
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
	bool is_positive_or_zero() const noexcept
	{
		for (auto& c : *this) {
			if (c < 0) {
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
	bool is_positive() const noexcept
	{
		for (auto& c : *this) {
			if (c <= 0) {
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
	bool is_negative() const noexcept
	{
		for (auto& c : *this) {
			if (c >= 0) {
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
	friend vector abs(const vector& v) noexcept
	{
		return v.comp_op([](const auto& a) {
			using std::abs;
			return abs(a);
		});
	}

	/**
	 * @brief Project this vector onto a given vector.
	 * @param vec - vector to project onto, it does not have to be normalized.
	 * @return Reference to this vector object.
	 */
	vector& project(const vector& vec) noexcept
	{
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
	template <typename enable_type = component_type>
	vector& rotate(const quaternion<std::enable_if_t<dimension == 3 || dimension == 4, enable_type>>& q) noexcept;

	/**
	 * @brief Get component-wise minimum of two vectors.
	 * @param va - first vector.
	 * @param vb - second vector.
	 * @return vector whose components are component-wise minimum of initial vectors.
	 */
	friend vector min(const vector& va, const vector& vb) noexcept
	{
		return va.comp_op(vb, [](const auto& a, const auto& b) {
			using std::min;
			return min(a, b);
		});
	}

	/**
	 * @brief Get component-wise maximum of two vectors.
	 * @param va - first vector.
	 * @param vb - second vector.
	 * @return vector whose components are component-wise maximum of initial vectors.
	 */
	friend vector max(const vector& va, const vector& vb) noexcept
	{
		return va.comp_op(vb, [](const auto& a, const auto& b) {
			using std::max;
			return max(a, b);
		});
	}

	friend std::ostream& operator<<(std::ostream& s, const vector<component_type, dimension>& vec)
	{
		static_assert(dimension >= 1, "dimension cannot be 0");
		if constexpr (std::is_same_v<component_type, uint8_t>) {
			s << unsigned(vec.x());
		} else {
			s << vec.x();
		}
		for (auto i = std::next(vec.begin()); i != vec.end(); ++i) {
			s << " ";
			if constexpr (std::is_same_v<component_type, uint8_t>) {
				s << unsigned(*i);
			} else {
				s << (*i);
			}
		}
		return s;
	}
};

template <typename component_type>
using vector2 = vector<component_type, 2>;
template <typename component_type>
using vector3 = vector<component_type, 3>;
template <typename component_type>
using vector4 = vector<component_type, 4>;

static_assert(sizeof(vector<float, 4>) == sizeof(float) * 4, "size mismatch");
static_assert(sizeof(vector<double, 4>) == sizeof(double) * 4, "size mismatch");

static_assert(
	sizeof(vector4<int>) == sizeof(vector4<int>::base_type),
	"r4::vector must not define any member variables"
);

} // namespace r4

#include "quaternion.hpp"

namespace r4 {

template <class component_type, size_t dimension>
template <typename enable_type>
vector<component_type, dimension>& vector<component_type, dimension>::rotate(
	const quaternion<std::enable_if_t<dimension == 3 || dimension == 4, enable_type>>& q
) noexcept
{
	*this = q.rot(*this);
	return *this;
}

} // namespace r4
