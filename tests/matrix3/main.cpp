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

		auto str = ss.str();

        ASSERT_INFO_ALWAYS(str == cmp, "m = " << str << "\ncmp = " << cmp)
        // v.negate();

        // ASSERT_ALWAYS(!v.is_negative())
        // ASSERT_ALWAYS(v.x == -13)
        // ASSERT_ALWAYS(v.y == 14)
    }

    // test operator[]
    {
        r4::matrix3<int> m;

        m[0][0] = 1;
        m[0][1] = 2;
        m[0][2] = 3;
        m[1][0] = 4;
        m[1][1] = 5;
        m[1][2] = 6;
        m[2][0] = 7;
        m[2][1] = 8;
        m[2][2] = 9;

        std::stringstream ss;

        ss << m;

        auto cmp = "\n\t/1 2 3\\\n\t|4 5 6|\n\t\\7 8 9/";
        auto str = ss.str();

        ASSERT_INFO_ALWAYS(str == cmp, "m = " << str << "\ncmp = " << cmp)
    }

    // test constructor from vector4 arguments
    {
        r4::vector4<int> r0(1, 2, 3, 4);
        r4::vector4<int> r1(5, 6, 7, 8);
        r4::vector4<int> r2(9, 10, 11, 12);

        r4::matrix3<int> m(r0, r1, r2);

        std::stringstream ss;

        ss << m;

        auto cmp = "\n\t/1 2 3\\\n\t|5 6 7|\n\t\\9 10 11/";
        auto str = ss.str();

        ASSERT_INFO_ALWAYS(str == cmp, "m = " << str << "\ncmp = " << cmp)
    }

    // test operator*(vector2)
    {
        r4::vector2<int> v(2, 3);

        r4::matrix3<int> m{
                { 2, 3, 4 },
                { 5, 6, 7 },
                { 8, 9, 10 }
            };
        
        auto r = m * v;

        ASSERT_INFO_ALWAYS(r[0] == 13, "r[0] = " << r[0])
        ASSERT_INFO_ALWAYS(r[1] == 28, "r[1] = " << r[1])
    }

    // test type conversion constructor
    {
        r4::matrix3<float> mf{
            { 1.1f, 2.2f, 3.3f },
            { 4.4f, 5.5f, 6.6f },
            { 7.7f, 8.8f, 9.9f }
        };

        auto mi = mf.to<int>();

        std::stringstream ss;

        ss << mi;

        auto cmp = "\n\t/1 2 3\\\n\t|4 5 6|\n\t\\7 8 9/";
        auto str = ss.str();

        ASSERT_INFO_ALWAYS(str == cmp, "m = " << str << "\ncmp = " << cmp)
    }

    return 0;
}
