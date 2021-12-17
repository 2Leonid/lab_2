#include "Graph.h"
#include "LinkedList.h"
#include <limits>
#include <queue>

DynamicArray<int> min_way_search(Graph& graph,int start,int finish){
    DynamicArray<int> dist(graph.vertices + 1);
    for (int i = 0; i < dist.GetSize(); ++i) {
        dist[i] = std::numeric_limits<int>::max();
    }

    DynamicArray<int> prev(graph.vertices + 1);
    for (int i = 0; i < prev.GetSize(); ++i) {
        prev[i] = -1;
    }

    dist[start] = 0;
    LinkedList<int> queue;
    queue.push(start);

    while (!queue.empty()){
        int u = queue.pop();
        for (int i = 0; i < graph.Get(u).GetSize(); ++i) {
            if(dist[graph.Get(u).Get(i)] == std::numeric_limits<int>::max()){
                dist[graph.Get(u).Get(i)] = dist[u] + 1;
                queue.push(graph.Get(u).Get(i));
                prev[graph.Get(u).Get(i)] = u;
            }
        }
    }

    //восстановление ответа
    DynamicArray<int> answer;
    int curr = finish;
    while (curr != -1){
        answer.Append(curr);
        curr = prev[curr];
    }

    for (int i = 0; i < answer.GetSize() / 2; ++i) {
        int tmp = answer[i];
        answer[i] = answer[answer.GetSize() - i - 1];
        answer[answer.GetSize() - i - 1] = tmp;
    }
    return answer;
}

DynamicArray<Pair<int,char>> heuristic_coloring(Graph& graph){

    DynamicArray<Pair<int,DynamicArray<int>>> tmp_graph = graph.adjacency_lists;
    for (int i = 0; i < tmp_graph.GetSize(); ++i) {
        for (int j = 0; j < tmp_graph.GetSize(); ++j) {
            if(tmp_graph.Get(i).second.GetSize() >= tmp_graph.Get(j).second.GetSize()){
                Pair<int,DynamicArray<int>> tmp = tmp_graph.Get(i);
                tmp_graph.Get(i) = tmp_graph.Get(j);
                tmp_graph.Get(j) = tmp;
            }
        }
    }

    DynamicArray<int> vert(tmp_graph.GetSize());//здесь хранятся номера вершин в порядке убывания степеней
    for (int i = 0; i < tmp_graph.GetSize(); ++i) {
        vert[i] = tmp_graph.Get(i).first;
    }

    DynamicArray<Pair<int,char>> ans(vert.GetSize());
    for (int i = 0; i < ans.GetSize(); ++i) {
        ans[i] = {vert[i],' '};
    }

    char curr_color = 'A';
    bool flag = true;
    for (int k = 0; k < ans.GetSize(); ++k) {
        if(ans[k].second == ' '){
            ans[k].second = curr_color;
            for (int i = k; i < ans.GetSize(); ++i) {
                for (int j = i; j >= 0; --j) {
                    if (graph.Get(ans[j].first).is_there(ans[i].first) && ans[j].second == curr_color)//если находится вершина,раскрашенная и связанная с текущей,то раскраска текущей не происходит
                        flag = false;
                }
                if (flag)
                    ans[i].second = curr_color;
                flag = true;
            }
            curr_color = char(curr_color + 1);
        }
    }

    return ans;
}
