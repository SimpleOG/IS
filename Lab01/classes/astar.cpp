#include "../headers/astar.h"

SearchResult AStar::findPath(Input &input) {
    auto t = std::chrono::high_resolution_clock::now();
    SearchResult result;

    input.start.f = 0;
    input.start.g = 0;
    open.addNode(input.start);

    Node current;
    while (open.getSize() != 0) {
        current = open.getMin();

        open.popMin();
        closed.addClose(current);

        if (current.x == input.goal.x && current.y == input.goal.y) {
            result.cost = current.g;
            result.pathfound = true;
            result.path = reconstructPath(current);
            break;
        }

        std::list<Node> neighbors = input.map.getValidMoves(current);
        for (Node neighbor: neighbors) {
            if (closed.inClose(neighbor.x, neighbor.y))
                continue;
            neighbor.g = current.g + input.map.getCost(current, neighbor);
            neighbor.f = neighbor.g + getHValue(neighbor, input.goal, input.map.diagonal_moves_allowed);
            neighbor.parent = closed.getPointer(current.x, current.y);
            open.addNode(neighbor);
        }
    }

    result.createdNodes = closed.getSize() + open.getSize();
    result.steps = closed.getSize();
    result.runtime = std::chrono::duration_cast<std::chrono::duration<double>>(
            std::chrono::high_resolution_clock::now() - t).count();
    return result;
}

double AStar::getHValue(Node &current, Node &goal, bool dma) {
    int dx = abs(current.x - goal.x), dy = abs(current.y - goal.y);
    if (dma)
        return abs(dx - dy) + 1.41421356 * std::min(dx, dy);
    else
        return dx + dy;
}

std::list<Node> AStar::reconstructPath(Node &current) {
    std::list<Node> path;

    while (current.parent != nullptr) {
        path.push_front(current);
        current = *current.parent;
    }
    path.push_front(current);

    return path;
}

