#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <container.hpp>

TEST_CASE("Должен инициализироваться с размером 0") {
		auto l = container<int>();

		REQUIRE(l.size() == 0);
}

TEST_CASE("Должен изменять размер и вместимость") {
		auto l = container<int>();

		l.push_back(1);
		l.push_back(2);

		REQUIRE(l.size() == 2);
}

TEST_CASE("Должна быть отчистка списка") {
		auto l = container<int>();

		REQUIRE(l.size() == 0);

		l.push_back(1);
		l.push_back(2);

		REQUIRE(l.size() == 2);

		l.erase();

		REQUIRE(l.size() == 0);
}

TEST_CASE("Должен быть опрос на пустоту") {
		auto l = container<int>();

		REQUIRE(l.empty());

		l.push_back(1);
		l.push_back(2);

		REQUIRE(!l.empty());

		l.erase();

		REQUIRE(l.empty());
}

TEST_CASE("Должен быть опрос наличия заданного значения") {
		auto l = container<int>();

		l.push_back(1);

		REQUIRE(l.contains(1));
		REQUIRE(!l.contains(2));
}

TEST_CASE("Должно быть чтение значения с заданным номером в списке") {
		auto l = container<int>();

		l.push_back(1);
		l.push_back(2);

		REQUIRE(l[0] == 1);
		REQUIRE(l[1] == 2);
}

TEST_CASE("Должно быть изменение значения с заданным номером в списке") {
		auto l = container<int>();

		l.push_back(1);

		REQUIRE(l[0] == 1);

		l[0] = 2;

		REQUIRE(l[0] == 2);
}

TEST_CASE("Должно быть получение позиции для заданного значения") {
		auto l = container<int>();

		l.push_back(1);
		l.push_back(2);
		l.insert(1, 3);

		REQUIRE(l.find(1) == 0);
		REQUIRE(l.find(3) == 1);
		REQUIRE(l.find(2) == 2);
}

TEST_CASE("Должно быть включение нового значения") {
		auto l = container<int>();

		int three = 3;

		l.push_back(1);
		l.push_back(2);
		l.push_back(three);

		REQUIRE(l.contains(1));
		REQUIRE(l.contains(2));
}

TEST_CASE("Должно быть включение нового значения с заданным номером") {
		auto l = container<int>();

		l.push_back(1);
		REQUIRE(l.contains(1));

		l.push_back(2);
		REQUIRE(l.contains(2));

		l.insert(1, 3);
		REQUIRE(l.contains(3));
}

TEST_CASE("Должно быть удаление заданного значения из списка") {
		auto l = container<int>();
		l.push_back(2);
		l.push_front(1);
		l.push_back(3);

		l.remove_value(1);
		REQUIRE(!l.contains(1));
}

TEST_CASE("Должно быть удаление значения с заданным номером") {
		auto l = container<int>();

		l.push_back(1);
		REQUIRE(l.contains(1));

		l.remove(0);
		REQUIRE(!l.contains(1));

		l.push_back(2);
		l.push_back(1);
		l.push_back(3);
		REQUIRE(l.contains(1));

		l.remove(1);
		REQUIRE(!l.contains(1));
}

TEST_CASE("Shiza") {
		auto l = container<int>();

		l.push_back(1);
		l.push_back(2);
		l.push_back(3);
		l.push_back(4);

		l.remove(0);

		l.remove_value(5);
		REQUIRE(!l.contains(5));

		l.insert(3, 5);

		REQUIRE(l[3] == 5);
}

TEST_CASE("should throw exception if capacity exceeded") {
		auto l = container<int>();

		container<int>::iterator iterator = { &l, 0 };

		l.push_back(1);
		l.push_back(2);
		l.push_back(3);
		l.push_back(4);

		try {
				l.push_back(5);
		}
		catch (std::out_of_range e) {
				REQUIRE(true);
		}
}