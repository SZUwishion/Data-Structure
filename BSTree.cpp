#include <iostream>
using namespace std;

struct BSTree {
  int data;
  BSTree *left;
  BSTree *right;
};

bool Search(BSTree *T, int key, BSTree *pre, BSTree **p) {
  if (!T) {
    *p = pre;
    return false;
  } else if (key == T->data) {
    *p = T;
    return true;
  } else if (key < T->data)
    return Search(T->left, key, T, p);
  else
    return Search(T->right, key, T, p);
}

bool Insert(BSTree **T, int e) {
  BSTree *p = new BSTree();
  if (!Search(*T, e, NULL, &p)) {
    BSTree *s = new BSTree();
    s->data = e;
    s->left = s->right = NULL;
    if (!p)
      *T = s;
    else if (e < p->data)
      p->left = s;
    else
      p->right = s;
    return true;
  }
  return false;
}

bool Delete(BSTree **T) {
  BSTree *p, *s;
  if (!(*T)->left && !(*T)->right)
    *T = NULL;
  else if (!(*T)->left) {
    p = *T;
    *T = (*T)->right;
    delete (p);
  } else if (!(*T)->right) {
    p = *T;
    *T = (*T)->left;
    delete (p);
  } else {
    p = *T;
    s = p->left;
    while (s->right) {
      p = s;
      s = s->right;
    }
    (*T)->data = s->data;
    if (p != *T)
      p->right = s->left;
    else
      p->left = s->left;
    delete (s);
  }
  return true;
}

bool DeleteBST(BSTree **T, int key) {
  if (!T)
    return true;
  else {
    if (key == (*T)->data) {
      Delete(&*T);
      return false;
    } else if (key < (*T)->data)
      return DeleteBST(&(*T)->left, key);
    else
      return DeleteBST(&(*T)->right, key);
  }
}

void MidOrder(BSTree *T) {
  if (T == NULL)
    return;
  MidOrder(T->left);
  cout << T->data << " ";
  MidOrder(T->right);
}

int main() {
  int a[] = {21, 43, 11, 54, 30, 49, 8}; // test data
  BSTree *T = new BSTree();
  T = NULL;
  for (int i = 0; i < 7; i++)
    Insert(&T, a[i]);
  MidOrder(T);
  cout << endl;
  DeleteBST(&T, 54);
  MidOrder(T);
}
