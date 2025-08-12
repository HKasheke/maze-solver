#ifndef STACK_H
#define STACK_H

enum Direction {
    N,
    E,
    S,
    W,
    OBSTACLE
};

struct Data {
    int _x_value {0};
    int _y_value {0};
    int _possible_directions[4]= {OBSTACLE, OBSTACLE, OBSTACLE, OBSTACLE};
};

class Stack {
    struct Node {
        Data _data;
        Node* _next {nullptr};
        explicit Node(const Data& data) : _data(data) {}
    };

    Node* _top {nullptr};

public:
    ~Stack();
    void push(const Data& data);
    [[nodiscard]] Data* top() const;
    void pop();
};

#endif //STACK_H