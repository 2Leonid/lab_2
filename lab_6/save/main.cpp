#include <iostream>
#include "Algorithms.h"
int main() {
    std::ifstream input("Data.txt");
    Graph graph(input);
    for (int i = 0; i < graph.vertices; ++i) {
        if(graph.adjacency_lists[i].GetSize() != 0)
            std::cout << i << " - " << graph.Get(i) << std::endl;
    }

    std::cout << min_way_search(graph,1,3);
    return 0;
}
