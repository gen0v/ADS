#include "MyAlgorithms.h"
#include <omp.h>

namespace MyAlgorithms {

  //************
  // QuickSort *
  //************      
  void QuickSort(vector<int> &arr, int low, int high) {
	  if (low < high) {
		  int par = part(arr, low, high);
		  QuickSort(arr, low, par - 1);
		  QuickSort(arr, par + 1, high);
	  }
  }

  int part(vector<int>& a, int low, int high)
  {
	  int piv = a[high];
	  int i = low - 1;
	  for (int j = low; j <= high - 1; j++)
	  {
		  //search with j for smaller or equal to piv
		  if (a[j] <= piv) {
			  i++;
			  swap(a[i], a[j]);
		  }
	  }
	  //swap pivot with last biggest element
	  swap(a[i + 1], a[high]);
	  return (i + 1);
  }

  //************
  // MergeSort *
  //************
  
  void MergeSort(vector<int> &a, int low, int high) {
	  if (low < high) {
		  int mid = low + (high - low) / 2;
		  //no overflow like this
		  MergeSort(a, low, mid);
		  MergeSort(a, mid+1, high);
		  //std::cout << "LOW " << low << " MID "<< mid << " HIGH " << high << std::endl;
		  merge(a, low, mid, high);
		  //Should be correct
	  }
  }
  void merge(vector<int> &a, int low,int mid, int high) {

	  int i, j, k;
	  int n1 = mid - low + 1;
	  //std::cout << "n1 " << n1 << std::endl;
	  int n2 = high - mid;
	  //std::cout << "n2 " << n2 << std::endl;
	  //Arrays
	  vector<int> left(n1);
	  vector<int> right(n2);
	  for (i = 0; i < n1; i++)
	  {
		  //left.push_back(a[low + i]);
		  left[i] = a[low + i];
	  }
	  for (j = 0; j < n2; j++)
	  {
		  //right.push_back(a[mid + j + 1]);
		  right[j] = a[mid + 1 + j];
	  }

	  i = 0;
	  j = 0;
	  k = low;
	  while(i < n1 && j < n2){
		  //std::cout << "IS " << left[i] <<" SMALLER OR EQUAl THAN "<<right[j]<< std::endl;
		  if (left[i] <= right[j]) {
			  //std::cout << "YES"<< std::endl;
			  a[k] = left[i];
			  i++;
		  }
		  else {
			  //std::cout << "NO" << std::endl;
			  a[k] = right[j];
			  j++;
		  }
		  k++;
	  }
	  //if some indexes are left which should not happen but for correction
	  //go through again so no error occurs
	  while (i < n1) {
		  a[k] = left[i];
		  i++;
		  k++;
	  }
	  while (j < n2) {
		  a[k] = right[j];
		  j++;
		  k++;
	  }

  }

  //************
  // Heapsort  *
  //************
  void HeapSort(vector<int> &a, int size) {
	  //change the array
	  int h = size / 2 - 1;
	  for (int i = h; i >= 0; i--)
	  {
		  //construct the heaparray
		  maxHeap(a, size, i);
	  }
	  //now delete the elements one by one
	  /*
	  for (int aa : a) {
	  std::cout << aa << "|";
	  }
	  */
	  for (int i = size - 1; i >= 0; i--)
	  {
		  swap(a[0], a[i]);
		  maxHeap(a, i, 0);
	  }
  }
  /*
  i : rootnode
  */
  void maxHeap(vector<int>& a, int size, int i)
  {
	  int biggest = i;
	  //get left and right node
	  int left = 2 * i + 1;
	  int right = 2 * i + 2;
	  //test the childnodes
	  //if they are bigger then swap
	  if (left < size && a[left] > a[biggest]) {
		  biggest = left;
	  }
	  if (right < size && a[right] > a[biggest]) {
		  biggest = right;
	  }
	  //case if root is not biggest swap and test the nodetree
	  if (biggest != i) {
		  swap(a[i], a[biggest]);
		  maxHeap(a, size, biggest);
	  }
  }


  //************
  // Shellsort *
  //************
  void ShellSort(vector<int> &a, int size) {
	  // Schleife über die Abstandsfolge
	  for (int gap = size / 2; gap > 0; gap /= 2) {
		  // Insertion Sort von Elementen mit Abstand gap
		  for (int i = gap; i < size; i++) {
			  int tmp = a[i];
			  int j = i;
			  for (; j >= gap && tmp < a[j - gap]; j -= gap) {
				  a[j] = a[j - gap];
			  }
			  a[j] = tmp;
		  }
	  }
  }
  /*
  void ShellSortHibbard(vector<int> &a, int size) {
	  //max Element in a as in h(i) < size - 1
	  //for (int gap = 1; gap < size-1; gap = pow(2,gap) + 1) {
	  //for (int gap = temp; gap < size; gap = 2 * gap + 1) {
	  int gap = 1;
	  while(gap < size-1){
		  //std::cout << "gap" << gap << std::endl;
		  for (int i = gap; i < size; i++) {
			  //std::cout << "i " << i << std::endl;
			  //std::cout << "a[i] " << a[i] << std::endl;
			  int tmp = a[i];
			  int j = i;
			  for (; j >= gap && tmp < a[j - gap]; j -= gap) {
				  a[j] = a[j - gap];
			  }
			  a[j] = tmp;
		  }
		  gap = gap * 2 + 1;
	  }
  }
  */
  void ShellSortHibbard(vector<int> &a, int size) {
	  //max Element in a as in h(i) < size - 1
	  int hib = 0;
	  for (int k = 1; k < size-1; k = k * 2 + 1)
	  {
		  hib = k;
	  }
	  //std::cout << hib << std::endl;
	  for (int gap = hib; gap > 0; gap = (gap-1)/2) {
		  // Insertion Sort von Elementen mit Abstand gap
		  for (int i = 0; i < size-gap+1; i++) {
			  int tmp = a[i];
			  int j = i;
			  for (; j >= gap && tmp < a[j - gap]; j -= gap) {
				  a[j] = a[j - gap];
			  }
			  a[j] = tmp;
		  }
	  }
  }
 
  //************************************
  //Matrix Multiplication Column Major *
  //************************************

  void MatrixMul_ColMajor(vector<double> &A,
	  vector<double> &B,
	  vector<double> &C,
	  int n,
	  int numThreads)
  {
	  //lda, ldb, ldc are leading dimensions of matrices A,B and C
	  int lda = n;
	  int ldb = n;
	  int ldc = n;
	  double s = 0.0;

	  //int num_procs = omp_get_num_procs();
	  omp_set_num_threads(numThreads);

#pragma omp parallel for
	  for (int i = 0; i < n; i++) {
		  for (int j = 0; j < n; j++) {
			  s = 0.0;
			  for (int k = 0; k < n; k++) {
				  s = s + A[i + n * k] * B[k + n * j];
				  //cout << "A " << A[i + n * k] << " * B " << B[k + n * j] << endl;
			  }
			  C[i + j * ldc] = s;
		  }
	  }
  }


  //*********************************
  //Matrix Multiplication Row Major *
  //*********************************

  void MatrixMul_RowMajor(vector<double> &A, 
			  vector<double> &B, 
			  vector<double> &C, 
			  int n,
			  int numThreads)
  {
	  //lda, ldb, ldc are leading dimensions of matrices A,B and C
	  int lda = n;
	  int ldb = n;
	  int ldc = n;
	  double s = 0.0;

	  //int num_procs = omp_get_num_procs();
	  omp_set_num_threads(numThreads);

#pragma omp parallel for
	  for (int i = 0; i<n; i++) {
		  for (int j = 0; j<n; j++) {
			  s = 0.0;
			  for (int k = 0; k<n; k++) {
				  s = s + A[i * n + k] * B[n * k +j];
				  //cout << "A " << A[i + n * k] << " * B " << B[k + n * j] << endl;
			  }
			  C[i * ldc + j] = s;
		  }
	  }

  }

  //********************
  // helper functions  *
  //********************
  double fRand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
  }

  void randomizeMatrix(vector<double> &matrix, int n) {
    matrix.resize(n*n);
    int i;
    for (i=0;i<matrix.size();i++)
      matrix[i]=fRand(-1000,1000);
  }

  void randomizeArray(vector<int> &array, int n) {
    array.resize(n);

    for(int i=0;i<array.size();i++)
      array[i]=rand() % 1000000;
  }
}
