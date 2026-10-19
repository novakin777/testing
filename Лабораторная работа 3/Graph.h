#pragma once

#include <string>
#include <vector>

class Graph
{
private:
    int vertices;
    std::vector<std::vector<int>> adjacencyList;

public:
    explicit Graph(int vertexCount);

    bool addEdge(int source, int destination);
    std::string printGraph() const;
    int getVertexCount() const;
    const std::vector<int>& getNeighbors(int vertex) const;
};
