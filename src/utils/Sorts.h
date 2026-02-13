#ifndef SORTS_H
#define SORTS_H
#include <iostream>
using namespace std;

// Made By daddy g

template <typename T>
class Sorts
{
public:
    Sorts() {}

    void swap(T &a, T &b)
    {
        T temp = a;
        a = b;
        b = temp;
    }
    void bubbleSort(T array[], int size)
    {
        for (int i = 0; i < size - 1; i++)
        {
            for (int j = 0; j < size - 1 - i; j++)
            {
                if (array[j] > array[j + 1])
                {
                    swap(array[j], array[j + 1]);
                }
            }
        }
    }

    void merge(T array[], int left, int mid, int right)
    {
        int n1 = mid - left + 1; // maintaining fthe sizes of the halves
        int n2 = right - mid;

        T *temp1 = new T[n1]; // creating arrays of the sizes
        T *temp2 = new T[n2];

        for (int i = 0; i < n1; i++)
            temp1[i] = array[left + i]; // copying elements to em
        for (int i = 0; i < n2; i++)
            temp2[i] = array[mid + 1 + i];

        int a = 0, b = 0;
        int c = left; // maintaining a variable that picks up elements for the original array

        while (a < n1 && b < n2) // parsing the variables to the sizes
        {
            if (temp1[a] <= temp2[b]) // picking up the ascending elements
            {
                array[c] = temp1[a];
                a++;
            }
            else
            {
                array[c] = temp2[b];
                b++;
            }
            c++;
        }

        while (a < n1) // solving even odd complication, such that an element remains in the new array
        {
            array[c] = temp1[a];
            a++;
            c++;
        }
        while (b < n2)
        {
            array[c] = temp2[b];
            b++;
            c++;
        }

        delete[] temp1; // deleting the arrays to prevent any memory leak
        delete[] temp2;
    }
    void mergeSort(T array[], int left, int right)
    {
        if (left >= right) // base condition for recursion
            return;

        int mid = left + (right - left) / 2; // mantaining a mid

        mergeSort(array, left, mid);        // recursing for the first half
        mergeSort(array, mid + 1, right); // recursing for the second half

        merge(array, left, mid, right); // actually calling the merging functionality
    }
};


#endif