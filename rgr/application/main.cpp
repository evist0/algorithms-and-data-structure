#include "graph/graph.hpp"
#include "vertex.hpp"
#include "edge.hpp"
#include "task_1.hpp"
#include "task_2.hpp"

typedef vertex<std::string, int> my_vertex;

typedef edge<::vertex<std::string, int>, int, int> my_edge;

typedef graph<::vertex<std::string, int>, ::edge<::vertex<std::string, int>, int, int >> my_graph;

int main() {
    my_graph* graph;
    my_vertex* vertex;
    my_edge* edge;

    my_graph::vertex_iterator* vIt;
    my_graph::edge_iterator* eIt;
    my_graph::outgoing_edge_iterator* oIt;

    std::cout << "1. Create Empty L-Graph" << std::endl;
    std::cout << "2. Create graph with vertices_amount vertices, without edges, type of D, form of F" << std::endl;
    std::cout << "3. Create graph with vertices_amount vertices, with edges_amount random edges, typeof D , form of F"
              << std::endl;
    std::cout << "4. Exit" << std::endl;
    while (true) {
        int menu;

        std::cout << "Choose operation: ";
        std::cin >> menu;

        switch (menu) {
        case 1: {
            graph = new my_graph();
            vIt = new my_graph::vertex_iterator(*graph);
            eIt = new my_graph::edge_iterator(*graph);
            break;
        }

        case 2: {
            int tmp1, tmp2, tmp3;

            std::cout << "Input vertices amount: ";
            std::cin >> tmp1;

            std::cout << "Oriented? (0 - false, 1 - true): ";
            std::cin >> tmp2;

            std::cout << "Form? (0 - L-Graph, 1 - M-Graph): ";
            std::cin >> tmp3;

            graph = new my_graph(tmp1, tmp2, tmp3);
            vIt = new my_graph::vertex_iterator(*graph);
            eIt = new my_graph::edge_iterator(*graph);
            break;
        }

        case 3: {
            int tmp1, tmp2, tmp3, tmp4;
            std::cout << "Input vertices amount: ";
            std::cin >> tmp1;
            std::cout << "Input edges amount: ";
            std::cin >> tmp2;
            std::cout << "Oriented? (0 - false, 1 - true): ";
            std::cin >> tmp3;
            std::cout << "Form? (0 - L-Graph, 1 - M-Graph): ";
            std::cin >> tmp4;

            graph = new my_graph(tmp1, tmp2, tmp3, tmp4);
            vIt = new my_graph::vertex_iterator(*graph);
            eIt = new my_graph::edge_iterator(*graph);
            break;
        }

        case 4: {
            return 0;
        }

        default: {
            std::cout << "Input Error" << std::endl;
        }
        }
        break;
    }

    while (true) {
        std::cout << "0. Print" << std::endl;
        std::cout << "1. Vertices amount" << std::endl;
        std::cout << "2. Edges amount" << std::endl;
        std::cout << "3. Graph type" << std::endl;
        std::cout << "4. Graph form" << std::endl;
        std::cout << "5. Saturation coefficient" << std::endl;
        std::cout << "6. To L-Graph" << std::endl;
        std::cout << "7. To M-Graph" << std::endl;
        std::cout << "8. Add vertex" << std::endl;
        std::cout << "9. Remove vertex" << std::endl;
        std::cout << "10. Insert Edge" << std::endl;
        std::cout << "11. Remove Edge" << std::endl;

        std::cout << std::endl << "Vertex Operations:" << std::endl;
        std::cout << "12. Read vertex data" << std::endl;
        std::cout << "13. Write vertex data" << std::endl;
        std::cout << "14. Rename Vertex" << std::endl;

        std::cout << std::endl << "Edge Operations:" << std::endl;
        std::cout << "15. Read edge weight" << std::endl;
        std::cout << "16. Read edge data" << std::endl;
        std::cout << "17. Write edge data" << std::endl;
        std::cout << "18. Write edge weight" << std::endl;

        std::cout << std::endl << "Vertex iterator:" << std::endl;
        std::cout << "19. begin()" << std::endl;
        std::cout << "20. end()" << std::endl;
        std::cout << "21. next()" << std::endl;
        std::cout << "22. Read Vertex Name" << std::endl;
        std::cout << "23. Read Vertex Data" << std::endl;
        std::cout << "24. Write Vertex Data" << std::endl;
        std::cout << "25. Rename Vertex" << std::endl;

        std::cout << std::endl << "Edge iterator:" << std::endl;
        std::cout << "26. begin()" << std::endl;
        std::cout << "27. end()" << std::endl;
        std::cout << "28. next()" << std::endl;
        std::cout << "29. Read Edge Weight" << std::endl;
        std::cout << "30. Read Edge Data" << std::endl;
        std::cout << "31. Write Edge Data" << std::endl;
        std::cout << "32. Write Edge Weight" << std::endl;

        std::cout << std::endl << "33. Iterator outgoing edges" << std::endl;

        std::cout << std::endl << "34. Classify edges from vertex" << std::endl;

        std::cout << std::endl << "40. Exit" << std::endl;

        int menu;
        std::cout << std::endl << "Choose Operation: ";
        std::cin >> menu;

        switch (menu) {
        case 0: {
            graph->print();
            break;
        }

        case 1: {
            std::cout << std::endl << graph->vertices_amount() << std::endl;
            break;
        }

        case 2: {
            std::cout << std::endl << graph->edges_amount() << std::endl;
            break;
        }

        case 3: {
            std::cout << std::endl << graph->directed() << std::endl;
            break;
        }

        case 4: {
            std::cout << std::endl << graph->dense() << std::endl;
            break;
        }

        case 5: {
            std::cout << std::endl << graph->saturation() << std::endl;
            break;
        }

        case 6: {
            graph->to_list();
            break;
        }

        case 7: {
            graph->to_matrix();
            break;
        }

        case 8: {
            std::cout << std::endl << graph->insert_v() << std::endl;
            break;
        }

        case 9: {
            std::string v1;
            std::cout << "Input vertex name: ";
            std::cin >> v1;

            std::cout << std::endl << graph->delete_v(v1) << std::endl;
            break;
        }

        case 10: {
            std::string v1, v2;
            std::cout << "First Vertex: ";
            std::cin >> v1;
            std::cout << "Second Vertex: ";
            std::cin >> v2;

            std::cout << std::endl << graph->insert_e(v1, v2) << std::endl;
            break;
        }

        case 11: {
            std::string v1, v2;
            std::cout << "First Vertex: ";
            std::cin >> v1;
            std::cout << "Second Vertex: ";
            std::cin >> v2;

            std::cout << std::endl << graph->delete_e(v1, v2) << std::endl;
            break;
        }

        case 12: {
            std::string v;
            std::cout << "Vertex Name: ";
            std::cin >> v;

            std::cout << std::endl << graph->read_v(v) << std::endl;
            break;
        }

        case 13: {
            int tmp;
            std::string v;
            std::cout << "Vertex Name: ";
            std::cin >> v;
            std::cout << "Input Data: ";
            std::cin >> tmp;

            std::cout << std::endl << graph->write_v(v, tmp) << std::endl;
            break;
        }

        case 14: {
            std::string v1, v2;
            std::cout << "Vertex Name: ";
            std::cin >> v1;
            std::cout << "New Vertex Name: ";
            std::cin >> v2;

            std::cout << std::endl << graph->rename_v(v1, v2) << std::endl;
            break;
        }

        case 15: {
            std::string v1, v2;
            std::cout << "First Vertex: ";
            std::cin >> v1;
            std::cout << "Second Vertex: ";
            std::cin >> v2;

            std::cout << std::endl << graph->weight_e(v1, v2) << std::endl;
            break;
        }

        case 16: {
            std::string v1, v2;
            std::cout << "First Vertex: ";
            std::cin >> v1;
            std::cout << "Second Vertex: ";
            std::cin >> v2;

            std::cout << std::endl << graph->data_e(v1, v2) << std::endl;
            break;
        }

        case 17: {
            int tmp;
            std::string v1, v2;
            std::cout << "First Vertex: ";
            std::cin >> v1;
            std::cout << "Second Vertex: ";
            std::cin >> v2;

            std::cout << "Edge Data: ";
            std::cin >> tmp;

            std::cout << std::endl << graph->write_data_e(v1, v2, tmp) << std::endl;
            break;
        }

        case 18: {
            int tmp;
            std::string v1, v2;
            std::cout << "First Vertex: ";
            std::cin >> v1;
            std::cout << "Second Vertex: ";
            std::cin >> v2;

            std::cout << "Edge weight: ";
            std::cin >> tmp;

            std::cout << std::endl << graph->write_weight_e(v1, v2, tmp) << std::endl;
            break;
        }

        case 19: {
            std::cout << std::endl << vIt->begin() << std::endl;
            break;
        }
        case 20: {
            std::cout << std::endl << vIt->to_end() << std::endl;
            break;
        }
        case 21: {
            try {
                ++*vIt;
            }
            catch (std::exception& e) {
                std::cerr << std::endl << "EXCEPTION" << std::endl;
            }

            break;
        }
        case 22: {
            try {
                std::cout << std::endl << vIt->read_vertex() << std::endl;
            }
            catch (std::exception& e) {
                std::cerr << std::endl << "EXCEPTION" << std::endl;
                break;
            }

            break;
        }
        case 23: {
            try {
                std::cout << std::endl << vIt->read_data_vertex() << std::endl;
            }
            catch (std::exception& e) {
                std::cerr << "EXCEPTION";
            }

            break;
        }
        case 24: {
            int tmp;
            std::cout << "Input Data: ";
            std::cin >> tmp;

            std::cout << std::endl << vIt->write_data_vertex(tmp) << std::endl;
            break;
        }
        case 25: {
            std::string cur;
            std::cout << "Input name: ";
            std::cin >> cur;

            std::cout << std::endl << vIt->write_name_vertex(cur) << std::endl;
            break;
        }

        case 26: {
            try {
                eIt->begin();
            }
            catch (std::exception& e) {
                std::cerr << std::endl << "EXCEPTION" << std::endl;
            }
            break;
        }

        case 27: {
            try {
                eIt->to_end();
            }
            catch (std::exception& e) {
                std::cerr << std::endl << "EXCEPTION" << std::endl;
            }

            break;
        }

        case 28: {
            try {
                ++*eIt;
            }
            catch (std::exception& e) {
                std::cerr << std::endl << "EXCEPTION" << std::endl;
            }

            break;
        }
        case 29: {
            try {
                std::cout << std::endl << eIt->read_weight_edge() << std::endl;
            }
            catch (std::exception& e) {
                std::cerr << std::endl << "EXCEPTION" << std::endl;
                break;
            }

            break;
        }
        case 30: {
            try {
                std::cout << std::endl << eIt->read_data_edge() << std::endl;
            }
            catch (std::exception& e) {
                std::cerr << std::endl << "EXCEPTION" << std::endl;
                break;
            }

            break;
        }
        case 31: {
            int tmp;
            std::cout << "Input Data: ";
            std::cin >> tmp;

            std::cout << std::endl << eIt->write_data_edge(tmp) << std::endl;
            break;
        }
        case 32: {
            int tmp;
            std::cout << "Input weight: ";
            std::cin >> tmp;

            std::cout << std::endl << eIt->write_weight_edge(tmp) << std::endl;
            break;
        }

        case 33: {
            int tmp, tmp2;
            bool ex = false;

            std::cout << std::endl << "Input Vertex: ";
            std::string name;
            std::cin >> name;

            try {
                oIt = new my_graph::outgoing_edge_iterator(*graph, *graph->get_vertex(name));
            }
            catch (std::exception& e) {
                std::cerr << "EXCEPTION";
                break;
            }

            while (true) {
                std::cout << std::endl << "Iterator Outgoing Edges:" << std::endl;
                std::cout << "1. begin()" << std::endl;
                std::cout << "2. end()" << std::endl;
                std::cout << "3. next()" << std::endl;
                std::cout << "4. Read weight" << std::endl;
                std::cout << "5. Read data" << std::endl;
                std::cout << "6. Write data" << std::endl;
                std::cout << "7. Write weight" << std::endl;
                std::cout << "10. Return" << std::endl;
                std::cout << std::endl << "Input Operation: ";
                std::cin >> tmp2;

                switch (tmp2) {
                case 1: {
                    oIt->begin();
                    break;
                }

                case 2: {
                    oIt->to_end();
                    break;
                }

                case 3: {
                    ++*oIt;

                    break;
                }

                case 4: {
                    try {
                        std::cout << std::endl << oIt->read_weight_edge() << std::endl;
                    }
                    catch (std::exception& e) {
                        std::cerr << std::endl << "EXCEPTION" << std::endl;
                    }
                    break;
                }

                case 5: {
                    try {
                        std::cout << std::endl << oIt->read_data_edge() << std::endl;
                    }
                    catch (std::exception& e) {
                        std::cerr << std::endl << "EXCEPTION" << std::endl;
                    }
                    break;
                }

                case 6: {
                    std::cout << "Input Data: ";
                    std::cin >> tmp;
                    std::cout << std::endl << oIt->write_data_edge(tmp) << std::endl;
                    break;
                }

                case 7: {
                    std::cout << "Input Weight: ";
                    std::cin >> tmp;

                    std::cout << std::endl << oIt->write_weight_edge(tmp) << std::endl;
                    break;
                }

                case 10: {
                    ex = true;
                    break;
                }

                default: {
                    std::cout << "Input error" << std::endl;
                }
                }
                if (ex) break;
            }
            break;
        }

        case 34: {
            int tmp;

            std::cout << std::endl << "Input Vertex: ";
            std::cin >> tmp;

            auto vertex_ = graph->get_vertex(tmp);

            auto task = task_1<my_vertex, my_edge>(graph, vertex_);

            auto result = task.result();

            for (auto pair: result) {
                auto v1 = pair.second->get_vertex1();
                auto v1_index = graph->get_v_index(v1);

                auto v2 = pair.second->get_vertex2();
                auto v2_index = graph->get_v_index(v2);

                if (pair.first == task_1<my_vertex, my_edge>::type::woody) {
                    std::cout << v1_index << "->" << v2_index << "woody" << std::endl;
                }

                if (pair.first == task_1<my_vertex, my_edge>::type::reverse) {
                    std::cout << v1_index << "->" << v2_index << "reverse" << std::endl;
                }

                if (pair.first == task_1<my_vertex, my_edge>::type::forward) {
                    std::cout << v1_index << "->" << v2_index << "forward" << std::endl;
                }

                if (pair.first == task_1<my_vertex, my_edge>::type::transverse) {
                    std::cout << v1_index << "->" << v2_index << "transverse" << std::endl;
                }
            }

            std::cout << std::endl;
            break;
        }

        case 35: {
            int tmp, tmp2;

            std::cout << std::endl << "Input Vertex: ";
            std::cin >> tmp;

            std::cout << std::endl << "Input Size: ";
            std::cin >> tmp2;

            auto vertex_ = graph->get_vertex(tmp);

            auto task = task_2<my_vertex, my_edge>(graph, 5);

            auto result = task.result();

            result->print();

            std::cout << std::endl;
            break;
        }

        case 40: {
            return 0;
        }
        default: {
            std::cout << "Input Error" << std::endl;
        }
        }
    }
}
