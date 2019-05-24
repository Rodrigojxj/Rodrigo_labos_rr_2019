#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include<stdio.h>
#include<stdlib.h>

#define CADEIRA 5
#define TRUE 1

sem_t CLIENTES;
sem_t BARBEIROS;
sem_t mutex;

int esperando = 0;

void* barbeiro(void* arg);
void* cliente(void* arg);
void corte_de_cabelo();
void cliente_chegou();
void cortar_cabelo();
void desistiu_de_cortar();

int main(){
	sem_init(&CLIENTES, TRUE, 0);
	sem_init(&BARBEIROS, TRUE, 0);
	sem_init(&mutex, TRUE, 1);

	pthread_t b, c;

	pthread_create(&b, NULL, barbeiro, NULL);

	while(TRUE){
		pthread_create(&c, NULL, cliente, NULL);
		usleep(1);
	}
	return 0;
}

void* barbeiro(void* arg){
	while(TRUE){
		sem_wait(&CLIENTES);
		sem_wait(&mutex);
		esperando--;
		sem_post(&BARBEIROS);
		sem_post(&mutex);
		corte_de_cabelo();
	}
	pthread_exit(NULL);
}

void* cliente(void* arg){
	sem_wait(&mutex);
	if(esperando < CADEIRA){
		cliente_chegou();
		esperando++;
		sem_post(&CLIENTES);
		sem_post(&mutex);
		sem_wait(&BARBEIROS);
		cortar_cabelo();
	}else{
		sem_post(&mutex);
		desistiu_de_cortar();
	}
	pthread_exit(NULL);
}

void corte_de_cabelo(){
	printf("Barbeiro esta cortando o cabelo de um cliente\n");
	usleep(3);
}
void cliente_chegou(){
	printf("Cliente chegou para cortar o cabelo\n");
}
void cortar_cabelo(){
	printf("Cabelo do cliente esta sendo cortado\n");
}
void desistiu_de_cortar(){
	printf("Cliente foi embora, salao cheio\n");
}
