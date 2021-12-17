#include <iostream>
#include <time.h>
#include <random>
#include <fstream>

#include "Array.hpp"
#include "ArraySequence.hpp"
#include "LinkedList.hpp"
#include "LinkedListSequence.hpp"
#include "Sequence.hpp"
#include "interface.hpp"
#include "bubble_sort.hpp"
#include "quck_sort.hpp"
#include "heap_sort.hpp"

void read(Sequence<int> &,std :: ifstream &);
void Rand(Sequence<int> &,long long int );
void print(Sequence<int>&, Sequence<int>&);

bool cmp(const int &a, const int &b) {
	return a < b;
}

bool cmp_r(const int &a, const int &b) {
	return a > b;
}


//main

int main () {
	srand(time(nullptr));
	ArraySequence<int> arr;



	std :: string u_i[8] = {"1. Отсортировать данные быстрой сортировкой", "2.Отсортировать данные пиромидальной сортировкой", "3.Отсортировать данные сортировкой пузырьком", "4.Проанализировать работу быстрой сортировка", "5.Проанализировать работу пирамидальной сортировки ", "6.Ввести данные с файла", "0.Выход", "Если данные не введены, сортируется массив заполненый рандомными данными. При сортировки выводится время сортировки. При сравнение сортировок сохраняется файл с временем сортировки и колличеством данных."};
	for (int i = 0; i < 8; i++){
		std :: cout << u_i[i] << '\n';
	}

	int p = 0;
	std :: cin >> p;
	bubble_sort<int> sort_b;
	heap_sort<int> sort_h;
	quck_sort<int> sort_q;

	while(p != 0){
		switch (p){
			case 1:{
				if(!arr.GetLength()){
					int n = 0;
					std :: cout << "Введите колличество элементов" << '\n';
					std :: cin >> n;
					Rand(arr, n);
				}
				ArraySequence<int> copy_arr(arr);
				clock_t t = clock();
				sort_q.sort(copy_arr, cmp);
				t = clock() - t;
				//std::cout << clock() << " " << t << std::endl;
				double time = (double)t / CLOCKS_PER_SEC;
				print(copy_arr, arr);
				printf("Время паботы: %lf \n", time);
				break;
			}
			case 2:{
				if(!arr.GetLength()){
					int n = 0;
					std :: cout << "Введите колличество элементов" << '\n';
					std :: cin >> n;
					Rand(arr, n);
				}
				ArraySequence<int> copy_arr(arr);
				clock_t t = clock();
				sort_h.sort(copy_arr, cmp);
				t = clock() - t;
				double time = (double)t / CLOCKS_PER_SEC;
				//print(copy_arr, arr);
				printf("Время паботы: %f \n", time);
				break;
			}
			case 3:{
				if(!arr.GetLength()){
					int n = 0;
					std :: cout << "Введите колличество элементов" << '\n';
					std :: cin >> n;
					Rand(arr, n);
				}
				ArraySequence<int> copy_arr(arr);
				clock_t t = clock();
				sort_b.sort(copy_arr, cmp);
				t = clock() - t;
				double time = (double)t / CLOCKS_PER_SEC;
				//print(copy_arr, arr);
				printf("Время работы: %f \n", time);
				break;
			}
			case 4:{
				std :: ofstream q_s_s;
				std :: ofstream q_s_g;
				std :: ofstream q_s_r;
				q_s_s.open("q_s_s.txt");
				q_s_g.open("q_s_g.txt");
				q_s_r.open("q_s_r.txt");

				for (int i = 10000; i <= 100000000; i+= i / 100){
					ArraySequence<int> arr_s;
					//1
					Rand(arr_s, i);
					clock_t t = clock();
					sort_q.sort(arr_s, cmp);
					t = clock() - t;
					double time = (double)t / (double)CLOCKS_PER_SEC;
					q_s_s << i << ' ' << time << '\n';
					//2
					t = clock();
					sort_q.sort(arr_s, cmp);
					t = clock() - t;
					time = (double)t / CLOCKS_PER_SEC;
					q_s_g << i << ' ' << time << '\n';
					//3
					t = clock();
					sort_q.sort(arr_s, cmp_r);
					t = clock() - t;
					time = (double)t / CLOCKS_PER_SEC;
					q_s_r << i << ' ' << time << '\n';
				}
				std :: cout <<"chek!";
				q_s_s.close();
				q_s_g.close();
				q_s_r.close();

				std :: ofstream q_l_s;
				std :: ofstream q_l_g;
				std :: ofstream q_l_r;
				q_l_s.open("q_l_s.txt");
				q_l_g.open("q_l_g.txt");
				q_l_r.open("q_l_r.txt");

				for (int i = 100; i <= 10000000; i+=10){
					LinkedListSequence<int> list;
					//1
					Rand(list, i);
					clock_t t = clock();
					sort_q.sort(list, cmp);
					t = clock() - t;
					double time = (double)t / CLOCKS_PER_SEC;
					q_l_s << time << ' ' << i << '\n';
					//2
					t = clock();
					sort_q.sort(list, cmp);
					t = clock() - t;
					time = (double)t / CLOCKS_PER_SEC;
					q_l_g << time << ' ' << i << '\n';
					//3
					t = clock();
					sort_q.sort(list, cmp_r);
					t = clock() - t;
					time = (double)t / CLOCKS_PER_SEC;
					q_l_r << time << ' ' << i << '\n';
				}
				std :: cout <<"chek!";
				q_l_s.close();
				q_l_g.close();
				q_l_r.close();
				 break;
			}
			case 5:{
				std :: ofstream h_s_s;
				std :: ofstream h_s_g;
				std :: ofstream h_s_r;
				h_s_s.open("h_s_s.txt");
				h_s_g.open("h_s_g.txt");
				h_s_r.open("h_s_r.txt");

				for (int i = 1000; i <= 13000000; i+=i/100){
					ArraySequence<int> arr_s;
					//1
					Rand(arr_s, i);
					clock_t t = clock();
					sort_h.sort(arr_s, cmp);
					t = clock() - t;
					double time = (double)t / CLOCKS_PER_SEC;
					h_s_s << time << ' ' << i << '\n';
					//2
					t = clock();
					sort_h.sort(arr_s, cmp);
					t = clock() - t;
					time = (double)t / CLOCKS_PER_SEC;
					h_s_g << time << ' ' << i << '\n';
					//3
					t = clock();
					sort_h.sort(arr_s, cmp_r);
					t = clock() - t;
					time = (double)t / CLOCKS_PER_SEC;
					h_s_r << time << ' ' << i << '\n';
				}
				std :: cout <<"chek!";
				h_s_s.close();
				h_s_g.close();
				h_s_r.close();

				std :: ofstream h_l_s;
				std :: ofstream h_l_g;
				std :: ofstream h_l_r;
				h_l_s.open("h_l_s.txt");
				h_l_g.open("h_l_g.txt");
				h_l_r.open("h_l_r.txt");

				for (int i = 1000; i <= 13000000; i+=i/100){
					LinkedListSequence<int> list;
					//1
					Rand(list, i);
					clock_t t = clock();
					sort_h.sort(list, cmp);
					t = clock() - t;
					double time = (double)t / CLOCKS_PER_SEC;
					h_l_s << time << ' ' << i << '\n';
					//2
					t = clock();
					sort_h.sort(list, cmp);
					t = clock() - t;
					time = (double)t / CLOCKS_PER_SEC;
					h_l_g << time << ' ' << i << '\n';
					//3
					t = clock();
					sort_h.sort(list, cmp_r);
					t = clock() - t;
					time = (double)t / CLOCKS_PER_SEC;
					h_l_r << time << ' ' << i << '\n';
				}
				std :: cout <<"chek!";
				h_l_s.close();
				h_l_g.close();
				h_l_r.close();

				break;
			}
			default:
			{
				std::cerr << "Error input" << std::endl;
				break;
			}
		 }
		 for (int i = 0; i < 8; i++){
			std :: cout << u_i[i] << '\n';
		}	
		std :: cin >> p;
	}

	return 0;
} 

void read(Sequence<int> & data, std :: ifstream& file){
	int i = 0;
	while(!file.eof()){
		file >> i;
		data.Append(i);
	}

}

void Rand(Sequence<int> & data, long long d){
	for ( int i = 0; i <= d; i++){
		data.Append(rand()%1000000000);
	}

}

void print(Sequence<int>& arr){
	for( int i = 0; i < arr.GetLength() - 1; i++){
		std :: cout << i << ' ' << arr.Get(i) << '\n';
	}
}

void print(Sequence<int>& arr, Sequence<int>& arr_o){
	for( int i = 0; i < arr.GetLength() - 1; i++){
		std :: cout << i << ' ' << arr.Get(i) << ' ' << arr_o.Get(i) << '\n';
	}
}