#pragma once
#include <sstream>

namespace NMatrix
{
    using ElementType = int;
    using size_t = unsigned long long;
    class Matrix
    {
        class Row
        {
        public:
            void setData(ElementType* &values);
            void setNumRow(size_t row);
            void setSizeRow(size_t size);
            ElementType& operator[](size_t numElement);
            ElementType operator[](size_t numElement) const;
        private:
            ElementType* pValues;
            size_t numRow;
            size_t sizeRow;
        };
    public:
        Matrix(size_t rows, size_t columns);
        Matrix(const Matrix& matrix);
        Row& operator[](size_t numRow);
        const Row& operator[](size_t numRow) const;
        Matrix& operator*=(ElementType coef);
        Matrix& operator+=(const Matrix& matrix);
        Matrix& operator=(const Matrix& matrix);
        Matrix operator+(const Matrix& matrix) const;
        bool operator!=(const Matrix& matrix) const;
        bool operator==(const Matrix& matrix) const;
        size_t rows() const;
        size_t columns() const;
        friend std::ostream& operator<<(std::ostream& out,
                                        const Matrix& matrix);
        size_t countElements() const;
        ~Matrix();
    private:
        ElementType* pValues;
        Row* pRows;
        size_t countRows;
        size_t countColumns;
    private:
        void createMatrix(size_t rows, size_t columns);
        void createCopyMatrix(const Matrix& matrix);
    };
}