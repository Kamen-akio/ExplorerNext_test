#pragma once
#include <vector>

#ifndef _UTILS_MUTLITREE_H_
#define _UTILS_MUTLITREE_H_

#define __NODE_ROOT_ nullptr

struct Node {
  void* data;
  Node *childNode, *nextNode;
};

class MutliTree {
 public:
  MutliTree();
  MutliTree(Node* root);
  ~MutliTree();

  void SetChild(void*, void*);
  void DeleteNode(void*);
  std::vector<void*> GetChildren(void*);
  Node* GetRoot() const { return ROOT_NODE; };

 private:
  Node* ROOT_NODE = nullptr;
};

#endif  // !_UTILS_MUTLITREE_H_
