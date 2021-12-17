#ifndef LinkedList_hpp
#define LinkedList_hpp


template<typename T> //двусвязный список
class Node{
public:
    Node* child;
    Node* parent;
    T DATA;
    Node(T DATA = T(),Node* parent = nullptr,Node* child = nullptr){
        this->DATA = DATA;
        this->parent = parent;
        this->child = child;
    }
};

template<typename T>
class LinkedList{
public:

    ~LinkedList(){
        clear();
    }


    LinkedList(){
        Size = 0;
        HEAD = nullptr;
    }

    //считывание значений из переданного массива
    LinkedList(T* items,int count){
        if(items == nullptr){
            Size = 0;
            HEAD = nullptr;
        } else {
            Size = 0;
            HEAD = nullptr;
            TAIL = nullptr;
            for (int i = 0; i < count; ++i) {
                Append(items[i]);
            }
        }
    }


    LinkedList(const LinkedList<T>& list){//Копирование
        Size = 0;
        HEAD = nullptr;//для корректного отрабатывания Append
        Node<T>* current = list.HEAD;
        for (int i = 0; i < list.Size; ++i) {//заменил Size на GetLength()
            Append(current->DATA);
            current = current->child;
        }
        //std::cout << "CopyConstructor done . . .\n";
    }


    LinkedList<T>* Concat(LinkedList<T>* list){
        TAIL->child = list->HEAD;
        list->HEAD->parent = TAIL;
        TAIL = list->TAIL;
        Size+=list->Size;

        return this;
    }

    int GetLength(){
        return Size;
    }

    T Get(int index){
        if(index < 0 || index >= Size)
            throw "\nGet Message : Index Out Of Range\n";

        Node<T>* current;

        if(index < Size/2){
            current = HEAD;
            for (int i = 0; i < index; ++i) {
                current = current->child;
            }
        } else {
            current = TAIL;
            for (int i = 0; i < Size-index-1; ++i) {
                current = current->parent;
            }
        }
        return current->DATA;

    }

    void Set(int index,T value){
        if(index < 0 || index >= Size)
            throw "\nGet Message : Index Out Of Range\n";
        Node<T>* current;
        if(index < Size/2){
            current = HEAD;
            for (int i = 0; i < index; ++i) {
            current = current->child;
        }
        }else{
            current = TAIL;
            for (int i = 0; i < Size-index-1; ++i) {
                current = current->parent;
            }
        }
        current->DATA=value;
    }


    T GetFirst() {
        if(Size == 0)
            throw "\nGetFirst Message : Index Out Of Range\n";
        return Get(0);
    }


    T GetLast(){
        if(Size == 0)
            throw "\nGetLast Message : Index Out Of Range\n";
        //std::cout<<"\nGetLast:\n";
        return Get(Size - 1);
    }


    LinkedList<T>* GetSubLinkedList(int startIndex,int endIndex){
        if(startIndex < 0 || endIndex < 0 || startIndex >= Size || endIndex >=Size)
            throw "\nGetSubLinkedList Message : Index Out Of Range\n";
        Node<T>* current = HEAD;

        for (int i = 0; i < startIndex; ++i)
            current = current->child;

        LinkedList<T>* items = new LinkedList<T>();
        for (int i = 0; i < endIndex - startIndex + 1; ++i) {
            items->Append(current->DATA);
            current = current->child;
        }

        return items;

    }


    void PrintFromEnd(){//печать с конца списка
        //std::cout << std::endl;
        Node<T>* tmp = TAIL;
        if(Size == 1)
            std::cout << TAIL->DATA << " ";
        else{
            while(tmp != nullptr){
                std::cout << tmp->DATA <<" ";
                tmp = tmp->parent;
            }
        }
        std::cout << std::endl;
    }


    void PrintFromBegin(){//печать с начала списка
        if(HEAD != nullptr){
            Node<T>* tmp = this->HEAD;
            if(Size == 1)
                std::cout << HEAD->DATA << " ";
            else{
                while(tmp != nullptr){
                    std::cout << tmp->DATA <<" ";
                    tmp = tmp->child;
                }
            }
            std::cout << std::endl;
        }
    }


/*
    void Append(T DATA){
        if(HEAD == nullptr){//если нет элементов,то заполняем HEAD
            HEAD = new Node<T>(DATA);
            TAIL = HEAD;

        } else {//если больше,то добавляем и присваиваем TAIL этот элемент
            Node<T>* current = this->HEAD;//временная переменная
            Node<T>* tmp;
            while(current->child != nullptr){
                tmp = current;
                current = current->child;
                current->parent = tmp;
            }

            TAIL = new Node<T>(DATA,current,current->child);//вставка между current и nullptr
            current->child = TAIL;
        }
        Size++;
    }
*/

    void Append(T DATA){
        if(HEAD == nullptr){//если нет элементов,то заполняем HEAD
            HEAD = new Node<T>(DATA);
            TAIL = HEAD;

        } else {//если больше,то добавляем и присваиваем TAIL этот элемент
            TAIL = new Node<T>(DATA, TAIL, nullptr);
            TAIL->parent->child = TAIL;
        }
        Size++;
    }


    void Prepend(T DATA) {
        if(HEAD == nullptr){
            HEAD = new Node<T>(DATA);
            TAIL = HEAD;
        }
        else{
            Node<T>* one_more = new Node<T>(DATA,HEAD->parent,HEAD);//создание нового узла(следующий - HEAD,предыдущего нет)
            HEAD->parent = one_more;
            HEAD = one_more;
            /*
            Node<T>* current = HEAD;
            while(current->child != nullptr){
                current = current->child;
            }
            this->TAIL = current;
            */
        }
        Size++;
    }


    void pop_front() {
        if(Size == 1){
            delete [] TAIL;
            TAIL = nullptr;
            HEAD = nullptr;
            Size--;
        }
        else{
            Node<T>* tmp = HEAD;//запоминаем ссылку,по которой находится текущий HEAD
            HEAD = HEAD->child;//сдвиг HEAD к концу на один элемент
            HEAD->parent = nullptr;//"обнуление" указателя на предыдущий элемент
            delete [] tmp;//удаление старого HEAD
            Size--;
        }

    }


    void pop_back(){
        Node<T>* tmp = TAIL;
        TAIL = TAIL->parent;
        TAIL->child = nullptr;
        delete [] tmp;
        Size--;
    }

    void InsertAt(T DATA, int index) {
        if(index < 0 || index >= Size)
            throw "\nInsertAt Message : Index Out Of Range\n";
        Node<T>* previous;
        Node<T>* tmp;
        if(index <= Size/2){//идём сначала
            if(index == 0)
                Prepend(DATA);
            previous = HEAD;
            for (int i = 0; i < index - 1; ++i) {
                previous = previous->child;
            }
        }
        else{//идём с конца

            previous = TAIL;
            for (int i = 0; i < Size - index; ++i) {
                previous = previous->parent;
            }
        }
        tmp = previous->child;//запоминаем адрес следующего узла
        Node<T> *new_elem = new Node<T>(DATA,previous,previous->child);//создаем новый узел
        previous->child = new_elem;//обновляем указатель на следующий узел у предыдущего
        tmp->parent = new_elem;//обновляем указатель на предыдущий узел у следующего

        Size++;
    }

    void removeAt(int index) {
        if(index < 0 || index >= Size)
            throw "removeAt Message : Index Out Of Range\n";
        if(index == 0)
            pop_front();
        else {
            if(index == Size - 1)
                pop_back();
            else {
                Node<T>* previous;
                Node<T>* toDelete;
                if(index <= Size/2){
                    previous = HEAD;
                    for (int i = 0; i < index - 1; ++i) {
                        previous = previous->child;
                    }
                }
                else{
                    previous = TAIL;
                    for (int i = 0; i < Size - index; ++i) {
                        previous = previous->parent;
                    }
                }

                toDelete = previous->child;//запоминаем ссылку на удаляемый узел
                previous->child = toDelete->child;//изменяем поле следующего узла у идущего перед удаляемым
                toDelete->child->parent = previous;//изменяем поле предыдущего узла у идущего после удаляемого

                delete[] toDelete;//очистка памяти по ссылке удаляемого узла
            }
            Size--;
        }
    }
    void ChangeValue(int index,T value){//изменяет по заданному индексу значение на value
        Node<T>* curr = HEAD;
        for (int i = 0; i < index; ++i) {//i + 1 < index вместо i < index - 1 для того,чтобы избежать переполнения числа
            curr = curr->child;
        }
        curr->DATA = value;
    }
    //очистка памяти
    void clear(){
        while(Size){
            pop_front();
        }
    }

    //усовершенствован для двусвязного списка
    T& operator[](const int index) {//перегрузка оператора []
        //для нахождения элемента с номером index
        int counter;
        Node<T> *current;
        if (index <= Size / 2) {//идём с начала
            counter = 0;
            current = HEAD;
            while (current != nullptr) {
                if (counter == index) {
                    return current->DATA;
                }
                current = current->child;
                counter++;
            }
        } else {//идём с конца
            counter = Size - 1;
            current = this->TAIL;
            while (current != nullptr) {
                if (counter == index) {
                    return current->DATA;
                }
                current = current->parent;
                counter--;
            }
        }
    }
private:
    int Size;
    Node<T>* HEAD;
    Node<T>* TAIL;
};

#endif