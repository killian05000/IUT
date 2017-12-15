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
