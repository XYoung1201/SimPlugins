#include "omp.h"

//set threads
omp_set_num_threads(4);
//record current time
omp_get_wtime();
//get thread num
omp_get_thread_num();
//get_total_thread_num
omp_get_num_threads();
//declare the content in each thread the number of which depends on iteration and the maximum iteration is the number of cores with some question.
#pragma omp parallel{...} 
//declar the for statement executing in each thread the number of which depends on iteration and the maximum iteration is the number of cores
#pragma omp parallel for 
//declar the for statement executing in threads of a specified number
#pragma omp parallel for num_threads(16) 
//make a sentance in a parallel scope run orderly
#pragma omp ordered

barrier
critical
single
master
ordered



