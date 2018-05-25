reset
set term pdf
set autoscale x
set autoscale y
set xlabel "n [-]"
set ylabel "t [s]"
set key top left
set out "algos.pdf"
plot \
"quicksort.txt" with linespoints title 'Quicksort',\
"mergesort.txt" with linespoints title 'Mergesort',\
"shellsort.txt" with linespoints title 'Shellsort',\
"heapsort.txt" with linespoints title 'Heapsort',\
