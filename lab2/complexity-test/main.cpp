#include <time.h>
#include <math.h>
#include <iostream>
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

    RRand = y1 & 0xfffffffffffff000 ^ (y2 & 0xfffffffffffff000) >> 32;

    return RRand;
}

void test_rand(int n) {
    bst<INT_64, int> tree;
    INT_64* m = new INT_64[n];

    sRand();

    for (int i = 0; i < n; i++) {
        auto res = LineRand();

        m[i] = res;
        tree.insert(m[i], 1);
    }

    std::cout << "Before test items count:" << tree.size() << std::endl;

    double I = 0;
    double D = 0;
    double S = 0;

    for (int i = 0; i < n / 2; i++)
        if (i % 10 == 0) {
            tree.remove(LineRand());
            D += tree.operations_amount();

            tree.insert(m[rand() % n], 1);
            I += tree.operations_amount();

            try {
                tree[LineRand()];
                S += tree.operations_amount();
            }
            catch (std::exception& e) {
                S += tree.operations_amount();
            }
        }
        else {
            int ind = rand() % n;

            tree.remove(m[ind]);
            D += tree.operations_amount();

            INT_64 key = LineRand();

            tree.insert(key, 1);
            I += tree.operations_amount();

            m[ind] = key;
            try {
                tree[m[rand() % n]];
                S += tree.operations_amount();
            }
            catch (std::exception& e) {
                S += tree.operations_amount();
            }
        }

    std::cout << "After test items count:" << tree.size() << std::endl;        //вывод размера дерева после теста

    std::cout << "1.39*log2(n)=" << 1.39 * (log((double)n) / log(2.0))
              << std::endl; //теоретической оценки трудоёмкости операций BST

    std::cout << "Count insert: " << I / (n / 2) << std::endl; //экспериментальной оценки трудоёмкости вставки

    std::cout << "Count delete: " << D / (n / 2) << std::endl; //экспериментальной оценки трудоёмкости удаления

    std::cout << "Count search: " << S / (n / 2) << std::endl; //экспериментальной оценки трудоёмкости поиска

    delete[] m;
}

void test_ord(int n) {
    bst<INT_64, int> tree;

    INT_64* m = new INT_64[n];

    for (int i = 0; i < n; i++) {
        m[i] = i * 10000;
        tree.insert(m[i], 1);
    }

    std::cout << "items count:" << tree.size() << std::endl;

    double I = 0;
    double D = 0;
    double S = 0;

    sRand();

    for (int i = 0; i < n / 2; i++) {
        if (i % 10 == 0) {
            int k = LineRand() % (10000 * n);
            k = k + !(k % 2);

            tree.remove(k);
            D += tree.operations_amount();

            tree.insert(m[rand() % n], 1);
            I += tree.operations_amount();

            k = LineRand() % (10000 * n);
            k = k + !(k % 2);

            try {
                tree[k];
                S += tree.operations_amount();
            }
            catch (std::exception& e) {
                S += tree.operations_amount();
            }
        }
        else {
            int ind = rand() % n;

            tree.remove(m[ind]);
            D += tree.operations_amount();

            int k = LineRand() % (10000 * n);
            k = k + k % 2;

            tree.insert(k, 1);
            I += tree.operations_amount();

            m[ind] = k;

            try {
                tree[m[rand() % n]];
                S += tree.operations_amount();
            }
            catch (std::exception& e) {
                S += tree.operations_amount();
            }
        }
    }
    std::cout << "items count:" << tree.size() << std::endl;// вывод размера дерева после теста

    std::cout << "n/2 =" << n / 2 << std::endl;//теоретической оценки трудоёмкости операций BST

    std::cout << "Count insert: " << I / (n / 2) << std::endl;//экспериментальной оценки трудоёмкости вставки

    std::cout << "Count delete: " << D / (n / 2) << std::endl;//экспериментальной оценки трудоёмкости удаления

    std::cout << "Count search: " << S / (n / 2) << std::endl;//экспериментальной оценки трудоёмкости поиска

    delete[] m;
}

int main() {

    std::cout << "Test Rand" << std::endl << std::endl;
    test_rand(2000);

    std::cout << std::endl;

    std::cout << "Test Ord" << std::endl << std::endl;
    test_ord(2000);
    std::cout << std::endl;
}