#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

#include "paged_array.h"

void quickSort(PagedArray& arr, int low, int high);
int partition(PagedArray& arr, int low, int high);
void insertionSort(PagedArray& arr, int n);
void bubbleSort(PagedArray& arr, int n);

#endif // SORTING_ALGORITHMS_H
