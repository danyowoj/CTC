#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>

int Compare = 0, M = 0;
typedef struct st
{
    struct st *next;
    int element;
} list;

typedef struct queue
{
    list *head = NULL;
    list *tail = NULL;
} line;

void Decrease(list *&head, int n)
{

    list *current;
    for (int i = 0; i < n; i++)
    {
        current = new list[1];
        current->element = i;
        current->next = head;
        head = current;
    }
}

void Increase(list *&head, int n)
{

    list *current;
    for (int i = 0; i < n; i++)
    {
        current = new list[1];
        current->element = n - i;
        current->next = head;
        head = current;
    }
}

void Random(list *&head, int n)
{

    list *current;
    for (int i = 0; i < n; i++)
    {
        current = new list[1];
        current->element = rand() % 10;
        current->next = head;
        head = current;
    }
}

void PrintStruct(list *&head)
{
    list *current;
    for (current = head; current; current = current->next)
    {
        printf("%3d", current->element);
    }
}

void Sum(list *&head)
{
    list *current;
    int sum = 0;
    for (current = head; current; current = current->next)
    {
        sum += current->element;
    }
    printf("\nSum = %d\n", sum);
}

void RunNumber(list *&head)
{
    list *current;
    int run = 1;
    for (current = head; current->next; current = current->next)
    {
        if (current->next->element < current->element)
        {
            run++;
        }
    }
    printf("RunNumber = %d\n", run);
}

void Clear(list *&head)
{
    list *q, *current;
    q = current = head; // assigning q and current to the head value
    while (current != NULL)
    {
        current = q->next; // assigning the current value of a list item after q
        delete q;
        q = current; // assigning q to the current value
    }
    head = NULL;
}

void FromListToLine(list *&list, line &queue)
{
    queue.tail->next = list;
    queue.tail = list;
    list = list->next;
}

void Merge(list *&A, int &q, list *&B, int &r, line &C)
{
    while ((q != 0) && (r != 0))
    {
        Compare++;
        if (A->element <= B->element)
        {
            FromListToLine(A, C);
            q = q - 1;
            M++;
        }
        else
        {
            FromListToLine(B, C);
            r = r - 1;
            M++;
        }
    }
    while (q > 0)
    {
        M++;
        FromListToLine(A, C);
        q = q - 1;
    }
    while (r > 0)
    {
        M++;
        FromListToLine(B, C);
        r = r - 1;
    }
}

int Split(list *&S, list *&A, list *&B)
{
    list *k, *p;
    int n = 1;
    A = S, B = S->next;
    k = A, p = B;
    while (p != NULL)
    {
        M += 2;
        n++;
        k->next = p->next;
        k = p;
        p = p->next;
    }
    return n;
}

void MergeSort(list *&S)
{
    int q, r;
    list *A, *B;
    A = B = NULL;
    line C[2];
    int length = Split(S, A, B);
    int p = 1;
    while (p < length)
    {
        for (int i = 0; i < 2; i++)
        {
            C[i].tail = (list *)&C[i].head;
        }
        int i = 0, m = length;
        while (m > 0)
        {
            if (m >= p)
            {
                q = p;
            }
            else
            {
                q = m;
            }
            m = m - q;
            if (m >= p)
            {
                r = p;
            }
            else
            {
                r = m;
            }
            m = m - r;
            Merge(A, q, B, r, C[i]);
            i = 1 - i;
        }
        A = C[0].head;
        B = C[1].head;
        p = 2 * p;
    }
    C[0].tail->next = NULL;
    S = C[0].head;
    printf("C = %d\tM = %d\tC+M = %d\n", Compare, M, Compare + M);
}

int main()
{
    srand(time(NULL));
    int n = 10;
    list *head;
    head = NULL;
    Compare = 0, M = 0;
    printf("=========Decrease=========\n");
    Decrease(head, n);
    PrintStruct(head);
    Sum(head);
    RunNumber(head);
    MergeSort(head);
    PrintStruct(head);
    Sum(head);
    RunNumber(head);
    Clear(head);

    Compare = 0, M = 0;
    head = NULL;
    printf("\n=========Increase=========\n");
    Increase(head, n);
    PrintStruct(head);
    Sum(head);
    RunNumber(head);
    MergeSort(head);
    PrintStruct(head);
    Sum(head);
    RunNumber(head);
    Clear(head);

    Compare = 0, M = 0;
    head = NULL;
    printf("\n=========Random=========\n");
    Random(head, n);
    PrintStruct(head);
    Sum(head);
    RunNumber(head);
    MergeSort(head);
    PrintStruct(head);
    Sum(head);
    RunNumber(head);
    Clear(head);
}