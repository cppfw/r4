#include <utki/debug.hpp>

#include "../../src/r4/vector.hpp"
#include "../../src/r4/vector.hpp"

void test(){
	// test constructor(x, y, z)
	{
		r4::vector3<int> v{3, 4, 5};

		ASSERT_ALWAYS(v[0] == 3)
		ASSERT_ALWAYS(v[1] == 4)
		ASSERT_ALWAYS(v[2] == 5)
	}

	// test constructor(n)
	{
		r4::vector3<int> v(4);

		ASSERT_ALWAYS(v[0] == 4)
		ASSERT_ALWAYS(v[1] == v[0])
		ASSERT_ALWAYS(v[2] == v[1])
	}

	// test constructor(x, y)
	{
		r4::vector3<int> a{3, 5};

		ASSERT_ALWAYS(a[0] == 3)
		ASSERT_INFO_ALWAYS(a[1] == 5, "a = " << a)
	}

	// test constructor(vector2, z)
	{
		r4::vector2<int> v2{3, 4};

		r4::vector3<int> v3{v2, 5};

		ASSERT_ALWAYS(v3[0] == 3)
		ASSERT_ALWAYS(v3[1] == 4)
		ASSERT_ALWAYS(v3[2] == 5)
	}

	// test constructor(vector4)
	{
		r4::vector4<int> v4{3, 4, 5, 6};

		r4::vector3<int> v3{v4};

		ASSERT_ALWAYS(v3[0] == 3)
		ASSERT_ALWAYS(v3[1] == 4)
		ASSERT_ALWAYS(v3[2] == 5)
	}

    // test to()
    {
        r4::vector3<float> vf(1.1f, 2.2f, 3.3f);
        
        auto vi = vf.to<int>();

        ASSERT_INFO_ALWAYS(vi[0] == 1, "vi[0] = " << vi[0])
        ASSERT_INFO_ALWAYS(vi[1] == 2, "vi[1] = " << vi[1])
		ASSERT_INFO_ALWAYS(vi[2] == 3, "vi[2] = " << vi[2])
    }

	// test operator=(vector2)
	{
		r4::vector2<int> a{3, 4};

		r4::vector3<int> b{5, 6, 7};

		b = a;

		ASSERT_ALWAYS(b[0] == 3)
		ASSERT_ALWAYS(b[1] == 4)
		ASSERT_ALWAYS(b[2] == 0)
	}

	// test operator=(n)
	{
		r4::vector3<int> b{5, 6, 7};

		b = 3;

		ASSERT_ALWAYS(b[0] == 3)
		ASSERT_ALWAYS(b[1] == b[0])
		ASSERT_ALWAYS(b[2] == b[1])
	}

	// test set(n)
	{
		r4::vector3<int> b{5, 6, 7};

		b.set(3);

		ASSERT_ALWAYS(b[0] == 3)
		ASSERT_ALWAYS(b[1] == b[0])
		ASSERT_ALWAYS(b[2] == b[1])
	}

	// test set(x, y, z)
	{
		r4::vector3<int> b{5, 6, 7};

		b.set(3, 4, 5);

		ASSERT_ALWAYS(b[0] == 3)
		ASSERT_ALWAYS(b[1] == 4)
		ASSERT_ALWAYS(b[2] == 5)
	}

	// test operator+=(vector2)
	{
		r4::vector2<int> a{3, 4};

		r4::vector3<int> b{5, 6, 7};

		b += a;

		ASSERT_ALWAYS(b[0] == 8)
		ASSERT_ALWAYS(b[1] == 10)
		ASSERT_ALWAYS(b[2] == 7)
	}

	// test operator+=(vector3)
	{
		r4::vector3<int> b{5, 6, 7};

		b += r4::vector3<int>{3, 4, 5};

		ASSERT_ALWAYS(b[0] == 8)
		ASSERT_ALWAYS(b[1] == 10)
		ASSERT_ALWAYS(b[2] == 12)
	}

	// test operator+(vector3)
	{
		r4::vector3<int> a{3, 4, 5};

		r4::vector3<int> b{5, 6, 7};

		auto r = a + b;

		ASSERT_ALWAYS(r[0] == 8)
		ASSERT_ALWAYS(r[1] == 10)
		ASSERT_ALWAYS(r[2] == 12)
	}

	// test operator-=(vector3)
	{
		r4::vector3<int> b{5, 6, 7};

		b -= r4::vector3<int>{4, 3, 2};

		ASSERT_ALWAYS(b[0] == 1)
		ASSERT_ALWAYS(b[1] == 3)
		ASSERT_ALWAYS(b[2] == 5)
	}

	// test operator-(vector3)
	{
		r4::vector3<int> a{3, 4, 5};

		r4::vector3<int> b{5, 7, 9};

		auto r = a - b;

		ASSERT_ALWAYS(r[0] == -2)
		ASSERT_ALWAYS(r[1] == -3)
		ASSERT_ALWAYS(r[2] == -4)
	}

	// test operator-()
	{
		r4::vector3<int> v{3, 4, 5};

		auto r = -v;

		ASSERT_ALWAYS(r[0] == -3)
		ASSERT_ALWAYS(r[1] == -4)
		ASSERT_ALWAYS(r[2] == -5)
	}

	// test operator*=(n)
	{
		r4::vector3<int> v{3, 4, 5};

		v *= 2;

		ASSERT_ALWAYS(v[0] == 6)
		ASSERT_ALWAYS(v[1] == 8)
		ASSERT_ALWAYS(v[2] == 10)
	}

	// test operator*(n)
	{
		r4::vector3<int> v{3, 4, 5};

		auto r = v * 2;

		ASSERT_ALWAYS(r[0] == 6)
		ASSERT_ALWAYS(r[1] == 8)
		ASSERT_ALWAYS(r[2] == 10)
	}

	// test operator(m, vector3)
	{
		r4::vector3<int> v{3, 4, 5};

		auto r = 2 * v;

		ASSERT_ALWAYS(r[0] == 6)
		ASSERT_ALWAYS(r[1] == 8)
		ASSERT_ALWAYS(r[2] == 10)
	}

	// test operator/=(n)
	{
		r4::vector3<int> v{4, 8, 12};

		v /= 2;

		ASSERT_ALWAYS(v[0] == 2)
		ASSERT_ALWAYS(v[1] == 4)
		ASSERT_ALWAYS(v[2] == 6)
	}

	// test operator/(n)
	{
		r4::vector3<int> v{4, 8, 12};

		auto r = v / 2;

		ASSERT_ALWAYS(r[0] == 2)
		ASSERT_ALWAYS(r[1] == 4)
		ASSERT_ALWAYS(r[2] == 6)
	}

	// test operator*(vector3)
	{
		r4::vector3<int> a{3, 4, 5};
		r4::vector3<int> b{6, 7, 8};

		auto r = a * b;

		ASSERT_ALWAYS(r == 3 * 6 + 4 * 7 + 5 * 8)
	}

	// test comp_mul(vector3)
	{
		r4::vector3<int> a{3, 4, 5};
		r4::vector3<int> b{6, 7, 8};

		auto r = a.comp_mul(b);

		ASSERT_ALWAYS(r[0] == 3 * 6)
		ASSERT_ALWAYS(r[1] == 4 * 7)
		ASSERT_ALWAYS(r[2] == 5 * 8)
	}

	// test comp_multiply(vector3)
	{
		r4::vector3<int> a{3, 4, 5};
		r4::vector3<int> b{6, 7, 8};

		a.comp_multiply(b);

		ASSERT_ALWAYS(a[0] == 3 * 6)
		ASSERT_ALWAYS(a[1] == 4 * 7)
		ASSERT_ALWAYS(a[2] == 5 * 8)
	}

	// test comp_div(vector3)
	{
		r4::vector3<int> a{6, 15, 24};
		r4::vector3<int> b{3, 5, 6};

		auto r = a.comp_div(b);

		ASSERT_ALWAYS(r[0] == 2)
		ASSERT_ALWAYS(r[1] == 3)
		ASSERT_ALWAYS(r[2] == 4)
	}

	// test comp_divide(vector3)
	{
		r4::vector3<int> a{6, 15, 24};

		a.comp_divide(r4::vector3<int>{3, 5, 6});

		ASSERT_ALWAYS(a[0] == 2)
		ASSERT_ALWAYS(a[1] == 3)
		ASSERT_ALWAYS(a[2] == 4)
	}

	// test operator%(vector3)
	{
		r4::vector3<int> a{3, 4, 5};
		r4::vector3<int> b{6, 7, 8};

		auto r = a % b;

		ASSERT_INFO_ALWAYS(r[0] == -3, "r = " << r)
		ASSERT_INFO_ALWAYS(r[1] == 6, "r = " << r)
		ASSERT_INFO_ALWAYS(r[2] == -3, "r = " << r)
	}

	// test is_zero()
	{
		{
			r4::vector3<int> a{0, 0, 0};
			ASSERT_ALWAYS(a.is_zero())
		}
		{
			r4::vector3<int> a{3, 0, 0};
			ASSERT_ALWAYS(!a.is_zero())
		}
		{
			r4::vector3<int> a{0, -4, 0};
			ASSERT_ALWAYS(!a.is_zero())
		}
		{
			r4::vector3<int> a{0, 0, 7};
			ASSERT_ALWAYS(!a.is_zero())
		}
		{
			r4::vector3<int> a{3, -4, 1};
			ASSERT_ALWAYS(!a.is_zero())
		}
	}

	// test negate()
	{
		r4::vector3<int> a{3, -4, 7};

		a.negate();

		ASSERT_ALWAYS(a[0] == -3)
		ASSERT_ALWAYS(a[1] == 4)
		ASSERT_ALWAYS(a[2] == -7)
	}

	// test norm_pow2()
	{
		r4::vector3<int> v{3, 4, 5};

		auto r = v.norm_pow2();

		ASSERT_ALWAYS(r == 3 * 3 + 4 * 4 + 5 * 5)
	}

	// test norm()
	{
		r4::vector3<float> v{2, 3, 4};

		auto r = v.norm() * 1000.0f;

		ASSERT_INFO_ALWAYS(int(r) == 5385, "r = " << r)
	}

	// test normalize()
	{
		r4::vector3<float> v{2, 3, 4};

		v.normalize();

		v *= 1000.0f;

		auto r = v.to<int>();

		ASSERT_INFO_ALWAYS(r[0] == 371, "r = " << r)
		ASSERT_INFO_ALWAYS(r[1] == 557, "r = " << r)
		ASSERT_INFO_ALWAYS(r[2] == 742, "r = " << r)
	}

	// test project(vector3)
	{
		r4::vector3<float> a{2, 3, 4};
		r4::vector3<float> b{5, 6, 7};

		a.project(b);

		a *= 1000.0f;

		auto r = a.to<int>();

		ASSERT_INFO_ALWAYS(r[0] == 2545, "r = " << r)
		ASSERT_INFO_ALWAYS(r[1] == 3054, "r = " << r)
		ASSERT_INFO_ALWAYS(r[2] == 3563, "r = " << r)
	}

	// test rotate(quaternion)
	{
		r4::vector3<float> a{2, 3, 4};

		a.rotate(r4::quaternion<float>{r4::vector3<float>{1, 2, 3}}) *= 1000.0f;

		auto r = a.to<int>();

		ASSERT_INFO_ALWAYS(r[0] == 1107, "r = " << r)
		ASSERT_INFO_ALWAYS(r[1] == 2437, "r = " << r)
		ASSERT_INFO_ALWAYS(r[2] == 4672, "r = " << r)
	}

	// test min(vector3, vector3)
	{
		r4::vector3<int> a{2, 3, 4};
		r4::vector3<int> b{5, 1, -5};

		auto r = min(a, b);

		ASSERT_ALWAYS(r[0] == 2)
		ASSERT_ALWAYS(r[1] == 1)
		ASSERT_ALWAYS(r[2] == -5)
	}

	// test max(vector3, vector3)
	{
		r4::vector3<int> a{2, 3, -4};
		r4::vector3<int> b{5, 1, -5};

		auto r = max(a, b);

		ASSERT_ALWAYS(r[0] == 5)
		ASSERT_ALWAYS(r[1] == 3)
		ASSERT_ALWAYS(r[2] == -4)
	}
}
