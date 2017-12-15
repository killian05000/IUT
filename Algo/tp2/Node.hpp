#include <iostream>
using namespace std;

class Node
{
  private:
    Node* parent;
    Node* left;
    Node* right;
    size_t value=0;


  public:
    Node(Node* _parent, size_t _value);
    Node(Node* _parent, Node* _left, Node* _right, size_t _value);

    const size_t getValue();
    void setValue(size_t _value);

    const bool isRoot();
    const bool isIntern();
    const bool isExtern();
    const bool isEmpty();

    const Node* getParent();
    const Node* getLeft();
    const Node* getRight();
};
