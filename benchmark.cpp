//
// (C) 2022-2023, E. Wes Bethel
// benchmark-* harness for running different versions of the sum study
//    over different problem sizes
//
// usage: no command line arguments
// set problem sizes, block sizes in the code below

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>
#include <string.h>

extern void setup(int64_t N, uint64_t A[]);
extern int64_t sum(int64_t N, uint64_t A[]);

// Constants for performance calculations
const double PEAK_BANDWIDTH = 204.8; // GB/s for Perlmutter CPU
const int BYTES_PER_ELEMENT = sizeof(uint64_t);

double calculate_mflops(int64_t N, double elapsed_time)
{
   double operations = static_cast<double>(N); // One addition per element
   return (operations / elapsed_time) / 1e6;
}

double calculate_bandwidth_utilization(int64_t N, double elapsed_time)
{
   double bytes_accessed = static_cast<double>(N) * BYTES_PER_ELEMENT;
   double bandwidth = (bytes_accessed / elapsed_time) / 1e9; // GB/s
   return (bandwidth / PEAK_BANDWIDTH) * 100.0;
}

double calculate_memory_latency(int64_t N, double elapsed_time)
{
   int64_t memory_accesses = N;                   // Assumes one memory access per element
   return (elapsed_time / memory_accesses) * 1e9; // Convert to nanoseconds
}

int main(int argc, char **argv)
{
   std::cout << std::fixed << std::setprecision(2);

#define MAX_PROBLEM_SIZE 1 << 28 //  256M
   std::vector<int64_t> problem_sizes{MAX_PROBLEM_SIZE >> 5, MAX_PROBLEM_SIZE >> 4, MAX_PROBLEM_SIZE >> 3, MAX_PROBLEM_SIZE >> 2, MAX_PROBLEM_SIZE >> 1, MAX_PROBLEM_SIZE};

   std::vector<uint64_t> A(MAX_PROBLEM_SIZE);

   int64_t t;
   int n_problems = problem_sizes.size();

   std::cout << "Problem Size,Elapsed Time (s),Sum Result,MFLOP/s,Bandwidth Utilization (%),Memory Latency (ns)\n";

   for (int64_t n : problem_sizes)
   {
      setup(n, &A[0]);

      auto start_time = std::chrono::high_resolution_clock::now();
      t = sum(n, &A[0]);
      auto end_time = std::chrono::high_resolution_clock::now();

      std::chrono::duration<double> elapsed_time = end_time - start_time;
      double elapsed_seconds = elapsed_time.count();

      double mflops = calculate_mflops(n, elapsed_seconds);
      double bandwidth_util = calculate_bandwidth_utilization(n, elapsed_seconds);
      double memory_latency = calculate_memory_latency(n, elapsed_seconds);

      std::cout << n << "," << mflops << "," << bandwidth_util << "," << memory_latency << "\n";

      std::cout << "Problem Size: " << n << "\n"
                << "Elapsed Time (s): " << elapsed_seconds << "\n"
                << "Sum Result: " << t << "\n"
                << "MFLOP/s: " << mflops << "\n"
                << "Bandwidth Utilization (%): " << bandwidth_util << "\n"
                << "Memory Latency (ns): " << memory_latency << "\n\n";
   }
}

// EOF
