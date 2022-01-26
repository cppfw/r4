#include <tst/set.hpp>
#include <tst/check.hpp>

#include "../../../src/r4/vector.hpp"

// declare templates to instantiate all template methods to include all methods to gcov coverage
template class r4::vector<int, 3>;

namespace{
tst::set set("vector3", [](tst::suite& suite){
    suite.add("constructor_x_y_z", []{
        r4::vector3<int> v{3, 4, 5};

		tst::check_eq(v[0], 3, SL);
		tst::check_eq(v[1], 4, SL);
		tst::check_eq(v[2], 5, SL);
    });

    suite.add("constructor_number", []{
        r4::vector3<int> v(4);

		tst::check_eq(v[0], 4, SL);
		tst::check_eq(v[1], v[0], SL);
		tst::check_eq(v[2], v[1], SL);
    });

    suite.add("constructor_vector2_z", []{
        r4::vector2<int> v2{3, 4};

		r4::vector3<int> v3{v2, 5};

		tst::check_eq(v3[0], 3, SL);
		tst::check_eq(v3[1], 4, SL);
		tst::check_eq(v3[2], 5, SL);
    });

    suite.add("constructor_vector4", []{
        r4::vector4<int> v4{3, 4, 5, 6};

		r4::vector3<int> v3{v4};

		tst::check_eq(v3[0], 3, SL);
		tst::check_eq(v3[1], 4, SL);
		tst::check_eq(v3[2], 5, SL);
    });

    suite.add("to", []{
        r4::vector3<float> vf(1.1f, 2.2f, 3.3f);
        
        auto vi = vf.to<int>();

        tst::check_eq(vi[0], 1, SL);
        tst::check_eq(vi[1], 2, SL);
		tst::check_eq(vi[2], 3, SL);
    });

    suite.add("operator_equals_vector2", []{
        r4::vector2<int> a{3, 4};

		r4::vector3<int> b{5, 6, 7};

		b = a;

		tst::check_eq(b[0], 3, SL);
		tst::check_eq(b[1], 4, SL);
		tst::check_eq(b[2], 0, SL);
    });

    suite.add("operator_equals_number", []{
        r4::vector3<int> b{5, 6, 7};

		b = 3;

		tst::check_eq(b[0], 3, SL);
		tst::check_eq(b[1], b[0], SL);
		tst::check_eq(b[2], b[1], SL);
    });

    suite.add("set_number", []{
        r4::vector3<int> b{5, 6, 7};

		b.set(3);

		tst::check_eq(b[0], 3, SL);
		tst::check_eq(b[1], b[0], SL);
		tst::check_eq(b[2], b[1], SL);
    });

    suite.add("set_x_y_z", []{
        r4::vector3<int> b{5, 6, 7};

		b.set(3, 4, 5);

		tst::check_eq(b[0], 3, SL);
		tst::check_eq(b[1], 4, SL);
		tst::check_eq(b[2], 5, SL);
    });

    suite.add("operator_plus_equals_vector2", []{
        r4::vector2<int> a{3, 4};

		r4::vector3<int> b{5, 6, 7};

		b += a;

		tst::check_eq(b[0], 8, SL);
		tst::check_eq(b[1], 10, SL);
		tst::check_eq(b[2], 7, SL);
    });

    suite.add("operator_plus_equals_vector3", []{
        r4::vector3<int> b{5, 6, 7};

		b += r4::vector3<int>{3, 4, 5};

		tst::check_eq(b[0], 8, SL);
		tst::check_eq(b[1], 10, SL);
		tst::check_eq(b[2], 12, SL);
    });

    suite.add("operator_plus_vector3", []{
        r4::vector3<int> a{3, 4, 5};

		r4::vector3<int> b{5, 6, 7};

		auto r = a + b;

		tst::check_eq(r[0], 8, SL);
		tst::check_eq(r[1], 10, SL);
		tst::check_eq(r[2], 12, SL);
    });
	
    suite.add("operator_plus_number", [](){
        r4::vector3<int> v3{3, 4, 5};

		auto r = v3 + 5;

		tst::check_eq(r[0], 8, SL);
		tst::check_eq(r[1], 9, SL);
		tst::check_eq(r[2], 10, SL);		
    });	

    suite.add("operator_minus_equals_vector3", []{
        r4::vector3<int> b{5, 6, 7};

		b -= r4::vector3<int>{4, 3, 2};

		tst::check_eq(b[0], 1, SL);
		tst::check_eq(b[1], 3, SL);
		tst::check_eq(b[2], 5, SL);
    });

    suite.add("operator_minus_vector3", []{
        r4::vector3<int> a{3, 4, 5};

		r4::vector3<int> b{5, 7, 9};

		auto r = a - b;

		tst::check_eq(r[0], -2, SL);
		tst::check_eq(r[1], -3, SL);
		tst::check_eq(r[2], -4, SL);
    });
	
    suite.add("operator_minus_number", [](){
        r4::vector3<int> v3{1, 2, 3};

		auto r = v3 - 5;

		tst::check_eq(r[0], -4, SL);
		tst::check_eq(r[1], -3, SL);
		tst::check_eq(r[2], -2, SL);		
    });		

    suite.add("operator_minus", []{
        r4::vector3<int> v{3, 4, 5};

		auto r = -v;

		tst::check_eq(r[0], -3, SL);
		tst::check_eq(r[1], -4, SL);
		tst::check_eq(r[2], -5, SL);
    });

    suite.add("operator_multiply_equals_number", []{
        r4::vector3<int> v{3, 4, 5};

		v *= 2;

		tst::check_eq(v[0], 6, SL);
		tst::check_eq(v[1], 8, SL);
		tst::check_eq(v[2], 10, SL);
    });

    suite.add("operator_multiply_number", []{
        r4::vector3<int> v{3, 4, 5};

		auto r = v * 2;

		tst::check_eq(r[0], 6, SL);
		tst::check_eq(r[1], 8, SL);
		tst::check_eq(r[2], 10, SL);
    });

    suite.add("operator_multiply_number_vector3", []{
        r4::vector3<int> v{3, 4, 5};

		auto r = 2 * v;

		tst::check_eq(r[0], 6, SL);
		tst::check_eq(r[1], 8, SL);
		tst::check_eq(r[2], 10, SL);
    });

    suite.add("operator_divide_equals_number", []{
        r4::vector3<int> v{4, 8, 12};

		v /= 2;

		tst::check_eq(v[0], 2, SL);
		tst::check_eq(v[1], 4, SL);
		tst::check_eq(v[2], 6, SL);
    });

    suite.add("operator_divide_number", []{
        r4::vector3<int> v{4, 8, 12};

		auto r = v / 2;

		tst::check_eq(r[0], 2, SL);
		tst::check_eq(r[1], 4, SL);
		tst::check_eq(r[2], 6, SL);
    });

    suite.add("operator_multiply_vector3", []{
        r4::vector3<int> a{3, 4, 5};
		r4::vector3<int> b{6, 7, 8};

		auto r = a * b;

		tst::check_eq(r, 3 * 6 + 4 * 7 + 5 * 8, SL);
    });

    suite.add("comp_mul_vector3", []{
        r4::vector3<int> a{3, 4, 5};
		r4::vector3<int> b{6, 7, 8};

		auto r = a.comp_mul(b);

		tst::check_eq(r[0], 3 * 6, SL);
		tst::check_eq(r[1], 4 * 7, SL);
		tst::check_eq(r[2], 5 * 8, SL);
    });

    suite.add("comp_multiply_vector3", []{
        r4::vector3<int> a{3, 4, 5};
		r4::vector3<int> b{6, 7, 8};

		a.comp_multiply(b);

		tst::check_eq(a[0], 3 * 6, SL);
		tst::check_eq(a[1], 4 * 7, SL);
		tst::check_eq(a[2], 5 * 8, SL);
    });

    suite.add("comp_div_vector3", []{
        r4::vector3<int> a{6, 15, 24};
		r4::vector3<int> b{3, 5, 6};

		auto r = a.comp_div(b);

		tst::check_eq(r[0], 2, SL);
		tst::check_eq(r[1], 3, SL);
		tst::check_eq(r[2], 4, SL);
    });

    suite.add("comp_divide_vector3", []{
        r4::vector3<int> a{6, 15, 24};

		a.comp_divide(r4::vector3<int>{3, 5, 6});

		tst::check_eq(a[0], 2, SL);
		tst::check_eq(a[1], 3, SL);
		tst::check_eq(a[2], 4, SL);
    });

    suite.add("operator_percent_vector3", []{
        r4::vector3<int> a{3, 4, 5};
		r4::vector3<int> b{6, 7, 8};

		auto r = a % b;

		tst::check_eq(r[0], -3, SL);
		tst::check_eq(r[1], 6, SL);
		tst::check_eq(r[2], -3, SL);
    });

    suite.add<std::pair<r4::vector3<int>, bool>>(
        "is_zero",
        {
            {{0, 0, 0}, true},
            {{3, 0, 0}, false},
            {{0, -4, 0}, false},
            {{0, 0, 7}, false},
            {{3, -4, 1}, false},
        },
        [](const auto& p){
            tst::check_eq(p.first.is_zero(), p.second, SL);
        }
    );

    suite.add("negate", []{
        r4::vector3<int> a{3, -4, 7};

		a.negate();

		tst::check_eq(a[0], -3, SL);
		tst::check_eq(a[1], 4, SL);
		tst::check_eq(a[2], -7, SL);
    });

    suite.add("norm_pow2", []{
        r4::vector3<int> v{3, 4, 5};

		auto r = v.norm_pow2();

		tst::check_eq(r, 3 * 3 + 4 * 4 + 5 * 5, SL);
    });

    suite.add("norm", []{
        r4::vector3<float> v{2, 3, 4};

		auto r = v.norm() * 1000.0f;

		tst::check_eq(int(r), 5385, SL);
    });

    suite.add("normalize", []{
        r4::vector3<float> v{2, 3, 4};

		v.normalize();

		v *= 1000.0f;

		auto r = v.to<int>();

		tst::check_eq(r[0], 371, SL);
		tst::check_eq(r[1], 557, SL);
		tst::check_eq(r[2], 742, SL);
    });

    suite.add("project_vector3", []{
        r4::vector3<float> a{2, 3, 4};
		r4::vector3<float> b{5, 6, 7};

		a.project(b);

		a *= 1000.0f;

		auto r = a.to<int>();

		tst::check_eq(r[0], 2545, SL);
		tst::check_eq(r[1], 3054, SL);
		tst::check_eq(r[2], 3563, SL);
    });

    suite.add("rotate_quaternion", []{
        r4::vector3<float> a{2, 3, 4};

		a.rotate(r4::quaternion<float>{r4::vector3<float>{1, 2, 3}}) *= 1000.0f;

		auto r = a.to<int>();

		tst::check_eq(r[0], 1107, SL);
		tst::check_eq(r[1], 2437, SL);
		tst::check_eq(r[2], 4672, SL);
    });

    suite.add("min_vector3_vector3", []{
        r4::vector3<int> a{2, 3, 4};
		r4::vector3<int> b{5, 1, -5};

		auto r = min(a, b);

		tst::check_eq(r[0], 2, SL);
		tst::check_eq(r[1], 1, SL);
		tst::check_eq(r[2], -5, SL);
    });

    suite.add("max_vector3_vector3", []{
        r4::vector3<int> a{2, 3, -4};
		r4::vector3<int> b{5, 1, -5};

		auto r = max(a, b);

		tst::check_eq(r[0], 5, SL);
		tst::check_eq(r[1], 3, SL);
		tst::check_eq(r[2], -4, SL);
    });
});
}
