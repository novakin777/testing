#include "Graph.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace
{
    int passed = 0;
    int failed = 0;

    void check(bool condition, const std::string& testName)
    {
        if (condition)
        {
            std::cout << "Тест пройден: " << testName << "\n";
            passed++;
        }
        else
        {
            std::cout << "Тест не пройден: " << testName << "\n";
            failed++;
        }
    }

    bool equal(const std::vector<int>& actual, const std::vector<int>& expected)
    {
        return actual == expected;
    }

    bool isValidNumber(const std::string& text, long long& number)
    {
        std::istringstream input(text);
        std::string extra;

        if (!(input >> number) || (input >> extra))
        {
            return false;
        }

        return number >= -1000000000 && number <= 1000000000;
    }
}

void runTests()
{
    std::cout << "Результаты тестирования графа:\n\n";

    Graph emptyGraph(0);
    check(emptyGraph.getVertexCount() == 0 && emptyGraph.printGraph().empty(),
          "Создание пустого графа");

    Graph graph(3);
    check(graph.getVertexCount() == 3 &&
              graph.getNeighbors(1).empty() &&
              graph.getNeighbors(2).empty() &&
              graph.getNeighbors(3).empty(),
          "Создание графа без рёбер");

    check(graph.addEdge(1, 2) && equal(graph.getNeighbors(1), { 2 }),
          "Добавление одного ребра");

    Graph exampleGraph(8);
    exampleGraph.addEdge(1, 3);
    exampleGraph.addEdge(1, 7);
    exampleGraph.addEdge(3, 1);
    exampleGraph.addEdge(3, 4);
    exampleGraph.addEdge(2, 4);
    exampleGraph.addEdge(2, 5);
    exampleGraph.addEdge(7, 3);
    exampleGraph.addEdge(7, 8);
    exampleGraph.addEdge(6, 4);
    exampleGraph.addEdge(8, 6);

    check(equal(exampleGraph.getNeighbors(1), { 3, 7 }) &&
              equal(exampleGraph.getNeighbors(2), { 4, 5 }) &&
              equal(exampleGraph.getNeighbors(3), { 1, 4 }) &&
              equal(exampleGraph.getNeighbors(7), { 3, 8 }),
          "Добавление рёбер из примера");

    const std::string expectedOutput =
        "Вершина 1: 3 7 \n"
        "Вершина 2: 4 5 \n"
        "Вершина 3: 1 4 \n"
        "Вершина 4: \n"
        "Вершина 5: \n"
        "Вершина 6: 4 \n"
        "Вершина 7: 3 8 \n"
        "Вершина 8: 6 \n";

    check(exampleGraph.printGraph() == expectedOutput,
          "Корректный вывод списка смежности");

    check(!exampleGraph.addEdge(0, 10) && !exampleGraph.addEdge(9, 1) &&
              exampleGraph.getNeighbors(1).size() == 2,
          "Обработка некорректных индексов");

    long long number = 0;
    check(isValidNumber("25", number) && number == 25,
          "Корректное число из ReadNumber");
    check(!isValidNumber("abc", number),
          "Неверный формат из ReadNumber");
    check(!isValidNumber("1000000001", number),
          "Число больше верхней границы из ReadNumber");
    check(!isValidNumber("-1000000001", number),
          "Число меньше нижней границы из ReadNumber");

    std::cout << "\nВсего тестов: " << passed + failed << "\n";
    std::cout << "Пройдено: " << passed << "\n";
    std::cout << "Не пройдено: " << failed << "\n";
}
