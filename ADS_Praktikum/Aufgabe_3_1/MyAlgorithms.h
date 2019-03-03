#ifndef _MYALGORITHMS_H_
#define _MYALGORITHMS_H_

#include <vector>
#include <iostream>

using namespace std;

namespace MyAlgorithms {
  
  //************
  // QuickSort *
  //************
  void QuickSort(vector<int> &arr, int left, int right);
  int part(vector<int> &a, int left, int right);
  //************
  // MergeSort *
  //************
  void MergeSort(vector<int> &a ,int low, int high);
  void merge(vector<int> &temp, int low, int mid, int high);
  //************
  // Heapsort  *
  //************
  void HeapSort(vector<int> &a, int n);
  void maxHeap(vector<int> &a, int i, int size);
  //************
  // Shellsort *
  //************
  void ShellSort(vector<int> &a, int n);
  void ShellSortHibbard(vector<int> &a, int n);

 
  //************************************
  //Matrix Multiplikation Column Major *
  //************************************

  void MatrixMul_ColMajor(vector<double> &A, 
			  vector<double> &B, 
			  vector<double> &C, 
			  int n, 
			  int numThreads);

  //*********************************
  //Matrix Multiplikation Row Major *
  //*********************************

  void MatrixMul_RowMajor(vector<double> &A, 
			  vector<double> &B, 
			  vector<double> &C, 
			  int n,
			  int numThreads);

  //********************
  // helper functions  *
  //********************

  double fRand(double fMin, double fMax);
  void randomizeMatrix(vector<double> &matrix, int n);   //fills vector<double> with n*n random double values
  void randomizeArray(vector<int> &array, int n);   //fills vector<int> with n random integer values
  
}
#endif 
