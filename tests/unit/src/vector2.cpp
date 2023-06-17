#include <tst/set.hpp>
#include <tst/check.hpp>

#include "../../../src/r4/vector.hpp"

// declare templates to instantiate all template methods to include all methods to gcov coverage
template class r4::vector<int, 2>;

namespace{
const tst::set set("vector2", [](tst::suite& suite){
    suite.add("constructor_x_y", [](){
        r4::vector2<int> v{2, 3};

		tst::check_eq(v[0], 2, SL);
		tst::check_eq(v[1], 3, SL);
    });

    suite.add("constructor_xy", [](){
        r4::vector2<int> v(3);

		tst::check_eq(v[0], 3, SL);
		tst::check_eq(v[1], 3, SL);
    });

    suite.add("constructor_vector3", [](){
        r4::vector3<int> v3{3, 4, 5};

		r4::vector2<int> v2{v3};

		tst::check_eq(v2[0], 3, SL);
		tst::check_eq(v2[1], 4, SL);
    });

	suite.add("constructor_number", [](){
		r4::vector2<int> v(13);

		tst::check_eq(v[0], 13, SL);
		tst::check_eq(v[1], v[0], SL);
	});

    suite.add("to", [](){
        r4::vector2<float> vf{4.4f, 5.5f};

		auto vi = vf.to<int>();

		tst::check_eq(vi[0], 4, SL);
		tst::check_eq(vi[1], 5, SL);
    });

    suite.add("operator_equals_vector3", [](){
        r4::vector3<int> v3{3, 4, 5};

		r4::vector2<int> v2(0);

		v2 = v3;

		tst::check_eq(v2[0], 3, SL);
		tst::check_eq(v2[1], 4, SL);
    });

    suite.add("operator_plus_vector3", [](){
        r4::vector3<int> v3{3, 4, 5};

		r4::vector2<int> v2{1, 2};

		auto r = v2 + v3;

		tst::check_eq(r[0], 4, SL);
		tst::check_eq(r[1], 6, SL);
    });

    suite.add("operator_plus_equals_vecotr2", [](){
        r4::vector2<int> v{1, 2};

		v += r4::vector2<int>{3, 4};

		tst::check_eq(v[0], 4, SL);
		tst::check_eq(v[1], 6, SL);
    });

    suite.add("operator_plus_vector2", [](){
        r4::vector2<int> v2_0{3, 4};

		r4::vector2<int> v2{1, 2};

		auto r = v2 + v2_0;

		tst::check_eq(r[0], 4, SL);
		tst::check_eq(r[1], 6, SL);
    });

    suite.add("operator_plus_number", [](){
        r4::vector2<int> v2{3, 4};

		auto r = v2 + 5;

		tst::check_eq(r[0], 8, SL);
		tst::check_eq(r[1], 9, SL);
    });

    suite.add("operator_minus_equals_vector2", []{
        r4::vector2<int> v2{1, 2};

		v2 -= r4::vector2<int>{3, 5};

		tst::check_eq(v2[0], -2, SL);
		tst::check_eq(v2[1], -3, SL);
    });

    suite.add("operator_minus_vector2", []{
        r4::vector2<int> v2_0{3, 5};

		r4::vector2<int> v2{1, 2};

		auto r = v2 - v2_0;

		tst::check_eq(r[0], -2, SL);
		tst::check_eq(r[1], -3, SL);
    });

    suite.add("operator_minus_vector3", []{
        r4::vector3<int> v3{3, 5, 6};

		r4::vector2<int> v2{1, 2};

		auto r = v2 - v3;

		tst::check_eq(r[0], -2, SL);
		tst::check_eq(r[1], -3, SL);
    });
	
    suite.add("operator_minus_number", [](){
        r4::vector2<int> v2{1, 2};

		auto r = v2 - 5;

		tst::check_eq(r[0], -4, SL);
		tst::check_eq(r[1], -3, SL);
    });	

    suite.add("operator_minus", []{
        auto r = -r4::vector2<int>{1, 2};

		tst::check_eq(r[0], -1, SL);
		tst::check_eq(r[1], -2, SL);
    });

    suite.add("operator_multiply_equals_number", []{
        r4::vector2<int> v2{2, 3};

		v2 *= 3;

		tst::check_eq(v2[0], 6, SL);
		tst::check_eq(v2[1], 9, SL);
    });

    suite.add("operator_multiply_number", []{
        r4::vector2<int> v2{2, 3};

		auto r = v2 * 3;

		tst::check_eq(r[0], 6, SL);
		tst::check_eq(r[1], 9, SL);
    });

    suite.add("operator_multiply_number_vector2", []{
        r4::vector2<int> v2{2, 3};

		auto r = 3 * v2;

		tst::check_eq(r[0], 6, SL);
		tst::check_eq(r[1], 9, SL);
    });

    suite.add("min_vector2_vector2", []{
        r4::vector2<int> a{2, 3};
		r4::vector2<int> b{5, 1};

		auto r = min(a, b);

		tst::check_eq(r[0], 2, SL);
		tst::check_eq(r[1], 1, SL);
    });

    suite.add("max_vector2_vector2", []{
        r4::vector2<int> a{2, 3};
		r4::vector2<int> b{5, 1};

		auto r = max(a, b);

		tst::check_eq(r[0], 5, SL);
		tst::check_eq(r[1], 3, SL);
    });

    suite.add("operator_divide_equals_number", []{
        r4::vector2<int> v2{6, 9};

		v2 /= 3;

		tst::check_eq(v2[0], 2, SL);
		tst::check_eq(v2[1], 3, SL);
    });

    suite.add("operator_divide_number", []{
        r4::vector2<int> v2{6, 9};

		auto r = v2 / 3;

		tst::check_eq(r[0], 2, SL);
		tst::check_eq(r[1], 3, SL);
    });

    suite.add("operator_multiply_vector2", []{
        r4::vector2<int> a{3, 4};
		r4::vector2<int> b{5, 6};

		auto r = a * b;

		tst::check_eq(r, 3 * 5 + 4 * 6, SL);
    });

    suite.add("comp_mul_vector2", []{
        r4::vector2<int> a{3, 4};
		r4::vector2<int> b{5, 6};

		auto r = a.comp_mul(b);

		tst::check_eq(r[0], 15, SL);
		tst::check_eq(r[1], 24, SL);
    });

    suite.add("comp_multiply_vector2", []{
        r4::vector2<int> a{3, 4};

		a.comp_multiply(r4::vector2<int>{5, 6});

		tst::check_eq(a[0], 15, SL);
		tst::check_eq(a[1], 24, SL);
    });

    suite.add("comp_div_vector2", []{
        r4::vector2<int> a{6, 15};
		r4::vector2<int> b{3, 5};

		auto r = a.comp_div(b);

		tst::check_eq(r[0], 2, SL);
		tst::check_eq(r[1], 3, SL);
    });

    suite.add("comp_divide_vector2", []{
        r4::vector2<int> a{6, 15};

		a.comp_divide(r4::vector2<int>{3, 5});

		tst::check_eq(a[0], 2, SL);
		tst::check_eq(a[1], 3, SL);
    });

    suite.add<std::pair<r4::vector2<int>, bool>>(
        "is_zero",
        {
            {{0, 0}, true},
            {{0, 3}, false},
            {{6, 0}, false},
            {{4, 3}, false},
            {{-4, 3}, false},
            {{-4, -4}, false},
            {{4, -3}, false},
        },
        [](const auto& p){
            tst::check_eq(p.first.is_zero(), p.second, SL);
        }
    );

    suite.add<std::pair<r4::vector2<int>, bool>>(
        "is_any_zero",
        {
            {{0, 0}, true},
            {{0, 3}, true},
            {{6, 0}, true},
            {{4, 3}, false},
            {{-4, 3}, false},
            {{-4, -4}, false},
            {{4, -3}, false},
        },
        [](const auto& p){
            tst::check_eq(p.first.is_any_zero(), p.second, SL);
        }
    );
    
    suite.add<std::pair<r4::vector2<int>, bool>>(
        "is_positive_or_zero",
        {
            {{0, 0}, true},
            {{0, 3}, true},
            {{6, 0}, true},
            {{4, 3}, true},
            {{0, -3}, false},
            {{-6, 0}, false},
            {{-4, -3}, false},
        },
        [](const auto& p){
            tst::check_eq(p.first.is_positive_or_zero(), p.second, SL);
        }
    );

    suite.add<std::pair<r4::vector2<int>, bool>>(
        "is_positive",
        {
            {{0, 0}, false},
            {{0, 3}, false},
            {{6, 0}, false},
            {{4, 3}, true},
            {{0, -3}, false},
            {{-6, 0}, false},
            {{-4, -3}, false},
        },
        [](const auto& p){
            tst::check_eq(p.first.is_positive(), p.second, SL);
        }
    );

    suite.add<std::pair<r4::vector2<int>, bool>>(
        "is_negative",
        {
            {{0, 0}, false},
            {{0, 3}, false},
            {{6, 0}, false},
            {{4, 3}, false},
            {{0, -3}, false},
            {{-6, 0}, false},
            {{-4, -3}, true},
        },
        [](const auto& p){
            tst::check_eq(p.first.is_negative(), p.second, SL);
        }
    );

    suite.add("negate", []{
        r4::vector2<int> v{13, -14};
        tst::check(!v.is_negative(), SL);

        v.negate();

        tst::check(!v.is_negative(), SL);
        tst::check_eq(v.x(), -13, SL);
        tst::check_eq(v.y(), 14, SL);
    });

    suite.add("abs", []{
        r4::vector2<int> v{-13, -14};

		using std::abs;

		tst::check(!v.is_positive_or_zero(), SL);
		tst::check(abs(v).is_positive_or_zero(), SL);
    });

    suite.add("norm_pow2", []{
        r4::vector2<int> v{3, 4};

		tst::check_eq(v.norm_pow2(), 25, SL);
    });

    suite.add("norm", []{
        r4::vector2<float> v{3.0f, 4.0f};

		tst::check_eq(v.norm(), 5.0f, SL);
    });

    suite.add("normalize", []{
        r4::vector2<float> v{3.0f, 4.0f};

		v.normalize();

		tst::check_eq(v[0], 0.6f, SL);
		tst::check_eq(v[1], 0.8f, SL);
    });

    suite.add("normed", []{
        r4::vector2<float> v{3.0f, 4.0f};

		auto r = v.normed();

		tst::check_eq(r[0], 0.6f, SL);
		tst::check_eq(r[1], 0.8f, SL);
    });

    suite.add("set_number", []{
        r4::vector2<int> v{3, 4};

		v.set(5);

		tst::check_eq(v[0], 5, SL);
		tst::check_eq(v[1], v[0], SL);
    });

    suite.add("set_x_y", []{
        r4::vector2<int> v{3, 4};

		v.set(5, 6);

		tst::check_eq(v[0], 5, SL);
		tst::check_eq(v[1], 6, SL);
    });

    suite.add("rotate_angle", []{
        r4::vector2<float> v{41.0f, 30.0f};

		v.rotate(utki::pi<float>() / 6);

		auto r = v.to<int>();

		tst::check_eq(r[0], 20, SL);
		tst::check_eq(r[1], 46, SL);
    });

    suite.add("rotated_angle", []{
        auto v = r4::vector2<float>{41.0f, 30.0f}.rot(utki::pi<float>() / 6);

		auto r = v.to<int>();

		tst::check_eq(r[0], 20, SL);
		tst::check_eq(r[1], 46, SL);
    });

    suite.add("round_vector2", []{
        using std::round;
		auto v = round(r4::vector2<float>{4.8f, 3.3f});

		auto r = v.to<int>();

		tst::check_eq(r[0], 5, SL);
		tst::check_eq(r[1], 3, SL);
    });

    suite.add("ceil_vector2", []{
        using std::ceil;
		auto v = ceil(r4::vector2<float>{4.8f, 3.3f});

		auto r = v.to<int>();

		tst::check_eq(r[0], 5, SL);
		tst::check_eq(r[1], 4, SL);
    });

    suite.add("floor_vector2", []{
        using std::floor;
		auto v = floor(r4::vector2<float>{4.8f, 3.3f});

		auto r = v.to<int>();

		tst::check_eq(r[0], 4, SL);
		tst::check_eq(r[1], 3, SL);
    });

    suite.add("variadic_args_constructor_is_not_used_to_convert_shared_ptr_to_vector", []{
        struct base{};
		struct derived : base{};

		struct ts{
			void func(const r4::vector2<float>& v){}
			void func(std::shared_ptr<const base> p){}
		} s;

		auto p = std::make_shared<const derived>();

		s.func(p);
    });
});
}
