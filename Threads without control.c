#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <signal.h>
using namespace std;
	int arreglo[100];
	int promedioHilo1,promedioHilo2,promedioHilo3,promedioHilo4,promedioTotal;


void gotoxy(int x, int y){			//Funcion que se utiliza para "imprimir" los hilos de manera organizada
	printf("\033[%d;%df",y,x);
}

void *recorrer1(void *args){    //Primer Hilo
	int i,x=0,y=5; 
	for(i=0;i<(25);i++){
		y++;
		fflush(stdout);
		gotoxy(x,y);
		printf("%d",arreglo[i]);     //Impresion del Hilo
		sleep(1);
		promedioHilo1=arreglo[i]+promedioHilo1; //Se va recopilando para hacer el promedio
	}
		promedioHilo1=promedioHilo1/25;
	gotoxy(40,108);
	printf("El Promedio del Hilo 1 es: ");
	printf("%d",promedioHilo1);
	printf("\n");
}
void *recorrer2(void *args){
	int i,x=5,y=5;
		for(i=25;i<(50);i++){
		y++;
		fflush(stdout);
		gotoxy(x,y);
		printf("%d",arreglo[i]);
		sleep(1);
		promedioHilo2=arreglo[i]+promedioHilo2;
	}
		promedioHilo2=promedioHilo2/25;
	gotoxy(40,107);
	printf("El Promedio del Hilo 2 es: ");
	printf("%d",promedioHilo2);
	printf("\n");
}
void *recorrer3(void *args){
	int i,x=10,y=5;
	for(i=50;i<(75);i++){
		y++;
		fflush(stdout);
		gotoxy(x,y);
		printf("%d",arreglo[i]);
		sleep(1);
		promedioHilo3=arreglo[i]+promedioHilo3;
	}
		promedioHilo3=promedioHilo3/25;
	gotoxy(40,106);
	printf("El Promedio del Hilo 3 es: ");
	printf("%d",promedioHilo3);
	printf("\n");
}
void *recorrer4(void *args){
	int i,x=15,y=5;
	for(i=75;i<(100);i++){
		y++;
		fflush(stdout);
		gotoxy(x,y);
		printf("%d",arreglo[i]);
		sleep(1);
		promedioHilo4=arreglo[i]+promedioHilo4;
	}
	promedioHilo4=promedioHilo4/25;
	gotoxy(40,105);
	printf("El Promedio del Hilo 4 es: ");
	printf("%d",promedioHilo4);
	printf("\n");
	
}



int main(int argc,char const *argv[]){
	int i, j;
    srand (time(NULL));
    for (i=0; i<=100; i++) {         //Se llena el arreglo de manera aleatoria
        arreglo[i] = rand()%1001;
    }
	pthread_t hilo1;
	pthread_t hilo2;
	pthread_t hilo3;
	pthread_t hilo4;

	pthread_create(&hilo1,NULL,recorrer1,NULL);   //Se hace la creacion de cada hilo y su asignacion
	pthread_create(&hilo2,NULL,recorrer2,NULL);
	pthread_create(&hilo3,NULL,recorrer3,NULL);
	pthread_create(&hilo4,NULL,recorrer4,NULL);


	pthread_join(hilo1,NULL); //espera la terminacion del thread
	
	pthread_join(hilo2,NULL); //espera la terminacion del thread
	
	pthread_join(hilo3,NULL); //espera la terminacion del thread
	

	pthread_join(hilo4,NULL); //espera la terminacion del thread

	promedioTotal=(promedioHilo1+promedioHilo2+promedioHilo3+promedioHilo4)/4;  //Al terminar los hilos se saca el 
	gotoxy(40,106);                                                            	//promedio por parte del padre
	printf("El Promedio de todos los Hilos es: ");
	printf("%d",promedioTotal);													//Se devuelve el promedio
	printf("\n");
	return 0;
}