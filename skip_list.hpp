#ifndef SKIP_LIST_HPP
#define SKIP_LIST_HPP

#include <vector>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <random>

template<typename T>
class SkipList {
private:
    struct Node {
        T value;
        std::vector<Node*> next;
        Node(int level, const T& val): value(val), next(level, nullptr) {}
    };

    static constexpr int MAX_LEVEL = 32;
    double p;
    int level;
    Node* head;
    std::mt19937_64 rng;
    std::uniform_real_distribution<double> dist;

    int randomLevel() {
        int lvl = 1;
        while (lvl < MAX_LEVEL && dist(rng) < p) ++lvl;
        return lvl;
    }

public:
    SkipList(): p(0.5), level(1), head(new Node(MAX_LEVEL, T())), rng(std::random_device{}()), dist(0.0, 1.0) {}

    ~SkipList() {
        Node* cur = head->next[0];
        while (cur) {
            Node* nxt = cur->next[0];
            delete cur;
            cur = nxt;
        }
        delete head;
    }

    void insert(const T & item) {
        std::vector<Node*> update(MAX_LEVEL, nullptr);
        Node* cur = head;
        for (int i = level - 1; i >= 0; --i) {
            while (cur->next[i] && cur->next[i]->value < item) cur = cur->next[i];
            update[i] = cur;
        }

        cur = cur->next[0];
        if (cur && !(item < cur->value) && !(cur->value < item)) return; // already exists

        int rl = randomLevel();
        if (rl > level) {
            for (int i = level; i < rl; ++i) update[i] = head;
            level = rl;
        }
        Node* node = new Node(rl, item);
        for (int i = 0; i < rl; ++i) {
            node->next[i] = update[i]->next[i];
            update[i]->next[i] = node;
        }
    }

    bool search(const T & item) {
        Node* cur = head;
        for (int i = level - 1; i >= 0; --i) {
            while (cur->next[i] && cur->next[i]->value < item) cur = cur->next[i];
        }
        cur = cur->next[0];
        return cur && !(item < cur->value) && !(cur->value < item);
    }

    void deleteItem(const T & item) {
        std::vector<Node*> update(MAX_LEVEL, nullptr);
        Node* cur = head;
        for (int i = level - 1; i >= 0; --i) {
            while (cur->next[i] && cur->next[i]->value < item) cur = cur->next[i];
            update[i] = cur;
        }
        cur = cur->next[0];
        if (!cur || (item < cur->value) || (cur->value < item)) return;
        int nodeLevel = (int)cur->next.size();
        for (int i = 0; i < nodeLevel; ++i) {
            if (update[i]->next[i] == cur) update[i]->next[i] = cur->next[i];
        }
        delete cur;
        while (level > 1 && head->next[level - 1] == nullptr) --level;
    }
};

#endif

