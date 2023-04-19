#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>

//#include "pch.h" 
#include<iostream>

//#include "dynamic_array.h"

//#include<string>
//#include<vector> 

using namespace std;
//using namespace System;

struct Leaks {
    ~Leaks() { _CrtDumpMemoryLeaks(); }
}_l;

/*

17. Усовершенствовать программу для упрощения работы со множествами целых чисел.

Реализовать:

a.функцию потокового вывода множества для консоли(операция << );

b.перегруженную операцию присваивания с множеством;

c.функцию сложения(ИЛИ) двух множеств в одно, используя перегруженную операцию + ;

d.функцию умножения(И) двух множеств в одно, используя перегруженную операцию *;

e.функцию вычитания одного множества из другого, которая возвращает все
элементы первого множества, которых нет во втором, используя перегруженную операцию - ;

f.перегруженную функцию сложения множества с целым для добавления числа во множество;

Усложнение №1(+4 балла).Реализовать функции сложения(ИЛИ), умножения(И) и
вычитания двух множеств, используя перегруженные операции +=, *= и -= соответственно
(не вместо, а в дополнение к основным).

Усложнение №2(+3 балла).Реализовать перегруженную операцию сравнения с другим
множеством;

Связка (до + 10 баллов).Если какой - либо студент из вашей группы(или смежной)
воспользуется вашим классом или классами для решения своей задачи, вы получите доп.
баллы.Польза от использования должна быть логически обоснована, а не добавлена “ради
галочки”.

*/

///*

template <typename T>                           //Связка (до + 10 баллов).

class dynamic_array
{
private:
    int m_size;                                 //размер массива (количество элементов в массиве, доступных пользователю)
    int m_capacity;                             //"вместимость" массива, то есть размер выделенной памяти для хранения элементов
    T * m_data;                                 //указатель на область памяти, где хранятся сами элементы массива

public:
    dynamic_array()                             //конструктор по умолчанию создает пустой массив, не содержащий элементов
    {
        m_size = 0;
        m_capacity = 0;
        m_data = NULL;
    }

    dynamic_array(const dynamic_array<T>& a)    //копи-конструктор создает копию существующего массива
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

    dynamic_array(int size)                     //конструктор, который создает массив заданного размера
    {
        m_size = size;
        m_capacity = size;
        if (size != 0)
            m_data = new T[size];
        else
            m_data = 0;
    }

    ~dynamic_array()                            //деструктор 
    {
        if (m_data)
            delete[] m_data;
    }

    void resize(int size)                       //метод resize изменяет размер массива, новый размер передается параметром size
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

    void push_back(T val)                       //метод push_back добавляет один новый элемент в конец массива
    {
        resize(m_size + 1);
        m_data[m_size - 1] = val;
    }

    int size() const                            //метод size возвращает размер массива
    {
        return m_size;
    }

    T& operator[] (int i)                       //доступ к элементам массива перегрузим оператор []. Это позволит обращаться к элементам класса dynamic_array так же, как к элементам обычного массива: a[i]
    {
        return m_data[i];
    }

    //метод, который проверяет находится ли заданный элемент во множестве

    char search_in_array(dynamic_array<int> array, int number_of_elements, int search_number)
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

    //b.перегруженную операцию присваивания с множеством;

    dynamic_array &operator= (const dynamic_array<T>& aRight)
    {
        if (this != &aRight)                    //проверка на самоприсваивание, если объект большой, можно потратить много времени на ненужное копирование, или при работе с указателями
        {   
            this->resize(aRight.size());
            for (int i = 0; i < aRight.size(); ++i)
                m_data[i] = aRight.m_data[i];
        }
        return *this;
    }

    //c.функцию сложения(ИЛИ) двух множеств в одно, используя перегруженную операцию +;

    dynamic_array operator+ (const dynamic_array<T>& aRight)
    {
        bool elementsBool = false;
        dynamic_array<int> arrTemp;
        arrTemp = *this;
        for (int i = 0; i < aRight.size() ; ++i)
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

    dynamic_array operator+= (const dynamic_array<T>& aRight)
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

    dynamic_array operator* (const dynamic_array<T>& aRight)
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

    dynamic_array operator*= (const dynamic_array<T>& aRight)
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

    dynamic_array operator- (const dynamic_array<T>& aRight) 
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

    dynamic_array operator-= (const dynamic_array<T>& aRight)
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

    dynamic_array operator+ (int& valueRight)
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

    dynamic_array operator== (const dynamic_array<T>& aRight)
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
};

//*/

// a.функцию потокового вывода множества для консоли ( операция << );

template<typename T>

ostream& operator << (ostream& out, dynamic_array<T> a)
{
    for (int i = 0; i < a.size(); ++i)
        out << a[i] << " ";
    return out;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    int valueNew = NULL;
    bool valueBool = false;

    dynamic_array<int> arr;
    int sizeDA;

    cout << "Введите размер множества: ";
    cin >> sizeDA;                             // получение от пользователя размера массива

    arr.resize(sizeDA);

    for (int i = 0; i < arr.size(); i++)
    {
        valueNew = NULL; 
        printf("Введите значение №%d: ", i);
        cin >> valueNew;
        valueBool = false;
        for (int j = 0; j < arr.size(); j++) {

            if (valueNew == arr[j])
            {
                valueBool = true;
                j = arr.size();
            }
        }
        if (!valueBool)
            arr[i] = valueNew;
        else
        {
            cout << "Значение: " << valueNew <<  " уже есть во множестве." << endl;
            i--;
        }
    }

    cout << endl;
    printf("Значения множества\n");
    for (int i = 0; i < arr.size(); i++)
        printf("dynamic_array [%d] \n", arr[i]);

    int searchDA;

    cout << endl;
    cout << "Введите значение, которое вы хотите найти в множестве: " << endl;
    cin >> searchDA;                            // получение от пользователя искомого элемента массива

    char answer;

    answer = arr.search_in_array(arr, arr.size(), searchDA);

    if (answer == 'y' || answer == 'Y')
    {
        arr.push_back(searchDA);

        cout << endl;
        printf("Значения множества:\n");
        for (int i = 0; i < arr.size(); i++)
            printf("dynamic_array [%d] \n", arr[i]);
    }

    dynamic_array<int> arr_copy;
    char answer_copy;

    cout << endl;
    cout << "Хотите сделать копию множества dynamic_array? y/n" << endl;
    cin >> answer_copy;                         // получение от пользователя ответа копировать или нет

    if (answer_copy == 'y' || answer_copy == 'Y')
    {
        dynamic_array<int> arr_copy = arr;

        cout << endl;
        printf("Значения множества:\n");
        for (int i = 0; i < arr_copy.size(); i++)
            printf("dynamic_array_copy [%d] \n", arr_copy[i]);
    }

    dynamic_array<int> arrNew;
    int sizeDAN;

    cout << endl;
    cout << "Введите размер нового, второго множества dynamic_array_new: ";
    cin >> sizeDAN;                             // получение от пользователя размера массива

    arrNew.resize(sizeDAN);

    for (int i = 0; i < arrNew.size(); i++)
    {
        valueNew = NULL; 
        printf("Введите значение множества dynamic_array_new №%d: ", i);
        cin >> valueNew;
        valueBool = false;
        for (int j = 0; j < arrNew.size(); j++) {

            if (valueNew == arrNew[j])
            {
                valueBool = true;
                j = arrNew.size();
            }
        }
        if (!valueBool)
            arrNew[i] = valueNew;
        else
        {
            cout << "Значение: " << valueNew << " уже есть во множестве множества dynamic_array_new." << endl;
            i--;
        }
    }

    cout << endl;
    printf("Значения множества:\n");
    for (int i = 0; i < arrNew.size(); i++)
        printf("dynamic_array_new [%d] \n", arrNew[i]);

    char answer_assignment;

    cout << endl;
    cout << "Присвоить значения множества dynamic_array множеству dynamic_array_new? " << endl;
    cin >> answer_assignment;                   // получение от пользователя ответа присваивать или нет

    if (answer_assignment == 'y' || answer_assignment == 'Y')
    {
        arr_copy = arrNew;

        arrNew = arr;                           // b.перегруженную операцию присваивания с множеством;

        cout << "Результат присваивания множеств dynamic_array и dynamic_array_new" << endl;

        cout << arrNew << endl;                 //a.функцию потокового вывода множества для консоли ( операция << );

        cout << endl;
        printf("Значения множества:\n");
        for (int i = 0; i < arrNew.size(); i++)
            printf("dynamic_array_new [%d] \n", arrNew[i]);

        cout << endl;
        cout << "Для дальнейшей демонстрации программы вернем изначальные значения множества dynamic_array_new" << endl;

        arrNew = arr_copy;

        cout << endl;
        printf("Значения множества:\n");
        for (int i = 0; i < arrNew.size(); i++)
            printf("dynamic_array_new [%d] \n", arrNew[i]);

    }

    char answer_plus;

    cout << endl;
    cout << "Сложить (+) значения множества dynamic_array и множества dynamic_array_new? " << endl;
    cin >> answer_plus;                         // получение от пользователя ответа складывать или нет

    if (answer_plus == 'y' || answer_plus == 'Y')
    {
        cout << "Результат сложения множеств dynamic_array и dynamic_array_new" << endl;;

        cout << arr + arrNew << endl;           //c.функцию сложения(ИЛИ) двух множеств в одно, используя перегруженную операцию +;

    }

    cout << endl;
    cout << "Сложить и присвоить (+=) значения множества dynamic_array и множества dynamic_array_new? " << endl;
    cin >> answer_plus;                         // получение от пользователя ответа складывать и присваивать или нет

    if (answer_plus == 'y' || answer_plus == 'Y')
    {
        dynamic_array<int> arrPlus;

        arr_copy = arr;

        arr += arrNew;                          //Усложнение №1(+4 балла) c.функцию сложения(ИЛИ) двух множеств в одно, используя перегруженную операцию +=;

        cout << "Результат сложения множеств dynamic_array и dynamic_array_new" << endl;

        cout << arr << endl;                    //a.функцию потокового вывода множества для консоли ( операция << );

        cout << endl;
        printf("Значения множества:\n");
        for (int i = 0; i < arr.size(); i++)
            printf("dynamic_array [%d] \n", arr[i]);

        cout << endl;
        cout << "Для дальнейшей демонстрации программы вернем изначальные значения множества dynamic_array," << endl;
        cout << "а результат сложения присвоим множеству dynamic_array_plus" << endl;

        arrPlus = arr;

        arr = arr_copy;

        cout << endl;
        printf("Значения множества:\n");
        for (int i = 0; i < arrPlus.size(); i++)
            printf("dynamic_array_plus [%d] \n", arrPlus[i]);
    }

    char answer_multiplication;

    cout << endl;
    cout << "Умножить (*) значения множества dynamic_array и множества dynamic_array_new? " << endl;
    cin >> answer_multiplication;               // получение от пользователя ответа умножать или нет

    if (answer_multiplication == 'y' || answer_multiplication == 'Y')
    {
        cout << "Результат сложения множеств dynamic_array и dynamic_array_new" << endl;;

        cout << arr * arrNew << endl;           //d.функцию умножения(И) двух множеств в одно, используя перегруженную операцию *;

    }

    cout << endl;
    cout << "Умножить и присвоить (*=) значения множества dynamic_array и множества dynamic_array_new? " << endl;
    cin >> answer_multiplication;               // получение от пользователя ответа умножать и присваивать или нет

    if (answer_multiplication == 'y' || answer_multiplication == 'Y')
    {
        dynamic_array<int> arrMultiplication;

        arr_copy = arr;

        arr *= arrNew;                           //Усложнение №1(+4 балла) d.функцию умножения(И) двух множеств в одно, используя перегруженную операцию *=;

        cout << "Результат умножения множеств dynamic_array и dynamic_array_new" << endl;

        cout << arr << endl;                    //a.функцию потокового вывода множества для консоли ( операция << );

        cout << endl;
        printf("Значения множества:\n");
        for (int i = 0; i < arr.size(); i++)
            printf("dynamic_array [%d] \n", arr[i]);

        cout << endl;
        cout << "Для дальнейшей демонстрации программы вернем изначальные значения множества dynamic_array," << endl;
        cout << "а результат умножения присвоим множеству dynamic_array_multiplication" << endl;

        arrMultiplication = arr;

        arr = arr_copy;

        cout << endl;
        printf("Значения множества:\n");
        for (int i = 0; i < arrMultiplication.size(); i++)
            printf("dynamic_array_multiplication [%d] \n", arrMultiplication[i]);
    }

    char answer_subtraction;

    cout << endl;
    cout << "Вычесть (-) значения множества dynamic_array из множества dynamic_array_new? " << endl;
    cin >> answer_subtraction;

    if (answer_subtraction == 'y' || answer_subtraction == 'Y')
    {
        cout << "Результат вычитания множеств dynamic_array и dynamic_array_new" << endl;;

        cout << arr - arrNew << endl;           //e.функцию вычитания одного множества из другого, которая возвращает все элементы первого множества, которых нет во втором, используя перегруженную операцию - ;

    }

    cout << endl;
    cout << "Вычесть и присвоить (-=) значения множества dynamic_array из множества dynamic_array_new? " << endl;
    cin >> answer_subtraction;

    if (answer_subtraction == 'y' || answer_subtraction == 'Y')
    {
        dynamic_array<int> arrSubtraction;

        arr_copy = arr;        

        arr -= arrNew;                          //Усложнение №1(+4 балла) e.функцию вычитания одного множества из другого, которая возвращает все элементы первого множества, которых нет во втором, используя перегруженную операцию -=;

        cout << "Результат вычитания множеств dynamic_array и dynamic_array_new" << endl;

        cout << arr << endl;                    //a.функцию потокового вывода множества для консоли ( операция << );

        cout << endl;
        printf("Значения множества:\n");
        for (int i = 0; i < arr.size(); i++)
            printf("dynamic_array [%d] \n", arr[i]);

        cout << endl;
        cout << "Для дальнейшей демонстрации программы вернем изначальные значения множества dynamic_array," << endl;
        cout << "а результат вычитания присвоим множеству dynamic_array_subtraction" << endl;
        
        arrSubtraction = arr;

        arr = arr_copy;

        cout << endl;
        printf("Значения множества:\n");
        for (int i = 0; i < arrSubtraction.size(); i++)
            printf("dynamic_array_subtraction [%d] \n", arrSubtraction[i]);
    }

    char answer_adding;

    valueBool = true;

    while (valueBool)
    {

        cout << endl;
        cout << "Добавить значение во множество dynamic_array? " << endl;
        cin >> answer_adding;

        if (answer_adding == 'y' || answer_adding == 'Y')
        {
            cout << endl;
            printf("Значения множества:\n");
            for (int i = 0; i < arr.size(); i++)
                printf("dynamic_array [%d] \n", arr[i]);

            valueNew = NULL;

            cout << endl;
            printf("Введите значение №%d: ", arr.size() + 1);
            cin >> valueNew;

            valueBool = false;

            for (int i = 0; i < arr.size(); i++)
            {
                if (valueNew == arr[i])
                {
                    valueBool = true;
                    i = arr.size();
                }
            }
            if (!valueBool)
            {
                arr + valueNew;                 //f.перегруженную функцию сложения множества с целым для добавления числа во множество;

                cout << arr;                    //a.функцию потокового вывода множества для консоли ( операция << );

                cout << endl;
                cout << endl;
                printf("Значения множества:\n");
                for (int i = 0; i < arr.size(); i++)
                    printf("dynamic_array [%d] \n", arr[i]);
            }
            else
            {
                cout << "Значение: " << valueNew << " уже есть во множестве." << endl;
                valueBool = true;
            }
        }
        else
            valueBool = false;        
    }

    char answer_compare;

    cout << endl;
    cout << "Сравнить два множества dynamic_array и dynamic_array_new? " << endl;
    cin >> answer_compare;

    if (answer_compare == 'y' || answer_compare == 'Y')
    {

        arr == arrNew;                          //Усложнение №2(+3 балла). Реализовать перегруженную операцию сравнения с другим множеством;
  
    }

    return 0;
}