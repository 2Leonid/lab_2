#include "Array.h"

DynamicArray<int> dec_to_bin(int a,int n){
    DynamicArray<int> res(n);
    int index = 0;
    while (a > 0){
        res[n - index - 1] = a % 2;
        a /= 2;
        index++ ;
    }
    return res;
}

template<typename T,typename M>
T scalar_multiplication(DynamicArray<T>& lhs,DynamicArray<M>& rhs){
    T res = T();
    for (int i = 0; i < lhs.GetSize(); ++i) {
        res += lhs[i] * rhs[i];
    }
    return res;
}

template<typename T>
class tree_elem{
public:

    T m_data;
    tree_elem* m_left;
    tree_elem* m_right;

    tree_elem(T key){//конструктор для создания нового узла
        m_data = key;
        m_left = NULL;
        m_right = NULL;
    }
    tree_elem(T key,tree_elem<T>* left,tree_elem<T>* right){//конструктор для копирования конкретного узла
        m_data = key;
        m_left = left;
        m_right = right;
    }
};


template<typename T,typename M>
class binary_tree{
private:

    tree_elem<T>* m_root;

    int size;

    void calculations(tree_elem<T>* curr,DynamicArray<M>& weights,DynamicArray<M>& volumes,DynamicArray<M>& prices,M& max_price_right_now,int& res_comb){
        if(curr){

            calculations(curr->m_left,weights,volumes,prices,max_price_right_now,res_comb);

            DynamicArray<int> curr_num = dec_to_bin(curr->m_data,count_of_elements);
            M curr_weight = scalar_multiplication(curr_num,weights);
            M curr_volume = scalar_multiplication(curr_num,volumes);
            M price_of_this_stuff = scalar_multiplication(curr_num,prices);
            if(curr_weight <= max_w && curr_volume <= max_v && price_of_this_stuff >= max_price_right_now){
                max_price_right_now = price_of_this_stuff;
                res_comb = curr->m_data;
            }


            calculations(curr->m_right,weights,volumes,prices,max_price_right_now,res_comb);
        }

    }

    void print_tree(tree_elem<T>* curr){
        if(curr){
            print_tree(curr->m_left);
            std::cout << curr->m_data << " ";
            print_tree(curr->m_right);
        }
    }
public:

    binary_tree(){
        m_root = nullptr;
        size = 0;
    }

    //конструктор с добавлением корня
    binary_tree(int key){
        m_root = new tree_elem<T>(key);
        size = 1;
    }
    ~binary_tree(){
        //delete_tree(m_root);
    }
    int get_size(){return size;}

    int count_of_elements;
    M max_w;
    M max_v;
    //печать дерева
    void print(){
        print_tree(m_root);
        std::cout << std::endl;
    }

    //удаление дерева
    void delete_tree(tree_elem<T>* curr){
        if(curr){
            delete_tree(curr->m_left);
            delete[] curr;
            delete_tree(curr->m_right);
        }
    }

    //поиск элемента в дереве
    bool find(int key){//поиск значения

        tree_elem<T>* curr = m_root;
        while(curr && curr->m_data != key){
            if(curr->m_data > key)
                curr = curr->m_left;
            else
                curr = curr->m_right;
        }
        return (bool)curr;
    }

    //добавление элемента
    void insert(int key){//добавление нового элемента в дерево
        if(m_root == nullptr){
            m_root = new tree_elem<T>(key);
            size = 1;
        }else{
            tree_elem<T>* curr = m_root;
            while(curr && curr->m_data != key){
                if(curr->m_data > key){//переход в левое поддерево
                    if(curr->m_left)//если есть возможность,то так как добавляемое значение меньше того,
                        //что в узле curr,
                        //то мы спускаемся в левое поддерево ещё раз(переход для следующей итерации)
                        curr = curr->m_left;
                    else{//если же возможность спуститься ещё ниже нет,то мы добавляем новый элемент в дерево
                        //(так как мы уже находимся на том месте,куда нужно добавить новый элемент)
                        curr->m_left = new tree_elem<T>(key);
                        size++;
                        return;
                    }
                }//для правого поддерева аналогично
                else{//переход в правое поддерево
                    if(curr->m_right)
                        curr = curr->m_right;
                    else{
                        curr->m_right = new tree_elem<T>(key);
                        size++;
                        return;
                    }
                }
            }
        }
    }


    M calculating_optimal_placement(DynamicArray<M>& weights,DynamicArray<M>& volumes,DynamicArray<M>& prices,int& res_comb){
        M max_price_right_now = M();
        calculations(m_root,weights,volumes,prices,max_price_right_now,res_comb);
        return max_price_right_now;
    }


};