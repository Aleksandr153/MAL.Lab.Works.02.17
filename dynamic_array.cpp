#include <crtdbg.h>
#include <stdlib.h>

#include<iostream>

#include "dynamic_array.h"

using namespace std;

template <typename T>
dynamic_array<T>::dynamic_array()
{
    m_size = 0;
    m_capacity = 0;
    m_data = NULL;
}

template <typename T>
dynamic_array<T>::dynamic_array(const dynamic_array<T>& a)
{
    m_size = a.m_size;
    m_capacity = m_size;
    m_data = NULL;
    if (m_size != 0)
        m_data = new T[m_size];
    else
        m_data = 0;
    for (int i = 0; i < m_size; ++i)
        m_data[i] = a.m_data[i];
}

template <typename T>
dynamic_array<T>::dynamic_array(int size)
{
    m_size = size;
    m_capacity = size;
    if (size != 0)
        m_data = new T[size];
    else
        m_data = 0;
}

template <typename T>
dynamic_array<T>::~dynamic_array()
{
    if (m_data)
        delete[] m_data;
}

template <typename T>
void dynamic_array<T>::resize(int size)
{
    if (size > m_capacity)
    {
        int new_capacity = max(size, m_size * 2);
        T* new_data = new T[new_capacity];
        for (int i = 0; i < m_size; ++i)
            new_data[i] = m_data[i];
        delete[] m_data;
        m_data = new_data;
        m_capacity = new_capacity;
    }
    m_size = size;
}

template <typename T>
void dynamic_array<T>::push_back(T val)
{
    resize(m_size + 1);
    m_data[m_size - 1] = val;
}

template <typename T>
int dynamic_array<T>::size() const
{
    return m_size;
}

template <typename T>
T& dynamic_array<T>::operator[] (int i)
{
    return m_data[i];
}

template <typename T>
char dynamic_array<T>::search_in_array(dynamic_array<int> array, int number_of_elements, int search_number)
{
    int j = 0;
    int k = 0;
    char awr = 'n';

    for (int i = 0; i < number_of_elements; i++)
        if (search_number == array[i])
            j = j + 1;
    if (j > 0)
    {
        dynamic_array<int> new_arr;
        new_arr.resize(j);
        for (int i = 0; i < number_of_elements; i++)
            if (search_number == array[i])
            {
                new_arr[k] = i;
                k = k + 1;
            }
        for (int k = 0; k < new_arr.size(); k++)
            cout << "Искомый элемент найден во множестве под номером: " << new_arr[k] << " " << endl;
    }
    else
    {
        cout << "Искомый элемент найден во множестве не найден" << endl;
        cout << "Хотите добавить элемент во множество? y/n" << endl;
        cin >> awr;
    }
    return awr;
}

// b.перегруженную операцию присваивания с множеством;
template <typename T>
dynamic_array<T>& dynamic_array<T>::operator= (const dynamic_array<T>& aRight)
{
    if (this != &aRight)
    {
        this->resize(aRight.size());
        for (int i = 0; i < aRight.size(); ++i)
            m_data[i] = aRight.m_data[i];
    }
    return *this;
}

//c.функцию сложения(ИЛИ) двух множеств в одно, используя перегруженную операцию +;
template <typename T>
dynamic_array<T> dynamic_array<T>::operator+ (const dynamic_array<T>& aRight)
{
    bool elementsBool = false;
    dynamic_array<int> arrTemp;
    arrTemp = *this;
    for (int i = 0; i < aRight.size(); ++i)
    {
        elementsBool = false;
        for (int j = 0; j < this->size(); ++j)
            if (aRight.m_data[i] == this->m_data[j])
                elementsBool = true;
        if (!elementsBool)
            arrTemp.push_back(aRight.m_data[i]);
    }
    return dynamic_array(arrTemp);
}

//Усложнение №1(+4 балла) c.функцию сложения(ИЛИ) двух множеств в одно, используя перегруженную операцию +=;
template <typename T>
dynamic_array<T> dynamic_array<T>::operator+= (const dynamic_array<T>& aRight)
{
    bool elementsBool = false;
    dynamic_array<int> arrTemp;
    arrTemp = *this;
    for (int i = 0; i < aRight.size(); ++i)
    {
        elementsBool = false;
        for (int j = 0; j < this->size(); ++j)
            if (aRight.m_data[i] == this->m_data[j])
                elementsBool = true;
        if (!elementsBool)
            arrTemp.push_back(aRight.m_data[i]);
    }
    *this = arrTemp;
    return *this;
}

//d.функцию умножения(И) двух множеств в одно, используя перегруженную операцию *;
template <typename T>
dynamic_array<T> dynamic_array<T>::operator* (const dynamic_array<T>& aRight)
{
    bool elementsBool = false;
    dynamic_array<int> arrTemp;
    for (int i = 0; i < aRight.size(); ++i)
    {
        elementsBool = false;
        for (int j = 0; j < this->size(); ++j)
            if (aRight.m_data[i] == m_data[j])
                elementsBool = true;
        if (elementsBool)
            arrTemp.push_back(aRight.m_data[i]);
    }
    return dynamic_array(arrTemp);
}

//Усложнение №1(+4 балла) d.функцию умножения(И) двух множеств в одно, используя перегруженную операцию *=;
template <typename T>
dynamic_array<T> dynamic_array<T>::operator*= (const dynamic_array<T>& aRight)
{
    bool elementsBool = false;
    dynamic_array<int> arrTemp;
    for (int i = 0; i < aRight.size(); ++i)
    {
        elementsBool = false;
        for (int j = 0; j < this->size(); ++j)
            if (aRight.m_data[i] == m_data[j])
                elementsBool = true;
        if (elementsBool)
            arrTemp.push_back(aRight.m_data[i]);
    }
    *this = arrTemp;
    return *this;
}

//e.функцию вычитания одного множества из другого, которая возвращает все элементы первого множества, которых нет во втором, используя перегруженную операцию -;
template <typename T>
dynamic_array<T> dynamic_array<T>::operator- (const dynamic_array<T>& aRight)
{
    bool elementsBool = false;
    dynamic_array<int> arrTemp;

    for (int i = 0; i < this->size(); ++i)
    {
        bool elementsBool = false;
        for (int j = 0; j < aRight.size(); ++j)
        {
            if (m_data[i] == aRight.m_data[j])
                elementsBool = true;
        }
        if (!elementsBool)
        {
            arrTemp.push_back(m_data[i]);
        }
    }
    return dynamic_array(arrTemp);
}

//Усложнение №1(+4 балла) e.функцию вычитания одного множества из другого, которая возвращает все элементы первого множества, которых нет во втором, используя перегруженную операцию -=;
template <typename T>
dynamic_array<T> dynamic_array<T>::operator-= (const dynamic_array<T>& aRight)
{
    bool elementsBool = false;
    dynamic_array<int> arrTemp;

    for (int i = 0; i < this->size(); ++i)
    {
        bool elementsBool = false;
        for (int j = 0; j < aRight.size(); ++j)
        {
            if (m_data[i] == aRight.m_data[j])
                elementsBool = true;
        }
        if (!elementsBool)
        {
            arrTemp.push_back(m_data[i]);
        }
    }
    *this = arrTemp;
    return *this;
}

//f.перегруженную функцию сложения множества с целым для добавления числа во множество;
template <typename T>
dynamic_array<T> dynamic_array<T>::operator+ (int& valueRight)
{
    bool elementsBool = false;
    dynamic_array<int> arrTemp;
    arrTemp = *this;
    for (int i = 0; i < this->size(); ++i)
        if (m_data[i] == valueRight)
            elementsBool = true;
    if (!elementsBool)
        arrTemp.push_back(valueRight);
    else
        cout << "Значение: " << valueRight << " уже есть во множестве." << endl;
    *this = arrTemp;
    return *this;
}

//Усложнение №2(+3 балла). Реализовать перегруженную операцию сравнения с другим множеством;
template <typename T>
dynamic_array<T> dynamic_array<T>::operator== (const dynamic_array<T>& aRight)
{
    bool elementsBool = false;
    bool elementsPower = false;
    bool elementsEqual = false;

    if (this->size() == aRight.size())
    {
        elementsPower = true;
        if (elementsPower)
        {
            for (int i = 0; i < this->size(); ++i)
            {
                elementsBool = false;
                for (int j = 0; j < aRight.size(); ++j)
                    if (m_data[i] == aRight.m_data[j])
                    {
                        elementsBool = true;
                        elementsEqual = true;
                    }
                if (!elementsBool)
                {
                    elementsEqual = false;
                    i = this->size();
                }
            }
        }
        if (elementsEqual)
        {
            cout << endl;
            cout << "Множества dynamic_array и dynamic_array_new равны." << endl;
        }
        else
        {
            cout << endl;
            cout << "Множества dynamic_array и dynamic_array_new равномощные, но не равны." << endl;
        }
    }
    else
    {
        cout << endl;
        cout << "Множества dynamic_array и dynamic_array_new не равны." << endl;
    }


    return *this;
}