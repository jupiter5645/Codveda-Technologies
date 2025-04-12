#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubbleSort(int arr[], int n);
void quickSort(int arr[], int low, int high);
int partition(int arr[], int low, int high);
int linearSearch(int arr[], int n, int key);
int binarySearch(int arr[], int low, int high, int key);
void printArray(int arr[], int n);
void compareTimeComplexity();

int main() {
    int n, choice, key;
    
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);
    
    int *arr = (int *)malloc(n * sizeof(int));
    
    printf("Enter the elements of the array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Choose sorting algorithm:\n1. Bubble Sort\n2. Quick Sort\n");
    scanf("%d", &choice);
    
    clock_t start, end;
    
    switch (choice) {
        case 1:
            start = clock();
            bubbleSort(arr, n);
            end = clock();
            printf("Sorted array using Bubble Sort:\n");
            printArray(arr, n);
            break;
        case 2:
            start = clock();
            quickSort(arr, 0, n - 1);
            end = clock();
            printf("Sorted array using Quick Sort:\n");
            printArray(arr, n);
            break;
        default:
            printf("Invalid choice!\n");
            free(arr);
            return 1;
    }
    
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", time_taken);
    
    printf("Enter the element to search: ");
    scanf("%d", &key);
    

    int linearResult = linearSearch(arr, n, key);
    if (linearResult != -1) {
        printf("Element found at index %d using Linear Search.\n", linearResult);
    } else {
        printf("Element not found using Linear Search.\n");
    }
    
    // Binary Search (requires sorted array)
    int binaryResult = binarySearch(arr, 0, n - 1, key);
    if (binaryResult != -1) {
        printf("Element found at index %d using Binary Search.\n", binaryResult);
    } else {
        printf("Element not found using Binary Search.\n");
    }
    

    compareTimeComplexity();
    
    free(arr);
    return 0;
}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j + 1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            // Swap arr[i] and arr[j]
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    // Swap arr[i + 1] and arr[high] (or pivot)
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

int linearSearch(int arr[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if ( arr[i] == key) {
            return i; // Return the index
        }
    }
    return -1; // Element not found
}

int binarySearch(int arr[], int low, int high, int key) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == key) {
            return mid; // Return the index
        }
        if (arr[mid] < key) {
            low = mid + 1; // Search in the right half
        } else {
            high = mid - 1; // Search in the left half
        }
    }
    return -1; // Element not found
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void compareTimeComplexity() {
    printf("Time Complexity:\n");
    printf("Bubble Sort: O(n^2)\n");
    printf("Quick Sort: O(n log n)\n");
    printf("Linear Search: O(n)\n");
    printf("Binary Search: O(log n)\n");
}
