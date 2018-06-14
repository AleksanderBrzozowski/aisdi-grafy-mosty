//
// Created by abrzozowski on 14.06.18.
//

#ifndef AISDI_GRAFY_MOSTY_GRAPH_H
#define AISDI_GRAFY_MOSTY_GRAPH_H


#include <vector>
#include <algorithm>
#include <iostream>
#include "Edge.h"

class Graph {
public:
    Graph(int vertices, const std::vector<Edge> &edges) : vertices(vertices) {
        this->adj = new std::vector<int>[vertices];
        std::for_each(edges.begin(), edges.end(), [this](const Edge &edge) {
            this->adj[edge.v1].push_back(edge.v2);
        });
    }

    std::vector<Edge> findBridges() {
        std::vector<Edge> bridges;
        for (int i = 0; i < vertices; ++i) {
            const auto adjVertices = adj[i];
            std::for_each(adjVertices.begin(), adjVertices.end(), [&adjVertices, i, &bridges, this](int v) {
                const auto removedVerticesAdj = withRemovedVerticesAdj(i, v);
                if (!isCoherent(removedVerticesAdj)) {
                    bridges.push_back(Edge {v1: i, v2: v});
                }
            });
        }

        return bridges;
    }

private:
    const int vertices;
    std::vector<int> *adj;

    const std::vector<int> *withRemovedVerticesAdj(int v1, int v2) {
        const auto withRemovedVerticesAdj = new std::vector<int>[vertices];
        for (int i = 0; i < vertices; ++i) {
            if (i != v1 && i != v2) {
                withRemovedVerticesAdj[i] = adj[i];
                withRemovedVerticesAdj[i].erase(
                        std::remove_if(withRemovedVerticesAdj[i].begin(), withRemovedVerticesAdj[i].end(),
                                       [v1, v2](int v) {
                                           return v == v1 || v == v2;
                                       }),
                        withRemovedVerticesAdj[i].end()
                );
            } else {
                withRemovedVerticesAdj[i] = std::vector<int>(0);
            }
        }
        return withRemovedVerticesAdj;
    }

    bool isCoherent(const std::vector<int> adj[]) {
        bool visited[vertices] = {0};
        int startV = -1;
        for (int i = 0; i < vertices; ++i) {
            if (!adj[i].empty()) {
                startV = i;
                break;
            }
        }
        if (startV == -1) {
            return true;
        }

        dfs(startV, visited, adj);

        const auto visitedCount = std::count_if(visited, visited + vertices, [](const bool visit) { return visit; });
        return visitedCount + 2 == vertices;
    }

    void dfs(int v, bool visited[], const std::vector<int> adj[]) {
        visited[v] = true;
        std::for_each(adj[v].begin(), adj[v].end(), [visited, this, &adj](int v) {
            if (!visited[v]) {
                dfs(v, visited, adj);
            }
        });
    }
};


#endif //AISDI_GRAFY_MOSTY_GRAPH_H
