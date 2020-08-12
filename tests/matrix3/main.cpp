#include <utki/debug.hpp>

#include "../../src/r4/matrix3.hpp"

#include <sstream>

int main(int argc, char** argv){

    // test operator<<
    {
        r4::matrix3<int> m;
		m.identity();

		std::stringstream ss;

		ss << m;

		auto cmp = "\n\t/1 0 0\\\n\t|0 1 0|\n\t\\0 0 1/";

		// TRACE_ALWAYS(<< "m = " << ss.str() << std::endl)
		// TRACE_ALWAYS(<< "cmp = " << cmp << std::endl)

		ASSERT_ALWAYS(ss.str() == cmp)
        // v.negate();

        // ASSERT_ALWAYS(!v.is_negative())
        // ASSERT_ALWAYS(v.x == -13)
        // ASSERT_ALWAYS(v.y == 14)
    }

    return 0;
}
