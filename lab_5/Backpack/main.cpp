#include <fstream>
#include <math.h>
#include "Tree.h"



int main() {
    int count_of_things;
    DynamicArray<double> weights;
    DynamicArray<double> volumes;
    DynamicArray<double> prices;

    double max_weight;
    double max_volume;

    std::ifstream in("Data.txt");
    in >> count_of_things;
    in >> max_volume;
    in >> max_weight;

    std::cout << "Count of things :" << count_of_things << "\nMax weight : " << max_weight << "\nMax volume : " << max_volume << std::endl;

    for (int i = 0; i < count_of_things; ++i) {
        double tmp;
        in >> tmp;
        weights.Append(tmp);
    }
    for (int i = 0; i < count_of_things; ++i) {
        double tmp;
        in >> tmp;
        volumes.Append(tmp);
    }
    for (int i = 0; i < count_of_things; ++i) {
        double tmp;
        in >> tmp;
        prices.Append(tmp);
    }
    weights.Print();
    volumes.Print();
    prices.Print();

    binary_tree<int,double> states;

    states.count_of_elements = count_of_things;
    states.max_v = max_volume;
    states.max_w = max_weight;

    for (int i = 0; i < std::pow(2,count_of_things); ++i) {
        states.insert(i);
    }

    int res_comb = 0;
    int result = states.calculating_optimal_placement(weights,volumes,prices,res_comb);
    std::cout << "Res price = " << result << std::endl;
    DynamicArray<int> result_state = dec_to_bin(res_comb,count_of_things);
    std::cout << "Result weights : ";
    for (int i = 0; i < count_of_things; ++i) {
        if(result_state[i])
            std::cout << weights[i] << ' ';
    }

    std::cout << "\nResult volumes : ";
    for (int i = 0; i < count_of_things; ++i) {
        if(result_state[i])
            std::cout << volumes[i] << ' ';
    }

    std::cout << "\nResult prices : ";
    for (int i = 0; i < count_of_things; ++i) {
        if(result_state[i])
            std::cout << prices[i] << ' ';
    }

    std::cout << "\nResult weight : ";
    double res_w = 0;
    for (int i = 0; i < count_of_things; ++i) {
        if(result_state[i])
            res_w += weights[i];
    }
    std::cout << res_w;

    std::cout << "\nResult volume : ";
    double res_v = 0;
    for (int i = 0; i < count_of_things; ++i) {
        if(result_state[i])
            res_v += volumes[i];
    }
    std::cout << res_v;

    std::cout << "\nResult price : ";
    double res_p = 0;
    for (int i = 0; i < count_of_things; ++i) {
        if(result_state[i])
            res_p += prices[i];
    }
    std::cout << res_p;
//    DynamicArray<int> a(5);
//    for (int i = 0; i < 5; ++i) {
//        a[i] = 5 - i + 1;
//    }
//    DynamicArray<int> b(5);
//    for (int i = 0; i < 5; ++i) {
//        b[i] = i + 1;
//    }
//    a.Print();
//    b.Print();
//    std::cout << scalar_multiplication(a,b);

//    for (int i = 0; i < 16; ++i) {
//        std::cout << dec_to_bin(i,4) << std::endl;
//    }
//    binary_tree<int> a(10);
//    for (int i = 0; i < 10; ++i) {
//        a.insert(i);
//    }
//    a.print();

    return 0;
}
