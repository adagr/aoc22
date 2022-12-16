#include "day.hpp"

enum class Result {
    None,
    Success,
    Fail
};

struct Node;
Result compareNext(std::deque<Node*> leftQ, std::deque<Node*> rightQ);

struct Node {
    Node* parent;
    int number = -1;
    std::deque<Node*> nodes;
    bool operator<(const Node& n) const {
        return compareNext(nodes, n.nodes) != Result::Fail;
    }
    bool operator==(const Node& n) const {
        bool success{true};
        success &= number == number;
        success &= nodes.size() == n.nodes.size();
        if (success)
            for (int i{}; i < nodes.size(); ++i)
                success &= nodes[i] == n.nodes[i];

        return success;
    }
};

Result compare(Node* left, Node* right, std::deque<Node*> leftQ, std::deque<Node*> rightQ) {
    if (left->number != -1 && right->number == -1) {
        if (right->nodes.empty())
            return Result::Fail;

        return compare(left, right->nodes.front(), {}, {right->nodes.begin() + 1, right->nodes.end()});
    }

    if (left->number == -1 && right->number != -1) {
        if (left->nodes.empty())
            return Result::Success;

        return compare(left->nodes.front(), right, {left->nodes.begin() + 1, left->nodes.end()}, {});
    }

    if (left->number == -1 && right->number == -1) {
        auto res = compareNext(left->nodes, right->nodes);
        if (res == Result::None)
            return compareNext(leftQ, rightQ);

        return res;
    }

    if (left->number != -1 && right->number != -1) {
        if (left->number < right->number)
            return Result::Success;

        if (left->number > right->number)
            return Result::Fail;

        return compareNext(leftQ, rightQ);
    }

    return Result::None;
}

Result compareNext(std::deque<Node*> leftQ, std::deque<Node*> rightQ) {
    if (leftQ.empty() && !rightQ.empty())
        return Result::Success;

    if (!leftQ.empty() && rightQ.empty())
        return Result::Fail;

    if (!leftQ.empty() && !rightQ.empty())
        return compare(*leftQ.begin(), *rightQ.begin(), {leftQ.begin() + 1, leftQ.end()}, {rightQ.begin() + 1, rightQ.end()});

    return Result::None;
}

class Day13 : public Day {

public:
    Day13() : Day{"input/day13.txt"} {}
    ~Day13() override = default;
    
    void run() override {
        // Part 1
        int correctOrder{};
        std::set<Node> nodes;
        Node* left;
        Node* right;
        for (int i{}; i < lines.size(); i += 3) {
            left = getNumberFromLine(i);
            right = getNumberFromLine(i+1);
            nodes.insert(*left);
            nodes.insert(*right);
            if (compareNext(left->nodes, right->nodes) != Result::Fail)
                correctOrder += i / 3 + 1;
        }

        correctOrder -= 151; // removes part2 stuff
        std::cout << correctOrder << std::endl;

        // Part 2
        int value{1};
        int index{};
        for (const auto& n : nodes) {
            ++index;
            if (n  == *left || n == *right)
                value *= index;
        }

        std::cout << value;
    }

    Node* getNumberFromLine(int line) const {
        Node* root = new Node{};
        Node* currentNode{root};
        auto l = lines[line].substr(1, lines[line].size() - 2);
        for (auto it = l.begin(); it != l.end(); ++it) {
            auto c = *it;
            if (c == '[') {
                Node* child = new Node{};
                child->parent = currentNode;
                currentNode->nodes.push_back(child);
                currentNode = child;
            } else if (c == ']') {
                currentNode = currentNode->parent;
            } else if (c == ',') {
                continue;
            } else {
                Node* child = new Node{};
                if (*(it+1) == '0') {
                    child->number = 10;
                    ++it;
                } else
                    child->number = std::stoi(std::string{c});

                child->parent = currentNode;
                currentNode->nodes.push_back(child);
            }
        }

        return root;
    }
};