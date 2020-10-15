#pragma once

#include <algorithm>
#include <iostream>
#include <array>

#include <utki/debug.hpp>

#include "vector3.hpp"

namespace r4{

template <typename T> class vector2;
template <typename T> class vector3;

/**
 * @brief 3x3 matrix template class.
 * Note, that this matrix class stores elements in row-major order.
 */
template <typename T> class matrix3 : public std::array<vector3<T>, 3>{
	typedef std::array<vector3<T>, 3> base_type;
public:
	/**
	 * @brief Default constructor.
	 * NOTE: it does not initialize the matrix with any values.
	 * Matrix elements are undefined after the matrix is created with this constructor.
	 */
	constexpr matrix3() = default;

	/**
	 * @brief Construct initialized matrix.
	 * Creates a matrix and initializes its rows with the given values.
     * @param row0 - 0th row of the matrix.
	 * @param row1 - 1st row of the matrix.
	 * @param row2 - 2nd row of the matrix.
     */
	constexpr matrix3(
			const vector3<T>& row0,
			const vector3<T>& row1,
			const vector3<T>& row2
		)noexcept :
			base_type{{row0, row1, row2}}
	{}

	constexpr matrix3(const matrix3&) = default;
	matrix3& operator=(const matrix3&) = default;

	/**
	 * @brief Convert to different element type.
	 * @return matrix3 with converted element type.
	 */
	template <typename TT> matrix3<TT> to()noexcept{
		return matrix3<TT>{
				this->row(0).template to<TT>(),
				this->row(1).template to<TT>(),
				this->row(2).template to<TT>()
			};
	}

	/**
	 * @brief Subtract matrix from this matrix.
	 * @param m - matrix to subtract from this matrix.
	 * @return resulting matrix of the subtraction.
	 */
	matrix3 operator-(const matrix3& m)const noexcept{
		return {
				this->row(0) - m.row(0),
				this->row(1) - m.row(1),
				this->row(2) - m.row(2)
			};
	}

	/**
	 * @brief Transform vector by matrix.
	 * Multiply vector V by this matrix M from the right (M * V).
	 * i.e. transform vector with this transformation matrix.
	 * @param vec - vector to transform.
     * @return Transformed vector.
     */
	vector2<T> operator*(const vector2<T>& vec)const noexcept;

	/**
	 * @brief Transform vector by matrix.
	 * Multiply vector V by this matrix M from the right (M * V).
	 * i.e. transform vector with this transformation matrix.
	 * @param vec - vector to transform.
     * @return Transformed vector.
     */
	vector3<T> operator*(const vector3<T>& vec)const noexcept;

	/**
	 * @brief Get matrix row.
	 * @param index - row index to get, must be from 0 to 2.
     * @return reference to vector3 representing the row of this matrix.
     */
	vector3<T>& row(unsigned index)noexcept{
		ASSERT(index < 3)
		return this->operator[](index);
	}

	/**
	 * @brief Get constant matrix row.
	 * @param index - row index to get, must be from 0 to 2.
     * @return constant reference to vector3 representing the row of this matrix.
     */
	const vector3<T>& row(unsigned index)const noexcept{
		ASSERT(index < 3)
		return this->operator[](index);
	}

	/**
	 * @brief Get matrix column.
	 * Constructs and returns a vector3 representing the requested matrix column.
	 * @param index - column index to get, must be from 0 to 2;
	 * @return vector3 representing the requested matrix column.
	 */
	vector3<T> col(unsigned index)const noexcept{
		return vector3<T>{
				this->row(0)[index],
				this->row(1)[index],
				this->row(2)[index]
			};
	}

	/**
	 * @brief Transpose matrix.
	 */
	matrix3& transpose()noexcept{
		std::swap(this->row(1)[0], this->row(0)[1]);
		std::swap(this->row(2)[0], this->row(0)[2]);
		std::swap(this->row(2)[1], this->row(1)[2]);
		return *this;
	}

	/**
	 * @brief Multiply matrix by scalar.
	 * @param num - scalar to multiply the matrix by.
	 * @return multiplied matrix.
	 */
	matrix3 operator*(T num)const noexcept{
		return {
				this->row(0) * num,
				this->row(1) * num,
				this->row(2) * num
			};
	}

	/**
	 * @brief Divide matrix by scalar.
	 * @param num - scalar to divide the matrix by.
	 * @return divided matrix.
	 */
	matrix3 operator/(T num)const noexcept{
		return {
				this->row(0) / num,
				this->row(1) / num,
				this->row(2) / num
			};
	}

	/**
	 * @brief Multiply by matrix from the right.
	 * Calculate result of this matrix M multiplied by another matrix K from the right (M * K).
	 * @param matr - matrix to multiply by (matrix K).
     * @return New matrix as a result of matrices product.
     */
	matrix3 operator*(const matrix3& matr)const noexcept{
		return matrix3{
				vector3<T>{this->row(0) * matr.col(0), this->row(0) * matr.col(1), this->row(0) * matr.col(2)},
				vector3<T>{this->row(1) * matr.col(0), this->row(1) * matr.col(1), this->row(1) * matr.col(2)},
				vector3<T>{this->row(2) * matr.col(0), this->row(2) * matr.col(1), this->row(2) * matr.col(2)}
			};
	}

	/**
	 * @brief Multiply by matrix from the right.
	 * Multiply this matrix M by another matrix K from the right (M  = M * K).
     * @return reference to this matrix object.
     */
	matrix3& operator*=(const matrix3& matr)noexcept{
		return this->operator=(this->operator*(matr));
	}

	/**
     * @brief Multiply matrix by scalar.
     * @param s - scalar to multiply the matrix by.
     * @return reference to this matrix.
     */
    matrix3& operator*=(T s)noexcept{
        this->row(0) *= s;
        this->row(1) *= s;
		this->row(2) *= s;
        return *this;
    }

	/**
	 * @brief Multiply by matrix from the right.
	 * Multiply this matrix M by another matrix K from the right (M  = M * K).
	 * This is the same as operator*=().
	 * @param matr - matrix to multiply by.
	 * @return reference to this matrix object.
	 */
	matrix3& right_multiply(const matrix3& matr)noexcept{
		return this->operator*=(matr);
	}

	/**
	 * @brief Multiply by matrix from the left.
	 * Multiply this matrix M by another matrix K from the left (M  = K * M).
	 * @param matr - matrix to multiply by.
	 * @return reference to this matrix object.
	 */
	matrix3& left_multiply(const matrix3& matr)noexcept{
		return this->operator=(matr.operator*(*this));
	}

	/**
	 * @brief Initialize this matrix with identity matrix.
	 */
	matrix3& set_identity()noexcept{
		this->row(0) = {1, 0, 0};
		this->row(1) = {0, 1, 0};
		this->row(2) = {0, 0, 1};
		return *this;
	}

	/**
	 * @brief Set each element of this matrix to a given number.
	 * @param num - number to set each matrix element to.
	 */
	matrix3& set(T num)noexcept{
		for(auto& e : *this){
			e.set(num);
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
	matrix3& scale(T x, T y)noexcept{
		// multiply this matrix from the right by the scale matrix:
		//               / x 0 0 \
		// this = this * | 0 y 0 |
		//               \ 0 0 1 /

		// update 0th column
		this->row(0)[0] *= x;
		this->row(1)[0] *= x;
		this->row(2)[0] *= x;

		// update 1st column
		this->row(0)[1] *= y;
		this->row(1)[1] *= y;
		this->row(2)[1] *= y;

		// NOTE: 2nd column remains unchanged
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
	matrix3& scale(T x, T y, T z)noexcept{
		// multiply this matrix from the right by the scale matrix:
		//               / x 0 0 \
		// this = this * | 0 y 0 |
		//               \ 0 0 z /

		this->scale(x, y);

		// update 2nd column
		this->row(0)[2] *= z;
		this->row(1)[2] *= z;
		this->row(2)[2] *= z;

		return *this;
	}

	/**
	 * @brief Multiply current matrix by scale matrix.
	 * Multiplies this matrix M by scale matrix S from the right (M = M * S).
	 * @param s - scaling factor to be applied in all 3 directions (x, y and z).
	 * @return reference to this matrix instance.
	 */
	matrix3& scale(T s)noexcept{
		return this->scale(s, s, s);
	}

	/**
	 * @brief Multiply current matrix by scale matrix.
	 * Multiplies this matrix M by scale matrix S from the right (M = M * S).
	 * @param s - vector of scaling factors in x and y directions, scaling factor in z direction is 1.
	 * @return reference to this matrix instance.
	 */
	matrix3& scale(const vector2<T>& s)noexcept;

	/**
	 * @brief Multiply this matrix by translation matrix.
	 * Multiplies this matrix M by translation matrix T from the right (M = M * T).
	 * @param x - x component of translation vector.
	 * @param y - y component of translation vector.
	 * @return reference to this matrix object.
	 */
	matrix3& translate(T x, T y)noexcept{
		// multiply this matrix from the right by the translation matrix:
		//               / 1 0 x \
		// this = this * | 0 1 y |
		//               \ 0 0 1 /

		// NOTE: 0th and 1st columns remain unchanged

		// calculate 2nd column
		this->row(0)[2] += this->row(0).x() * x + this->row(0).y() * y;
		this->row(1)[2] += this->row(1).x() * x + this->row(1).y() * y;

		return *this;
	}

	/**
	 * @brief Multiply this matrix by translation matrix.
	 * Multiplies this matrix M by translation matrix T from the right (M = M * T).
	 * @param t - translation vector.
	 * @return reference to this matrix object.
	 */
	matrix3& translate(const vector2<T>& t)noexcept;

	/**
	 * @brief Multiply this matrix by rotation matrix.
	 * Multiplies this matrix M by rotation matrix R from the right (M = M * R).
	 * Positive direction of rotation is counter-clockwise, i.e. from X-axis to Y-axis.
	 * @param a - the angle of rotation in radians.
	 * @return reference to this matrix object.
	 */
	matrix3& rotate(T a)noexcept{
		// multiply this matrix from the right by the rotation matrix:
		//               / cos(a) -sin(a) 0 \
		// this = this * | sin(a)  cos(a) 0 |
		//               \      0       0 1 /

		using std::cos;
		using std::sin;
		T sina = sin(a);
		T cosa = cos(a);

		T m00 = this->row(0)[0] * cosa + this->row(0)[1] * sina;
		T m10 = this->row(1)[0] * cosa + this->row(1)[1] * sina;
		T m20 = this->row(2)[0] * cosa + this->row(2)[1] * sina;
		sina = -sina;
		T m01 = this->row(0)[0] * sina + this->row(0)[1] * cosa;
		T m11 = this->row(1)[0] * sina + this->row(1)[1] * cosa;
		T m21 = this->row(2)[0] * sina + this->row(2)[1] * cosa;

		this->row(0)[0] = m00;
		this->row(1)[0] = m10;
		this->row(2)[0] = m20;

		this->row(0)[1] = m01;
		this->row(1)[1] = m11;
		this->row(2)[1] = m21;

		return *this;
	}

	/**
	 * @brief Calculate matrix's minor.
	 * @param r - index of the row to remove from this matrix.
	 * @param c - index of the column to remove from this matrix.
	 * @return determinant of the matrix constructed from this matrix by removing given row and given column.
	 */
	T minor(unsigned r, unsigned c)const noexcept{
		std::array<std::array<T, 2>, 2> mm;

		for(unsigned dr = 0; dr != r; ++dr){
			for(unsigned dc = 0; dc != c; ++dc){
				mm[dr][dc] = this->row(dr)[dc];
			}
			for(unsigned dc = c; dc != mm[dr].size(); ++dc){
				mm[dr][dc] = this->row(dr)[dc + 1];
			}
		}

		for(unsigned dr = r; dr != mm.size(); ++dr){
			for(unsigned dc = 0; dc != c; ++dc){
				mm[dr][dc] = this->row(dr + 1)[dc];
			}
			for(unsigned dc = c; dc != mm[dr].size(); ++dc){
				mm[dr][dc] = this->row(dr + 1)[dc + 1];
			}
		}

		return mm[0][0] * mm[1][1] - mm[0][1] * mm[1][0];
	}

	/**
	 * @brief Calculate matrix determinant.
	 * @return matrix determinant.
	 */
	T det()const noexcept{
		//    |a b c|          |e f|          |d f|          |d e|
		// det|d e f| = a * det|h i| - b * det|g i| + c * det|g h| = aei + bfg + cdh - ceg - bdi - afh
		//    |g h i|
		return this->row(0)[0] * this->row(1)[1] * this->row(2)[2]
				+ this->row(0)[1] * this->row(1)[2] * this->row(2)[0]
				+ this->row(0)[2] * this->row(1)[0] * this->row(2)[1]
				- this->row(0)[2] * this->row(1)[1] * this->row(2)[0]
				- this->row(0)[1] * this->row(1)[0] * this->row(2)[2]
				- this->row(0)[0] * this->row(1)[2] * this->row(2)[1];
	}

	/**
	 * @brief Calculate right inverse of the matrix.
	 * The resulting inverse matrix is to multiply this matrix from the right to get identioty matrix.
	 *     T * T^-1 = I
	 * @return right inverse matrix of this matrix.
	 */
	matrix3<T> inv()const noexcept{
		T d = this->det();

		// calculate matrix of minors
		matrix3<T> mm;

		T sign = 1;
		for(unsigned r = 0; r != this->size(); ++r){
			for(unsigned c = 0; c != this->row(r).size(); ++c){
				mm[r][c] = sign * this->minor(r, c);
				sign = -sign;
			}
		}

		mm.transpose();

		return mm / d;
	}

	/**
	 * @brief Invert this matrix.
	 * @return reference to this matrix.
	 */
	matrix3& invert()noexcept{
		this->operator=(this->inv());
		return *this;
	}

	/**
	 * @brief Snap each matrix component to 0.
	 * For each component, set it to 0 if its absolute value does not exceed the given threshold.
	 * @param threshold - the snapping threshold.
	 * @return reference to this matrix.
	 */
	matrix3& snap_to_zero(T threshold)noexcept{
		for(auto& e : *this){
			e.snap_to_zero(threshold);
		}
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& s, const matrix3<T>& mat){
		s << "\n";
		s << "\t/" << mat[0][0] << " " << mat[0][1] << " " << mat[0][2] << "\\" << std::endl;
		s << "\t|" << mat[1][0] << " " << mat[1][1] << " " << mat[1][2] << "|" << std::endl;
		s << "\t\\" << mat[2][0] << " " << mat[2][1] << " " << mat[2][2] << "/";
		return s;
	};
};

}

#include "vector2.hpp"
#include "vector3.hpp"

namespace r4{

template <class T> vector2<T> matrix3<T>::operator*(const vector2<T>& vec)const noexcept{
	// TRACE_ALWAYS(<< "this->row(1) = " << this->row(1) << " vec = " << vec << std::endl)
	return vector2<T>(
			this->row(0) * vec,
			this->row(1) * vec
		);
}

template <class T> vector3<T> matrix3<T>::operator*(const vector3<T>& vec)const noexcept{
	return vector3<T>(
			this->row(0) * vec,
			this->row(1) * vec,
			this->row(2) * vec
		);
}

template <class T> matrix3<T>& matrix3<T>::scale(const vector2<T>& s)noexcept{
	return this->scale(s.x, s.y);
}

template <class T> matrix3<T>& matrix3<T>::translate(const vector2<T>& t)noexcept{
	return this->translate(t.x(), t.y());
}

static_assert(sizeof(matrix3<float>) == sizeof(float) * 3 * 3, "size mismatch");
static_assert(sizeof(matrix3<double>) == sizeof(double) * 3 * 3, "size mismatch");

}
