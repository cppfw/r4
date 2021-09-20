#include <tst/set.hpp>
#include <tst/check.hpp>

#include "../../../src/r4/matrix.hpp"

using namespace std::string_literals;

namespace{
tst::set set("matrix2", [](tst::suite& suite){
    suite.add("operator_out", []{
        r4::matrix2<int> m;
		m.set_identity();

		std::stringstream ss;

		ss << m;

		auto cmp =
				"|1 0 0" "\n"
				"|0 1 0" "\n"s;

		auto str = ss.str();

        tst::check_eq(str, cmp, SL);
    });

    suite.add("constructor_vector3_vector3", []{
        r4::matrix2<int> m{
            {1, 2, 3},
            {4, 5, 6}
        };

        tst::check_eq(m[0][0], 1, SL);
        tst::check_eq(m[0][1], 2, SL);
        tst::check_eq(m[0][2], 3, SL);

        tst::check_eq(m[1][0], 4, SL);
        tst::check_eq(m[1][1], 5, SL);
        tst::check_eq(m[1][2], 6, SL);
    });

    suite.add("to", []{
        r4::matrix2<double> m0{
            {1.1, 2.2, 3.3},
            {4.4, 5.5, 6.6}
        };

        auto m = m0.to<int>();

        tst::check_eq(m[0][0], 1, SL);
        tst::check_eq(m[0][1], 2, SL);
        tst::check_eq(m[0][2], 3, SL);
        tst::check_eq(m[1][0], 4, SL);
        tst::check_eq(m[1][1], 5, SL);
        tst::check_eq(m[1][2], 6, SL);
    });

    suite.add("operator_multiply_vector2", []{
        r4::matrix2<int> m{
            {1, 2, 3},
            {4, 5, 6}
        };

        auto r = m * r4::vector2<int>{3, 4};

        tst::check_eq(r[0], 14, SL);
        tst::check_eq(r[1], 38, SL);
    });

    suite.add("transpose", []{
        r4::matrix2<int> m{
            {1, 2, 3},
            {4, 5, 6}
        };

        m.transpose();

        tst::check_eq(m[0][0], 1, SL);
		tst::check_eq(m[0][1], 4, SL);
		tst::check_eq(m[0][2], 0, SL);
        tst::check_eq(m[1][0], 2, SL);
		tst::check_eq(m[1][1], 5, SL);
		tst::check_eq(m[1][2], 0, SL);
    });

    suite.add("operator_multiply_matrix2", []{
        r4::matrix2<int> m0{
            {1, 2, 3},
            {4, 5, 6}
        };

        r4::matrix2<int> m1{
            {3, 4, 5},
            {6, 7, 8}
        };

        auto m = m0 * m1;

        tst::check_eq(m[0][0], 15, SL); tst::check_eq(m[0][1], 18, SL); tst::check_eq(m[0][2], 24, SL);
        tst::check_eq(m[1][0], 42, SL); tst::check_eq(m[1][1], 51, SL); tst::check_eq(m[1][2], 66, SL);
    });

    suite.add("operator_multiply_equals_matrix2", []{
        r4::matrix2<int> m{
            {1, 2, 3},
            {4, 5, 6}
        };

        r4::matrix2<int> m1{
            {3, 4, 5},
            {6, 7, 8}
        };

        m *= m1;

        tst::check_eq(m[0][0], 15, SL); tst::check_eq(m[0][1], 18, SL); tst::check_eq(m[0][2], 24, SL);
        tst::check_eq(m[1][0], 42, SL); tst::check_eq(m[1][1], 51, SL); tst::check_eq(m[1][2], 66, SL);
    });

    suite.add("left_multiply_matrix2", []{
        r4::matrix2<int> m1{
            {1, 2, 3},
            {4, 5, 6}
        };

        r4::matrix2<int> m{
            {3, 4, 5},
            {6, 7, 8}
        };

        m.left_mul(m1);

        tst::check_eq(m[0][0], 15, SL); tst::check_eq(m[0][1], 18, SL); tst::check_eq(m[0][2], 24, SL);
        tst::check_eq(m[1][0], 42, SL); tst::check_eq(m[1][1], 51, SL); tst::check_eq(m[1][2], 66, SL);
    });

    suite.add("set_identity", []{
        r4::matrix2<int> m{
            {3, 4, 5},
            {6, 7, 8}
        };

        m.set_identity();

        tst::check_eq(m[0][0], 1, SL); tst::check_eq(m[0][1], 0, SL); tst::check_eq(m[0][2], 0, SL);
        tst::check_eq(m[1][0], 0, SL); tst::check_eq(m[1][1], 1, SL); tst::check_eq(m[1][2], 0, SL);
    });

    suite.add("scale_x_y", []{
        r4::matrix2<int> m{
            {1, 2, 3},
            {4, 5, 6}
        };

        m.scale(3, 4);

        tst::check_eq(m[0][0], 3, SL); tst::check_eq(m[0][1], 8, SL); tst::check_eq(m[0][2], 3, SL);
        tst::check_eq(m[1][0], 12, SL); tst::check_eq(m[1][1], 20, SL); tst::check_eq(m[1][2], 6, SL);
    });

    suite.add("scale_number", []{
        r4::matrix2<int> m{
            {1, 2, 3},
            {4, 5, 6}
        };

        m.scale(3);

        tst::check_eq(m[0][0], 3, SL); tst::check_eq(m[0][1], 6, SL); tst::check_eq(m[0][2], 3, SL);
        tst::check_eq(m[1][0], 12, SL); tst::check_eq(m[1][1], 15, SL); tst::check_eq(m[1][2], 6, SL);
    });

    suite.add("scale_vector2", []{
        r4::matrix2<int> m{
            {1, 2, 3},
            {4, 5, 6}
        };

        m.scale(r4::vector2<int>{3, 4});

        tst::check_eq(m[0][0], 3, SL); tst::check_eq(m[0][1], 8, SL); tst::check_eq(m[0][2], 3, SL);
        tst::check_eq(m[1][0], 12, SL); tst::check_eq(m[1][1], 20, SL); tst::check_eq(m[1][2], 6, SL);
    });

    suite.add("translate_x_y", []{
        r4::matrix2<int> m{
            {1, 2, 3},
            {4, 5, 6}
        };

        m.translate(3, 4);

        tst::check_eq(m[0][0], 1, SL); tst::check_eq(m[0][1], 2, SL); tst::check_eq(m[0][2], 14, SL);
        tst::check_eq(m[1][0], 4, SL); tst::check_eq(m[1][1], 5, SL); tst::check_eq(m[1][2], 38, SL);
    });

    suite.add("translate_vector2", []{
        r4::matrix2<int> m{
            {1, 2, 3},
            {4, 5, 6}
        };

        m.translate(r4::vector2<int>{3, 4});

        tst::check_eq(m[0][0], 1, SL); tst::check_eq(m[0][1], 2, SL); tst::check_eq(m[0][2], 14, SL);
        tst::check_eq(m[1][0], 4, SL); tst::check_eq(m[1][1], 5, SL); tst::check_eq(m[1][2], 38, SL);
    });

    suite.add("rotate_angle", []{
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

        tst::check_eq(res.to<int>(), cmp.to<int>(), SL);
    });

    suite.add("det", []{
        r4::matrix2<int> m{
            { 10, 20, 30 },
            { 40, 50, 60 }
        };
		
		tst::check_eq(m.det(), -300, SL);
    });

    suite.add("inv", []{
        r4::matrix2<float> m{
		 	{1.0f, 3.0f, 5.0f},
			{2.0f, 3.0f, 1.0f},
		};

		auto i = m * m.inv();

		const float epsilon = 1e-6f;

		auto diff = decltype(m)().set_identity() - i;

		diff.snap_to_zero(epsilon);

		tst::check_eq(diff, decltype(m)().set(0), SL);
    });
});
}
