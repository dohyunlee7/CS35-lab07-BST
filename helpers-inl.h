/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#include "helpers.h"

template <typename T> vector<T> dynamicListToStaticVector(List<T>* list) {
  vector<T> myVector;
  for(int i = 0; i < list->getSize(); i ++){
    myVector.push_back(list->get(i));
  }
  return myVector;
}
