#include <iostream>
#include <vector>

class Graph
{
   public:
       int size_graph;
       std::vector<std::vector<bool>> matrix_graph;

       //( m, std::vector<int>(m)); // зачем-то нужен n

   public:
       Graph() {}

       Graph(std::vector<std::vector<bool>>matrix)
       {
           matrix_graph = matrix;
           size_graph = matrix.size();

           bool proverka = true;
           for(std::vector<bool> vec : matrix)
           {
               if(vec.size() != size_graph)
               {
                   proverka = false;
               }
           }
           if (not(proverka))
           {
               std::cout << "The input is not a matrix";
           }
           //std::vector<std::vector<int>> matrix_graph;

       }

       void add_edge(int nomer_1_top, int nomer_2_top)
       {
           matrix_graph[nomer_1_top][nomer_2_top] = true;
           matrix_graph[nomer_2_top][nomer_1_top] = true;
       }

       void delete_edge(int nomer_1_top, int nomer_2_top)
       {
           matrix_graph[nomer_1_top][nomer_2_top] = false;
           matrix_graph[nomer_2_top][nomer_1_top] = false;
       }

       void add_top(std::vector<bool> edges_vector)
       {
           if (edges_vector.size() - 1 == size_graph)
           {
               matrix_graph.push_back(edges_vector);
               size_graph ++;
               for(int i = 0; i < size_graph -1; i++)
               {
                   matrix_graph[i].push_back(edges_vector[i]);
               }
            }
            else
            {
                std::cout << "Size of vector incorrect";
            }
       }

       void print()
       {
           for(int i = 0; i < size_graph; i++)
           {
               for ( bool el : matrix_graph[i])
               {
                   std::cout << el << " ";
               }
               std::cout << std::endl;
           }
           std::cout << std::endl;
       }

       //Get matrix
       // Set matrix

};

class Virt_search
{
public:
    virtual void initialize_vertex(int s, Graph g) {std::cout << "PRIV!!!";}
    virtual void start_vertex(int s, Graph g) {std::cout << "Ku";}
    virtual void discover_vertex(int u, Graph g) {}
    virtual void examine_edge(bool e, Graph g ) {}
    virtual void tree_edge (bool e, Graph g) {}
    virtual void back_edge (bool e, Graph g) {}
    virtual void forward_or_cross_edge(bool e, Graph g) {}
    virtual void finish_vertex(int u, Graph g) {}
};

class Element_graph_search
{
public:
    int number;
    std::string name;
    bool color;

    Element_graph_search() {}

    Element_graph_search(int num, std::string nam)
    {
        number = num;
        name = nam;
        color = false;
    }
};

class Depth_first_search:public Virt_search
{
public:
    Graph graph;
    int size_graph;
    std::vector<Element_graph_search> search_vec_graf;

public:
    Depth_first_search(Graph gr)//Graph gr)
    {
        graph = gr;
        size_graph = graph.matrix_graph.size();
        for(int i = 0; i < size_graph; i++)
        {
            Element_graph_search e = Element_graph_search(i, std::to_string(i));
            search_vec_graf.push_back(e);
        }
        //vec_flag = std::vector<bool>(size_graph);

    }

    void initialize_vertex(int num, Graph graph)
    {
        search_vec_graf[]
    }

    void DFS(Element_graph_search& ver, int depth_rec)
    {
        std::cout << ver.name << " ";
        //vec_flag[ver] = true;
        ver.color = true;


        for(int i = 0; i < size_graph; i++)
        {
            if(graph.matrix_graph[ver.number][i] && not(search_vec_graf[i].color))
            {
                DFS(search_vec_graf[i], depth_rec + 1);

            }
        }
    }
};

class Breadth_first_search:public Virt_search
{
private:
    Graph graph;
    std::vector<bool> vec_flag;
    int size_graph;
    std::vector<std::vector<bool>> mat_viz;

public:
    Breadth_first_search(Graph gr)//Graph gr)
    {
        graph = gr;
        size_graph = graph.matrix_graph.size();
        vec_flag = std::vector<bool>(size_graph);
        for(int i; i < size_graph; i++)
        {
            mat_viz.push_back(std::vector<bool>(size_graph));
        }

    }

    void BFS_rec(int ver, int depth_rec)
    {
        vec_flag[ver] = true;
        mat_viz[depth_rec][ver] = true;
        for(int i = 0; i < size_graph; i++)
        {
            if(graph.matrix_graph[ver][i] && not(vec_flag[i]))
            {
                BFS_rec(i, depth_rec + 1);
            }
        }
    }

    void BFS(int ver)
    {
        BFS_rec(ver, 0);
        for (std::vector<bool> vec : mat_viz)
        {
            for(int i = 0; i < size_graph; i ++)
            {
                if(vec[i])
                {
                    std::cout << i << " ";
                }
            }
        }
    }

    void print()
       {
           for(int i = 0; i < size_graph; i++)
           {
               for ( bool el : mat_viz[i])
               {
                   std::cout << el << " ";
               }
               std::cout << std::endl;
           }
           std::cout << std::endl;
       }
};

int main()
{
    int m = 7;
    std::vector<std::vector<bool>> matrix;
    for(int i = 0; i < m; i++)
    {
        matrix.push_back( std::vector<bool>(m));
    }
    Graph g = Graph(matrix);
    g.add_edge(3, 2);
    g.add_top(std::vector<bool> {true, true, false, false, true, false, true, true});
    //Graph g;
    g.print();
    Depth_first_search d = Depth_first_search(g);

    d.DFS(d.search_vec_graf[1], 0);
    std::cout << std::endl;
    /*
    Breadth_first_search b = Breadth_first_search(g);
    b.BFS(1);
    std::cout << std::endl;
    b.print();
    b.initialize_vertex(2, g);
    //g.matrix_graph;
       //std::vector<int> asd = {3,4,6};
       //std::vector<std::vector<int>> matrix_graph(m, std::vector<int>(m));
    */
}

