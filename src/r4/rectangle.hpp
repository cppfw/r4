#pragma once

#include <iostream>

#include <algorithm>

#include "vector2.hpp"

// Under Windows and MSVC compiler there are 'min' and 'max' macros defined for some reason, get rid of them.
#ifdef min
#	undef min
#endif
#ifdef max
#	undef max
#endif

namespace r4{

/**
 * @brief 2d axis-aligned rectangle class.
 */
template <class T> class rectangle{
public:
	/**
	 * @brief Rectangle origin point.
	 * The rectangle origin point coincides with one of the rectangle's corner points.
	 */
	vector2<T> p;

	/**
	 * @brief Dimensions of the rectangle.
	 */
	vector2<T> d;

	/**
	 * @brief constructor.
	 * Default constructor. It does not initialize the rectangle.
	 */
	constexpr rectangle() = default;

	/**
	 * @brief constructor.
	 * Initializes the rectangle to given position and dimensions.
	 * @param x - X coordinate of the rectangle's origin point.
	 * @param y - Y coordinate of the rectangle's origin point.
	 * @param width - width of the rectangle.
	 * @param height - height of the rectangle.
	 */
	constexpr rectangle(T x, T y, T width, T height)noexcept :
			p(x, y),
			d(width, height)
	{}

	/**
	 * @brief constructor.
	 * Initializes the rectangle to given position and dimensions.
	 * @param pos - the rectangle's origin point.
	 * @param dims - the rectangle's dimensions.
	 */
	constexpr rectangle(const vector2<T>& pos, const vector2<T>& dims)noexcept :
			p(pos),
			d(dims)
	{}

	/**
	 * @brief Test rectangles for equality.
	 * @param r - rectangle to test this rectangle with.
	 * @return true if two rectangles are equal, i.e. their origin points and dimensions are equal.
	 * @return false otherwise.
	 */
	bool operator==(const rectangle& r)const noexcept{
		return this->p == r.p && this->d == r.d;
	}

	/**
	 * @brief Get center point of the rectangle.
	 * @return vector2 representing the center point of the rectangle.
	 */
	vector2<T> center()const noexcept{
		return this->p + this->d / 2;
	}

	/**
	 * @brief Move rectangle.
	 * Move the rectangle so that its center point coincides with the given point.
	 * @param new_center - new center point of the rectangle.
	 */
	void move_center_to(const vector2<T>& new_center)noexcept{
		this->p = new_center - this->d / 2;
	}

	/**
	 * @brief Test if the rectangle overlaps given point.
	 * @param point - point to test for overlapping.
	 * @return true if the rectangle overlaps the given point.
	 * @return false otherwise.
	 */
	bool overlaps(const vector2<T>& point)const noexcept{
		return
				point.x() >= this->p.x() &&
				point.y() >= this->p.y() &&
				point.x() < this->x2() &&
				point.y() < this->y2()
			;
	}

	/**
	 * @brief Intersect this rectangle with given rectangle.
	 * The intersection result is stored in this rectangle.
	 * @param rect - rectangle to intersect this rectnagle with.
	 * @return referenct to this rectangle.
	 */
	rectangle& intersect(const rectangle& rect)noexcept{
		using std::min;
		using std::max;

		auto end = min(this->x2_y2(), rect.x2_y2());
		this->p = max(this->p, rect.p);
		this->d = end - min(this->p, end); // d components are clamped from bottom by 0

		return *this;
	}

	/**
	 * @brief Unite this rectangle with given rectangle.
	 * @param rect - rectangle to unite this rectangle with.
	 * @return reference to this rectangle.
	 */
	rectangle& unite(const rectangle& rect)noexcept{
		using std::min;
		using std::max;
		auto min_xy = min(this->p, rect.p);
		auto max_xy = max(this->x2_y2(), rect.x2_y2());

		this->p = min_xy;
		this->d = max_xy - min_xy;
		return *this;
	}

	/**
	 * @brief Get point of the rectangle with maxium X and Y coordinates.
	 * @return point of the rectangle with maximal X anf Y coordinates.
	 */
	vector2<T> x2_y2()const noexcept{
		return this->p + this->d;
	}

	/**
	 * @brief Get point of the rectangle with minimal X and maximal Y coordinates.
	 * @return point of the rectangle with minimal X and maximal Y coordinates.
	 */
	vector2<T> x1_y2()const noexcept{
		return vector2<T>(this->p.x(), this->y2());
	}

	/**
	 * @brief Get maximal Y coordinate.
	 * @return maximal Y coordinate of the rectangle's point.
	 */
	T y2()const noexcept{
		return this->p.y() + this->d.y();
	}

	/**
	 * @brief Get x+width coordinate.
	 * @return x+width coordinate of the rectangle.
	 */
	T x2()const noexcept{
		return this->p.x() + this->d.x();
	}

	/**
	 * @brief Get point of the rectangle with maximal X and minimal Y coordinates.
	 * @return point of the rectangle with maximal X and minimal Y coordinates.
	 */
	vector2<T> x2_y1()const noexcept{
		return vector2<T>(this->x2(), this->p.y());
	}

	/**
	 * @brief Convert to rectangle2 with different type of component.
	 * Convert this rectangle2 to a rectangle2 whose component type is different from T.
	 * Components are converted using constructor of target type passing the source
	 * component as argument of the target type constructor.
     * @return converted vector2.
     */
	template <class TS> rectangle<TS> to()const noexcept{
		return rectangle<TS>{
				this->p.template to<TS>(),
				this->d.template to<TS>()
			};
	}

	friend std::ostream& operator<<(std::ostream& s, const rectangle<T>& rect){
		s << "[" << rect.p << rect.d << "]";
		return s;
	}
};

}
