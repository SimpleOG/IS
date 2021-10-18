#include <iostream>
#include "headers/dijkstra.h"

int main(int argc, const char *argv[]) {
//    Dijkstra planner;
    AStar planner;
    bool diagonal_moves_allowed = false;

    std::string input_name = "../Lab01/Data/8.map";
    if (argc > 1)
        input_name = argv[1];
    Input input(input_name, diagonal_moves_allowed);

    SearchResult result = planner.findPath(input);

    if (result.pathfound) {
        for (auto it = result.path.begin(); it != --result.path.end(); it++)
            std::cout << "(" << it->x << "," << it->y << ")->";
        std::cout << "(" << (--result.path.end())->x << "," << (--result.path.end())->y << ")";
    } else
        std::cout << "PATH NOT FOUND!";

    std::cout << "\nCost: " << result.cost
              << "\nRuntime: " << result.runtime
              << "\nSteps: " << result.steps
              << "\nNodes Created: " << result.createdNodes
              << "\nTrue Cardinal Cost: " << input.true_cardinal_cost
              << "\nTrue Diagonal Cost: " << input.true_diagonal_cost << "\n";
    return 0;
}
