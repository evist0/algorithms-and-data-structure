#pragma once

template<class N, class D>
class vertex {
    N name;
    D data;
    bool name_set_, data_set_;

public:
    vertex();
    vertex(N name, D data);
    void set_name(N name);
    void set_data(D data);
    N get_name();
    D get_data();
    bool is_name_set();
    bool is_data_set();
};

//Конструкторы
template<class N, class D>
vertex<N, D>::vertex()
        : name_set_(false), data_set_(false) {
}

template<class N, class D>
vertex<N, D>::vertex(N name, D data)
        :
        name(name),
        data(data),
        name_set_(true),
        data_set_(true) {
}

//Установка, получение имени и данных
template<class N, class D>
void vertex<N, D>::set_name(N name) {
    this->name = name;
    name_set_ = true;
}

template<class N, class D>
void vertex<N, D>::set_data(D data) {
    this->data = data;
    data_set_ = true;
}

template<class N, class D>
N vertex<N, D>::get_name() {
    return name;
}

template<class N, class D>
D vertex<N, D>::get_data() {
    return data;
}

template<class N, class D>
bool vertex<N, D>::is_name_set() {
    return name_set_;
}

template<class N, class D>
bool vertex<N, D>::is_data_set() {
    return data_set_;
}
