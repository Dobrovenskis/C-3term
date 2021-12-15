#include <iostream>
#include <string>
#include <list>

int return_hash(std::string s, int table_len, int prime = 7)
{
    int my_hash = 0;
    for (int i = 0; i < s.length(); i++)
    {
        my_hash = (prime*my_hash + s[i]) % table_len;
    }
    return my_hash;
}


class Hash_table
{
private:
    int size_table = 8;
    std::list < std::string >* table;

public:
    Hash_table()
    {
        table = new std::list < std::string >[size_table];

    }

    void print()
    {
        for(int i = 0; i < size_table; i++)
        {
            for (std::string n : table[i])
            {
                std::cout << n << ", ";
            }
            std::cout << std::endl;
            //std::cout << table[i].value << " " << table[i].flag << std::endl;
        }
    }

    bool my_find(std::string value)
    {
        int x_hash = return_hash(value, size_table);
        bool Q_in_table = false;

        for(std::string element :table[x_hash])
        {
            if( element == value)
            {
                Q_in_table = true;
            }
        }
        return Q_in_table;
    }

    void add(std::string value)
    {
        if(my_find(value))
        {
            std::cout << "Table has this element" << std::endl;
        }
        else
        {
            int x_hash = return_hash(value, size_table);
            table[x_hash].push_back(value);
        }
    }

    void my_delete(std::string value)
    {
        if(not my_find(value))
        {
            std::cout << "Table has not this element" << std::endl;
        }
        else
        {
            int x_hash = return_hash(value, size_table);
            table[x_hash].remove(value);
        }
    }
    ~Hash_table()
    {
        delete[] table;
    }

};

int main()
{

  Hash_table h2;
  h2.add("oxo1");
  h2.add("oxo1");
  h2.add("oxo2");
  h2.add("oxo3");
  h2.add("oxo4");
  h2.add("oxo5");
  h2.add("oxo6");
  h2.add("oxo7");
  h2.add("oxo8");
  h2.add("oxo9");
  h2.add("adsf");
  h2.add("adkfj;");
  h2.add("asdf;");
  h2.print();

  std::cout << std::endl << h2.my_find("asdf;") << std::endl;
  std::cout << h2.my_find("asdfadfgzx") << std::endl;

  h2.my_delete("adkfj;");
  h2.print();


  h2.add("lol");
  h2.add("oxo");
  h2.add("oxo1");
  h2.add("oxo2");
  h2.add("oxo3");
  h2.add("oxo4");
  h2.add("oxo5");
  h2.add("oxo6");
  h2.add("oxo7");
  h2.add("lol");

  h2.my_delete("lol");
  h2.my_delete("asdf");
  h2.print();

  h2.my_delete("lol");
  h2.add("lol");
  h2.print();


  h2.my_delete("oxo");
  h2.my_delete("oxo1");
  h2.my_delete("oxo2");
  h2.my_delete("oxo3");
  h2.my_delete("oxo4");
  h2.my_delete("oxo5");
  h2.my_delete("oxo6");

  h2.add("oxo10");
  h2.add("oxo11");
  h2.add("oxo12");
  h2.add("oxo13");
  h2.add("oxo14");
  h2.add("oxo15");
  h2.add("oxo16");
  h2.add("oxo17");
  h2.my_delete("oxo13");
  h2.add("oxo18");
  h2.add("oxo19");

  std::cout << std::endl << std::endl;
  h2.print();
}

