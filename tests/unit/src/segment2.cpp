#include <tst/set.hpp>
#include <tst/check.hpp>

#include <r4/segment2.hpp>

// declare templates to instantiate all template methods to include all methods to gcov coverage
template class r4::segment2<int>;

namespace{
const tst::set set("segment2", [](tst::suite& suite){
	
	suite.add("set_empty_bounding_box", [](){
		r4::segment2<int> seg{};

		seg.set_empty_bounding_box();

		tst::check_eq(seg.p1.x(), std::numeric_limits<int>::max(), SL);
		tst::check_eq(seg.p1.y(), std::numeric_limits<int>::max(), SL);
		tst::check_eq(seg.p2.x(), std::numeric_limits<int>::min(), SL);
		tst::check_eq(seg.p2.y(), std::numeric_limits<int>::min(), SL);
	});

	suite.add<std::pair<r4::segment2<int>, r4::segment2<int>>>(
		"unite",
		{
			{
				{{10, 20}, {30, 40}},
				{{50, 60}, {70, 80}}
			},
		},
		[](const auto& p){
			auto seg(p.first);

			seg.unite(p.second);

			using std::min;
			using std::max;

			tst::check_eq(seg.p1.x(), min(p.first.min_x(), p.second.min_x()), SL);
			tst::check_eq(seg.p1.y(), min(p.first.min_y(), p.second.min_y()), SL);
			tst::check_eq(seg.p2.x(), max(p.first.max_x(), p.second.max_x()), SL);
			tst::check_eq(seg.p2.y(), max(p.first.max_y(), p.second.max_y()), SL);
		}
	);
});
}
