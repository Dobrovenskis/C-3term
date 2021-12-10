# include<iostream>
#include<cmath>

int main()
{
    //std::cout << SIZE_MAX << "\n" ;
    //std::cout << a + 1;

    //int* a = new int [3];
    //a[0] = 1;
    //a[1] = 2;
    //a[2] = 3;

    //int a[] = {1,2,3};

    //std::cout << a[2];
    //for(int el : a)
    //{
     //   std::cout << el;
    //}
    int s = 128;
    int* a = new int[s];
    for(int i = 0; i > -1; i++)
    {
        a[i] = 2;
        delete [] a;
        a = new int[s];
        std::cout << i;
    }


    //sqrt(a);
}
