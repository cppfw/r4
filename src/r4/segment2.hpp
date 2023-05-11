/*
The MIT License (MIT)

Copyright (c) 2015-2023 Ivan Gagis <igagis@gmail.com>

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
 * @brief Line segment.
 * Line segment can also be thought of as an axis-aligned box which represents
 * line segment's bounding box.
 */
template <class component_type>
class segment2
{
public:
	/**
	 * @brief Begin point of the segment.
	 */
	vector2<component_type> p1;

	/**
	 * @brief End point of the segment.
	 */
	vector2<component_type> p2;

	/**
	 * @brief Get (x1, y2) point.
	 * @return (x1, y2) point.
	 */
	vector2<component_type> x1_y2() const noexcept
	{
		return {this->p1.x(), this->p2.y()};
	}

	/**
	 * @brief Get (x2, y1) point.
	 * @return (x2, y1) point.
	 */
	vector2<component_type> x2_y1() const noexcept
	{
		return {this->p2.x(), this->p1.y()};
	}

	/**
	 * @brief Get x2 - x1.
	 * @return x2 - x1.
	 */
	component_type dx() const noexcept
	{
		return this->p2.x() - this->p1.x();
	}

	/**
	 * @brief Get y2 - y1.
	 * @return y2 - y1.
	 */
	component_type dy() const noexcept
	{
		return this->p2.y() - this->p1.y();
	}

	/**
	 * @brief Get (dx, dy) vector.
	 * @return (dx, dy) vector.
	 */
	vector2<component_type> dx_dy() const noexcept
	{
		return this->p2 - this->p1;
	}

	/**
	 * @brief Get minimal x coordinate.
	 * @return Minimal x coordinate from the two segment points.
	 */
	component_type min_x() const noexcept
	{
		using std::min;
		return min(this->p1.x(), this->p2.x());
	}

	/**
	 * @brief Get minimal y coordinate.
	 * @return Minimal y coordinate from the two segment points.
	 */
	component_type min_y() const noexcept
	{
		using std::min;
		return min(this->p1.y(), this->p2.y());
	}

	/**
	 * @brief Get maximal x coordinate.
	 * @return Maximal x coordinate from the two segment points.
	 */
	component_type max_x() const noexcept
	{
		using std::max;
		return max(this->p1.x(), this->p2.x());
	}

	/**
	 * @brief Get maximal y coordinate.
	 * @return Maximal y coordinate from the two segment points.
	 */
	component_type max_y() const noexcept
	{
		using std::max;
		return max(this->p1.y(), this->p2.y());
	}

	/**
	 * @brief Get width of the segment's bounding box.
	 * @return dx if it spositive.
	 * @return 0 otherwise.
	 */
	component_type width() const noexcept
	{
		using std::max;
		return max(component_type(0), this->dx());
	}

	/**
	 * @brief Get height of the segment's bounding box.
	 * @return dy if it spositive.
	 * @return 0 otherwise.
	 */
	component_type height() const noexcept
	{
		using std::max;
		return max(component_type(0), this->dy());
	}

	/**
	 * @brief Get dimensions of the segment's bounding box.
	 * @return (width, height) vector.
	 */
	vector2<component_type> dims() const noexcept
	{
		using std::max;
		return {this->width(), this->height()};
	}

	/**
	 * @brief Set this segment so that it's bounding box is empty.
	 * Empty bounding box is when p1 has maximal possible values and p2 has
	 * minimal possible values of the value_type representing components of p1 and p2.
	 * @return reference to this object.
	 */
	segment2& set_empty_bounding_box() noexcept
	{
		using std::numeric_limits;
		using limits = numeric_limits<typename decltype(this->p1)::value_type>;
		this->p1 = decltype(this->p1)(limits::max());
		this->p2 = decltype(this->p2)(limits::min());
		return *this;
	}

	/**
	 * @brief Unite this this segment with another one.
	 * The resulting segment is the one which has minimum p1 values and maximum p2 values of the
	 * two segments.
	 * @param seg - another segment to unite this one with.
	 * @return reference to this object.
	 */
	segment2& unite(const segment2& seg) noexcept
	{
		using std::min;
		using std::max;

		this->p1 = min(this->p1, seg.p1);
		this->p2 = max(this->p2, seg.p2);

		return *this;
	}
};

} // namespace r4
