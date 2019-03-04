// Compute the running median of a sequence of numbers.That is, given a stream of numbers,
// print out the median of the list so far on each new element.
// Recall that the median of an even -
// numbered list is the average of the two middle numbers.
// For example,
// given the sequence[2, 1, 5, 7, 2, 0, 5], your algorithm should print out :
// 2 1.5 2 3.5 2 2 2
#include <iostream>
#include <cstdio>
using namespace std;
int example[] = {2, 1, 5, 7, 2, 0, 5};


// To find the medians we need sorted lists. Lets use two heaps to store the upper and lower halves for maximum 
// efficiency.
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

class Heap{
    int *heap_array;
    int capacity;
    int heapSize;
    public:
        int getHeapSize(){
            return heapSize;
        }

        Heap(int capacity);

        void MinHeapify(int);

        void MaxHeapify(int);

        int parent(int i)  {
            return (i - 1) / 2;
        }

        int left(int i)  {
            return (2 * i) + 1;
        }

        int right(int i)  {
            return (2 * i) + 2;
        }

        int extractMin();

        int extractMax();

        int getMinOrMax(){
            return heap_array[0];
        }

        void insertKeyMin(int k);

        void insertKeyMax(int k);
};

Heap::Heap(int cap){
    heapSize = 0;
    capacity = cap;
    heap_array = new int[cap];
}

void Heap::insertKeyMin(int k){
    if (heapSize == capacity){
        cout << "\nOverflow: Could not insertKey\n";
        return;
    }

    heapSize++;
    int i = heapSize - 1;
    heap_array[i] = k;

    while (i != 0 && heap_array[parent(i)] > heap_array[i]){
        swap(&heap_array[i], &heap_array[parent(i)]);
        i = parent(i);
    }
}

void Heap::insertKeyMax(int k)
{
    if (heapSize == capacity){
        cout << "\nOverflow: Could not insertKey\n";
        return;
    }

    heapSize++;
    int i = heapSize - 1;
    heap_array[i] = k;

    while (i != 0 && heap_array[parent(i)] < heap_array[i]){
        swap(&heap_array[i], &heap_array[parent(i)]);
        i = parent(i);
    }
}

int Heap::extractMin(){
    if (heapSize <= 0)
        return -1;
    if (heapSize == 1) {
        heapSize--;
        return heap_array[0];
    }

    int root = heap_array[0];
    heap_array[0] = heap_array[heapSize - 1];
    heapSize--;
    MinHeapify(0);

    return root;
}

int Heap::extractMax(){
    if (heapSize <= 0)
        return -1;
    if (heapSize == 1){
        heapSize--;
        return heap_array[0];
    }

    int root = heap_array[0];
    heap_array[0] = heap_array[heapSize - 1];
    heapSize--;
    MaxHeapify(0);

    return root;
}

void Heap::MinHeapify(int i){
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heapSize && heap_array[l] < heap_array[i])
        smallest = l;
    if (r < heapSize && heap_array[r] < heap_array[smallest])
        smallest = r;
    if (smallest != i){
        swap(&heap_array[i], &heap_array[smallest]);
        MinHeapify(smallest);
    }
}

void Heap::MaxHeapify(int i){
    int l = left(i);
    int r = right(i);
    int biggest = i;
    if (l < heapSize && heap_array[l] > heap_array[i])
        biggest = l;
    if (r < heapSize && heap_array[r] > heap_array[biggest])
        biggest = r;
    if (biggest != i){
        swap(&heap_array[i], &heap_array[biggest]);
        MaxHeapify(biggest);
    }
}

// Starts by adding the first number to the lowers heap, after that, if the number is smaller than the biggest number on lowers
// we add it to the lowers heap, otherwise we add it to the highers heap
void addNumber(int number, Heap &lowers, Heap &highers){
    if (lowers.getHeapSize() == 0 || number < lowers.getMinOrMax()) lowers.insertKeyMax(number);
    else highers.insertKeyMin(number);
}

// If there are ever 2 or more items in one heap, reorganize them, taking either the biggest item on the lowers heap
// and putting it on highers or the smallest item on highest and putting it on lowers
void rebalance(Heap &lowers, Heap &highers){
    if (lowers.getHeapSize() > highers.getHeapSize() && (lowers.getHeapSize() - highers.getHeapSize()) >= 2)
        highers.insertKeyMin(lowers.extractMax());
    else if (lowers.getHeapSize() < highers.getHeapSize() && (highers.getHeapSize() - lowers.getHeapSize()) >= 2)
        lowers.insertKeyMax(highers.extractMin());
}

// if there are more items in either heap, it means that that heap's head is the median of the whole array
// if there are the same amount of numbers on both heaps, we take the highest number on lowers and the
// smallest on highers and return their mean.
float getMedian(Heap &lowers, Heap &highers){
    if (lowers.getHeapSize() > highers.getHeapSize()) return lowers.getMinOrMax();
    else if (lowers.getHeapSize() < highers.getHeapSize()) return highers.getMinOrMax();
    else return (float(lowers.getMinOrMax()) + float(highers.getMinOrMax())) / 2;
}

void runningMedian(int sequence[], int size){
    Heap lowers(size / 2 + 1);
    Heap highers(size / 2 + 1);
    for (int i = 0; i < size; i++){
        addNumber(sequence[i], lowers, highers);
        rebalance(lowers, highers);
        cout << getMedian(lowers, highers) << endl;
    }
}

int main(){
    freopen( "Exercise5Output.txt", "w", stdout);  // log output
    int size = sizeof(example) / sizeof(example[0]);
    runningMedian(example, size);
    return 0;
}
