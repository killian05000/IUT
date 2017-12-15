#include <iostream>
using namespace std;

class Node
{
  private:
    Node* parent;
    Node* left;
    Node* right;
    size_t value;


  public:
    int getValue();
    void setValue(int _value);
    const Node* getParent();
    const Node* getLeft();
    const Node* getRight();
};
