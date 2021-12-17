#include <iostream>
#include<rbst.hpp>

int input_key_ui() {
    int value;
    std::cout << "Please, input key." << std::endl;

    std::cin >> value;

    std::cout << std::endl;

    return value;
}

int input_value_ui() {
    int value;
    std::cout << "Please, input value." << std::endl;

    std::cin >> value;

    std::cout << std::endl;

    return value;
}

void insert_ui(rbst<int, int>& container) {
    auto key = input_key_ui();
    auto value = input_value_ui();

    std::cout << container.insert(key, value) << std::endl << std::endl;
}

void modify_ui(rbst<int, int>& container) {
    auto key = input_key_ui();
    auto value = input_value_ui();

    container[key] = value;
}

void read_ui(rbst<int, int>& container) {
    auto key = input_key_ui();

    std::cout << container[key] << std::endl << std::endl;
}

void remove_ui(rbst<int, int>& container) {
    auto key = input_key_ui();

    std::cout << container.remove(key) << std::endl << std::endl;
}

void size_ui(rbst<int, int>& container) {
    std::cout << container.size() << std::endl << std::endl;
}

void clear_ui(rbst<int, int>& container) {
    container.clear();
    std::cout << std::endl << std::endl;
}

void empty_ui(rbst<int, int>& container) {
    std::cout << container.empty() << std::endl << std::endl;
}

void depth_ui(rbst<int, int>& container) {
    std::cout << container.depth() << std::endl << std::endl;
}

void keys_ui(rbst<int, int>& container) {
    auto keys = container.keys();

    for (auto key: keys) {
        std::cout << key << " ";
    }

    std::cout << std::endl << std::endl;
}

void print_ui(rbst<int, int>& container) {
    container.print(std::cout);
    std::cout << std::endl;
}

void iterator_ui(rbst<int, int>::iterator& iterator, rbst<int, int>& container) {
    int selected;

    while (true) {
        std::cout << "\t\t Iterator menu"
                     "\n 1. Next"
                     "\n 2. Previous"
                     "\n\n"
                     "\n 3. Read"
                     "\n 4. Modify"
                     "\n\n"
                     "\n 5. Equals to begin"
                     "\n 6. Equals to end"
                     "\n 0. Exit" << std::endl;

        std::cin >> selected;

        std::cout << std::endl;

        if (selected == 1) {
            ++iterator;
        }

        if (selected == 2) {
            --iterator;
        }

        if (selected == 3) {
            std::cout << *iterator << std::endl;
        }

        if (selected == 4) {
            auto value = input_value_ui();

            *iterator = value;
        }

        if (selected == 5) {
            std::cout << (iterator == container.begin()) << std::endl;
        }

        if (selected == 6) {
            std::cout << (iterator == container.end()) << std::endl;
        }

        if (selected == 0) {
            return;
        }
    }
}

void reverse_iterator_ui(rbst<int, int>::reverse_iterator& riterator, rbst<int, int>& container) {
    int selected;

    while (true) {
        std::cout << "\t\t Iterator menu"
                     "\n 1. Next"
                     "\n 2. Previous"
                     "\n\n"
                     "\n 3. Read"
                     "\n 4. Modify"
                     "\n\n"
                     "\n 5. Equals to begin"
                     "\n 6. Equals to end"
                     "\n 0. Exit" << std::endl;

        std::cin >> selected;

        std::cout << std::endl;

        if (selected == 1) {
            ++riterator;
        }

        if (selected == 2) {
            --riterator;
        }

        if (selected == 3) {
            std::cout << *riterator << std::endl;
        }

        if (selected == 4) {
            auto value = input_value_ui();

            *riterator = value;
        }

        if (selected == 5) {
            std::cout << (riterator == container.rbegin()) << std::endl;
        }

        if (selected == 6) {
            std::cout << (riterator == container.rend()) << std::endl;
        }

        if (selected == 0) {
            return;
        }
    }
}

int main() {
    int selected;

    auto container = rbst<int, int>();

    auto container_iterator = container.begin();

    auto container_reverse_iterator = container.rbegin();

    while (true) {
        try {
            std::cout << "\t\t Main menu"
                         "\n 1. Insert"
                         "\n 2. Modify"
                         "\n 3. Read"
                         "\n 4. Remove"
                         "\n 5. Size"
                         "\n 6. Clear"
                         "\n 7. Check empty"
                         "\n 8. Depth"
                         "\n 9. Keys"
                         "\n 10. Print"
                         "\n 11. iterator = begin()"
                         "\n 12. iterator = end()"
                         "\n 13. reverse_iterator = rbegin()"
                         "\n 14. reverse_iterator = rend()"
                         "\n 15. Iterator menu"
                         "\n 16. Reverse iterator menu"
                         "\n 0. Exit" << std::endl;

            std::cin >> selected;

            std::cout << std::endl;

            switch (selected) {
            case 1:
                insert_ui(container);
                break;
            case 2:
                modify_ui(container);
                break;
            case 3:
                read_ui(container);
                break;
            case 4:
                remove_ui(container);
                break;
            case 5:
                size_ui(container);
                break;
            case 6:
                clear_ui(container);
                break;
            case 7:
                empty_ui(container);
                break;
            case 8:
                depth_ui(container);
                break;
            case 9:
                keys_ui(container);
                break;
            case 10:
                print_ui(container);
                break;
            case 11:
                container_iterator = container.begin();
                break;
            case 12:
                container_iterator = container.end();
                break;
            case 13:
                container_reverse_iterator = container.rbegin();
                break;
            case 14:
                container_reverse_iterator = container.rend();
                break;
            case 15:
                iterator_ui(container_iterator, container);
                break;
            case 16:
                reverse_iterator_ui(container_reverse_iterator, container);
                break;

            case 0:
                return 0;

            default:
                std::cout << "Unknown value. Try again.";
            }
        }

        catch (std::exception& e) {
            std::cerr << std::endl << e.what() << std::endl;
        }
    }
}