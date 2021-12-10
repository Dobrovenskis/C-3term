# include<iostream>
#include<cmath>
#include<map>

size_t sqrt_size_max = sqrt(SIZE_MAX);


template <class T>
class Grid {
    private:
        T *memory;
        size_t x_size, y_size;
        std::map<size_t, Grid<T>> map_subgrids;


    public:
        bool if_delete = true;
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
                if(map_subgrids.find(x_size * y_idx + x_idx)==map_subgrids.end())
                {
                    m_return = memory[x_size * y_idx + x_idx];
                }
                else
                {
                    std::cout << "Na dannom meste naxoditsa setka";
                    m_return = memory[x_size * y_idx + x_idx];
                }
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
                if(map_subgrids.find(x_size * y_idx + x_idx)==map_subgrids.end())
                {
                    T& m_return = memory[x_size * y_idx + x_idx];
                    return m_return;
                }
                else
                {
                    std::cout << "Na dannom meste naxoditsa setka";
                }
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
            ret << "{";
            for(int i = 0; i < m_grid.y_size; i++)
            {
                ret << "{";
                for(int k = 0; k < m_grid.x_size; k ++)
                {
                    auto num = i*m_grid.x_size + k;
                    if(m_grid.map_subgrids.find(num)==m_grid.map_subgrids.end())
                    {
                        ret << m_grid.memory[i*m_grid.x_size + k];
                    }
                    else
                    {
                        ret << m_grid.map_subgrids.find(num) ->second;
                    }

                    if(k != m_grid.x_size - 1)
                    {
                        ret << ", ";
                    }
                }
                ret << "}";
                if(i != m_grid.y_size - 1)
                {
                    ret << ", ";
                }
            }
            ret << "}";
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

        Grid& make_subgrid(
             size_t x_idx, size_t y_idx,
             size_t x_sub_size, size_t y_sub_size)
        {
            Grid subgrid = Grid(x_sub_size, y_sub_size);

            //Grid subgrid(x_sub_size, y_sub_size);
            size_t num = x_size * y_idx + x_idx;
            subgrid.if_delete = false;
            map_subgrids.insert(std::pair<size_t,Grid>(num,subgrid));


            //std::cout << subgrid;
            //delete[] subgrid.memory;
            //subgrid.~Grid();
            //std::cout << 3;
            return *this;

        };

        Grid& get_subgrid(size_t x_idx, size_t y_idx)
        {
            size_t num = x_size * y_idx + x_idx;
            //Grid<T> subgrid = map_subgrids.find(num) -> second;
            //std::cout << "allo";
            //subgrid.if_delete = false;
            //return subgrid;
            return map_subgrids.find(num) -> second;
        };

        Grid& collapse_subgrid(size_t x_idx, size_t y_idx)
        {
            size_t num = x_size * y_idx + x_idx;
            auto it = map_subgrids.find(num);
            map_subgrids.erase(it);
            (it->second).if_delete = true;
            (it->second).~Grid();
        };


        bool is_subrid(size_t x_idx, size_t y_idx) const
        {
            size_t num = x_size * y_idx + x_idx;
            bool usl = (map_subgrids.find(num) != map_subgrids.end());
            return usl;
        }

        ~Grid()
        {
            if(if_delete)
            {
                for(auto& map_el : map_subgrids)
                {
                    map_el.second.if_delete = true;
                    map_el.second.~Grid();
                }
                if (memory != nullptr)
                {
                    delete[] memory;
                    memory = nullptr;
                }
            }
        }
};

int main()
{
    Grid<int> gr1(2,3);
    gr1 = 1;
    //std::cout << gr1;
    gr1.make_subgrid(1,2, 2, 5);
    gr1.get_subgrid(1, 2) = 5;
    std::cout << gr1 << "\n";
    gr1.~Grid();

    Grid <int> gr2(2,3);
    gr2.make_subgrid(1,2, 2, 2);
    //gr2.collapse_subgrid(1,2);
    std::cout << gr2 << "\n";
    gr2.~Grid();

    std::cout << "end";
}
