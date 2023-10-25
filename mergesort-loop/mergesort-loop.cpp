#include <chrono>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <iostream>

#include <omp.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

void generateMergeSortData(int *arr, size_t n);
void checkMergeSortResult(const int *arr, size_t n);

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

  // get arr data
  auto *const arr = new int[n];
  generateMergeSortData(arr, n);

  // start timing
  const auto start = std::chrono::system_clock::now();
  // insert sorting code here

  // printArray(arr, n);
  // end time
  const auto end = std::chrono::system_clock::now();
  const auto elapsed_seconds = std::chrono::duration<double>{end - start};
  // Print the total execution time (in sec) to the error stream
  std::cerr << elapsed_seconds.count() << '\n';

  checkMergeSortResult(arr, n);

  delete[] arr;

  return EXIT_SUCCESS;
}
