#include <iostream>
#include <string>

int return_hash(std::string s, int table_len, int prime)
{
    int my_hash = 0;
    for (int i = 0; i < s.length(); i++)
    {
        my_hash = (prime*my_hash + s[i]) % table_len;
    }
    if (my_hash % 2 == 0)
    {
        my_hash++;
    }
    return my_hash;
}


class Field
{
public:
    std::string value;
    bool flag; //true - не удалён

public:
    Field(std::string in_value = "zero23473485")
    {
        flag = true;
        value = in_value;
    }
    ~Field(){}
};

class Hash_table
{
private:
    int begin_size = 8;
    Field* table;
    int size_table;
    int quantity_not_zero = 0;

public:
    Hash_table()
    {
        size_table = begin_size;
        table = new Field[size_table];

    }

    void print()
    {
        for(int i = 0; i < size_table; i++)
        {
            std::cout << table[i].value << " " << table[i].flag << std::endl;
        }
    }

    void doublex()
    {

        Field* table_old = table;
        table = new Field[size_table*2];
        size_table *= 2;
        quantity_not_zero = 0;
        for(int i = 0; i < size_table/2; i++)
        {
            if (table_old[i].value != "zero23473485")
            {
                add(table_old[i].value);
            }

        }
        delete[] table_old;
    }

    bool my_find(std::string value)
    {
        int hash_1 = return_hash(value, size_table, 7);
        int hash_2 = return_hash(value, size_table, 17);
        int nomer = hash_1;
        bool Q_in_table = false;

        for(int i = 0; table[nomer].value != "zero23473485"; i++)
        {
            if(table[nomer].value == value && table[nomer].flag)
            {
                Q_in_table = true;
            }
            nomer = (hash_1 + i*hash_2) % size_table;
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
            if(quantity_not_zero >= size_table * 3/4)
            {
                doublex();
            }
            int hash_1 = return_hash(value, size_table, 7);
            int hash_2 = return_hash(value, size_table, 17);
            int nomer = hash_1;


            for(int i = 0; table[nomer].value != "zero23473485" && (table[nomer].value != value); i++)
            {
                nomer = (hash_1 + i*hash_2) % size_table;
            }


            if((table[nomer].value == value))
            {
                table[nomer].flag = true;
            }
            else
            {
                Field new_field = Field(value);
                table[nomer] = new_field;
                quantity_not_zero ++;
            }


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
            int hash_1 = return_hash(value, size_table, 7);
            int hash_2 = return_hash(value, size_table, 17);
            int nomer = hash_1;

            for(int i = 0; table[nomer].value != "zero23473485"; i++)
            {
                if(table[nomer].value == value && table[nomer].flag)
                {
                    table[nomer].flag = false;
                }
                nomer = (hash_1 + i*hash_2) % size_table;
            }
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

  h2.print();
  std::cout << std::endl << h2.my_find("lol") << std::endl;
  std::cout << h2.my_find("adsf") << std::endl;

  h2.my_delete("lol");
  h2.my_delete("asdf");
  h2.print();

  std::cout << std:: endl << h2.my_find("lol") << std::endl;
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
