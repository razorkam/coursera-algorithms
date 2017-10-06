#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>



using namespace std;

long comps = 0;


vector<int>::iterator partition(vector<int>::iterator left, vector<int>::iterator right){



    long length = distance(left, right);
    auto middle = left + length / 2;
    if (!(length % 2)){ //even
        middle--;
    }

    int median = *left + *middle + *(right-1) - min(*left, min(*middle, *(right-1))) - max(*left, max(*middle, *(right-1)));

    if (*middle == median){
        iter_swap(left, middle);
    } else if (*(right-1) == median){
        iter_swap(left, right-1);
    }


    int pivot = *left;
    auto i = left+1;
    for (auto j = left+1; j < right; ++j){
        if (*j < pivot){
            iter_swap(i++, j);
        }
    }
    iter_swap(left, i-1);
    return i-1;
}


void qsort(vector<int>::iterator left, vector<int>::iterator right){

    if (right == left)
        return;

    comps += distance(left, right) - 1;
    auto pivot_pos = partition(left, right);
    qsort(left, pivot_pos);
    qsort(pivot_pos+1, right);
}


int main() {

    ifstream input("input.txt");
    int num = 0;
    vector<int> src;
    while (input >> num) {
       src.push_back(num);
    }

    qsort(src.begin(), src.end());

    cout << "Hello" << endl;


    return 0;

}