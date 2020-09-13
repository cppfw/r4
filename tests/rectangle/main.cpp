#include <utki/debug.hpp>

#include "../../src/r4/rectangle.hpp"

int main(int argc, char** argv){

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
			{1, 2}, {5, 3}, {10 ,3},
			{2, 5}, {5, 7}, {11, 7},
			{-1, 13}, {7, 14}, {13, 17}
		}};

		ASSERT_ALWAYS(!r.overlaps(p[0]))
		ASSERT_ALWAYS(!r.overlaps(p[1]))
		ASSERT_ALWAYS(!r.overlaps(p[2]))
		ASSERT_ALWAYS(!r.overlaps(p[3]))
		ASSERT_ALWAYS(r.overlaps(p[4]))
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

	// test intersection(rectangle)
	{
		r4::rectangle<int> r0{ {3, 4}, {6, 8} };
		r4::rectangle<int> r1{ {5, 6}, {6, 8} };

		auto r = r0.intersection(r1);

		r4::rectangle<int> cmp{ {5, 6}, {4, 6} };

		ASSERT_INFO_ALWAYS(r == cmp, "r = " << r)
	}

	// test pdx_pdy()
	{
		r4::rectangle<int> r{ {3, 4}, {6, 8} };

		r4::vector2<int> cmp{9, 12};

		ASSERT_ALWAYS(r.pdx_pdy() == cmp)
	}

	// test x_pdy()
	{
		r4::rectangle<int> r{ {3, 4}, {6, 8} };

		r4::vector2<int> cmp{3, 12};

		ASSERT_ALWAYS(r.x_pdy() == cmp)
	}

	// test pdy()
	{
		r4::rectangle<int> r{ {3, 4}, {6, 8} };

		ASSERT_ALWAYS(r.pdy() == 12)
	}

	// test pdx()
	{
		r4::rectangle<int> r{ {3, 4}, {6, 8} };

		ASSERT_ALWAYS(r.pdx() == 9)
	}

	// test pdx_y()
	{
		r4::rectangle<int> r{ {3, 4}, {6, 8} };

		r4::vector2<int> cmp{9, 4};

		ASSERT_ALWAYS(r.pdx_y() == cmp)
	}

	// test to()
	{
		r4::rectangle<float> r{ {3.3f, 4.4f}, {6.6f, 8.8f} };
		r4::rectangle<int> cmp{ {3, 4}, {6, 8} };

		ASSERT_ALWAYS(r.to<int>() == cmp)
	}

	return 0;
}
