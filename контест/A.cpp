#include<iostream>
#include<vector>
#include <set>
#include <array>

int main()
{

    int m_size;
    std::cin >> m_size;
    //std::vector<long long int> vec(m_size);
    std::multiset <long long int> m_set;

    for (int i = 0; i < m_size; i ++)
    {
        long long int num;
        std::cin >> num;
        m_set.insert(num);
    }

    long long int sum;
    std::cin >> sum;

    /*
    for(int i = 0; i < m_size; i++)
    {
        auto n1 = vec[i];

        for(int k = i + 1; k < m_size; k++)
        {
            auto n2 = vec[k]

            for
        }
    }
    */
    std::multiset<long long int> :: iterator it1; //= m_set.begin();
    std::multiset<long long int> :: iterator it2;
    std::multiset<long long int> :: iterator it3;
    std::multiset<long long int> :: iterator it4;


    std::array<long long int, 4> ar {0, 0, 0, 0};
    std::set<std::array<long long int, 4>> cout_set;

    it1 = m_set.begin();
    /*
    std::set<long long int> :: iterator end_set_minus_3 = m_set.end();
    ((end_set_minus_3 --) --) --;
    std::set<long long int> :: iterator end_set_minus_2 = m_set.end();
    (end_set_minus_2 --) --;
    std::set<long long int> :: iterator end_set_minus_1 = m_set.end() --;
    (end_set_minus_1 --);
    */
    std::multiset<long long int> :: iterator end_set = m_set.end();
    while(it1 != end_set)
    {
        it2 = it1;
        it2++;

        while(it2 != end_set)
        {
            it3 = it2;
            it3++;

            while(it3 != end_set)
            {
                it4 = it3;
                it4++;

                while(it4 != end_set)
                {
                    if(*it1 + *it2 + *it3 + *it4 == sum)
                    {
                        ar[0] = *it1;
                        ar[1] = *it2;
                        ar[2] = *it3;
                        ar[3] = *it4;
                        cout_set.insert(ar);
                       // std::cout << *it1 << " " << *it2 << " " << *it3 << " "<<*it4 << "\n";
                    }
                    it4++;
                }

                it3 ++;
            }

            it2 ++;
            //std::cout << *it2 << "\n";
        }

        it1 ++;

    }
    //std::cout << *(end_set_minus_3 ++);
    for(auto el : cout_set)
    {
        for(auto el2 : el)
        {
            std::cout << el2 << " ";
        }

        std::cout <<"\n";
    }

}
