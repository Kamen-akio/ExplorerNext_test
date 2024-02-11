#include "mutliTree.h"

static void _Destroy(Node* currNode) {
  if (!currNode)
    return;

  Node *deleteNode = currNode->childNode, *newNode;

  while (deleteNode) {
    newNode = deleteNode->nextNode;
    _Destroy(deleteNode);
    deleteNode = newNode;
  }

  delete currNode;
  return;
}

static void _Delete(Node* currNode, void* target) {
  if (!currNode)
    return;

  if (currNode->data == target) {
    _Destroy(currNode);
    return;
  }

  if (currNode->childNode && currNode->childNode->data == target)
    currNode->childNode = currNode->childNode->nextNode;

  _Delete(currNode->nextNode, target);

  if (currNode->nextNode && currNode->nextNode->data == target)
    currNode->nextNode = currNode->nextNode->nextNode;

  _Delete(currNode->nextNode, target);
}

static void _Set(Node* currNode, void* parent, void* child) {
  if (currNode == nullptr)
    return;

  if (currNode->data == parent) {
    Node* newChild = new Node;
    newChild->data = child;
    newChild->childNode = newChild->nextNode = nullptr;

    if (currNode->childNode) {
      Node* nextChild = currNode->childNode;

      while (nextChild->nextNode) {
        nextChild = nextChild->nextNode;
      }

      nextChild->nextNode = newChild;

    } else {
      currNode->childNode = newChild;
    }
  } else {
    _Set(currNode->childNode, parent, child);
    _Set(currNode->nextNode, parent, child);
  }
}

static Node* _Find(Node* currNode, void* target) {
  if (!currNode) {
    return nullptr;
  }

  if (currNode->data == target) {
    return currNode;
  }

  auto ret = _Find(currNode->childNode, target);
  if (ret)
    return ret;

  return _Find(currNode->nextNode, target);
}


MutliTree::MutliTree() {
  Node* ROOT = new Node;
  ROOT->data = __NODE_ROOT_;
  ROOT->childNode = ROOT->nextNode = nullptr;

  ROOT_NODE = ROOT;
};

MutliTree::~MutliTree() {
  _Destroy(ROOT_NODE);
};

void MutliTree::SetChild(void* parent, void* child) {
  _Set(ROOT_NODE, parent, child);
}

std::vector<void*> MutliTree::GetChildren(void* parent) {
  std::vector<void*> vecChild{};
  auto parentNode = _Find(ROOT_NODE, parent);

  if (!parentNode->childNode)
    return vecChild;

  Node* childNode = parentNode->childNode;
  vecChild.push_back(childNode);

  while (childNode->nextNode) {
    childNode = childNode->nextNode;
    vecChild.push_back(childNode);
  }

  return vecChild;
}

void MutliTree::DeleteNode(void* target) {
  _Delete(ROOT_NODE, target);
};
