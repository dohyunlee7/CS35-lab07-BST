/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#include <stdexcept>
#include <utility>
#include <vector>

#include "adts/list.h"
#include "adts/queue.h"
#include "adts/stlList.h"
#include "adts/stlQueue.h"

#include "linkedBSTNode.h"
#include "helpers.h"

using std::pair;
using std::runtime_error;
using std::vector;

template <typename K, typename V> LinkedBST<K, V>::LinkedBST() {
    this->size = 0;
    this->root = nullptr;
}

template <typename K, typename V> LinkedBST<K, V>::~LinkedBST() {

  deleteSubtree(this->root);

}

template <typename K, typename V> int LinkedBST<K, V>::getSize() {
    return this->size;
}

template <typename K, typename V> bool LinkedBST<K, V>::isEmpty() {
    if(this->size != 0){
      return false;
    } else{
      return true;
    }
}

template <typename K, typename V> void LinkedBST<K, V>::insert(K key, V value) {
    //LinkedBSTNode<K,V>* node = new LinkedBSTNode<K,V>(key,value);
    this->root = insertInSubtree(this->root, key, value);
    this->size += 1;
}

template <typename K, typename V> void LinkedBST<K, V>::update(K key, V value) {
    updateInSubtree(this->root, key, value);
}

template <typename K, typename V> V LinkedBST<K, V>::get(K key) {
    //call findInSubtree here
    return findInSubtree(this->root, key);
}

template <typename K, typename V> bool LinkedBST<K, V>::contains(K key) {
    return containsInSubtree(this->root, key);
}

template <typename K, typename V> void LinkedBST<K, V>::remove(K key) {
    if(this->root == nullptr){
      throw runtime_error("Key not in dictionary");
    }
    this->root = removeFromSubtree(this->root, key);
    this->size --;
}

template <typename K, typename V> vector<K> LinkedBST<K, V>::getKeys() {
    vector <K> vectorKeys;
    vector<pair<K,V>> myVector = getItems();
    for (int i = 0; i < myVector.size(); i++) {
      //myVector[i] this is the item
      //extract key from this
      vectorKeys.push_back(myVector[i].first);
    }
    return vectorKeys;

}

template <typename K, typename V>
vector<pair<K, V>> LinkedBST<K, V>::getItems() {
    return traverseInOrder();
}

template <typename K, typename V> int LinkedBST<K, V>::getHeight() {
    return getHeightInSubtree(this->root);
}

template <typename K, typename V> K LinkedBST<K, V>::getMaxKey() {
    pair<K,V> myKey = getMaxInSubtree(this->root);
    return myKey.first;

}

template <typename K, typename V> K LinkedBST<K, V>::getMinKey() {
    pair<K,V> myKey = getMinInSubtree(this->root);
    return myKey.first;
}

template <typename K, typename V>
vector<pair<K, V>> LinkedBST<K, V>::traversePreOrder() {
    List <pair<K,V>>* myList = new STLList<pair<K,V>>();
    buildPreOrderTraversal(this->root, myList);
    //call dynamicListToStaticVector(myList); and store in vec
    //delete myList delete myList;
    //return the name of the list
    vector<pair<K,V>> myVectorPair = dynamicListToStaticVector(myList);
    delete myList;
    return myVectorPair;
}

template <typename K, typename V>
vector<pair<K, V>> LinkedBST<K, V>::traverseInOrder() {
  List <pair<K,V>>* myList = new STLList<pair<K,V>>();
  buildInOrderTraversal(this->root, myList);
  vector<pair<K,V>> myVectorPair = dynamicListToStaticVector(myList);
  delete myList;
  return myVectorPair;
}

template <typename K, typename V>
vector<pair<K, V>> LinkedBST<K, V>::traversePostOrder() {
  List <pair<K,V>>* myList = new STLList<pair<K,V>>();
  buildPostOrderTraversal(this->root, myList);
  vector<pair<K,V>> myVectorPair = dynamicListToStaticVector(myList);
  delete myList;
  return myVectorPair;
}

template <typename K, typename V>
vector<pair<K, V>> LinkedBST<K, V>::traverseLevelOrder() {
  STLQueue<LinkedBSTNode<K,V>*> queue;
  vector<pair<K,V>> theVector;
  queue.enqueue(this->root);
  while(!queue.isEmpty()){
    LinkedBSTNode<K,V>* currentVal = queue.dequeue();
    K theKey = currentVal->getKey();
    V theVal = currentVal->getValue();
    pair<K,V> thePair(theKey, theVal);
    theVector.push_back(thePair);
    if(currentVal->getLeft() != nullptr){
      queue.enqueue(currentVal->getLeft());
    }
    if(currentVal->getRight() != nullptr){
      queue.enqueue(currentVal->getRight());
    }
  }

  return theVector;

}

template <typename K, typename V> void LinkedBST<K, V>::checkInvariants() {
    if(this->countNodes(this->root) != this->size) {
        throw runtime_error(
            "Problem in BST: Node count doesn't match tree size");
    }
    if(this->root != nullptr) {
        // The bounds provided here are arbitrary because the false arguments
        // indicate that they do not apply.  But we need a value of type K to
        // fill this parameter since we don't have globally min/max K values
        // generically.
        this->verifyKeysBoundedBy(this->root, false, this->root->getKey(),
                                  false, this->root->getKey());
    }
}
