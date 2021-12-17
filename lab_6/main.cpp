#include <iostream>
#include "Algorithms.h"
int main() {
    std::cout << "What do you want ? Enter 1 or 2 (min_way or approximate coloring)\n";
    char answer;
    std::cin >> answer;
    if(answer == '1'){
        std::ifstream input1("Data1.txt");
        Graph graph1(input1);
        int start;
        std::cout << "Enter start :";
        std::cin >> start;
        int finish;
        std::cout << "Enter finish :";
        std::cin >> finish;

        std::cout << "Your graph :\n";
        graph1.print();
        std::cout << std::endl;
        DynamicArray<int> min_way = min_way_search(graph1,start,finish);
        std::cout << "Length of min way : " << min_way.GetSize() << std::endl;
        std::cout << "Min way : " << min_way;
    }
    if (answer == '2'){
        std::ifstream input2("Data2.txt");
        Graph graph2(input2);
        std::cout << "Second graph :\n";
        graph2.print();
        std::cout << "Approximate coloring of the second graph :\n";
        std::cout << heuristic_coloring(graph2);
    }

    return 0;
}
