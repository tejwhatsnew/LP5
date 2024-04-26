#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

int minval_sequential(int arr[], int n) {
  int minval = arr[0];
  for(int i = 0; i < n; i++) {
    if(arr[i] < minval) minval = arr[i];
  }
  return minval;
}

int maxval_sequential(int arr[], int n) {
  int maxval = arr[0];
  for(int i = 0; i < n; i++) {
    if(arr[i] > maxval) maxval = arr[i];
  }
  return maxval;
}

int sum_sequential(int arr[], int n) {
  int sum = 0;
  for(int i = 0; i < n; i++) {
    sum += arr[i];
  }
  return sum;
}

double average_sequential(int arr[], int n) {
  return (double)sum_sequential(arr, n) / n;
}

int minval_parallel(int arr[], int n) {
  int minval = arr[0];
  #pragma omp parallel for reduction(min : minval)
  for(int i = 0; i < n; i++) {
    if(arr[i] < minval) minval = arr[i];
  }
  return minval;
}

int maxval_parallel(int arr[], int n) {
  int maxval = arr[0];
  #pragma omp parallel for reduction(max : maxval)
  for(int i = 0; i < n; i++) {
    if(arr[i] > maxval) maxval = arr[i];
  }
  return maxval;
}

int sum_parallel(int arr[], int n) {
  int sum = 0;
  #pragma omp parallel for reduction(+ : sum)
  for(int i = 0; i < n; i++) {
    sum += arr[i];
  }
  return sum;
}

double average_parallel(int arr[], int n) {
  return (double)sum_parallel(arr, n) / n;
}

int main() {
  int n;
  cout << "Enter the number of elements: ";
  cin >> n;
  int arr[n];
  cout << "Enter the elements: ";
  for(int i = 0; i < n; i++) {
    cin >> arr[i];
  }

  auto start = high_resolution_clock::now();
  cout << "The minimum value (sequential) is: " << minval_sequential(arr, n) << '\n';
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  cout << "Time taken by sequential minval: " << duration.count() << " microseconds" << endl;

  start = high_resolution_clock::now();
  cout << "The maximum value (sequential) is: " << maxval_sequential(arr, n) << '\n';
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  cout << "Time taken by sequential maxval: " << duration.count() << " microseconds" << endl;

  start = high_resolution_clock::now();
  cout << "The summation (sequential) is: " << sum_sequential(arr, n) << '\n';
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  cout << "Time taken by sequential sum: " << duration.count() << " microseconds" << endl;

  start = high_resolution_clock::now();
  cout << "The average (sequential) is: " << average_sequential(arr, n) << '\n';
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  cout << "Time taken by sequential average: " << duration.count() << " microseconds" << endl;

  start = high_resolution_clock::now();
  cout << "The minimum value (parallel) is: " << minval_parallel(arr, n) << '\n';
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  cout << "Time taken by parallel minval: " << duration.count() << " microseconds" << endl;

  start = high_resolution_clock::now();
  cout << "The maximum value (parallel) is: " << maxval_parallel(arr, n) << '\n';
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  cout << "Time taken by parallel maxval: " << duration.count() << " microseconds" << endl;

  start = high_resolution_clock::now();
  cout << "The summation (parallel) is: " << sum_parallel(arr, n) << '\n';
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  cout << "Time taken by parallel sum: " << duration.count() << " microseconds" << endl;

  start = high_resolution_clock::now();
  cout << "The average (parallel) is: " << average_parallel(arr, n) << '\n';
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  cout << "Time taken by parallel average: " << duration.count() << " microseconds" << endl;

  return 0;
}
