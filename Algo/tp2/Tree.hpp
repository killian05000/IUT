#include <iostream>
#include "Node.hpp"
using namespace std;

class Tree
{
  private:
    Node* root;
  public:
    Tree();
    ~Tree();

    const void display(Node* node);
    const Node* findValue(size_t _value);

    Node* insert(Node* node, size_t _value);
};
