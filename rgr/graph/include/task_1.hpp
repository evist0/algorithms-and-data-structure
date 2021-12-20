#pragma once
#include <graph/graph.hpp>
#include <string>
#include <map>
#include <set>
#include <queue>

template<class V, class E>
class task_1 {
public:
    enum class type {
        woody,
        reverse,
        forward,
        transverse
    };

    task_1(graph<V, E>* g, V* v)
            :graph_(g), vertex_(v) {
        start();
    }

    task_1(const task_1<V, E>& t1)
            :graph_(t1.g), vertex_(t1.v) {
    }

    void set(graph<V, E>* g, V* v) {
        graph_ = g;
        vertex_ = v;

        start();
    }

    void start() {
        visit_vertices();
        calculate_result();
    }

    std::vector<std::pair<type, E*>> result() {
        return result_;
    }

private:
    graph<V, E>* graph_;
    V* vertex_;

    struct description {
        int color;
        int d;
        V* p;
        int f;
    };

    int counter_;
    std::map<V*, description> vertex_description_;
    std::queue<E*> path_;

    std::vector<std::pair<type, E*>> result_;

    type analyze_edge(V* u, V* v) {
        type edge_type;

        auto v1 = vertex_description_[u];
        auto v2 = vertex_description_[v];

        if (v1.d < v2.d && v1.f > v2.f && v2.p == u)
            edge_type = type::woody;
        if (v1.d > v2.d && v1.f < v2.f)
            edge_type = type::reverse;
        if (v1.d < v2.d && v1.f > v2.f && v2.p != u)
            edge_type = type::forward;
        if (v1.d > v2.d && v1.f > v2.f)
            edge_type = type::transverse;

        return edge_type;
    }

    void calculate_result() {        //Цикл по рёбрам:
        while (!path_.empty()) {
            E* current_edge = path_.front();
            path_.pop();

            V* u = current_edge->get_vertex1();
            V* v = current_edge->get_vertex2();

            result_.emplace_back(analyze_edge(u, v), current_edge);
        }
    }

    void visit_vertices() {
        vertex_description_.clear();
        counter_ = 0;

        auto it = new typename graph<V, E>::vertex_iterator(*graph_);
        it->begin();

        while (!(it->on_end())) {
            vertex_description_[*(*it)].color = 0;
            vertex_description_[*(*it)].p = NULL;
            ++(*it);
        }

        visit_vertex(vertex_);

        it->begin();
        while (!(it->on_end())) {
            if (vertex_description_[*(*it)].color == 0)
                visit_vertex(*(*it));
            ++(*it);
        }
    }

    void visit_vertex(V* u) {
        vertex_description_[u].color = 1;
        vertex_description_[u].d = ++counter_;

        auto itout = new typename graph<V, E>::outgoing_edge_iterator(*graph_, *u);

        itout->begin();
        E* cedge = nullptr;

        while (!(itout->on_end())) {
            cedge = *(*itout);
            path_.push(cedge);
            V* v = NULL;
            if (cedge->get_vertex1() == u)
                v = cedge->get_vertex2();
            else
                v = cedge->get_vertex1();

            if (vertex_description_[v].color == 0) {
                vertex_description_[v].p = u;
                visit_vertex(v);
            }
            ++(*itout);
        }
        vertex_description_[u].color = 2;
        vertex_description_[u].f = counter_++;
    }
};
