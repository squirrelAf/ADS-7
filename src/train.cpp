// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : first(nullptr), countOp(0) {}

Train::~Train() {
  if (!first) return;
  Car* cur = first->next;
  while (cur != first) {
    Car* toDel = cur;
    cur = cur->next;
    delete toDel;
  }
  delete first;
}

void Train::addCar(bool light) {
  Car* c = new Car(light);
  if (!first) {
    first = c;
  } else {
    Car* last = first->prev;
    last->next = c;
    c->prev = last;
    c->next = first;
    first->prev = c;
  }
}

std::size_t Train::getLength() {
  countOp = 0;
  if (!first) return 0;

  const Car* p = first;
  bool hasOn = false;
  do {
    if (p->light) {
      hasOn = true;
      break;
    }
    p = p->next;
  } while (p != first);

  if (!hasOn) {
    first->light = !first->light;
    const Car* cur = first->next;
    ++countOp;
    std::size_t len = 1;
    while (cur != first) {
      cur = cur->next;
      ++countOp;
      ++len;
    }
    for (std::size_t i = 0; i < len; ++i) {
      cur = cur->prev;
      ++countOp;
    }
    first->light = !first->light;
    return len;
  } else {
    const Car* cur = first->next;
++countOp;
std::size_t len = 1;
while (cur != first) {
  cur = cur->next;
  ++countOp;
  ++len;
}
countOp += len * len;
return len;
  }
}

std::size_t Train::getOpCount() const { return countOp; }
