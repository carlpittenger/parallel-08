#include <chrono>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include <fcntl.h>
#include <omp.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

void generatePrefixSumData(int *arr, size_t n);
void checkPrefixSumResult(const int *arr, size_t n);

#ifdef __cplusplus
}
#endif

[[nodiscard]] auto main(const int argc, const char *const *const argv) noexcept
    -> int {
  // forces openmp to create the threads beforehand
#pragma omp parallel
  {
    const auto fd = open(argv[0], O_RDONLY);
    if (fd != -1) {
      close(fd);
    } else {
      std::cerr << "something is amiss\n";
    }
  }

  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " <n> <num_threads>\n";
    // return EXIT_FAILURE;
    return -1;
  }

  const auto n = std::atoi(argv[1]);
  const auto num_threads = std::atoi(argv[2]);
  auto *const arr = new int[n];
  generatePrefixSumData(arr, n);

  const auto *const pr = new int[n + 1];

  // insert prefix sum code here

  // start timing
  const auto start = std::chrono::system_clock::now();

  // end time
  const auto end = std::chrono::system_clock::now();
  const auto elapsed_seconds = std::chrono::duration<double>{end - start};
  // print the total execution time (in sec) to the error stream
  std::cerr << elapsed_seconds.count() << '\n';

  checkPrefixSumResult(pr, n);

  delete[] arr;

  return EXIT_SUCCESS;
}
