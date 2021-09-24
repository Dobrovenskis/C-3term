#include <iostream>
#include <vector>

class Graph
{
   public:
       int size_graph;
       std::vector<std::vector<bool>> matrix_graph;

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

class Depth_first_search:public Virt_search
{
private:
    Graph graph;
    std::vector<bool> vec_flag;
    int size_graph;

public:
    Depth_first_search(Graph gr)
    {
        graph = gr;
        size_graph = graph.matrix_graph.size();
        vec_flag = std::vector<bool>(size_graph);

    }
    void initialize_vertex(int number, Graph g)
    {
        vec_flag[number] = false;
    }

    void discover_vertex(int number, Graph g)
    {
        vec_flag[number] = true;
    }

    void DFS(int ver, int depth_rec)
    {
        std::cout << ver << " ";
        discover_vertex(ver, graph);

        for(int i = 0; i < size_graph; i++)
        {
            if(graph.matrix_graph[ver][i] && not(vec_flag[i]))
            {
                DFS(i, depth_rec + 1);
            }
        }
    }

    void first_DFS(int ver)
    {
        for(int i =0; i < size_graph; i++)
        {
            initialize_vertex(i, graph);
        }
        DFS(ver, 0);
        std::cout << std::endl;
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
    Breadth_first_search(Graph gr)
    {
        graph = gr;
        size_graph = graph.matrix_graph.size();
        vec_flag = std::vector<bool>(size_graph);
        for(int i; i < size_graph; i++)
        {
            mat_viz.push_back(std::vector<bool>(size_graph));
        }

    }

    void initialize_vertex(int number, Graph g)
    {
        vec_flag[number] = false;
        for(int i = 0; i < size_graph; i++)
        {
            mat_viz[i][number] = false;
        }

    }

    void discover_vertex(int number, Graph g)
    {
        vec_flag[number] = true;
    }

    void BFS_rec(int ver, int depth_rec)
    {
        discover_vertex(ver, graph);
        mat_viz[depth_rec][ver] = true;
        for(int i = 0; i < size_graph; i++)
        {
            if(graph.matrix_graph[ver][i] && not(vec_flag[i]))
            {
                BFS_rec(i, depth_rec + 1);
            }
        }
    }

    void BFS_first(int ver)
    {
        for(int i =0; i < size_graph; i++)
        {
            initialize_vertex(i, graph);
        }

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
        std::cout << std::endl;
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
    d.first_DFS(1);
    d.first_DFS(3);

    Breadth_first_search b = Breadth_first_search(g);
    b.BFS_first(1);
}

