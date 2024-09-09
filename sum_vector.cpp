#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>
#include <string.h>

void setup(int64_t N, uint64_t A[])
{
   printf(" inside sum_vector problem_setup, N=%lld \n", N);
   for (int64_t i = 0; i < N; i++)
   {
      A[i] = i; // Initialize array with values 0 to N-1
   }
}

int64_t
sum(int64_t N, uint64_t A[])
{
   printf(" inside sum_vector perform_sum, N=%lld \n", N);
   int64_t total = 0;
   for (int64_t i = 0; i < N; i++)
   {
      total += A[i];
   }
   return total;
}