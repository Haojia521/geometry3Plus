#define TEST_AAB3

#ifdef TEST_AAB2
#include "testAxisAlignedBox2.h"
#endif

#ifdef TEST_AAB3
#include "testAxisAlignedBox3.h"
#endif

using namespace g3test;

int main()
{
#ifdef TEST_AAB2
    // test axis aligned box 2
    testAAB2_constructor();
    testAAB2_nonConstFunctions();
    std::cout << std::endl;
    testAAB2_nonConstFunctions2();
    std::cout << std::endl;
    testAAB2_constFunctions();
#endif

#ifdef TEST_AAB3
    // test axis aligned box 3
    testAAB3_constructor();
    std::cout << std::endl;
    std::cout << "testAAB3_constFunctions :" << std::endl;
    testAAB3_constFunctions();
    std::cout << std::endl;
    std::cout << "testAAB3_nonConstFunctions :" << std::endl;
    testAAB3_nonConstFunctions();
#endif

    system("pause");
    return 0;
}