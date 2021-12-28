#include <time.h>
#include <math.h>
#include <iostream>
#include <rbst.hpp>
#include <bst.hpp>

typedef unsigned long long INT_64;

static INT_64 RRand = 15750;

const INT_64 mRand = (1 << 63) - 1;

const INT_64 aRand = 6364136223846793005;

const INT_64 cRand = 1442695040888963407;

void sRand() {
    srand(time(0));

    RRand = (INT_64)rand();
}

INT_64 LineRand() {
    INT_64 y1, y2;
    y1 = (aRand * RRand + cRand) % mRand;
    y2 = (aRand * y1 + cRand) % mRand;

    RRand = y1 & 0xffffffffffffffff ^ (y2 & 0xffffffffffffffff) >> 32;

    return RRand;
}

void test_rand(int n) {
    rbst<INT_64, int> tree_1;
    bst<INT_64, int> tree_2;
    INT_64* m = new INT_64[n];

    sRand();

    for (int i = 0; i < n; i++) {
        auto res = LineRand();

        m[i] = res;
        tree_1.insert(m[i], 1);
        tree_2.insert(m[i], 1);
    }

    std::cout << "RBST: Before test items count:" << tree_1.size() << std::endl;
    std::cout << "BST: Before test items count:" << tree_2.size() << std::endl;

    double I = 0;
    double D = 0;
    double S = 0;

    double I0 = 0;
    double D0 = 0;
    double S0 = 0;

    for (int i = 0; i < n / 2; i++)
        if (i % 10 == 0) {
            tree_1.remove(LineRand());
            D += tree_1.operations_amount();

            tree_2.remove(LineRand());
            D0 += tree_2.operations_amount();

            tree_1.insert(m[rand() % n], 1);
            I += tree_1.operations_amount();

            tree_2.insert(m[rand() % n], 1);
            I0 += tree_2.operations_amount();

            try {
                tree_1[LineRand()];
                S += tree_1.operations_amount();

                tree_2[LineRand()];
                S0 += tree_2.operations_amount();
            }
            catch (std::exception& e) {
                S += tree_1.operations_amount();
                S0 += tree_2.operations_amount();
            }
        }
        else {
            int ind = rand() % n;

            tree_1.remove(m[ind]);
            D += tree_1.operations_amount();

            tree_2.remove(m[ind]);
            D0 += tree_2.operations_amount();

            INT_64 key = LineRand();

            tree_1.insert(key, 1);
            I += tree_1.operations_amount();

            tree_2.insert(key, 1);
            I0 += tree_2.operations_amount();

            m[ind] = key;
            try {
                tree_1[m[rand() % n]];
                S += tree_1.operations_amount();

                tree_2[m[rand() % n]];
                S0 += tree_2.operations_amount();
            }
            catch (std::exception& e) {
                S += tree_1.operations_amount();
                S0 += tree_2.operations_amount();
            }
        }

    std::cout << "RBST: After test items count:" << tree_1.size()
              << std::endl;        //вывод размера дерева после теста
    std::cout << "BST: After test items count:" << tree_2.size() << std::endl;        //вывод размера дерева после теста

    std::cout << "1.39*log2(n)=" << 1.39 * (log((double)n) / log(2.0))
              << std::endl; //теоретической оценки трудоёмкости операций BST

    std::cout << "RBST: Count delete: " << D / (n / 2) << std::endl; //экспериментальной оценки трудоёмкости удаления

    std::cout << "RBST: Count insert: " << I / (n / 2) << std::endl; //экспериментальной оценки трудоёмкости вставки

    std::cout << "RBST: Count search: " << S / (n / 2) << std::endl; //экспериментальной оценки трудоёмкости поиска

    std::cout << "BST: Count delete: " << D0 / (n / 2) << std::endl; //экспериментальной оценки трудоёмкости удаления

    std::cout << "BST: Count insert: " << I0 / (n / 2) << std::endl; //экспериментальной оценки трудоёмкости вставки

    std::cout << "BST: Count search: " << S0 / (n / 2) << std::endl; //экспериментальной оценки трудоёмкости поиска

    delete[] m;
}

void test_ord(int n) {
    rbst<INT_64, int> tree_1;
    bst<INT_64, int> tree_2;

    INT_64* m = new INT_64[n];

    for (int i = 0; i < n; i++) {
        m[i] = i * 10000;
        tree_1.insert(m[i], 1);
        tree_2.insert(m[i], 1);
    }

    std::cout << "items count rbst:" << tree_1.size() << std::endl;
    std::cout << "items count bst:" << tree_2.size() << std::endl;

    double I = 0;
    double D = 0;
    double S = 0;

    double I0 = 0;
    double D0 = 0;
    double S0 = 0;

    sRand();

    for (int i = 0; i < n / 2; i++) {
        if (i % 10 == 0) {
            int k = LineRand() % (10000 * n);
            k = k + !(k % 2);

            tree_1.remove(k);
            D += tree_1.operations_amount();

            tree_2.remove(k);
            D0 += tree_2.operations_amount();

            tree_1.insert(m[rand() % n], 1);
            I += tree_1.operations_amount();

            tree_2.insert(m[rand() % n], 1);
            I0 += tree_2.operations_amount();

            k = LineRand() % (10000 * n);
            k = k + !(k % 2);

            try {
                tree_1[k];
                S += tree_1.operations_amount();

                tree_2[k];
                S0 += tree_2.operations_amount();
            }
            catch (std::exception& e) {
                S += tree_1.operations_amount();
                S0 += tree_2.operations_amount();
            }
        }
        else {
            int ind = rand() % n;

            tree_1.remove(m[ind]);
            D += tree_1.operations_amount();

            tree_2.remove(m[ind]);
            D0 += tree_2.operations_amount();

            int k = LineRand() % (10000 * n);
            k = k + k % 2;

            tree_1.insert(k, 1);
            I += tree_1.operations_amount();

            tree_2.insert(k, 1);
            I0 += tree_1.operations_amount();

            m[ind] = k;

            try {
                tree_1[m[rand() % n]];
                S += tree_1.operations_amount();

                tree_2[m[rand() % n]];
                S0 += tree_2.operations_amount();
            }
            catch (std::exception& e) {
                S += tree_1.operations_amount();
                S0 += tree_2.operations_amount();
            }
        }
    }

    std::cout << "rbst items count:" << tree_1.size() << std::endl;// вывод размера дерева после теста
    std::cout << "rbst items count:" << tree_2.size() << std::endl;// вывод размера дерева после теста

    std::cout << "1.39*log2(n)=" << 1.39 * (log((double)n) / log(2.0))
              << std::endl; //теоретической оценки трудоёмкости операций BST

    std::cout << "RBST Count delete: " << D / (n / 2) << std::endl;//экспериментальной оценки трудоёмкости удаления

    std::cout << "RBST Count insert: " << I / (n / 2) << std::endl;//экспериментальной оценки трудоёмкости вставки

    std::cout << "RBST Count search: " << S / (n / 2) << std::endl;//экспериментальной оценки трудоёмкости поиска

    std::cout << "BST Count delete: " << D0 / (n / 2) << std::endl;//экспериментальной оценки трудоёмкости удаления

    std::cout << "BST Count insert: " << I0 / (n / 2) << std::endl;//экспериментальной оценки трудоёмкости вставки

    std::cout << "BST Count search: " << S0 / (n / 2) << std::endl;//экспериментальной оценки трудоёмкости поиска

    delete[] m;
}

int main() {
    std::cout << "Test Rand" << std::endl << std::endl;

    test_rand(3000);

    std::cout << std::endl;

    std::cout << "Test Ord" << std::endl << std::endl;

    test_ord(3000);

    std::cout << std::endl;
}