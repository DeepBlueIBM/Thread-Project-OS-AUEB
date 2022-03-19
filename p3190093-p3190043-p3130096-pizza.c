#include "p3190093-p3190043-p3130096-pizza.h"

//Dhlwseis Global metavlitwn.

unsigned int sleep(unsigned int seconds);
unsigned int* seed;

struct timespec start;
struct timespec stop;

double max_time = -1;
double max_colding_time = -1;
double total_service_time = 0;
double max_service_time  = -1;
double max_customer_wait_time = -1;
double anamonh_time = 0;
double packet_time = 0;
double total_customer_wait_time =0;
double total_from_oven_time = 0;

int total_revenue;
int n_cust;
int n_fail=0;
int n_pass=0;
int n_available_tel = n_tel;
int n_available_cooks = n_cook;
int n_available_ovens = n_oven;
int n_available_packet = 1;
int n_available_deliverers = n_deliverer;

pthread_mutex_t lock;
pthread_cond_t cond;

//Function paraggelias.

void *main_thread(void *threadid) {

	//Dhlwseis main_thread.
	
	bool successfull_payment;
	
	int rc;
	int tid = (int) threadid;	
	int t_order;
	int t_payment_time;	
	int n_pizzas;
	
	double time_spent;
	double thread_time;
	double delivery_time;
	double customer_wait_time;
	double total_delivery_time;
	double from_oven_time = 0;
	

	
	rc = pthread_mutex_lock(&lock);
	if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_lock() is %d\n", rc);
		pthread_exit(&rc);
	}		
	clock_gettime(CLOCK_REALTIME, &start);
	
	//Perimene gia thlefwnites.	
	while (n_available_tel == 0) {
		rc = pthread_cond_wait(&cond, &lock);
		if (rc != 0) {	
			printf("ERROR: return code from pthread_cond_wait() is %d\n", rc);
			pthread_exit(&rc);
		}
	}
	
	clock_gettime(CLOCK_REALTIME, &stop);
	time_spent = (stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec)/BILLION;
	
	//Desmeush thlefwnith.
	n_available_tel --;
	
	rc = pthread_cond_signal(&cond);
	if (rc != 0) {	
		printf("ERROR: return code from pthread_cond_signal() is %d\n", rc);
		pthread_exit(&rc);
				}	
	rc = pthread_mutex_unlock(&lock);
	if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_unlock() is %d\n", rc);
		pthread_exit(&rc);
	}
	
	t_order = rand_r(&seed) % (t_orderhigh + 1 - t_orderlow) + t_orderlow;	
	sleep(t_order);
	
	thread_time= time_spent + t_order;
	customer_wait_time = thread_time;
	total_customer_wait_time += customer_wait_time;
	
	t_payment_time= rand_r(&seed) % (t_paymenthigh + 1 - t_paymentlow) + t_paymentlow;
	sleep(t_payment_time);
	
	thread_time = time_spent + t_payment_time;
	total_delivery_time += thread_time; 
	
	n_pizzas = rand_r(&seed) % (n_orderhigh + 1 - n_orderlow) + n_orderlow;
		
	successfull_payment=rand_r(&seed) % 100 / 100.0f > p_fail;
	
	//Elegxos epituxias ths paraggelias.
	
	if(!successfull_payment)
	{
		rc = pthread_mutex_lock(&lock);
	if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_lock() is %d\n", rc);
		pthread_exit(&rc);
	}		
		
		//Apodesmeush thlefwnith.
		n_available_tel++;
		n_fail++;
		
		//Meiwsh ncust gia swsto meso oro.
		n_cust--;
		printf("Η παραγγελία με αριθμό %d απέτυχε.\n",tid);
		rc = pthread_cond_signal(&cond);
	if (rc != 0) {	
		printf("ERROR: return code from pthread_cond_signal() is %d\n", rc);
		pthread_exit(&rc);
				}
		rc = pthread_mutex_unlock(&lock);
	if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_unlock() is %d\n", rc);
		pthread_exit(&rc);
	}
	}
	else
	{
		rc = pthread_mutex_lock(&lock);
	if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_lock() is %d\n", rc);
		pthread_exit(&rc);
	}
		printf("Η παραγγελία με αριθμό %d καταχωρήθηκε.\n",tid);
		//Apodesmeush thlefwnith.
		n_available_tel++;
		n_pass++;
		total_revenue = total_revenue + (c_pizza*n_pizzas);
		rc = pthread_cond_signal(&cond);
	if (rc != 0) {	
		printf("ERROR: return code from pthread_cond_signal() is %d\n", rc);
		pthread_exit(&rc);
				}
		rc = pthread_mutex_unlock(&lock);
	if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_unlock() is %d\n", rc);
		pthread_exit(&rc);
	}
	}	

	rc = pthread_mutex_lock(&lock);
	if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_lock() is %d\n", rc);
		pthread_exit(&rc);
	}
	clock_gettime(CLOCK_REALTIME, &start);
	
	//Perimene gia cooks.
	while (n_available_cooks == 0) {
		rc = pthread_cond_wait(&cond, &lock);
		if (rc != 0) {	
			printf("ERROR: return code from pthread_cond_wait() is %d\n", rc);
			pthread_exit(&rc);
		}
	}
	
	clock_gettime(CLOCK_REALTIME, &stop);
	time_spent = (stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec)/BILLION;
	
	//Desmeush cook.
	n_available_cooks --;
	rc = pthread_cond_signal(&cond);
	if (rc != 0) {	
		printf("ERROR: return code from pthread_cond_signal() is %d\n", rc);
		pthread_exit(&rc);
				}
	rc = pthread_mutex_unlock(&lock);
	if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_unlock() is %d\n", rc);
		pthread_exit(&rc);
	}
	
	sleep(t_prep*n_pizzas);
	
	//Ypologismos xronou.
	thread_time= time_spent + (t_prep * n_pizzas);
	total_delivery_time += thread_time;

	rc = pthread_mutex_lock(&lock);
	if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_lock() is %d\n", rc);
		pthread_exit(&rc);
	}
	clock_gettime(CLOCK_REALTIME, &start);
	
	//Perimene gia fournous.
	while (n_available_ovens < n_pizzas) {
		rc = pthread_cond_wait(&cond, &lock);
		if (rc != 0) {	
			printf("ERROR: return code from pthread_cond_wait() is %d\n", rc);
			pthread_exit(&rc);
		}
	}
	
	clock_gettime(CLOCK_REALTIME, &stop);
	time_spent = (stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec)/BILLION;
	
	//Desmeush fournwn.
	n_available_ovens = n_available_ovens - n_pizzas;
	//Apodesmeush cook.
	n_available_cooks ++;
	sleep(t_bake);
	rc = pthread_cond_signal(&cond);
	if (rc != 0) {	
		printf("ERROR: return code from pthread_cond_signal() is %d\n", rc);
		pthread_exit(&rc);
				}
	rc = pthread_mutex_unlock(&lock);
	if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_unlock() is %d\n", rc);
		pthread_exit(&rc);
	}
	
	//Ypologismos xronou.
	thread_time += time_spent + t_bake;
	total_delivery_time += thread_time;
	
	
	rc = pthread_mutex_lock(&lock);
	if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_lock() is %d\n", rc);
		pthread_exit(&rc);
	}
	clock_gettime(CLOCK_REALTIME, &start);
	
	//Perimene paketarisma.
	while (n_available_packet == 0) {
		rc = pthread_cond_wait(&cond, &lock);
		if (rc != 0) {	
			printf("ERROR: return code from pthread_cond_wait() is %d\n", rc);
			pthread_exit(&rc);
		}
	}
	
	clock_gettime(CLOCK_REALTIME, &stop);
	time_spent = (stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec)/BILLION;
	
	//Desmeush paketarismatos.
	n_available_packet--;
	rc = pthread_cond_signal(&cond);
	if (rc != 0) {	
		printf("ERROR: return code from pthread_cond_signal() is %d\n", rc);
		pthread_exit(&rc);
				}
	rc = pthread_mutex_unlock(&lock);
	if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_unlock() is %d\n", rc);
		pthread_exit(&rc);
	}
	
	sleep(t_pack);
	
	thread_time= time_spent + t_pack;
	
	//Apodesmeush paketarismatos.
	n_available_packet++;
	total_delivery_time += thread_time;
	
	rc = pthread_mutex_lock(&lock);
	if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_lock() is %d\n", rc);
		pthread_exit(&rc);
	}
	printf("Η παραγγελία με αριθμό %d ετοιμάστηκε σε %d λεπτά.\n",tid,(int) total_delivery_time);
	
	rc = pthread_cond_signal(&cond);
	if (rc != 0) {	
		printf("ERROR: return code from pthread_cond_signal() is %d\n", rc);
		pthread_exit(&rc);
				}
	rc = pthread_mutex_unlock(&lock);
	if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_unlock() is %d\n", rc);
		pthread_exit(&rc);
	}
	
	
	rc = pthread_mutex_lock(&lock);
	if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_lock() is %d\n", rc);
		pthread_exit(&rc);
	}
	clock_gettime(CLOCK_REALTIME, &start);
	
	//Perimene delivery.
	while (n_available_deliverers == 0) {
		rc = pthread_cond_wait(&cond, &lock);
		if (rc != 0) {	
			printf("ERROR: return code from pthread_cond_wait() is %d\n", rc);
			pthread_exit(&rc);
		}
	}
	
	clock_gettime(CLOCK_REALTIME, &stop);
	time_spent = (stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec)/BILLION;
	
	//Apodesmeush fournwn.
	n_available_ovens  = n_available_ovens + n_pizzas;
	
	//Desmeush delivery.
	n_available_deliverers --;
	rc = pthread_cond_signal(&cond);
	if (rc != 0) {	
		printf("ERROR: return code from pthread_cond_signal() is %d\n", rc);
		pthread_exit(&rc);
				}
	rc = pthread_mutex_unlock(&lock);
	if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_unlock() is %d\n", rc);
		pthread_exit(&rc);
	}	
	
	delivery_time = rand_r(&seed) % (t_delhigh + 1 - t_dellow) + t_dellow;
	thread_time += time_spent + delivery_time;
	total_delivery_time += time_spent + delivery_time;
	from_oven_time = delivery_time + t_prep + time_spent;
	total_from_oven_time += from_oven_time;
	
	sleep(2*delivery_time);

	rc = pthread_mutex_lock(&lock);
	if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_lock() is %d\n", rc);
		pthread_exit(&rc);
	}
	
	//Apodesmeush delivery.
	n_available_deliverers ++;
	printf("Η παραγγελία με αριθμό %d παραδόθηκε σε %d λεπτά.\n", tid, (int) total_delivery_time);
	
	if (thread_time > max_time) {
		max_time =  thread_time;
	}
	total_service_time += total_delivery_time;
	if (total_delivery_time > max_service_time) {
		max_service_time =  total_delivery_time;
	}
	if(from_oven_time > max_colding_time) {
		max_colding_time = from_oven_time;
	}
	if(customer_wait_time > max_customer_wait_time){
		max_customer_wait_time = customer_wait_time;
	}
	rc = pthread_cond_signal(&cond);
	if (rc != 0) {	
		printf("ERROR: return code from pthread_cond_signal() is %d\n", rc);
		pthread_exit(&rc);
				}
	rc = pthread_mutex_unlock(&lock);
	if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_unlock() is %d\n", rc);
		pthread_exit(&rc);
	}
	
	pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
	
	//Elegxos egkurwn parametrwn.
	if (argc != 3) {
		printf("Δώσατε λάθος αριθμό παραμέτρων.\n");
		exit(-1);
	}
	
	//Dhlwseis main.
	int rc;
	double next_order;
	n_cust = atoi(argv[1]);
	seed = atoi(argv[2]);
	int customer_id[n_cust];
	pthread_t threads[n_cust];
	rc = pthread_mutex_init(&lock, NULL);
	if (rc != 0) {
    		printf("ERROR: return code from pthread_mutex_init() is %d\n", rc);
       		exit(-1);
	}	
	rc = pthread_cond_init(&cond, NULL);
	if (rc != 0) {
    		printf("ERROR: return code from pthread_cond_init() is %d\n", rc);
       		exit(-1);
	}
	
	//Elegxos egkurou arithmou pelatwn.
    if(n_cust <0) {
        printf("Μη έγκυρος αριθμός πελατών.\n\n");
        exit(-1);
    	}	
	
	 printf("\nΚαλωσήρθατε στην πιτσαρία του ΟΠΑ. Σήμερα έχουμε %d πελάτες. Σε λίγο θα σας εξυπηρετήσουμε.\n\n", n_cust);
	
	//Dhmiourgia threads-pelatwn.
	for (int i = 0; i < n_cust; i++) {
		customer_id[i] = i + 1;
		rc = pthread_create(&threads[i], NULL, main_thread, customer_id[i]);
		if (rc != 0) {
    		printf("ERROR: return code from pthread_create() is %d\n", rc);
       		exit(-1);
	}
		next_order = rand_r(&seed) % (t_orderhigh + 1 - t_orderlow) + t_orderlow;
		sleep(next_order);
	}
	
	for (int i = 0; i < n_cust; i++) {
		rc = pthread_join(threads[i], NULL);
		if (rc != 0) {
			printf("ERROR: return code from pthread_join() is %d\n", rc);
			exit(-1);		
		}
	}
	
	//Ektupwseis othonhs.
	printf("Τα συνολικά έσοδα από τις πωλήσεις: %d ευρω.\n", total_revenue);
	printf("Tο πλήθος των επιτυχημένων παραγγελιών: %d .\n", n_pass);
	printf("Tο πλήθος των αποτυχημένων παραγγελιών: %d .\n", n_fail);
	printf("Μέσος χρόνος αναμονής των πελατών: %.2f λεπτά.\n", total_customer_wait_time/ n_cust);
	printf("Μέγιστος χρόνος αναμονής των πελατών: %d λεπτά.\n", (int) max_customer_wait_time);
	printf("Μέσος χρόνος  κρυώματος των παραγγελιών: %.2f λεπτά.\n", total_from_oven_time/ n_cust);
	printf("Μέγιστος χρόνος  κρυώματος των παραγγελιών: %d λεπτά.\n", (int) max_colding_time);
	printf("Μέσος χρόνος εξυπηρέτησης των πελατών: %.2f λεπτά.\n", total_service_time/ n_cust);
	printf("Μέγιστος χρόνος εξυπηρέτησης των πελατών: %d λεπτά.\n", (int) max_service_time);
	
	//Katastrofeis	
	pthread_mutex_destroy(&lock);
	if (rc != 0) {
		printf("ERROR: return code from pthread_mutex_destroy() is %d\n", rc);
		exit(-1);		
	}
	pthread_cond_destroy(&cond);
	if (rc != 0) {
		printf("ERROR: return code from pthread_cond_destroy() is %d\n", rc);
		exit(-1);		
	}

	return 0;

}