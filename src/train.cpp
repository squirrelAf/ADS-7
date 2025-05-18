// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() : countOp(0), first(nullptr) {}

void Train::addCar(bool light) {
  Car* newTrainCar = new Car{light, nullptr, nullptr};
  if (!first) {
    first = newTrainCar;
    first->next = first;
    first->prev = first;
  } else {
    Car* lastTrainCar = first->prev;
    lastTrainCar->next = newTrainCar;
    newTrainCar->prev = lastTrainCar;
    newTrainCar->next = first;
    first->prev = newTrainCar;
  }
}

int Train::getLength() {
  if (!first) return 0;

  Car* currentTrainCar = first;
  if (!currentTrainCar->light) {
    currentTrainCar->light = true;
  }

  int trainLength = 0;
  while (true) {
    int traversalSteps = 0;
    while (true) {
      currentTrainCar = currentTrainCar->next;
      traversalSteps++;
      countOp++;
      if (currentTrainCar->light || currentTrainCar == first) break;
    }

    if (currentTrainCar == first && !currentTrainCar->light) break;

    if (currentTrainCar->light) {
      currentTrainCar->light = false;
    }

    for (int i = 0; i < traversalSteps; i++) {
      currentTrainCar = currentTrainCar->prev;
      countOp++;
    }

    if (!currentTrainCar->light) {
      trainLength = traversalSteps;
      break;
    }
  }

  return trainLength;
}

int Train::getOpCount() {
  return countOp;
}
