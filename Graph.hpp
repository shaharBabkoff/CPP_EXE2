//id:324207935
//email:shbabkoff123@gmail.com
#pragma once
#include <cstddef>
#include <vector>
#include <iostream>  


namespace  ariel
{
class Graph
{
private:
    std::vector<std::vector<int>> adjacenctMat_;
    bool isDirected_;
    size_t verticesNum_;//number of vertices
    size_t edgesNum_;//number of edges
public:

void loadGraph(std::vector<std::vector<int>> g,bool isDirected = true);
void printGraph();
std::string graphToString();
const std::vector<std::vector<int>>& getAdjacenctMat() const;
size_t getVerticesNum() const;
size_t getEdgesNum() const;
bool isDirected() const;
friend std::ostream& operator<<(std::ostream& os, const Graph& graph);
Graph operator+(const Graph& other);
Graph& operator+=(int num);
Graph& operator+=(const Graph& other);
Graph operator-(const Graph& other);
Graph& operator-=(int num);
Graph& operator-=(const Graph& other);
Graph& operator+();
Graph& operator++();//++g
Graph& operator--();//--g
Graph operator++(int num);//g++
Graph operator--(int num);//g--
Graph& operator-();
Graph& operator*=(int num);
Graph& operator/=(int num);
Graph operator*(const Graph& other);
bool operator==(const Graph& other);
bool operator!=(const Graph& other);
bool operator>(const Graph& other);
bool operator<(const Graph& other);
bool operator>=(const Graph& other);
bool operator<=(const Graph& other);

};    
} // namespace  ariel
