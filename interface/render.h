#pragma once
#include "../common.h"
#include "../core/gdiplus_ext/doubleBuffer.h"

#include <vector>
#define _TEMPLATE_RENDER_H_

#ifndef _TEMPLATE_RENDER_H_
#define _TEMPLATE_RENDER_H_

/*
 *
 * e.g.
 * [Root] - - - - - - - - - - - - - - -
 *   |          |          |          |
 *   | child    |          |          |
 *   | node     |          |          |
 * [Node] - - [Node] - - [Node] - - [Node] ...
 *     last node  last node  last node
 *   .                               .
 *   .                                .
 *   .                                 .
 */

namespace Layout {

typedef struct __tagNode {
  RenderBase* data;
  Node* lastNode, childNode;
} Node;

std::vector<Node> NodeTree{};

class RenderBase {
 public:
  RenderBase(HWND hWnd, Gdiplus::DoubleBuffer* db) {
    _hWnd = hWnd;
    renderContext = db;
    NodeTree.push_back(Node({__NODE_ROOT_, nullptr, new Node({this, nullptr, nullptr})}));
  }

  virtual void Layout(Gdiplus::Graphics&){};

 private:
  HWND _hWnd{};
  SIZE _szWnd{};
  POINT _posWnd{};

  Gdiplus::DoubleBuffer* renderContext;
};

}  // namespace Layout

#endif  // !_TEMPLATE_RENDER_H_
