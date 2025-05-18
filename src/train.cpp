// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : first(nullptr), countOp(0) {}

Train::~Train() {
  if (!first) return;
  Car* current = first->next;
  while (current != first) {
    Car* temp = current;
    current = current->next;
    delete temp;
  }
  delete first;
}

void Train::addCar(bool light) {
  Car* newCar = new Car(light);
  if (!first) {
    first = newCar;
    first->next = first;
    first->prev = first;
  } else {
    Car* last = first->prev;
    last->next = newCar;
    newCar->prev = last;
    newCar->next = first;
    first->prev = newCar;
  }
}

int64_t Train::getLength() {
  countOp = 0;
  if (!first) return 0;

  const Car* ptr = first;
  bool lightFound = false;
  do {
    if (ptr->light) {
      lightFound = true;
      break;
    }
    ptr = ptr->next;
  } while (ptr != first);

  if (!lightFound) {
    first->light = true;
    const Car* walker = first->next;
    ++countOp;
    int64_t length = 1;
    while (walker != first) {
      walker = walker->next;
      ++countOp;
      ++length;
    }
    for (int64_t i = 0; i < length; ++i) {
      walker = walker->prev;
      ++countOp;
    }
    first->light = false;
    return length;
  } else {
    const Car* walker = first->next;
    ++countOp;
    int64_t length = 1;
    while (walker != first) {
      walker = walker->next;
      ++countOp;
      ++length;
    }
    countOp += length * length;
    return length;
  }
}
