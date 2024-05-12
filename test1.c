#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>

#define MAX_WAITING_CHAIRS 5

/* Mutex */
pthread_mutex_t mutex;

/* Semaphores */
sem_t barber_ready;
sem_t customer_ready;
sem_t modifySeats;

int available_seats = MAX_WAITING_CHAIRS;
int served_customers = 0;
int total_customers = MAX_WAITING_CHAIRS;
int customer_number=0;
int all_customers_served=0,total_time_worked=0;

void *barber_function(void *arg);
void *customer_function(void *arg);

void serve_customer() {
     
    int service_time = (rand() % 3) + 1;
    total_time_worked+=service_time;
    printf("\nServing customer \n");
    sleep(service_time);
}

void *barber_function(void *arg) {

    while ( all_customers_served==0) {
        /* Wait for a customer to arrive */
        sem_wait(&customer_ready); 
        /* Signal that the barber is ready */
        sem_post(&barber_ready);
        serve_customer();
        
        printf("\nBarber served  customer .\n");
        pthread_mutex_lock(&mutex);

        served_customers++;
        available_seats++;
 
       printf("\nServed customers: %d. Available seats: %d  \n", served_customers, available_seats);
     
        pthread_mutex_unlock(&mutex);
      
    }
      printf("\nAll customers have been served or have left. Barber thread exiting.\n");
    pthread_exit(NULL);
}

void *customer_function(void *arg) {
     customer_number = *(int *)arg;

    /* Lock mutex for updating shared variables */
    pthread_mutex_lock(&mutex);

    /* Increment total customers */
    total_customers++;

    /* Check if there are available seats */
    if (available_seats > 0) {
        /* Occupy a waiting seat */
        available_seats--;
        printf("\nCustomer %d arrived. Available seats: %d", customer_number, available_seats);
        if(available_seats==0)
        {
        	printf(" (No more seats available!!)\n");
		}
        /* Signal that a customer is ready */
        sem_post(&customer_ready);

        /* Unlock mutex */
        pthread_mutex_unlock(&mutex);

        /* Wait for the barber to be ready */
        sem_wait(&barber_ready);
        //printf("\nCustomer %d is being served.\n", customer_number);
    } else {
        /* Unlock mutex */
        pthread_mutex_unlock(&mutex);

        /* No available seats, customer leaves */
        printf("\nCustomer %d arrived, but no available seats. Customer %d has left.\n", customer_number, customer_number);
    }

    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));

    int num_customers;
    printf("ENTER THE NUMBER OF CUSTOMERS: ");
    scanf("%d", &num_customers);
    

    total_customers=num_customers;
    /* Initialize mutex and semaphores */
    pthread_mutex_init(&mutex, NULL);
    sem_init(&barber_ready, 0, 0);
    sem_init(&customer_ready, 0, 0);

    /* Create barber thread */
    pthread_t barber_thread;
    int barber_id = 0;  // Barber has ID 0
    if (pthread_create(&barber_thread, NULL, barber_function, &barber_id) != 0) {
        perror("Failed to create barber thread");
        exit(EXIT_FAILURE);
    }

    /* Create customer threads */
    pthread_t *customer_threads = malloc(num_customers * sizeof(pthread_t));
    int *customer_ids = malloc(num_customers * sizeof(int));
    if (customer_threads == NULL || customer_ids == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < num_customers; i++) {
        customer_ids[i] = i + 1;  // Customer IDs start from 1
        if (pthread_create(&customer_threads[i], NULL, customer_function, &customer_ids[i]) != 0) {
            perror("Failed to create customer thread");
            exit(EXIT_FAILURE);
        }

        /* Sleep to simulate arrival interval */
        sleep(rand() % 3);
    }


    /* Join customer threads */
    for (int i = 0; i < num_customers; i++) {
        pthread_join(customer_threads[i], NULL);
    }


 all_customers_served = 1;

    /* Join barber thread */
    pthread_join(barber_thread, NULL);
    
    printf("Total Time Served by Barber: %d",total_time_worked);
    
    /* Cleanup */
    pthread_mutex_destroy(&mutex);
    sem_destroy(&barber_ready);
    sem_destroy(&customer_ready);
    free(customer_threads);
    free(customer_ids);

    return 0;
}
