#include <tst/set.hpp>
#include <tst/check.hpp>

#include "../../../src/r4/quaternion.hpp"

// declare templates to instantiate all template methods to include all methods to gcov coverage
template class r4::quaternion<int>;

namespace{
tst::set set("quaternion", [](tst::suite& suite){
	suite.add("constructor_vec_scalar", []{
		r4::vector3<int> v{3, 4, 5};
		r4::quaternion<int> a{v, 6};

		tst::check_eq(a.v[0], 3, SL);
		tst::check_eq(a.v[1], 4, SL);
		tst::check_eq(a.v[2], 5, SL);
		tst::check_eq(a.s, 6, SL);
	});

    suite.add("constructor_x_y_z_w", []{
        r4::quaternion<int> a{3, 4, 5, 6};

		tst::check_eq(a.v[0], 3, SL);
		tst::check_eq(a.v[1], 4, SL);
		tst::check_eq(a.v[2], 5, SL);
		tst::check_eq(a.s, 6, SL);
    });

    suite.add("constructor_vector3", []{
        r4::quaternion<float> q{r4::vector3<float>{3, 4, 5}};
		q *= 1000.0f;
		auto r = q.to<int>();

		tst::check_eq(r.v[0], -162, SL);
		tst::check_eq(r.v[1], -217, SL);
		tst::check_eq(r.v[2], -271, SL);
		tst::check_eq(r.s, -923, SL);
    });
    suite.add("to", []{
        r4::quaternion<float> qf(1.1f, 2.2f, 3.3f, 4.4f);
        
        auto qi = qf.to<int>();

        tst::check_eq(qi.v[0], 1, SL);
        tst::check_eq(qi.v[1], 2, SL);
		tst::check_eq(qi.v[2], 3, SL);
		tst::check_eq(qi.s, 4, SL);
    });

    suite.add("operator_exclamation_mark", []{
        r4::quaternion<int> a{3, 4, 5, 6};

		auto r = !a;

		tst::check_eq(r.v[0], -3, SL);
		tst::check_eq(r.v[1], -4, SL);
		tst::check_eq(r.v[2], -5, SL);
		tst::check_eq(r.s, 6, SL);
    });

    suite.add("operator_plus_equals_quaternion", []{
        r4::quaternion<int> a{3, 4, 5, 6};

		a += r4::quaternion<int>{1, 2, 3, 4};

		tst::check_eq(a.v[0], 4, SL);
		tst::check_eq(a.v[1], 6, SL);
		tst::check_eq(a.v[2], 8, SL);
		tst::check_eq(a.s, 10, SL);
    });

    suite.add("operator_plus_quaternion", []{
        r4::quaternion<int> a{3, 4, 5, 6};

		auto r = a + r4::quaternion<int>{1, 2, 3, 4};

		tst::check_eq(r.v[0], 4, SL);
		tst::check_eq(r.v[1], 6, SL);
		tst::check_eq(r.v[2], 8, SL);
		tst::check_eq(r.s, 10, SL);
    });

	suite.add("operator_minus", []{
        r4::quaternion<int> a{3, 4, 5, 6};

		auto r = -a;

		tst::check_eq(r.v[0], -3, SL);
		tst::check_eq(r.v[1], -4, SL);
		tst::check_eq(r.v[2], -5, SL);
		tst::check_eq(r.s, -6, SL);
    });

	suite.add("operator_minus_quaternion", []{
        r4::quaternion<int> a{3, 4, 5, 6};

		auto r = a - r4::quaternion<int>{1, 2, 3, 4};

		tst::check_eq(r.v[0], 2, SL);
		tst::check_eq(r.v[1], 2, SL);
		tst::check_eq(r.v[2], 2, SL);
		tst::check_eq(r.s, 2, SL);
    });

    suite.add("operator_multiply_equals_number", []{
        r4::quaternion<int> a{3, 4, 5, 6};

		a *= 3;

		tst::check_eq(a.v[0], 9, SL);
		tst::check_eq(a.v[1], 12, SL);
		tst::check_eq(a.v[2], 15, SL);
		tst::check_eq(a.s, 18, SL);
    });

    suite.add("operator_multiply_number", []{
        r4::quaternion<int> a{3, 4, 5, 6};

		auto r = a * 3;

		tst::check_eq(r.v[0], 9, SL);
		tst::check_eq(r.v[1], 12, SL);
		tst::check_eq(r.v[2], 15, SL);
		tst::check_eq(r.s, 18, SL);
    });

    suite.add("operator_multiply_number_quaternion", []{
        r4::quaternion<int> a{3, 4, 5, 6};

		auto r = 3 * a;

		tst::check_eq(r.v[0], 9, SL);
		tst::check_eq(r.v[1], 12, SL);
		tst::check_eq(r.v[2], 15, SL);
		tst::check_eq(r.s, 18, SL);
    });

    suite.add("operator_divide_equals_number", []{
        r4::quaternion<int> a{9, 12, 15, 18};

		a /= 3;

		tst::check_eq(a.v[0], 3, SL);
		tst::check_eq(a.v[1], 4, SL);
		tst::check_eq(a.v[2], 5, SL);
		tst::check_eq(a.s, 6, SL);
    });

    suite.add("operator_divide_number", []{
        r4::quaternion<int> a{9, 12, 15, 18};

		auto r = a / 3;

		tst::check_eq(r.v[0], 3, SL);
		tst::check_eq(r.v[1], 4, SL);
		tst::check_eq(r.v[2], 5, SL);
		tst::check_eq(r.s, 6, SL);
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

		tst::check_eq(a.v[0], 20, SL);
		tst::check_eq(a.v[1], 24, SL);
		tst::check_eq(a.v[2], 40, SL);
		tst::check_eq(a.s, -2, SL);
    });

    suite.add("operator_percent_quaternion", []{
        r4::quaternion<int> a{3, 4, 5, 6};
		r4::quaternion<int> b{1, 2, 3, 4};

		auto r = a % b;

		tst::check_eq(r.v[0], 20, SL);
		tst::check_eq(r.v[1], 24, SL);
		tst::check_eq(r.v[2], 40, SL);
		tst::check_eq(r.s, -2, SL);
    });

    suite.add("set_identity", []{
        r4::quaternion<int> a{3, 4, 5, 6};

		a.set_identity();

		tst::check_eq(a.v[0], 0, SL);
		tst::check_eq(a.v[1], 0, SL);
		tst::check_eq(a.v[2], 0, SL);
		tst::check_eq(a.s, 1, SL);
    });

    suite.add("conjugate", []{
        r4::quaternion<int> a{3, 4, 5, 6};

		a.conjugate();

		tst::check_eq(a.v[0], -3, SL);
		tst::check_eq(a.v[1], -4, SL);
		tst::check_eq(a.v[2], -5, SL);
		tst::check_eq(a.s, 6, SL);
    });

    suite.add("negate", []{
        r4::quaternion<int> a{3, 4, 5, 6};

		a.negate();

		tst::check_eq(a.v[0], -3, SL);
		tst::check_eq(a.v[1], -4, SL);
		tst::check_eq(a.v[2], -5, SL);
		tst::check_eq(a.s, -6, SL);
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

		tst::check_eq(r.v[0], 323, SL);
		tst::check_eq(r.v[1], 431, SL);
		tst::check_eq(r.v[2], 539, SL);
		tst::check_eq(r.s, 646, SL);
    });

    suite.add("set_rotation_x_y_z_a", []{
        r4::quaternion<float> a{3, 4, 5, 6};

		a.set_rotation(1, 2, 3, 4);

		a *= 1000.0f;

		auto r = a.to<int>();

		tst::check_eq(r.v[0], 909, SL);
		tst::check_eq(r.v[1], 1818, SL);
		tst::check_eq(r.v[2], 2727, SL);
		tst::check_eq(r.s, -416, SL);
    });

    suite.add("set_rotation_vector3_angle", []{
        r4::quaternion<float> a{3, 4, 5, 6};

		a.set_rotation(r4::vector3<float>{1, 2, 3}, 4);

		a *= 1000.0f;

		auto r = a.to<int>();

		tst::check_eq(r.v[0], 909, SL);
		tst::check_eq(r.v[1], 1818, SL);
		tst::check_eq(r.v[2], 2727, SL);
		tst::check_eq(r.s, -416, SL);
    });

	suite.add("inversion", []{
		r4::quaternion<float> a{3, 4, 5, 6};

		auto inverted = !a / a.norm_pow2();

		tst::check_eq(a.inv(), inverted, SL);

		{
			auto b = a;
			b.invert();
			tst::check_eq(b, inverted, SL);
		}
	});

	suite.add("operator_equals_equals", [](){
		r4::quaternion<float> a{3, 4, 5, 6};
		r4::quaternion<float> b{3, 4, 5, 6};

		tst::check_eq(a, b, SL);

		b.v.y() = 1;
		tst::check(!(a == b), SL);
	});

    suite.add_disabled("to_matrix4", []{
        // TODO: test to_matrix4()
    });

    suite.add<std::tuple<r4::quaternion<float>, r4::quaternion<float>, float>>(
		"slerp",
		{
			{
				r4::quaternion<float>().set_rotation(1, 0, 0, utki::pi<float>() / 2),
				r4::quaternion<float>().set_rotation(0, 1, 0, utki::pi<float>() / 2),
				0.001f
			},
			{
				r4::quaternion<float>().set_rotation(1, 0, 0, utki::pi<float>() / 2),
				r4::quaternion<float>().set_rotation(0, 1, 0, utki::pi<float>() / 2),
				0.5f
			},
			{
				r4::quaternion<float>().set_rotation(1, 0, 0, utki::pi<float>() / 2),
				r4::quaternion<float>().set_rotation(0, 1, 0, utki::pi<float>() / 2),
				0.999f
			}
		},
		[](const auto& p){
			float eps = 0.11f; // TODO: lower the epsilon to something like 0.001

			auto slow_slerp = [](r4::quaternion<float> a, r4::quaternion<float> b, float t){
				tst::check_le(t, decltype(t)(1), SL);
				tst::check_ge(t, decltype(t)(0), SL);

				// Let slerp(0) = A and slerp(1) = B, then for slerp(t) calculation:
				// c = (a^-1) % b
				// angle = acos(c.s) * t
				// slerp(t) = a % quaternion(c.v * sin(angle) / c.v.norm(), cos(angle))

				auto c = a.inv() % b;

				using std::acos;
				auto angle = acos(c.s) * t;

				using std::sin;
				using std::cos;
				return a % r4::quaternion(c.v * sin(angle) / c.v.norm(), cos(angle));
			};

			auto a = std::get<0>(p);
			auto b = std::get<1>(p);
			auto t = std::get<2>(p);

			auto slow_slerp_res = slow_slerp(a, b, t);
			auto slerp_res = a.slerp(b, t);

			auto diff = slerp_res - slow_slerp_res;

			using std::abs;
			auto abs_v = abs(diff.v);
			auto abs_s = abs(diff.s);

			tst::check_lt(abs_s, eps, SL);
			tst::check(abs_v.snap_to_zero(eps).is_zero(), SL) << "diff_v = " << diff.v;
    });
});
}
