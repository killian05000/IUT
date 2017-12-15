#include "Node.hpp"

Node::Node(Node* _parent, size_t _value)
{
  parent = _parent;
  left = nullptr;
  right = nullptr;
  value = _value;
}

Node::Node(Node* _parent, Node* _left, Node* _right, size_t _value)
{
  parent = _parent;
  left = _left;
  right = _right;
  value = _value;
}

const size_t Node::getValue()
{
  return value;
}

void Node::setValue(size_t _value)
{
  value = _value;
}

const bool Node::isRoot()
{
  return(parent==nullptr);
}

const bool Node::isIntern()
{
  return((left != nullptr) || (right != nullptr));
}

const bool Node::isExtern()
{
  return((left == nullptr) && (right == nullptr));
}

const bool Node::isEmpty()
{
  return(value==0); // Change the default value
}
