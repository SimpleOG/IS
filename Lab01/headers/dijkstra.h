#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "astar.h"

class Dijkstra : public AStar {
    ClosedList closed;
    OpenList open;
public:
    double getHValue(Node &current, Node &goal, bool dma) override {
        return 0;
    }
};

#endif // DIJKSTRA_H
