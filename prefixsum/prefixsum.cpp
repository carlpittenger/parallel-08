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

auto prefix_sum(const int *const arr, const int n, int *const ptr,
                const int num_threads) noexcept -> void {
  // std::cout << "prefix_sum()\n";
  // initial value for prefix sum
  ptr[0] = 0;

  // for (auto i = 0; i < n; ++i) {
  //   ptr[i + 1] = ptr[i] + arr[i];
  // }

  const auto chunk_size = n / num_threads;

  // step 1: compute prefix sums for each chunk in parallel
#pragma omp parallel num_threads(num_threads) default(none)                    \
    shared(n, chunk_size, ptr, arr, num_threads)
  {
    const auto thread_id = omp_get_thread_num();
    const auto start = thread_id * chunk_size;
    const auto end = (thread_id == num_threads - 1) ? n : (start + chunk_size);

    auto prefix_sum = 0;
    for (auto i = start; i < end; ++i) {
      prefix_sum += arr[i];
      ptr[i + 1] = prefix_sum;
    }
  }

// step 2: adjust prefix sums for chunk boundaries
#pragma omp parallel num_threads(num_threads) default(none)                    \
    shared(n, chunk_size, ptr, num_threads)
  {
    const auto thread_id = omp_get_thread_num();
    const auto start = thread_id * chunk_size;

    if (thread_id < num_threads - 1) {
      const auto last_element = ptr[start + chunk_size];
#pragma omp barrier
      for (auto i = start + chunk_size; i < n + 1; ++i) {
        ptr[i] += last_element;
      }
    }
  }
}

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
  const auto arr = new int[n];
  generatePrefixSumData(arr, n);

  const auto ptr = new int[n + 1];

  // start timing
  const auto start = std::chrono::system_clock::now();

  // insert prefix sum code here

  prefix_sum(arr, n, ptr, num_threads);

  // end time
  const auto end = std::chrono::system_clock::now();
  const auto elapsed_seconds = std::chrono::duration<double>{end - start};
  // print the total execution time (in sec) to the error stream
  std::cerr << elapsed_seconds.count() << '\n';

  checkPrefixSumResult(ptr, n);

  delete[] arr;
  delete[] ptr;

  return EXIT_SUCCESS;
}
