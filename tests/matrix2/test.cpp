#include <utki/debug.hpp>
#include <utki/math.hpp>

#include "../../src/r4/matrix.hpp"

#include <sstream>

void test_matrix2(){
	// test operator<<
    {
        r4::matrix2<int> m;
		m.set_identity();

		std::stringstream ss;

		ss << m;

		auto cmp =
				"|1 0 0" "\n"
				"|0 1 0" "\n";

		// TRACE_ALWAYS(<< "m = " << ss.str() << std::endl)
		// TRACE_ALWAYS(<< "cmp = " << cmp << std::endl)

		auto str = ss.str();

        ASSERT_INFO_ALWAYS(str == cmp, "m =\n" << str << "\ncmp =\n" << cmp)
        // v.negate();

        // ASSERT_ALWAYS(!v.is_negative())
        // ASSERT_ALWAYS(v.x == -13)
        // ASSERT_ALWAYS(v.y == 14)
    }

    // test constructor(vector3, vector3)
    {
        r4::matrix2<int> m{
            {1, 2, 3},
            {4, 5, 6}
        };

        ASSERT_ALWAYS(m[0][0] == 1)
        ASSERT_ALWAYS(m[0][1] == 2)
        ASSERT_ALWAYS(m[0][2] == 3)

        ASSERT_ALWAYS(m[1][0] == 4)
        ASSERT_ALWAYS(m[1][1] == 5)
        ASSERT_ALWAYS(m[1][2] == 6)
    }

    // test to()
    {
        r4::matrix2<double> m0{
            {1.1, 2.2, 3.3},
            {4.4, 5.5, 6.6}
        };

        auto m = m0.to<int>();

        ASSERT_ALWAYS(m[0][0] == 1)
        ASSERT_ALWAYS(m[0][1] == 2)
        ASSERT_ALWAYS(m[0][2] == 3)

        ASSERT_ALWAYS(m[1][0] == 4)
        ASSERT_ALWAYS(m[1][1] == 5)
        ASSERT_ALWAYS(m[1][2] == 6)
    }

    // test operator*(vector2)
    {
        r4::matrix2<int> m{
            {1, 2, 3},
            {4, 5, 6}
        };

        auto r = m * r4::vector2<int>{3, 4};

        ASSERT_ALWAYS(r[0] == 14)
        ASSERT_ALWAYS(r[1] == 38)
    }

    // test transpose()
    {
        r4::matrix2<int> m{
            {1, 2, 3},
            {4, 5, 6}
        };

        m.transpose();

        ASSERT_ALWAYS(m[0][0] == 1)
		ASSERT_ALWAYS(m[0][1] == 4)
		ASSERT_ALWAYS(m[0][2] == 0)
        ASSERT_ALWAYS(m[1][0] == 2)
		ASSERT_ALWAYS(m[1][1] == 5)
		ASSERT_ALWAYS(m[1][2] == 0)
    }

    // test operator*(matrix2)
    {
        r4::matrix2<int> m0{
            {1, 2, 3},
            {4, 5, 6}
        };

        r4::matrix2<int> m1{
            {3, 4, 5},
            {6, 7, 8}
        };

        auto m = m0 * m1;

        ASSERT_ALWAYS(m[0][0] == 15) ASSERT_ALWAYS(m[0][1] == 18) ASSERT_ALWAYS(m[0][2] == 24)
        ASSERT_ALWAYS(m[1][0] == 42) ASSERT_ALWAYS(m[1][1] == 51) ASSERT_ALWAYS(m[1][2] == 66)
    }

    // test operator*=(matrix2)
    {
        r4::matrix2<int> m{
            {1, 2, 3},
            {4, 5, 6}
        };

        r4::matrix2<int> m1{
            {3, 4, 5},
            {6, 7, 8}
        };

        m *= m1;

        ASSERT_ALWAYS(m[0][0] == 15) ASSERT_ALWAYS(m[0][1] == 18) ASSERT_ALWAYS(m[0][2] == 24)
        ASSERT_ALWAYS(m[1][0] == 42) ASSERT_ALWAYS(m[1][1] == 51) ASSERT_ALWAYS(m[1][2] == 66)
    }

    // test left_multiply(matrix2)
    {
        r4::matrix2<int> m1{
            {1, 2, 3},
            {4, 5, 6}
        };

        r4::matrix2<int> m{
            {3, 4, 5},
            {6, 7, 8}
        };

        m.left_mul(m1);

        ASSERT_ALWAYS(m[0][0] == 15) ASSERT_ALWAYS(m[0][1] == 18) ASSERT_ALWAYS(m[0][2] == 24)
        ASSERT_ALWAYS(m[1][0] == 42) ASSERT_ALWAYS(m[1][1] == 51) ASSERT_ALWAYS(m[1][2] == 66)
    }

    // test set_identity()
    {
        r4::matrix2<int> m{
            {3, 4, 5},
            {6, 7, 8}
        };

        m.set_identity();

        ASSERT_ALWAYS(m[0][0] == 1) ASSERT_ALWAYS(m[0][1] == 0) ASSERT_ALWAYS(m[0][2] == 0)
        ASSERT_ALWAYS(m[1][0] == 0) ASSERT_ALWAYS(m[1][1] == 1) ASSERT_ALWAYS(m[1][2] == 0)
    }

    // test scale(x, y)
    {
        r4::matrix2<int> m{
            {1, 2, 3},
            {4, 5, 6}
        };

        m.scale(3, 4);

        ASSERT_ALWAYS(m[0][0] == 3) ASSERT_ALWAYS(m[0][1] == 8) ASSERT_ALWAYS(m[0][2] == 3)
        ASSERT_ALWAYS(m[1][0] == 12) ASSERT_ALWAYS(m[1][1] == 20) ASSERT_ALWAYS(m[1][2] == 6)
    }

    // test scale(n)
    {
        r4::matrix2<int> m{
            {1, 2, 3},
            {4, 5, 6}
        };

        m.scale(3);

        ASSERT_ALWAYS(m[0][0] == 3) ASSERT_ALWAYS(m[0][1] == 6) ASSERT_ALWAYS(m[0][2] == 3)
        ASSERT_ALWAYS(m[1][0] == 12) ASSERT_ALWAYS(m[1][1] == 15) ASSERT_ALWAYS(m[1][2] == 6)
    }

    // test scale(vector2)
    {
        r4::matrix2<int> m{
            {1, 2, 3},
            {4, 5, 6}
        };

        m.scale(r4::vector2<int>{3, 4});

        ASSERT_ALWAYS(m[0][0] == 3) ASSERT_ALWAYS(m[0][1] == 8) ASSERT_ALWAYS(m[0][2] == 3)
        ASSERT_ALWAYS(m[1][0] == 12) ASSERT_ALWAYS(m[1][1] == 20) ASSERT_ALWAYS(m[1][2] == 6)
    }

    // test translate(x, y)
    {
        r4::matrix2<int> m{
            {1, 2, 3},
            {4, 5, 6}
        };

        m.translate(3, 4);

        ASSERT_ALWAYS(m[0][0] == 1) ASSERT_ALWAYS(m[0][1] == 2) ASSERT_ALWAYS(m[0][2] == 14)
        ASSERT_ALWAYS(m[1][0] == 4) ASSERT_ALWAYS(m[1][1] == 5) ASSERT_ALWAYS(m[1][2] == 38)
    }

    // test translate(vector2)
    {
        r4::matrix2<int> m{
            {1, 2, 3},
            {4, 5, 6}
        };

        m.translate(r4::vector2<int>{3, 4});

        ASSERT_ALWAYS(m[0][0] == 1) ASSERT_ALWAYS(m[0][1] == 2) ASSERT_ALWAYS(m[0][2] == 14)
        ASSERT_ALWAYS(m[1][0] == 4) ASSERT_ALWAYS(m[1][1] == 5) ASSERT_ALWAYS(m[1][2] == 38)
    }

    // test rotate(a)
    {
        r4::matrix2<float> m{
            {1, 2, 3},
            {4, 5, 6}
        };

        float a = utki::pi<float>() / 6;

        decltype(m) res(m);
        res.rotate(a);

        using std::sin;
        using std::cos;

        r4::matrix2<float> rot{
            {cos(a), -sin(a), 0},
            {sin(a), cos(a), 0}
        };

        auto cmp = m * rot;

        cmp *= 1000.0f;
        res *= 1000.0f;

        ASSERT_INFO_ALWAYS(res.to<int>() == cmp.to<int>(), "res = " << res << " cmp = " << cmp)
    }

	// test det()
	{
		r4::matrix2<int> m{
                { 10, 20, 30 },
                { 40, 50, 60 }
            };
		
		ASSERT_ALWAYS(m.det() == -300)
	}

	// test inv()
	{
		r4::matrix2<float> m{
		 	{1, 3, 5},
			{2, 3, 1},
		};

		auto i = m * m.inv();

		const float epsilon = 1e-6;

		auto diff = decltype(m)().set_identity() - i;

		diff.snap_to_zero(epsilon);

		ASSERT_INFO_ALWAYS(diff == decltype(m)().set(0), std::endl << "i = " << i.snap_to_zero(epsilon) << std::endl << "diff = " << diff)
	}
}
