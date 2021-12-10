#include <iostream>

class MyMatrix
{
private:
    int n;
    int m;
    float** Mat;

public:

    MyMatrix(int n1, int m1)
    {
        n = n1;
        m = m1;
        Mat = new float*[n];
        for (int i = 0; i < n; i++)
        {
            Mat[i] = new float[m];
            for(int k = 0; k < m; k++)
            {
                Mat[i][k] = 0;
            }
        }
    }

    void zapolnit()
    {
        for (int i = 0; i < n; i++)
        {
            for(int k = 0; k < m; k++)
            {
                float a;
                std::cin >> a;
                Mat[i][k] = a;
            }
        }
    }

    void print()
    {
        for (int i = 0; i < n; i++)
        {
            for(int k = 0; k < m; k++)
            {
                std::cout << Mat[i][k] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
    ~MyMatrix()
    {
        for (int i = 0; i < n; i++)
        {
            delete[] Mat[i];
        }
        delete[] Mat;
    }
};



int main()
{
    MyMatrix M(3, 2);
    M.zapolnit();
    M.print();
}
