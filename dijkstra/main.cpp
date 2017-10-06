#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
struct edge {
    int head;
    int tail;
    int weight;
};


void dijkstra (vector<edge>& edges, int start){

    vector<bool> visited(200,false);
    vector<int> marks(200, 1000000);
    marks.at(start-1) = 0;
    visited.at(start-1) = true;


    while (true) {
        int dgc = 1000000;
        int vertex;

        for (edge e : edges) {
            if (visited.at(e.tail - 1) && !visited.at(e.head - 1)) {
                if (marks.at(e.tail - 1) + e.weight < dgc) {
                    dgc = marks.at(e.tail - 1) + e.weight;
                    vertex = e.head;
                }
            }

        }

        visited.at(vertex - 1) = true;
        marks.at(vertex - 1) = dgc;
        if (dgc == 1000000)
            break;
    }



}

int main() {

    ifstream in("data.txt");
    string line;
    vector<edge> edges;
    edge e;
    string hw;
    while(getline(in,line)){
        stringstream ss(line);
        ss >> e.tail;
        while(ss.good()){
            ss >> hw;
            stringstream hws(hw);
            string head, weight;
            getline(hws, head, ',');
            getline(hws, weight, ',');
            e.head = stoi(head);
            e.weight = stoi(weight);
            edges.push_back(e);
        }

    }

    dijkstra(edges, 1);
    return 0;
}