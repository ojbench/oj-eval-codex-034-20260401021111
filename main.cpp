#include <bits/stdc++.h>
#include "skip_list.hpp"

static bool is_integer(const std::string &s, long long &out) {
    if (s.empty()) return false;
    char *end = nullptr;
    errno = 0;
    long long val = strtoll(s.c_str(), &end, 10);
    if (errno != 0 || end == s.c_str() || *end != '\0') return false;
    out = val;
    return true;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    SkipList<long long> sl;

    // Read all tokens to flexibly handle both formats with/without leading count
    std::vector<std::string> tokens;
    tokens.reserve(1 << 20);
    std::string tok;
    while (std::cin >> tok) tokens.push_back(tok);
    size_t idx = 0;

    if (!tokens.empty()) {
        long long n;
        if (is_integer(tokens[0], n) && n >= 0 && tokens.size() == static_cast<size_t>(1 + 2 * n)) {
            idx = 1; // treat first as count
        }
    }

    auto to_op = [](const std::string &s) -> int {
        long long v;
        if (is_integer(s, v)) return static_cast<int>(v);
        std::string t;
        t.resize(s.size());
        std::transform(s.begin(), s.end(), t.begin(), [](unsigned char c){ return std::tolower(c); });
        if (t == "i" || t == "ins" || t == "insert" || t == "add") return 1;
        if (t == "d" || t == "del" || t == "delete" || t == "erase" || t == "remove") return 2;
        if (t == "s" || t == "search" || t == "find" || t == "query") return 3;
        return -1;
    };

    while (idx + 1 < tokens.size()) {
        int op = to_op(tokens[idx]);
        long long x;
        if (!is_integer(tokens[idx + 1], x)) {
            idx += 1; // try to resync if malformed
            continue;
        }
        idx += 2;
        if (op == 1) {
            sl.insert(x);
        } else if (op == 2) {
            sl.deleteItem(x);
        } else if (op == 3) {
            std::cout << (sl.search(x) ? 1 : 0) << '\n';
        } else {
            // unknown op: ignore
        }
    }
    return 0;
}
