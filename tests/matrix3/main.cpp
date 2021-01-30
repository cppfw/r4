#include <utki/debug.hpp>
#include <utki/math.hpp>

#include "../../src/r4/matrix.hpp"

#include <sstream>

int main(int argc, char** argv){

    // test operator<<
    {
        r4::matrix3<int> m;
		m.set_identity();

		std::stringstream ss;

		ss << m;

		auto cmp =
                "|1 0 0" "\n"
                "|0 1 0" "\n"
                "|0 0 1" "\n";

		// TRACE_ALWAYS(<< "m = " << ss.str() << std::endl)
		// TRACE_ALWAYS(<< "cmp = " << cmp << std::endl)

		auto str = ss.str();

        ASSERT_INFO_ALWAYS(str == cmp, "m = " << str << "\ncmp = " << cmp)
        // v.negate();

        // ASSERT_ALWAYS(!v.is_negative())
        // ASSERT_ALWAYS(v.x == -13)
        // ASSERT_ALWAYS(v.y == 14)
    }

    // test operator[]
    {
        r4::matrix3<int> m;

        m[0][0] = 1;
        m[0][1] = 2;
        m[0][2] = 3;
        m[1][0] = 4;
        m[1][1] = 5;
        m[1][2] = 6;
        m[2][0] = 7;
        m[2][1] = 8;
        m[2][2] = 9;

        std::stringstream ss;

        ss << m;

        auto cmp =
                "|1 2 3" "\n"
                "|4 5 6" "\n"
                "|7 8 9" "\n";
        auto str = ss.str();

        ASSERT_INFO_ALWAYS(str == cmp, "m = " << str << "\ncmp = " << cmp)
    }

    // test constructor from vector4 arguments
    {
        r4::vector4<int> r0(1, 2, 3, 4);
        r4::vector4<int> r1(5, 6, 7, 8);
        r4::vector4<int> r2(9, 10, 11, 12);

        r4::matrix3<int> m(r0, r1, r2);

        std::stringstream ss;

        ss << m;

        auto cmp =
                "|1 2 3" "\n"
                "|5 6 7" "\n"
                "|9 10 11" "\n";
        auto str = ss.str();

        ASSERT_INFO_ALWAYS(str == cmp, "m = " << str << "\ncmp = " << cmp)
    }

    // test element type conversion
    {
        r4::matrix3<float> mf{
            { 1.1f, 2.2f, 3.3f },
            { 4.4f, 5.5f, 6.6f },
            { 7.7f, 8.8f, 9.9f }
        };

        auto mi = mf.to<int>();

        std::stringstream ss;

        ss << mi;

        auto cmp =
                "|1 2 3" "\n"
                "|4 5 6" "\n"
                "|7 8 9" "\n";
        auto str = ss.str();

        ASSERT_INFO_ALWAYS(str == cmp, "m = " << str << "\ncmp = " << cmp)
    }

    // test operator*(vector2)
    {
        r4::vector2<int> v(2, 3);

        r4::matrix3<int> m{
                { 2, 3, 4 },
                { 5, 6, 7 },
                { 8, 9, 10 }
            };
        
        auto r = m * v;

        ASSERT_INFO_ALWAYS(r[0] == 13, "r[0] = " << r[0])
        ASSERT_INFO_ALWAYS(r[1] == 28, "r[1] = " << r[1])
    }

    // test operator*(vector3)
    {
        r4::vector3<int> v(2, 3, 4);

        r4::matrix3<int> m{
                { 2, 3, 4 },
                { 5, 6, 7 },
                { 8, 9, 10 }
            };
        
        auto r = m * v;

        ASSERT_INFO_ALWAYS(r[0] == 2 * 2 + 3 * 3 + 4 * 4, "r[0] = " << r[0])
        ASSERT_INFO_ALWAYS(r[1] == 2 * 5 + 3 * 6 + 4 * 7, "r[1] = " << r[1])
        ASSERT_INFO_ALWAYS(r[2] == 2 * 8 + 3 * 9 + 4 * 10, "r[2] = " << r[2])
    }

    // test transpose()
    {
        r4::matrix3<int> m{
            { 1, 2, 3 },
            { 4, 5, 6 },
            { 7, 8, 9 }
        };

        m.transpose();

        std::stringstream ss;

        ss << m;

        auto cmp =
                "|1 4 7" "\n"
                "|2 5 8" "\n"
                "|3 6 9" "\n";
        auto str = ss.str();

        ASSERT_INFO_ALWAYS(str == cmp, "m = " << str << "\ncmp = " << cmp)
    }

    // test operator*(matrix3)
    {
        r4::matrix3<int> m1{
                { 1, 2, 3 },
                { 4, 5, 6 },
                { 7, 8, 9 }
            };

        r4::matrix3<int> m2{
                { 2, 3, 4 },
                { 5, 6, 7 },
                { 8, 9, 10 }
            };

        auto r = m1 * m2;

        ASSERT_INFO_ALWAYS(r[0][0] == 1 * 2 + 2 * 5 + 3 * 8, "r[0][0] = " << r[0][0])
        ASSERT_INFO_ALWAYS(r[1][0] == 4 * 2 + 5 * 5 + 6 * 8, "r[1][0] = " << r[1][0])
        ASSERT_INFO_ALWAYS(r[2][0] == 7 * 2 + 8 * 5 + 9 * 8, "r[2][0] = " << r[2][0])

        ASSERT_INFO_ALWAYS(r[0][1] == 1 * 3 + 2 * 6 + 3 * 9, "r[0][1] = " << r[0][1])
        ASSERT_INFO_ALWAYS(r[1][1] == 4 * 3 + 5 * 6 + 6 * 9, "r[1][1] = " << r[1][1])
        ASSERT_INFO_ALWAYS(r[2][1] == 7 * 3 + 8 * 6 + 9 * 9, "r[2][1] = " << r[2][1])

        ASSERT_INFO_ALWAYS(r[0][2] == 1 * 4 + 2 * 7 + 3 * 10, "r[0][2] = " << r[0][2])
        ASSERT_INFO_ALWAYS(r[1][2] == 4 * 4 + 5 * 7 + 6 * 10, "r[1][2] = " << r[1][2])
        ASSERT_INFO_ALWAYS(r[2][2] == 7 * 4 + 8 * 7 + 9 * 10, "r[2][2] = " << r[2][2])
    }

    // test operator*=(matrix3)
    {
        r4::matrix3<int> m1{
                { 1, 2, 3 },
                { 4, 5, 6 },
                { 7, 8, 9 }
            };

        r4::matrix3<int> m2{
                { 2, 3, 4 },
                { 5, 6, 7 },
                { 8, 9, 10 }
            };
        
        auto r = m1 * m2;

        m1 *= m2;

        ASSERT_INFO_ALWAYS(m1 == r, "m1 = " << m1 << " r = " << r)
    }

    // test left_mul(matrix3)
    {
        r4::matrix3<int> m1{
                { 1, 2, 3 },
                { 4, 5, 6 },
                { 7, 8, 9 }
            };

        r4::matrix3<int> m2{
                { 2, 3, 4 },
                { 5, 6, 7 },
                { 8, 9, 10 }
            };
        
        auto r = m1 * m2;

        m2.left_mul(m1);

        ASSERT_INFO_ALWAYS(m2 == r, "m2 = " << m2 << " r = " << r)
    }

    // test scale(x, y, z)
    {
        r4::matrix3<int> m{
                { 1, 2, 3 },
                { 4, 5, 6 },
                { 7, 8, 9 }
            };
        
        m.scale(2, 3, 4);

        std::stringstream ss;

        ss << m;

        auto cmp =
                "|2 6 12" "\n"
                "|8 15 24" "\n"
                "|14 24 36" "\n";
        auto str = ss.str();

        ASSERT_INFO_ALWAYS(str == cmp, "m = " << str << "\ncmp = " << cmp)
    }

    // test scale(x, y)
    {
        r4::matrix3<int> m{
                { 1, 2, 3 },
                { 4, 5, 6 },
                { 7, 8, 9 }
            };
        
        m.scale(2, 3);

        std::stringstream ss;

        ss << m;

        auto cmp =
                "|2 6 3" "\n"
                "|8 15 6" "\n"
                "|14 24 9" "\n";
        auto str = ss.str();

        ASSERT_INFO_ALWAYS(str == cmp, "m = " << str << "\ncmp = " << cmp)
    }

    // test scale(s)
    {
        r4::matrix3<int> m{
                { 1, 2, 3 },
                { 4, 5, 6 },
                { 7, 8, 9 }
            };
        
        m.scale(2);

        std::stringstream ss;

        ss << m;

        auto cmp =
                "|2 4 6" "\n"
                "|8 10 12" "\n"
                "|14 16 18" "\n";
        auto str = ss.str();

        ASSERT_INFO_ALWAYS(str == cmp, "m = " << str << "\ncmp = " << cmp)
    }

    // test translate(x, y)
    {
        r4::matrix3<int> m{
                { 1, 2, 3 },
                { 4, 5, 6 },
                { 7, 8, 9 }
            };
        
        m.translate(2, 3);

        std::stringstream ss;

        ss << m;

        auto cmp =
                "|1 2 11" "\n"
                "|4 5 29" "\n"
                "|7 8 47" "\n";
        auto str = ss.str();

        ASSERT_INFO_ALWAYS(str == cmp, "m =\n" << str << "\ncmp =\n" << cmp)
    }

    // test translate(vector2)
    {
        r4::matrix3<int> m{
                { 1, 2, 3 },
                { 4, 5, 6 },
                { 7, 8, 9 }
            };
        
        m.translate(r4::vector2<int>{2, 3});

        std::stringstream ss;

        ss << m;

        auto cmp =
            "|1 2 11" "\n"
            "|4 5 29" "\n"
            "|7 8 47" "\n";
        auto str = ss.str();

        ASSERT_INFO_ALWAYS(str == cmp, "m =\n" << str << "\ncmp =\n" << cmp)
    }

    // test rotate(a)
    {
        r4::matrix3<float> m{
                { 10, 20, 30 },
                { 40, 50, 60 },
                { 70, 80, 90 }
            };
        
        float a = utki::pi<float>() / 6;

        decltype(m) res(m);
        res.rotate(a);

        using std::sin;
        using std::cos;

        r4::matrix3<float> rot{
            {cos(a), -sin(a), 0},
            {sin(a), cos(a), 0},
            {0, 0, 1}
        };

        auto cmp = m * rot;

        cmp *= 1000.0f;
        res *= 1000.0f;

        ASSERT_INFO_ALWAYS(res.to<int>() == cmp.to<int>(), "res = " << res << " cmp = " << cmp)
    }

	// test minor(r, c)
	{
		r4::matrix3<int> m{
			{3, 0, 2},
			{2, 0, -2},
			{0, 1, 1}
		};

		ASSERT_ALWAYS(m.minor(0, 0) == 2)
		ASSERT_ALWAYS(m.minor(0, 1) == 2)
		ASSERT_ALWAYS(m.minor(0, 2) == 2)

		ASSERT_ALWAYS(m.minor(1, 0) == -2)
		ASSERT_ALWAYS(m.minor(1, 1) == 3)
		ASSERT_ALWAYS(m.minor(1, 2) == 3)

		ASSERT_ALWAYS(m.minor(2, 0) == 0)
		ASSERT_ALWAYS(m.minor(2, 1) == -10)
		ASSERT_ALWAYS(m.minor(2, 2) == 0)
	}

	// test det()
	{
		r4::matrix3<int> m{
                { 10, 20, 30 },
                { 40, 50, 60 },
                { 70, 80, 100 }
            };
		
		ASSERT_ALWAYS(m.det() == -3000)
	}

	// test inv()
	{
		r4::matrix3<float> m{
		 	{1, 3, 5},
			{1, 3, 1},
			{4, 3, 9},
		};

		auto i = m * m.inv();

		const float epsilon = 1e-6;

		auto diff = decltype(m)().set_identity() - i;

		diff.snap_to_zero(epsilon);

		ASSERT_INFO_ALWAYS(diff == decltype(m)().set(0), std::endl << "i = " << i.snap_to_zero(epsilon) << std::endl << "diff = " << diff)
	}

    return 0;
}
