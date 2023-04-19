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

    // b.������������� �������� ������������ � ����������;

    dynamic_array& operator= (const dynamic_array<T>& aRight);

    //c.������� ��������(���) ���� �������� � ����, ��������� ������������� �������� +;

    dynamic_array operator+ (const dynamic_array<T>& aRight);

    //���������� �1(+4 �����) c.������� ��������(���) ���� �������� � ����, ��������� ������������� �������� +=;

    dynamic_array operator+= (const dynamic_array<T>& aRight);

    //d.������� ���������(�) ���� �������� � ����, ��������� ������������� �������� *;

    dynamic_array operator* (const dynamic_array<T>& aRight);

    //���������� �1(+4 �����) d.������� ���������(�) ���� �������� � ����, ��������� ������������� �������� *=;

    dynamic_array operator*= (const dynamic_array<T>& aRight);

    //e.������� ��������� ������ ��������� �� �������, ������� ���������� ��� �������� ������� ���������, ������� ��� �� ������, ��������� ������������� �������� -;

    dynamic_array operator- (const dynamic_array<T>& aRight);

    //���������� �1(+4 �����) e.������� ��������� ������ ��������� �� �������, ������� ���������� ��� �������� ������� ���������, ������� ��� �� ������, ��������� ������������� �������� -=;

    dynamic_array operator-= (const dynamic_array<T>& aRight);

    //f.������������� ������� �������� ��������� � ����� ��� ���������� ����� �� ���������;

    dynamic_array operator+ (int& valueRight);

    //���������� �2(+3 �����). ����������� ������������� �������� ��������� � ������ ����������;

    dynamic_array operator== (const dynamic_array<T>& aRight);

};