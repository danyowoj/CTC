#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

string ToString(int i)
{
    stringstream ss;
    ss << i;
    return ss.str();
}

int StrToInt(char b)
{
    return b - '0';
}

int oper = 0;

int Multiplication(string, string);

int oper_sum = 0;
int oper_umnoj = 0;

string mult(string, string);

string sum(string, string);

string multWithPow(string, int);

string multWithNum(string, int);

string sub(string, string);

string generateNumber(int digits, bool withOverflow)
{
    string num;
    for (int i = 0; i < digits; i++)
    {
        num += '9';
    }
    if (withOverflow)
    {
        num[0] = '1';
    }
    return num;
}

bool isOverflow(string result, int digits)
{
    return result.length() > digits * 2;
}

void printMultiplicationSteps(string num1, string num2)
{
    cout << num1 << " * " << num2 << endl;
}

void printTable()
{
    cout << "Разрядность | Без переполнения | С одним переполнением | С двумя переполнениями | Итог" << endl;
    cout << "------------------------------------------------------------------------------------------" << endl;

    int digits[] = {1, 2, 4, 8, 16};
    for (int d : digits)
    {
        string num1 = generateNumber(d, false);
        string num2 = generateNumber(d, false);

        printMultiplicationSteps(num1, num2);
        string resultNoOverflow = mult(num1, num2);
        bool overflowNoOverflow = isOverflow(resultNoOverflow, d);

        num1 = generateNumber(d, true);
        num2 = generateNumber(d, false);

        printMultiplicationSteps(num1, num2);
        string resultOneOverflow = mult(num1, num2);
        bool overflowOneOverflow = isOverflow(resultOneOverflow, d);

        num1 = generateNumber(d, true);
        num2 = generateNumber(d, true);

        printMultiplicationSteps(num1, num2);
        string resultTwoOverflow = mult(num1, num2);
        bool overflowTwoOverflow = isOverflow(resultTwoOverflow, d);

        cout << "          " << d << " | ";
        if (overflowNoOverflow)
        {
            cout << "Переполнение";
        }
        else
        {
            cout << resultNoOverflow;
        }
        cout << " | ";
        if (overflowOneOverflow)
        {
            cout << "Переполнение";
        }
        else
        {
            cout << resultOneOverflow;
        }
        cout << " | ";
        if (overflowTwoOverflow)
        {
            cout << "Переполнение";
        }
        else
        {
            cout << resultTwoOverflow;
        }
        cout << " | ";
        if (overflowNoOverflow || overflowOneOverflow || overflowTwoOverflow)
        {
            cout << "Переполнение";
        }
        else
        {
            cout << "Успех";
        }
        cout << endl;
    }
}

int main()
{
    setlocale(LC_ALL, "");

    printTable();

    return 0;
}

void swap(string &aStr, string &bStr)
{
    int k = 0;
    int l = 0;
    int n = aStr.length();
    int m = bStr.length();
    for (int i = n - 1; i >= 0; i--)
    {
        if (StrToInt(aStr[i]) == 0)
        {
            k++;
        }
        else
        {
            break;
        }
    }
    for (int i = m - 1; i >= 0; i--)
    {
        if (StrToInt(bStr[i]) == 0)
        {
            l++;
        }
        else
        {
            break;
        }
    }
    if (n - k < m - l)
    {
        string tmp = bStr;
        bStr = aStr;
        aStr = tmp;
    }
}

int Multiplication(string aStr, string bStr)
{
    int t;
    int n = aStr.length();
    int m = bStr.length();
    t = n + m;
    int *C = new int[t];
    for (int i = 0; i < t; i++)
        C[i] = 0;
    int tmp = 0;
    int tmp_str = 0;
    int k = 0;
    double mnoj_j = 0.1;
    double mnoj_i = 1;
    for (int j = m - 1; j >= 0; j--)
    {
        mnoj_j *= 10;
        if (StrToInt(bStr[j]) != 0)
        {
            tmp_str = 0;
            mnoj_i = 0.1;
            for (int i = n - 1; i >= 0; i--)
            {
                mnoj_i *= 10;
                if (StrToInt(aStr[i]) != 0)
                {
                    tmp_str += StrToInt(aStr[i]) * StrToInt(bStr[j]) * mnoj_i;
                    // cout << j << " - " << i << " : " << StrToInt(aStr[i]) * StrToInt(bStr[j]) << endl;
                    oper_umnoj++;
                }
            }
            cout << "\t" << tmp_str << endl;
            tmp += tmp_str * mnoj_j;
            oper_sum++;
        }
        // cout << "tmp: " << tmp << endl;
    }
    return tmp;
}

string mult(string x, string y)
{
    if (x.length() == 1 && y.length() == 1)
    {
        return to_string(atoi(x.c_str()) * atoi(y.c_str()));
    }
    if (x[0] == '0' && y[0] == '0')
    {
        while (x[0] == '0')
        {
            x = x.substr(1, x.length());
        }
        while (y[0] == '0')
        {
            y = y.substr(1, y.length());
        }
    }

    int len = x.length() > y.length() ? x.length() : y.length();
    while (len > x.length())
    {
        x = '0' + x;
    }
    while (len > y.length())
    {
        y = '0' + y;
    }

    string a = x.substr(0, len / 2),
           b = x.substr(len / 2, len),
           c = y.substr(0, len / 2),
           d = y.substr(len / 2, len);

    int n = len;
    if (n % 2)
    {
        n++;
    }
    int k = n / 2;

    while (a[0] == '0' && a.length() > 1)
    {
        a = a.substr(1, a.length());
    }
    while (b[0] == '0' && b.length() > 1)
    {
        b = b.substr(1, b.length());
    }
    while (c[0] == '0' && c.length() > 1)
    {
        c = c.substr(1, c.length());
    }
    while (d[0] == '0' && d.length() > 1)
    {
        d = d.substr(1, d.length());
    }

    string sumAB = sum(a, b), sumCD = sum(c, d);

    string u;
    if (sumAB.length() > a.length() || sumCD.length() > c.length())
    {
        len = sumAB.length() > sumCD.length() ? sumAB.length() : sumCD.length();
        while (len > sumAB.length())
        {
            sumAB = '0' + sumAB;
        }
        while (len > sumCD.length())
        {
            sumCD = '0' + sumCD;
        }

        len = n;
        while (len > sumAB.length())
        {
            sumAB = '0' + sumAB;
        }
        while (len > sumCD.length())
        {
            sumCD = '0' + sumCD;
        }

        string asub = sumAB.substr(0, len / 2),
               bsub = sumAB.substr(len / 2, len),
               csub = sumCD.substr(0, len / 2),
               dsub = sumCD.substr(len / 2, len);

        while (asub[0] == '0' && asub.length() > 1)
        {
            asub = asub.substr(1, asub.length());
        }
        while (bsub[0] == '0' && bsub.length() > 1)
        {
            bsub = bsub.substr(1, bsub.length());
        }
        while (csub[0] == '0' && csub.length() > 1)
        {
            csub = csub.substr(1, csub.length());
        }
        while (dsub[0] == '0' && dsub.length() > 1)
        {
            dsub = dsub.substr(1, dsub.length());
        }

        string middle = multWithPow(sum(multWithNum(dsub, a[0] - '0'), multWithNum(bsub, c[0] - '0')), k);
        string begin = sum(multWithPow(to_string((a[0] - '0') * (c[0] - '0')), n), middle);
        u = sum(begin, mult(dsub, bsub));
    }
    else
    {
        u = mult(sumAB, sumCD);
    }
    string v = mult(a, c);
    string w = mult(b, d);

    string check = sub(u, v);
    check = sub(check, w);
    string begin = sum(multWithPow(v, n), multWithPow(check, k));

    return sum(begin, w);
}

string sum(string x, string y)
{
    int len = x.length() > y.length() ? x.length() : y.length();
    while (len > x.length())
    {
        x = '0' + x;
    }
    while (len > y.length())
    {
        y = '0' + y;
    }
    string c = "";
    int tmp = 0, sumRaz;
    for (int i = x.length() - 1; i >= 0; i--)
    {
        sumRaz = (x[i] - '0') + (y[i] - '0') + tmp;
        tmp = sumRaz % 10;
        c = to_string(tmp) + c;
        tmp = sumRaz / 10;
    }
    if (tmp)
    {
        c = to_string(tmp) + c;
    }
    return c;
}

string multWithPow(string s, int n)
{
    for (int i = 0; i < n; i++)
        s += '0';
    return s;
}

string multWithNum(string s, int alpha)
{
    if (alpha == 1)
        return s;
    else
        return to_string(0);
}
string sub(string a, string b)
{
    int raz = a.length() - b.length();
    if (raz > 0)
    {
        while (a.length() - b.length())
        {
            b = '0' + b;
        }
    }
    else if (raz < 0)
    {
        while (b.length() - a.length())
        {
            a = '0' + a;
        }
    }

    int i = 0, flag = 0;
    while (i < a.length() && a[i] == b[i])
    {
        i++;
    }
    if (i < a.length() && a[i] > b[i])
    {
        flag = 1;
    }

    string c;

    if (!flag)
    {
        string tmp = a;
        a = b;
        b = tmp;
    }
    for (int i = a.length() - 1; i > -1; i--)
    {
        int suber = (a[i] - '0') - (b[i] - '0');
        if (suber < 0)
        {
            suber += 10;
            int j;
            for (j = i - 1; j > -1 && a[j] == '0'; j--)
            {
                a[j] = '9';
            }
            a[j]--;
        }
        c = to_string(suber) + c;
    }

    return c;
}
