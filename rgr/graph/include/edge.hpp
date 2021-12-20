#pragma once

template<class V, class W, class D>
class edge {
    V* v1, * v2;
    W weight;
    D data;
    bool weight_set_, data_set_;
public:
    edge(V* v1, V* v2);
    edge(V* v1, V* v2, W weight);
    edge(V* v1, V* v2, W weight, D data);
    void set_weight(W weight);
    void set_data(D data);
    W get_weight();
    D get_data();
    bool is_weight_set();
    bool is_data_set();
    V* get_vertex1();
    V* get_vertex2();
};

//Конструкторы
template<class V, class W, class D>
edge<V, W, D>::edge(V* v1, V* v2)
        :
        v1(v1),
        v2(v2),
        weight_set_(false),
        weight(0),
        data_set_(false) {
}

template<class V, class W, class D>
edge<V, W, D>::edge(V* v1, V* v2, W weight)
        :
        v1(v1),
        v2(v2),
        weight(weight),
        weight_set_(true),
        data_set_(false) {
}

template<class V, class W, class D>
edge<V, W, D>::edge(V* v1, V* v2, W weight, D data)
        :
        v1(v1),
        v2(v2),
        weight(weight),
        data(data),
        weight_set_(true),
        data_set_(true) {
}

template<class V, class W, class D>
void edge<V, W, D>::set_weight(W weight) {
    this->weight = weight;
    weight_set_ = true;
}

template<class V, class W, class D>
void edge<V, W, D>::set_data(D data) {
    this->data = data;
    data_set_ = true;
}

template<class V, class W, class D>
W edge<V, W, D>::get_weight() {
    return weight;
}

template<class V, class W, class D>
D edge<V, W, D>::get_data() {
    return data;
}

template<class V, class W, class D>
V* edge<V, W, D>::get_vertex1() {
    return v1;
}

template<class V, class W, class D>
V* edge<V, W, D>::get_vertex2() {
    return v2;
}

template<class V, class W, class D>
bool edge<V, W, D>::is_weight_set() {
    return weight_set_;
}

template<class V, class W, class D>
bool edge<V, W, D>::is_data_set() {
    return data_set_;
}