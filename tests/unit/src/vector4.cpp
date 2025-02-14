#include <tst/set.hpp>
#include <tst/check.hpp>

#include <utki/string.hpp>

#include "../../../src/r4/vector.hpp"

using namespace std::string_literals;

// declare templates to instantiate all template methods to include all methods to gcov coverage
template class r4::vector<int, 4>;

namespace{
const tst::set set("vector4", [](tst::suite& suite){
    suite.add("constructor_x_y_z_w", []{
        r4::vector4<int> v{3, 4, 5, 6};

		tst::check_eq(v[0], 3, SL);
		tst::check_eq(v[1], 4, SL);
		tst::check_eq(v[2], 5, SL);
		tst::check_eq(v[3], 6, SL);
    });

    suite.add("constructor_number", []{
        r4::vector4<int> v(3);

		tst::check_eq(v[0], 3, SL);
		tst::check_eq(v[1], v[0], SL);
		tst::check_eq(v[2], v[1], SL);
		tst::check_eq(v[3], v[2], SL);
    });

    suite.add("constructor_n_w", []{
        r4::vector4<int> v(3, 5);

		tst::check_eq(v[0], 3, SL);
		tst::check_eq(v[1], v[0], SL);
		tst::check_eq(v[2], v[1], SL);
		tst::check_eq(v[3], 5, SL);
    });

    suite.add("constructor_vector2_z_w", []{
        r4::vector2<int> v2{3, 4};
		r4::vector4<int> v{v2, 5, 6};

		tst::check_eq(v[0], 3, SL);
		tst::check_eq(v[1], 4, SL);
		tst::check_eq(v[2], 5, SL);
		tst::check_eq(v[3], 6, SL);
    });

    suite.add("constructor_vector3_w", []{
        r4::vector3<int> v3{3, 4, 5};
		r4::vector4<int> v{v3, 6};

		tst::check_eq(v[0], 3, SL);
		tst::check_eq(v[1], 4, SL);
		tst::check_eq(v[2], 5, SL);
		tst::check_eq(v[3], 6, SL);
    });

    suite.add("to", []{
        r4::vector4<float> vf(1.1f, 2.2f, 3.3f, 4.4f);
        
        auto vi = vf.to<int>();

        tst::check_eq(vi[0], 1, SL);
        tst::check_eq(vi[1], 2, SL);
		tst::check_eq(vi[2], 3, SL);
		tst::check_eq(vi[3], 4, SL);
    });

    suite.add("operator_equals_vector3", []{
        r4::vector4<int> v4{3, 4, 5, 6};
		r4::vector3<int> v3{7, 8, 9};

		v4 = v3;

		tst::check_eq(v4[0], 7, SL);
        tst::check_eq(v4[1], 8, SL);
		tst::check_eq(v4[2], 9, SL);
		tst::check_eq(v4[3], 0, SL);
    });

    suite.add("operator_equals_vector2", []{
        r4::vector4<int> v4{3, 4, 5, 6};
		r4::vector2<int> v2{7, 8};

		v4 = v2;

		tst::check_eq(v4[0], 7, SL);
        tst::check_eq(v4[1], 8, SL);
		tst::check_eq(v4[2], 0, SL);
		tst::check_eq(v4[3], 0, SL);
    });

    suite.add("operator_equals_number", []{
        r4::vector4<int> v4{3, 4, 5, 6};

		v4 = 8;

		tst::check_eq(v4[0], 8, SL);
        tst::check_eq(v4[1], 8, SL);
		tst::check_eq(v4[2], 8, SL);
		tst::check_eq(v4[3], 8, SL);
    });

    suite.add("set_number", []{
        r4::vector4<int> v4{3, 4, 5, 6};

		v4.set(8);

		tst::check_eq(v4[0], 8, SL);
        tst::check_eq(v4[1], 8, SL);
		tst::check_eq(v4[2], 8, SL);
		tst::check_eq(v4[3], 8, SL);
    });

    suite.add("set_x_y_z_w", []{
        r4::vector4<int> v4{3, 4, 5, 6};

		v4.set(8, 9, 10, 11);

		tst::check_eq(v4[0], 8, SL);
        tst::check_eq(v4[1], 9, SL);
		tst::check_eq(v4[2], 10, SL);
		tst::check_eq(v4[3], 11, SL);
    });

    suite.add("operator_plus_equals_vector2", []{
        r4::vector4<int> v4{3, 4, 5, 6};
		r4::vector2<int> v2{7, 8};

		v4 += v2;

		tst::check_eq(v4[0], 10, SL);
        tst::check_eq(v4[1], 12, SL);
		tst::check_eq(v4[2], 5, SL);
		tst::check_eq(v4[3], 6, SL);
    });

    suite.add("operator_plus_equals_vector3", []{
        r4::vector4<int> v4{3, 4, 5, 6};
		r4::vector3<int> v3{7, 8, 9};

		v4 += v3;

		tst::check_eq(v4[0], 10, SL);
        tst::check_eq(v4[1], 12, SL);
		tst::check_eq(v4[2], 14, SL);
		tst::check_eq(v4[3], 6, SL);
    });

    suite.add("operator_plus_equals_vector4", []{
        r4::vector4<int> v4{3, 4, 5, 6};

		v4 += r4::vector4<int>{7, 8, 9, 10};

		tst::check_eq(v4[0], 10, SL);
        tst::check_eq(v4[1], 12, SL);
		tst::check_eq(v4[2], 14, SL);
		tst::check_eq(v4[3], 16, SL);
    });

    suite.add("operator_plus_vector4", []{
        r4::vector4<int> v4{3, 4, 5, 6};

		auto r = v4 + r4::vector4<int>{7, 8, 9, 10};

		tst::check_eq(r[0], 10, SL);
        tst::check_eq(r[1], 12, SL);
		tst::check_eq(r[2], 14, SL);
		tst::check_eq(r[3], 16, SL);
    });
	
    suite.add("operator_plus_number", [](){
        r4::vector4<int> v4{3, 4, 5, 6};

		auto r = v4 + 5;

		tst::check_eq(r[0], 8, SL);
		tst::check_eq(r[1], 9, SL);
		tst::check_eq(r[2], 10, SL);	
		tst::check_eq(r[3], 11, SL);		
    });		

    suite.add("operator_minus_equals_vector4", []{
        r4::vector4<int> v4{3, 4, 5, 6};

		v4 -= r4::vector4<int>{7, 9, 11, 13};

		tst::check_eq(v4[0], -4, SL);
        tst::check_eq(v4[1], -5, SL);
		tst::check_eq(v4[2], -6, SL);
		tst::check_eq(v4[3], -7, SL);
    });

    suite.add("operator_minus_vector4", []{
        r4::vector4<int> v4{3, 4, 5, 6};

		auto r = v4 - r4::vector4<int>{7, 9, 11, 13};

		tst::check_eq(r[0], -4, SL);
        tst::check_eq(r[1], -5, SL);
		tst::check_eq(r[2], -6, SL);
		tst::check_eq(r[3], -7, SL);
    });
	
    suite.add("operator_minus_number", [](){
        r4::vector4<int> v4{1, 2, 3, 4};

		auto r = v4 - 5;

		tst::check_eq(r[0], -4, SL);
		tst::check_eq(r[1], -3, SL);
		tst::check_eq(r[2], -2, SL);
		tst::check_eq(r[3], -1, SL);
    });	

    suite.add("operator_minus", []{
        r4::vector4<int> v4{3, 4, 5, 6};

		auto r = -v4;

		tst::check_eq(r[0], -3, SL);
        tst::check_eq(r[1], -4, SL);
		tst::check_eq(r[2], -5, SL);
		tst::check_eq(r[3], -6, SL);
    });

    suite.add("operator_multiply_equals_number", []{
        r4::vector4<int> v4{3, 4, 5, 6};

		v4 *= 2;

		tst::check_eq(v4[0], 6, SL);
        tst::check_eq(v4[1], 8, SL);
		tst::check_eq(v4[2], 10, SL);
		tst::check_eq(v4[3], 12, SL);
    });

    suite.add("operator_multiply_number", []{
        r4::vector4<int> v4{3, 4, 5, 6};

		auto r = v4 * 2;

		tst::check_eq(r[0], 6, SL);
        tst::check_eq(r[1], 8, SL);
		tst::check_eq(r[2], 10, SL);
		tst::check_eq(r[3], 12, SL);
    });

    suite.add("operator_multiply_number_vector4", []{
        r4::vector4<int> v4{3, 4, 5, 6};

		auto r = 2 * v4;

		tst::check_eq(r[0], 6, SL);
        tst::check_eq(r[1], 8, SL);
		tst::check_eq(r[2], 10, SL);
		tst::check_eq(r[3], 12, SL);
    });

    suite.add("operator_divide_equals_number", []{
        r4::vector4<int> v4{6, 8, 10, 12};

		v4 /= 2;

		tst::check_eq(v4[0], 3, SL);
        tst::check_eq(v4[1], 4, SL);
		tst::check_eq(v4[2], 5, SL);
		tst::check_eq(v4[3], 6, SL);
    });

    suite.add("operator_divide_number", []{
        r4::vector4<int> v4{6, 8, 10, 12};

		auto r = v4 / 2;

		tst::check_eq(r[0], 3, SL);
        tst::check_eq(r[1], 4, SL);
		tst::check_eq(r[2], 5, SL);
		tst::check_eq(r[3], 6, SL);
    });

    suite.add("operator_multiply_vector4", []{
        r4::vector4<int> v4{3, 4, 5, 6};

		auto r = v4 * r4::vector4<int>{7, 8, 9, 10};

		tst::check_eq(r, 3 * 7 + 4 * 8 + 5 * 9 + 6 * 10, SL);
    });

    suite.add("dot_product", []{
        r4::vector4<int> v4{3, 4, 5, 6};

		auto r = v4.dot(r4::vector4<int>{7, 8, 9, 10});

		tst::check_eq(r, 3 * 7 + 4 * 8 + 5 * 9 + 6 * 10, SL);
    });

	suite.add("cross_vector4", []{
        r4::vector4<int> v4{3, 4, 5, 6};

		auto r = v4.cross({7, 8, 9, 10});

		tst::check_eq(r[0], -4, SL);
        tst::check_eq(r[1], 8, SL);
		tst::check_eq(r[2], -4, SL);
		tst::check_eq(r[3], 60, SL);
    });

    suite.add<std::pair<r4::vector4<int>, r4::vector4<int>>>(
        "operator_equals_equals_vector4_true",
        {
            {{3, 4, 5, 6}, {3, 4, 5, 6}},
            {{0, 0, 0, 0}, {0, 0, 0, 0}},
            {{-3, 4, -5, 6}, {-3, 4, -5, 6}},
        },
        [](const auto& p){
            tst::check(p.first == p.second, SL);
        }
    );

    suite.add<std::pair<r4::vector4<int>, r4::vector4<int>>>(
        "operator_equals_equals_vector4_false",
        {
            {{3, 4, 5, 6}, {3, 4, 6, 6}},
            {{0, 0, 0, 0}, {0, 0, 1, 0}},
            {{-3, 4, -5, 6}, {-3, -4, -5, 6}},
        },
        [](const auto& p){
            tst::check(!(p.first == p.second), SL);
        }
    );

    suite.add<std::pair<r4::vector4<int>, r4::vector4<int>>>(
        "operator_not_equals_vector4_false",
        {
            {{3, 4, 5, 6}, {3, 4, 5, 6}},
            {{0, 0, 0, 0}, {0, 0, 0, 0}},
            {{-3, 4, -5, 6}, {-3, 4, -5, 6}},
        },
        [](const auto& p){
            tst::check(!(p.first != p.second), SL);
        }
    );

    suite.add<std::pair<r4::vector4<int>, r4::vector4<int>>>(
        "operator_not_equals_vector4_true",
        {
            {{3, 4, 5, 6}, {3, 4, 6, 6}},
            {{0, 0, 0, 0}, {0, 0, 1, 0}},
            {{-3, 4, -5, 6}, {-3, -4, -5, 6}},
        },
        [](const auto& p){
            tst::check(p.first != p.second, SL);
        }
    );

    suite.add("operator_output__int", [](){
        r4::vector4<int> a{3, 4, 5, 6};

        std::stringstream ss;
        ss << a;

        auto s = ss.str();

        tst::check_eq(s, "3 4 5 6"s, SL);
    });

    suite.add("operator_output__uint8_t", [](){
        r4::vector4<uint8_t> a{3, 4, 5, 6};

        std::stringstream ss;
        ss << a;

        auto s = ss.str();

        tst::check_eq(s, "3 4 5 6"s, SL);
    });

    suite.add("operator_output__float", [](){
        r4::vector4<float> a{3.5, 4.6, 5.7, 6.8};

        std::stringstream ss;
        ss << a;

        auto s = ss.str();

        tst::check_eq(s, "3.5 4.6 5.7 6.8"s, SL);
    });

    suite.add("comp_op__unary__change_type", []{
        r4::vector4<int> a{3, 4, 5, 6};

        auto res = a.comp_op([](const auto& e){
            return utki::cat(e);
        });

        r4::vector4<std::string> expected = {
            "3", "4", "5", "6"
        };

        tst::check_eq(res, expected, SL);
    });

    suite.add("comp_op__binary__change_type", []{
        r4::vector4<int> a{3, 4, 5, 6};
        r4::vector4<int> b{6, 7, 8, 9};

        auto res = a.comp_op(
            b, //
            [](const auto& ea, const auto& eb){
                return utki::cat(ea, eb);
            }
        );

        r4::vector4<std::string> expected = {
            "36", "47", "58", "69"
        };

        tst::check_eq(res, expected, SL);
    });

    suite.add("comp_mul_vector4", []{
        r4::vector4<int> a{3, 4, 5, 6};
		r4::vector4<int> b{6, 7, 8, 9};

		auto r = a.comp_mul(b);

		tst::check_eq(r[0], 3 * 6, SL);
		tst::check_eq(r[1], 4 * 7, SL);
		tst::check_eq(r[2], 5 * 8, SL);
		tst::check_eq(r[3], 6 * 9, SL);
    });

    suite.add("comp_multiply_vector4", []{
        r4::vector4<int> a{3, 4, 5, 6};
		r4::vector4<int> b{6, 7, 8, 9};

		a.comp_multiply(b);

		tst::check_eq(a[0], 3 * 6, SL);
		tst::check_eq(a[1], 4 * 7, SL);
		tst::check_eq(a[2], 5 * 8, SL);
		tst::check_eq(a[3], 6 * 9, SL);
    });

    suite.add("comp_div_vector4", []{
        r4::vector4<int> a{6, 15, 24, 35};
		r4::vector4<int> b{3, 5, 6, 7};

		auto r = a.comp_div(b);

		tst::check_eq(r[0], 2, SL);
		tst::check_eq(r[1], 3, SL);
		tst::check_eq(r[2], 4, SL);
		tst::check_eq(r[3], 5, SL);
    });

    suite.add("comp_divide_vector4", []{
        r4::vector4<int> a{6, 15, 24, 35};

		a.comp_divide(r4::vector4<int>{3, 5, 6, 7});

		tst::check_eq(a[0], 2, SL);
		tst::check_eq(a[1], 3, SL);
		tst::check_eq(a[2], 4, SL);
		tst::check_eq(a[3], 5, SL);
    });

    suite.add("negate", []{
        r4::vector4<int> v4{3, 4, 5, 6};

		v4.negate();

		tst::check_eq(v4[0], -3, SL);
        tst::check_eq(v4[1], -4, SL);
		tst::check_eq(v4[2], -5, SL);
		tst::check_eq(v4[3], -6, SL);
    });

    suite.add("norm_pow2", []{
        r4::vector4<int> v4{3, 4, 5, 6};

		auto r = v4.norm_pow2();

		tst::check_eq(r, 3 * 3 + 4 * 4 + 5 * 5 + 6 * 6, SL);
    });

    suite.add("norm", []{
        r4::vector4<float> v4{3, 4, 5, 6};

		auto r = v4.norm();

		tst::check_eq(int(r), 9, SL);
    });

    suite.add("normalize", []{
        r4::vector4<float> v4{3, 4, 5, 6};

		v4.normalize();
		v4 *= 1000.0f;

		auto r = v4.to<int>();

		tst::check_eq(r[0], 323, SL);
        tst::check_eq(r[1], 431, SL);
		tst::check_eq(r[2], 539, SL);
		tst::check_eq(r[3], 646, SL);
    });

    suite.add("min_vector4_vector4", []{
        r4::vector4<int> a{2, 3, 4, -6};
		r4::vector4<int> b{5, 1, -5, -7};

		auto r = min(a, b);

		tst::check_eq(r[0], 2, SL);
		tst::check_eq(r[1], 1, SL);
		tst::check_eq(r[2], -5, SL);
		tst::check_eq(r[3], -7, SL);
    });

    suite.add("max_vector4_vector4", []{
        r4::vector4<int> a{2, 3, -4, -6};
		r4::vector4<int> b{5, 1, -5, -7};

		auto r = max(a, b);

		tst::check_eq(r[0], 5, SL);
		tst::check_eq(r[1], 3, SL);
		tst::check_eq(r[2], -4, SL);
		tst::check_eq(r[3], -6, SL);
    });
});
}
