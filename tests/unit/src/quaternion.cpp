#include <tst/set.hpp>
#include <tst/check.hpp>

#include "../../../src/r4/quaternion.hpp"

namespace{
tst::set set("quaternion", [](tst::suite& suite){
    suite.add("constructor_x_y_z_w", []{
        r4::quaternion<int> a{3, 4, 5, 6};

		tst::check_eq(a[0], 3, SL);
		tst::check_eq(a[1], 4, SL);
		tst::check_eq(a[2], 5, SL);
		tst::check_eq(a[3], 6, SL);
    });

    suite.add("constructor_vector3", []{
        r4::quaternion<float> q{r4::vector3<float>{3, 4, 5}};
		q *= 1000.0f;
		auto r = q.to<int>();

		tst::check_eq(r[0], -162, SL);
		tst::check_eq(r[1], -217, SL);
		tst::check_eq(r[2], -271, SL);
		tst::check_eq(r[3], -923, SL);
    });

    suite.add("to", []{
        r4::quaternion<float> qf(1.1f, 2.2f, 3.3f, 4.4f);
        
        auto qi = qf.to<int>();

        tst::check_eq(qi[0], 1, SL);
        tst::check_eq(qi[1], 2, SL);
		tst::check_eq(qi[2], 3, SL);
		tst::check_eq(qi[3], 4, SL);
    });

    suite.add("operator_exclamation_mark", []{
        r4::quaternion<int> a{3, 4, 5, 6};

		auto r = !a;

		tst::check_eq(r[0], -3, SL);
		tst::check_eq(r[1], -4, SL);
		tst::check_eq(r[2], -5, SL);
		tst::check_eq(r[3], 6, SL);
    });

    suite.add("operator_plus_equals_quaternion", []{
        r4::quaternion<int> a{3, 4, 5, 6};

		a += r4::quaternion<int>{1, 2, 3, 4};

		tst::check_eq(a[0], 4, SL);
		tst::check_eq(a[1], 6, SL);
		tst::check_eq(a[2], 8, SL);
		tst::check_eq(a[3], 10, SL);
    });

    suite.add("operator_plus_quaternion", []{
        r4::quaternion<int> a{3, 4, 5, 6};

		auto r = a + r4::quaternion<int>{1, 2, 3, 4};

		tst::check_eq(r[0], 4, SL);
		tst::check_eq(r[1], 6, SL);
		tst::check_eq(r[2], 8, SL);
		tst::check_eq(r[3], 10, SL);
    });

    suite.add("operator_multiply_equals_number", []{
        r4::quaternion<int> a{3, 4, 5, 6};

		a *= 3;

		tst::check_eq(a[0], 9, SL);
		tst::check_eq(a[1], 12, SL);
		tst::check_eq(a[2], 15, SL);
		tst::check_eq(a[3], 18, SL);
    });

    suite.add("operator_multiply_number", []{
        r4::quaternion<int> a{3, 4, 5, 6};

		auto r = a * 3;

		tst::check_eq(r[0], 9, SL);
		tst::check_eq(r[1], 12, SL);
		tst::check_eq(r[2], 15, SL);
		tst::check_eq(r[3], 18, SL);
    });

    suite.add("operator_multiply_number_quaternion", []{
        r4::quaternion<int> a{3, 4, 5, 6};

		auto r = 3 * a;

		tst::check_eq(r[0], 9, SL);
		tst::check_eq(r[1], 12, SL);
		tst::check_eq(r[2], 15, SL);
		tst::check_eq(r[3], 18, SL);
    });

    suite.add("operator_divide_equals_number", []{
        r4::quaternion<int> a{9, 12, 15, 18};

		a /= 3;

		tst::check_eq(a[0], 3, SL);
		tst::check_eq(a[1], 4, SL);
		tst::check_eq(a[2], 5, SL);
		tst::check_eq(a[3], 6, SL);
    });

    suite.add("operator_divide_number", []{
        r4::quaternion<int> a{9, 12, 15, 18};

		auto r = a / 3;

		tst::check_eq(r[0], 3, SL);
		tst::check_eq(r[1], 4, SL);
		tst::check_eq(r[2], 5, SL);
		tst::check_eq(r[3], 6, SL);
    });

    suite.add("operator_multiply_quaternion", []{
        r4::quaternion<int> a{3, 4, 5, 6};
		r4::quaternion<int> b{1, 2, 3, 4};

		auto r = a * b;

		tst::check_eq(r, 3 * 1 + 4 * 2 + 5 * 3 + 6 * 4, SL);
    });

    suite.add("operator_percent_equals_quaternion", []{
        r4::quaternion<int> a{3, 4, 5, 6};
		r4::quaternion<int> b{1, 2, 3, 4};

		a %= b;

		tst::check_eq(a[0], 20, SL);
		tst::check_eq(a[1], 24, SL);
		tst::check_eq(a[2], 40, SL);
		tst::check_eq(a[3], -2, SL);
    });

    suite.add("operator_percent_quaternion", []{
        r4::quaternion<int> a{3, 4, 5, 6};
		r4::quaternion<int> b{1, 2, 3, 4};

		auto r = a % b;

		tst::check_eq(r[0], 20, SL);
		tst::check_eq(r[1], 24, SL);
		tst::check_eq(r[2], 40, SL);
		tst::check_eq(r[3], -2, SL);
    });

    suite.add("set_identity", []{
        r4::quaternion<int> a{3, 4, 5, 6};

		a.set_identity();

		tst::check_eq(a[0], 0, SL);
		tst::check_eq(a[1], 0, SL);
		tst::check_eq(a[2], 0, SL);
		tst::check_eq(a[3], 1, SL);
    });

    suite.add("conjugate", []{
        r4::quaternion<int> a{3, 4, 5, 6};

		a.conjugate();

		tst::check_eq(a[0], -3, SL);
		tst::check_eq(a[1], -4, SL);
		tst::check_eq(a[2], -5, SL);
		tst::check_eq(a[3], 6, SL);
    });

    suite.add("negate", []{
        r4::quaternion<int> a{3, 4, 5, 6};

		a.negate();

		tst::check_eq(a[0], -3, SL);
		tst::check_eq(a[1], -4, SL);
		tst::check_eq(a[2], -5, SL);
		tst::check_eq(a[3], -6, SL);
    });

    suite.add("norm_pow2", []{
        r4::quaternion<int> a{3, 4, 5, 6};

		auto r = a.norm_pow2();

		tst::check_eq(r, 3 * 3 + 4 * 4 + 5 * 5 + 6 * 6, SL);
    });

    suite.add("norm", []{
        r4::quaternion<float> a{3, 4, 5, 6};

		auto r = a.norm();

		using std::sqrt;
		tst::check_eq(int(r), int(sqrt(3 * 3 + 4 * 4 + 5 * 5 + 6 * 6)), SL);
    });

    suite.add("normalize", []{
        r4::quaternion<float> a{3, 4, 5, 6};

		a.normalize();

		a *= 1000.0f;

		auto r = a.to<int>();

		tst::check_eq(r[0], 323, SL);
		tst::check_eq(r[1], 431, SL);
		tst::check_eq(r[2], 539, SL);
		tst::check_eq(r[3], 646, SL);
    });

    suite.add("set_rotation_x_y_z_a", []{
        r4::quaternion<float> a{3, 4, 5, 6};

		a.set_rotation(1, 2, 3, 4);

		a *= 1000.0f;

		auto r = a.to<int>();

		tst::check_eq(r[0], 909, SL);
		tst::check_eq(r[1], 1818, SL);
		tst::check_eq(r[2], 2727, SL);
		tst::check_eq(r[3], -416, SL);
    });

    suite.add("set_rotation_vector3_angle", []{
        r4::quaternion<float> a{3, 4, 5, 6};

		a.set_rotation(r4::vector3<float>{1, 2, 3}, 4);

		a *= 1000.0f;

		auto r = a.to<int>();

		tst::check_eq(r[0], 909, SL);
		tst::check_eq(r[1], 1818, SL);
		tst::check_eq(r[2], 2727, SL);
		tst::check_eq(r[3], -416, SL);
    });

    suite.add_disabled("to_matrix4", []{
        // TODO: test to_matrix4()
    });

    suite.add_disabled("slerp_quaternion_t", []{
        // TODO: test slerp(quaternion, t)
    });
});
}
