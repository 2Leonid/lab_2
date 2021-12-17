#ifndef Array_hpp
#define Array_hpp
#include <iostream>
#include <string.h>

template <class T>
class DynamicArray{
private:

    T* m_data;
    int m_size;
    int m_capacity;
public:
    DynamicArray(){
        m_data = NULL;
        m_size = 0;
        m_capacity = 0;
    }

   ~DynamicArray(){
        delete[] this->m_data;
    }



    DynamicArray(int size){
        m_size = size;
        m_capacity = size;
        m_data = new T[size];
    }

    DynamicArray(T* items,int count){//передаем указатель на первый элемент массива и его длинну
        if(items == nullptr){
            m_data = nullptr;
            m_size = 0;
            m_capacity = 0;
        }
        else{
            m_size = count;     
            m_capacity = count;
            m_data = new T[count]; //Выделяем память под массив
            m_data = (T*)memcpy(m_data,items, count * sizeof(T)); //копируем область памяти
        }
    }

    DynamicArray(const DynamicArray<T> &dynamicArray){ //Конструктор копирования
        if(dynamicArray.m_size == 0){
            m_data = nullptr;
            m_size = 0;
            m_capacity = 0;
        }
        else{
            m_size = dynamicArray.m_size;
            m_capacity = m_size;
            m_data = new T[m_size];
            m_data = (T*)memcpy(m_data, dynamicArray.m_data, dynamicArray.m_size* sizeof(T));//(куда, откуда, сколько байт)
        }
    }


    void Resize(int newSize){
        if(newSize > m_capacity){
            int new_capacity = std::max(2 * m_size, newSize);
            T* new_data = new T[new_capacity];
            new_data = (T*)memcpy(new_data,m_data,m_size*sizeof(T));
            delete[] m_data;
            m_data = new_data;
            m_capacity = new_capacity;
        }
        m_size = newSize;
    }

    T Get(int index) const{
        if(index < 0 || index >= m_capacity)
            throw "\nGet Message : Index Out Of Range\n";
        return m_data[index];
    }

    void Set(int index,T value){
        if(index < 0 || index > m_capacity)
            throw "\nSet Message : Index Out Of Range\n";
        m_data[index] = value;

    }

    int GetSize() const{
        return m_size;
    }

    void Append(T val){ //push
        Resize(m_size + 1);
        m_data[m_size - 1] = val;
    }
    void Prepend(T val){ //Добавить в начало
        Resize(m_size + 1);
        for (int i = m_size - 2; i >= 0; --i){
            m_data[i + 1] = m_data[i];
        }
        m_data[0] = val;
    }

    T & operator [] (int i){//перегрузка оператора
        return m_data[i];
    }

    void Print(){
        if(m_size > 0){
            std::cout << std::endl;
            for (int i = 0; i < m_size; ++i) {
                std::cout << m_data[i] << "\t";
            }
            std::cout << std::endl;
        }
        else{
            std::cout << "\nObject is empty!\n";
        }
    }
};
#endif