#include "Graph.h"

#include <sstream>

Graph::Graph(int vertexCount)
{
    vertices = vertexCount < 0 ? 0 : vertexCount;
    adjacencyList.resize(vertices + 1);
}

bool Graph::addEdge(int source, int destination)
{
    if (source < 1 || source > vertices || destination < 1 || destination > vertices)
    {
        return false;
    }

    adjacencyList[source].push_back(destination);
    return true;
}

std::string Graph::printGraph() const
{
    std::ostringstream output;

    for (int vertex = 1; vertex <= vertices; vertex++)
    {
        output << "Вершина " << vertex << ": ";

        for (int neighbor : adjacencyList[vertex])
        {
            output << neighbor << " ";
        }

        output << "\n";
    }

    return output.str();
}

int Graph::getVertexCount() const
{
    return vertices;
}

const std::vector<int>& Graph::getNeighbors(int vertex) const
{
    static const std::vector<int> empty;

    if (vertex < 1 || vertex > vertices)
    {
        return empty;
    }

    return adjacencyList[vertex];
}
