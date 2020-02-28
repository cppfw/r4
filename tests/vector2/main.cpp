#include <utki/debug.hpp>

#include "../../src/r4/vector2.hpp"

int main(int argc, char** argv){

    // test negate
    {
        r4::vector2<int> v(13, -14);
        ASSERT_ALWAYS(!v.is_negative())

        v.negate();

        ASSERT_ALWAYS(!v.is_negative())
        ASSERT_ALWAYS(v.x == -13)
        ASSERT_ALWAYS(v.y == 14)
    }

    return 0;
}
