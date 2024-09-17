#include <iostream>
#include <ctime>

void FillRand(int array[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        array[i] = rand() % 100;
    }
}

void PrintArr(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf(" %d", array[i]);
    }
    printf("\n");
}

double SelectSort(int array[], int size)
{
    int i, j, temp, C = 0, M = 0;
    std::cout << "\nSorting the array..." << std::endl;
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
    return clock() / 1000.0;
}

main()
{
    const int size = 500;
    int array[size];
    FillRand(array, size);
    std::cout << "Unsorted array:" << std::endl;
    PrintArr(array, size);

    double runtime = SelectSort(array, size);
    std::cout << "\nSorted array:" << std::endl;
    PrintArr(array, size);

    std::cout << "\nRuntime: " << runtime << std::endl;

    return 0;
}
