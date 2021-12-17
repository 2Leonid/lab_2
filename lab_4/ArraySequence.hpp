#ifndef ArraySequence_hpp
#define ArraySequence_hpp

#include "Sequence.hpp"
#include "LinkedList.hpp"


template<typename T>
class ArraySequence : public Sequence <T>{
public:

    ArraySequence(): DATA() {}

    ArraySequence(int size) : DATA(size) {}

    ArraySequence(T* item, int count): DATA(item, count) {}

    ArraySequence(ArraySequence<T>& array): DATA(array.DATA) {}//копиконструктор для параметра ArraySequence

    ArraySequence(LinkedList<T>& list){//копиконструктор для параметра LinkedList
        T* items;
        items = new T[list.GetLength()];
        for (int i = 0; i < list.GetLength(); ++i) {
            items[i] = list.Get(i);
        }

        DATA = DynamicArray<T>(items,list.GetLength());
        delete[] items;
    }
    int GetLength(){
        return DATA.GetSize();
    }
    T Get(int index){
        return DATA.Get(index);
    }
    T GetFirst(){
        return DATA.Get(0);
    }
    T GetLast(){
        return DATA.Get(DATA.GetSize()-1);
    }

    void Set(int index, const T& value){
        return DATA.Set(index, value);
    }

    void Append(T item){
        DATA.Append(item);
    }
    void Prepend(T item){
        DATA.Prepend(item);
    }
    void InsertAt(T item,int index){//Вставка
        if(index >= DATA.GetSize() || index < 0)
            throw "\nInsertAt Message : Index Out Of Range";
        DATA.Resize(DATA.GetSize()+1);
        for (int i = DATA.GetSize()-2; i >= index ; --i) {
            DATA.Set(i+1,DATA.Get(i));
        }
        DATA.Set(index,item);
    }
    void Print(){
        DATA.Print();
    }

    ArraySequence<T>* GetSubsequence(int startIndex,int endIndex){
        ArraySequence<T>* items = new ArraySequence<T>(endIndex-startIndex);
        for (int i = startIndex; i < endIndex; ++i) {
            items->Set(i-startIndex, DATA.Get(i));
        }
        
        return items;
    }

    ArraySequence<T>* Concat(Sequence<T>* list){
        if(list->GetLength() != 0){
            ArraySequence<T>* items = new ArraySequence<T>(DATA.GetSize()+list->GetLength());
            for (int i = 0; i < DATA.GetSize(); ++i) {
                items->Set(i, DATA.Get(i));
            }
            for (int i = 0; i < list->GetLength(); ++i) {
                items->Set(i + DATA.GetSize(), list->Get(i));
                items[i+DATA.GetSize()] = list->Get(i); 
            }

            return items;
        } else {
            ArraySequence<T>* result = new ArraySequence<T>(*this);
            return result;
        }

    }
private:
    DynamicArray<T> DATA;
};

#endif