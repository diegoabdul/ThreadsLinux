#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/resource.h>

pthread_t hilo1;//Inicializando cada thread
pthread_t hilo2;
pthread_t hilo3;
pthread_t hilo4;
int tiempo;
int tiempoej;
int volumen;
int caudal=3;
int caudalvaci=7;
int umbral=10;
int peligro=12;
pthread_mutex_t llave;


void *reloj(void *args){
	pthread_mutex_lock(&llave);
	printf("Introduzca un tiempo para el reloj \n");
	scanf("%i",&tiempo);

	tiempoej=tiempo*10;
	pthread_mutex_unlock(&llave);
	
}

void *llenado(void *args){
	
	while(tiempo<tiempoej){
		pthread_mutex_lock(&llave);
		volumen=volumen+caudal;
		printf( "Llenado: volumen = " "%d\n",volumen );
		tiempo++;
		pthread_mutex_unlock(&llave);
		sleep(1);
	}
	pthread_exit(NULL);
}

void *controldep(void *args){
	setpriority(PRIO_PROCESS,0,19);
	while(tiempo<tiempoej){
		if (volumen>umbral){
			pthread_mutex_lock(&llave);
			volumen=volumen-caudalvaci;
			printf( "Contro: he reducido el volumen a " "%d\n",volumen );
			tiempo++;
			pthread_mutex_unlock(&llave);
			sleep(2);
		}
		}
	}

void *alarma(void *args){
	setpriority(PRIO_PROCESS,0,-20);
	while(tiempo<tiempoej){
		if (volumen>peligro)
		{
			printf( "Alarma: cuidado, el volumen es " "%d\n",volumen );
			sleep(1);
		}
	}
	
}


int main(int argc,char const *argv[]){
	
	pthread_mutex_init(&llave,NULL);  //inicializando la llave

	pthread_create(&hilo1,NULL,reloj,NULL);
	pthread_join(hilo1,NULL);
	pthread_create (&hilo2, NULL, llenado,NULL);
	
	pthread_create (&hilo3, NULL, controldep, NULL);
	
	pthread_create (&hilo4, NULL, alarma, NULL);
	pthread_join(hilo2,NULL);
	//pthread_join(hilo3,NULL);
	//pthread_join(hilo4,NULL);
	//pthread_exit (NULL);

	

	
	return 0;
}