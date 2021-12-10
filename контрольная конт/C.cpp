#include<iostream>
#include<map>
#include<vector>

int main()
{
    std::multimap <int, int> mp;

    int N;
    std::cin >> N;

    for(int i = 0; i < N; i++)
    {
        int a1;
        int a2;
        int a3;
        int colvo;

        std::cin >> a1;
        std::cin.ignore();
        std::cin >> a2;
        std::cin.ignore();
        std::cin >> a3;

        std::cin >> colvo;

        int my_data = a3*10000 + a2*100 + a1;

        //mp[my_data] = colvo;
        mp.insert( std::pair<int, int>(my_data, colvo));
    }

    int M;
    std::cin >> M;
    std::vector<int> vec;
    for(int i = 0; i < M; i++)
    {
        int a1;
        int a2;
        int a3;

        std::cin >> a1;
        std::cin.ignore();
        std::cin >> a2;
        std::cin.ignore();
        std::cin >> a3;

        int my_data = a3*10000 + a2*100 + a1;


        int maxim = 0;
        for(auto& el : mp)
        {
            if(el.first <= my_data)
            {
                maxim = std::max(el.second, maxim);
            }
        }
        vec.push_back(maxim);


    }

    for(auto el : vec)
    {
        std::cout << el << "\n";
    }
    /*
    for(auto& [key, value] : mp)
    {
        std::cout << key <<":"<< value << " ";
    }*/

}
