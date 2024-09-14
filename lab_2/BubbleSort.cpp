#include <stdio.h>
#include <stdlib.h>

void FillInc(int A[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        A[i] = i;
    }
}

void FillDec(int A[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        A[i] = n - i;
    }
}

void FillRand(int A[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        A[i] = rand() % 100;
    }
}

void PrintMas(int A[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf(" %d", A[i]);
    }
    printf("\n");
}

void BubbleSort(int A[], int n)
{
    int i, j, temp;
    int M = 0, C = 0; // количество пересылок и сравнений
    for (i = 0; i < n - 1; i++)
    {
        for (j = n - 1; j >= i + 1; j--)
        {
            C++;
            if (A[j] < A[j - 1])
            {
                temp = A[j];
                A[j] = A[j - 1];
                A[j - 1] = temp;
                M += 3;
            }
        }
    }
    printf("fact M + C = %d\n", M + C);
}

main()
{
    int n;

    for (n = 100; n <= 500; n += 100)
    {
        int A[n];
        printf("\n\n n = %d\n", n);

        printf("\nDec arr\n");
        FillDec(A, n);
        printf("theor M + C = %d\n", 3 * (n * n - n) / 2 + (n * n - n) / 2);
        BubbleSort(A, n);

        printf("\nRand arr\n");
        FillRand(A, n);
        printf("theor M + C %d\n", 3 * (n * n - n) / 4 + (n * n - n) / 2);
        BubbleSort(A, n);

        printf("\nInc arr\n");
        FillInc(A, n);
        printf("theor M + C = %d\n", 0 + (n * n - n) / 2);
        BubbleSort(A, n);
    }
    return 0;
}