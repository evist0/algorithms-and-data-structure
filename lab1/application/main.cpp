#include <iostream>
#include <container.hpp>

int input_key_ui() {
    int value;
    std::cout << "\n\n Please input position. \n\n";

    std::cin >> value;

    return value;
}

int input_value_ui() {
    int value;
    std::cout << "\n\n Please, input value. \n\n";

    std::cin >> value;

    return value;
}

void emplace_ui(container<int>& container) {
    int selected;

    while (true) {
        std::cout << "\t\t Emplace element"
                     "\n 1. Emplace front"
                     "\n 2. Emplace back"
                     "\n 3. Emplace position"
                     "\n 0. Exit" << std::endl;

        std::cin >> selected;

        if (selected == 1) {
            auto value = input_value_ui();
            container.push_front(value);
        }

        if (selected == 2) {
            auto value = input_value_ui();
            container.push_back(value);
        }

        if (selected == 3) {
            auto position = input_key_ui();
            auto value = input_value_ui();
            container.insert(position, value);
        }

        if (selected == 0) {
            return;
        }
    }
}

void edit_ui(container<int>& container) {
    auto position = input_key_ui();
    auto value = input_value_ui();

    container[position] = value;
}

void remove_ui(container<int>& container) {
    int selected;

    while (true) {
        std::cout << "\t\t Remove element"
                     "\n 1. By value"
                     "\n 2. By position"
                     "\n 0. Exit" << std::endl;

        std::cin >> selected;

        if (selected == 1) {
            auto value = input_value_ui();
            std::cout << container.remove_value(value);
        }

        if (selected == 2) {
            auto position = input_key_ui();
            container.remove(position);
        }

        if (selected == 0) {
            return;
        }
    }
}

void search_ui(container<int>& container) {
    auto value = input_value_ui();
    std::cout << container.find(value);
}

void erase_ui(container<int>& container) {
    container.erase();
    std::cout << "\n\n Container cleared! \n\n";
}

void empty_ui(container<int>& container) {
    std::cout << container.empty();
}

void print_ui(container<int>& container) {
    for (std::size_t i = 0; i < container.size(); i++) {
        std::cout << container[i] << " ";
    }

    std::cout << std::endl;
}

void iterator_ui(container<int>::iterator& iterator, container<int>& container) {
    int selected;

		while (true) {
				std::cout << "\t\t Iterator menu"
				             "\n 1. Begin"
				             "\n 2. End"
				             "\n 3. Next"
				             "\n 4. Print"
				             "\n 5. Equals to begin"
				             "\n 6. Equals to end"
																	"\n 7. Modify"
				             "\n 0. Exit" << std::endl;

        std::cin >> selected;

        if (selected == 1) {
            iterator = container.begin();
        }

        if (selected == 2) { ;
            iterator = container.end();
        }

        if (selected == 3) {
            iterator = iterator.next();
        }

        if (selected == 4) {
            std::cout << *iterator;
        }

        if (selected == 5) {
            std::cout << (iterator == container.begin());
        }

        if (selected == 6) {
            std::cout << (iterator == container.end());
        }

        if (selected == 7) {
            std::cout << "Input new value";
            std::cin >> *iterator;
        }

        if (selected == 0) {
            return;
        }
    }
}

int main() {
    int selected;

    auto main_container = container<int>(5);
    auto main_container_iter = main_container.begin();

		while (true) {
				try {
						std::cout << "\t\t Main menu"
						             "\n 1. Emplace element"
						             "\n 2. Edit element"
						             "\n 3. Remove element"
						             "\n 4. Search element"
						             "\n 5. Clear container"
						             "\n 6. Check empty"
						             "\n 7. Print values"
						             "\n 8. Iterator menu"
						             "\n 0. Exit" << std::endl;

            std::cin >> selected;

            switch (selected) {
            case 1:
                emplace_ui(main_container);
                break;
            case 2:
                edit_ui(main_container);
                break;
            case 3:
                remove_ui(main_container);
                break;
            case 4:
                search_ui(main_container);
                break;
            case 5:
                erase_ui(main_container);
                break;
            case 6:
                empty_ui(main_container);
                break;
            case 7:
                print_ui(main_container);
                break;
            case 8:
                iterator_ui(main_container_iter, main_container);
                break;
            case 0:
                return 0;

            default:
                std::cout << "Unknown value. Try again.";
            }
        }
        catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
}