#include <tst/set.hpp>
#include <tst/check.hpp>

#include "../../../src/r4/segment2.hpp"

// declare templates to instantiate all template methods to include all methods to gcov coverage
template class r4::segment2<int>;

namespace{
tst::set set("segment2", [](tst::suite& suite){
	// TODO: add tests
});
}
