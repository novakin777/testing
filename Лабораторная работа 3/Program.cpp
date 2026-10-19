#include "Graph.h"

#include <windows.h>
#include <iostream>
#include <string>

void runTests();

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "Лабораторная работа 3. Тестовое покрытие на графах\n";
    std::cout << "1 - Показать граф\n";
    std::cout << "2 - Запустить тесты\n";
    std::cout << "Выберите действие: ";

    std::string choice;
    std::getline(std::cin, choice);

    if (choice == "2")
    {
        runTests();
        return 0;
    }

    Graph graph(8);
    graph.addEdge(1, 3);
    graph.addEdge(1, 7);
    graph.addEdge(3, 1);
    graph.addEdge(3, 4);
    graph.addEdge(2, 4);
    graph.addEdge(2, 5);
    graph.addEdge(7, 3);
    graph.addEdge(7, 8);
    graph.addEdge(6, 4);
    graph.addEdge(8, 6);

    std::cout << "\nСписок смежности:\n";
    std::cout << graph.printGraph();
    return 0;
}
