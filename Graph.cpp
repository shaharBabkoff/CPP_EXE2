// id:324207935
// email:shbabkoff123@gmail.com
#include <iostream>
#include <stdexcept>
#include <vector>
#include "Graph.hpp"
#include <sstream>
#include <iostream>
using namespace std;
namespace ariel
{
    void Graph::loadGraph(vector<vector<int>> g, bool isDirected)
    {
        isDirected_ = isDirected;
        verticesNum_ = g.size();
        adjacenctMat_ = g;
        size_t edgeCounter = 0;

        for (vector<int> i : adjacenctMat_) // checking valid input(square matrix)
        {
            if (i.size() != verticesNum_)
            {
                std::invalid_argument dimensions("Invalid graph: The graph is not a square matrix.");
                throw(dimensions);
            }
        }

        if (!isDirected_) // if the graph is undirected, cheking if the matrix is symetric
        {
            for (size_t i = 0; i < verticesNum_; i++)
            {
                for (size_t j = 0; j < verticesNum_; j++)
                {
                    if (adjacenctMat_[i][j] != adjacenctMat_[j][i])
                    {
                        invalid_argument symetry("Invalid graph: the graph is not directed however not symetric");
                        throw(symetry);
                    }
                }
            }
        }

        for (vector<int> row : adjacenctMat_)
        {
            for (int value : row)
            {
                if (value != 0)
                {
                    edgeCounter++;
                }
            }
        }
        if (isDirected_ == false)
        {
            edgesNum_ = edgeCounter / 2;
        }
        else
        {
            edgesNum_ = edgeCounter;
        }
    }
    void Graph::printGraph()
    {

        for (vector<int> row : adjacenctMat_)
        {
            for (int value : row)
            {
                cout << value << " ";
            }
            cout << endl;
        }
        cout << endl;
        cout << "Graph with " << verticesNum_ << " vertices and " << edgesNum_ << " edges." << endl;
    }
    string Graph::graphToString()
    {
        ostringstream oss; // Create a stringstream to store the graph data

        // Iterate over each row of the adjacency matrix
        for (size_t i = 0; i < adjacenctMat_.size(); ++i)
        {
            oss << "["; // Start of the row
            for (size_t j = 0; j < adjacenctMat_[i].size(); ++j)
            {
                oss << adjacenctMat_[i][j]; // Insert each value into the stream
                if (j < adjacenctMat_[i].size() - 1)
                {
                    oss << ", "; // Add comma only between numbers, not at the end
                }
            }
            oss << "]"; // End of the row
            if (i < adjacenctMat_.size() - 1)
            {
                oss << "\n"; // Add a newline after each row except the last
            }
        }

        // Return the string stream content
        return oss.str();
    }
    const vector<vector<int>> &Graph ::getAdjacenctMat() const
    {
        return adjacenctMat_;
    }
    size_t Graph::getVerticesNum() const
    {
        return verticesNum_;
    }
    size_t Graph::getEdgesNum() const
    {
        return edgesNum_;
    }
    bool Graph::isDirected() const
    {
        return isDirected_;
    }
    ostream &operator<<(ostream &os, const Graph &graph)
    {

        for (size_t i = 0; i < graph.adjacenctMat_.size(); ++i)
        {
            os << "[";
            for (size_t j = 0; j < graph.adjacenctMat_[i].size(); ++j)
            {
                os << graph.adjacenctMat_[i][j];
                if (j < graph.adjacenctMat_[i].size() - 1)
                    os << ", ";
            }
            os << "]";
            if (i < graph.adjacenctMat_.size() - 1)
                os << ", ";
        }
        return os;
    }
    Graph Graph::operator+(const Graph &other)
    {
        if (verticesNum_ != other.getVerticesNum())
        {
            throw std::invalid_argument("Graphs must be of the same size to add.");
        }

        std::vector<std::vector<int>> newAdjMat(verticesNum_, std::vector<int>(verticesNum_, 0));
        for (size_t i = 0; i < verticesNum_; ++i)
        {
            for (size_t j = 0; j < verticesNum_; ++j)
            {
                newAdjMat[i][j] = adjacenctMat_[i][j] + other.getAdjacenctMat()[i][j];
            }
        }

        Graph newGraph;
        newGraph.loadGraph(newAdjMat, (isDirected_||other.isDirected()));
        return newGraph;
    }

    Graph Graph::operator-(const Graph &other)
    {
        if (verticesNum_ != other.getVerticesNum())
        {
            throw std::invalid_argument("Graphs must be of the same size to add.");
        }

        std::vector<std::vector<int>> newAdjMat(verticesNum_, std::vector<int>(verticesNum_, 0));
        for (size_t i = 0; i < verticesNum_; ++i)
        {
            for (size_t j = 0; j < verticesNum_; ++j)
            {
                newAdjMat[i][j] = adjacenctMat_[i][j] - other.getAdjacenctMat()[i][j];
            }
        }

        Graph newGraph;
        newGraph.loadGraph(newAdjMat, (isDirected_||other.isDirected()));
        return newGraph;
    }
    Graph &Graph::operator+=(int num)
    {
        for (size_t i = 0; i < verticesNum_; i++)
        {
            for (size_t j = 0; j < verticesNum_; j++)
            {
                adjacenctMat_[i][j] += num;
            }
        }
        return *this;
    }
    Graph &Graph::operator+=(const Graph &other)
    {
        if (verticesNum_ != other.getVerticesNum())
        {
            throw std::invalid_argument("Graphs must be of the same size to add.");
        }
        for (size_t i = 0; i < verticesNum_; i++)
        {
            for (size_t j = 0; j < verticesNum_; j++)
            {
                adjacenctMat_[i][j] += other.adjacenctMat_[i][j];
            }
        }
        return *this;
    }
    Graph &Graph::operator-=(const Graph &other)
    {
        if (verticesNum_ != other.getVerticesNum())
        {
            throw std::invalid_argument("Graphs must be of the same size to add.");
        }
        for (size_t i = 0; i < verticesNum_; i++)
        {
            for (size_t j = 0; j < verticesNum_; j++)
            {
                adjacenctMat_[i][j] -= other.adjacenctMat_[i][j];
            }
        }
        return *this;
    }
    Graph &Graph::operator-=(int num)
    {
        for (size_t i = 0; i < verticesNum_; i++)
        {
            for (size_t j = 0; j < verticesNum_; j++)
            {
                adjacenctMat_[i][j] -= num;
            }
        }
        return *this;
    }
    Graph &Graph::operator*=(int num)
    {
        for (size_t i = 0; i < verticesNum_; i++)
        {
            for (size_t j = 0; j < verticesNum_; j++)
            {
                adjacenctMat_[i][j] *= num;
            }
        }
        return *this;
    }
    Graph &Graph::operator/=(int num)
    {
        
        for (size_t i = 0; i < verticesNum_; i++)
        {
            for (size_t j = 0; j < verticesNum_; j++)
            {
                adjacenctMat_[i][j] /= num;
            }
        }
        return *this;
    }
    Graph &Graph::operator-()
    {
        return operator*=(-1);
    }
    Graph &Graph::operator+()
    {
        return *this;
    }
    Graph &Graph::operator++()//++g
    {
        return operator+=(1);
    }
    Graph &Graph::operator--()//--g
    {
        return operator-=(1);
    }
    Graph Graph::operator++(int num)//g++
    {
        Graph newGrap;
        newGrap.loadGraph(adjacenctMat_);
        operator+=(1);
        return newGrap;
    }
    Graph Graph::operator--(int num)//g--
    {
         Graph newGrap;
        newGrap.loadGraph(adjacenctMat_);
        operator-=(1);
        return newGrap;
    }
    Graph Graph::operator*(const Graph &other)
    {
        if (verticesNum_ != other.verticesNum_)
        {
            throw std::invalid_argument("Graphs must be of the same size to multiply.");
        }

        std::vector<std::vector<int>> result(verticesNum_, std::vector<int>(verticesNum_, 0));
        for (size_t i = 0; i < verticesNum_; ++i)
        {
            for (size_t j = 0; j < other.verticesNum_; ++j)
            {
                for (size_t k = 0; k < verticesNum_; ++k)
                {
                    result[i][j] += adjacenctMat_[i][k] * other.adjacenctMat_[k][j];
                }
            }
        }

        Graph newGraph;
        newGraph.loadGraph(result, isDirected_);
        return newGraph;
    }
    bool Graph::operator==(const Graph &other)
    {
        if (other.verticesNum_ == verticesNum_)
        {
            for (size_t i = 0; i < verticesNum_; i++)
            {
                for (size_t j = 0; j < verticesNum_; j++)
                {
                    if (!(adjacenctMat_[i][j] == other.adjacenctMat_[i][j]))
                    {
                        return false;
                    }
                }
            }
            return true;
          
        }
        return false;
    }
    bool Graph ::operator!=(const Graph& other){
        if(!operator==(other)){
            return true;
        }
    return false;
    }

    bool Graph::operator>(const Graph &other)
    {
        int count = 0;
        if (other.verticesNum_ < verticesNum_)
        {
            for (size_t i = 0; i < other.verticesNum_; i++)
            {
                for (size_t j = 0; j < verticesNum_; j++)
                {
                    if (!(adjacenctMat_[i][j] xor adjacenctMat_[i][j]))
                    {
                        count++;
                    }
                }
            }
            if (count == other.verticesNum_ * other.verticesNum_)
            {
                return true;
            }
        }
        if (edgesNum_ > other.edgesNum_)
        {
            return true;
        }
        if (edgesNum_ == other.edgesNum_)
        {
            if (verticesNum_ > other.verticesNum_)
            {
                return true;
            }
        }

        return false;
    }

    bool Graph::operator<(const Graph &other)
    {
        return (*this != other)&&(!(*this>other));
    }
   
    bool Graph::operator<=(const Graph &other)
   {
        if (*this<other||*this ==other)
        {
            return true;
        }
        return false;
    }

    bool Graph::operator>=(const Graph &other)
    {
        if (*this>other||*this ==other)
        {
            return true;
        }
        return false;
    }
    
} // namespace ariel
