#include <algorithm>
#include <iostream>
using namespace std;

struct AVLNode {
  int data;
  int height;
  AVLNode *left;
  AVLNode *right;
  AVLNode *parent;
};

void MidOrder(AVLNode *root) {
  if (root->left != NULL)
    MidOrder(root->left);
  cout << root->data << " ";
  if (root->right != NULL)
    MidOrder(root->right);
}

int calHeight(AVLNode *root) {
  int LeftHeight = 0, RightHeight = 0;
  if (root->left != NULL)
    LeftHeight = calHeight(root->left);
  if (root->right != NULL)
    RightHeight = calHeight(root->right);
  return max(LeftHeight, RightHeight) + 1;
}

int calBalance(AVLNode *root) {
  if (root == NULL)
    return 0;
  else if (root->left == NULL && root->right == NULL)
    return 0;
  else if (root->left == NULL)
    return -root->right->height;
  else if (root->right == NULL)
    return root->left->height;
  else
    return root->left->height - root->right->height;
}

AVLNode *LeftRotate(AVLNode *root) {
  AVLNode *oldroot = root;
  AVLNode *newroot = root->right;
  AVLNode *parent = root->parent;
  if (parent != NULL) {
    if (oldroot->parent->data > oldroot->data)
      parent->left = newroot;
    else
      parent->right = newroot;
  }
  newroot->parent = parent;
  oldroot->right = newroot->left;
  if (newroot->left != NULL)
    newroot->left->parent = oldroot;
  newroot->left = oldroot;
  oldroot->parent = newroot;
  oldroot->height = calHeight(oldroot);
  newroot->height = calHeight(newroot);
  return newroot;
}

AVLNode *RightRotate(AVLNode *root) {
  AVLNode *oldroot = root;
  AVLNode *newroot = root->left;
  AVLNode *parent = root->parent;
  if (parent != NULL) {
    if (oldroot->parent->data > oldroot->data)
      parent->left = newroot;
    else
      parent->right = newroot;
  }
  newroot->parent = parent;
  oldroot->right = newroot->left;
  if (newroot->left != NULL)
    newroot->left->parent = oldroot;
  oldroot->parent = newroot;
  newroot->left = oldroot;
  oldroot->height = calHeight(oldroot);
  newroot->height = calHeight(newroot);
  return newroot;
}

AVLNode *Insert(AVLNode *root, int data) {
  if (root == NULL) {
    root = new AVLNode;
    root->data = data;
    root->height = 1;
    root->left = NULL;
    root->right = NULL;
    root->parent = NULL;
    return root;
  } else if (data < root->data) {
    if (root->left == NULL) {
      root->left = new AVLNode;
      root->left->data = data;
      root->left->parent = root;
      root->left->left = NULL;
      root->left->right = NULL;
      root->left->height = 1;
    } else
      root->left = Insert(root->left, data);
  } else if (data > root->data) {
    if (root->right == NULL) {
      root->right = new AVLNode;
      root->right->data = data;
      root->right->parent = root;
      root->right->left = NULL;
      root->right->right = NULL;
      root->right->height = 1;
    } else
      root->right = Insert(root->right, data);
  }
  root->height = calHeight(root);
  if (calBalance(root) == 2) {
    if (calBalance(root) == -1)
      root = LeftRotate(root->left);
    root = RightRotate(root);
  }
  if (calBalance(root) == -2) {
    if (calBalance(root) == 1)
      root = RightRotate(root->right);
    root = LeftRotate(root);
  }
  return root;
}

AVLNode *Delete(AVLNode *root) {
  AVLNode *p, *s;
  if (!root->left && !root->right) {
    p = root;
    root = root->parent;
    if (root->left == p)
      root->left = NULL;
    else
      root->right = NULL;
  } else if (!root->left) {
    p = root;
    root = root->right;
    delete (p);
  } else if (!root->right) {
    p = root;
    root = root->left;
    delete (p);
  } else {
    p = root;
    s = p->left;
    while (s->right) {
      p = s;
      s = s->right;
    }
    root->data = s->data;
    if (p != root)
      p->right = s->left;
    else
      p->left = s->left;
    delete (s);
  }
  return root;
}

AVLNode *DeleteAVL(AVLNode *root, int key) {
  if (!root)
    return root;
  else {
    if (key == root->data) {
      root = Delete(root);
      root->height = calHeight(root);
      if (calBalance(root) == 2) {
        if (calBalance(root) == -1)
          root = LeftRotate(root->left);
        root = RightRotate(root);
      }
      if (calBalance(root) == -2) {
        if (calBalance(root) == 1)
          root = RightRotate(root->right);
        root = LeftRotate(root);
      }
      return root;
    } else if (key < root->data)
      return DeleteAVL(root->left, key);
    else
      return DeleteAVL(root->right, key);
  }
}

bool IsBalanceTree(AVLNode *root) {
  if (root == NULL || (root->left == NULL && root->right == NULL))
    return true;
  int leftHeight = 0;
  int rightHeight = 0;
  if (root->left == NULL && root->right != NULL) {
    leftHeight = 0;
    rightHeight = root->right->height;
  } else if (root->right == NULL && root->left != NULL) {
    leftHeight = root->left->height;
    rightHeight = 0;
  } else {
    leftHeight = root->left->height;
    rightHeight = root->right->height;
  }
  int diff = leftHeight - rightHeight;
  if ((diff) >= 2) {
    cout << root->data << "节点平衡因子异常" << endl;
    return false;
  }

  if (diff != calBalance(root)) {
    cout << root->data << "节点平衡因子不符合实际" << endl;
    return false;
  }

  // 判断左右子树
  return IsBalanceTree(root->left) && IsBalanceTree(root->right);
}

int main() {
  AVLNode *tree = new AVLNode();
  tree = NULL;
  for (int i = 1; i <= 9; i++) {
    int x;
    cin >> x;
    tree = Insert(tree, x);
  }
  MidOrder(tree);
  cout << endl;
  if (IsBalanceTree(tree))
    cout << "YES" << endl;
  else
    cout << "NO" << endl;
  DeleteAVL(tree, 10);
  MidOrder(tree);
  cout << endl;
  if (IsBalanceTree(tree))
    cout << "YES" << endl;
  else
    cout << "NO" << endl;
  return 0;
}
