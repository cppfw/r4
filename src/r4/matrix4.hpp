#pragma once

#include <algorithm>
#include <iostream>
#include <array>

#include <utki/debug.hpp>

#include "vector4.hpp"

#ifdef minor
#	undef minor
#endif

namespace r4{

template <class T> class vector2;
template <class T> class vector3;
template <class T> class quaternion;
template <class T> class matrix3;

/**
 * @brief 4x4 matrix template class.
 * Elements are stored in memory in row-major order.
 */
template <typename T> class matrix4 : public std::array<r4::vector4<T>, 4>{
	typedef std::array<r4::vector4<T>, 4> base_type;
public:
	/**
	 * @brief Default constructor.
	 * NOTE: it does not initialize the matrix with any values.
	 * Matrix elements are undefined after the matrix is created with this constructor.
	 */
	constexpr matrix4() = default;

	/**
	 * @brief Construct initialized matrix.
	 * Creates a matrix and initializes its columns by the given values.
     * @param row0 - 0th row of the matrix.
	 * @param row1 - 1st row of the matrix.
	 * @param row2 - 2nd row of the matrix.
	 * @param row3 - 3rd row of the matrix.
     */
	constexpr matrix4(
			const vector4<T>& row0,
			const vector4<T>& row1,
			const vector4<T>& row2,
			const vector4<T>& row3
		)noexcept :
			base_type{
					row0,
					row1,
					row2,
					row3
				}
	{}

	/**
	 * @brief Construct rotation matrix.
	 * Constructs matrix and initializes it to a rotation matrix from given unit quaternion.
     * @param quat - unit quaternion defining the rotation.
     */
	constexpr matrix4(const quaternion<T>& quat)noexcept;

	constexpr matrix4(const matrix4&) = default;
	matrix4& operator=(const matrix4&) = default;

	/**
	 * @brief Convert to different element type.
	 * @return matrix4 with converted element type.
	 */
	template <typename TT> matrix4<TT> to()noexcept{
		return matrix4<TT>{
				this->row(0).template to<TT>(),
				this->row(1).template to<TT>(),
				this->row(2).template to<TT>(),
				this->row(3).template to<TT>()
			};
	}

	/**
	 * @brief Subtract matrix from this matrix.
	 * @param m - matrix to subtract from this matrix.
	 * @return resulting matrix of the subtraction.
	 */
	matrix4 operator-(const matrix4& m)const noexcept{
		return {
				this->row(0) - m.row(0),
				this->row(1) - m.row(1),
				this->row(2) - m.row(2),
				this->row(3) - m.row(3)
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
	 * @brief Transform vector by matrix.
	 * Multiply vector V by this matrix M from the right (M * V).
	 * i.e. transform vector with this transformation matrix.
	 * @param vec - vector to transform.
     * @return Transformed vector.
     */
	vector4<T> operator*(const vector4<T>& vec)const noexcept;

	/**
	 * @brief Get matrix row.
	 * @param rowNum - row number to get, must be from 0 to 3.
     * @return reference to vector4 representing the row of this matrix.
     */
	vector4<T>& row(unsigned rowNum)noexcept{
		ASSERT(rowNum < 4)
		return this->operator[](rowNum);
	}

	/**
	 * @brief Get matrix row.
	 * @param rowNum - row number to get, must be from 0 to 3.
     * @return reference to vector4 representing the row of this matrix.
     */
	const vector4<T>& row(unsigned rowNum)const noexcept{
		ASSERT(rowNum < 4)
		return this->operator[](rowNum);
	}

	/**
	 * @brief Get matrix column.
	 * Constructs and returns a vector4 representing the requested matrix column.
	 * @param index - column index to get, must be from 0 to 3;
	 * @return vector4 representing the requested matrix column.
	 */
	vector4<T> col(unsigned index)const noexcept{
		return vector4<T>{
				this->row(0)[index],
				this->row(1)[index],
				this->row(2)[index],
				this->row(3)[index]
			};
	}

	/**
	 * @brief Multiply by matrix from the right.
	 * Calculate result of this matrix M multiplied by another matrix K from the right (M * K).
	 * @param matr - matrix to multiply by (matrix K).
     * @return New matrix as a result of matrices product.
     */
	matrix4 operator*(const matrix4& matr)const noexcept{
		return matrix4{
				vector4<T>{this->row(0) * matr.col(0), this->row(0) * matr.col(1), this->row(0) * matr.col(2), this->row(0) * matr.col(3)},
				vector4<T>{this->row(1) * matr.col(0), this->row(1) * matr.col(1), this->row(1) * matr.col(2), this->row(1) * matr.col(3)},
				vector4<T>{this->row(2) * matr.col(0), this->row(2) * matr.col(1), this->row(2) * matr.col(2), this->row(2) * matr.col(3)},
				vector4<T>{this->row(3) * matr.col(0), this->row(3) * matr.col(1), this->row(3) * matr.col(2), this->row(3) * matr.col(3)}
			};
	}

	/**
	 * @brief Multiply matrix by scalar.
	 * @param num - scalar to multiply the matrix by.
	 * @return multiplied matrix.
	 */
	matrix4 operator*(T num)const noexcept{
		return {
				this->row(0) * num,
				this->row(1) * num,
				this->row(2) * num,
				this->row(3) * num
			};
	}

	/**
	 * @brief Divide matrix by scalar.
	 * @param num - scalar to divide the matrix by.
	 * @return divided matrix.
	 */
	matrix4 operator/(T num)const noexcept{
		return {
				this->row(0) / num,
				this->row(1) / num,
				this->row(2) / num,
				this->row(3) / num
			};
	}

	/**
	 * @brief Transpose matrix.
	 */
	matrix4& transpose()noexcept{
		std::swap(this->row(1)[0], this->row(0)[1]);
		std::swap(this->row(2)[0], this->row(0)[2]);
		std::swap(this->row(3)[0], this->row(0)[3]);

		std::swap(this->row(2)[1], this->row(1)[2]);
		std::swap(this->row(3)[1], this->row(1)[3]);

		std::swap(this->row(3)[2], this->row(2)[3]);
		return *this;
	}

	/**
	 * @brief Multiply by matrix from the right.
	 * Multiply this matrix M by another matrix K from the right (M  = M * K).
     * @return reference to this matrix object.
     */
	matrix4& operator*=(const matrix4& matr)noexcept{
		return this->operator=(this->operator*(matr));
	}

	/**
	 * @brief Multiply matrix by scalar.
	 * @param n - scalar to multiply the matrix by.
	 * @return reference to this matrix4.
	 */
	matrix4& operator*=(T n){
		this->row(0) *= n;
		this->row(1) *= n;
		this->row(2) *= n;
		this->row(3) *= n;
		return *this;
	}

	/**
	 * @brief Multiply by matrix from the right.
	 * Multiply this matrix M by another matrix K from the right (M  = M * K).
	 * This is the same as operator*=().
	 * @param matr - matrix to multiply by.
	 * @return reference to this matrix object.
	 */
	matrix4& right_mul(const matrix4& matr)noexcept{
		return this->operator*=(matr);
	}

	/**
	 * @brief Multiply by matrix from the left.
	 * Multiply this matrix M by another matrix K from the left (M  = K * M).
	 * @param matr - matrix to multiply by.
	 * @return reference to this matrix object.
	 */
	matrix4& left_mul(const matrix4& matr)noexcept{
		return this->operator=(matr.operator*(*this));
	}

	/**
	 * @brief Initialize this matrix with identity matrix.
	 */
	matrix4& set_identity()noexcept{
		this->row(0) = vector4<T>(1, 0, 0, 0);
		this->row(1) = vector4<T>(0, 1, 0, 0);
		this->row(2) = vector4<T>(0, 0, 1, 0);
		this->row(3) = vector4<T>(0, 0, 0, 1);
		return *this;
	}

	/**
	 * @brief Set current matrix to frustum matrix.
	 * Parameters are identical to glFrustum() function from OpenGL.
	 * @param left - left vertical clipping plane.
	 * @param right - right vertical clipping plane.
	 * @param bottom - bottom horizontal clipping plane.
	 * @param top - top horizontal clipping plane.
	 * @param nearVal - distance to near depth clipping plane. Must be positive.
	 * @param farVal - distance to the far clipping plane. Must be positive.
	 * @return reference to this matrix instance.
	 */
	matrix4& set_frustum(T left, T right, T bottom, T top, T nearVal, T farVal)noexcept{
		T w = right - left;
		ASSERT(w != 0)

		T h = top - bottom;
		ASSERT(h != 0)

		T d = farVal - nearVal;
		ASSERT(d != 0)

		matrix4& f = *this;
		f[0][0] = 2 * nearVal / w;
		f[0][1] = 0;
		f[0][2] = (right + left) / w;
		f[0][3] = 0;

		f[1][0] = 0;
		f[1][1] = 2 * nearVal / h;
		f[1][2] = (top + bottom) / h;
		f[1][3] = 0;

		f[2][0] = 0;
		f[2][1] = 0;
		f[2][2] = -(farVal + nearVal) / d;
		f[2][3] = -2 * farVal * nearVal / d;

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
	 * @param left - left vertical clipping plane.
	 * @param right - right vertical clipping plane.
	 * @param bottom - bottom horizontal clipping plane.
	 * @param top - top horizontal clipping plane.
	 * @param nearVal - distance to near depth clipping plane. Must be positive.
	 * @param farVal - distance to the far clipping plane. Must be positive.
	 * @return reference to this matrix instance.
	 */
	matrix4& frustum(T left, T right, T bottom, T top, T nearVal, T farVal)noexcept{
		matrix4 f;

		f.set_frustum(left, right, bottom, top, nearVal, farVal);

		return this->right_mul(f);
	}

	/**
	 * @brief Set each element of this matrix to a given number.
	 * @param num - number to set each matrix element to.
	 */
	matrix4& set(T num)noexcept{
		for(auto& e : *this){
			e.set(num);
		}
		return *this;
	}

	/**
	 * @brief Set this matrix to be a rotation matrix.
	 * Sets this matrix to a matrix representing a rotation defined by a unit quaternion.
     * @param quat - unit quaternion defining the rotation.
     * @return Reference to this matrix object.
     */
	matrix4& set(const quaternion<T>& quat)noexcept;

	/**
	 * @brief Multiply current matrix by scale matrix.
	 * Multiplies this matrix M by scale matrix S from the right (M = M * S).
	 * Scaling factor in z direction is 1.
	 * @param x - scaling factor in x direction.
	 * @param y - scaling factor in y direction.
	 * @return reference to this matrix instance.
	 */
	matrix4& scale(T x, T y)noexcept{
		// update 0th column
		this->row(0)[0] *= x;
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
	 * @brief Multiply current matrix by scale matrix.
	 * Multiplies this matrix M by scale matrix S from the right (M = M * S).
	 * @param x - scaling factor in x direction.
	 * @param y - scaling factor in y direction.
	 * @param z - scaling factor in z direction.
	 * @return reference to this matrix instance.
	 */
	matrix4& scale(T x, T y, T z)noexcept{
		// update 0th and 1st columns
		this->scale(x, y);

		// update 2nd column
		this->row(0)[2] *= z;
		this->row(1)[2] *= z;
		this->row(2)[2] *= z;
		this->row(3)[2] *= z;

		// NOTE: 3rd column remains unchanged
		return *this;
	}

	/**
	 * @brief Multiply current matrix by scale matrix.
	 * Multiplies this matrix M by scale matrix S from the right (M = M * S).
	 * @param s - scaling factor to be applied in all 3 directions (x, y and z).
	 * @return reference to this matrix instance.
	 */
	matrix4& scale(T s)noexcept{
		return this->scale(s, s, s);
	}

	/**
	 * @brief Multiply current matrix by scale matrix.
	 * Multiplies this matrix M by scale matrix S from the right (M = M * S).
	 * @param s - vector of scaling factors in x and y directions, scaling factor in z direction is 1.
	 * @return reference to this matrix instance.
	 */
	matrix4& scale(const vector2<T>& s)noexcept;

	/**
	 * @brief Multiply current matrix by scale matrix.
	 * Multiplies this matrix M by scale matrix S from the right (M = M * S).
	 * @param s - vector of scaling factors in x, y and z directions.
	 * @return reference to this matrix instance.
	 */
	matrix4& scale(const vector3<T>& s)noexcept;

	/**
	 * @brief Multiply this matrix by translation matrix.
	 * Multiplies this matrix M by translation matrix T from the right (M = M * T).
	 * Translation only occurs in x-y plane, no translation in z direction,
	 * i.e. z component of translation vector is assumed to be 0.
	 * @param x - x component of translation vector.
	 * @param y - y component of translation vector.
	 * @return reference to this matrix object.
	 */
	matrix4& translate(T x, T y)noexcept{
		// NOTE: 0th, 1st and 2nd columns remain unchanged

		// calculate 3rd column
		this->row(0)[3] += this->row(0)[0] * x + this->row(0)[1] * y;
		this->row(1)[3] += this->row(1)[0] * x + this->row(1)[1] * y;
		this->row(2)[3] += this->row(2)[0] * x + this->row(2)[1] * y;
		this->row(3)[3] += this->row(3)[0] * x + this->row(3)[1] * y;

		return *this;
	}

	/**
	 * @brief Multiply this matrix by translation matrix.
	 * Multiplies this matrix M by translation matrix T from the right (M = M * T).
	 * @param x - x component of translation vector.
	 * @param y - y component of translation vector.
	 * @param z - z component of translation vector.
	 * @return reference to this matrix object.
	 */
	matrix4& translate(T x, T y, T z)noexcept{
		// NOTE: 0th, 1st and 2nd columns remain unchanged
		this->translate(x, y);

		this->row(0)[3] += this->row(0)[2] * z;
		this->row(1)[3] += this->row(1)[2] * z;
		this->row(2)[3] += this->row(2)[2] * z;
		this->row(3)[3] += this->row(3)[2] * z;

		return *this;
	}

	/**
	 * @brief Multiply this matrix by translation matrix.
	 * Multiplies this matrix M by translation matrix T from the right (M = M * T).
	 * Translation only occurs in x-y plane, no translation in z direction,
	 * i.e. z component of translation vector is assumed being 0.
	 * @param t - translation vector.
	 * @return reference to this matrix object.
	 */
	matrix4& translate(const vector2<T>& t)noexcept;

	/**
	 * @brief Multiply this matrix by translation matrix.
	 * Multiplies this matrix M by translation matrix T from the right (M = M * T)
	 * @param t - translation vector.
	 * @return reference to this matrix object.
	 */
	matrix4& translate(const vector3<T>& t)noexcept;

	/**
	 * @brief Multiply this matrix by rotation matrix.
	 * Multiplies this matrix M by rotation matrix R from the right (M = M * R).
	 * @param q - unit quaternion, representing the rotation.
	 * @return reference to this matrix object.
	 */
	matrix4& rotate(const quaternion<T>& q)noexcept;

	/**
	 * @brief Multiply this matrix by rotation matrix.
	 * Multiplies this matrix M by rotation matrix R from the right (M = M * R).
	 * @param rot - vector, representing the rotation. The vector direction
	 *              defines the axis of rotation, vector length defines
	 *              the angle of rotation in radians.
	 * @return reference to this matrix object.
	 */
	matrix4& rotate(const vector3<T>& rot)noexcept;

	/**
	 * @brief Multiply this matrix by rotation matrix.
	 * Multiplies this matrix M by rotation matrix R from the right (M = M * R).
	 * Rotation is done around (0, 0, 1) axis by given number of radians.
	 * Positive direction of rotation is determined by a right-hand rule, i.e. from X-axis to Y-axis.
	 * @param rot - the angle of rotation in radians.
	 * @return reference to this matrix object.
	 */
	matrix4& rotate(T rot)noexcept;

	/**
	 * @brief Get minor matrix.
	 * Retruns a 3x3 matrix which is constructed from this matrix by removing given row and given column.
	 * @param r - index of the row to remove.
	 * @param c - index of the column to remove.
	 * @return minor matrix.
	 */
	matrix3<T> minor_matrix(T r, T c)const noexcept;

	/**
	 * @brief Claculate minor.
	 * This is equivalent to matrix_minor(r, c).det().
	 */
	T minor(T r, T c)const noexcept{
		return this->minor_matrix(r, c).det();
	}

	/**
	 * @brief Calculate matrix determinant.
	 * @return matrix determinant.
	 */
	T det()const noexcept{
		T ret = 0;
		T sign = 1;
		for(unsigned i = 0; i != this->row(0).size(); ++i, sign = -sign){
			ret += sign * this->row(0)[i] * this->minor(0, i);
		}

		return ret;
	}

	/**
	 * @brief Snap each matrix component to 0.
	 * For each component, set it to 0 if its absolute value does not exceed the given threshold.
	 * @param threshold - the snapping threshold.
	 * @return reference to this matrix.
	 */
	matrix4& snap_to_zero(T threshold)noexcept{
		for(auto& e : *this){
			e.snap_to_zero(threshold);
		}
		return *this;
	}

	/**
	 * @brief Calculate right inverse of the matrix.
	 * The resulting inverse matrix is to multiply this matrix from the right to get identioty matrix.
	 *     T * T^-1 = I
	 * @return right inverse matrix of this matrix.
	 */
	matrix4<T> inv()const noexcept{
		T d = this->det();

		// calculate matrix of minors
		matrix4<T> mm;

		T sign = 1;
		for(unsigned r = 0; r != this->size(); ++r){
			for(unsigned c = 0; c != this->row(r).size(); ++c){
				mm[r][c] = sign * this->minor(r, c);
				sign = -sign;
			}
			sign = -sign;
		}

		mm.transpose();

		return mm / d;
	}

	friend std::ostream& operator<<(std::ostream& s, const matrix4<T>& mat){
		s << "\n";
		s << "\t/" << mat[0][0] << " " << mat[0][1] << " " << mat[0][2] << " " << mat[0][3] << "\\" << std::endl;
		s << "\t|" << mat[1][0] << " " << mat[1][1] << " " << mat[1][2] << " " << mat[1][3] << "|" << std::endl;
		s << "\t|" << mat[2][0] << " " << mat[2][1] << " " << mat[2][2] << " " << mat[2][3] << "|" << std::endl;
		s << "\t\\" << mat[3][0] << " " << mat[3][1] << " " << mat[3][2] << " " << mat[3][3] << "/";
		return s;
	};
};

}

#include "vector2.hpp"
#include "vector3.hpp"
#include "quaternion.hpp"
#include "matrix3.hpp"

namespace r4{

template <class T> vector2<T> matrix4<T>::operator*(const vector2<T>& vec)const noexcept{
	return vector2<T>(
			this->row(0) * vec,
			this->row(1) * vec
		);
}

template <class T> vector3<T> matrix4<T>::operator*(const vector3<T>& vec)const noexcept{
	return vector3<T>(
			this->row(0) * vec,
			this->row(1) * vec,
			this->row(2) * vec
		);
}

template <class T> vector4<T> matrix4<T>::operator*(const vector4<T>& vec)const noexcept{
	return vector4<T>(
			this->row(0) * vec,
			this->row(1) * vec,
			this->row(2) * vec,
			this->row(3) * vec
		);
}

template <class T> matrix4<T>& matrix4<T>::scale(const vector3<T>& s)noexcept{
	return this->scale(s.x(), s.y(), s.z());
}

template <class T> matrix4<T>& matrix4<T>::scale(const vector2<T>& s)noexcept{
	return this->scale(s.x(), s.y());
}

template <class T> matrix4<T>& matrix4<T>::translate(const vector2<T>& t)noexcept{
	return this->translate(t.x(), t.y());
}

template <class T> matrix4<T>& matrix4<T>::translate(const vector3<T>& t)noexcept{
	return this->translate(t.x(), t.y(), t.z());
}

template <class T> matrix4<T>& matrix4<T>::rotate(const quaternion<T>& q)noexcept{
	return this->right_mul(matrix4<T>(q));
}

template <class T> matrix4<T>& matrix4<T>::rotate(const vector3<T>& rot)noexcept{
	return this->rotate(quaternion<T>(rot));
}

template <class T> matrix4<T>& matrix4<T>::rotate(T rot)noexcept{
	return this->rotate(vector3<T>(0, 0, rot));
}

template <class T> constexpr matrix4<T>::matrix4(const quaternion<T>& quat)noexcept{
	this->set(quat);
}

template <class T> matrix4<T>& matrix4<T>::set(const quaternion<T>& quat)noexcept{
	// Quaternion to matrix conversion:
	//     /  1-(2y^2+2z^2)   2xy-2zw         2xz+2yw         0   \
	// M = |  2xy+2zw         1-(2x^2+2z^2)   2yz-2xw         0   |
	//     |  2xz-2yw         2zy+2xw         1-(2x^2+2y^2)   0   |
	//     \  0               0               0               1   /

	// First column
	this->row(0)[0] = T(1) - T(2) * (utki::pow2(quat.y()) + utki::pow2(quat.z()));
	this->row(1)[0] = T(2) * (quat.x() * quat.y() + quat.z() * quat.w());
	this->row(2)[0] = T(2) * (quat.x() * quat.z() - quat.y() * quat.w());
	this->row(3)[0] = T(0);

	// Second column
	this->row(0)[1] = T(2) * (quat.x() * quat.y() - quat.z() * quat.w());
	this->row(1)[1] = T(1) - T(2) * (utki::pow2(quat.x()) + utki::pow2(quat.z()));
	this->row(2)[1] = T(2) * (quat.z() * quat.y() + quat.x() * quat.w());
	this->row(3)[1] = T(0);

	// Third column
	this->row(0)[2] = T(2) * (quat.x() * quat.z() + quat.y() * quat.w());
	this->row(1)[2] = T(2) * (quat.y() * quat.z() - quat.x() * quat.w());
	this->row(2)[2] = T(1) - T(2) * (utki::pow2(quat.x()) + utki::pow2(quat.y()));
	this->row(3)[2] = T(0);

	// Fourth column
	this->row(0)[3] = T(0);
	this->row(1)[3] = T(0);
	this->row(2)[3] = T(0);
	this->row(3)[3] = T(1);

	return *this;
}

template <class T> matrix3<T> matrix4<T>::minor_matrix(T r, T c)const noexcept{
	matrix3<T> ret;

	for(unsigned dr = 0; dr != r; ++dr){
		for(unsigned dc = 0; dc != c; ++dc){
			ret[dr][dc] = this->row(dr)[dc];
		}
		for(unsigned dc = c; dc != ret[dr].size(); ++dc){
			ret[dr][dc] = this->row(dr)[dc + 1];
		}
	}

	for(unsigned dr = r; dr != ret.size(); ++dr){
		for(unsigned dc = 0; dc != c; ++dc){
			ret[dr][dc] = this->row(dr + 1)[dc];
		}
		for(unsigned dc = c; dc != ret[dr].size(); ++dc){
			ret[dr][dc] = this->row(dr + 1)[dc + 1];
		}
	}

	return ret;
}

static_assert(sizeof(matrix4<float>) == sizeof(float) * 4 * 4, "size mismatch");
static_assert(sizeof(matrix4<double>) == sizeof(double) * 4 * 4, "size mismatch");

}
