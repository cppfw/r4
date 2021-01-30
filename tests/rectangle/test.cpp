#include <utki/debug.hpp>

#include "../../src/r4/rectangle.hpp"

void test(){
	// test constructor(x, y, w, h)
	{
		r4::rectangle<int> r{3, 4, 5, 6};

		ASSERT_ALWAYS(r.p.x() == 3)
		ASSERT_ALWAYS(r.p.y() == 4)
		ASSERT_ALWAYS(r.d.x() == 5)
		ASSERT_ALWAYS(r.d.y() == 6)
	}

	// test constructor(vector2, vector2)
	{
		r4::rectangle<int> r{ {3, 4}, {5, 6} };

		ASSERT_ALWAYS(r.p.x() == 3)
		ASSERT_ALWAYS(r.p.y() == 4)
		ASSERT_ALWAYS(r.d.x() == 5)
		ASSERT_ALWAYS(r.d.y() == 6)
	}

	// test center()
	{
		r4::rectangle<int> r{ {3, 4}, {6, 8} };

		r4::vector2<int> cmp{6, 8};
		ASSERT_INFO_ALWAYS(r.center() == cmp, "r.venter() = " << r.center())
	}

	// test move_center_to(vector2)
	{
		r4::rectangle<int> r{ {3, 4}, {6, 8} };

		r4::vector2<int> cmp{1, 2};

		r.move_center_to(cmp);
		ASSERT_INFO_ALWAYS(r.center() == cmp, "r.venter() = " << r.center())
	}

	// test overlaps(vector2)
	{
		r4::rectangle<int> r{ {3, 4}, {6, 8} };

		std::array<r4::vector2<int>, 9> p = {{
			r4::vector2<int>{1, 2}, r4::vector2<int>{5, 3}, r4::vector2<int>{10 ,3},
			r4::vector2<int>{2, 5}, r4::vector2<int>{5, 7}, r4::vector2<int>{11, 7},
			r4::vector2<int>{-1, 13}, r4::vector2<int>{7, 14}, r4::vector2<int>{13, 17}
		}};

		ASSERT_ALWAYS(!r.overlaps(p[0]))
		ASSERT_ALWAYS(!r.overlaps(p[1]))
		ASSERT_ALWAYS(!r.overlaps(p[2]))
		ASSERT_ALWAYS(!r.overlaps(p[3]))
		ASSERT_INFO_ALWAYS(r.overlaps(p[4]), "r = " << r << " p = " << p[4])
		ASSERT_ALWAYS(!r.overlaps(p[5]))
		ASSERT_ALWAYS(!r.overlaps(p[6]))
		ASSERT_ALWAYS(!r.overlaps(p[7]))
		ASSERT_ALWAYS(!r.overlaps(p[8]))
	}

	// test intersect(rectangle)
	{
		r4::rectangle<int> r{ {3, 4}, {6, 8} };
		r4::rectangle<int> r1{ {5, 6}, {6, 8} };

		r.intersect(r1);

		r4::rectangle<int> cmp{ {5, 6}, {4, 6} };

		ASSERT_INFO_ALWAYS(r == cmp, "r = " << r)
	}

	// test rectangle<unsigned>{0, 0}.intersect(rectangle)
	{
		r4::rectangle<unsigned> r{ 0, 0 };
		r4::rectangle<unsigned> r1{ 289, 3, 149, 248 };

		r.intersect(r1);

		ASSERT_INFO_ALWAYS(r.d.is_zero(), "r = " << r)
	}

	// test unite(rectangle)
	{
		r4::rectangle<int> r0{ {3, 4}, {6, 8} };
		r4::rectangle<int> r1{ {5, 6}, {6, 8} };

		r0.unite(r1);

		r4::rectangle<int> cmp{ {3, 4}, {8, 10} };

		ASSERT_INFO_ALWAYS(r0 == cmp, "r0 = " << r0)
	}

	// test pdx_pdy()
	{
		r4::rectangle<int> r{ {3, 4}, {6, 8} };

		r4::vector2<int> cmp{9, 12};

		ASSERT_ALWAYS(r.x2_y2() == cmp)
	}

	// test x_pdy()
	{
		r4::rectangle<int> r{ {3, 4}, {6, 8} };

		r4::vector2<int> cmp{3, 12};

		ASSERT_ALWAYS(r.x1_y2() == cmp)
	}

	// test pdy()
	{
		r4::rectangle<int> r{ {3, 4}, {6, 8} };

		ASSERT_ALWAYS(r.y2() == 12)
	}

	// test pdx()
	{
		r4::rectangle<int> r{ {3, 4}, {6, 8} };

		ASSERT_ALWAYS(r.x2() == 9)
	}

	// test pdx_y()
	{
		r4::rectangle<int> r{ {3, 4}, {6, 8} };

		r4::vector2<int> cmp{9, 4};

		ASSERT_ALWAYS(r.x2_y1() == cmp)
	}

	// test to()
	{
		r4::rectangle<float> r{ {3.3f, 4.4f}, {6.6f, 8.8f} };
		r4::rectangle<int> cmp{ {3, 4}, {6, 8} };

		ASSERT_ALWAYS(r.to<int>() == cmp)
	}

	// test operator=(rectangle)
	{
		r4::rectangle<int> r{3, 4, 5, 6};

		r4::rectangle<int> r2{5, 6, 7, 8};

		r = r2;

		ASSERT_ALWAYS(r == r2)
	}
}
