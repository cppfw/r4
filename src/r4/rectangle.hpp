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
	typedef T T_Component;

	//TODO: doxygen
	vector2<T> p; //Left-Bottom corner

	//TODO: doxygen
	vector2<T> d; //dimensions

	//TODO: doxygen
	rectangle()noexcept{}

	//TODO: doxygen
	rectangle(T value)noexcept :
			p(value),
			d(value)
	{}

	//TODO: doxygen
	rectangle(T left, T bottom, T width, T height)noexcept :
			p(left, bottom),
			d(width, height)
	{}

	//TODO: doxygen
	rectangle(vector2<T> leftBottom, vector2<T> dimensions)noexcept :
			p(leftBottom),
			d(dimensions)
	{}

	template <class TT> explicit rectangle(const rectangle<TT>& r) :
			p(r.p),
			d(r.d)
	{}

	//TODO: doxygen
	vector2<T> center()const noexcept{
		return this->p + this->d / 2;
	}

	//TODO: doxygen
	void move_center_to(const vector2<T>& vec)noexcept{
		this->p = vec - this->d / 2;
	}

	//TODO: doxygen
	bool overlaps(const vector2<T>& vec)const noexcept{
		return
				vec.x < this->right() &&
				vec.x >= this->left() &&
				vec.y >= this->bottom() &&
				vec.y < this->top()
			;
	}

	//TODO: doxygen
	// get intersection of two rectangles
	rectangle intersection(const rectangle& rect)const noexcept{
		return rectangle(*this).intersect(rect);
	}

	//TODO: doxygen
	rectangle& intersect(const rectangle& rect)noexcept{
		for(unsigned i = 0; i != 2; ++i){
			T end = std::min(this->p[i] + this->d[i], rect.p[i] + rect.d[i]);
			this->p[i] = std::max(this->p[i], rect.p[i]);
			if(end > this->p[i]){
				this->d[i] = end - this->p[i];
			}else{
				this->d[i] = 0;
			}
		}

		return *this;
	}

	//TODO: doxygen
	vector2<T> extent()const noexcept{
		return this->d / 2;
	}

	//TODO: doxygen
	vector2<T> right_top()const noexcept{
		return this->p + this->d;
	}

	//TODO: doxygen
	T& left()noexcept{
		return this->p.x;
	}

	//TODO: doxygen
	const T& left()const noexcept{
		return this->p.x;
	}

	//TODO: doxygen
	vector2<T> left_top()const noexcept{
		return vector2<T>(this->p.x, this->p.y + this->d.y);
	}

	//TODO: doxygen
	T top()const noexcept{
		return this->p.y + this->d.y;
	}

	//TODO: doxygen
	T right()const noexcept{
		return this->p.x + this->d.x;
	}

	//TODO: doxygen
	vector2<T> right_bottom()const noexcept{
		return vector2<T>(this->p.x + this->d.x, this->p.y);
	}

	//TODO: doxygen
	T& bottom()noexcept{
		return this->p.y;
	}

	//TODO: doxygen
	const T& bottom()const noexcept{
		return this->p.y;
	}

	//TODO: doxygen
	bool operator==(const rectangle& r)const noexcept{
		return this->p == r.p && this->d == r.d;
	}

	/**
	 * @brief Convert to rectangle2 with different type of component.
	 * Convert this rectangle2 to a rectangle2 whose component type is different from T.
	 * Components are converted using constructor of target type passing the source
	 * component as argument of the target type constructor.
     * @return converted vector2.
     */
	template <class TS> rectangle<TS> to()const noexcept{
		return rectangle<TS>(*this);
	}

	friend std::ostream& operator<<(std::ostream& s, const rectangle<T>& rect){
		s << "[" << rect.p << rect.d << "]";
		return s;
	}
};

typedef rectangle<float> rectf;

typedef rectangle<double> rectd;

typedef rectangle<int> recti;

typedef rectangle<unsigned> rectu;

}
