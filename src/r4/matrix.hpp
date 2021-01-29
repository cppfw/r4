#pragma once

#include <array>

#include "vector.hpp"
#include "quaternion.hpp"

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
			matrix(rows, std::make_index_sequence<R>())
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
		for(unsigned i = 0; i != R; ++i){
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
		//     /  1-(2y^2+2z^2)   2xy-2zw         2xz+2yw         0   \
		// M = |  2xy+2zw         1-(2x^2+2z^2)   2yz-2xw         0   |
		//     |  2xz-2yw         2zy+2xw         1-(2x^2+2y^2)   0   |
		//     \  0               0               0               1   /

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
	vector<T, C>& row(unsigned r)noexcept{
		ASSERT(r < this->size())
		return this->operator[](r);
	}

	/**
	 * @brief Get matrix row.
	 * @param r - row number to get.
     * @return reference to vector representing the row of this matrix.
     */
	const vector<T, C>& row(unsigned r)const noexcept{
		ASSERT(r < this->size())
		return this->operator[](r);
	}

	/**
	 * @brief Transform vector by matrix.
	 * Multiply vector V by this matrix M from the right (M * V).
	 * i.e. transform vector with this transformation matrix.
	 * @param vec - vector to transform.
	 * @return Transformed vector.
	 */
	vector<T, R> operator*(const vector<T, C>& vec)const noexcept{
		vector<T, R> r;
		for(unsigned i = 0; i != R; ++i){
			r[i] = this->row(i) * vec;
		}
		return r;
	}

	/**
	 * @brief Multiply by matrix from the right.
	 * Calculate result of this matrix M multiplied by another matrix K from the right (M * K).
	 * @param m - matrix to multiply by (matrix K).
     * @return New matrix as a result of matrices product.
     */
	template <size_t CC> matrix<T, R, CC> operator*(const matrix<T, C, CC>& m)const noexcept{
		matrix<T, R, CC> ret;
		for(unsigned rd = 0; rd != ret.size(); ++rd){
			auto& row_d = ret[rd];
			for(unsigned cd = 0; cd != row_d.size(); ++cd){
				auto v = 0;
				for(unsigned i = 0; i != C; ++i){
					v += this->row(rd)[i] * m[i][cd];
				}
				ret[rd][cd] = v;
			}

		}
		return ret;
	}

	/**
	 * @brief Multiply by matrix from the right.
	 * Defined only for square matrices.
	 * Multiply this matrix M by another matrix K from the right (M  = M * K).
     * @return reference to this matrix object.
     */
	template <typename E = matrix> std::enable_if_t<R == C, matrix&> operator*=(const matrix& matr)noexcept{
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
	 * @brief Multiply by matrix from the right.
	 * Multiply this matrix M by another matrix K from the right (M  = M * K).
	 * This is the same as operator*=().
	 * @param matr - matrix to multiply by.
	 * @return reference to this matrix object.
	 */
	template <typename E = matrix> std::enable_if_t<R == C, matrix&> right_mul(const matrix& matr)noexcept{
		return this->operator*=(matr);
	}

	/**
	 * @brief Multiply by matrix from the left.
	 * Multiply this matrix M by another matrix K from the left (M  = K * M).
	 * Defined only for square matrices.
	 * @param matr - matrix to multiply by.
	 * @return reference to this matrix object.
	 */
	matrix& left_mul(const matrix& matr)noexcept{
		return this->operator=(matr.operator*(*this));
	}

	/**
	 * @brief Initialize this matrix with identity matrix.
	 * Defined for both, square and non-square matrices.
	 */
	matrix& set_identity()noexcept{
		using std::min;
		for(unsigned r = 1; r != R; ++r){
			for(unsigned c = 0; c != min(r, C); ++c){
				this->row(r)[c] = T(0);
			}
		}
		for(unsigned i = 0; i != min(R, C); ++i){
			this->row(i)[i] = T(1);
		}
		for(unsigned r = 0; r != R - 1; ++r){
			if(r >= C) continue;
			for(unsigned c = r + 1; c != C; ++c){
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
	template <typename E = matrix>
	std::enable_if_t<R == C && R == 4, matrix&> set_frustum(
			 T left,
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
		unsigned end_col = min(min(C, R), 3); // for 2x3 and 4x4 matrix do not scale last column
		for(unsigned r = 0; r != R; ++r){
			auto& cur_row = this->row(r);
			for(unsigned c = 0; c != end_col; ++c) cur_row[c] *= s;
		}

		return this->scale(s, s, s);
	}

	/**
	 * @brief Multiply current matrix by scale matrix.
	 * Multiplies this matrix M by scale matrix S from the right (M = M * S).
	 * Scaling factor in z direction is 1.
	 * @param x - scaling factor in x direction.
	 * @param y - scaling factor in y direction.
	 * @return reference to this matrix instance.
	 */
	matrix& scale(T x, T y)noexcept{
		// TODO:

		// update 0th column
		this->row(0)[0] * = x;
		this->row(1)[0] *= x;
		this->row(2)[0] *= x;
		this->row(3)[0] *= x;

		// update 1st column
		this->row(0)[1] *= y;
		this->row(1)[1] *= y;
		this->row(2)[1] *= y;
		this->row(3)[1] *= y;

		// NOTE: 2nd and 3rd columns remain unchanged
		return *this;
	}

	/**
	 * @brief Transpose this matrix.
	 */
	matrix& transpose()noexcept{
		using std::swap;
		for(unsigned r = 1; r != this->size(); ++r){
			for(unsigned c = 0; c != r; ++c){
				swap(this->row(r)[c], this->row(c)[r]);
			}
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
