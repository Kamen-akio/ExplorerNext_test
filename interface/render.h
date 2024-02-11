#pragma once

/* 注解
 * _Handler   传递有关鼠标坐标的都是相对与窗口左上角
 * LayoutUnit 中 _szUnit & _posUnit 坐标都是相对于窗口左上角，（相对于父类组件太碍事 :( ）
 */

#include "../common.h"
#include "../core/gdiplus_ext/doubleBuffer.h"
#include "../utils/mutliTree.h"

#include <vector>

using namespace Gdiplus;

#ifndef _TEMPLATE_RENDER_H_
#define _TEMPLATE_RENDER_H_

#define WM_UNIT_DESTROYED WM_USER + 0x1
#define WM_UNIT_PARENTCHANGED WM_USER + 0x2
#define WM_UNIT_ZINDEXCHANGED WM_USER + 0x3

#define RENDER_LAYOUT (int)0x01

class LayoutUtil abstract {
 public:
  LayoutUtil(Node* root) { _nodeTree = root; };
  ~LayoutUtil(){};

  void SetChild(LayoutUtil* child) {
    _nodeTree.SetChild(this, child);
    ((LayoutUnit*)(void*)child)->OnParentChanged();
  };
  void SetParent(LayoutUtil* parent) {
    _nodeTree.SetChild(parent, this);
    ((LayoutUnit*)(void*)this)->OnParentChanged();
  };
  void _Destroy(LayoutUtil* self) { _nodeTree.DeleteNode(self); };

 private:
  MutliTree _nodeTree{};
};

class LayoutUnit : LayoutUtil {
 public:
  LayoutUnit(Graphics* Layout, DoubleBuffer* Context, Node* Root)
      : LayoutUtil(Root) {
    _ROOT_NODE_ = Root;

    LayoutGraphics = Layout;
    LayoutContext = Context;

    OnCreate();
  };

  ~LayoutUnit() {
    OnDestroy();

    LayoutGraphics = nullptr;
    LayoutContext = nullptr;
    _Destroy(this);
  };

  virtual void OnCreate(){};
  virtual void OnDestroy(){};
  virtual void Render(){};
  virtual void OnWndSize(SIZE szNewWnd){};
  virtual void OnParentChanged(){};  // 感觉没啥用

  const int _Handler(LayoutUnit* parent,
                     UINT uMsg,
                     WPARAM wData,
                     LPARAM lData) {
    if (uMsg == WM_SIZE or uMsg == WM_MOVE) {
      if (uMsg == WM_SIZE) {
        OnWndSize(_szWnd = {LOWORD(lData), HIWORD(lData)});
        return NULL;
      }

      _posWnd = {GET_X_LPARAM(lData), GET_Y_LPARAM(lData)};
      return NULL;
    }

    if (uMsg == WM_UNIT_DESTROYED) {
      // 没用，因为在获得此消息前已经被销毁了。
      return NULL;
    }

    if (uMsg == WM_UNIT_PARENTCHANGED) {
      ParentLayout = parent;
      OnParentChanged();
      return NULL;
    }

    if (uMsg == WM_LBUTTONDOWN) {
      // TODO
    }
  }

 public:
  Graphics* LayoutGraphics{};

 private:
  SIZE _szUnit{};
  POINT _posUnit{};

  Node* _ROOT_NODE_{};
  SIZE _szWnd{};
  POINT _posWnd{};
  LayoutUnit* ParentLayout{};
  DoubleBuffer* LayoutContext{};
};

#endif  // !_TEMPLATE_RENDER_H_

// nothing

class test : public LayoutUnit {
 public:
  test(Graphics* Layout) : LayoutUnit(Layout, nullptr, nullptr){};
};

Graphics b;
test a(&b);