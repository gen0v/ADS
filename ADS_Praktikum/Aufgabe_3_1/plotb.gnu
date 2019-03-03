reset
set term pdf
set autoscale x
set autoscale y
set xlabel "n [-]"
set ylabel "t [s]"
set key top left
set out 'matrix_multiplication_results.pdf'
plot \
"matrix_colmajor_1b.txt" with linespoints title 'matrixmul\_colmajor\_singlethread',\
"matrix_rowmajor_1b.txt" with linespoints title 'matrixmul\_rowmajor\_singlethread',\
"matrix_colmajor_maxb.txt" with linespoints title 'matrixmul\_colmajor\_maxthreads',\
"matrix_rowmajor_maxb.txt" with linespoints title 'matrixmul\_rowmajor\_maxthreads',\