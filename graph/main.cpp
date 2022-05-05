#include <iostream>
#include <vector>
#include <assert.h>

class IGraph {
public:
    virtual ~IGraph() {}

    IGraph() {};

    IGraph(const IGraph &_oth) {
        *this=_oth;
    };
    IGraph& operator=(const IGraph &_oth){
        *this=_oth;
        return *this;
    }
        // Метод принимает вершины начала и конца ребра и добавляет ребро
    virtual void AddEdge(int from, int to) = 0;
        // Метод должен считать текущее количество вершин
    virtual int VerticesCount() const = 0;
        // Для конкретной вершины метод выводит в вектор “вершины” все вершины,
        //в которые можно дойти по ребру из данной
    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const = 0;
        // Для конкретной вершины метод выводит в вектор “вершины” все вершины,
        // из которых можно дойти по ребру в данную
    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const = 0;

};

class ListGraph:public IGraph{
    std::vector<std::vector<int>> list;
    std::vector<int> pair;
public:
     void AddEdge(int from, int to)override{
        bool ok= false;
        if(list.empty()){
            pair.push_back(from);
            pair.push_back(to);
            list.push_back(pair);
        }
        else{
            for( int i=0;i<list.size();i++){
                pair=list[i];
                if(pair[0]==from){
                    pair.push_back(to);
                    list[i]=pair;
                    ok=true;
                    break;
                }
                pair.clear();
            }

            if(!ok){
                pair.push_back(from);
                pair.push_back(to);
                list.push_back(pair);
            }
        }
        pair.clear();
    }
    int VerticesCount()const override{
         std::vector<int>count;
         for( std::vector<int> vec:list){
             for(int num:vec){
                 bool ok= false;
                 if(count.empty()){
                     count.push_back(num);
                 }
                 else{
                     for(int item:count){
                         if(num==item){
                             ok=true;
                             break;
                         }
                     }
                     if(!ok){
                         count.push_back(num);
                     }
                 }
             }
         }
       return (int)count.size();
     }

    void GetNextVertices(int vertex, std::vector<int> &vertices) const override{
        for( std::vector<int> vec:list){
            if(vec[0]==vertex){
                for(int i=1;i<vec.size();i++){
                    vertices.push_back(vec[i]);
                }
            }
        }
    }

    void GetPrevVertices(int vertex, std::vector<int> &vertices) const override{
        for( std::vector<int> vec:list){
            for(int i=1;i<vec.size();i++){
                if(vec[i]==vertex){
                    vertices.push_back(vec[0]);
                }
            }
        }
    }
};

class MatrixGraph:public IGraph{

    bool matrix [10][10]{};
public:
    void AddEdge(int from, int to)override{
        assert(from>=0&&to>=0);
        assert(from<10&&to<10);
        matrix[from][to] =true;
    }
    int VerticesCount()const override{
        std::vector<int> count;
        for(int i=1;i<10;i++){
            for(int j=1;j<10;j++){
                if(matrix[i][j]){
                    bool okI = false;
                    bool okJ = false;
                    if(count.empty()) {
                        count.push_back(i);
                        if (i != j)count.push_back(j);
                    }else {
                        for(int item:count){
                            if(i==item)okI = true;
                            if(j==item && j!=i)okJ= true;
                        }
                        if(!okI)count.push_back(i);
                        if(!okJ)count.push_back(j);
                    }
                }

            }
        }
        return (int)count.size();
    }
    void GetNextVertices(int vertex, std::vector<int> &vertices) const override{
        for(int i=1;i<10;i++){
            if(matrix[vertex][i]){
                vertices.push_back(i);
            }
        }

    }
    void GetPrevVertices(int vertex, std::vector<int> &vertices) const override{
        for(int i=1;i<10;i++){
            if(matrix[i][vertex]){
                vertices.push_back(i);
            }
        }

    }

};

int main() {
    std::vector<int> vertices;
    IGraph* a = new ListGraph();
    IGraph* b = new MatrixGraph();
    IGraph* c(a);
    a->AddEdge(1,2);
    a->AddEdge(1,3);
    a->AddEdge(2,3);
    a->AddEdge(4,1);
    a->AddEdge(4,3);
    b->AddEdge(1,2);
    b->AddEdge(1,3);
    b->AddEdge(2,3);
    b->AddEdge(4,1);
    b->AddEdge(4,3);
    std::cout<< a->VerticesCount()<<" "<<b->VerticesCount()<<" "<<c->VerticesCount()<<std::endl;
    a->GetNextVertices(1,vertices);
    for(int i=0;i<vertices.size();i++){
        std::cout<<vertices[i]<<" ";
    }
    vertices.clear();
    std::cout<<std::endl;
    b->GetNextVertices(1,vertices);
    for(int i=0;i<vertices.size();i++){
        std::cout<<vertices[i]<<" ";
    }
    vertices.clear();
    std::cout<<std::endl;
    a->GetPrevVertices(3,vertices);
    for(int i=0;i<vertices.size();i++){
        std::cout<<vertices[i]<<" ";
    }
    vertices.clear();
    std::cout<<std::endl;
    c->GetPrevVertices(3,vertices);
    for(int i=0;i<vertices.size();i++){
        std::cout<<vertices[i]<<" ";
    }
    std::cout<<std::endl;
    delete a;
    delete b;
    return 0;
}
