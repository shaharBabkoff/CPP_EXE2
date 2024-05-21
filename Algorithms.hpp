//id:324207935
//email:shbabkoff123@gmail.com
#pragma once
#include "Graph.hpp"
#include <vector>
#include <string>

namespace Algorithms
{
    bool isConnected( const ariel::Graph &g);
    std::string shortestPath( const ariel::Graph &g,int start,int end);
    bool isContainsCycle( const ariel::Graph &g);
     std::string isBipartite( const ariel::Graph &g);
    std::string  negativeCycle( const ariel::Graph &g) ;
}