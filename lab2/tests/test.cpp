#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <bst.hpp>

TEST_CASE("copy constructor") {
    auto tree = bst<int, int>();

    tree.insert(30, 30);
    tree.insert(10, 10);
    tree.insert(50, 50);

    auto another_tree = bst<int, int>(tree);

    SECTION("should copy") {
        REQUIRE(another_tree.size() == tree.size());

        REQUIRE(another_tree[30] == tree[30]);
        REQUIRE(another_tree[10] == tree[10]);
        REQUIRE(another_tree[50] == tree[50]);
    }

    SECTION("should be unique") {
        tree[30] = 300;
        tree[10] = 100;
        tree[50] = 500;

        REQUIRE(another_tree[30] != tree[30]);
        REQUIRE(another_tree[10] != tree[10]);
        REQUIRE(another_tree[50] != tree[50]);
    }
}

TEST_CASE("insert") {
    auto tree = bst<int, int>();

    tree.insert(30, 30);

    SECTION("should insert") {
        REQUIRE(tree[30] == 30);
    }

    SECTION("should insert left") {
        tree.insert(15, 15);
        REQUIRE(tree[30] == 30);
        REQUIRE(tree[15] == 15);
    }

    SECTION("should insert right") {
        tree.insert(45, 45);
        REQUIRE(tree[30] == 30);
        REQUIRE(tree[45] == 45);
    }

    SECTION("should return false if key exists") {
        REQUIRE(tree.insert(30, 30) == false);
    }
}

TEST_CASE("key access") {
    auto tree = bst<int, int>();

    tree.insert(30, 30);

    tree.insert(10, 10);
    tree.insert(50, 50);

    tree.insert(5, 5);
    tree.insert(15, 15);
    tree.insert(12, 12);
    tree.insert(13, 13);

    tree.insert(40, 40);
    tree.insert(60, 60);

    SECTION("should throw exception if not found") {
        REQUIRE_THROWS(tree[105] = 5);
    }

    SECTION("should return reference to the element") {
        tree[12] = 101;
        REQUIRE(tree[12] == 101);
    }
}

TEST_CASE("remove") {
    auto tree = bst<int, int>();

    tree.insert(30, 30);

    tree.insert(10, 10);
    tree.insert(50, 50);

    tree.insert(5, 5);
    tree.insert(15, 15);
    tree.insert(12, 12);
    tree.insert(13, 13);

    tree.insert(40, 40);
    tree.insert(60, 60);

    SECTION("should return false if not found") {
        REQUIRE(tree.remove(25) == false);
    }

    SECTION("should remove with no children") {
        REQUIRE(tree[13] == 13);

        REQUIRE(tree.remove(13));

        REQUIRE_THROWS(tree[13] == 13);
    }

    SECTION("should remove with left children") {
        REQUIRE(tree[15] == 15);

        REQUIRE(tree.remove(15));

        REQUIRE_THROWS(tree[15] == 15);

        REQUIRE(tree[12] == 12);
    }

    SECTION("should remove with right children") {
        REQUIRE(tree[12] == 12);

        REQUIRE(tree.remove(12));

        REQUIRE_THROWS(tree[12] == 12);

        REQUIRE(tree[13] == 13);
    }

    SECTION("should remove with both children") {
        REQUIRE(tree[30] == 30);

        REQUIRE(tree.remove(30));

        REQUIRE_THROWS(tree[30] == 30);

        REQUIRE(tree[10] == 10);
        REQUIRE(tree[50] == 50);

        REQUIRE(tree[5] == 5);
        REQUIRE(tree[15] == 15);
        REQUIRE(tree[12] == 12);
        REQUIRE(tree[13] == 13);

        REQUIRE(tree[40] == 40);
        REQUIRE(tree[60] == 60);
    }
}

TEST_CASE("size") {
    auto tree = bst<int, int>();

    tree.insert(30, 30);
    tree.insert(10, 10);
    tree.insert(50, 50);

    SECTION("should return size") {
        REQUIRE(tree.size() == 3);
    }

    SECTION("should return size after insert") {
        tree.insert(60, 60);
        REQUIRE(tree.size() == 4);
    }

    SECTION("should return size after remove") {
        tree.remove(10);
        REQUIRE(tree.size() == 2);
    }
}

TEST_CASE("clear") {
    auto tree = bst<int, int>();

    tree.insert(30, 30);
    tree.insert(10, 10);
    tree.insert(50, 50);

    SECTION("should clear and return true") {
        tree.clear();

        REQUIRE_THROWS(tree[30] == 30);
        REQUIRE_THROWS(tree[10] == 10);
        REQUIRE_THROWS(tree[50] == 50);

        REQUIRE(tree.size() == 0);
    }
}

TEST_CASE("empty") {
    auto tree = bst<int, int>();

    tree.insert(30, 30);
    tree.insert(10, 10);
    tree.insert(50, 50);

    SECTION("should return false") {
        REQUIRE(tree.empty() == false);
    }

    SECTION("should return true") {
        tree.clear();
        REQUIRE(tree.empty());
    }
}

TEST_CASE("depth") {
    auto tree = bst<int, int>();

    tree.insert(30, 30);

    tree.insert(10, 10);
    tree.insert(50, 50);

    tree.insert(5, 5);
    tree.insert(15, 15);
    tree.insert(12, 12);
    tree.insert(13, 13);

    tree.insert(40, 40);
    tree.insert(60, 60);

    SECTION("should return depth properly") {
        REQUIRE(tree.depth() == 5);
    }
}

TEST_CASE("keys") {
    auto tree = bst<int, int>();

    tree.insert(30, 30);

    tree.insert(10, 10);
    tree.insert(50, 50);

    tree.insert(5, 5);
    tree.insert(15, 15);
    tree.insert(12, 12);
    tree.insert(13, 13);

    tree.insert(40, 40);
    tree.insert(60, 60);

    SECTION("should return keys_ in t -> Lt -> Rt order") {
        auto keys = tree.keys();
        std::vector<int> expected_keys = { 30, 10, 5, 15, 12, 13, 50, 40, 60 };

        REQUIRE(keys == expected_keys);
    }
}

TEST_CASE("iterator") {
    auto tree = bst<int, int>();

    tree.insert(30, 30);

    tree.insert(10, 10);
    tree.insert(50, 50);

    tree.insert(5, 5);
    tree.insert(15, 15);
    tree.insert(12, 12);
    tree.insert(13, 13);

    tree.insert(40, 40);
    tree.insert(60, 60);

    auto iterator = tree.begin();

    SECTION("should equals to rend if rbegin--") {
        REQUIRE(--iterator == tree.end());
    }

    SECTION("should iterate from begin to end") {
        REQUIRE(*iterator == 5);
        REQUIRE(*(++iterator) == 10);
        REQUIRE(*(++iterator) == 12);
        REQUIRE(*(++iterator) == 13);
        REQUIRE(*(++iterator) == 15);
        REQUIRE(*(++iterator) == 30);
        REQUIRE(*(++iterator) == 40);
        REQUIRE(*(++iterator) == 50);
        REQUIRE(*(++iterator) == 60);

        REQUIRE_THROWS(*(++iterator) = 5);

        REQUIRE(iterator == tree.end());
    }

    SECTION("should iterate back and forth") {
        REQUIRE(*iterator == 5);
        REQUIRE(*(++iterator) == 10);
        REQUIRE(*(++iterator) == 12);
        REQUIRE(*(++iterator) == 13);
        REQUIRE(*(++iterator) == 15);
        REQUIRE(*(++iterator) == 30);
        REQUIRE(*(++iterator) == 40);
        REQUIRE(*(++iterator) == 50);

        REQUIRE(*(++iterator) == 60);

        REQUIRE(*(--iterator) == 50);
        REQUIRE(*(--iterator) == 40);
        REQUIRE(*(--iterator) == 30);
        REQUIRE(*(--iterator) == 15);
        REQUIRE(*(--iterator) == 13);
        REQUIRE(*(--iterator) == 12);
        REQUIRE(*(--iterator) == 10);
        REQUIRE(*(--iterator) == 5);
    }
}

TEST_CASE("reverse iterator") {
    auto tree = bst<int, int>();

    tree.insert(30, 30);

    tree.insert(10, 10);
    tree.insert(50, 50);

    tree.insert(5, 5);
    tree.insert(15, 15);
    tree.insert(12, 12);
    tree.insert(13, 13);

    tree.insert(40, 40);
    tree.insert(60, 60);

    auto iterator = tree.rbegin();

    SECTION("should equals to rend if rbegin--") {
        REQUIRE(--iterator == tree.rend());
    }

    SECTION("should iterate from rbegin to rend") {
        REQUIRE(*iterator == 60);
        REQUIRE(*(++iterator) == 50);
        REQUIRE(*(++iterator) == 40);
        REQUIRE(*(++iterator) == 30);
        REQUIRE(*(++iterator) == 15);
        REQUIRE(*(++iterator) == 13);
        REQUIRE(*(++iterator) == 12);
        REQUIRE(*(++iterator) == 10);
        REQUIRE(*(++iterator) == 5);

        REQUIRE_THROWS(*(++iterator) = 60);

        REQUIRE(iterator == tree.rend());
    }

    SECTION("should iterate back and forth") {
        REQUIRE(*iterator == 60);
        REQUIRE(*(++iterator) == 50);
        REQUIRE(*(++iterator) == 40);
        REQUIRE(*(++iterator) == 30);
        REQUIRE(*(++iterator) == 15);
        REQUIRE(*(++iterator) == 13);
        REQUIRE(*(++iterator) == 12);
        REQUIRE(*(++iterator) == 10);

        REQUIRE(*(++iterator) == 5);

        REQUIRE(*(--iterator) == 10);
        REQUIRE(*(--iterator) == 12);
        REQUIRE(*(--iterator) == 13);
        REQUIRE(*(--iterator) == 15);
        REQUIRE(*(--iterator) == 30);
        REQUIRE(*(--iterator) == 40);
        REQUIRE(*(--iterator) == 50);
        REQUIRE(*(--iterator) == 60);
    }
}