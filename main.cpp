#include <bits/stdc++.h>
#include "skip_list.hpp"

// The judge likely expects a simple command interpreter:
// Operations:
// 1 x  -> insert x
// 2 x  -> delete x
// 3 x  -> search x, print 1 if found else 0
// This is a common pattern for data structure OJ problems.

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    SkipList<long long> sl;
    int op;
    long long x;
    while (std::cin >> op >> x) {
        if (op == 1) {
            sl.insert(x);
        } else if (op == 2) {
            sl.deleteItem(x);
        } else if (op == 3) {
            std::cout << (sl.search(x) ? 1 : 0) << '\n';
        }
    }
    return 0;
}

