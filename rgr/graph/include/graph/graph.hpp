#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include <vertex.hpp>
#include <graph/graph_forms.hpp>

template<class V, class E>
class graph {
private:
    std::vector<V*> vertices_;
    abstract_form<E>* data_;

    bool directed_;
    bool dense_;
    int edges_amount_;

    int get_v_index_from_name_(std::string n);
    int sz_;

public:
    graph();
    graph(int vertex_count, bool directed_, bool dense_);
    graph(int vertex_count, int edgeCount, bool directed_, bool dense_);
    graph(const graph<V, E>& G);
    ~graph();

    int vertices_amount();
    int edges_amount();

    bool dense();
    bool directed();
    double saturation();

    void to_list();
    void to_matrix();

    // Vertices
    V* insert_v();

    bool delete_v(int index);
    bool delete_v(V* v);
    bool delete_v(std::string n);

    int get_v_index(V* v);
    V* get_vertex(std::string n);
    V* get_vertex(int index);

    bool rename_v(std::string v, std::string str);

    bool write_v(std::string v1, int d);
    int read_v(std::string v1);

    // Edges
    E* insert_e(V* v1, V* v2);
    bool insert_e(std::string v1, std::string v2);

    bool delete_e(std::string v1, std::string v2);
    bool delete_e(V* v1, V* v2);

    E* get_edge(V* v1, V* v2);

    bool has_edge(V* v1, V* v2);
    bool has_edge(int v1, int v2);

    int weight_e(std::string _v1, std::string _v2); //Прочитать вес ребра
    int data_e(std::string _v1, std::string _v2); //Прочитать данные о ребре
    bool write_weight_e(std::string _v1, std::string _v2, int w); //Записать вес ребра
    bool write_data_e(std::string _v1, std::string _v2, int data_); //Записать данные о ребре

    void print();

    class vertex_iterator {
    private:
        graph<V, E>* graph_;
        bool end_;
        int current_;
    public:
        vertex_iterator(graph<V, E>& g) {
            graph_ = &g;
        };

        bool begin() {
            if (graph_->vertices_.size() == 0) {
                end_ = true;
                return false;
            }
            current_ = 0;
            end_ = false;
            return true;
        }

        bool operator++() {
            try {
                if (end_) {
                    current_ = -1;
                    throw std::bad_exception();
                }
            }
            catch (std::exception& error) {
                return false;
            }

            current_++;
            if (graph_->vertices_.size() - 1 == current_) {
                end_ = true;
            }

            return true;
        }

        bool to_end() {
            end_ = true;
            current_ = graph_->vertices_.size() - 1;
            if (current_ < 0)
                return false;
            else
                return true;
        }

        bool on_end() {
            return end_;
        }

        V* operator*() {
            if (current_ >= graph_->vertices_.size() || current_ == -1)
                throw std::bad_exception();

            return graph_->vertices_[current_];
        }

        std::string read_vertex() {
            auto* v = operator*();

            if (v->is_name_set())
                return v->get_name();
            else
                throw std::bad_exception();
        }

        int read_data_vertex() {
            auto v = operator*();

            if (v->is_data_set())
                return v->get_data();
            else throw std::bad_exception();
        }

        bool write_data_vertex(int d) {
            try {
                auto v = operator*();
                v->set_data(d);
                return true;
            }
            catch (std::exception& error) {
                return false;
            }
        }

        //Записать имя вершины по текущей позиции итератора
        bool write_name_vertex(std::string str) {
            try {
                auto v = operator*();
                v->set_name(str);
                return true;
            }
            catch (std::exception& error) {
                return false;
            }
        }
    };

    class edge_iterator {
        graph<V, E>* graph_; //Обрабатываемый граф
        typename m_graph<E>::edge_iterator* mIt;
        typename l_graph<E>::edge_iterator* lIt;
        bool useM;
    public:
        int curV1, curV2;
        std::string str1, str2, str3, str4;
        bool end;

        edge_iterator(graph<V, E>& g) {
            graph_ = &g;
            if (graph_->dense()) {
                mIt = new typename m_graph<E>::edge_iterator(static_cast<m_graph<E>*>(g.data_));
                useM = true;
            }
            else {
                lIt = new typename l_graph<E>::edge_iterator(static_cast<l_graph<E>*>(g.data_));
                useM = false;
            }
        }

        bool begin() {
            if (useM)
                return mIt->begin();
            else
                return lIt->begin();
        }

        bool operator++() {
            if (useM)
                return mIt->next();
            else
                return lIt->next();
        }

        bool on_end() {
            if (useM)
                return mIt->on_end();
            else
                return lIt->on_end();
        }

        bool to_end() {
            if (useM)
                return mIt->to_end();
            else
                return lIt->to_end();
        }

        E* operator*() {
            if (on_end())
                throw std::bad_exception();

            if (useM)
                return mIt->get_edge();
            else
                return lIt->get_edge();
        }

        int read_weight_edge() {
            E* f;
            try {
                f = operator*();
            }
            catch (char* e) {
                throw std::bad_exception();
            }
            if (f->is_weight_set())
                return f->get_weight();
            else
                throw std::bad_exception();
        };

        int read_data_edge() {
            E* f;
            try {
                f = operator*();
            }
            catch (char* e) {
                throw std::bad_exception();
            }
            if (f->is_data_set())
                return f->get_data();
            else
                throw std::bad_exception();
        };

        bool write_data_edge(int d) {
            E* e;
            try {
                e = operator*();
            }
            catch (char* e) {
                return false;
            }
            e->set_data(d);
            return true;
        };

        bool write_weight_edge(int w) {
            E* e;
            try {
                e = operator*();
            }
            catch (char* Error) {
                return false;
            }
            e->set_weight(w);
            return true;
        }

    };

    class outgoing_edge_iterator {
        graph<V, E>* graph_;
        typename m_graph<E>::outgoing_edge_iterator* mIt;
        typename l_graph<E>::outgoing_edge_iterator* lIt;
        bool useM;
    public:
        bool end;
        int curV1, curV2;

        outgoing_edge_iterator(graph<V, E>& g, V& v) {
            graph_ = &g;
            curV1 = graph_->get_v_index(&v);
            if (graph_->dense_) {
                mIt = new typename m_graph<E>::outgoing_edge_iterator(static_cast<m_graph<E>*>(g.data_),
                        curV1);
                useM = true;
            }
            else {
                lIt = new typename l_graph<E>::outgoing_edge_iterator(static_cast<l_graph<E>*>(g.data_), curV1);
                useM = false;
            }
        }

        bool begin() {
            if (useM)
                return mIt->begin();
            else
                return lIt->begin();
        }

        bool operator++() {
            if (useM)
                return mIt->next();
            else
                return lIt->next();
        }

        bool to_end() {
            if (useM)
                return mIt->to_end();
            else
                return lIt->to_end();
        }

        bool on_end() {
            if (useM)
                return mIt->on_end();
            else
                return lIt->on_end();
        }

        E* operator*() {
            if (on_end())
                throw std::bad_exception();
            if (useM)
                return mIt->get_edge();
            else
                return lIt->get_edge();
        }

        int read_weight_edge() {
            E* e;
            try {
                e = operator*();
            }
            catch (char* f) {
                throw std::bad_exception();
            }
            if (e->is_weight_set())
                return e->get_weight();
            else
                throw std::bad_exception();
        };

        int read_data_edge() {
            E* e;
            try {
                e = operator*();
            }
            catch (char* f) {
                throw std::bad_exception();
            }
            if (e->is_data_set())
                return e->get_data();
            else
                throw std::bad_exception();
        };

        bool write_data_edge(int d) {
            E* e;
            try {
                e = operator*();
            }
            catch (char* Error) {
                return false;
            }
            e->set_data(d);
            return true;
        };

        bool write_weight_edge(int w) {
            E* e;
            try {
                e = operator*();
            }
            catch (char* Error) {
                return false;
            }
            e->set_weight(w);
            return true;
        }

    };
};

template<class V, class E>
int graph<V, E>::get_v_index_from_name_(std::string n) {
    int index = 0;
    for (int i = 0; i < vertices_.size(); i++) {
        if (vertices_[index]->get_name() == n)
            break;
        ++index;
    }
    if (index == vertices_.size())
        throw std::bad_exception();
    return index;
}

template<class V, class E>
graph<V, E>::graph() {
    sz_ = 0;
    data_ = new l_graph<E>(false);
    directed_ = true;
    dense_ = false;
    edges_amount_ = 0;
}

template<class V, class E>
graph<V, E>::graph(int vertex_count, bool directed_, bool dense_) {
    sz_ = 0;
    if (dense_)
        data_ = new m_graph<E>(directed_);
    else
        data_ = new l_graph<E>(directed_);

    for (int i = 0; i < vertex_count; i++)
        data_->insert_v(i);
    for (int i = 0; i < vertex_count; i++) {
        auto v = new V();
        v->set_name(std::to_string(sz_));
        sz_++;
        vertices_.push_back(v);
        data_->insert_v(i);
    }
    this->directed_ = directed_;
    this->dense_ = dense_;
    edges_amount_ = 0;
}

template<class V, class E>
graph<V, E>::graph(int vertex_count, int edgeCount, bool directed_, bool dense_) {
    sz_ = 0;
    if (dense_)
        data_ = new m_graph<E>(directed_);
    else
        data_ = new l_graph<E>(directed_);

    // Создаём вершины и помещаем в структуру
    for (int i = 0; i < vertex_count; i++)
        data_->insert_v(i);
    for (int i = 0; i < vertex_count; i++) {
        auto v = new V();
        v->set_name(std::to_string(sz_));
        sz_++;
        vertices_.push_back(v);
        data_->insert_v(i);
    }
    this->directed_ = directed_;
    this->dense_ = dense_;
    edges_amount_ = 0;

    if (edgeCount <= 0) return;
    if (directed_) {
        if (edgeCount > vertex_count * (vertex_count - 1))
            edgeCount = vertex_count * (vertex_count - 1);
        srand((unsigned)time(NULL));
    }
    else {
        if (edgeCount > (vertex_count * (vertex_count - 1)) / 2)
            edgeCount = (vertex_count * (vertex_count - 1)) / 2;
    }
    int v1, v2;

    while (edges_amount_ < edgeCount) {
        v1 = rand() % vertex_count;
        v2 = rand() % vertex_count;
        if (v1 == v2)
            continue;
        if (data_->has_edge(v1, v2))
            continue;

        auto t = new E(vertices_[v1], vertices_[v2]);
        data_->insert_e(v1, v2, t);
        t->set_weight((rand() % 9) + 1);
        if (directed_ == false)
            data_->insert_e(v2, v1, t);
        edges_amount_++;
    }
}

// Конструктор копирования
template<class V, class E>
graph<V, E>::graph(const graph<V, E>& G) {
    sz_ = 0;
    delete data_;
    if (G.dense())
        data_ = new m_graph<E>(*(G.data_));
    else
        data_ = new l_graph<E>(*(G.data_));
    directed_ = G.directed_;
    dense_ = G.dense_;
}

// Деструктор
template<class V, class E>
graph<V, E>::~graph() {
    while (vertices_.size() != 0)
        delete_v(0);
    delete data_;
}

// Информация о графе
// Число вершин, рёбер, насыщенность
template<class V, class E>
int graph<V, E>::vertices_amount() {
    return vertices_.size();
}

template<class V, class E>
int graph<V, E>::edges_amount() {
    return edges_amount_;
}

// Возвращает тип графа
template<class V, class E>
bool graph<V, E>::directed() {
    return directed_;
}

// Возвращает форму представления графа
template<class V, class E>
bool graph<V, E>::dense() {
    return dense_;
}

// Возвращает коэффициент насыщенности графа
template<class V, class E>
double graph<V, E>::saturation() {
    int max = vertices_.size() * (vertices_.size() - 1);
    if (!directed_) {
        max /= 2;
    }
    if (max == 0) {
        return -1;
    }
    else {
        return (double)edges_amount_ / (double)max;
    }
}

// Преобразует граф к L-графу
template<class V, class E>
void graph<V, E>::to_list() {
    // Создаём структуру хранения L-графа
    abstract_form<E>* newData = new l_graph<E>(this->directed_);

    // Создаём вершины
    for (int i = 0; i < vertices_.size(); i++)
        newData->insert_v(i);

    // Переносим рёбра
    for (int i = 0; i < vertices_.size(); i++)
        for (int j = 0; j < vertices_.size(); j++)
            if (data_->has_edge(i, j))
                newData->insert_e(i, j, data_->get_edge(i, j));
    delete data_;
    data_ = newData;
    dense_ = false;
}

// Преобразует граф к M-графу
template<class V, class E>
void graph<V, E>::to_matrix() {
    // Создаём структуру хранения М-графа
    abstract_form<E>* newData = new m_graph<E>(this->directed_);

    // Создаём вершины
    for (int i = 0; i < vertices_.size(); i++)
        newData->insert_v(i);

    // Переносим рёбра
    for (int i = 0; i < vertices_.size(); i++)
        for (int j = 0; j < vertices_.size(); j++)
            if (data_->has_edge(i, j))
                newData->insert_e(i, j, data_->get_edge(i, j));

    delete data_;
    data_ = newData;
    dense_ = true;
}

template<class V, class E>
V* graph<V, E>::insert_v() {
    auto v = new V();
    if (data_->insert_v(vertices_.size()) == false)
        throw std::bad_exception();
    v->set_name(std::to_string(sz_));
    sz_++;
    vertices_.push_back(v);
    return v;
}

template<class V, class E>
bool graph<V, E>::delete_v(V* v) {
    int index = get_v_index(v);
    edges_amount_ -= data_->delete_adj_e(index, directed_);
    if (data_->delete_v(index)) {
        vertices_.erase(vertices_.begin() + index);//
        return true;
    }
    return false;
}

template<class V, class E>
bool graph<V, E>::delete_v(int index) {
    edges_amount_ -= data_->DeleteEsFromvertex(index, directed_);
    if (data_->delete_v(index)) {
        vertices_.erase(vertices_.begin() + index);//
        return true;
    }
    return false;
}

template<class V, class E>
bool graph<V, E>::delete_v(std::string n) {
    try {
        auto v = get_vertex(n);

        return delete_v(v);
    }
    catch (std::exception* e) {
        return false;
    }
}

template<class V, class E>
V* graph<V, E>::get_vertex(int index) {
    if (index < 0 || index >= vertices_.size())
        throw std::bad_exception();

    return vertices_[index];
}

template<class V, class E>
V* graph<V, E>::get_vertex(std::string n) {
    for (int i = 0; i < vertices_.size(); i++)
        if (vertices_[i]->get_name() == n)
            return vertices_[i];

    throw std::bad_exception();
}

template<class V, class E>
int graph<V, E>::get_v_index(V* v) {
    int index = 0;
    for (int i = 0; i < vertices_.size(); ++i) {
        if (vertices_[index] == v)
            break;
        index++;
    }
    if (index == vertices_.size())
        throw std::bad_exception();

    return index;
}

template<class V, class E>
bool graph<V, E>::insert_e(std::string v1, std::string v2) {
    try {
        auto _v1 = new V();
        auto _v2 = new V();

        _v1 = get_vertex(v1);
        _v2 = get_vertex(v2);
        insert_e(_v1, _v2);
    }
    catch (std::exception& error) {
        return false;
    }

    return true;
}

template<class V, class E>
E* graph<V, E>::insert_e(V* v1, V* v2) {
    E* e = new E(v1, v2);
    if (!data_->insert_e(get_v_index(v1), get_v_index(v2), e)) throw std::bad_exception();

    if (directed_ == false)
        data_->insert_e(get_v_index(v2), get_v_index(v1), e);
    edges_amount_++;
    return e;
}

template<class V, class E>
bool graph<V, E>::delete_e(std::string v1, std::string v2) {

    try {
        auto _v1 = new V();
        auto _v2 = new V();

        _v1 = get_vertex(v1);
        _v2 = get_vertex(v2);

        if (!delete_e(_v1, _v2)) return false;
        else return true;
    }
    catch (std::exception& error) {
        return false;
    }
}

template<class V, class E>
bool graph<V, E>::delete_e(V* v1, V* v2) {
    if (data_->delete_e(get_v_index(v1), get_v_index(v2))) {
        edges_amount_--;
        if (directed_ == false)
            data_->delete_e(get_v_index(v2), get_v_index(v1));
        return true;
    }
    else
        return false;
}

template<class V, class E>
bool graph<V, E>::has_edge(V* v1, V* v2) {
    int ind1, ind2;

    try {
        ind1 = get_v_index(v1);
    }
    catch (std::exception& error) {
        return false;
    }
    try {
        ind2 = get_v_index(v2);
    }
    catch (std::exception& error) {
        return false;
    }
    return data_->has_edge(get_v_index(v1), get_v_index(v2));
}

template<class V, class E>
bool graph<V, E>::has_edge(int v1, int v2) {
    if (v1 < 0 || v1 >= vertices_.size())
        return false;
    if (v2 < 0 || v2 >= vertices_.size())
        return false;
    return data_->has_edge(v1, v2);
}

template<class V, class E>
E* graph<V, E>::get_edge(V* v1, V* v2) {
    E* e;
    try {
        e = data_->get_edge(get_v_index(v1), get_v_index(v2));
    }
    catch (std::exception& error) {
        throw std::bad_exception();
    }
    return e;
}

template<class V, class E>
bool graph<V, E>::write_data_e(std::string _v1, std::string _v2, int data_) {
    try {
        auto v1 = get_vertex(_v1);
        auto v2 = get_vertex(_v2);

        auto e = get_edge(v1, v2);
        e->set_data(data_);
    }
    catch (std::exception& error) {
        return false;
    }

    return true;
}

template<class V, class E>
bool graph<V, E>::write_weight_e(std::string _v1, std::string _v2, int w) {
    try {
        auto v1 = get_vertex(_v1);
        auto v2 = get_vertex(_v2);

        auto e = get_edge(v1, v2);
        e->set_weight(w);
    }
    catch (std::exception& error) {
        return false;
    }

    return true;
}

template<class V, class E>
int graph<V, E>::data_e(std::string _v1, std::string _v2) {
    try {
        auto v1 = get_vertex(_v1);
        auto v2 = get_vertex(_v2);

        auto e = get_edge(v1, v2);

        return e->get_data();
    }
    catch (std::exception& error) {
        return -1;
    }
}

template<class V, class E>
int graph<V, E>::weight_e(std::string _v1, std::string _v2) {
    try {
        auto v1 = get_vertex(_v1);
        auto v2 = get_vertex(_v2);
        auto e = get_edge(v1, v2);

        return e->get_weight();
    }
    catch (std::exception& error) {
        return -1;
    }
}

template<class V, class E>
void graph<V, E>::print() {
    if (dense_) {
        std::cout << std::setw(5) << "  ";

        for (int i = 0; i < vertices_amount(); i++) {
            auto v = get_vertex(i);
            std::cout << std::setw(4) << v->get_name();
        }
        std::cout << std::endl;

        for (int i = 0; i < 5 * vertices_amount() + 4; i++)
            std::cout << "_";
        std::cout << std::endl;

        for (int i = 0; i < vertices_amount(); i++) {
            auto v = get_vertex(i);
            std::cout << std::setw(4) << v->get_name() << "|";
            for (int j = 0; j < vertices_amount(); j++)
                if (has_edge(i, j)) {
                    auto e = get_edge(get_vertex(i), get_vertex(j));
                    std::cout << std::setw(4) << e->get_weight();
                }
                else
                    std::cout << std::setw(4) << "-";
            std::cout << std::endl;
        }
    }
    else {
        for (int i = 0; i < vertices_amount(); i++) {
            auto v = get_vertex(i);

            std::cout << v->get_name() << ": ";
            for (auto j = 0; j < vertices_amount(); j++) {
                v = get_vertex(j);
                if (has_edge(i, j))
                    std::cout << v->get_name() << "; ";
            }
            std::cout << std::endl;
        }
    }
};

template<class V, class E>
int graph<V, E>::read_v(std::string v1) {
    try {
        auto v = get_vertex(v1);
        auto d = v->get_data();
    }
    catch (std::exception& error) {
        return -1;
    }
}

template<class V, class E>
bool graph<V, E>::write_v(std::string v1, int d) {
    try {
        auto v = get_vertex(v1);
        v->set_data(d);
    }
    catch (std::exception& error) {
        return false;
    }

    return true;
}

template<class V, class E>
bool graph<V, E>::rename_v(std::string v1, std::string str) {
    try {
        auto v = get_vertex(v1);
        v->set_name(str);
    }
    catch (std::exception& error) {
        return false;
    }

    return true;
}
