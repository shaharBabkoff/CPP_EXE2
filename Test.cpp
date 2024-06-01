#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;

TEST_CASE("Test graph addition")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g1 + g2;
    CHECK(g3.graphToString() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]");
    g3+=5;
     CHECK(g3.graphToString() == "[5, 7, 6]\n[7, 5, 8]\n[6, 8, 5]");
    g3+=-1;
     CHECK(g3.graphToString() == "[4, 6, 5]\n[6, 4, 7]\n[5, 7, 4]");
    g3+=g2;
    CHECK(g3.graphToString() == "[4, 7, 6]\n[7, 4, 9]\n[6, 9, 4]");
   // g3++;
    CHECK(g3++.graphToString() == "[4, 7, 6]\n[7, 4, 9]\n[6, 9, 4]");
    ++g3;
    CHECK(g3.graphToString() == "[6, 9, 8]\n[9, 6, 11]\n[8, 11, 6]");




}
TEST_CASE("Test graph subtraction")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g1 -g2;
    CHECK(g3.graphToString() == "[0, 0, -1]\n[0, 0, -1]\n[-1, -1, 0]");
    g3-=5;
     CHECK(g3.graphToString() == "[-5, -5, -6]\n[-5, -5, -6]\n[-6, -6, -5]");
    g3-=-1;
     CHECK(g3.graphToString() == "[-4, -4, -5]\n[-4, -4, -5]\n[-5, -5, -4]");
    g3-=g2;
    CHECK(g3.graphToString() == "[-4, -5, -6]\n[-5, -4, -7]\n[-6, -7, -4]");
    g3--;
    CHECK(g3.graphToString() == "[-5, -6, -7]\n[-6, -5, -8]\n[-7, -8, -5]");
    --g3;
    CHECK(g3.graphToString() == "[-6, -7, -8]\n[-7, -6, -9]\n[-8, -9, -6]");




}

TEST_CASE("Test graph multiplication")
{
    ariel::Graph g1;
    vector<vector<int>> mat1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(mat1);
    ariel::Graph g2;
    vector<vector<int>> mat2 = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(mat2);
    ariel::Graph g4 = g1 * g2;
    CHECK(g4.graphToString() == "[1, 0, 2]\n[1, 3, 1]\n[1, 0, 2]");
    g4 *= 2;
    CHECK(g4.graphToString() == "[2, 0, 4]\n[2, 6, 2]\n[2, 0, 4]");
    ariel::Graph g5;
    vector<vector<int>> mat3 = {
        {0, -5, 9},
        {1, 0, 9},
        {8, 1, 0}};
    g5.loadGraph(mat3);
    ariel::Graph g6;
    vector<vector<int>> mat4 = {
        {0, 1, 1},
        {8, 0, 2},
        {1, -9, 0}};
    g6.loadGraph(mat4);
    ariel::Graph g7 = g5 * g6;
    CHECK(g7.graphToString() == "[-31, -81, -10]\n[9, -80, 1]\n[8, 8, 10]");
    g7 *= 0;
    CHECK(g7.graphToString() == "[0, 0, 0]\n[0, 0, 0]\n[0, 0, 0]");
}
TEST_CASE("<,> ,=>,<=operations")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g2.loadGraph(graph2);

    CHECK_FALSE(g2 > g1); // the graphs are equel
    CHECK(g1 >= g2);

    ariel::Graph g3;
    vector<vector<int>> graph3 = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    g3.loadGraph(graph3);

    ariel::Graph g4;
    vector<vector<int>> graph4 = {
        {0, 1, 1, 0},
        {1, 0, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0}};
    g4.loadGraph(graph4);
    CHECK(g4 > g3);

    ariel::Graph g5;
    vector<vector<int>> graph5 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g5.loadGraph(graph5);

    CHECK_FALSE(g5 > g4); // graph 0 (g5) isn't contined graph
    CHECK_FALSE(g5 >= g4);
}
TEST_CASE("algorithms"){
     ariel::Graph g1;
    vector<vector<int>> mat3 = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    g1.loadGraph(mat3);
    CHECK(Algorithms::shortestPath(g1,1,2)=="1->2");
    CHECK(Algorithms::negativeCycle(g1)=="No negative cycle detected.");
    -g1;
    
    CHECK(Algorithms::shortestPath(g1,1,2)=="-1");
    CHECK(Algorithms::negativeCycle(g1)=="2 -> 1 -> 2");


}
TEST_CASE("Invalid operations")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1, 1},
        {1, 0, 2, 1},
        {1, 2, 0, 1},
        {1, 2, 0, 1}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g5;
    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g5.loadGraph(graph2);
    CHECK_THROWS(g5 * g1);
    CHECK_THROWS(g1 * g2);

    // Addition of two graphs with different dimensions
    ariel::Graph g6;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g6.loadGraph(graph3);
    CHECK_THROWS(g1 + g6);
}