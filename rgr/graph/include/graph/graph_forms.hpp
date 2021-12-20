#pragma once
#include <vector>
#include <list>

template<class E> class abstract_form {
public:
    virtual bool insert_v(int index) = 0;
    virtual bool delete_v(int index) = 0;

    virtual bool insert_e(int v1, int v2, E* t) = 0;
    virtual bool delete_e(int v1, int v2) = 0;

    // Удалить входящие и исходящие из вершины рёбра
    virtual int delete_adj_e(int index, bool directed) = 0;

    virtual bool has_edge(int v1, int v2) = 0;
    virtual E* get_edge(int v1, int v2) = 0;
};

template<class E> class m_graph : public abstract_form<E> {
    bool directed_;
public:
    std::vector<std::vector<E*>> matrix_;

    m_graph(bool directed)
            :directed_(directed) {
    }

    bool insert_v(int index) {
        int size = matrix_.size();

        //Неверный номер вершины
        if (index < 0 || index > size) return false;

        //Создаём новую пустую строку
        std::vector<E*> newLine;
        newLine.assign(size, NULL);

        //Вставляем новую строку:
        matrix_.insert(matrix_.begin() + index, newLine);
        ++size;

        //Вставляем новый столбец:
        for (int i = 0; i < size; ++i) {
            matrix_[i].insert(matrix_[i].begin() + index, (E*)NULL);
        }
        return true;
    }

    bool delete_v(int index) {
        int size = matrix_.size();

        //Неверный номер вершины
        if (index < 0 || index >= size)
            return false;

        //Удаляем строку:
        matrix_.erase(matrix_.begin() + index);
        --size;

        //Удаляем столбец:
        for (int i = 0; i < size; i++) {
            matrix_[i].erase(matrix_[i].begin() + index);
        }
        return true;
    }

    bool insert_e(int v1, int v2, E* t) {
        int size = matrix_.size();

        //Неверный номер вершины
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size) return false;

        //Петля или ребро уже есть
        if (v1 == v2 || matrix_[v1][v2] != NULL) return false;

        //Вставляем ребро
        matrix_[v1][v2] = t;
        return true;
    }

    bool delete_e(int v1, int v2) {
        int size = matrix_.size();

        //Неверный номер вершины
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size) return false;

        //Ребра нет
        if (v1 == v2 || matrix_[v1][v2] == NULL) return false;

        matrix_[v1][v2] = NULL;
        return true;
    }

    int delete_adj_e(int index, bool directed) {
        int size = matrix_.size();

        //Неверный номер вершины
        if (index < 0 || index >= size) return 0;

        int deleted = 0;

        //Удаляем связанные с вершиной рёбра
        for (int i = 0; i < size; i++) {
            if (matrix_[i][index] != NULL) {
                delete matrix_[i][index];
                matrix_[i][index] = NULL;
                ++deleted;

                //Стираем симметричное ребро
                if (!directed)
                    matrix_[index][i] = NULL;
            }
            if (matrix_[index][i] != NULL) {
                delete matrix_[index][i];
                matrix_[index][i] = NULL;
                ++deleted;
            }
        }

        return deleted;
    }

    // Проверка и получение
    bool has_edge(int v1, int v2) {
        int size = matrix_.size(); // Число вершин

        // Неверный номер вершины
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
            return false;

        // Петля
        if (v1 == v2)
            return false;

        if (matrix_[v1][v2] != NULL)
            return true;

        return false;
    }

    E* get_edge(int v1, int v2) {
        int size = matrix_.size();

        // Неверный номер вершины
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
            throw std::bad_exception();

        // Петля
        if (v1 == v2 || matrix_[v1][v2] == nullptr)
            return nullptr;

        return matrix_[v1][v2];
    }

    class edge_iterator {
        bool end;
        m_graph* f;
    public:
        int curI, curJ;

        edge_iterator(m_graph* f) {
            this->f = f;
            begin();
        }

        bool begin() {
            for (int i = 0; i < f->matrix_.size(); ++i)
                for (int j = 0; j < f->matrix_.size(); ++j)
                    if (f->matrix_[i][j]) {
                        curI = i;
                        curJ = j;
                        end = false;
                        return true;
                    }
            end = true;
            return false;
        }

        bool on_end() {
            return end;
        }

        bool to_end() {
            for (int i = f->matrix_.size() - 1; i >= 0; --i)
                for (int j = f->matrix_.size() - 1; j >= 0; --j)
                    if (f->matrix_[i][j]) {
                        curI = i;
                        curJ = j;
                        end = false;
                        return true;
                    }
            end = true;
            return false;
        }

        bool next() {
            if (end)
                return false;
            ++curJ;
            while (curI < f->matrix_.size()) {
                while (curJ < f->matrix_.size()) {
                    if (f->matrix_[curI][curJ])
                        return true;
                    ++curJ;
                }
                ++curI;
                curJ = (f->directed_ ? 0 : curI + 1);
            }
            end = true;
            return false;
        }

        E* get_edge() {
            if (end)
                throw std::bad_exception();;
            if (!(f->matrix_[curI][curJ]))
                throw std::bad_exception();;
            return f->matrix_[curI][curJ];
        }
    };

    class outgoing_edge_iterator {
        int curI, curJ;
        bool end;
        m_graph* f;
    public:
        outgoing_edge_iterator(m_graph* f, int vIndex) {
            this->f = f;
            curI = vIndex;
            begin();
        }

        bool begin() {
            for (curJ = 0; curJ < f->matrix_.size(); ++curJ)
                if (f->matrix_[curI][curJ]) {
                    end = false;
                    return true;
                }
            end = true;
            return false;
        }

        bool to_end() {
            for (curJ = f->matrix_.size() - 1; curJ >= 0; --curJ)
                if (f->matrix_[curI][curJ]) {
                    end = false;
                    return true;
                }
            end = true;
            return false;
        }

        bool on_end() {
            return end;
        }

        bool next() {
            if (end)
                return false;
            ++curJ;
            while (curJ < f->matrix_.size()) {
                if (f->matrix_[curI][curJ])
                    return true;
                ++curJ;
            }
            end = true;
            return false;
        }

        E* get_edge() {
            if (end)
                throw std::bad_exception();;
            return f->matrix_[curI][curJ];
        }
    };
};

template<class E> class l_graph : public abstract_form<E> {
    class node {
    public:
        E* edge;
        int v2;
    };

    bool directed_;
    std::vector<std::list<node>> edge_list_;

public:
    l_graph(bool directed)
            :directed_(directed) {
    }

    bool insert_v(int index) {
        int size = edge_list_.size();

        // Неверный номер вершины
        if (index < 0 || index > size)
            return false;

        // Создаём новый список смежности
        std::list<node> newList;

        // Вставляем
        edge_list_.insert(edge_list_.begin() + index, newList);
        ++size;

        // Обновляем дескрипторы
        for (int i = 0; i < size; ++i)
            for (typename std::list<node>::iterator j = edge_list_[i].begin(); j != edge_list_[i].end(); ++j)
                if ((*j).v2 >= index) // Если текущая вершина больше, чем вставляемая, то увеличиваем этот номер
                    ++((*j).v2);
        return true;
    }

    bool delete_v(int index) {
        int size = edge_list_.size();

        // Неверный номер вершины
        if (index < 0 || index >= size)
            return false;

        // Удаляем из списков записи о рёбрах
        for (int i = 0; i < size; ++i)
            for (typename std::list<node>::iterator j = edge_list_[i].begin(); j != edge_list_[i].end(); ++j)
                if ((*j).v2 == index) {
                    edge_list_[i].erase(j);
                    break;
                }

        // Удаляем список смежности
        edge_list_.erase(edge_list_.begin() + index);
        --size;

        //Обновляем дескрипторы
        for (int i = 0; i < size; ++i)
            for (typename std::list<node>::iterator j = edge_list_[i].begin(); j != edge_list_[i].end(); ++j)
                if ((*j).v2 > index) // Если текущая вершина имеет больший номер, чем удаляемая, то уменьшить этот номер
                    --((*j).v2);
        return true;
    }

    bool insert_e(int v1, int v2, E* t) {
        int size = edge_list_.size();

        // Неверный номер вершины
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
            return false;

        //Петля или ребро уже есть
        if (v1 == v2 || has_edge(v1, v2))
            return false;

        //Вставляем ребро
        node node;
        node.edge = t;
        node.v2 = v2;
        edge_list_[v1].push_front(node);
        return true;
    }

    bool delete_e(int v1, int v2) {
        int size = edge_list_.size();

        //Неверный номер вершины
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
            return false;

        //Ребра нет
        if (v1 == v2 || has_edge(v1, v2) == false)
            return false;

        //Удаляем ребро
        for (typename std::list<node>::iterator j = edge_list_[v1].begin(); j != edge_list_[v1].end(); ++j)
            if ((*j).v2 == v2) {
                edge_list_[v1].erase(j);
                break;
            }
        return true;
    }

    int delete_adj_e(int index, bool directed) {
        int size = edge_list_.size();

        //Неверный номер вершины
        if (index < 0 || index >= size)
            return 0;

        int deleted = 0;

        //Удаляем связанные с вершиной рёбра
        for (int i = 0; i < size; ++i)
            for (typename std::list<node>::iterator j = edge_list_[i].begin(); j != edge_list_[i].end(); ++j)
                if ((*j).v2 == index) {
                    //Стираем симметричное ребро
                    if (!directed)
                        for (typename std::list<node>::iterator k = edge_list_[index].begin();
                             k != edge_list_[index].end();
                             ++k)
                            if ((*k).v2 == i) {
                                edge_list_[index].erase(k);
                                break;
                            }
                    delete (*j).edge;
                    edge_list_[i].erase(j);
                    ++deleted;
                    break;
                }
        return deleted;
    }

    bool has_edge(int v1, int v2) {
        int size = edge_list_.size();

        //Неверный номер вершины
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
            return false;

        //Петля
        if (v1 == v2)
            return false;
        for (typename std::list<node>::iterator j = edge_list_[v1].begin(); j != edge_list_[v1].end(); ++j)
            if ((*j).v2 == v2)
                return true;
        return false;
    }

    E* get_edge(int v1, int v2) {
        int size = edge_list_.size();

        //Неверный номер вершины
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
            throw std::bad_exception();

        //Петля
        if (v1 == v2)
            throw std::bad_exception();;
        for (typename std::list<node>::iterator j = edge_list_[v1].begin(); j != edge_list_[v1].end(); ++j)
            if ((*j).v2 == v2)
                return (*j).edge;
        throw std::bad_exception();
    }

    class edge_iterator {
        int curI;
        typename std::list<typename l_graph<E>::node>::iterator curJ;
        bool end;
        l_graph* f;
    public:
        edge_iterator(l_graph* f) {
            this->f = f;
        }

        bool begin() {
            for (curI = 0; curI < f->edge_list_.size(); ++curI)
                for (curJ = f->edge_list_[curI].begin(); curJ != f->edge_list_[curI].end(); ++curJ)
                    if ((*curJ).edge) {
                        end = false;
                        return true;
                    }
            end = true;
            return false;
        }

        bool on_end() {
            return end;
        }

        //Установить итератор рёбер на конечное ребро
        bool to_end() {
            typename std::list<typename l_graph<E>::node>::iterator prev_curJ;
            for (curI = 0; curI < f->edge_list_.size(); ++curI) {
                for (curJ = f->edge_list_[curI].begin(); curJ != f->edge_list_[curI].end(); ++curJ) {
                    if ((*curJ).edge)
                        prev_curJ = curJ;
                    if (!(*prev_curJ).edge) {
                        end = true;
                        return false;
                    }
                    else {
                        end = false;
                        curJ = prev_curJ;
                        return true;
                    }
                }
            }
        };

        bool next() {
            if (end)
                return false;
            ++curJ;
            while (curI < f->edge_list_.size()) {
                while (curJ != f->edge_list_[curI].end()) {
                    if ((*curJ).edge && (f->directed_ || !f->directed_ && (*curJ).v2 > curI))
                        return true;
                    ++curJ;
                }
                ++curI;
                if (curI < f->edge_list_.size())
                    curJ = f->edge_list_[curI].begin();
            }
            end = true;
            return true;
        }

        E* get_edge() {
            if (end)
                throw std::bad_exception();;
            return (*curJ).edge;
        }
    };

    class outgoing_edge_iterator {
        int curI;
        typename std::list<typename l_graph<E>::node>::iterator curJ;
        bool end;
        l_graph* f;
    public:
        outgoing_edge_iterator(l_graph* f, int vIndex) {
            this->f = f;
            curI = vIndex;
            begin();
        }

        bool begin() {
            for (curJ = f->edge_list_[curI].begin(); curJ != f->edge_list_[curI].end(); ++curJ)
                if ((*curJ).edge) {
                    end = false;
                    return true;
                }
            end = true;
            return false;
        }

        bool on_end() {
            return end;
        }

        bool to_end() {
            typename std::list<typename l_graph<E>::node>::iterator prev_curJ;
            for (curJ = f->edge_list_[curI].begin(); curJ != f->edge_list_[curI].end(); ++curJ)
                if ((*curJ).edge)
                    prev_curJ = curJ;
            if (!(*prev_curJ).edge) {
                end = true;
                return false;
            }
            else {
                end = false;
                curJ = prev_curJ;
                return true;
            };
        }

        bool next() {
            if (end)
                return false;
            ++curJ;
            while (curJ != f->edge_list_[curI].end()) {
                if ((*curJ).edge)
                    return true;
                ++curJ;
            }
            end = true;
            return true;
        }

        E* get_edge() {
            if (end)
                throw std::bad_exception();;
            return (*curJ).edge;
        }
    };
};
