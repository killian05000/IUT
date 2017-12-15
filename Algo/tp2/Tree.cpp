#include "Tree.hpp"

Tree::Tree()
{
  root=nullptr;
}

Tree::~Tree()
{
  delete root;
}

const void Tree::display(Node* node)
{
  if(node)
  {
    display(node->getLeft());
    cout << "Value : " << node->getValue() << " / ";
    display(node->getRight());
  }
}

const Node* Tree::findValue(size_t _value)
{
  Node* n= root;
  while (n != nullptr and n->getValue()!=_value)
  {
    if (n->getValue() <= _value)
      n = n->getLeft();
    else if (n->getValue() > _value)
      n = n->getRight();
  }
  return n;
}

Node* Node::insert(Node* node, size_t _value)
{
  Node* n = node;
}
