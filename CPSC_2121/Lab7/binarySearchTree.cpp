/*
 * Keenan Grant
 * 11/9/22
 * 003
 * Lab 7: Binary Search Tree
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <assert.h>

#include "binarySearchTree.h"

using namespace std;

void fix_size(Node *T)
{
  T->size = 1;
  if (T->left) T->size += T->left->size;
  if (T->right) T->size += T->right->size;
}

// insert key k into tree T, returning a pointer to the resulting tree
Node *insert(Node *T, int k)
{
  if (T == nullptr) return new Node(k);
  if (k < T->key) T->left = insert(T->left, k);
  else T->right = insert(T->right, k);
  fix_size(T);
  return T;
}

// returns a vector of key values corresponding to the inorder traversal of T (i.e., the contents of T in sorted order)
vector<int> inorder_traversal(Node *T)
{
  vector<int> inorder;
  vector<int> rhs;
  if (T == nullptr) return inorder;
  inorder=inorder_traversal(T->left);
  inorder.push_back(T->key);
  rhs=inorder_traversal(T->right);
  inorder.insert(inorder.end(), rhs.begin(), rhs.end());
  return inorder;
}

// return a pointer to the node with key k in tree T, or nullptr if it doesn't exist
Node *find(Node *T, int k) {
  //Implement Node *find(Node *T, int k)

  if (T == nullptr || T -> key == k) {
    return T;
  }
  if (k < T -> key) {
    return find(T -> left, k);
  }
  return find(T -> right, k);
}

// return pointer to node of rank r (with r'th largest key; e.g. r=0 is the minimum)
Node *select(Node *T, int r) {
  assert(T!=nullptr && r>=0 && r<T->size);

  //Implement Node *select(Node *T, int r)
  int rank = 0;
  if (T -> left != nullptr) {
    rank = T -> left -> size;
  }
  if (rank > r) {
    return select(T -> left, r);
  }
  if (rank < r) {
    return select(T -> right, r - rank - 1);
  }
  return T;
}

// Join trees L and R (with L containing keys all <= the keys in R)
// Return a pointer to the joined tree.  
Node *join(Node *L, Node *R) {
  // choose either the root of L or the root of R to be the root of the joined tree
  // (where we choose with probabilities proportional to the sizes of L and R)
  
  //Implement Node *join(Node *L, Node *R)
  //If either node is null then the other node will be returned
  if (L == nullptr) {
    return R;
  }
  if (R == nullptr) {
    return L;
  }

  double prob = abs(L -> size) / (abs(L -> size) + abs(R -> size));
  double value = rand() / (double)RAND_MAX;

  if (value <= prob) {
    L -> right = join(L -> right, R);
    fix_size(L);
    return L;
  }
  else {
    R -> left = join(L, R -> left);
    fix_size(R);
    return R;
  }
}

// remove key k from T, returning a pointer to the resulting tree.
// it is required that k be present in T
Node *remove(Node *T, int k) {
  assert(T != nullptr);
  
  //Implement Node *remove(Node *T, int k)
  //If the key is less than the node's key then a recursive call is made on the left node
  if (k < T -> key) {
    T -> left = remove(T -> left, k);
    fix_size(T);
    return T;
  }
  //If the key is greater than the node's key then a recursive call is made on the right node
  if (k > T -> key) {
    T -> right = remove(T -> right, k);
    fix_size(T);
    return T;
  }
  //Removes the node if the key equals the node's key
  if (k == T -> key) {
    Node *temp = T;
    T = join(T -> left, T -> right);
    if (T != nullptr) {
      fix_size(T);
    }
    delete temp;
    return T;
  }
  //A placebo return value
  return T;
}

// Split tree T on key k into tree L (containing keys <= k) and a tree R (containing keys > k)
void split(Node *T, int k, Node **L, Node **R) {
  //Implement void split(Node *T, int k, Node **L, Node **R)
  if (T == nullptr) {
    *L = nullptr;
    *R = nullptr;
  }
  if (T -> key <= k) {
    if (T -> right != nullptr) {
      split(T -> right, k, L, R);
      T -> right = *L;
      *L = T;
    }
    //If the current tree's right side is null then the left tree becomes the current tree
    else {
      *L = T;
      *R = nullptr;
    }
    if (*L != nullptr) {
      fix_size(*L);
    }
  }
  if (T -> key > k) {
    if (T -> left != nullptr) {
      split(T -> left, k, L, R);
      T -> left = *R;
      *R = T;
    }
    //If the current tree's left side is null then the right tree becomes the current tree
    else {
      *R = T;
      *L = nullptr;
    }
    if (*R != nullptr) {
      fix_size(*R);
    }
  }
}

// insert key k into the tree T, returning a pointer to the resulting tree
Node *insert_random(Node *T, int k) {
  // If k is the Nth node inserted into T, then:
  // with probability 1/N, insert k at the root of T
  // otherwise, insert_random k recursively left or right of the root of T
  
  //Implement Node *insert_random(Node *T, int k)
  if (T == nullptr) {
    Node *newNode = new Node(k);
    return newNode;
  }

  double value = rand() / (double)RAND_MAX;
  double prob = rand() % T -> size;

  //If the probability is 0 then a new node is inserted into the tree using split()
  if (prob == 0) {
    Node *newNode = new Node(k);
    split(T, k, &newNode -> left, &newNode -> right);
    fix_size(newNode);
    return newNode;
  }
  //If the key is less than the node value then a recursive call is made on the left node
  else if (k < T -> key) {
    T -> left = insert_random(T -> left, k);
    fix_size(T);
    return T;
  }
  //If the key is greater than the node value then a recursive call is made on the right node
  else if (k > T -> key) {
    T -> right = insert_random(T -> right, k);
    fix_size(T);
    return T;
  }
  //Placebo return value
  return T;
}

void printVector(vector<int> v)
{
    for (int i=0; i<v.size(); i++)
    {
        cout << v[i] << endl;
    }
}

// int main(void)
// {
//   vector<int> inorder;
//   vector<int> A(10,0);
  
//   // put 0..9 into A[0..9] in random order
//   for (int i=0; i<10; i++) A[i] = i;
//   for (int i=9; i>0; i--) swap(A[i], A[rand()%i]);
//   cout << "Contents of A (to be inserted into BST):\n";
//   printVector(A);
  
//   // insert contents of A into a BST
//   Node *T = nullptr;
//   for (int i=0; i<10; i++) T = insert(T, A[i]);
  
//   // print contents of BST (should be 0..9 in sorted order)
//   cout << "Contents of BST (should be 0..9 in sorted order):\n";
//   inorder=inorder_traversal(T);
//   printVector(inorder);

//   // test select
//   for (int i=0; i<10; i++) {
//     Node *result = select(T, i);
//     if (!result || result->key != i) cout << "Select test failed for select(" << i << ")!\n";
//   }

//   // test find: Elements 0..9 should be found; 10 should not be found
//   cout << "Elements 0..9 should be found; 10 should not be found:\n";
//   for (int i=0; i<11; i++) 
//     if (find(T,i)) cout << i << " found\n";
//     else cout << i << " not found\n";

//   // test split
//   Node *L, *R;
//   split(T, 4, &L, &R);
//   cout << "Contents of left tree after split (should be 0..4):\n";
//   inorder=inorder_traversal(L);
//   printVector(inorder);
//   cout << "Left tree size " << L->size << "\n";
//   cout << "Contents of right tree after split (should be 5..9):\n";
//   inorder=inorder_traversal(R);
//   printVector(inorder);
//   cout << "Right tree size " << R->size << "\n";
    
//   // test join
//   T = join(L, R);
//   cout << "Contents of re-joined tree (should be 0..9)\n";
//   inorder=inorder_traversal(T);
//   printVector(inorder);
//   cout << "Tree size " << T->size << "\n";
  
//   // test remove
//   for (int i=0; i<10; i++) A[i] = i;
//   for (int i=9; i>0; i--) swap(A[i], A[rand()%i]);
//   for (int i=0; i<10; i++) {
//     T = remove(T, A[i]);
//     cout << "Contents of tree after removing " << A[i] << ":\n";
//     inorder=inorder_traversal(T);
//     printVector(inorder);
//     if (T != nullptr)
//       cout << "Tree size " << T->size << "\n";
//   }

//   // test insert_random
//   cout << "Inserting 1 million elements in order; this should be very fast...\n";
//   for (int i=0; i<1000000; i++) T = insert_random(T, i);
//   cout << "Tree size " << T->size << "\n";
//   cout << "Done\n";
  
//   return 0;
// }
