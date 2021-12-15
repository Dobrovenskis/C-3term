#include <vector>
#include <random>
#include <iostream>
#include <time.h>

//using namespace std;

bool rand_bool(float p)
{
    float f_rand = ((float)rand() / (float)RAND_MAX);
     bool ret;
     if( f_rand < p)
     {
         ret = true;
     }
     else
     {
         ret = false;
     }

     return ret;
}

template <class T>
struct Node {
public:
    T val;
    Node<T>* right;
    Node<T>* left;
    Node<T>* up;
    Node<T>* down;

    Node(T val): val(val), right(nullptr), left(nullptr), up(nullptr), down(nullptr) {};
    Node(): val(0), right(nullptr), left(nullptr), up(nullptr), down(nullptr) {};

    friend std::ostream& operator << (std::ostream& ret, Node<T> const* nod2)
    {
        T inf = INFINITY;
        if (nod2->val < inf && nod2->val > -inf )
        {
            ret << nod2->val;
        }
        return ret;
    }

};


template<class T>
class Skip_list_iterator : public std::iterator<std::bidirectional_iterator_tag, T>
{
private:
	Node<T>* p_nod;

public:
	Skip_list_iterator(Node<T>* p_nod) : p_nod(p_nod) {};

	Skip_list_iterator& operator++()
	{
		p_nod = p_nod->right;
		return *this;
	}

	Skip_list_iterator& operator--()
	{
		p_nod = p_nod->left;
		return *this;
	}

	T operator *()
	{
		return p_nod->val;
	}

	bool operator==(Skip_list_iterator& iter2)
	{
		bool ret = false;
		if (p_nod == iter2.p_nod)
		{
			ret = true;
		}
		return ret;
	}

	bool operator!=(Skip_list_iterator& iter2)
	{
		bool ret = false;
		if (this == iter2)
		{
			ret = true;
		}
		return ret;
	}

	Node<T>* cheat_func()
	{
	    return p_nod;
	}
};


template <class T>
class SkipList {
private:
    std::vector<Node<T>*> vec_heads;
    int hight = 1;
    int length=0;
    float prob;
    Skip_list_iterator<T>* it_begin;
    Skip_list_iterator<T>* it_end;

public:

    SkipList() : SkipList(0.5) {};

    SkipList(float prob): prob(prob)
    {
        srand(static_cast<unsigned int>
        (time(NULL)));

        Node<T>* head = new Node<T>(-INFINITY);
        Node<T>* end_first = new Node<T>(INFINITY);

        head->right = end_first;
        end_first->left = end_first; //todo delete

        vec_heads.push_back(head);

        Skip_list_iterator<T>* it_2 = new Skip_list_iterator<T>(head);
        it_begin = it_2;
        Skip_list_iterator<T>* it_3 = new Skip_list_iterator<T>(end_first);
        it_end = it_3;
    };

    SkipList( SkipList<T> &sk2): SkipList()
    {
        auto Heads_sk2 = sk2.get_heads();
        for(auto el : Heads_sk2)
        {
            Node<T>* push_node = new Node<T>();
            push_node = el;
            vec_heads.push_back(push_node);

        }

        hight = sk2.hight;
        length = sk2.length;
        prob = sk2.prob;
    };



    Node<T>* insert_on_level(T data, int level, Node<T>* Down)
    {
        Node<T>* ins_node = new Node<T>(data);
        ins_node->down = Down;
        Node<T>* head_level = new Node<T>();

        head_level = vec_heads[level];

        while (head_level->right != nullptr
            && data > head_level->right->val)
        {
            head_level = head_level->right;
        }

        ins_node->left = head_level;
        ins_node->right = head_level->right;
        head_level->right = ins_node;

        return ins_node;
    }

    void insert(T data)
    {

        length++ ;
        Node<T>* floor_node = insert_on_level(data, 0, nullptr);

        int i = 1;

        for (; rand_bool(prob) && hight >= i -2; i++)
        {
            if (hight < i + 1)
            {
                hight += 1;
                Node<T>* NewHead = new Node <T>(-INFINITY);
                Node<T>* NewTail = new Node <T>(INFINITY);
                NewHead->right = NewTail;
                NewTail->left = NewHead;

                vec_heads[i - 1]->up = NewHead;
                NewHead -> down = vec_heads[i-1];
                vec_heads.push_back(NewHead);
            }
            Node <T>* N = insert_on_level(data, i, floor_node);
            floor_node->up = N;
            floor_node = N;
        }

        return;
    }

    Skip_list_iterator<T> search(T key)
    {
        Node <T>* toplevel;
        toplevel = vec_heads[vec_heads.size() - 1];
        Node<T>* pt = new Node<T>();
        pt = toplevel;

        while (pt != nullptr)
        {
            if (pt->val == key) {
            break;
            }
            else if (key > pt->val && key >= pt->right->val) {
            pt = pt->right;
            }
            else if (key > pt->val && key < pt->right->val) {
            pt = pt->down;
            }
        }

    Skip_list_iterator<T> iter(pt);
    return iter;
    }


    void ers_konkr(Node<T>* ers_node)
    {
        ers_node->left->right = ers_node -> right;
        ers_node -> right ->left = ers_node ->left;
        delete(ers_node);
    }

    void erarse(Skip_list_iterator<T> itr)
    {
        Node<T>* ers_node = itr.cheat_func();
        while(ers_node -> down != nullptr)
        {
            Node<T>* ers_node_down = ers_node->down;
            ers_konkr(ers_node);
             ers_node = ers_node_down;

        }
        ers_konkr(ers_node);
        length --;
    }

    int get_length()
    {
        return length;
    }

    void print()
    {
        for (int i = 0; i != vec_heads.size(); i++) {
            Node<T>* pt = new Node<T>(-INFINITY);
            pt = vec_heads[i];
            while (pt != nullptr) {
                std::cout << pt << " ";
                pt = pt->right;
            }
            std::cout << "\n";
        }
    }

    std::vector<Node<T>*> get_heads()
    {
        return vec_heads;
    }
};


int main() {
    SkipList<int> th_sl(0.3);

    th_sl.insert(3);
    th_sl.insert(2);
    th_sl.insert(5);
    th_sl.insert(8);
    th_sl.insert(9);
    th_sl.insert(4);
    th_sl.insert(-5);
    th_sl.insert(311);
    th_sl.insert(0);
    th_sl.insert(8);
    th_sl.insert(11);
    th_sl.insert(40);
    for(int i = 20; i <= 40; i++)
    {
        th_sl.insert(i);
    }
    th_sl.print();


    //Node<int> a = *(mySL.search(4));

    std::cout << "\n search = " << *(th_sl.search(4)) << " \n";
    Skip_list_iterator<int> it_th = th_sl.search(5);
    //std::cout << "asd";

    th_sl.erarse(it_th);
    //mySl.erarse

    std::cout << "\n Delete 5: \n";
    th_sl.print();

    std::cout << "\n";
    std::cout << th_sl.get_length() ;

    return 0;
}
