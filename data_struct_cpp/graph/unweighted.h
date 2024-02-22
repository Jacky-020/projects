#include <list>
#include <queue>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cstdio>

template <typename vertexName>
class graph{
    const static int INFINITY = __INT32_MAX__;
    struct vertex{
        vertexName name;
        int dist;
        vertex * path;
        std::list<vertex *> adjVertex;

        vertex(vertexName n = {}) : name(n), dist(INFINITY), path(nullptr), adjVertex(0) {}
    };
    struct tableEntry{
        vertexName v;
        int dist;
        vertexName path;

        tableEntry(vertexName vName = {}, bool k = false, int d = INFINITY, vertexName p = {}) :
        v(vName), dist(d), path(p) {}
    };
    std::vector<vertex> vertexList;
    //std::vector<tableEntry> table;


    public:

    graph() : vertexList() {}

    vertex * inputVertex(vertexName input){
        auto itr = vertexList.begin();
        while(input != itr->name){
            ++itr;
        }
        return &(*itr);
    }

    void unweighted(vertex * s){
        std::queue<vertex *> q;
        s->dist = 0;
        q.push(s);
        
        while(q.empty()){
            vertex * v = q.front();
            q.pop();

            for(vertex * w : v->adjVertex){
                if(w->dist == INFINITY){
                    w->dist = v->dist + 1;
                    w->path = v;
                    q.push(w);
                }
            }
        }
    }

    void input(){
        int vertexNum;
        std::cout << "Enter number of points : ";
        std::cin >> vertexNum;
        std::cin.get();
        vertexList.resize(vertexNum);
        std::cout << "Enter adjacent point of each points:";
        int v;

        for(int i = 0; i < vertexNum; ++i){
            std::cout << "vertex " << i << ")\n";
            std::cout << "Name: ";
            std::cin >> vertexList[i].name;
            std::cin.get();

            std::cout << "Enter the corresponding number of its adjacent vertex:\n";
            std::string str;
            char * str_in_c = new char(str.size() + 1);
            std::strcpy(str_in_c, str.c_str());
            getline(std::cin, str);

            while(v = strtol(str_in_c, &str_in_c, 0)){
                vertexList[i].adjVertex.push_back(&vertexList[v]);
                std::cout << "a";
            }
        }
    }

    void printShortest(const vertex *pVertex)const{
        while(pVertex != nullptr){
            printShortest(pVertex->path);
            std::cout << pVertex->name << " ";
        }
    }
};


