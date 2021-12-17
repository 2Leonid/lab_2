#ifndef quck_sort_hpp
#define quck_sort_hpp
#include "interface.hpp"

template<typename T>
class quck_sort: public sorts<T>{
public:
    void sort(Sequence<T>& arr, bool(*cmp)(const T&, const T&)) {
        quckSort(arr, 0, arr.GetLength() - 1, cmp);
    }

    void quckSort (Sequence<T>& arr, int start, int end, bool(*cmp)(const T&, const T&)) {
        if (end - start <= 1){
            if(!cmp(arr.Get(start), arr.Get(end))){
                T tmp = arr.Get(start);
                arr.Set(start, arr.Get(end));
                arr.Set(end, tmp);
            }
        } else {   
            T key;
            int left = start;
            int right = end;
            if ((end - start) % 2 == 0){
                key = arr.Get((end + start) / 2);
            } else {
                key = arr.Get((end + start + 1) / 2);
            }

            while (right > left) {
                while(cmp(arr.Get(left), key)) left++;
                while(cmp(key, arr.Get(right))) right--;
                if (right > left){
                    T tmp = arr.Get(left);
                    arr.Set(left, arr.Get(right));
                    arr.Set(right, tmp);
                    right--;
                    left++;

                }
            }
            
            if (right - left <= 0){
                if(left < end)
                    quckSort(arr, left, end, cmp);
                if (right > start)
                    quckSort(arr, start, right, cmp);   
            }
        }
    }
};

#endif