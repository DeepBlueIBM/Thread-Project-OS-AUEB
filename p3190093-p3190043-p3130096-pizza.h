#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

#define n_tel 3
#define n_cook 2
#define n_oven 10
#define n_deliverer 7
#define t_orderlow 1
#define t_orderhigh 5
#define n_orderlow 1
#define n_orderhigh 5
#define t_paymentlow 1
#define t_paymenthigh 2
#define c_pizza 10
#define p_fail 0.05
#define t_prep 1
#define t_bake 10
#define t_pack 2
#define t_dellow 5
#define t_delhigh 15
#define BILLION 1000000000L