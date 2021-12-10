#include<iostream>
#include<map>
#include<vector>
#include<algorithm>

int main()
{
    std::map <int, std::vector<float>> mp;

    int N;
    std::cin >> N;

    for(int i = 0; i < N; i++)
    {
        int a1;
        int ind;
        float a3;
        float a4;
        float a5;
        float neur;
        float a6;

        std::cin >> a1 >> ind >> a3 >> a4 >> a5 >> neur >> a6;

        auto it_ind = mp.find(ind);
        if (it_ind == mp.end())
        {
            std::vector<float> vec_neur {neur};
            mp[ind] = vec_neur;
        }
        else
        {
            (it_ind -> second).push_back(neur);
        }

    }

    std::multimap <float, int> mp2;
    for(auto& el : mp)
        {
            std::vector<float> vec = el.second;
            if(vec.size() != 1)
            {
                float maxim = *std::max_element(vec.begin(), vec.end());
                float minim = *std::min_element(vec.begin(), vec.end());
                float delta = maxim - minim;

                //mp2[delta] = el.first;
                mp2.insert(std::pair<float, int>(delta, el.first));
            }

        }
    //auto it = mp2.begin();
    int i = 0;
    for(auto it = mp2.begin(); it != mp2.end() && i <3; it++, i++ )
    {
        std::cout << it->second << " ";
    }
    if( i == 0)
    {
        std::cout << -1;
    }
    /*
    for(auto& [key, value] : mp)
    {
        std::cout << key <<":"<< value << " ";
    }*/

}
