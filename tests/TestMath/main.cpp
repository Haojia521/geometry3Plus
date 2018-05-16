#define TEST_MAT3

#ifdef TEST_AAB2
#include "testAxisAlignedBox2.h"
#endif

#ifdef TEST_AAB3
#include "testAxisAlignedBox3.h"
#endif

#ifdef TEST_MAT2
#include "testMatrix2.h"
#endif

#ifdef TEST_MAT3
#include "testMatrix3.h"
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

#ifdef TEST_MAT2
    // test matrix 2
    testMatrix2_constructor();
    std::cout << std::endl;
    std::cout << "testMatrix2_constFunctions :" << std::endl;
    testMatrix2_constFunctions();
    std::cout << std::endl;
    std::cout << "testMatrix2_nonConstFunctions :" << std::endl;
    testMatrix2_nonConstFunctions();
    std::cout << std::endl;
    std::cout << "testMatrix2_operatorFunctions" << std::endl;
    testMatrix2_operatorFunctions();
#endif

#ifdef TEST_MAT3
    // test matrix 3
    testMatrix3_constructors();
    std::cout << std::endl;
    std::cout << "testMatrix3_constFunctions :" << std::endl;
    testMatrix3_constFunctions();
    std::cout << std::endl;
    std::cout << "testMatrix3_operatorFunctions" << std::endl;
    testMatrix3_operatorFunctions();
#endif

    system("pause");
    return 0;
}
