#include <iostream>
#include <fstream>
#include <random>
#include <list>
#include <sstream>
#include <iterator>
#include <map>
#include <algorithm>


template<typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
    std::uniform_int_distribution<> dst(0, static_cast<int> (std::distance(start, end) - 1));
    std::advance(start, dst(g));
    return start;
}

template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return select_randomly(start, end, gen);
}


int minCut(std::map<int, std::list<int>> &graph){

    int min_edges = 1000;
    int iters = log(200) * 200 * 199 / 2;
    iters = 100;

    for (int it = 0; it < iters; ++it){
        auto cur_graph = graph;

        while (cur_graph.size() > 2){

            auto head = select_randomly(cur_graph.begin(), cur_graph.end());
            auto& head_neighbours = head->second;
            auto tail = *select_randomly(head_neighbours.begin(), head_neighbours.end());
            auto tail_neighbours = cur_graph.at(tail);
            for (auto i : tail_neighbours){
                auto& neis = cur_graph[i];
                for (auto j = neis.begin(); j != neis.end(); ++j){
                    if (*j == tail){
                        *j = head->first;
                    }
                }
            }

            head_neighbours.insert(head_neighbours.end(), tail_neighbours.begin(), tail_neighbours.end());
            cur_graph.erase(tail);


            for (auto i = head_neighbours.begin(); i != head_neighbours.end();){
                if (*i == head->first){
                    i = head_neighbours.erase(i);
                } else{
                    ++i;
                }

            }

        }

        if (cur_graph.begin()->second.size() < min_edges){
            min_edges = cur_graph.begin()->second.size();
        }

    }




    return min_edges;
}


int main() {

    std::ifstream in("input.txt");

    std::map<int, std::list<int>> src;

    std::string line;
    while(getline(in, line)){
        std::stringstream ss(line);
        int head;
        ss >> head;
        std::list<int> tails;
        int tail;
        while(ss >> tail){
            tails.push_back(tail);
        }

       src[head] = tails;
    }

    in.close();

    int res = minCut(src);


    std::cout << "Hello" << std::endl;
    return 0;
}



