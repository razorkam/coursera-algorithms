#include <iostream>
#include <fstream>


using namespace std;



long mergeNCountSplit(int* arr, int left, int mid, int right){


    int n1 = left;
    int n2 = mid+1;

    int* tmp = new int[right - left + 1];

    int n3 = 0;

    long split = 0;

    while (n1 <= mid && n2 <= right){

        if (arr[n1] < arr[n2]){

            tmp[n3++] = arr[n1++];
        }
        else{

            split += mid - n1 + 1;
            tmp[n3++] = arr[n2++];
        }

    }

    while (n2 <= right){
        tmp[n3++] = arr[n2++];
    }

    while(n1 <= mid){
        tmp[n3++] = arr[n1++];
    }


    for (n3 = 0; n3 < right - left + 1; ++n3){
        arr[left+n3] = tmp[n3];
    }

    delete[] tmp;

    return split;

}

long sortNCount(int* arr, int left, int right){
    if (left == right)
        return 0;

    int mid = (left + right) / 2;

    long l_inv = sortNCount(arr, left, mid);
    long r_inv = sortNCount(arr, mid + 1, right);
    long split = mergeNCountSplit(arr, left, mid, right);
    return l_inv + r_inv + split;
}



int main() {

    ifstream input("input.txt");
    int* src = new int[100000];
    int k = 0;
    int num = 0;
    while (input >> num) {
        src[k++] = num;
    }

    long inv = sortNCount(src, 0, k - 1);
    delete[] src;
    return 0;
}