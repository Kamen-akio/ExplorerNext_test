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
  ~MutliTree();

  void SetChild(void*, void*);
  void DeleteNode(void*);
  std::vector<void*> GetChildren(void*);

 private:
  Node* ROOT_NODE = nullptr;
};

#endif  // !_UTILS_MUTLITREE_H_
