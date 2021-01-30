#include <utki/debug.hpp>

#include "../../src/r4/vector.hpp"

int main(int argc, char** argv){
	// test constructor(x, y)
	{
		r4::vector2<int> v{2, 3};

		ASSERT_ALWAYS(v[0] == 2)
		ASSERT_ALWAYS(v[1] == 3)
	}

	// test constructor(xy)
	{
		r4::vector2<int> v(3);

		ASSERT_ALWAYS(v[0] == 3)
		ASSERT_ALWAYS(v[1] == 3)
	}

	// test constructor(vector3)
	{
		r4::vector3<int> v3{3, 4, 5};

		r4::vector2<int> v2{v3};

		ASSERT_ALWAYS(v2[0] == 3)
		ASSERT_ALWAYS(v2[1] == 4)
	}

	// test to()
	{
		r4::vector2<float> vf{4.4f, 5.5f};

		auto vi = vf.to<int>();

		ASSERT_ALWAYS(vi[0] == 4)
		ASSERT_ALWAYS(vi[1] == 5)
	}

	// test operator=(vector3)
	{
		r4::vector3<int> v3{3, 4, 5};

		r4::vector2<int> v2(0);

		v2 = v3;

		ASSERT_ALWAYS(v2[0] == 3)
		ASSERT_ALWAYS(v2[1] == 4)
	}

	// test operator+(vector3)
	{
		r4::vector3<int> v3{3, 4, 5};

		r4::vector2<int> v2{1, 2};

		auto r = v2 + v3;

		ASSERT_ALWAYS(r[0] == 4)
		ASSERT_ALWAYS(r[1] == 6)
	}

	// test operator+=(vector2)
	{
		r4::vector2<int> v{1, 2};

		v += r4::vector2<int>{3, 4};

		ASSERT_ALWAYS(v[0] == 4)
		ASSERT_ALWAYS(v[1] == 6)
	}

	// test operator+(vector2)
	{
		r4::vector2<int> v2_0{3, 4};

		r4::vector2<int> v2{1, 2};

		auto r = v2 + v2_0;

		ASSERT_ALWAYS(r[0] == 4)
		ASSERT_ALWAYS(r[1] == 6)
	}

	// test operator+(n)
	{
		r4::vector2<int> v2{3, 4};

		auto r = v2 + 5;

		ASSERT_ALWAYS(r[0] == 8)
		ASSERT_ALWAYS(r[1] == 9)
	}

	// test operator-=(vector2)
	{
		r4::vector2<int> v2{1, 2};

		v2 -= r4::vector2<int>{3, 5};

		ASSERT_ALWAYS(v2[0] == -2)
		ASSERT_ALWAYS(v2[1] == -3)
	}

	// test operator-(vector2)
	{
		r4::vector2<int> v2_0{3, 5};

		r4::vector2<int> v2{1, 2};

		auto r = v2 - v2_0;

		ASSERT_ALWAYS(r[0] == -2)
		ASSERT_ALWAYS(r[1] == -3)
	}

	// test operator-(vector3)
	{
		r4::vector3<int> v3{3, 5, 6};

		r4::vector2<int> v2{1, 2};

		auto r = v2 - v3;

		ASSERT_ALWAYS(r[0] == -2)
		ASSERT_ALWAYS(r[1] == -3)
	}

	// test operator-()
	{
		auto r = -r4::vector2<int>{1, 2};

		ASSERT_ALWAYS(r[0] == -1)
		ASSERT_ALWAYS(r[1] == -2)
	}

	// test operator*=(n)
	{
		r4::vector2<int> v2{2, 3};

		v2 *= 3;

		ASSERT_ALWAYS(v2[0] == 6)
		ASSERT_ALWAYS(v2[1] == 9)
	}

	// test operator*(n)
	{
		r4::vector2<int> v2{2, 3};

		auto r = v2 * 3;

		ASSERT_ALWAYS(r[0] == 6)
		ASSERT_ALWAYS(r[1] == 9)
	}

	// test operator*(n, vector2)
	{
		r4::vector2<int> v2{2, 3};

		auto r = 3 * v2;

		ASSERT_ALWAYS(r[0] == 6)
		ASSERT_ALWAYS(r[1] == 9)
	}

	// test min(vector2, vector2)
	{
		r4::vector2<int> a{2, 3};
		r4::vector2<int> b{5, 1};

		auto r = min(a, b);

		ASSERT_ALWAYS(r[0] == 2)
		ASSERT_ALWAYS(r[1] == 1)
	}

	// test max(vector2, vector2)
	{
		r4::vector2<int> a{2, 3};
		r4::vector2<int> b{5, 1};

		auto r = max(a, b);

		ASSERT_ALWAYS(r[0] == 5)
		ASSERT_ALWAYS(r[1] == 3)
	}

	// test operator/=(n)
	{
		r4::vector2<int> v2{6, 9};

		v2 /= 3;

		ASSERT_ALWAYS(v2[0] == 2)
		ASSERT_ALWAYS(v2[1] == 3)
	}

	// test operator/(n)
	{
		r4::vector2<int> v2{6, 9};

		auto r = v2 / 3;

		ASSERT_ALWAYS(r[0] == 2)
		ASSERT_ALWAYS(r[1] == 3)
	}

	// test operator*(vector2)
	{
		r4::vector2<int> a{3, 4};
		r4::vector2<int> b{5, 6};

		auto r = a * b;

		ASSERT_ALWAYS(r == 3 * 5 + 4 * 6)
	}

	// test comp_mul(vector2)
	{
		r4::vector2<int> a{3, 4};
		r4::vector2<int> b{5, 6};

		auto r = a.comp_mul(b);

		ASSERT_ALWAYS(r[0] == 15)
		ASSERT_ALWAYS(r[1] == 24)
	}

	// test comp_multiply(vector2)
	{
		r4::vector2<int> a{3, 4};

		a.comp_multiply(r4::vector2<int>{5, 6});

		ASSERT_ALWAYS(a[0] == 15)
		ASSERT_ALWAYS(a[1] == 24)
	}

	// test comp_div(vector2)
	{
		r4::vector2<int> a{6, 15};
		r4::vector2<int> b{3, 5};

		auto r = a.comp_div(b);

		ASSERT_ALWAYS(r[0] == 2)
		ASSERT_ALWAYS(r[1] == 3)
	}

	// test comp_divide(vector2)
	{
		r4::vector2<int> a{6, 15};

		a.comp_divide(r4::vector2<int>{3, 5});

		ASSERT_ALWAYS(a[0] == 2)
		ASSERT_ALWAYS(a[1] == 3)
	}

	// test is_zero()
	{
		{
			r4::vector2<int> a{0, 0};
			ASSERT_ALWAYS(a.is_zero())
		}
		{
			r4::vector2<int> a{0, 3};
			ASSERT_ALWAYS(!a.is_zero())
		}
		{
			r4::vector2<int> a{6, 0};
			ASSERT_ALWAYS(!a.is_zero())
		}
		{
			r4::vector2<int> a{4, 3};
			ASSERT_ALWAYS(!a.is_zero())
		}
	}

	// test is_positive_or_zero()
	{
		{
			r4::vector2<int> a{0, 0};
			ASSERT_ALWAYS(a.is_positive_or_zero())
		}
		{
			r4::vector2<int> a{0, 3};
			ASSERT_ALWAYS(a.is_positive_or_zero())
		}
		{
			r4::vector2<int> a{6, 0};
			ASSERT_ALWAYS(a.is_positive_or_zero())
		}
		{
			r4::vector2<int> a{4, 3};
			ASSERT_ALWAYS(a.is_positive_or_zero())
		}
		{
			r4::vector2<int> a{0, -3};
			ASSERT_ALWAYS(!a.is_positive_or_zero())
		}
		{
			r4::vector2<int> a{-6, 0};
			ASSERT_ALWAYS(!a.is_positive_or_zero())
		}
		{
			r4::vector2<int> a{-4, -3};
			ASSERT_ALWAYS(!a.is_positive_or_zero())
		}
	}

	// test is_positive()
	{
		{
			r4::vector2<int> a{0, 0};
			ASSERT_ALWAYS(!a.is_positive())
		}
		{
			r4::vector2<int> a{0, 3};
			ASSERT_ALWAYS(!a.is_positive())
		}
		{
			r4::vector2<int> a{6, 0};
			ASSERT_ALWAYS(!a.is_positive())
		}
		{
			r4::vector2<int> a{4, 3};
			ASSERT_ALWAYS(a.is_positive())
		}
		{
			r4::vector2<int> a{0, -3};
			ASSERT_ALWAYS(!a.is_positive())
		}
		{
			r4::vector2<int> a{-6, 0};
			ASSERT_ALWAYS(!a.is_positive())
		}
		{
			r4::vector2<int> a{-4, -3};
			ASSERT_ALWAYS(!a.is_positive())
		}
	}

	// test is_negative()
	{
		{
			r4::vector2<int> a{0, 0};
			ASSERT_ALWAYS(!a.is_negative())
		}
		{
			r4::vector2<int> a{0, 3};
			ASSERT_ALWAYS(!a.is_negative())
		}
		{
			r4::vector2<int> a{6, 0};
			ASSERT_ALWAYS(!a.is_negative())
		}
		{
			r4::vector2<int> a{4, 3};
			ASSERT_ALWAYS(!a.is_negative())
		}
		{
			r4::vector2<int> a{0, -3};
			ASSERT_ALWAYS(!a.is_negative())
		}
		{
			r4::vector2<int> a{-6, 0};
			ASSERT_ALWAYS(!a.is_negative())
		}
		{
			r4::vector2<int> a{-4, -3};
			ASSERT_ALWAYS(a.is_negative())
		}
	}

    // test negate
    {
        r4::vector2<int> v{13, -14};
        ASSERT_ALWAYS(!v.is_negative())

        v.negate();

        ASSERT_ALWAYS(!v.is_negative())
        ASSERT_ALWAYS(v.x() == -13)
        ASSERT_ALWAYS(v.y() == 14)
    }

	// test abs()
	{
		r4::vector2<int> v{-13, -14};

		using std::abs;

		ASSERT_ALWAYS(!v.is_positive_or_zero())
		ASSERT_ALWAYS(abs(v).is_positive_or_zero())
	}

	// test norm_pow2()
	{
		r4::vector2<int> v{3, 4};

		ASSERT_ALWAYS(v.norm_pow2() == 25)
	}

	// test norm()
	{
		r4::vector2<float> v{3.0f, 4.0f};

		ASSERT_ALWAYS(v.norm() == 5.0f)
	}

	// test normalize()
	{
		r4::vector2<float> v{3.0f, 4.0f};

		v.normalize();

		ASSERT_INFO_ALWAYS(v[0] == 0.6f, "v = " << v)
		ASSERT_INFO_ALWAYS(v[1] == 0.8f, "v = " << v)
	}

	// test normed()
	{
		r4::vector2<float> v{3.0f, 4.0f};

		auto r = v.normed();

		ASSERT_INFO_ALWAYS(r[0] == 0.6f, "r = " << r)
		ASSERT_INFO_ALWAYS(r[1] == 0.8f, "r = " << r)
	}

	// test set(n)
	{
		r4::vector2<int> v{3, 4};

		v.set(5);

		ASSERT_ALWAYS(v[0] == 5)
		ASSERT_ALWAYS(v[1] == v[0])
	}

	// test set(x, y)
	{
		r4::vector2<int> v{3, 4};

		v.set(5, 6);

		ASSERT_ALWAYS(v[0] == 5)
		ASSERT_ALWAYS(v[1] == 6)
	}

	// test rotate(a)
	{
		r4::vector2<float> v{41.0f, 30.0f};

		v.rotate(utki::pi<float>() / 6);

		auto r = v.to<int>();

		ASSERT_INFO_ALWAYS(r[0] == 20, "r = " << r)
		ASSERT_INFO_ALWAYS(r[1] == 46, "r = " << r)
	}

	// test rotated(a)
	{
		auto v = r4::vector2<float>{41.0f, 30.0f}.rot(utki::pi<float>() / 6);

		auto r = v.to<int>();

		ASSERT_INFO_ALWAYS(r[0] == 20, "r = " << r)
		ASSERT_INFO_ALWAYS(r[1] == 46, "r = " << r)
	}

	// test round(vector2)
	{
		using std::round;
		auto v = round(r4::vector2<float>{4.8f, 3.3f});

		auto r = v.to<int>();

		ASSERT_ALWAYS(r[0] == 5)
		ASSERT_ALWAYS(r[1] == 3)
	}

	// test ceil(vector2)
	{
		using std::ceil;
		auto v = ceil(r4::vector2<float>{4.8f, 3.3f});

		auto r = v.to<int>();

		ASSERT_ALWAYS(r[0] == 5)
		ASSERT_ALWAYS(r[1] == 4)
	}

	// test floor(vector2)
	{
		using std::floor;
		auto v = floor(r4::vector2<float>{4.8f, 3.3f});

		auto r = v.to<int>();

		ASSERT_ALWAYS(r[0] == 4)
		ASSERT_ALWAYS(r[1] == 3)
	}

	// test that vector::vector(A... a) constructor does is not used to convert shared_ptr to vector.
	{
		struct base{};
		struct derived : base{};

		struct ts{
			void func(const r4::vector2<float>& v){}
			void func(std::shared_ptr<const base> p){}
		} s;

		auto p = std::make_shared<const derived>();

		s.func(p);
	}

    return 0;
}
