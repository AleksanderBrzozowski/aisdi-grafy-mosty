#include <iostream>
#include "Graph.h"

int main() {
//    const auto edges = std::vector<Edge>({Edge{0, 2}, Edge{3, 0}, Edge{0, 1}, Edge{1, 2}, Edge{2, 3}});
    const auto edges = std::vector<Edge>({Edge{1, 3}, Edge{0, 1}, Edge{0, 2}, Edge{2, 3}, Edge{3, 4}});
//    const auto edges = std::vector<Edge>({Edge{0, 1}, Edge{0, 2}, Edge{1, 2} });
    auto g = Graph(5, edges);
    auto bridges = g.findBridges();
    return 0;
}