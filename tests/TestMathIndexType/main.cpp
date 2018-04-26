#include <iostream>

#include <math/indexType.h>

using namespace g3;

void test_Index()
{
    Index i = 10;

    int x = i;
    unsigned int y = i;
    std::cout << "x : " << x << "  y : " << y << std::endl;

    bool b1 = 125 > i;
    bool b2 = 12.3 < i;
    std::cout << "b1 : " << b1 << "  b2 : " << b2 << std::endl;

    int a = 5;
    i = a;
    std::cout << "i = a : " << i << std::endl;

    long b = 3;
    i = b;
    std::cout << "i = b : " << i << std::endl;

    short c = -5;
    i = c;
    std::cout << "i = c : " << i << std::endl;

    char d = -1;
    i = d;
    std::cout << "i = d : " << i << std::endl;

    auto add = i + 6.0;
    std::cout << "add : " << add << std::endl;

    std::cout << "valid() : " << i.valid() << std::endl;

    i.invalidate();
    std::cout << "invalidate() -> value: " << i << "  valid() : " << i.valid() << std::endl;

    std::cout << "sizeof(unsigned int) : " << sizeof(unsigned int) << std::endl;
    std::cout << "sizeof(Index)        : " << sizeof(Index) << std::endl;
}

void test_IndexTemplate()
{
    IndexTemplate<3> it = IndexTemplate<3>::zero;
    std::cout << "IndexTemplate<3> = zero : " << it[0] << " , " << it[1] << " , " << it[2] << std::endl;

    IndexTemplate<3> it2(3);
    std::cout << "IndexTemplate<3>(3) : " << it2[0] << " , " << it2[1] << " , " << it2[2] << std::endl;

    IndexTemplate<3> it3(4);
    it3 = it2;
    std::cout << "it3 = it2 : " << it2[0] << " , " << it2[1] << " , " << it2[2] << std::endl;

    Index2 i2(3);
    Index2::value_type i;
    Index2::one;

    Index2 i2_1;
    i2_1 = i2;

    Index3 i3_1(1, 2, 3);
    Index3 i3_2(1, 2, 3, true);
    Index3 i3_3(5);
    Index3 i3_4(i3_1);
    Index3 i3_5 = i3_2;
    Index3 i3_6;
    std::cout << "i3_1 : " << i3_1[0] << " , " << i3_1[1] << " , " << i3_1[2] << std::endl;
    std::cout << "i3_2 : " << i3_2[0] << " , " << i3_2[1] << " , " << i3_2[2] << std::endl;
    std::cout << "i3_3 : " << i3_3[0] << " , " << i3_3[1] << " , " << i3_3[2] << std::endl;
    std::cout << "i3_4 : " << i3_4[0] << " , " << i3_4[1] << " , " << i3_4[2] << std::endl;
    std::cout << "i3_5 : " << i3_5[0] << " , " << i3_5[1] << " , " << i3_5[2] << std::endl;
    std::cout << "i3_6 : " << i3_6[0] << " , " << i3_6[1] << " , " << i3_6[2] << std::endl;

    i3_6 = i3_3;
    std::cout << "i3_6 = i3_3 : " << i3_6[0] << " , " << i3_6[1] << " , " << i3_6[2] << std::endl;

    std::cout << "i3_6 == i3_3 : " << (i3_6 == i3_3) << std::endl;

    i3_6[1] = 6;
    std::cout << "i3_6[1] = 6 : " << i3_6[0] << " , " << i3_6[1] << " , " << i3_6[2] << std::endl;
    std::cout << "i3_6 == i3_3 : " << (i3_6 == i3_3) << std::endl;
}

int main()
{
    test_IndexTemplate();

    system("pause");
    return 0;
}