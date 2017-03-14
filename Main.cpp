#include <iostream>
using namespace std;

template <typename S>
class Node{
  public:
        S key;
        Node<S> *left, *right, *parent;
        Node (S k) {
            key = k;
            left = nullptr;
            right = nullptr;
            parent = nullptr;
        }
};

template <typename T>
class BST{
private:
      Node<T> *root;

      void insertRecur(Node<T> *root, T r){
        if (root->key > r){
          if (root->left == nullptr){
            root->left = new Node<T>(r);
            root->left->parent = root;
          }
          else {
            insertRecur(root->left, r);
          }
        }
        else {
          if (root->right == nullptr){
            root->right = new Node<T>(r);
            root->right->parent = root;
          }
          else{
            insertRecur(root->right, r);
          }
        }
      }

      void printerHelper(Node<T> *p){
        if (p==nullptr) return;
          cout<<p->key<<endl;
          printerHelper(p->left);
          printerHelper(p->right);
      }

      Node<T> * finding(Node<T> *y, T k){
        if (y == nullptr) return nullptr;
        else if(k < y->key) return finding(y->left,k);
        else if(k > y->key) return finding(y->right,k);
        else {
          cout<<"number to be deleted is: ";
          cout<<y->key<<endl;
          return y;
        }
      }


      int deeper(Node<T> *root){
        if (root == nullptr) {
          return 0;
        }
        else {
          return 1 + max(deeper(root->left),deeper(root->right));
        }
      }

      void deleteTree(Node<T> *root){
        if (root->left == nullptr && root->right == nullptr){
          free(root);
        }
        else{
          deleteTree(root->left);
          deleteTree(root->right);
        }
      }

      Node<T> * findMinRightSubtree(Node<T> *q) {
        if (q->left == nullptr) {
          cout<<q->key<<endl;
          return q;
        }
        else{findMinRightSubtree(q->left);}
        }

      void replaceValue(Node<T> *first, Node<T> *replaced){
        first->key = replaced->key;
        if (replaced->parent->right == replaced) {
          replaced->parent->right = nullptr;
        }
        if (replaced->parent->left == replaced) {
          replaced->parent->left = nullptr;
        }
        delete(replaced);
      }

      void remover(Node<T> *x){
        if (x->right == nullptr && x->left == nullptr){
          if (x->parent->right == x) x->parent->right = nullptr;
          if (x->parent->left == x) x->parent->left = nullptr;
          delete(x);
        }

        if (x->right == nullptr ^ x->left == nullptr){
          if (x->right == nullptr) {
            x->left->parent = x->parent;
            x->parent->left = x->left;
          }
          if (x->left == nullptr) {
            x->right->parent = x->parent;
            x->parent->right = x->right;
          }
          delete(x);
        }
        if (x->right != nullptr && x->left != nullptr){
          Node<T> *temp = x;
          x = x->right;
          Node<T> *v = findMinRightSubtree(x);
          replaceValue(temp,v);
        }
      }




    public:

      BST(){
        root = nullptr;
      };

      ~BST(){
        deleteTree(root);
      };

      void insert(T key) {
        if (root != nullptr) {
          insertRecur(root, key);
        }
        else{
          root = new Node<T>(key);
        }
      }

      void printPreorder(){
        printerHelper(root);
      }

      Node<T>* find(T key){
        return finding(root, key);
      };

      int depth() {
        int x = deeper(root)-1;
        return x;
        }

      void remove(T key){
        remover(find(key));
      };
};

int main(){
  BST<int> *bst = new BST<int>();
  bst->insert(10);
  bst->insert(12);
  bst->insert(13);
  bst->insert(8);
  bst->insert(9);
  bst->insert(3);
  bst->insert(1);
  bst->insert(11);
  bst->printPreorder();
  cout<<"depth of the tree is: ";
  cout<<bst->depth()<<endl;
  bst->remove(12);
  bst->printPreorder();
  return 0;
}
