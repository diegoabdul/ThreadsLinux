#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <signal.h>
	using namespace std;
	int arreglo[100];
	pthread_mutex_t llave;
	int promedio;


void gotoxy(int x, int y){
	printf("\033[%d;%df",y,x);
}
void signalHandler(int signum)				//Espera a la terminacion de cada thread para imprimir 
											//el promedio de cada uno por parte del padre.
{

   if (signum == SIGUSR1){
      printf("%d",promedio);
		printf("\n");
		pthread_mutex_unlock(&llave);
 }
}
void *recorrer1(void *args){
	int i,x=0,y=5;
	pthread_mutex_lock(&llave);  //flag en la llave para restringir los hilos "semaforo"
	for(i=0;i<(25);i++){
		y++;
		fflush(stdout);
		gotoxy(x,y);
		printf("%d",arreglo[i]);
		sleep(1);
		promedio=arreglo[i]+promedio;
	}
		promedio=promedio/25;
	gotoxy(40,108);
	printf("El Promedio del Hilo 1 es: ");
	kill(getpid(), SIGUSR1);
}
void *recorrer2(void *args){
	int i,x=5,y=5;
	pthread_mutex_lock(&llave);  //flag en la llave para restringir los hilos "semaforo"
	for(i=25;i<(50);i++){
		y++;
		fflush(stdout);
		gotoxy(x,y);
		printf("%d",arreglo[i]);
		sleep(1);
		promedio=arreglo[i]+promedio;
	}
		promedio=promedio/25;
	gotoxy(40,107);
	printf("El Promedio del Hilo 2 es: ");
	kill(getpid(), SIGUSR1);
}
void *recorrer3(void *args){
	int i,x=10,y=5;
	pthread_mutex_lock(&llave);  //flag en la llave para restringir los hilos "semaforo"
	for(i=50;i<(75);i++){
		y++;
		fflush(stdout);
		gotoxy(x,y);
		printf("%d",arreglo[i]);
		sleep(1);
		promedio=arreglo[i]+promedio;
	}
		promedio=promedio/25;
	gotoxy(40,106);
	printf("El Promedio del Hilo 3 es: ");
	kill(getpid(), SIGUSR1);
}
void *recorrer4(void *args){
	int i,x=15,y=5;
	pthread_mutex_lock(&llave);  //flag en la llave para restringir los hilos "semaforo"
	for(i=75;i<(100);i++){
		y++;
		fflush(stdout);
		gotoxy(x,y);
		printf("%d",arreglo[i]);
		sleep(1);
		promedio=arreglo[i]+promedio;
	}
	promedio=promedio/25;
	gotoxy(40,105);
	printf("El Promedio del Hilo 4 es: ");
	kill(getpid(), SIGUSR1);
	
}



int main(int argc,char const *argv[]){
	int i, j;
    srand (time(NULL));
    for (i=0; i<=100; i++) {
        arreglo[i] = rand()%1001;
    }
	pthread_t hilo1;//Inicializando cada thread
	pthread_t hilo2;
	pthread_t hilo3;
	pthread_t hilo4;
	pthread_mutex_init(&llave,NULL);  //inicializando la llave
	pthread_create(&hilo1,NULL,recorrer1,NULL);
	pthread_create(&hilo2,NULL,recorrer2,NULL);
	pthread_create(&hilo3,NULL,recorrer3,NULL);
	pthread_create(&hilo4,NULL,recorrer4,NULL);


	signal(SIGUSR1, signalHandler);				//Al terminar cada thread se envia una señal para la 
												//impresion de su promedio controladamente por parte del padre.

	pthread_join(hilo1,NULL); //espera la terminacion del thread
	
	signal(SIGUSR1, signalHandler);
	pthread_join(hilo2,NULL); //espera la terminacion del thread
	
	signal(SIGUSR1, signalHandler);
	pthread_join(hilo3,NULL); //espera la terminacion del thread
	


	signal(SIGUSR1, signalHandler);
	pthread_join(hilo4,NULL); //espera la terminacion del thread
	
	return 0;
}