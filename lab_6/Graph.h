#include "Array.h"
#include "Pair.h"
#include <fstream>

class Graph{
public:
    int vertices;

    DynamicArray<Pair<int,DynamicArray<int>>> adjacency_lists;
    Graph(std::ifstream& input){
        input >> vertices;//количество вершин,о которых содержится информания в файле
        adjacency_lists.Resize(vertices);//0 - эффективное значение(хотя мб пригодится для случая нумерации вершин с 0)
        int index = 0;
        for (int i = 0; i < vertices; ++i) {
            int tmp_v;//номер вершины для которой в данной строке указана окрестность
            int size_of_vicinity;//размер окрестности данной вершины
            input >> tmp_v >> size_of_vicinity;

            DynamicArray<int> tmp_vicinity;
            for (int j = 0; j < size_of_vicinity; ++j) {
                int tmp_vicinity_vertice;
                input >> tmp_vicinity_vertice;
                tmp_vicinity.Append(tmp_vicinity_vertice);
            }
            adjacency_lists[index] = {tmp_v,tmp_vicinity};
            index++;
        }

    }
    void print(){
        for (int i = 0; i < vertices; ++i) {
            std::cout << adjacency_lists.Get(i) <<std::endl;
        }
    }
    DynamicArray<int> Get(int value_num){

        for (int i = 0; i < adjacency_lists.GetSize(); ++i) {
            if(adjacency_lists.Get(i).first == value_num)
                return adjacency_lists.Get(i).second;
        }
        return DynamicArray<int>();

    }
};

std::ostream & operator << (std::ostream & out, Graph graph){
    return out << graph.adjacency_lists;
}