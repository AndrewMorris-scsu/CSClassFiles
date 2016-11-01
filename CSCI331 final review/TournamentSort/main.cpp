#include <iostream>
#include <queue>


using namespace std;

struct Example {
    int value;
    int run;
};

struct MaxHeap
{
    bool operator()(Example const &a, Example const &b) { return a.value < b.value; }
};

struct MinHeap
{
    bool operator()(Example const &a, Example const &b) { return a.value > b.value; }
};

int main() {


    priority_queue<Example, vector<Example>, ((Minimizing)? MinHeap: MaxHeap)> Heap;

    int a[] = {5, 4, 2, 3, 5, 2, 6, 6, 7, 2, 3, 1};
    Example Array[12];


    for (int i = 0; i < 12; i++) {
        Array[i].value = a[i];
        Array[i].run = 0;
    }



    for (int i = 0; i < 12; i++) {
        Heap.push(Array[i]);
    }

    for (int i = 0; i < 12; i++ ) {
        Example temp;
        temp = Heap.top();

        cout <<  temp.value << endl;
        Heap.pop();
    }


    return 0;
}