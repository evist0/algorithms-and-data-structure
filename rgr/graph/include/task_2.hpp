#pragma once
#include <algorithm>
#include "graph/graph.hpp"
#include "edge.hpp"

template<class V, class E>
class task_2 {
public:
    task_2(graph<V, E>* g, std::size_t d)
            :graph_(g) {
        result_ = new graph<V, E>(g->vertices_amount(), false, true);

        start();
    }

    void set(graph<V, E>* g, std::size_t d) {
        graph_ = g;
        result_ = new graph<V, E>(g->vertices_amount(), false, true);
    };

    void start() {
        std::vector<E*> edges;

        auto eIt = typename graph<V, E>::edge_iterator(*graph_);

        while (++eIt) {
            edges.push_back(*eIt);
        }

        std::sort(edges.begin(), edges.end());

        for (auto edge_iterator: edges) {
            auto v1 = edge_iterator->get_vertex1();
            auto v2 = edge_iterator->get_vertex2();

            if (!result_->has_edge(v1, v2)) {
                result_->insert_e(v1, v2);
            }
        }
    }

    graph<V, E>* result() {
        return result_;
    }

private:
    graph<V, E>* graph_;

    graph<V, E>* result_;

    bool comp(E* a, E* b) {
        return a->get_weight() < b->get_weight();
    }
};
