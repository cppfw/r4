#include <tst/set.hpp>
#include <tst/check.hpp>

#include "../../../src/r4/rectangle.hpp"

// declare templates to instantiate all template methods to include all methods to gcov coverage
template class r4::rectangle<int>;

namespace{
const tst::set set("rectangle", [](tst::suite& suite){
    suite.add("constructor__x_y_w_h", []{
        r4::rectangle<int> r{3, 4, 5, 6};

		tst::check_eq(r.p.x(), 3, SL);
		tst::check_eq(r.p.y(), 4, SL);
		tst::check_eq(r.d.x(), 5, SL);
		tst::check_eq(r.d.y(), 6, SL);
    });

    suite.add("constructor__vector2_vector2", []{
        r4::rectangle<int> r{ {3, 4}, {5, 6} };

		tst::check_eq(r.p.x(), 3, SL);
		tst::check_eq(r.p.y(), 4, SL);
		tst::check_eq(r.d.x(), 5, SL);
		tst::check_eq(r.d.y(), 6, SL);
    });

	suite.add<std::pair<r4::segment2<int>, r4::rectangle<int>>>(
		"constructor__segment",
		{
			{
				{{10, 20}, {30, 50}}, // segment
				{{10, 20}, {20, 30}} // rectangle
			},
			{
				{{30, 50}, {10, 20}}, // segment
				{{10, 20}, {20, 30}} // rectangle
			},
			{
				{{10, 50}, {20, 30}}, // segment
				{{10, 30}, {10, 20}} // rectangle
			},
			{
				{{30, 20}, {10, 50}}, // segment
				{{10, 20}, {20, 30}} // rectangle
			},
		},
		[](const auto& p){
			r4::rectangle<int> r(p.first);
			tst::check_eq(r, p.second, SL);
		}
	);

    suite.add("center", []{
        r4::rectangle<int> r{ {3, 4}, {6, 8} };

		r4::vector2<int> cmp{6, 8};
	    tst::check_eq(r.center(), cmp, SL);
    });

    suite.add("move_center_to", []{
        r4::rectangle<int> r{ {3, 4}, {6, 8} };

		r4::vector2<int> cmp{1, 2};

		r.move_center_to(cmp);
		tst::check_eq(r.center(), cmp, SL);
    });

    suite.add("overlaps_vector2", []{
        r4::rectangle<int> r{ {3, 4}, {6, 8} };

		std::array<r4::vector2<int>, 9> p = {{
			r4::vector2<int>{1, 2}, r4::vector2<int>{5, 3}, r4::vector2<int>{10 ,3},
			r4::vector2<int>{2, 5}, r4::vector2<int>{5, 7}, r4::vector2<int>{11, 7},
			r4::vector2<int>{-1, 13}, r4::vector2<int>{7, 14}, r4::vector2<int>{13, 17}
		}};

		tst::check(!r.overlaps(p[0]), SL);
		tst::check(!r.overlaps(p[1]), SL);
		tst::check(!r.overlaps(p[2]), SL);
		tst::check(!r.overlaps(p[3]), SL);
		tst::check(r.overlaps(p[4]), SL);
		tst::check(!r.overlaps(p[5]), SL);
		tst::check(!r.overlaps(p[6]), SL);
		tst::check(!r.overlaps(p[7]), SL);
		tst::check(!r.overlaps(p[8]), SL);
    });

	suite.add<std::pair<r4::rectangle<int>, r4::rectangle<int>>>(
		"contains__rectangle__true",
		{
			{{{10, 20},{30, 40}}, {{10, 20},{30, 40}}},
			{{{10, 20},{30, 40}}, {{11, 20},{29, 40}}},
			{{{10, 20},{30, 40}}, {{11, 21},{29, 39}}},
		},
		[](const auto& p){
			tst::check(p.first.contains(p.second), SL);
		}
	);

	suite.add<std::pair<r4::rectangle<int>, r4::rectangle<int>>>(
		"contains__rectangle__false",
		{
			{{{10, 20},{30, 40}}, {{11, 20},{30, 40}}},
			{{{10, 20},{30, 40}}, {{9, 20},{30, 40}}},
			{{{10, 20},{30, 40}}, {{10, 21},{30, 40}}},
			{{{10, 20},{30, 40}}, {{10, 19},{30, 40}}},
		},
		[](const auto& p){
			tst::check(!p.first.contains(p.second), SL);
		}
	);

    suite.add("intersect_rectangle", []{
        r4::rectangle<int> r{ {3, 4}, {6, 8} };
		r4::rectangle<int> r1{ {5, 6}, {6, 8} };

		r.intersect(r1);

		r4::rectangle<int> cmp{ {5, 6}, {4, 6} };

		tst::check_eq(r, cmp, SL);
    });

    suite.add("intersect_zero_rectangle_with_non_zero_rectangle_should_result_in_zero_rectangle", []{
        r4::rectangle<unsigned> r{ 0, 0 };
		r4::rectangle<unsigned> r1{ 289, 3, 149, 248 };

		r.intersect(r1);

		tst::check(r.d.is_zero(), SL);
    });

    suite.add("unite", []{
        r4::rectangle<int> r0{ {3, 4}, {6, 8} };
		r4::rectangle<int> r1{ {5, 6}, {6, 8} };

		r0.unite(r1);

		r4::rectangle<int> cmp{ {3, 4}, {8, 10} };

		tst::check_eq(r0, cmp, SL);
    });

    suite.add("pdx_pdy", []{
        r4::rectangle<int> r{ {3, 4}, {6, 8} };

		r4::vector2<int> cmp{9, 12};

		tst::check_eq(r.x2_y2(), cmp, SL);
    });

    suite.add("x_pdy", []{
        r4::rectangle<int> r{ {3, 4}, {6, 8} };

		r4::vector2<int> cmp{3, 12};

		tst::check_eq(r.x1_y2(), cmp, SL);
    });

    suite.add("pdy", []{
        r4::rectangle<int> r{ {3, 4}, {6, 8} };

		tst::check_eq(r.y2(), 12, SL);
    });

    suite.add("pdx", []{
        r4::rectangle<int> r{ {3, 4}, {6, 8} };

		tst::check_eq(r.x2(), 9, SL);
    });

    suite.add("pdx_y", []{
        r4::rectangle<int> r{ {3, 4}, {6, 8} };

		r4::vector2<int> cmp{9, 4};

		tst::check_eq(r.x2_y1(), cmp, SL);
    });

    suite.add("to", []{
        r4::rectangle<float> r{ {3.3f, 4.4f}, {6.6f, 8.8f} };
		r4::rectangle<int> cmp{ {3, 4}, {6, 8} };

		tst::check_eq(r.to<int>(), cmp, SL);
    });

    suite.add("operator_equals_rectangle", []{
        r4::rectangle<int> r{3, 4, 5, 6};

		r4::rectangle<int> r2{5, 6, 7, 8};

		r = r2;

		tst::check_eq(r, r2, SL);
    });
});
}
