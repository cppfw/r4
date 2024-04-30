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

#include "quaternion.hpp"
#include "vector.hpp"

// undefine possibly defined macros
#ifdef minor
#	undef minor
#endif
#ifdef near
#	undef near
#endif
#ifdef far
#	undef far
#endif

namespace r4 {

template <class component_type, size_t num_rows, size_t num_columns>
class matrix :
	// it's ok to inherit std::array<component_type> because r4::matrix only defines methods
	// and doesn't define any new member variables (checked by static_assert after the
	// class declaration), so it is ok that std::array has non-virtual destructor
	public std::array<vector<component_type, num_columns>, num_rows>
{
	static_assert(num_rows >= 1, "matrix cannot have 0 rows");

public:
	using base_type = std::array<vector<component_type, num_columns>, num_rows>;

	/**
	 * @brief Default constructor.
	 * NOTE: it does not initialize the matrix with any values.
	 * Matrix elements are undefined after the matrix is created with this constructor.
	 */
	// NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
	constexpr matrix() = default;

	/**
	 * @brief Constructor.
	 * Initializes matrix rows to given values.
	 * @param rows - parameter pack with initializing rows.
	 */
	template <typename... argument_type, std::enable_if_t<sizeof...(argument_type) == num_rows, bool> = true>
	constexpr explicit matrix(const vector<argument_type, num_columns>&... rows) noexcept :
		base_type{rows...}
	{
		static_assert(
			sizeof...(rows) == num_rows,
			"number of constructor arguments is not equal to number of rows in this matrix"
		);
	}

private:
	template <size_t... indices>
	constexpr matrix(std::initializer_list<vector<component_type, num_columns>> rows, std::index_sequence<indices...>) noexcept
		:
		base_type{*std::next(rows.begin(), indices)...}
	{}

public:
	/**
	 * @brief Construct initialized matrix.
	 * Creates a matrix and initializes its rows by the given values.
	 * @param rows - initializer list of vectors to set as rows of the matrix.
	 */
	constexpr matrix(std::initializer_list<vector<component_type, num_columns>> rows) noexcept :
		matrix(
			[&rows]() {
				if (rows.size() == num_rows)
					return rows;
				std::cerr << "wrong number of elements in initializer list of matrix(std::initializer_list), expected "
						  << num_rows << ", got " << rows.size() << std::endl;
				std::abort();
			}(),
			std::make_index_sequence<num_rows>()
		)
	{}

	/**
	 * @brief Construct rotation matrix.
	 * Defined only for 3x3 and 4x4 matrices.
	 * Constructs matrix and initializes it to a rotation matrix from given unit quaternion.
	 * @param quat - unit quaternion defining the rotation.
	 */
	template <typename enable_type = component_type>
	constexpr matrix(
		const quaternion<std::enable_if_t<num_rows == num_columns && (num_rows == 3 || num_rows == 4), enable_type>>&
			quat
	) noexcept
	{
		this->set(quat);
	}

	/**
	 * @brief Unary component-wise operation.
	 * Perform unary operation on each component of the vector.
	 * @param op - unary operation to perform on each component of the vector.
	 * @return Resulting vector.
	 */
	template <typename unary_operation_type>
	matrix comp_op(unary_operation_type op) const
	{
		matrix res{};
		std::transform(this->begin(), this->end(), res.begin(), op);
		return res;
	}

	/**
	 * @brief Binary component-wise operation.
	 * Perform binary operation on each component of two vectors.
	 * @param mat - second matrix.
	 * @param op - binary operation to perform on each component of two vectors.
	 * @return Resulting vector.
	 */
	template <typename binary_operation_type>
	matrix comp_op(const matrix& mat, binary_operation_type op) const
	{
		matrix res{};
		std::transform(this->begin(), this->end(), mat.begin(), res.begin(), op);
		return res;
	}

	/**
	 * @brief Convert to different element type.
	 * @return matrix with converted element type.
	 */
	template <typename another_component_type>
	matrix<another_component_type, num_rows, num_columns> to() noexcept
	{
		matrix<another_component_type, num_rows, num_columns> ret;
		std::transform( //
			this->begin(),
			this->end(),
			ret.begin(),
			[](const auto& r) {
				return r.template to<another_component_type>();
			}
		);
		return ret;
	}

	/**
	 * @brief Set this matrix to be a rotation matrix.
	 * Defined only for 3x3 and 4x4 matrices.
	 * Sets this matrix to a matrix representing a rotation defined by a unit quaternion.
	 * @param quat - unit quaternion defining the rotation.
	 * @return Reference to this matrix object.
	 */
	template <typename enable_type = component_type>
	matrix& set(
		const quaternion<std::enable_if_t<num_rows == num_columns && (num_rows == 3 || num_rows == 4), enable_type>>&
			quat
	) noexcept
	{
		// Quaternion to matrix conversion:
		//     |  1-(2y^2+2z^2)   2xy-2zw         2xz+2yw         0   |
		// M = |  2xy+2zw         1-(2x^2+2z^2)   2yz-2xw         0   |
		//     |  2xz-2yw         2zy+2xw         1-(2x^2+2y^2)   0   |
		//     |  0               0               0               1   |

		// First column
		this->row(0)[0] = component_type(1) - component_type(2) * (utki::pow2(quat.y()) + utki::pow2(quat.z()));
		this->row(1)[0] = component_type(2) * (quat.x() * quat.y() + quat.z() * quat.w());
		this->row(2)[0] = component_type(2) * (quat.x() * quat.z() - quat.y() * quat.w());
		if constexpr (num_rows == 4) {
			this->row(3)[0] = component_type(0);
		}

		// Second column
		this->row(0)[1] = component_type(2) * (quat.x() * quat.y() - quat.z() * quat.w());
		this->row(1)[1] = component_type(1) - component_type(2) * (utki::pow2(quat.x()) + utki::pow2(quat.z()));
		this->row(2)[1] = component_type(2) * (quat.z() * quat.y() + quat.x() * quat.w());
		if constexpr (num_rows == 4) {
			this->row(3)[1] = component_type(0);
		}

		// Third column
		this->row(0)[2] = component_type(2) * (quat.x() * quat.z() + quat.y() * quat.w());
		this->row(1)[2] = component_type(2) * (quat.y() * quat.z() - quat.x() * quat.w());
		this->row(2)[2] = component_type(1) - component_type(2) * (utki::pow2(quat.x()) + utki::pow2(quat.y()));
		if constexpr (num_rows == 4) {
			this->row(3)[2] = component_type(0);
		}

		// Fourth column
		if constexpr (num_rows == 4) {
			this->row(0)[3] = component_type(0);
			this->row(1)[3] = component_type(0);
			this->row(2)[3] = component_type(0);
			this->row(3)[3] = component_type(1);
		}

		return *this;
	}

	/**
	 * @brief Get matrix row.
	 * @param r - row number to get.
	 * @return reference to vector representing the row of this matrix.
	 */
	vector<component_type, num_columns>& row(size_t r) noexcept
	{
		ASSERT(r < this->size())
		return this->operator[](r);
	}

	/**
	 * @brief Get matrix row.
	 * @param r - row number to get.
	 * @return reference to vector representing the row of this matrix.
	 */
	const vector<component_type, num_columns>& row(size_t r) const noexcept
	{
		ASSERT(r < this->size())
		return this->operator[](r);
	}

	/**
	 * @brief Subtract matrix from this matrix.
	 * @param m - matrix to subtract from this matrix.
	 * @return resulting matrix of the subtraction.
	 */
	matrix operator-(const matrix& m) const noexcept
	{
		return this->comp_op( //
			m,
			[](const auto& r1, const auto& r2) {
				return r1 - r2;
			}
		);
	}

	/**
	 * @brief Transform vector by matrix.
	 * Multiply vector V by this matrix M from the right (M * V).
	 * i.e. transform vector with this transformation matrix.
	 * @param vec - vector to transform. Must have same number of components, as number of columns in this matrix.
	 * @return Transformed vector.
	 */
	vector<component_type, num_rows> operator*(const vector<component_type, num_columns>& vec) const noexcept
	{
		vector<component_type, num_rows> res;
		std::transform( //
			this->begin(),
			this->end(),
			res.begin(),
			[&vec](const auto& r) {
				return r * vec;
			}
		);
		return res;
	}

	// TODO: add doxygen comment
	// Transform 2d or 3d vector by matrix.
	// Defined only for 4x4 matrix.
	template <size_t dimension, typename enable_type = component_type>
	vector<std::enable_if_t<num_rows == 4 && num_columns == 4 && (dimension == 2 || dimension == 3), enable_type>, 4>
	operator*(const vector<component_type, dimension>& vec) const noexcept
	{
		static_assert(num_rows == 4 && num_columns == 4, "4x4 matrix expected");
		return vector<component_type, 4>{
			this->row(0) * vec + this->row(0)[3],
			this->row(1) * vec + this->row(1)[3],
			this->row(2) * vec + this->row(2)[3],
			this->row(3) * vec + this->row(3)[3],
		};
	}

	// TODO: add doxygen comment
	template <size_t dimension, typename enable_type = component_type>
	vector<std::enable_if_t<(num_rows == 2 && num_columns == 3 && dimension == 2), enable_type>, 2> operator*(
		const vector<component_type, dimension>& vec
	) const noexcept
	{
		static_assert(num_rows == 2 && num_columns == 3, "2x3 matrix expected");
		static_assert(dimension == 2, "2d vector expected");
		return vector<component_type, 2>{
			this->row(0) * vec + this->row(0)[2], //
			this->row(1) * vec + this->row(1)[2]
		};
	}

	/**
	 * @brief Multiply by matrix from the right.
	 * Calculate result of this matrix M multiplied by another matrix K from the right (M * K).
	 * Matrices M and K must be matched. Let's say this matrix has num_rows rows and num_columns columns.
	 * Then the matrix K must have num_columns rows and, let's say, another_num_column columns.
	 * And the result matrix of the multiplication will be with num_rows rows and another_num_column columns.
	 * The matrix multiplication operator is also defined for 2x3 matrices. In this case, before the operation,
	 * both matrices are implicitly converted to 3x3 matrices with last added row to be (0, 0, 1), so that the matrices
	 * are square and, thus, are matched.
	 * @param m - matrix to multiply by (matrix K).
	 * @return New matrix of size RxCC as a result of matrices product.
	 */
	template <size_t another_num_column>
	matrix<component_type, num_rows, another_num_column> operator*(
		const matrix<component_type, num_columns, another_num_column>& m
	) const noexcept
	{
		matrix<component_type, num_rows, another_num_column> ret;
		for (size_t rd = 0; rd != ret.size(); ++rd) {
			// NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
			auto& row_dst = ret[rd];
			const auto& row_src = this->row(rd);

			for (size_t cd = 0; cd != row_dst.size(); ++cd) {
				component_type v = 0;
				for (size_t i = 0; i != num_columns; ++i) {
					// NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
					v += row_src[i] * m[i][cd];
				}
				// NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
				row_dst[cd] = v;
			}
		}
		return ret;
	}

	// Define operator*(matrix) for 2x3 matrices. See description of operator*(matrix) for square matrices for info.
	template <typename enable_type = matrix>
	std::enable_if_t<num_rows == 2 && num_columns == 3, enable_type> operator*(const matrix& matr) const noexcept
	{
		return matrix{
			vector<component_type, 3>{
									  this->row(0)[0] * matr[0][0] + this->row(0)[1] * matr[1][0],
									  this->row(0)[0] * matr[0][1] + this->row(0)[1] * matr[1][1],
									  this->row(0)[0] * matr[0][2] + this->row(0)[1] * matr[1][2] + this->row(0)[2]},
			vector<component_type, 3>{
									  this->row(1)[0] * matr[0][0] + this->row(1)[1] * matr[1][0],
									  this->row(1)[0] * matr[0][1] + this->row(1)[1] * matr[1][1],
									  this->row(1)[0] * matr[0][2] + this->row(1)[1] * matr[1][2] + this->row(1)[2]},
		};
	}

	/**
	 * @brief Multiply by matrix from the right.
	 * Defined only for square matrices and for 2x3 matrices. Im case of 2x3 matrices, those are
	 * implicitly converted to square matrix before the opration by adding (0, 0, 1) row as a third row, and
	 * after assignment, the third row is discarded again.
	 * Multiply this matrix M by another matrix K from the right (M  = M * K).
	 * @return reference to this matrix object.
	 */
	template <typename enable_type = matrix>
	std::enable_if_t<num_rows == num_columns || (num_rows == 2 && num_columns == 3), enable_type&> operator*=(
		const matrix& matr
	) noexcept
	{
		return this->operator=(this->operator*(matr));
	}

	/**
	 * @brief Multiply matrix by scalar.
	 * @param n - scalar to multiply the matrix by.
	 * @return reference to this matrix.
	 */
	matrix& operator*=(component_type n)
	{
		for (auto& r : *this) {
			r *= n;
		}
		return *this;
	}

	/**
	 * @brief Divide matrix by scalar.
	 * @param n - scalar to divide the matrix by.
	 * @return reference to this matrix.
	 */
	matrix& operator/=(component_type n)
	{
		for (auto& r : *this) {
			r /= n;
		}
		return *this;
	}

	/**
	 * @brief Divide matrix by scalar.
	 * @param num - scalar to divide the matrix by.
	 * @return divided matrix.
	 */
	matrix operator/(component_type num) const noexcept
	{
		return this->comp_op([&num](const auto& r) {
			return r / num;
		});
	}

	/**
	 * @brief Multiply by matrix from the left.
	 * Multiply this matrix M by another matrix K from the left (M  = K * M).
	 * Defined only for square matrices and 2x3 matrices. For details about 2x3 matrices see
	 * description of operator*(matrix).
	 * @param matr - matrix to multiply by.
	 * @return reference to this matrix object.
	 */
	template <typename enable_type = matrix>
	std::enable_if_t<num_rows == num_columns || (num_rows == 2 && num_columns == 3), enable_type&> left_mul(
		const matrix& matr
	) noexcept
	{
		return this->operator=(matr.operator*(*this));
	}

	/**
	 * @brief Initialize this matrix with identity matrix.
	 * Defined only for square matrices and 2x3 matrix.
	 */
	std::enable_if_t<num_rows == num_columns || (num_rows == 2 && num_columns == 3), matrix>& set_identity() noexcept
	{
		size_t row_index = 0;
		for (auto& r : *this) {
			auto one_iter = utki::next(r.begin(), row_index);

			std::fill(r.begin(), one_iter, component_type(0));

			*one_iter = component_type(1);

			std::fill(std::next(one_iter), r.end(), component_type(0));

			++row_index;
		}
		return *this;
	}

	/**
	 * @brief Set current matrix to frustum matrix.
	 * The frustum matrix is same as defined by OpenGL, see glFrustum() function.
	 * Parameters are identical to glFrustum() function from OpenGL.
	 * Defined only for 4x4 matrices.
	 * @param left - left vertical clipping plane.
	 * @param right - right vertical clipping plane.
	 * @param bottom - bottom horizontal clipping plane.
	 * @param top - top horizontal clipping plane.
	 * @param near_val - distance to near clipping plane. Must be positive.
	 * @param far_val - distance to the far clipping plane. Must be positive.
	 * @return reference to this matrix instance.
	 */
	template <typename enable_type = component_type>
	matrix& set_frustum(
		std::enable_if_t<num_rows == num_columns && num_rows == 4, enable_type> left,
		component_type right,
		component_type bottom,
		component_type top,
		component_type near_val,
		component_type far_val
	) noexcept
	{
		component_type w = right - left;
		ASSERT(w != 0)

		component_type h = top - bottom;
		ASSERT(h != 0)

		component_type d = far_val - near_val;
		ASSERT(d != 0)

		matrix& f = *this;
		f[0][0] = 2 * near_val / w;
		f[0][1] = 0;
		f[0][2] = (right + left) / w;
		f[0][3] = 0;

		f[1][0] = 0;
		f[1][1] = 2 * near_val / h;
		f[1][2] = (top + bottom) / h;
		f[1][3] = 0;

		f[2][0] = 0;
		f[2][1] = 0;
		f[2][2] = -(far_val + near_val) / d;
		f[2][3] = -2 * far_val * near_val / d;

		f[3][0] = 0;
		f[3][1] = 0;
		f[3][2] = -1;
		f[3][3] = 0;

		return *this;
	}

	/**
	 * @brief Multiply current matrix by frustum matrix.
	 * Multiplies this matrix M by frustum matrix F from the right (M = M * F).
	 * The frustum matrix is same as defined by OpenGL, see glFrustum() function.
	 * Parameters are identical to glFrustum() function from OpenGL.
	 * Defined only for 4x4 matrices.
	 * @param left - left vertical clipping plane.
	 * @param right - right vertical clipping plane.
	 * @param bottom - bottom horizontal clipping plane.
	 * @param top - top horizontal clipping plane.
	 * @param near - distance to near clipping plane. Must be positive.
	 * @param far - distance to the far clipping plane. Must be positive.
	 * @return reference to this matrix instance.
	 */
	template <typename enable_type = component_type>
	matrix& frustum(
		std::enable_if_t<num_rows == num_columns && num_rows == 4, enable_type> left,
		component_type right,
		component_type bottom,
		component_type top,
		component_type near,
		component_type far
	) noexcept
	{
		matrix f;
		f.set_frustum(left, right, bottom, top, near, far);
		return this->operator*=(f);
	}

	/**
	 * @brief Set current matrix to perspective projection matrix.
	 * The perspective projection matrix is same as defined by
	 * OpenGL Utility library (GLU), see gluPerspective() function.
	 * Parameters are identical to gluPerspective() function from GLU,
	 * except 'fov_y' is in radians.
	 * Defined only for 4x4 matrices.
	 * @param fov_y - y-axis field of view angle, in radians.
	 * @param aspect - the field of view aspect ratio, x / y.
	 * @param near - near clipping plane, must be positive.
	 * @param far - far clipping plane, must be positive.
	 * @return reference to this matrix instance.
	 */
	template <typename enable_type = component_type>
	matrix& set_perspective(
		std::enable_if_t<num_rows == num_columns && num_rows == 4, enable_type> fov_y,
		component_type aspect,
		component_type near,
		component_type far
	) noexcept
	{
		ASSERT(aspect > 0)
		ASSERT(near > 0)
		ASSERT(far > near)

		using std::tan;
		component_type tan_half_fov_y = tan(fov_y / component_type(2));
		component_type minus_d = near - far;

		this->set(0);

		this->row(0)[0] = component_type(1) / (aspect * tan_half_fov_y);
		this->row(1)[1] = component_type(1) / tan_half_fov_y;
		this->row(2)[2] = (far + near) / minus_d;
		this->row(2)[3] = component_type(2) * far * near / minus_d;
		this->row(3)[2] = -component_type(1);

		return *this;
	}

	/**
	 * @brief Multiply current matrix by perspective projection matrix.
	 * Multiplies this matrix M by perspective projection matrix P from the right (M = M * P).
	 * The perspective projection matrix is same as defined by
	 * OpenGL Utility library (GLU), see gluPerspective() function.
	 * Parameters are identical to gluPerspective() function from GLU,
	 * except 'fov_y' is in radians.
	 * Defined only for 4x4 matrices.
	 * @param fov_y - y-axis field of view angle, in radians.
	 * @param aspect - the field of view aspect ratio, x / y.
	 * @param near - near clipping plane, must be positive.
	 * @param far - far clipping plane, must be positive.
	 * @return reference to this matrix instance.
	 */
	template <typename enable_type = component_type>
	matrix& perspective(
		std::enable_if_t<num_rows == num_columns && num_rows == 4, enable_type> fov_y,
		component_type aspect,
		component_type near,
		component_type far
	) noexcept
	{
		matrix p;
		p.set_perspective(fov_y, aspect, near, far);
		return this->operator*=(p);
	}

	/**
	 * @brief Multiply current matrix by perspective projection matrix.
	 * Multiplies this matrix by perspective projection matrix P from the right (M = M * P).
	 * This operation is defined only for 4x4 matrices.
	 * Perspective projection matrix is:
	 *
	 *      | 1 0 0 0 |
	 *  P = | 0 1 0 0 |
	 *      | 0 0 1 0 |
	 *      | 0 0 p 1 |
	 *
	 * The meaning of this matrix is as follows:
	 * - the projection center point, i.e. the eye, is at (0, 0, -1 / p) point.
	 * - the projection surface is the x-y plane
	 *
	 * @param p - element [3][2] of matrix P.
	 * @return Reference to this matrix.
	 */
	template <typename enable_type = component_type>
	matrix& perspective(
		std::enable_if_t<num_rows == num_columns && num_rows == 4, enable_type> p = component_type(1)
	) noexcept
	{
		this->row(0)[2] += this->row(0)[3] * p;
		this->row(1)[2] += this->row(1)[3] * p;
		this->row(2)[2] += this->row(2)[3] * p;
		this->row(3)[2] += this->row(3)[3] * p;
		return *this;
	}

	/**
	 * @brief Set current matrix to look-at matrix.
	 * The look-at matrix is same as defined by
	 * OpenGL Utility library (GLU), see gluLookAt() function.
	 * Defined only for 4x4 matrices.
	 * @param eye - position of the eye point.
	 * @param center - position of the look-at point.
	 * @param up - direction of the up vector.
	 * @return reference to this matrix instance.
	 */
	template <typename enable_type = component_type>
	matrix& set_look_at(
		std::enable_if_t<num_rows == num_columns && num_rows == 4, vector3<enable_type>> eye,
		vector3<component_type> center,
		vector3<component_type> up
	) noexcept
	{
		auto f = (center - eye).normalize();
		auto s = f.cross(up).normalize();
		auto u = s.cross(f);

		this->set(0);

		this->row(0)[0] = s[0];
		this->row(0)[1] = s[1];
		this->row(0)[2] = s[2];
		this->row(0)[3] = -s * eye;
		this->row(1)[0] = u[0];
		this->row(1)[1] = u[1];
		this->row(1)[2] = u[2];
		this->row(1)[3] = -u * eye;
		this->row(2)[0] = -f[0];
		this->row(2)[1] = -f[1];
		this->row(2)[2] = -f[2];
		this->row(2)[3] = f * eye;
		this->row(3)[3] = 1;

		return *this;
	}

	/**
	 * @brief Multiply current matrix by look-at matrix.
	 * Multiplies this matrix M by look-at matrix L from the right (M = M * L).
	 * The look-at matrix is same as defined by
	 * OpenGL Utility library (GLU), see gluLookAt() function.
	 * Defined only for 4x4 matrices.
	 * @param eye - position of the eye point.
	 * @param center - position of the look-at point.
	 * @param up - direction of the up vector.
	 * @return reference to this matrix instance.
	 */
	template <typename enable_type = component_type>
	matrix& look_at(
		std::enable_if_t<num_rows == num_columns && num_rows == 4, vector3<enable_type>> eye,
		vector3<component_type> center,
		vector3<component_type> up
	) noexcept
	{
		matrix l;
		l.set_look_at(eye, center, up);
		return this->operator*=(l);
	}

	/**
	 * @brief Multiply current matrix by scale matrix.
	 * Multiplies this matrix M by scale matrix S from the right (M = M * S).
	 * Defined only for 1x1, 2x2, 2x3, 3x3, 4x4 matrices.
	 * @param s - scaling factor to be applied in all directions (x, y and z).
	 * @return reference to this matrix instance.
	 */
	template <typename enable_type = matrix>
	std::enable_if_t<
		(num_rows == num_columns && (1 <= num_rows && num_rows <= 4)) || (num_rows == 2 && num_columns == 3),
		matrix&>
	scale(component_type s) noexcept
	{
		using std::min;
		size_t num_cols = min(min(num_columns, num_rows), size_t(3)); // for 2x3 and 4x4 matrix do not scale last column
		for (auto& r : *this) {
			for (auto& e : utki::make_span(r.data(), num_cols)) {
				e *= s;
			}
		}
		return *this;
	}

	/**
	 * @brief Multiply current matrix by scale matrix.
	 * Multiplies this matrix M by scale matrix S from the right (M = M * S).
	 * @param x - scaling factor in x direction.
	 * @param y - scaling factor in y direction.
	 * @return reference to this matrix instance.
	 */
	matrix& scale(component_type x, component_type y) noexcept
	{
		for (size_t r = 0; r != num_rows; ++r) {
			this->row(r)[0] *= x;
		}
		if constexpr (num_columns >= 2) {
			for (size_t r = 0; r != num_rows; ++r) {
				this->row(r)[1] *= y;
			}
		}
		return *this;
	}

	/**
	 * @brief Multiply current matrix by scale matrix.
	 * Multiplies this matrix M by scale matrix S from the right (M = M * S).
	 * @param x - scaling factor in x direction.
	 * @param y - scaling factor in y direction.
	 * @param z - scaling factor in z direction.
	 * @return reference to this matrix instance.
	 */
	matrix& scale(component_type x, component_type y, component_type z) noexcept
	{
		// update 0th and 1st columns
		this->scale(x, y);

		// update 2nd column
		if constexpr (num_columns >= 3) {
			for (size_t r = 0; r != num_rows; ++r) {
				this->row(r)[2] *= z;
			}
		}
		return *this;
	}

	/**
	 * @brief Multiply current matrix by scale matrix.
	 * Multiplies this matrix M by scale matrix S from the right (M = M * S).
	 * @param s - vector of scaling factors.
	 * @return reference to this matrix instance.
	 */
	template <size_t dimension>
	matrix& scale(const vector<component_type, dimension>& s) noexcept
	{
		using std::min;
		constexpr auto num_cols = min(dimension, num_columns);

		for (auto& r : *this) {
			auto s_iter = s.begin();
			for (auto& e : utki::make_span(r.data(), num_cols)) {
				e *= *s_iter;
				++s_iter;
			}
		}

		return *this;
	}

	/**
	 * @brief Multiply this matrix by translation matrix.
	 * Multiplies this matrix M by translation matrix T from the right (M = M * T).
	 * Translation only occurs in x-y plane, no translation in other directions.
	 * Defined only for 2x3, 3x3 and 4x4 matrices.
	 * @param x - x component of translation vector.
	 * @param y - y component of translation vector.
	 * @return reference to this matrix object.
	 */
	template <typename enable_type = component_type>
	matrix& translate(
		std::enable_if_t<
			(num_rows == 2 && num_columns == 3) || (num_rows == num_columns && (num_rows == 3 || num_rows == 4)),
			enable_type> x,
		component_type y
	) noexcept
	{
		// only last column of the matrix changes
		for (size_t r = 0; r != num_rows; ++r) {
			this->row(r)[num_columns - 1] += this->row(r)[0] * x + this->row(r)[1] * y;
		}
		return *this;
	}

	/**
	 * @brief Multiply this matrix by translation matrix.
	 * Multiplies this matrix M by translation matrix T from the right (M = M * T).
	 * Defined only for 4x4 matrix.
	 * @param x - x component of translation vector.
	 * @param y - y component of translation vector.
	 * @param z - z component of translation vector.
	 * @return reference to this matrix object.
	 */
	template <typename enable_type = component_type>
	matrix& translate(
		std::enable_if_t<num_rows == num_columns && num_rows == 4, enable_type> x,
		component_type y,
		component_type z
	) noexcept
	{
		// only last column of the matrix changes
		for (size_t r = 0; r != num_rows; ++r) {
			this->row(r)[num_columns - 1] += this->row(r)[0] * x + this->row(r)[1] * y + this->row(r)[2] * z;
		}
		return *this;
	}

	/**
	 * @brief Multiply this matrix by translation matrix.
	 * Multiplies this matrix M by translation matrix T from the right (M = M * T).
	 * Defined only for 2x3, 3x3 and 4x4 matrices.
	 * @param t - translation vector, can have 2 or 3 components.
	 * @return reference to this matrix object.
	 */
	template <typename enable_type = component_type, size_t dimension>
	matrix& translate(const vector<
					  std::enable_if_t<
						  ((num_rows == 2 && num_columns == 3) ||
						   (num_rows == num_columns && (num_rows == 3 || num_rows == 4))) &&
							  (dimension == 2 || dimension == 3) && (dimension < num_columns),
						  enable_type>,
					  dimension>& t) noexcept
	{
		// only last column of the matrix changes
		for (auto& r : *this) {
			auto& res = r.back();

			auto r_iter = r.begin();
			for (const auto& e : t) {
				res += *r_iter * e;
				++r_iter;
			}
		}

		return *this;
	}

	/**
	 * @brief Multiply this matrix by rotation matrix.
	 * Multiplies this matrix M by rotation matrix num_rows from the right (M = M * num_rows).
	 * Defined only for 3x3 and 4x4 matrices.
	 * @param q - unit quaternion, representing the rotation.
	 * @return reference to this matrix object.
	 */
	template <typename enable_type = component_type>
	matrix& rotate(
		const quaternion<std::enable_if_t<num_rows == num_columns && (num_rows == 3 || num_rows == 4), enable_type>>& q
	) noexcept
	{
		return this->operator*=(matrix<component_type, num_rows, num_columns>(q));
	}

	/**
	 * @brief Multiply this matrix by rotation matrix.
	 * Multiplies this matrix M by rotation matrix num_rows from the right (M = M * num_rows).
	 * Rotation is done around (0, 0, 1) axis by given number of radians.
	 * Positive direction of rotation is determined by a right-hand rule, i.e. from X-axis to Y-axis.
	 * Defined only for 2x3, 3x3 and 4x4 matrices.
	 * @param a - the angle of rotation in radians.
	 * @return reference to this matrix object.
	 */
	template <typename enable_type = component_type>
	matrix& rotate(std::enable_if_t<
				   (num_rows == 2 && num_columns == 3) || (num_rows == num_columns && (num_rows == 3 || num_rows == 4)),
				   enable_type> a) noexcept
	{
		if constexpr (num_rows == num_columns) {
			// square matrix
			return this->rotate(vector<component_type, 3>(0, 0, a));
		} else {
			static_assert(num_rows == 2 && num_columns == 3, "2x3 matrix expected");

			// multiply this matrix from the right by the rotation matrix:
			//               | cos(a) -sin(a) 0 |
			// this = this * | sin(a)  cos(a) 0 |

			using std::cos;
			using std::sin;
			component_type sina = sin(a);
			component_type cosa = cos(a);

			component_type m00 = this->row(0)[0] * cosa + this->row(0)[1] * sina;
			component_type m10 = this->row(1)[0] * cosa + this->row(1)[1] * sina;
			sina = -sina;
			component_type m01 = this->row(0)[0] * sina + this->row(0)[1] * cosa;
			component_type m11 = this->row(1)[0] * sina + this->row(1)[1] * cosa;

			this->row(0)[0] = m00;
			this->row(1)[0] = m10;

			this->row(0)[1] = m01;
			this->row(1)[1] = m11;

			return *this;
		}
	}

	/**
	 * @brief Transpose this matrix.
	 */
	matrix& transpose() noexcept
	{
		using std::swap;
		using std::min;

		auto square_index = min(num_rows, num_columns);
		for (size_t r = 1; r != square_index; ++r) {
			for (size_t c = 0; c != r; ++c) {
				// NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
				swap(this->row(r)[c], this->row(c)[r]);
			}
		}
		// in case the matrix is not square, then zero out the "non-square" parts
		if constexpr (num_columns > num_rows) {
			for (size_t r = 0; r != num_rows; ++r) {
				auto& cur_row = this->row(r);
				for (size_t c = num_rows; c != num_columns; ++c) {
					// NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
					cur_row[c] = component_type(0);
				}
			}
		} else {
			static_assert(num_rows >= num_columns, "expected matrix with num_rows >= num_columns");
			for (size_t r = num_columns; r != num_rows; ++r) {
				this->row(r).set(component_type(0));
			}
		}

		return *this;
	}

	/**
	 * @brief Make transposed matrix.
	 * @return a new matrix which is a transpose of this matrix.
	 */
	matrix tposed() const noexcept
	{
		matrix ret;

		using std::min;

		auto square_index = min(num_columns, num_rows);

		for (size_t r = 1; r != square_index; ++r) {
			// NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
			auto& ret_row = ret[r];
			const auto& src_row = this->row(r);
			for (size_t c = 0; c != r; ++c) {
				// NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
				ret_row[c] = this->row(c)[r];
				// NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
				ret[c][r] = src_row[c];
			}
		}

		// copy diagonal elements
		for (size_t i = 0; i != square_index; ++i) {
			// NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
			ret[i][i] = this->row(i)[i];
		}

		// in case the matrix is not square, then zero out the "non-square" parts
		if constexpr (num_columns > num_rows) {
			for (auto& r : ret) {
				for (auto& c : utki::make_span(r).subspan(num_rows)) {
					c = component_type(0);
				}
			}
		} else {
			static_assert(num_rows >= num_columns, "expected matrix with num_rows >= num_columns");
			for (size_t r = num_columns; r != num_rows; ++r) {
				// NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
				ret[r].set(component_type(0));
			}
		}

		return ret;
	}

	/**
	 * @brief Get sub-matrix matrix by removing given row and column.
	 * Retruns a sub-matrix matrix which is constructed from this matrix by removing given row and given column.
	 * @param row - index of the row to remove.
	 * @param col - index of the column to remove.
	 * @return minor matrix.
	 */
	template <typename enable_type = component_type>
	matrix<std::enable_if_t<(num_rows >= 2 && num_columns >= 2), enable_type>, num_rows - 1, num_columns - 1> remove(
		size_t row,
		size_t col
	) const noexcept
	{
		matrix<component_type, num_rows - 1, num_columns - 1> ret;

		ASSERT(row < num_rows)
		ASSERT(col < num_columns)

		for (size_t dr = 0; dr != row; ++dr) {
			for (size_t dc = 0; dc != col; ++dc) {
				// NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
				ret[dr][dc] = this->row(dr)[dc];
			}
			// NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
			for (size_t dc = col; dc != ret[dr].size(); ++dc) {
				// NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
				ret[dr][dc] = this->row(dr)[dc + 1];
			}
		}

		for (size_t dr = row; dr != ret.size(); ++dr) {
			for (size_t dc = 0; dc != col; ++dc) {
				// NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
				ret[dr][dc] = this->row(dr + 1)[dc];
			}
			// NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
			for (size_t dc = col; dc != ret[dr].size(); ++dc) {
				// NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
				ret[dr][dc] = this->row(dr + 1)[dc + 1];
			}
		}

		return ret;
	}

	/**
	 * @brief Claculate minor.
	 * Calculate determinant of submatrix with removed given row and column.
	 * This is equivalent to remove(r, c).det().
	 * Defined only for square matrices 2x2 or bigger.
	 * @param row - index of the row to remove.
	 * @param col - index of the column to remove.
	 */
	template <typename enable_type = component_type>
	std::enable_if_t<num_rows == num_columns && (num_rows >= 2), enable_type> minor(size_t row, size_t col)
		const noexcept
	{
		return this->remove(row, col).det();
	}

	/**
	 * @brief Calculate matrix determinant.
	 * Defined only for square matrices and 2x3 matrix.
	 * For 2x3 matrix the determinant is calculated as if it was a 2x2 matrix without the 3rd column.
	 * @return matrix determinant.
	 */
	template <typename enable_type = component_type>
	std::enable_if_t<num_rows == num_columns || (num_rows == 2 && num_columns == 3), enable_type> det() const noexcept
	{
		if constexpr (num_rows == num_columns) {
			if constexpr (num_rows == 1) {
				return this->row(0)[0];
			} else {
				component_type ret = 0;
				component_type sign = 1;
				for (size_t i = 0; i != num_columns; ++i, sign = -sign) {
					// NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
					ret += sign * this->row(0)[i] * this->minor(0, i);
				}
				return ret;
			}
		} else {
			static_assert(num_rows == 2 && (num_columns == 2 || num_columns == 3), "expected 2x2 or 2x3 matrix");
			// for 2x3 matrix:

			//    |a b c|          |e f|          |d f|          |d e|
			// det|d e f| = a * det|0 1| - b * det|0 1| + c * det|0 0| = ae - bd
			//    |0 0 1|

			// for 2x2 matrix:

			//    |a b|
			// det|d e| = ae - bd

			// i.e. same formulae

			return this->row(0)[0] * this->row(1)[1] - this->row(0)[1] * this->row(1)[0];
		}
	}

	/**
	 * @brief Calculate inverse of the matrix.
	 * The resulting inverse matrix M^-1 is to multiply this matrix to get identity matrix.
	 *     M * M^-1 = I
	 *     M^-1 * M = I
	 * Defined only for square matrices and 2x3 matrix. The 2x3 matrix, before the inversion, is converted to
	 * 3x3 matrix by adding (0, 0, 1) as a last row, then inverted as square matrix, then the last row of the
	 * inversion resulting matrix is discarded.
	 * @return right inverse matrix of this matrix.
	 */
	template <typename enable_type = component_type>
	matrix<
		std::enable_if_t<num_rows == num_columns || (num_rows == 2 && num_columns == 3), enable_type>,
		num_rows,
		num_columns>
	inv() const noexcept
	{
		if constexpr (num_rows == num_columns) {
			if constexpr (num_rows == 1) {
				return component_type(1) / this->row(0)[0];
			} else {
				component_type d = this->det();

				// calculate matrix of minors
				static_assert(num_rows == num_columns, "expected square matrix");
				matrix<component_type, num_rows, num_columns> mm;

				for (size_t r = 0; r != num_rows; ++r) {
					component_type sign = r % 2 == 0 ? component_type(1) : component_type(-1);
					for (size_t c = 0; c != num_columns; ++c) {
						// NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
						mm[r][c] = sign * this->minor(r, c);
						sign = -sign;
					}
				}

				mm.transpose();
				mm /= d;
				return mm;
			}
		} else {
			static_assert(num_rows == 2 && num_columns == 3, "expected 2x3 matrix");

			matrix<component_type, 3, 3> m{
				this->row(0),
				this->row(1),
				{0, 0, 1}
			};

			m.invert();

			return {m[0], m[1]};
		}
	}

	/**
	 * @brief Invert this matrix.
	 * @return reference to this matrix.
	 */
	matrix& invert() noexcept
	{
		this->operator=(this->inv());
		return *this;
	}

	/**
	 * @brief Snap each matrix component to 0.
	 * For each component, set it to 0 if its absolute value does not exceed the given threshold.
	 * @param threshold - the snapping threshold.
	 * @return reference to this matrix.
	 */
	matrix& snap_to_zero(component_type threshold) noexcept
	{
		for (auto& r : *this) {
			r.snap_to_zero(threshold);
		}
		return *this;
	}

	/**
	 * @brief Set each element of this matrix to a given number.
	 * @param num - number to set each matrix element to.
	 */
	matrix& set(component_type num) noexcept
	{
		for (auto& e : *this) {
			e.set(num);
		}
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& s, const matrix& mat)
	{
		for (auto& r : mat) {
			s << "|" << r << std::endl;
		}
		return s;
	};
};

template <class component_type>
using matrix2 = matrix<component_type, 2, 3>;
template <class component_type>
using matrix3 = matrix<component_type, 3, 3>;
template <class component_type>
using matrix4 = matrix<component_type, 4, 4>;

static_assert(
	sizeof(matrix4<int>) == sizeof(matrix4<int>::base_type),
	"r4::matrix must not define any member variables"
);

} // namespace r4
