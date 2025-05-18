#include <chrono>
#include <cstdint>
#include <iostream>
#include <random>
#include <vector>
#include "train.h"

using Clock = std::chrono::high_resolution_clock;

enum InitMode { ALL_OFF, ALL_ON, RANDOM };

void run_experiment(InitMode mode, const std::vector<int>& ns) {
  std::mt19937_64 rnd{static_cast<uint64_t>(std::random_device {}())};
  std::uniform_int_distribution<int> bit{0, 1};

  for (int n : ns) {
    Train train;
    for (int i = 0; i < n; ++i) {
      bool light = (mode == ALL_OFF ? false : mode == ALL_ON ? true : bit(rnd));
      train.addCar(light);
    }

    auto t0 = Clock::now();
    std::size_t length = train.getLength();
    auto t1 = Clock::now();

    double elapsed_ms =
        std::chrono::duration<double, std::milli>(t1 - t0).count();
    std::size_t ops = train.getOpCount();

    std::cout << (mode == ALL_OFF  ? "ALL_OFF  "
                  : mode == ALL_ON ? "ALL_ON   "
                                   : "RANDOM   ")
              << "n=" << length << "  ops=" << ops
              << "  time(ms)=" << elapsed_ms << '\n';
  }
}

int main() {
  std::vector<int> ns;
  for (int n = 1000; n <= 10000; n += 1000) {
    ns.push_back(n);
  }

  std::cout << "ALL_OFF\n";
  run_experiment(ALL_OFF, ns);

  std::cout << "\nALL_ON\n";
  run_experiment(ALL_ON, ns);

  std::cout << "\nRANDOM\n";
  run_experiment(RANDOM, ns);

  return 0;
}
