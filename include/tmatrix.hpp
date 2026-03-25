// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
// Copyright (c) Сысоев А.В.

#ifndef __TDYNAMICMATRIX_H__
#define __TDYNAMICMATRIX_H__

#include <iostream>
#include <stdexcept>
#include <algorithm>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

template<typename T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;

public:
    // Конструктор по размеру
    TDynamicVector(size_t size = 1) : sz(size)
    {
        if (sz == 0)
            throw out_of_range("Vector size should be greater than zero");
        if (sz > MAX_VECTOR_SIZE)
            throw out_of_range("Vector size exceeds maximum allowed size");

        pMem = new (nothrow) T[sz]();
        if (!pMem)
            throw bad_alloc();
    }

    // Конструктор из массива
    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        if (sz == 0)
            throw out_of_range("Vector size should be greater than zero");
        if (sz > MAX_VECTOR_SIZE)
            throw out_of_range("Vector size exceeds maximum allowed size");
        if (!arr)
            throw invalid_argument("Source array cannot be nullptr");

        pMem = new (nothrow) T[sz];
        if (!pMem) throw bad_alloc();

        try {
            std::copy(arr, arr + sz, pMem);
        } catch (...) {
            delete[] pMem;
            throw;
        }
    }

    // Конструктор копирования
    TDynamicVector(const TDynamicVector& v) : sz(v.sz), pMem(new T[v.sz])
    {
        for (size_t i = 0; i < sz; ++i)
            pMem[i] = v.pMem[i];
    }

    // Конструктор перемещения
    TDynamicVector(TDynamicVector&& v) noexcept : sz(v.sz), pMem(v.pMem)
    {
        v.sz = 0;
        v.pMem = nullptr;
    }

    // Деструктор
    ~TDynamicVector()
    {
        delete[] pMem;
        pMem = nullptr;
    }

    // Присваивание 
    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (this != &v) {
            TDynamicVector tmp(v);
            swap(*this, tmp);
        }
        return *this;
    }

    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        if (this != &v) {
            swap(*this, v);
        }
        return *this;
    }

    size_t size() const noexcept { return sz; }

    // Индексация
    T& operator[](size_t i) { return pMem[i]; }

    const T& operator[](size_t i) const { return pMem[i]; }

    T& at(size_t i)
    {
        if (i >= sz) throw out_of_range("Index out of range");
        return pMem[i];
    }

    const T& at(size_t i) const
    {
        if (i >= sz) throw out_of_range("Index out of range");
        return pMem[i];
    }

    // Сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz) return false;
        for (size_t i = 0; i < sz; i++)
            if (pMem[i] != v.pMem[i]) return false;
        return true;
    }

    bool operator!=(const TDynamicVector& v) const noexcept { return !(*this == v); }

    // Скалярные операции
    TDynamicVector operator+(T val)
    {
        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; i++) res.pMem[i] = pMem[i] + val;
        return res;
    }

    TDynamicVector operator-(T val)
    {
        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; i++) res.pMem[i] = pMem[i] - val;
        return res;
    }

    TDynamicVector operator*(T val)
    {
        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; i++) res.pMem[i] = pMem[i] * val;
        return res;
    }

    // Векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (sz != v.sz) throw invalid_argument("Vectors must have same size for addition");
        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; i++) res.pMem[i] = pMem[i] + v.pMem[i];
        return res;
    }

    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz != v.sz) throw invalid_argument("Vectors must have same size for subtraction");
        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; i++) res.pMem[i] = pMem[i] - v.pMem[i];
        return res;
    }

    T operator*(const TDynamicVector& v)
    {
        if (sz != v.sz) throw invalid_argument("Vectors must have same size for dot product");
        T result = T();
        for (size_t i = 0; i < sz; i++) result += pMem[i] * v.pMem[i];
        return result;
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    // Ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++) istr >> v.pMem[i];
        return istr;
    }

    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++) ostr << v.pMem[i] << ' ';
        return ostr;
    }
};


template<typename T>
class TDynamicMatrix : public TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;

public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        if (s == 0)
            throw out_of_range("Matrix size should be greater than zero");
        if (s > MAX_MATRIX_SIZE)
            throw out_of_range("Matrix size exceeds maximum allowed size");

        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(sz);
    }

    using TDynamicVector<TDynamicVector<T>>::operator[];

    TDynamicVector<T>& at(size_t i)
    {
        if (i >= sz) throw out_of_range("Matrix row index out of range");
        return pMem[i];
    }

    const TDynamicVector<T>& at(size_t i) const
    {
        if (i >= sz) throw out_of_range("Matrix row index out of range");
        return pMem[i];
    }

    // Сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        if (sz != m.sz) return false;
        for (size_t i = 0; i < sz; i++)
            if (pMem[i] != m.pMem[i]) return false;
        return true;
    }

    bool operator!=(const TDynamicMatrix& m) const noexcept { return !(*this == m); }

    // Матрица * скаляр
    TDynamicMatrix operator*(const T& val)
    {
        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; i++) res[i] = pMem[i] * val;
        return res;
    }

    // Матрица * вектор
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        if (sz != v.size()) throw invalid_argument("Matrix and vector sizes don't match for multiplication");
        TDynamicVector<T> res(sz);
        for (size_t i = 0; i < sz; i++) res[i] = pMem[i] * v;
        return res;
    }

    // Матрица * матрица
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        if (sz != m.sz) throw invalid_argument("Matrix sizes must be equal for addition");
        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; i++) res[i] = pMem[i] + m[i];
        return res;
    }

    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        if (sz != m.sz) throw invalid_argument("Matrix sizes must be equal for subtraction");
        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; i++) res[i] = pMem[i] - m[i];
        return res;
    }

    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        if (sz != m.sz) throw invalid_argument("Matrix sizes must be equal for multiplication");
        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; i++)
            for (size_t j = 0; j < sz; j++)
            {
                T sum = T();
                for (size_t k = 0; k < sz; k++)
                    sum += pMem[i][k] * m[k][j];
                res[i][j] = sum;
            }
        return res;
    }

    // Ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& m)
    {
        for (size_t i = 0; i < m.sz; i++) istr >> m.pMem[i];
        return istr;
    }

    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& m)
    {
        for (size_t i = 0; i < m.sz; i++) ostr << m.pMem[i] << '\n';
        return ostr;
    }
};

#endif