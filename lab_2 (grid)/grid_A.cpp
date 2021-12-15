# include<iostream>
#include<cmath>

size_t sqrt_size_max = sqrt(SIZE_MAX);


template <class T>
class Grid {
    private:
        T *memory;
        size_t x_size, y_size;

    public:
        Grid(size_t x_size, size_t y_size): x_size(x_size), y_size(y_size)
        {
            if(x_size == 0 || y_size == 0)
            {
                std::cout << "\n Razmer setki = 0, vse slomano \n";

            }
             else if(x_size > sqrt_size_max || y_size > sqrt_size_max)
            {
                std::cout << "\n Razmer setki slishkom bolhoy \n";
            }
            else
            {
                memory = new T[x_size*y_size];
            }
        };

        T operator()(size_t x_idx, size_t y_idx) const
        {
            T m_return;
            if(x_idx <= x_size && y_idx <= y_size)
            {
                m_return = memory[x_size * y_idx + x_idx];
            }
            else
            {
                std::cout << "Nomer elementa > razmera setki";
            }
            return m_return;
        };

        T& operator()(size_t x_idx, size_t y_idx)
        {
            //T& m_return;
            if(x_idx <= x_size && y_idx <= y_size)
            {
                T& m_return = memory[x_size * y_idx + x_idx];
                return m_return;
            }
            else
            {
                std::cout << "Nomer elementa > razmera setki\n";
            }

        };

        size_t get_xsize() const
        {
            return x_size;
        };

        size_t get_ysize() const
        {
            return y_size;
        };

        Grid& operator=(T val)
        {
            for(size_t i = 0; i < x_size * y_size; i++)
            {
                memory[i] = val;
            }

            return *this;
        };

        friend std::ostream& operator<<(std::ostream& ret, Grid const& m_grid)
        {
            for(int i = 0; i < m_grid.y_size; i++)
            {
                for(int k = 0; k < m_grid.x_size; k ++)
                {
                    ret << m_grid.memory[i*m_grid.x_size + k] << " ";
                }
                ret << "\n";
            }
            return ret;
        };
        friend std::istream& operator>>(std::istream& m_istr, Grid & m_grid)
        {
            for(int i = 0; i < m_grid.y_size; i++)
            {
                for(int k = 0; k < m_grid.x_size; k ++)
                {
                    m_istr >> m_grid.memory[i*m_grid.x_size + k];
                }
            }
            return m_istr;
        };

        ~Grid()
        {
            if(memory != nullptr)
            {
                delete[] memory;
                memory = nullptr;
            }

        }
};

int main()
{
    Grid<int> gr1(2,3);
    gr1 = 1;
    std::cout << gr1;
    Grid<float> gr2(2,3);


    std::cout << "Vvedite setku 3x2\n";
    std::cin >> gr2;
    std::cout << gr2;

    std::cout << gr2(1, 2) << "\n";
    std::cout << gr2(5,4) << "\n";
    gr2(1, 2) = 3;
    std::cout << gr2 << "\n";

    Grid<int> gr4(2,3);
    gr4 = 4;
    std::cout << gr4;
    gr4.~Grid();
    Grid<int> gr5(2,3);
    gr5 = 5;
    std::cout << gr5;
    gr5.~Grid();
    Grid<int> gr6(2,3);
    gr6 = 6;
    std::cout << gr6;


    for(int i = 0; i < 25; i++)
    {
        Grid<float> gr3(2,3);
        gr3 = 1;
        std::cout << i << " ";
        gr3.~Grid();
    }
}
