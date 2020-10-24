#include "matrix.h"
#include <cstring>
#include <iostream>

namespace NMatrix
{

    void Matrix::Row::setData(ElementType* values)
    {
        pValues = values;
    }
    void Matrix::Row::setNumRow(size_t row)
    {
        numRow = row;
    }
    void Matrix::Row::setSizeRow(size_t size)
    {
        sizeRow = size;
    }
    ElementType& Matrix::Row::operator[](size_t numElement)
    {
        return pValues[numElement + sizeRow * numRow];
    }
    ElementType Matrix::Row::operator[](size_t numElement) const
    {
        return pValues[numElement + sizeRow * numRow];
    }

    Matrix::Matrix(size_t rows, size_t columns)
    {
        createMatrix(rows, columns);
    }
    Matrix::Matrix(const Matrix& matrix)
    {
        createCopyMatrix(matrix);
    }
    Matrix::Row& Matrix::operator[](size_t numRow)
    {
        if (numRow >= countRows)
            throw std::out_of_range("out of range of rows");
        return pRows[numRow];
    }
    const Matrix::Row& Matrix::operator[](size_t numRow) const
    {
        if (numRow >= countRows)
            throw std::out_of_range("out of range of rows");
        return pRows[numRow];
    }
    Matrix& Matrix::operator*=(ElementType coef)
    {
        size_t cntElements = countElements();
        for (size_t index = 0; index < cntElements; ++index)
            pValues[index] *= coef;
        return *this;
    }
    Matrix& Matrix::operator+=(const Matrix& matrix)
    {
        if (countRows != matrix.countRows ||
            countColumns != matrix.countColumns)
        {
            throw std::logic_error("impossible calculate sum");
        }
        size_t cntElements = countElements();
        for (size_t index = 0; index < cntElements; ++index)
            pValues[index] += matrix.pValues[index];
        return *this;
    }
    Matrix& Matrix::operator=(const Matrix& matrix)
    {
        delete[] pRows;
        delete[] pValues;
        createCopyMatrix(matrix);
        return *this;
    }
    Matrix Matrix::operator+(const Matrix& matrix) const
    {
        Matrix sum(*this);
        return sum += matrix;
    }

    bool Matrix::operator!=(const Matrix& matrix) const
    {
        if (countRows != matrix.countRows ||
            countColumns != matrix.countColumns)
        {
            return true;
        }
        size_t cntElements = countElements();
        for (size_t index = 0; index < cntElements; ++index)
        {
            if (pValues[index] != matrix.pValues[index])
                return true;
        }
        return false;
    }
    bool Matrix::operator==(const Matrix& matrix) const
    {
        return !(*this != matrix);
    }
    size_t Matrix::rows() const
    {
        return countRows;
    }
    size_t Matrix::columns() const
    {
        return countColumns;
    }
    std::ostream& operator<<(std::ostream& out, const Matrix& matrix)
    {
        for (size_t rowNum = 0; rowNum < matrix.countRows; ++rowNum)
        {
            const auto& row = matrix[rowNum];
            for (size_t colNum = 0; colNum < matrix.countColumns; ++colNum)
                out << row[colNum] << ' ';
            out << std::endl;
        }
        return out;
    }
    size_t Matrix::countElements() const
    {
        return countRows * countColumns;
    }
    Matrix::~Matrix()
    {
        delete[] pValues;
        delete[] pRows;
    }
    void Matrix::createMatrix(size_t rows, size_t columns)
    {
        countRows = rows;
        countColumns = columns;
        pValues = new ElementType[countElements()];
        pRows = new Row[rows];
        for (size_t row = 0; row < countRows; ++row)
        {
            pRows[row].setNumRow(row);
            pRows[row].setSizeRow(countColumns);
            pRows[row].setData(pValues);
        }
    }
    void Matrix::createCopyMatrix(const Matrix& matrix)
    {
        createMatrix(matrix.countRows, matrix.countColumns);
        std::memcpy(pValues,
                    matrix.pValues,
                    sizeof(*pValues) * countElements());
    }
}