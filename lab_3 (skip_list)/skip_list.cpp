#include<iostream>
#include<vector>
#include <iterator>
#include<cstdlib>

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
struct Node
{
	T val;
	//T height;
	bool if_head;
	//vector<Node*> next;
	//vector<Node*> below;
	Node* up;
	Node* down;
	Node* left;
	Node* right;

	Node(T val): val(val), up(nullptr), left(nullptr), right(nullptr), down(nullptr), if_head(false){};
	Node() :  up(nullptr), left(nullptr), right(nullptr), down(nullptr), if_head(false) {};
	Node(const Node<T> &nd): val(nd.val), up(nd.up), left(nd.left), right(nd.right), down(nd.down) {};

	/*
	Node& operator = (const Node<T>& nod2)
	{
	    val = nod2.val;
	    up = nod2.up;
	    down = nod2.down;
	    left = nod2.left;
	    right = nod2.right;
	}*/
};

template <class T>
class Skip_list;

template<class T>
class Skip_list_iterator : public std::iterator<std::bidirectional_iterator_tag, T>
{
private:
	Node<T>* p_nod;

public:
	Skip_list_iterator(Node<T> p_nod) : p_nod(p_nod) {};

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
};


template <class T>
class Skip_list
{
private:
	float prob;
	unsigned len;
	unsigned max_height = 1;
	//std::vector<unsigned> vec_len;
	Node<T>* head;
	//friend class Skip_list_iterator<T> iter;

public:
	Skip_list()
	{
		//vec_len = std::vector<unsigned>(0);
		prob = 0.5;
		max_height = 1;
		head = nullptr;

		//iter = Skip_list_iterator<T>(head);
		// TODO: reverse_it
	};

	/*
	Skip_list( SkipList<T> &sk2)
	{
		prob = sk2.prob;
		len = sk2.len;
		size = sk2.size;
		max_height = sk2.max_height;
		head = sk2.head;
	};*/

	Skip_list(Skip_list& sk2)
	{
		prob = sk2.prob;
		head = sk2.head;
		//iter = sk2.iter;
	};

	Skip_list(float prob): prob(prob)
	{
	    head = nullptr;
		//iter = Skip_list_iterator<T>(head);
	};

	Skip_list(float prob, Node<T>* head, unsigned len): prob(prob), head(head), len(len)
	{
		//iter = Skip_list_iterator<T>(head);
	};

	Skip_list_iterator<T> end()
	{
        return Skip_list_iterator<T>(nullptr);
    }

	unsigned size()
	{
		return len;
	}

	bool empty()
	{
		bool ret = false;
		if (head == nullptr)
		{
			ret = true;
		}
		return ret;
	}



	Skip_list_iterator<T>& find(T key)
	{
	    Skip_list_iterator<T> it;
	    Node<T>* th_node = head;
	    while(th_node -> right != nullptr && th_node -> down != nullptr)
        {
            if(th_node -> val == key)
            {
                it = Skip_list_iterator<T>(th_node);
            }
            else if(th_node -> right == nullptr)
            {
                th_node = th_node -> down;
            }
            else if((th_node -> right) -> val > key)
            {
                if(th_node -> down == nullptr)
                {
                    std::cout << "Net\n";
                    it = end();
                }
                else
                {
                   th_node = th_node -> down;
                }

            }
            else
            {
                th_node = th_node -> right;
            }
        }
        return it;
	}

	unsigned count(T val)
	{
        Skip_list_iterator<T> it = find(val);
        Node<T> th_node = *it;
        unsigned colvo = 0;

        if(it == end())
        {
            colvo = 0;
        }
        else
        {
            while(th_node->down != nullptr)
            {
                th_node = th_node -> down;
            }

            while(th_node->right->val = val)
            {
                colvo ++;
            }
        }

        return colvo;

	}

	Skip_list_iterator<T> lower_bound(T key)
	{
        Skip_list_iterator<T> it;
	    Node<T>* th_node = head;
	    while(th_node -> right != nullptr && th_node -> down != nullptr)
        {
            if(th_node -> right == nullptr)
            {
                th_node = th_node -> down;
            }
            else if((th_node -> right) -> val >= key)
            {
                if(th_node -> down == nullptr)
                {
                    it = Skip_list_iterator<T>(th_node -> right);
                }
                else
                {
                   th_node = th_node -> down;
                }

            }
            else
            {
                th_node = th_node -> right;
            }
        }
        return it;
	}

	Skip_list_iterator<T> upper_bound(T key)
	{
        Skip_list_iterator<T> it;
	    Node<T>* th_node = head;
	    while(th_node -> right != nullptr && th_node -> down != nullptr)
        {
            if(th_node -> right == nullptr)
            {
                th_node = th_node -> down;
            }
            else if((th_node -> right) -> val > key)
            {
                if(th_node -> down == nullptr)
                {
                    it = Skip_list_iterator<T>(th_node -> right);
                }
                else
                {
                   th_node = th_node -> down;
                }

            }
            else
            {
                th_node = th_node -> right;
            }
        }
        return it;
	}

	void clear() {}

	void erase(Skip_list_iterator<T> it2)
	{
        Node<T> th_node = *it2;
        if(th_node -> left != nullptr)
        {
            (th_node -> left) -> right = th_node -> right;
            head = th_node;
        }
        if(th_node -> right != nullptr)
        {
            (th_node -> right) -> left = th_node -> left;
        }

        Node<T> th_node_save = th_node;
        while(th_node -> up != nullptr)
        {
            th_node = th_node->up;
            if(th_node -> left != nullptr)
            {
                (th_node -> left) -> right = th_node -> right;
                head = th_node;
            }
            if(th_node -> right != nullptr)
            {
                (th_node -> right) -> left = th_node -> left;
            }
        }
        while(th_node_save -> down != nullptr)
        {
            th_node_save = th_node_save->down;
            if(th_node -> left != nullptr)
            {
                (th_node -> left) -> right = th_node -> right;
            }
            if(th_node -> right != nullptr)
            {
                (th_node -> right) -> left = th_node -> left;
            }
        }
	}

	void erase(Skip_list_iterator<T> itbeg, Skip_list_iterator<T> itend )
	{
        for(auto it = itbeg; it != itend; it ++)
        {
            erase(it);
        }
	}

	void insert(T value)
	{
	    //std::cout << "d";

        //th_val = th_node->val;
        //std::cout << "d";
        if(head != nullptr)
        {
            Node<T> th_node = *head;
            std::cout << head -> down -> down -> down -> val;
            while(th_node.down != nullptr)
            {
                //std::cout << th_node.down -> down -> down -> val;
                th_node = *(th_node.down);
            }
        }
        //std::cout << "d";
        if(head != nullptr)
        {
            Node<T> th_node = *head;
            //std::cout << "d";
            if(head -> val < value)
            {
                //std::cout << "d";
                while(true)//th_node -> right -> val < value)
                {

                    //th_node = th_node -> right;
                    if(th_node.right == nullptr)
                    {
                        Node<T> ins_node(value);
                        th_node.right = &ins_node;
                        //std::cout << head -> right -> val;
                        ins_node.left = &th_node;
                        //std::cout << "d";
                        //return;
                        break;
                    }
                    else if(th_node.right->val < value)
                    {
                        //std::cout << "d";
                        th_node = *th_node.right;
                    }
                    else
                    {
                        //std::cout << "d";
                        break;
                    }
                }
                Node<T> ins_node_0(value);
                ins_node_0.right = th_node.right;
                ins_node_0.left = &th_node;
                th_node.right = &ins_node_0;
                //std::cout << "lal";

                int i = 0;
                for(; rand_bool(prob) && (i < max_height - 1 ); i++)
                {
                    Node<T> ins_node_1(value);
                    ins_node_0.up = &ins_node_1;
                    ins_node_1.down = &ins_node_0;
                    if(th_node.up == nullptr)
                    {
                        th_node = *th_node.left;
                    }
                    else
                    {
                        Node<T> th_node_floor = th_node;
                        while(th_node_floor.right->val < value)
                        {
                            th_node_floor = *th_node_floor.right;
                        }
                        ins_node_1.right = th_node.right;
                        ins_node_1.left = &th_node;
                        th_node.right = &ins_node_1;
                    }
                    ins_node_0 = ins_node_1;
                }
                //std::cout << "i=" << max_height - 1;
                if(i == max_height - 1 && rand_bool(prob))
                {
                    max_height ++;
                    Node<T> new_head(head -> val);
                    head->up = &new_head;
                    new_head.down = head;

                    Node<T> ins_node_end(value);
                    ins_node_end.left = head;
                    head->right = &ins_node_end;

                    head = &new_head;
                }
            }
            else
            {
                //std::cout << "d";
                Node<T> ins_node(value);
                th_node.left = &ins_node;
                ins_node.right = &th_node;
                for(int i = 0; i < max_height; i++)
                {
                    Node<T> ins_node_1(value);
                    ins_node.up = &ins_node_1;
                    ins_node_1.down = &ins_node;
                    ins_node_1.right = th_node.up;
                    th_node.up = &ins_node_1;
                    ins_node = ins_node_1;
                }
                max_height ++;
                Node<T> ins_node_1(value);
                ins_node.up = &ins_node_1;
                ins_node_1.down = &ins_node;
                head = &ins_node_1;
            }
        }
        else
        {
            //std::cout << "d";
            //Node<T> ins_node(value);
            //std::cout << "d";
            //Node<T>* new_head = new Node<T>(value);//&ins_node;
            Node<T> new_head(value);
            //std::cout << silka->val;
            Node<T> down_head(value);
            new_head.down = &down_head;
            down_head.up = &new_head;
            //down_head.down = nullptr;
            head = &new_head;//silka;
            //std::cout << head->down -> down -> down<< "\n";
            max_height = 2;
            //std::cout << "\n\n" << head->down-> val << "\n\n";
        }
	}

	void print()
	{
	    if(head == nullptr)
        {
            std::cout << "Empty";
        }
        else
        {
            std::cout << "\n\n" << head->down ->val << "\n\n";
            Node<T>* th_node = head;
            Node<T>* th_i_head = head;
            //Node<T> th_node(*head);
            //Node<T> th_i_head(*head);
            std::cout << "\n\n" << head ->down ->val << "\n\n";
            //std::cout << th_node.val;

            for(int i = 0; i < max_height; i++)
            {
                //std::cout << (th_node.down -> right != nullptr);

                while(th_node->right != nullptr)
                {
                    //std::cout << "allo";
                    std::cout << th_node->val << " ";
                    th_node = (th_node->right);
                }
                std::cout << th_node->val;

                std::cout << "\n";
                //std::cout << "\n\n" << head->down -> val << "\n\n";
                th_i_head = (th_i_head->down);
                //std::cout << "\n\nth " << head ->down ->val << " th\n\n";
                //

                th_node = th_i_head;
            }

        }
	}


};

int main()
{
	/*
	int s = 0;

	for(int i = 0; i < 1000; i++)
    {
        s += int(rand_bool(0.9));
    }
    std::cout << s;*/

    Skip_list<int> skipList(0.5);
    //skipList.print();
    //std::cout << "\n \n";
    skipList.insert(1);
    //skipList.insert(2);
    //skipList.insert(2);
    //std::cout << "2";
    //skipList.insert(2);
    //skipList.insert(3);
    skipList.print();
}
