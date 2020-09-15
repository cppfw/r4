#include <utki/debug.hpp>

#include "../../src/r4/vector4.hpp"

int main(int argc, char** argv){

	// test constructor(x, y, z, w)
	{
		r4::vector4<int> v{3, 4, 5, 6};

		ASSERT_ALWAYS(v[0] == 3)
		ASSERT_ALWAYS(v[1] == 4)
		ASSERT_ALWAYS(v[2] == 5)
		ASSERT_ALWAYS(v[3] == 6)
	}

	// test constructor(n)
	{
		r4::vector4<int> v{3};

		ASSERT_ALWAYS(v[0] == 3)
		ASSERT_ALWAYS(v[1] == v[0])
		ASSERT_ALWAYS(v[2] == v[1])
		ASSERT_ALWAYS(v[3] == v[2])
	}

	// test constructor(n, w)
	{
		r4::vector4<int> v{3, 5};

		ASSERT_ALWAYS(v[0] == 3)
		ASSERT_ALWAYS(v[1] == v[0])
		ASSERT_ALWAYS(v[2] == v[1])
		ASSERT_ALWAYS(v[3] == 5)
	}

	// test constructor(vector2, z, w)
	{
		r4::vector2<int> v2{3, 4};
		r4::vector4<int> v{v2, 5, 6};

		ASSERT_ALWAYS(v[0] == 3)
		ASSERT_ALWAYS(v[1] == 4)
		ASSERT_ALWAYS(v[2] == 5)
		ASSERT_ALWAYS(v[3] == 6)
	}

	// test constructor(vector3, w)
	{
		r4::vector3<int> v3{3, 4, 5};
		r4::vector4<int> v{v3, 6};

		ASSERT_ALWAYS(v[0] == 3)
		ASSERT_ALWAYS(v[1] == 4)
		ASSERT_ALWAYS(v[2] == 5)
		ASSERT_ALWAYS(v[3] == 6)
	}

	// test to()
	{
		r4::vector4<float> vf(1.1f, 2.2f, 3.3f, 4.4f);
        
        auto vi = vf.to<int>();

        ASSERT_INFO_ALWAYS(vi[0] == 1, "vi[0] = " << vi[0])
        ASSERT_INFO_ALWAYS(vi[1] == 2, "vi[1] = " << vi[1])
		ASSERT_INFO_ALWAYS(vi[2] == 3, "vi[2] = " << vi[2])
		ASSERT_INFO_ALWAYS(vi[3] == 4, "vi[3] = " << vi[3])
	}

	// test operator=(vector3)
	{
		r4::vector4<int> v4{3, 4, 5, 6};
		r4::vector3<int> v3{7, 8, 9};

		v4 = v3;

		ASSERT_INFO_ALWAYS(v4[0] == 7, "v4[0] = " << v4[0])
        ASSERT_INFO_ALWAYS(v4[1] == 8, "v4[1] = " << v4[1])
		ASSERT_INFO_ALWAYS(v4[2] == 9, "v4[2] = " << v4[2])
		ASSERT_INFO_ALWAYS(v4[3] == 1, "v4[3] = " << v4[3])
	}

	// test operator=(vector2)
	{
		r4::vector4<int> v4{3, 4, 5, 6};
		r4::vector2<int> v2{7, 8};

		v4 = v2;

		ASSERT_INFO_ALWAYS(v4[0] == 7, "v4[0] = " << v4[0])
        ASSERT_INFO_ALWAYS(v4[1] == 8, "v4[1] = " << v4[1])
		ASSERT_INFO_ALWAYS(v4[2] == 0, "v4[2] = " << v4[2])
		ASSERT_INFO_ALWAYS(v4[3] == 1, "v4[3] = " << v4[3])
	}

	// test operator=(n)
	{
		r4::vector4<int> v4{3, 4, 5, 6};

		v4 = 8;

		ASSERT_INFO_ALWAYS(v4[0] == 8, "v4[0] = " << v4[0])
        ASSERT_INFO_ALWAYS(v4[1] == 8, "v4[1] = " << v4[1])
		ASSERT_INFO_ALWAYS(v4[2] == 8, "v4[2] = " << v4[2])
		ASSERT_INFO_ALWAYS(v4[3] == 8, "v4[3] = " << v4[3])
	}

	// test set(n)
	{
		r4::vector4<int> v4{3, 4, 5, 6};

		v4.set(8);

		ASSERT_INFO_ALWAYS(v4[0] == 8, "v4[0] = " << v4[0])
        ASSERT_INFO_ALWAYS(v4[1] == 8, "v4[1] = " << v4[1])
		ASSERT_INFO_ALWAYS(v4[2] == 8, "v4[2] = " << v4[2])
		ASSERT_INFO_ALWAYS(v4[3] == 8, "v4[3] = " << v4[3])
	}

	// test operator+=(vector2)
	{
		r4::vector4<int> v4{3, 4, 5, 6};
		r4::vector2<int> v2{7, 8};

		v4 += v2;

		ASSERT_INFO_ALWAYS(v4[0] == 10, "v4[0] = " << v4[0])
        ASSERT_INFO_ALWAYS(v4[1] == 12, "v4[1] = " << v4[1])
		ASSERT_INFO_ALWAYS(v4[2] == 5, "v4[2] = " << v4[2])
		ASSERT_INFO_ALWAYS(v4[3] == 6, "v4[3] = " << v4[3])
	}

	// test operator+=(vector3)
	{
		r4::vector4<int> v4{3, 4, 5, 6};
		r4::vector3<int> v3{7, 8, 9};

		v4 += v3;

		ASSERT_INFO_ALWAYS(v4[0] == 10, "v4[0] = " << v4[0])
        ASSERT_INFO_ALWAYS(v4[1] == 12, "v4[1] = " << v4[1])
		ASSERT_INFO_ALWAYS(v4[2] == 14, "v4[2] = " << v4[2])
		ASSERT_INFO_ALWAYS(v4[3] == 6, "v4[3] = " << v4[3])
	}

	// test operator+=(vector4)
	{
		r4::vector4<int> v4{3, 4, 5, 6};

		v4 += r4::vector4<int>{7, 8, 9, 10};

		ASSERT_INFO_ALWAYS(v4[0] == 10, "v4[0] = " << v4[0])
        ASSERT_INFO_ALWAYS(v4[1] == 12, "v4[1] = " << v4[1])
		ASSERT_INFO_ALWAYS(v4[2] == 14, "v4[2] = " << v4[2])
		ASSERT_INFO_ALWAYS(v4[3] == 16, "v4[3] = " << v4[3])
	}

	// test operator+(vector4)
	{
		r4::vector4<int> v4{3, 4, 5, 6};

		auto r = v4 + r4::vector4<int>{7, 8, 9, 10};

		ASSERT_INFO_ALWAYS(r[0] == 10, "r[0] = " << r[0])
        ASSERT_INFO_ALWAYS(r[1] == 12, "r[1] = " << r[1])
		ASSERT_INFO_ALWAYS(r[2] == 14, "r[2] = " << r[2])
		ASSERT_INFO_ALWAYS(r[3] == 16, "r[3] = " << r[3])
	}

	// test operator-=(vector4)
	{
		r4::vector4<int> v4{3, 4, 5, 6};

		v4 -= r4::vector4<int>{7, 9, 11, 13};

		ASSERT_INFO_ALWAYS(v4[0] == -4, "v4[0] = " << v4[0])
        ASSERT_INFO_ALWAYS(v4[1] == -5, "v4[1] = " << v4[1])
		ASSERT_INFO_ALWAYS(v4[2] == -6, "v4[2] = " << v4[2])
		ASSERT_INFO_ALWAYS(v4[3] == -7, "v4[3] = " << v4[3])
	}

	// test operator-(vector4)
	{
		r4::vector4<int> v4{3, 4, 5, 6};

		auto r = v4 - r4::vector4<int>{7, 9, 11, 13};

		ASSERT_INFO_ALWAYS(r[0] == -4, "r[0] = " << r[0])
        ASSERT_INFO_ALWAYS(r[1] == -5, "r[1] = " << r[1])
		ASSERT_INFO_ALWAYS(r[2] == -6, "r[2] = " << r[2])
		ASSERT_INFO_ALWAYS(r[3] == -7, "r[3] = " << r[3])
	}

	// test operator-()
	{
		r4::vector4<int> v4{3, 4, 5, 6};

		auto r = -v4;

		ASSERT_INFO_ALWAYS(r[0] == -3, "r[0] = " << r[0])
        ASSERT_INFO_ALWAYS(r[1] == -4, "r[1] = " << r[1])
		ASSERT_INFO_ALWAYS(r[2] == -5, "r[2] = " << r[2])
		ASSERT_INFO_ALWAYS(r[3] == -6, "r[3] = " << r[3])
	}

	// test operator*=(n)
	{
		r4::vector4<int> v4{3, 4, 5, 6};

		v4 *= 2;

		ASSERT_INFO_ALWAYS(v4[0] == 6, "v4[0] = " << v4[0])
        ASSERT_INFO_ALWAYS(v4[1] == 8, "v4[1] = " << v4[1])
		ASSERT_INFO_ALWAYS(v4[2] == 10, "v4[2] = " << v4[2])
		ASSERT_INFO_ALWAYS(v4[3] == 12, "v4[3] = " << v4[3])
	}

	// test operator*(n)
	{
		r4::vector4<int> v4{3, 4, 5, 6};

		auto r = v4 * 2;

		ASSERT_INFO_ALWAYS(r[0] == 6, "r[0] = " << r[0])
        ASSERT_INFO_ALWAYS(r[1] == 8, "r[1] = " << r[1])
		ASSERT_INFO_ALWAYS(r[2] == 10, "r[2] = " << r[2])
		ASSERT_INFO_ALWAYS(r[3] == 12, "r[3] = " << r[3])
	}

	// test operator*(n, vector4)
	{
		r4::vector4<int> v4{3, 4, 5, 6};

		auto r = 2 * v4;

		ASSERT_INFO_ALWAYS(r[0] == 6, "r[0] = " << r[0])
        ASSERT_INFO_ALWAYS(r[1] == 8, "r[1] = " << r[1])
		ASSERT_INFO_ALWAYS(r[2] == 10, "r[2] = " << r[2])
		ASSERT_INFO_ALWAYS(r[3] == 12, "r[3] = " << r[3])
	}

	// test operator/=(n)
	{
		r4::vector4<int> v4{6, 8, 10, 12};

		v4 /= 2;

		ASSERT_INFO_ALWAYS(v4[0] == 3, "v4[0] = " << v4[0])
        ASSERT_INFO_ALWAYS(v4[1] == 4, "v4[1] = " << v4[1])
		ASSERT_INFO_ALWAYS(v4[2] == 5, "v4[2] = " << v4[2])
		ASSERT_INFO_ALWAYS(v4[3] == 6, "v4[3] = " << v4[3])
	}

	// test operator/(n)
	{
		r4::vector4<int> v4{6, 8, 10, 12};

		auto r = v4 / 2;

		ASSERT_INFO_ALWAYS(r[0] == 3, "r[0] = " << r[0])
        ASSERT_INFO_ALWAYS(r[1] == 4, "r[1] = " << r[1])
		ASSERT_INFO_ALWAYS(r[2] == 5, "r[2] = " << r[2])
		ASSERT_INFO_ALWAYS(r[3] == 6, "r[3] = " << r[3])
	}

	// test operator*(vector4)
	{
		r4::vector4<int> v4{3, 4, 5, 6};

		auto r = v4 * r4::vector4<int>{7, 8, 9, 10};

		ASSERT_INFO_ALWAYS(r == 3 * 7 + 4 * 8 + 5 * 9 + 6 * 10, "r = " << r)
	}

	// test operator%(vector4)
	{
		r4::vector4<int> v4{3, 4, 5, 6};

		auto r = v4 % r4::vector4<int>{7, 8, 9, 10};

		ASSERT_INFO_ALWAYS(r[0] == -4, "r[0] = " << r[0])
        ASSERT_INFO_ALWAYS(r[1] == 8, "r[1] = " << r[1])
		ASSERT_INFO_ALWAYS(r[2] == -4, "r[2] = " << r[2])
		ASSERT_INFO_ALWAYS(r[3] == 60, "r[3] = " << r[3])
	}

	// test negate()
	{
		r4::vector4<int> v4{3, 4, 5, 6};

		v4.negate();

		ASSERT_INFO_ALWAYS(v4[0] == -3, "v4[0] = " << v4[0])
        ASSERT_INFO_ALWAYS(v4[1] == -4, "v4[1] = " << v4[1])
		ASSERT_INFO_ALWAYS(v4[2] == -5, "v4[2] = " << v4[2])
		ASSERT_INFO_ALWAYS(v4[3] == -6, "v4[3] = " << v4[3])
	}

	// test norm_pow2()
	{
		r4::vector4<int> v4{3, 4, 5, 6};

		auto r = v4.norm_pow2();

		ASSERT_ALWAYS(r == 3 * 3 + 4 * 4 + 5 * 5 + 6 * 6)
	}

	// test norm()
	{
		r4::vector4<float> v4{3, 4, 5, 6};

		auto r = v4.norm();

		ASSERT_INFO_ALWAYS(int(r) == 9, "r = " << r)
	}

	// test normalize()
	{
		r4::vector4<float> v4{3, 4, 5, 6};

		v4.normalize();
		v4 *= 1000.0f;

		auto r = v4.to<int>();

		ASSERT_INFO_ALWAYS(r[0] == 323, "v4[0] = " << v4[0])
        ASSERT_INFO_ALWAYS(r[1] == 431, "v4[1] = " << v4[1])
		ASSERT_INFO_ALWAYS(r[2] == 539, "v4[2] = " << v4[2])
		ASSERT_INFO_ALWAYS(r[3] == 646, "v4[3] = " << v4[3])
	}

	// test min(vector4, vector4)
	{
		r4::vector4<int> a{2, 3, 4, -6};
		r4::vector4<int> b{5, 1, -5, -7};

		auto r = min(a, b);

		ASSERT_ALWAYS(r[0] == 2)
		ASSERT_ALWAYS(r[1] == 1)
		ASSERT_ALWAYS(r[2] == -5)
		ASSERT_ALWAYS(r[3] == -7)
	}

	// test max(vector4, vector4)
	{
		r4::vector4<int> a{2, 3, -4, -6};
		r4::vector4<int> b{5, 1, -5, -7};

		auto r = max(a, b);

		ASSERT_ALWAYS(r[0] == 5)
		ASSERT_ALWAYS(r[1] == 3)
		ASSERT_ALWAYS(r[2] == -4)
		ASSERT_ALWAYS(r[3] == -6)
	}

	return 0;
}
