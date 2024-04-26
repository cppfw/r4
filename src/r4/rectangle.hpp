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

#include <algorithm>
#include <iostream>

#include "vector.hpp"

// Under Windows and MSVC compiler there are 'min' and 'max' macros defined for some reason, get rid of them.
#ifdef min
#	undef min
#endif
#ifdef max
#	undef max
#endif

namespace r4 {

/**
 * @brief 2d axis-aligned rectangle class.
 */
template <class component_type>
class rectangle
{
public:
	/**
	 * @brief Rectangle origin point.
	 * The rectangle origin point coincides with one of the rectangle's corner points.
	 */
	vector2<component_type> p;

	/**
	 * @brief Dimensions of the rectangle.
	 */
	vector2<component_type> d;

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
	constexpr rectangle(component_type x, component_type y, component_type width, component_type height) noexcept :
		p(x, y),
		d(width, height)
	{}

	/**
	 * @brief constructor.
	 * Initializes the rectangle to given position and dimensions.
	 * @param pos - the rectangle's origin point.
	 * @param dims - the rectangle's dimensions.
	 */
	constexpr rectangle(const vector2<component_type>& pos, const vector2<component_type>& dims) noexcept :
		p(pos),
		d(dims)
	{}

	/**
	 * @brief Test rectangles for equality.
	 * @param r - rectangle to test this rectangle with.
	 * @return true if two rectangles are equal, i.e. their origin points and dimensions are equal.
	 * @return false otherwise.
	 */
	bool operator==(const rectangle& r) const noexcept
	{
		return this->p == r.p && this->d == r.d;
	}

	/**
	 * @brief Get center point of the rectangle.
	 * @return vector2 representing the center point of the rectangle.
	 */
	vector2<component_type> center() const noexcept
	{
		return this->p + this->d / 2;
	}

	/**
	 * @brief Move rectangle.
	 * Move the rectangle so that its center point coincides with the given point.
	 * @param new_center - new center point of the rectangle.
	 */
	void move_center_to(const vector2<component_type>& new_center) noexcept
	{
		this->p = new_center - this->d / 2;
	}

	/**
	 * @brief Test if the rectangle overlaps given point.
	 * @param point - point to test for overlapping.
	 * @return true if the rectangle overlaps the given point.
	 * @return false otherwise.
	 */
	bool overlaps(const vector2<component_type>& point) const noexcept
	{
		return point.x() >= this->p.x() && point.y() >= this->p.y() && point.x() < this->x2() && point.y() < this->y2();
	}

	/**
	 * @brief Test if the rectangle contains given rectangle.
	 *
	 * @param rect - rectangle to test for containment.
	 * @return true if the rectangle fully contains the given rectangle.
	 * @return false otherwise.
	 */
	bool contains(const rectangle& rect) const noexcept
	{
		auto this_x2y2 = this->x2_y2();
		auto rect_x2y2 = rect.x2_y2();

		return //
			this->p.x() <= rect.p.x() && //
			this->p.y() <= rect.p.y() && //
			this_x2y2.x() >= rect_x2y2.x() && //
			this_x2y2.y() >= rect_x2y2.y();
	}

	/**
	 * @brief Intersect this rectangle with given rectangle.
	 * The intersection result is stored in this rectangle.
	 * @param rect - rectangle to intersect this rectnagle with.
	 * @return referenct to this rectangle.
	 */
	rectangle& intersect(const rectangle& rect) noexcept
	{
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
	rectangle& unite(const rectangle& rect) noexcept
	{
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
	vector2<component_type> x2_y2() const noexcept
	{
		return this->p + this->d;
	}

	/**
	 * @brief Get point of the rectangle with minimal X and maximal Y coordinates.
	 * @return point of the rectangle with minimal X and maximal Y coordinates.
	 */
	vector2<component_type> x1_y2() const noexcept
	{
		return vector2<component_type>(this->p.x(), this->y2());
	}

	/**
	 * @brief Get maximal Y coordinate.
	 * @return maximal Y coordinate of the rectangle's point.
	 */
	component_type y2() const noexcept
	{
		return this->p.y() + this->d.y();
	}

	/**
	 * @brief Get x+width coordinate.
	 * @return x+width coordinate of the rectangle.
	 */
	component_type x2() const noexcept
	{
		return this->p.x() + this->d.x();
	}

	/**
	 * @brief Get point of the rectangle with maximal X and minimal Y coordinates.
	 * @return point of the rectangle with maximal X and minimal Y coordinates.
	 */
	vector2<component_type> x2_y1() const noexcept
	{
		return vector2<component_type>(this->x2(), this->p.y());
	}

	/**
	 * @brief Convert to rectangle2 with different type of component.
	 * Convert this rectangle2 to a rectangle2 whose component type is different from component_type.
	 * Components are converted using constructor of target type passing the source
	 * component as argument of the target type constructor.
	 * @return converted vector2.
	 */
	template <class another_component_type>
	rectangle<another_component_type> to() const noexcept
	{
		return rectangle<another_component_type>{
			this->p.template to<another_component_type>(),
			this->d.template to<another_component_type>()
		};
	}

	friend std::ostream& operator<<(std::ostream& s, const rectangle<component_type>& rect)
	{
		s << "(" << rect.p << ")(" << rect.d << ")";
		return s;
	}
};

} // namespace r4
