#include <stdlib.h>
#include <stdio.h>
#include <iostream>

void FillRand(int array[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        array[i] = rand() % 100;
    }
}

void CheckSum(int array[], int size)
{
    int i, sum = 0;
    for (i = 0; i < size; i++)
    {
        sum += array[i];
    }
    printf("%d\n", sum);
}

void PrintArr(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf(" %d", array[i]);
    }
    printf("\n");
}

void RunNumber(int array[], int size)
{
    int i, k = 1;
    for (i = 0; i < size; i++)
    {
        if (array[i + 1] < array[i])
        {
            k++;
        }
    }
    printf("%d\n", k);
}

void SelectSort(int array[], int size)
{
    int i, j, temp, C = 0, M = 0;
    for (i = 0; i < size - 1; i++)
    {
        M += 3;
        for (j = i + 1; j < size; j++)
        {
            C++;
            if (array[i] > array[j])
            {
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
    printf("\nActual complexity = %d; M = %d\n", C, M);
    printf("Theoretical complexity = %d; M = %d\n", (size * size - size) / 2, 3 * (size - 1));
}

main()
{
    const int size = 10;
    int array[size];
    FillRand(array, size);
    std::cout << "Unsorted array:" << std::endl;
    PrintArr(array, size);

    SelectSort(array, size);
    std::cout << "\nSorted array:" << std::endl;
    PrintArr(array, size);

    return 0;
}
