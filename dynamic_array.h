#pragma once

template <typename T>

class dynamic_array

{
private:
    int m_size;
    int m_capacity;
    T* m_data;

public:
    dynamic_array();

    dynamic_array(const dynamic_array<T>& a);

    dynamic_array(int size);

    ~dynamic_array();

    void resize(int size);

    void push_back(T val);

    int size() const;

    T& operator[] (int i);

    char search_in_array(dynamic_array<int> array, int number_of_elements, int search_number);

    // b.перегруженную операцию присваивани€ с множеством;

    dynamic_array& operator= (const dynamic_array<T>& aRight);

    //c.функцию сложени€(»Ћ») двух множеств в одно, использу€ перегруженную операцию +;

    dynamic_array operator+ (const dynamic_array<T>& aRight);

    //”сложнение є1(+4 балла) c.функцию сложени€(»Ћ») двух множеств в одно, использу€ перегруженную операцию +=;

    dynamic_array operator+= (const dynamic_array<T>& aRight);

    //d.функцию умножени€(») двух множеств в одно, использу€ перегруженную операцию *;

    dynamic_array operator* (const dynamic_array<T>& aRight);

    //”сложнение є1(+4 балла) d.функцию умножени€(») двух множеств в одно, использу€ перегруженную операцию *=;

    dynamic_array operator*= (const dynamic_array<T>& aRight);

    //e.функцию вычитани€ одного множества из другого, котора€ возвращает все элементы первого множества, которых нет во втором, использу€ перегруженную операцию -;

    dynamic_array operator- (const dynamic_array<T>& aRight);

    //”сложнение є1(+4 балла) e.функцию вычитани€ одного множества из другого, котора€ возвращает все элементы первого множества, которых нет во втором, использу€ перегруженную операцию -=;

    dynamic_array operator-= (const dynamic_array<T>& aRight);

    //f.перегруженную функцию сложени€ множества с целым дл€ добавлени€ числа во множество;

    dynamic_array operator+ (int& valueRight);

    //”сложнение є2(+3 балла). –еализовать перегруженную операцию сравнени€ с другим множеством;

    dynamic_array operator== (const dynamic_array<T>& aRight);

};