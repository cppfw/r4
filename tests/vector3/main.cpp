#include <utki/debug.hpp>

#include "../../src/r4/vector3.hpp"

int main(int argc, char** argv){

    // test element type conversion
    {
        r4::vector3<float> vf(1.1f, 2.2f, 3.3f);
        
        auto vi = vf.to<int>();

        ASSERT_INFO_ALWAYS(vi[0] == 1, "vi[0] = " << vi[0])
        ASSERT_INFO_ALWAYS(vi[1] == 2, "vi[1] = " << vi[1])
    }

    return 0;
}
