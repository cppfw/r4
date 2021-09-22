/*
The MIT License (MIT)

Copyright (c) 2015-2021 igagis

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

#include "vector.hpp"
#include "quaternion.hpp"

// undefine possibly defined macro
#ifdef minor
#	undef minor
#endif

namespace r4{

template <class T, size_t R, size_t C> class matrix : public std::array<vector<T, C>, R>{
	static_assert(R >= 1, "matrix cannot have 0 rows");
	typedef std::array<vector<T, C>, R> base_type;
public:
	/**
	 * @brief Default constructor.
	 * NOTE: it does not initialize the matrix with any values.
	 * Matrix elements are undefined after the matrix is created with this constructor.
	 */
	constexpr matrix() = default;

	/**
	 * @brief Constructor.
	 * Initializes matrix rows to given values.
	 * @param rows - parameter pack with initializing rows.
	 */
	template <typename... A, std::enable_if_t<sizeof...(A) == R, bool> = true>
	constexpr explicit matrix(A... rows)noexcept :
			base_type{rows...}
	{
		static_assert(sizeof...(rows) == R, "number of constructor arguments is not equal to number of rows in this matrix");
	}

private:
	template <size_t... I>
	constexpr matrix(std::initializer_list<vector<T, C>> rows, std::index_sequence<I...>)noexcept :
			base_type{ *std::next(rows.begin(), I)... }
	{}
public:
	/**
	 * @brief Construct initialized matrix.
	 * Creates a matrix and initializes its rows by the given values.
	 * @param rows - initializer list of vectors to set as rows of the matrix.
	 */
	constexpr matrix(std::initializer_list<vector<T, C>> rows)noexcept :
			matrix(
					[&rows](){
						if(rows.size() == R) return rows;
						std::cerr << "wrong number of elements in initializer list of matrix(std::initializer_list), expected "
								<< R << ", got " << rows.size() << std::endl;
						std::abort();
					}(),
					std::make_index_sequence<R>()
				)
	{}

	/**
	 * @brief Construct rotation matrix.
	 * Defined only for 3x3 and 4x4 matrices.
	 * Constructs matrix and initializes it to a rotation matrix from given unit quaternion.
	 * @param quat - unit quaternion defining the rotation.
	 */
	template <typename E = T>
	constexpr matrix(const quaternion<std::enable_if_t<R == C && (R == 3 || R == 4), E>>& quat)noexcept{
		this->set(quat);
	}

	/**
	 * @brief Convert to different element type.
	 * @return matrix with converted element type.
	 */
	template <typename TT> matrix<TT, R, C> to()noexcept{
		matrix<TT, R, C> ret;
		for(size_t i = 0; i != R; ++i){
			ret[i] = this->row(i).template to<TT>();
		}
		return ret;
	}

	/**
	 * @brief Set this matrix to be a rotation matrix.
	 * Defined only for 3x3 and 4x4 matrices.
	 * Sets this matrix to a matrix representing a rotation defined by a unit quaternion.
	 * @param quat - unit quaternion defining the rotation.
	 * @return Reference to this matrix object.
	 */
	template <typename E = T> matrix& set(const quaternion<std::enable_if_t<R == C && (R == 3 || R == 4), E>>& quat)noexcept{
		// Quaternion to matrix conversion:
		//     |  1-(2y^2+2z^2)   2xy-2zw         2xz+2yw         0   |
		// M = |  2xy+2zw         1-(2x^2+2z^2)   2yz-2xw         0   |
		//     |  2xz-2yw         2zy+2xw         1-(2x^2+2y^2)   0   |
		//     |  0               0               0               1   |

		// First column
		this->row(0)[0] = T(1) - T(2) * (utki::pow2(quat.y()) + utki::pow2(quat.z()));
		this->row(1)[0] = T(2) * (quat.x() * quat.y() + quat.z() * quat.w());
		this->row(2)[0] = T(2) * (quat.x() * quat.z() - quat.y() * quat.w());
		if constexpr (R == 4) this->row(3)[0] = T(0);

		// Second column
		this->row(0)[1] = T(2) * (quat.x() * quat.y() - quat.z() * quat.w());
		this->row(1)[1] = T(1) - T(2) * (utki::pow2(quat.x()) + utki::pow2(quat.z()));
		this->row(2)[1] = T(2) * (quat.z() * quat.y() + quat.x() * quat.w());
		if constexpr (R == 4) this->row(3)[1] = T(0);

		// Third column
		this->row(0)[2] = T(2) * (quat.x() * quat.z() + quat.y() * quat.w());
		this->row(1)[2] = T(2) * (quat.y() * quat.z() - quat.x() * quat.w());
		this->row(2)[2] = T(1) - T(2) * (utki::pow2(quat.x()) + utki::pow2(quat.y()));
		if constexpr (R == 4) this->row(3)[2] = T(0);

		// Fourth column
		if constexpr (R == 4){
			this->row(0)[3] = T(0);
			this->row(1)[3] = T(0);
			this->row(2)[3] = T(0);
			this->row(3)[3] = T(1);
		}

		return *this;
	}

	/**
	 * @brief Get matrix row.
	 * @param r - row number to get.
	 * @return reference to vector representing the row of this matrix.
	 */
	vector<T, C>& row(size_t r)noexcept{
		ASSERT(r < this->size())
		return this->operator[](r);
	}

	/**
	 * @brief Get matrix row.
	 * @param r - row number to get.
	 * @return reference to vector representing the row of this matrix.
	 */
	const vector<T, C>& row(size_t r)const noexcept{
		ASSERT(r < this->size())
		return this->operator[](r);
	}

	/**
	 * @brief Subtract matrix from this matrix.
	 * @param m - matrix to subtract from this matrix.
	 * @return resulting matrix of the subtraction.
	 */
	matrix operator-(const matrix& m)const noexcept{
		matrix res;
		for(size_t r = 0; r != R; ++r){
			res[r] = this->row(r) - m[r];
		}
		return res;
	}

	/**
	 * @brief Transform vector by matrix.
	 * Multiply vector V by this matrix M from the right (M * V).
	 * i.e. transform vector with this transformation matrix.
	 * @param vec - vector to transform. Must have same number of components, as number of columns in this matrix.
	 * @return Transformed vector.
	 */
	vector<T, R> operator*(const vector<T, C>& vec)const noexcept
	{
		vector<T, R> r;
		for(size_t i = 0; i != R; ++i){
			r[i] = this->row(i) * vec;
		}
		return r;
	}

	template <size_t S, typename E = T>
	vector<std::enable_if_t<
			(R == 2 && C == 3 && S == 2),
			E
		>, S> operator*(const vector<T, S>& vec)const noexcept
	{
		static_assert(R == 2 && C == 3, "2x3 matrix expected");
		static_assert(S == 2, "2d vector expected");
		return vector<T, 2>{
				this->row(0) * vec + this->row(0)[2],
				this->row(1) * vec + this->row(1)[2]
			};
	}

	/**
	 * @brief Multiply by matrix from the right.
	 * Calculate result of this matrix M multiplied by another matrix K from the right (M * K).
	 * Matrices M and K must be matched. Let's say this matrix has R rows and C columns.
	 * Then the matrix K must have C rows and, let's say, CC columns.
	 * And the result matrix of the multiplication will be with R rows and CC rows.
	 * The matrix multiplication operator is also defined for 2x3 matrices. In this case, before the operation,
	 * both matrices are implicitly converted to 3x3 matrices with last added row to be (0, 0, 1), so that the matrices are square
	 * and, thus, are matched.
	 * @param m - matrix to multiply by (matrix K).
	 * @return New matrix of size RxCC as a result of matrices product.
	 */
	template <size_t CC>
	matrix<T, R, CC> operator*(const matrix<T, C, CC>& m)const noexcept{
		matrix<T, R, CC> ret;
		for(size_t rd = 0; rd != ret.size(); ++rd){
			auto& row_d = ret[rd];
			for(size_t cd = 0; cd != row_d.size(); ++cd){
				T v = 0;
				for(size_t i = 0; i != C; ++i){
					v += this->row(rd)[i] * m[i][cd];
				}
				ret[rd][cd] = v;
			}
		}
		return ret;
	}

	// Define operaotr*(matrix) for 2x3 matrices. See description of operator*(matrix) for square matrices for info.
	template <typename E = matrix>
	std::enable_if_t<R == 2 && C == 3, E> operator*(const matrix& matr)const noexcept{
		return matrix{
				vector<T, 3>{
						this->row(0)[0] * matr[0][0] + this->row(0)[1] * matr[1][0],
						this->row(0)[0] * matr[0][1] + this->row(0)[1] * matr[1][1],
						this->row(0)[0] * matr[0][2] + this->row(0)[1] * matr[1][2] + this->row(0)[2]
					},
				vector<T, 3>{
						this->row(1)[0] * matr[0][0] + this->row(1)[1] * matr[1][0],
						this->row(1)[0] * matr[0][1] + this->row(1)[1] * matr[1][1],
						this->row(1)[0] * matr[0][2] + this->row(1)[1] * matr[1][2] + this->row(1)[2]
					},
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
	template <typename E = matrix>
	std::enable_if_t<R == C || (R == 2 && C == 3), E&> operator*=(const matrix& matr)noexcept{
		return this->operator=(this->operator*(matr));
	}

	/**
	 * @brief Multiply matrix by scalar.
	 * @param n - scalar to multiply the matrix by.
	 * @return reference to this matrix.
	 */
	matrix& operator*=(T n){
		for(auto& r : *this){
			r *= n;
		}
		return *this;
	}

	/**
	 * @brief Divide matrix by scalar.
	 * @param n - scalar to divide the matrix by.
	 * @return reference to this matrix.
	 */
	matrix& operator/=(T n){
		for(auto& r : *this){
			r /= n;
		}
		return *this;
	}

	/**
	 * @brief Divide matrix by scalar.
	 * @param num - scalar to divide the matrix by.
	 * @return divided matrix.
	 */
	matrix operator/(T num)const noexcept{
		matrix res;
		for(unsigned r = 0; r != R; ++r){
			res[r] = this->row(r) / num;
		}
		return res;
	}

	/**
	 * @brief Multiply by matrix from the left.
	 * Multiply this matrix M by another matrix K from the left (M  = K * M).
	 * Defined only for square matrices and 2x3 matrices. For details about 2x3 matrices see
	 * description of operator*(matrix).
	 * @param matr - matrix to multiply by.
	 * @return reference to this matrix object.
	 */
	template <typename E = matrix>
	std::enable_if_t<R == C || (R == 2 && C == 3), E&> left_mul(const matrix& matr)noexcept{
		return this->operator=(matr.operator*(*this));
	}

	/**
	 * @brief Initialize this matrix with identity matrix.
	 * Defined for both, square and non-square matrices.
	 */
	matrix& set_identity()noexcept{
		using std::min;
		for(size_t r = 1; r != R; ++r){
			for(size_t c = 0; c != min(r, C); ++c){
				this->row(r)[c] = T(0);
			}
		}
		for(size_t i = 0; i != min(R, C); ++i){
			this->row(i)[i] = T(1);
		}
		for(size_t r = 0; r != C; ++r){
			for(size_t c = r + 1; c != C; ++c){
				this->row(r)[c] = T(0);
			}
		}
		return *this;
	}

	/**
	 * @brief Set current matrix to frustum matrix.
	 * Parameters are identical to glFrustum() function from OpenGL.
	 * Defined only for 4x4 matrices.
	 * @param left - left vertical clipping plane.
	 * @param right - right vertical clipping plane.
	 * @param bottom - bottom horizontal clipping plane.
	 * @param top - top horizontal clipping plane.
	 * @param near_val - distance to near depth clipping plane. Must be positive.
	 * @param far_val - distance to the far clipping plane. Must be positive.
	 * @return reference to this matrix instance.
	 */
	template <typename E = T>
	matrix& set_frustum(
			std::enable_if_t<R == C && R == 4, E> left,
			T right,
			T bottom,
			T top,
			T near_val,
			T far_val
		)noexcept
	{
		T w = right - left;
		ASSERT(w != 0)

		T h = top - bottom;
		ASSERT(h != 0)

		T d = far_val - near_val;
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
	 * Multiplies this matrix M by frustum matrix S from the right (M = M * S).
	 * Parameters are identical to glFrustum() function from OpenGL.
	 * Defined only for 4x4 matrices.
	 * @param left - left vertical clipping plane.
	 * @param right - right vertical clipping plane.
	 * @param bottom - bottom horizontal clipping plane.
	 * @param top - top horizontal clipping plane.
	 * @param near_val - distance to near depth clipping plane. Must be positive.
	 * @param far_val - distance to the far clipping plane. Must be positive.
	 * @return reference to this matrix instance.
	 */
	template <typename E = T>
	matrix frustum(
			std::enable_if_t<R == C && R == 4, E> left,
			T right,
			T bottom,
			T top,
			T near_val,
			T far_val
		)noexcept
	{
		matrix f;
		f.set_frustum(left, right, bottom, top, near_val, far_val);
		return this->operator*=(f);
	}

	/**
	 * @brief Multiply current matrix by scale matrix.
	 * Multiplies this matrix M by scale matrix S from the right (M = M * S).
	 * Defined only for 1x1, 2x2, 2x3, 3x3, 4x4 matrices.
	 * @param s - scaling factor to be applied in all directions (x, y and z).
	 * @return reference to this matrix instance.
	 */
	template <typename E = matrix>
	std::enable_if_t<
			(R == C && (1 <= R && R <= 4)) || (R == 2 && C == 3),
			matrix&
		>scale(T s)noexcept
	{
		using std::min;
		size_t end_col = min(min(C, R), size_t(3)); // for 2x3 and 4x4 matrix do not scale last column
		for(size_t r = 0; r != R; ++r){
			auto& cur_row = this->row(r);
			for(size_t c = 0; c != end_col; ++c){
				cur_row[c] *= s;
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
	matrix& scale(T x, T y)noexcept{
		for(size_t r = 0; r != R; ++r){
			this->row(r)[0] *= x;
		}
		if constexpr (C >= 2){
			for(size_t r = 0; r != R; ++r){
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
	matrix& scale(T x, T y, T z)noexcept{
		// update 0th and 1st columns
		this->scale(x, y);

		// update 2nd column
		if constexpr (C >= 3){
			for(size_t r = 0; r != R; ++r){
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
	template <size_t S> matrix& scale(const vector<T, S>& s)noexcept{
		using std::min;
		for(size_t c = 0; c != min(S, C); ++c){
			for(size_t r = 0; r != R; ++r){
				this->row(r)[c] *= s[c];
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
	template <typename E = T>
	matrix& translate(std::enable_if_t<(R == 2 && C == 3) || (R == C && (R == 3 || R == 4)), E> x, T y)noexcept{
		// only last column of the matrix changes
		for(size_t r = 0; r != R; ++r){
			this->row(r)[C - 1] += this->row(r)[0] * x + this->row(r)[1] * y;
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
	template <typename E = T> matrix& translate(std::enable_if_t<R == C && R == 4, E> x, T y, T z)noexcept{
		// only last column of the matrix changes
		for(size_t r = 0; r != R; ++r){
			this->row(r)[C - 1] += this->row(r)[0] * x + this->row(r)[1] * y + this->row(r)[2] * z;
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
	template <typename E = T, size_t S>
	matrix& translate(
			const vector<std::enable_if_t<
					((R == 2 && C == 3) || (R == C && (R == 3 || R == 4))) && (S == 2 || S == 3)
				, E>, S>& t
		)noexcept
	{
		// only last column of the matrix changes
		for(size_t r = 0; r != R; ++r){
			auto& e = this->row(r)[C - 1];
			using std::min;
			for(size_t s = 0; s != min(S, C - 1); ++s){
				e += this->row(r)[s] * t[s];
			}
		}
		return *this;
	}

	/**
	 * @brief Multiply this matrix by rotation matrix.
	 * Multiplies this matrix M by rotation matrix R from the right (M = M * R).
	 * Defined only for 3x3 and 4x4 matrices.
	 * @param q - unit quaternion, representing the rotation.
	 * @return reference to this matrix object.
	 */
	template <typename E = T>
	matrix& rotate(const quaternion<std::enable_if_t<R == C && (R == 3 || R == 4), E>>& q)noexcept{
		return this->operator*=(matrix<T, R, C>(q));
	}

	/**
	 * @brief Multiply this matrix by rotation matrix.
	 * Multiplies this matrix M by rotation matrix R from the right (M = M * R).
	 * Rotation is done around (0, 0, 1) axis by given number of radians.
	 * Positive direction of rotation is determined by a right-hand rule, i.e. from X-axis to Y-axis.
	 * Defined only for 2x3, 3x3 and 4x4 matrices.
	 * @param a - the angle of rotation in radians.
	 * @return reference to this matrix object.
	 */
	template <typename E = T>
	matrix& rotate(std::enable_if_t<(R == 2 && C == 3) || (R == C && (R == 3 || R == 4)), E> a)noexcept{
		if constexpr (R == C){
			// square matrix
			return this->rotate(vector<T, 3>(0, 0, a));
		}else{
			static_assert(R == 2 && C == 3, "2x3 matrix expected");

			// multiply this matrix from the right by the rotation matrix:
			//               | cos(a) -sin(a) 0 |
			// this = this * | sin(a)  cos(a) 0 |

			using std::cos;
			using std::sin;
			T sina = sin(a);
			T cosa = cos(a);

			T m00 = this->row(0)[0] * cosa + this->row(0)[1] * sina;
			T m10 = this->row(1)[0] * cosa + this->row(1)[1] * sina;
			sina = -sina;
			T m01 = this->row(0)[0] * sina + this->row(0)[1] * cosa;
			T m11 = this->row(1)[0] * sina + this->row(1)[1] * cosa;

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
	matrix& transpose()noexcept{
		using std::swap;
		using std::min;
		for(size_t r = 1; r != min(R, C); ++r){
			for(size_t c = 0; c != r; ++c){
				swap(this->row(r)[c], this->row(c)[r]);
			}
		}
		// in case the matrix is not square, then zero out the "non-square" parts
		if constexpr (C > R){
			for(size_t r = 0; r != R; ++r){
				auto& cur_row = this->row(r);
				for(size_t c = R; c != C; ++c){
					cur_row[c] = T(0);
				}
			}
		}else{
			static_assert(R >= C, "");
			for(size_t r = C; r != R; ++r){
				this->row(r).set(T(0));
			}
		}

		return *this;
	}

	/**
	 * @brief Make transposed matrix.
	 * @return a new matrix which is a transpose of this matrix.
	 */
	matrix tpose()const noexcept{
		matrix ret;

		using std::min;

		for(size_t r = 1; r != min(C, R); ++r){
			for(size_t c = 0; c != r; ++c){
				ret[r][c] = this->row(c)[r];
				ret[c][r] = this->row(r)[c];
			}
		}

		// copy diagonal elements
		for(size_t i = 0; i != min(C, R); ++i){
			ret[i][i] = this->row(i)[i];
		}

		// in case the matrix is not square, then zero out the "non-square" parts
		if constexpr (C > R){
			for(size_t r = 0; r != R; ++r){
				auto& cur_row = ret[r];
				for(size_t c = R; c != C; ++c){
					cur_row[c] = T(0);
				}
			}
		}else{
			static_assert(R >= C, "");
			for(size_t r = C; r != R; ++r){
				ret[r].set(T(0));
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
	template <typename E = T>
	matrix<std::enable_if_t<(R >= 2 && C >= 2), E>, R - 1, C - 1> remove(size_t row, size_t col)const noexcept{
		matrix<T, R - 1, C - 1> ret;

		for(size_t dr = 0; dr != row; ++dr){
			for(size_t dc = 0; dc != col; ++dc){
				ret[dr][dc] = this->row(dr)[dc];
			}
			for(size_t dc = col; dc != ret[dr].size(); ++dc){
				ret[dr][dc] = this->row(dr)[dc + 1];
			}
		}

		for(size_t dr = row; dr != ret.size(); ++dr){
			for(size_t dc = 0; dc != col; ++dc){
				ret[dr][dc] = this->row(dr + 1)[dc];
			}
			for(size_t dc = col; dc != ret[dr].size(); ++dc){
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
	template <typename E = T>
	std::enable_if_t<R == C && (R >= 2), E> minor(size_t row, size_t col)const noexcept{
		return this->remove(row, col).det();
	}

	/**
	 * @brief Calculate matrix determinant.
	 * Defined only for square matrices and 2x3 matrix.
	 * @return matrix determinant.
	 */
	template <typename E = T>
	std::enable_if_t<R == C || (R == 2 && C == 3), E> det()const noexcept{
		if constexpr (R == C){
			if constexpr (R == 1){
				return this->row(0)[0];
			}else{
				T ret = 0;
				T sign = 1;
				for(size_t i = 0; i != C; ++i, sign = -sign){
					ret += sign * this->row(0)[i] * this->minor(0, i);
				}
				return ret;
			}
		}else{
			static_assert(R == 2 && (C == 2 || C == 3), "");
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
	 * @brief Calculate right inverse of the matrix.
	 * The resulting inverse matrix T^-1 is to multiply this matrix from the right to get identity matrix.
	 *     T * T^-1 = I
	 * Defined only for square matrices and 2x3 matrix. The 2x3 matrix, before the inversion, is converted to
	 * 3x3 matrix by adding (0, 0, 1) as a last row, then inverted as square matrix, then the last row of the
	 * inversion resulting matrix is discarded.
	 * @return right inverse matrix of this matrix.
	 */
	template <typename E = T>
	matrix<std::enable_if_t<R == C || (R == 2 && C == 3), E>, R, C> inv()const noexcept{
		if constexpr (R == C){
			if constexpr (R == 1){
				return T(1) / this->row(0)[0];
			}else{
				T d = this->det();

				// calculate matrix of minors
				static_assert(R == C, "");
				matrix<T, R, C> mm;

				for(size_t r = 0; r != R; ++r){
					T sign = r % 2 == 0 ? T(1) : T(-1);
					for(size_t c = 0; c != C; ++c){
						mm[r][c] = sign * this->minor(r, c);
						sign = -sign;
					}
				}

				mm.transpose();
				mm /= d;
				return mm;
			}
		}else{
			static_assert(R == 2 && C == 3, "");

			matrix<T, 3, 3> m{
				this->row(0),
				this->row(1),
				{0, 0, 1}
			};

			m.invert();

			return {
				m[0],
				m[1]
			};
		}
	}

	/**
	 * @brief Invert this matrix.
	 * @return reference to this matrix.
	 */
	matrix& invert()noexcept{
		this->operator=(this->inv());
		return *this;
	}

	/**
	 * @brief Snap each matrix component to 0.
	 * For each component, set it to 0 if its absolute value does not exceed the given threshold.
	 * @param threshold - the snapping threshold.
	 * @return reference to this matrix.
	 */
	matrix& snap_to_zero(T threshold)noexcept{
		for(auto& r : *this){
			r.snap_to_zero(threshold);
		}
		return *this;
	}

	/**
	 * @brief Set each element of this matrix to a given number.
	 * @param num - number to set each matrix element to.
	 */
	matrix& set(T num)noexcept{
		for(auto& e : *this){
			e.set(num);
		}
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& s, const matrix& mat){
		for(auto& r : mat){
			s << "|" << r << std::endl;
		}
		return s;
	};
};

template <class T> using matrix2 = matrix<T, 2, 3>;
template <class T> using matrix3 = matrix<T, 3, 3>;
template <class T> using matrix4 = matrix<T, 4, 4>;

}
