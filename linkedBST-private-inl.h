/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#include <stdexcept>
#include <utility>

#include "adts/list.h"
#include "adts/stlList.h"

using std::runtime_error;

template <typename K, typename V>


 V LinkedBST<K, V>::findInSubtree(LinkedBSTNode<K, V>* current, K key) {
    if (current == nullptr) {
      throw runtime_error("Key is not in tree.");
    }
    else if (current->getKey() < key) {
      current = current->getRight();
      return findInSubtree(current, key);
    }
    else if (current->getKey() > key) {
      current = current->getLeft();
      return findInSubtree(current, key);
    } else {
      return current->getValue();
    }
}

template <typename K, typename V>
bool LinkedBST<K, V>::containsInSubtree(LinkedBSTNode<K, V>* current, K key) {
  if (current == nullptr) {
    return false;
  }
  else if (current->getKey() < key) {
    current = current->getRight();
    return containsInSubtree(current, key);
  }
  else if (current->getKey() > key) {
    current = current->getLeft();
    return containsInSubtree(current, key);
  } else {
    return true;
  }
}

template <typename K, typename V>
void LinkedBST<K, V>::updateInSubtree(LinkedBSTNode<K, V>* current, K key, V value) {
  if (current == nullptr) {
    throw runtime_error("Key is not in tree.");
  } else if (current->getKey() < key) {
    current = current->getRight();
    return updateInSubtree(current, key, value);
  }
  else if (current->getKey() > key) {
    current = current->getLeft();
    return updateInSubtree(current, key, value);
  } else {
     current->setValue(value);
  }
}

template <typename K, typename V>
int LinkedBST<K, V>::getHeightInSubtree(LinkedBSTNode<K, V>* current) {
  if(current == nullptr){
    return -1;
  }
  int leftHeight = getHeightInSubtree(current->getLeft());
  int rightHeight = getHeightInSubtree(current->getRight());
  if (leftHeight > rightHeight) {
      return leftHeight + 1;
    }
  return rightHeight + 1;
}


template <typename K, typename V>
pair<K, V> LinkedBST<K, V>::getMinInSubtree(LinkedBSTNode<K, V>* current) {
  if(current == nullptr){
    throw runtime_error("Error");
  }
  while(current->getLeft()!= nullptr){
    current = current->getLeft();
  }
  return pair<K,V>(current->getKey(),current->getValue());
}

template <typename K, typename V>
pair<K, V> LinkedBST<K, V>::getMaxInSubtree(LinkedBSTNode<K, V>* current) {
  if(current == nullptr){
    throw runtime_error("Error");
  }
  while(current->getRight()!= nullptr){
    current = current->getRight();
  }
  return pair<K,V>(current->getKey(), current->getValue());
}


template <typename K, typename V>
LinkedBSTNode<K, V>*
LinkedBST<K, V>::insertInSubtree(LinkedBSTNode<K, V>* current, K key, V value) {
  if(current == nullptr){
    LinkedBSTNode<K,V>* theNode = new LinkedBSTNode<K,V>(key, value);
    return theNode;
  }
  else if(key < current->getKey()){
    current->setLeft(insertInSubtree(current->getLeft(), key, value));
    return current;
  }
  else if(key > current->getKey()){
    current->setRight(insertInSubtree(current->getRight(), key, value));
    return current;
  }
  else{
    throw runtime_error("Duplicate Key");
  }
}

template <typename K, typename V>
LinkedBSTNode<K, V>*
LinkedBST<K, V>::removeFromSubtree(LinkedBSTNode<K, V>* current, K key) {
  if (current == nullptr) {
    throw runtime_error("AH - Key not in subtree");
  }
  else if (key < current->getKey()) {
    current->setLeft(removeFromSubtree(current->getLeft(), key));
    return current;
  }
  else if (key > current->getKey()) {
    current->setRight(removeFromSubtree(current->getRight(), key));
    return current;
  }
  else {
    if (current->getLeft() == nullptr && current->getLeft() == nullptr) {
      delete current;
      return nullptr;
    }//call getMaxInSubtree on the left subtree
    else if (current->getLeft() == nullptr) {
      LinkedBSTNode<K,V>* newVar = current->getRight();
      delete current;
      return newVar;
    }
    else if (current->getRight() == nullptr) {
      LinkedBSTNode<K,V>* newVar = current->getLeft();
      delete current;
      return newVar;
    } else {
      //lost on this case
      pair<K,V> myPair = getMaxInSubtree(current->getLeft());
      current->setKey(myPair.first);
      current->setValue(myPair.second);
      current->setLeft(removeFromSubtree(current->getLeft(), myPair.first));
      return current;
    }
  }
}

template <typename K, typename V>
void LinkedBST<K, V>::deleteSubtree(LinkedBSTNode<K, V>* current) {
  if(current != nullptr){
    deleteSubtree(current->getLeft());
    deleteSubtree(current->getRight());
    delete current;

  }
}

template <typename K, typename V>
void LinkedBST<K, V>::buildPreOrderTraversal(LinkedBSTNode<K, V>* current,
                                             List<pair<K, V>>* list) {
  if(current == nullptr) {
    return;
    }

  pair <K, V> thePair(current->getKey(), current->getValue());
  list->insertLast(thePair);
  buildPreOrderTraversal(current->getLeft(), list);
  buildPreOrderTraversal(current->getRight(), list);

}

template <typename K, typename V>
void LinkedBST<K, V>::buildInOrderTraversal(LinkedBSTNode<K, V>* current,
                                            List<pair<K, V>>* list) {
    if(current == nullptr) {
      return;
    } else {
      buildInOrderTraversal(current->getLeft(), list);
      list->insertLast(pair<K,V>(current->getKey(), current->getValue()));
      buildInOrderTraversal(current->getRight(), list);
    }
}

template <typename K, typename V>
void LinkedBST<K, V>::buildPostOrderTraversal(LinkedBSTNode<K, V>* current,
                                              List<pair<K, V>>* list) {
    if(current == nullptr) {
      return;
    } else {
      buildPostOrderTraversal(current->getLeft(), list);
      buildPostOrderTraversal(current->getRight(), list);
      list->insertLast(pair<K,V>(current->getKey(), current->getValue()));
    }
}

template <typename K, typename V>
int LinkedBST<K, V>::countNodes(LinkedBSTNode<K, V>* current) {
    if (current == nullptr) {
        return 0;
    } else {
        return this->countNodes(current->getLeft()) +
               this->countNodes(current->getRight()) + 1;
    }
}

template <typename K, typename V>
void LinkedBST<K, V>::verifyKeysBoundedBy(LinkedBSTNode<K, V>* current,
                                          bool minApplies, K minBound,
                                          bool maxApplies, K maxBound) {
    if (minApplies && current->getKey() < minBound) {
        throw runtime_error("LinkedBST::verifyKeysBoundedBy: a node has a "
                            "right descendent with lesser key");
    }
    if (maxApplies && current->getKey() > maxBound) {
        throw runtime_error("LinkedBST::verifyKeysBoundedBy: a node has a left "
                            "descendent with greater key");
    }
    if (current->getLeft() != nullptr) {
        verifyKeysBoundedBy(current->getLeft(), minApplies, minBound, true,
                            current->getKey());
    }
    if (current->getRight() != nullptr) {
        verifyKeysBoundedBy(current->getRight(), true, current->getKey(),
                            maxApplies, maxBound);
    }
}
