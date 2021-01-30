#include <utki/debug.hpp>

#include "../../src/r4/quaternion.hpp"

void test(){
	// test constructor(x, y, z, w)
	{
		r4::quaternion<int> a{3, 4, 5, 6};

		ASSERT_ALWAYS(a[0] == 3)
		ASSERT_ALWAYS(a[1] == 4)
		ASSERT_ALWAYS(a[2] == 5)
		ASSERT_ALWAYS(a[3] == 6)
	}

	// test constructor(vector3)
	{
		r4::quaternion<float> q{r4::vector3<float>{3, 4, 5}};
		q *= 1000.0f;
		auto r = q.to<int>();

		ASSERT_INFO_ALWAYS(r[0] == -162, "q = " << q)
		ASSERT_INFO_ALWAYS(r[1] == -217, "q = " << q)
		ASSERT_INFO_ALWAYS(r[2] == -271, "q = " << q)
		ASSERT_INFO_ALWAYS(r[3] == -923, "q = " << q)
	}
	
	// test to()
	{
		r4::quaternion<float> qf(1.1f, 2.2f, 3.3f, 4.4f);
        
        auto qi = qf.to<int>();

        ASSERT_INFO_ALWAYS(qi[0] == 1, "qi[0] = " << qi[0])
        ASSERT_INFO_ALWAYS(qi[1] == 2, "qi[1] = " << qi[1])
		ASSERT_INFO_ALWAYS(qi[2] == 3, "qi[2] = " << qi[2])
		ASSERT_INFO_ALWAYS(qi[3] == 4, "qi[3] = " << qi[3])
	}

	// test operator!()
	{
		r4::quaternion<int> a{3, 4, 5, 6};

		auto r = !a;

		ASSERT_ALWAYS(r[0] == -3)
		ASSERT_ALWAYS(r[1] == -4)
		ASSERT_ALWAYS(r[2] == -5)
		ASSERT_ALWAYS(r[3] == 6)
	}

	// test operator+=(quaternion)
	{
		r4::quaternion<int> a{3, 4, 5, 6};

		a += r4::quaternion<int>{1, 2, 3, 4};

		ASSERT_ALWAYS(a[0] == 4)
		ASSERT_ALWAYS(a[1] == 6)
		ASSERT_ALWAYS(a[2] == 8)
		ASSERT_ALWAYS(a[3] == 10)
	}

	// test operator+(quaternion)
	{
		r4::quaternion<int> a{3, 4, 5, 6};

		auto r = a + r4::quaternion<int>{1, 2, 3, 4};

		ASSERT_ALWAYS(r[0] == 4)
		ASSERT_ALWAYS(r[1] == 6)
		ASSERT_ALWAYS(r[2] == 8)
		ASSERT_ALWAYS(r[3] == 10)
	}

	// test operator*=(n)
	{
		r4::quaternion<int> a{3, 4, 5, 6};

		a *= 3;

		ASSERT_ALWAYS(a[0] == 9)
		ASSERT_ALWAYS(a[1] == 12)
		ASSERT_ALWAYS(a[2] == 15)
		ASSERT_ALWAYS(a[3] == 18)
	}

	// test operator*(n)
	{
		r4::quaternion<int> a{3, 4, 5, 6};

		auto r = a * 3;

		ASSERT_ALWAYS(r[0] == 9)
		ASSERT_ALWAYS(r[1] == 12)
		ASSERT_ALWAYS(r[2] == 15)
		ASSERT_ALWAYS(r[3] == 18)
	}

	// test operator(n, quaternion)
	{
		r4::quaternion<int> a{3, 4, 5, 6};

		auto r = 3 * a;

		ASSERT_ALWAYS(r[0] == 9)
		ASSERT_ALWAYS(r[1] == 12)
		ASSERT_ALWAYS(r[2] == 15)
		ASSERT_ALWAYS(r[3] == 18)
	}

	// test operator/=(n)
	{
		r4::quaternion<int> a{9, 12, 15, 18};

		a /= 3;

		ASSERT_ALWAYS(a[0] == 3)
		ASSERT_ALWAYS(a[1] == 4)
		ASSERT_ALWAYS(a[2] == 5)
		ASSERT_ALWAYS(a[3] == 6)
	}

	// test operator/(n)
	{
		r4::quaternion<int> a{9, 12, 15, 18};

		auto r = a / 3;

		ASSERT_ALWAYS(r[0] == 3)
		ASSERT_ALWAYS(r[1] == 4)
		ASSERT_ALWAYS(r[2] == 5)
		ASSERT_ALWAYS(r[3] == 6)
	}

	// test operator*(quaternion)
	{
		r4::quaternion<int> a{3, 4, 5, 6};
		r4::quaternion<int> b{1, 2, 3, 4};

		auto r = a * b;

		ASSERT_ALWAYS(r == 3 * 1 + 4 * 2 + 5 * 3 + 6 * 4)
	}

	// test operator%=(quaternion)
	{
		r4::quaternion<int> a{3, 4, 5, 6};
		r4::quaternion<int> b{1, 2, 3, 4};

		a %= b;

		ASSERT_INFO_ALWAYS(a[0] == 20, "a = " << a)
		ASSERT_INFO_ALWAYS(a[1] == 24, "a = " << a)
		ASSERT_INFO_ALWAYS(a[2] == 40, "a = " << a)
		ASSERT_INFO_ALWAYS(a[3] == -2, "a = " << a)
	}

	// test operator%(quaternion)
	{
		r4::quaternion<int> a{3, 4, 5, 6};
		r4::quaternion<int> b{1, 2, 3, 4};

		auto r = a % b;

		ASSERT_INFO_ALWAYS(r[0] == 20, "r = " << r)
		ASSERT_INFO_ALWAYS(r[1] == 24, "r = " << r)
		ASSERT_INFO_ALWAYS(r[2] == 40, "r = " << r)
		ASSERT_INFO_ALWAYS(r[3] == -2, "r = " << r)
	}

	// test set_identity()
	{
		r4::quaternion<int> a{3, 4, 5, 6};

		a.set_identity();

		ASSERT_ALWAYS(a[0] == 0)
		ASSERT_ALWAYS(a[1] == 0)
		ASSERT_ALWAYS(a[2] == 0)
		ASSERT_ALWAYS(a[3] == 1)
	}

	// test conjugate()
	{
		r4::quaternion<int> a{3, 4, 5, 6};

		a.conjugate();

		ASSERT_ALWAYS(a[0] == -3)
		ASSERT_ALWAYS(a[1] == -4)
		ASSERT_ALWAYS(a[2] == -5)
		ASSERT_ALWAYS(a[3] == 6)
	}

	// test negate()
	{
		r4::quaternion<int> a{3, 4, 5, 6};

		a.negate();

		ASSERT_ALWAYS(a[0] == -3)
		ASSERT_ALWAYS(a[1] == -4)
		ASSERT_ALWAYS(a[2] == -5)
		ASSERT_ALWAYS(a[3] == -6)
	}

	// test norm_pow2()
	{
		r4::quaternion<int> a{3, 4, 5, 6};

		auto r = a.norm_pow2();

		ASSERT_ALWAYS(r == 3 * 3 + 4 * 4 + 5 * 5 + 6 * 6)
	}

	// test norm()
	{
		r4::quaternion<float> a{3, 4, 5, 6};

		auto r = a.norm();

		using std::sqrt;
		ASSERT_INFO_ALWAYS(int(r) == int(sqrt(3 * 3 + 4 * 4 + 5 * 5 + 6 * 6)), "r = " << r)
	}

	// test normalize()
	{
		r4::quaternion<float> a{3, 4, 5, 6};

		a.normalize();

		a *= 1000.0f;

		auto r = a.to<int>();

		ASSERT_INFO_ALWAYS(r[0] == 323, "a = " << a)
		ASSERT_INFO_ALWAYS(r[1] == 431, "a = " << a)
		ASSERT_INFO_ALWAYS(r[2] == 539, "a = " << a)
		ASSERT_INFO_ALWAYS(r[3] == 646, "a = " << a)
	}

	// test set_rotation(x, y, z, a)
	{
		r4::quaternion<float> a{3, 4, 5, 6};

		a.set_rotation(1, 2, 3, 4);

		a *= 1000.0f;

		auto r = a.to<int>();

		ASSERT_INFO_ALWAYS(r[0] == 909, "a = " << a)
		ASSERT_INFO_ALWAYS(r[1] == 1818, "a = " << a)
		ASSERT_INFO_ALWAYS(r[2] == 2727, "a = " << a)
		ASSERT_INFO_ALWAYS(r[3] == -416, "a = " << a)
	}

	// test set_rotation(vector3, a)
	{
		r4::quaternion<float> a{3, 4, 5, 6};

		a.set_rotation(r4::vector3<float>{1, 2, 3}, 4);

		a *= 1000.0f;

		auto r = a.to<int>();

		ASSERT_INFO_ALWAYS(r[0] == 909, "a = " << a)
		ASSERT_INFO_ALWAYS(r[1] == 1818, "a = " << a)
		ASSERT_INFO_ALWAYS(r[2] == 2727, "a = " << a)
		ASSERT_INFO_ALWAYS(r[3] == -416, "a = " << a)
	}

	// test to_matrix4()
	{
		// TODO:
	}

	// test slerp(quaternion, t)
	{
		// TODO:
	}
}
