#pragma once
#include <iostream>
#include "Node.h"


template<typename T>
class LinkedList {
public:
    int size;
    LinkedList():size(0){};

    void push(T value){
        Node<T>* newNode = new Node<T>(value);

        if(size == 0){
            head = tail = newNode;
        }
        else{
            tail->pNext = newNode;
            tail = newNode;
        }
        size++;
    }

    T pop(){
        T value = head->data;
        if(head == tail){
            head = tail = nullptr;
        }
        else{
            head = head->pNext;
        }
        size--;
        return value;
    }

    bool empty(){
        return size == 0;
    }

    void print(){
        Node<T>* curr = head;
        while (curr != nullptr){
            std::cout << curr->data << ' ';
            curr = curr->pNext;
        }
    }

private:
    Node<T>* head;
    Node<T>* tail;
};
