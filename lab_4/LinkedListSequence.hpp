#ifndef LinkedListSequence_hpp
#define LinkedListSequence_hpp

#include "Sequence.hpp"
#include "Array.hpp"


template<typename T>
class LinkedListSequence : public Sequence <T>{
public://информация о размере хранится в поле DATA


    LinkedListSequence(): DATA() {}

    LinkedListSequence(T* items,int count): DATA(items, count) {}

    LinkedListSequence(LinkedListSequence<T>& list): DATA(list->DATA) {}

    //переопределение не охватывает соответствующую функцию из LinkedList,
    // так как требуется общность первого параметра,вследствие чего нет возможности получить данные
    LinkedListSequence<T>* Concat(Sequence<T>* list){
        for (int i = 0; i < list->GetLength(); ++i) {//добавляю в DATA все элементы из list,её Size увеличивается
            DATA.Append(list->Get(i));
        }
        LinkedListSequence<T>* items = new LinkedListSequence<T>();
        for (int i = 0; i < DATA.GetLength(); ++i) {
            items->Append(DATA.Get(i));
        }

        return items;
    }

    LinkedListSequence<T>* GetSubsequence(int startIndex,int endIndex){//вернуть Sequence<T>*
        LinkedList<T>* tmp = DATA.GetSubLinkedList(startIndex,endIndex);//создаем экземляр с указанными индексами
        LinkedListSequence<T>* items = new LinkedListSequence<T>();
        items->DATA = *tmp;
        return items;
    }

    ~ LinkedListSequence () {
        DATA.~ LinkedList();
    }

    int GetLength(){
        return DATA.GetLength();
    }
    T GetFirst(){
       return  DATA.GetFirst();
    }
    T GetLast(){
        return DATA.GetLast();
    }
    T Get(int index){
       return DATA.Get(index);
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
    void InsertAt(T item,int index){
        DATA.InsertAt(item,index);
    }
    void removeAt(int index){
        DATA.removeAt(index);
    }
    void Print(){
        DATA.PrintFromBegin();
    }
private:
    LinkedList<T> DATA;
};

#endif