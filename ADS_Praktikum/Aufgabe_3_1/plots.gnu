reset
set term pdf
#set autoscale x
set autoscale y
set xlabel "n [-]"
set ylabel "t [s]"
set key top left
set key font ",6"
set xtics font ",6"

set out 'sorting_algorithm_results.pdf'
set xrange [1000:1000000]
plot \
"heapsort.txt" with linespoints title 'Heapsort',\
"quicksort.txt" with linespoints title 'Quicksort',\
"mergesort.txt" with linespoints title 'Mergesort',\
"shellsort.txt" with linespoints title 'Shellsort',\

pause -1

set out 'matrix_multiplication_results.pdf'
set xrange [1:600]
plot \
"matrix_colmajor_1.txt" with linespoints title 'matrixmul\_colmajor\_singlethread',\
"matrix_rowmajor_1.txt" with linespoints title 'matrixmul\_rowmajor\_singlethread',\
"matrix_colmajor_max.txt" with linespoints title 'matrixmul\_colmajor\_maxthreads',\
"matrix_rowmajor_max.txt" with linespoints title 'matrixmul\_rowmajor\_maxthreads',\