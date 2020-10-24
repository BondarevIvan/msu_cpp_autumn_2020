#include "matrix.h"

#include <vector>
#include <iostream>
#include <cassert>

using SimpleMatrix = std::vector<std::vector<NMatrix::ElementType>>;

NMatrix::Matrix constructMatrix(const SimpleMatrix& values)
{
    NMatrix::Matrix m(values.size(), values[0].size());
    for (size_t row = 0; row < m.rows(); ++row)
        for (size_t col = 0; col < m.columns(); ++col)
            m[row][col] = values[row][col];
    return m;
}

void testMult()
{
    auto I = constructMatrix({{ 1, 0 }, { 0, 1 }});
    auto I2 = I;
    I2 *= 2;
    assert(I2 == constructMatrix( {{ 2, 0 }, { 0, 2 }}));
}

void testSum()
{
    {
        auto A = constructMatrix({{ 1, 1, 1 }, { 2, 2, 2 }});
        auto B = constructMatrix({{ -1, -1, -1 }, { 1, 0, -1 }});
        assert((A + B) == constructMatrix({{ 0, 0, 0 }, { 3, 2, 1 }}));
    }
    {
        bool flag = false;
        try
        {
            auto A = constructMatrix({{ 1, 1 }, { 2, 2 }});
            auto B = constructMatrix({{ -1, -1, -1 }, { 1, 0, -1 }});
            auto C = A + B;
        } catch (...)
        {
            flag = true;
        }
        assert(flag);
    }
}

void testEquals()
{
    {
        auto A = constructMatrix({{ 1, 1, 1 }, { 2, 2, 2 }});
        auto B = constructMatrix({{ -1, -1, -1 }, { 1, 0, -1 }});
        assert(A != B);
    }
    {
        auto A = constructMatrix({{ 1, 1, 1 }, { 2, 2, 2 }});
        auto B = A;
        assert(A == B);
    }
    {
        auto A = constructMatrix({{ 1, 1 }, { 2, 2 }});
        auto B = constructMatrix({{ -1, -1, -1 }, { 1, 0, -1 }});
        assert(A != B);
    }
}

void testGetElement()
{
    auto A = constructMatrix({{ 0x00, 0x01 }, { 0x10, 0x11 }});
    bool flag = false;
    try
    {
        assert(A[0][0] == 0x00 && A[0][1] == 0x01 && 
               A[1][0] == 0x10 && A[1][1] == 0x11);
        flag = true;
    }
    catch(...)
    {
        flag = false;
    }
    assert(flag);
    flag = false;
    try
    {
        constructMatrix({{ 1 }, { 2 }})[100][100];
    }
    catch(const std::exception& e)
    {
        flag = true;
    }
    assert(flag);
}

void testLeaks()
{
    for (int _ = 0; _ < 100; ++_)
    {
        auto A = constructMatrix({{1}, {2}});
        auto B = constructMatrix({{0}, {3}});
        auto C = A;
        C = A + B;
    }
}

int main()
{
    testMult();
    testSum();
    testEquals();
    testGetElement();
    std::cout << "OK\n";
    // для запуска valgrind
    testLeaks();
    return 0;
}