#include <iostream>
#include <fstream> 
#include <iomanip> 
#include <vector>
#include <omp.h>
#include "MyAlgorithms.h"

using namespace std;

void printArray(vector<double> arraya) {
	for (double a : arraya) {
		std::cout << a << "\n";
	}
}

int main(int argc, char** argv) {

  //***************
  // file streams *
  //***************
  ofstream quicksort;
  ofstream mergesort;
  ofstream heapsort;
  ofstream shellsort;

  ofstream matrix_rowmajor_1;
  ofstream matrix_rowmajor_max;
  ofstream matrix_colmajor_1;
  ofstream matrix_colmajor_max;

  ofstream matrix_rowmajor_1b;
  ofstream matrix_rowmajor_maxb;
  ofstream matrix_colmajor_1b;
  ofstream matrix_colmajor_maxb;

  quicksort.open("quicksort.txt", ios::out | ios::app);
  mergesort.open("mergesort.txt", ios::out | ios::app);
  heapsort.open("heapsort.txt", ios::out | ios::app);
  shellsort.open("shellsort.txt", ios::out | ios::app);

  matrix_rowmajor_1.open("matrix_rowmajor_1.txt", ios::out | ios::app);
  matrix_rowmajor_max.open("matrix_rowmajor_max.txt", ios::out | ios::app);
  matrix_colmajor_1.open("matrix_colmajor_1.txt", ios::out | ios::app);
  matrix_colmajor_max.open("matrix_colmajor_max.txt", ios::out | ios::app);

  matrix_rowmajor_1b.open("matrix_rowmajor_1b.txt", ios::out | ios::app);
  matrix_rowmajor_maxb.open("matrix_rowmajor_maxb.txt", ios::out | ios::app);
  matrix_colmajor_1b.open("matrix_colmajor_1b.txt", ios::out | ios::app);
  matrix_colmajor_maxb.open("matrix_colmajor_maxb.txt", ios::out | ios::app);

  
  //******************** 
  //benchmark settings *
  //********************
  
  double dtime;
  int n_start = 800;
  int n_step = 11;
  int n_end = 1800;
  //int n_end = 1000000;
  int numThreads = 1; //only for matrix multiplication

  //********************************************************************
  //data structures for sorting algorithms (int) and matrices (double) *
  //********************************************************************
 
  vector<int> array,temp_array;
  vector<double> A,B,C; 


  //********************************************************
  //benchmark main loop (run only ONE algorithm at a time) *
  //********************************************************

  for (int n = n_start; n<n_end; n+=n_step) {    
    cout << "n: " << n << endl;

    //***************************************
    //init data structure with random values*
    //***************************************
    
    //sorting algorithms
    //MyAlgorithms::randomizeArray(array,n);
	
    //matrix multiplication
	/*
	vector<double> A;
	vector<double> B;
	A.push_back(1);
	A.push_back(3);
	A.push_back(2);
	A.push_back(4);
	
	B.push_back(5);
	B.push_back(7);
	B.push_back(6);
	B.push_back(8);

	A.push_back(1);
	A.push_back(2);
	A.push_back(3);
	A.push_back(4);

	B.push_back(5);
	B.push_back(6);
	B.push_back(7);
	B.push_back(8);

	vector<double> C(4);
	*/

    //if (n>800) { n_step=11; }
    MyAlgorithms::randomizeMatrix(A,n);
	//cout << "-A-\n";
	//printArray(A);
    MyAlgorithms::randomizeMatrix(B,n);
	//cout << "-B-\n";
	//printArray(B);
    C.resize(n*n);
	//cout << "-C-\n";
	//break;
   
	//****************
    //  start clock  *
    //**************** 
    dtime = omp_get_wtime();
	
    //**********************
    //  execute algorithm  *
    //**********************
	MyAlgorithms::MatrixMul_ColMajor(A, B, C, n, numThreads);
	//MyAlgorithms::MatrixMul_RowMajor(A, B, C, n, numThreads);
	//printArray(C);
	//for (int a : array) {
	//	std::cout << a << "|";
	//}

    //MyAlgorithms::QuickSort(array,0,array.size()-1);
	//MyAlgorithms::MergeSort(array, 0, array.size()-1);
	//MyAlgorithms::HeapSort(array, array.size());
	//MyAlgorithms::ShellSortHibbard(array, array.size());
	
	//break;
	//MyAlgorithms::ShellSort(array, array.size());
	/*
	for (int a = 0; a < array.size();a++) {
		std::cout << array[a] << "|";
	}
	break;
	*/
    //***************
    //  stop clock  *
    //***************
    dtime = omp_get_wtime() - dtime;    
    
    //*************************
    //  write results to file *
    //*************************
    //quicksort << n << "\t" << setprecision(10) << scientific << dtime << endl;
	//mergesort << n << "\t" << setprecision(10) << scientific << dtime << endl;
	//heapsort << n << "\t" << setprecision(10) << scientific << dtime << endl;
	//shellsort << n << "\t" << setprecision(10) << scientific << dtime << endl;

	//matrix_rowmajor_1 << n << "\t" << setprecision(10) << scientific << dtime << endl;
	//matrix_rowmajor_max << n << "\t" << setprecision(10) << scientific << dtime << endl;
	//matrix_colmajor_1 << n << "\t" << setprecision(10) << scientific << dtime << endl;
	//matrix_colmajor_max << n << "\t" << setprecision(10) << scientific << dtime << endl;

	//matrix_rowmajor_1b << n << "\t" << setprecision(10) << scientific << dtime << endl;
	//matrix_rowmajor_maxb << n << "\t" << setprecision(10) << scientific << dtime << endl;
	matrix_colmajor_1b << n << "\t" << setprecision(10) << scientific << dtime << endl;
	//matrix_colmajor_maxb << n << "\t" << setprecision(10) << scientific << dtime << endl;
  } 

  //**********************
  //  close file handles *
  //**********************
  system("PAUSE");
  quicksort.close();
  mergesort.close();
  heapsort.close();
  shellsort.close();
  matrix_rowmajor_1.close();
  matrix_rowmajor_max.close();
  matrix_colmajor_1.close();
  matrix_colmajor_max.close();
  matrix_rowmajor_1b.close();
  matrix_rowmajor_maxb.close();
  matrix_colmajor_1b.close();
  matrix_colmajor_maxb.close();
}

