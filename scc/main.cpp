#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;


vector<int> scc(vector<vector<int>>& reversed_graph, vector<vector<int>>& graph, vector<bool>& visited){

    stack<int> dfs_stack;
    vector<bool> finished(reversed_graph.size(), false);
    vector<int> times(reversed_graph.size(), 0);
    long time_index = reversed_graph.size() - 1;
    for (int i = 0; i < reversed_graph.size(); ++i){ //step 1, reversed
       if (!visited[i]){
           dfs_stack.push(i);
           while (!dfs_stack.empty()){
               int top = dfs_stack.top();
               if (!visited[top]){
                   visited[top] = true;
                   for (int head : reversed_graph[top]){
                       if (!visited[head])
                           dfs_stack.push(head);
                   }
               }
               else{

                   if (!finished[top]){
                       times[time_index--] = top;
                       finished[top] = true;
                   }

                   dfs_stack.pop();
               }
           }
       }
    }

    visited.assign(visited.size(), false);
    vector<int> sccs;

    for (int i = 0; i < times.size(); ++i){  //step 2
        int vertex = times[i];
        if (!visited[vertex]){
            dfs_stack.push(vertex);
            visited[vertex] = true;
            int scc_size = 0;
            while(!dfs_stack.empty()){
                int top = dfs_stack.top();
                //visited[top] = true;
                dfs_stack.pop();
                scc_size++;
                for (int head : graph[top]){
                    if (!visited[head]){
                        dfs_stack.push(head);
                        visited[head] = true;
                    }

                }

            }

            sccs.push_back(scc_size);
        }
    }


    sort(sccs.begin(), sccs.end(), std::greater<int>());
    return sccs;
}


int main() {

    ifstream f("test.txt");
    vector<vector<int>> reversed_graph(875714, vector<int>()); //875714
    vector<vector<int>> graph(reversed_graph.size(), vector<int>());
    vector<bool> visited(reversed_graph.size(), false);
    int tail, head;
    while (true){
        if (!(f >> tail))
            break;
        f >> head;
        graph[tail-1].push_back(head-1);
        reversed_graph[head-1].push_back(tail-1); //reversed
    }

    vector<int> sccs;
    sccs = scc(reversed_graph, graph, visited);

    std::cout << "size: " << reversed_graph.size() << std::endl;
    return 0;
}