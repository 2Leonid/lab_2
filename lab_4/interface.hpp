#ifndef interface_hpp
#define interface_hpp


template<typename T>
class sorts{
public:
    void sort(Sequence<T>&, bool(*cmp)(T, T));
};

#endif