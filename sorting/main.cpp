#include <iostream>
using namespace std;

int k, N, quickCall;

void insertion(int list[]){
    int i, j, result = 0, key;
    for(i = 1; i < N; i++){
        key = list[i];
        for(j = i - 1; j >= 0 && list[j] > key; j--){
            result++;
            list[j + 1] = list[j];
        }
        list[j + 1] = key;
        if(j >= 0) result++;
        if(i == k){
            cout << result;
            return;
        }
    }
}

void selection(int list[]){
    int smallest;
    for(int i = 0; i < N - 1; i++){
        smallest = i;
        for(int j = i + 1; j < N; j++)
            if(list[j] < list[smallest])
                smallest = j;
        
        swap(list[smallest], list[i]);

        if(k == i + 1){
            for(int k = 0; k < N; k++)
                cout << list[k] << "\n";
            return;
        }
    }
}

int partition(int list[], int low, int high){
    int left = low + 1;
    int pivotValue = list[low];
    int right = high;

    while(left <= right){
        while(list[left] <= pivotValue && high > low) left++;
        while(list[right] >= pivotValue && low < right) right--;
        if(left < right)    
            swap(list[left], list[right]);
    }
    list[low] = list[right];
    list[right] = pivotValue;
    return right;
}

void quicksort(int list[], int low, int high){
    int pivot;
    if(high > low){
        pivot = partition(list, low, high);
        quickCall++;
        if(k == quickCall){
            for(int i = 0; i < N; i++)
                cout << list[i] << "\n";
            exit(0);
        }
        quicksort(list, low, pivot - 1);
        quicksort(list, pivot + 1, high);
    }
}

void makeMinHeap(int list[], int root, int n, bool update){
    int parent = list[root];
    int leftChild = 2 * root + 1;
    
    for(; leftChild < n; leftChild = leftChild * 2 + 1){
        if(leftChild < n && list[leftChild] > list[leftChild + 1])
                leftChild++;
        if(update && leftChild >= n) leftChild--;
        
        if(parent <= list[leftChild]) 
            break;

        list[(leftChild - 1) / 2] = list[leftChild];
    }
    list[(leftChild - 1) / 2] = parent;
}

void heapSort(int list[], int n, int k){
    for(int i = n / 2 - 1; i >= 0; i--)
        makeMinHeap(list, i, n, false);
    
    for(int i = 0; i < k; i++){
        swap(list[0], list[n - (i + 1)]);
        makeMinHeap(list, 0, n - (i + 1), true);
    }
}

int main(){
    int sortingType;
    cin >> sortingType >> k;
    cin >> N;

    int arr[N];

    for(int i = 0; i < N; i++)  
        cin >> arr[i];

    if(sortingType == 1)
        insertion(arr);
    
    else if(sortingType == 2)
        selection(arr);

    else if(sortingType == 3) {
        heapSort(arr, N, k);
        for(int i = 0; i < N - k; i++)
            cout << arr[i] << "\n";
    }

    else if(sortingType == 4){
        quicksort(arr, 0, N - 1);
        if(quickCall)
            for(int i = 0; i < N; i++)  
                cout << arr[i] << "\n";
    }

    return 0;
}