#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void generateReduceData(int *const arr, const size_t n) {
  for (size_t i = 0; i < n; ++i) {
    if (i % 2 == 0) {
      arr[i] = (int)(i / 2);
    } else {
      arr[i] = (int)(-(i / 2));
    }
  }
}

void generateMergeSortData(int *const arr, const size_t n) {
  for (int i = 0; i < (int)n; ++i) {
    arr[i] = i;
  }

  for (int i = (int)(n - 1); i > 0; --i) {
    const int swap_with = rand() % i;
    const int temp = arr[i];
    arr[i] = arr[swap_with];
    arr[swap_with] = temp;
  }
}

void generatePrefixSumData(int *const arr, const size_t n) {
  for (unsigned i = 0u; i < n; ++i) {
    if (i % 2 == 0) {
      arr[i] = (int)(i / 2);
    } else {
      arr[i] = (int)-(i / 2);
    }
  }
}

void checkPrefixSumResult(const int *const arr, const size_t n) {
  int *const data = malloc(sizeof(int) * n);
  generatePrefixSumData(data, n);

  int correct = (arr[0] == 0);

  int sum = 0;
  for (unsigned i = 0u; i < n; ++i) {
    sum += data[i];
    if (arr[i + 1] != sum) {
      correct = 0;
    }
  }

  if (correct) {
    printf("checked\n");
  } else {
    printf("incorrect\n");
  }
  free(data);
}

// this is based on how MS data is generated
void checkMergeSortResult(const int *const arr, const size_t n) {
  bool correct = true;

  for (int i = 0; i < (int)(n - 1); ++i) {
    correct = correct && (arr[i] == i);
  }

  if (correct) {
    printf("checked\n");
  } else {
    printf("incorrect\n");
  }
}

// assumes n and m are powers of 10
void generateLCS(char *const X, const int m, char *const Y, const int n) {
  const char A = 'A';
  const char B = 'B';
  const char C = 'C';

  const int x = (n > m) ? m : n;

  // X ~ AABBAAAAAA
  for (int i = 0; i < (2 * x / 10); ++i) {
    X[i] = A;
    X[i + (2 * x / 10)] = B;
  }
  for (int i = (4 * x / 10); i < m; ++i) {
    X[i] = A;
  }

  // Y ~ CCCCCCCCBB
  for (int i = 0; i < (n - (2 * x / 10)); ++i) {
    Y[i] = C;
  }
  for (int i = n - (2 * x / 10); i < n; ++i) {
    Y[i] = B;
  }
}

void checkLCS(const char *const X, const int m, const char *const Y,
              const int n, const int result) {
  const int x = (n > m) ? m : n;
  if ((x * 2 / 10) == result) {
    printf("checked\n");
  } else {
    printf("incorrect\n");
  }
}
