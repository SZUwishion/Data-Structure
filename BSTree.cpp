#include <iostream>
using namespace std;

struct BSTree
{
  int data;
  BSTree *left;
  BSTree *right;
};

bool Search(BSTree *Node, int key, BSTree *pre, BSTree **temp)
{
  if (!Node) {
    *temp = pre;
    return false;
  } else if (key == Node->data) {
    *temp = Node;
    return true;
  } else if (key < Node->data){
    return Search(Node->left, key, Node, temp);
  } else {
    return Search(Node->right, key, Node, temp);
  }
}

bool Insert(BSTree **Node, int element)
{
  BSTree *temp = new BSTree();
  if (!Search(*Node, element, NULL, &temp)) {
    BSTree *newtemp = new BSTree();
    newtemp->data = element;
    newtemp->left = newtemp->right = NULL;
    if (!temp) {
      *Node = newtemp;
    } else if (element < temp->data) {
      temp->left = newtemp;
    } else {
      temp->right = newtemp;
    }
    return true;
  }
  return false;
}

bool Delete(BSTree **Node)
{
  BSTree *temp1, *temp2;
  if (!(*Node)->left && !(*Node)->right){
    *Node = NULL;
  } else if (!(*Node)->left) {
    temp1 = *Node;
    *Node = (*Node)->right;
    delete (temp1);
  } else if (!(*Node)->right) {
    temp1 = *Node;
    *Node = (*Node)->left;
    delete (temp1);
  } else {
    temp1 = *Node;
    temp2 = temp1->left;
    while (temp2->right) {
      temp1 = temp2;
      temp2 = temp2->right;
    }
    (*Node)->data = temp2->data;
    if (temp1 != *Node) {
      temp1->right = temp2->left;
    } else {
      temp1->left = temp2->left;
    }
    delete (temp2);
  }
  return true;
}

bool DeleteBST(BSTree **Node, int key)
{
  if (!Node) {
    return true;
  } else {
    if (key == (*Node)->data) {
      Delete(&*Node);
      return false;
    } else if (key < (*Node)->data) {
      return DeleteBST(&(*Node)->left, key);
    } else {
      return DeleteBST(&(*Node)->right, key);
    }
  }
}

void MidOrder(BSTree *Node) {
  if (Node == NULL) {
    return;
  }
  MidOrder(Node->left);
  cout << Node->data << " ";
  MidOrder(Node->right);
}

int main() {
  int a[] = {21, 43, 11, 54, 30, 49, 8}; // test data
  BSTree *Tree = new BSTree();
  Tree = NULL;
  for (int i = 0; i < 7; i++) {
    Insert(&Tree, a[i]);
  }
  MidOrder(Tree);
  cout << endl;
  DeleteBST(&Tree, 54);
  MidOrder(Tree);
}
