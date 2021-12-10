#include<iostream>
#include<string>
#include <set>

int main()
{
    //std::string a =  "Zfaaa";
    std::set<std::string> m_set;
    int m_size;
    std::cin >> m_size;

    for (int i = 0; i < m_size; i ++)
    {
        std::string str;
        std::cin >> str;
        for(int k = 0; k < str.length(); k++)
        {
            int ch = int(str[k]);
            if(ch <= 90 && ch >= 65)
            {
                str[k] += 32;

            }
        }

        m_set.insert(str);
    }

    for(auto it = m_set.rbegin(); it != m_set.rend(); it++)
    {
        std::cout << *it << " ";
    }
    /*
    for(int i = 0; i < a.length(); i++)
    {
        int ch = int(a[i]);
        if(ch <= 90 && ch >= 65)
        {
            std::cout << a[i] << "->";
            a[i] += 32;
            std::cout << a[i] << "\n";

        }
    }*/
    //char b = "A";

}
