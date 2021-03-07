#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct producto { char nombre[40]; float precio; int ventas_mes[12]; };

#define CANT_PRODUCTOS 4

void inicializar (struct producto [], int);
void mostrar_ventas_anio(struct producto [], int , char []);
void mostrar_precio(struct producto [], int);
void mostrar_alfabetico(struct producto [], int);
float calcular_ventas_totales(struct producto [], int);
void mostrar_mas_vendido(struct producto [], int);

int main() {
	struct producto ventas[CANT_PRODUCTOS];
	float aux = 0.0;

	inicializar(ventas, CANT_PRODUCTOS);

	strcpy(ventas[0].nombre, "Arandela");
	ventas[0].precio = 1.5;
	ventas[0].ventas_mes[0] = 300;
	ventas[0].ventas_mes[5] = 100;
	ventas[0].ventas_mes[11] = 50;

	strcpy(ventas[1].nombre, "Tuerca");
	ventas[1].precio = 2.2;
	ventas[1].ventas_mes[0] = 200;
	ventas[1].ventas_mes[5] = 100;
	ventas[1].ventas_mes[11] = 50;

	strcpy(ventas[2].nombre, "Tornillo");
	ventas[2].precio = 3.5;
	ventas[2].ventas_mes[0] = 400;
	ventas[2].ventas_mes[5] = 200;
	ventas[2].ventas_mes[11] = 150;

	strcpy(ventas[3].nombre, "Tarugo");
	ventas[3].precio = 5.2;
	ventas[3].ventas_mes[0] = 500;
	ventas[3].ventas_mes[5] = 300;
	ventas[3].ventas_mes[11] = 250;

    mostrar_ventas_anio(ventas, CANT_PRODUCTOS, "Tornillo");
	mostrar_precio(ventas, CANT_PRODUCTOS);
	mostrar_alfabetico(ventas, CANT_PRODUCTOS);
	aux = calcular_ventas_totales(ventas, CANT_PRODUCTOS);
	printf("$ %.2f", aux);
	mostrar_mas_vendido(ventas, CANT_PRODUCTOS);

	return 0;
}

void inicializar (struct producto ventas[], int x){
	int i, j;

	for(i = 0; i < x; i++){
		for(j = 0; j < 12; j++){
			ventas[i].ventas_mes[j] = 0;
		}
	}
}

void mostrar_ventas_anio(struct producto ventas[], int x, char p[]){
	int i, j, acum = 0;

	for(i = 0; i < x; i++){
		for(j = 0; j < 12; j++){
			if(!strcmpi(p, ventas[i].nombre)){
				acum += ventas[i].ventas_mes[j];
			}
		}
	}
	printf("%s %d unidades", p, acum);
}

void mostrar_precio(struct producto ventas[], int x){
	int i, j;
	struct producto aux;

	for(i = 0; i < x - 1; i++){
		for(j = 0; j < x - i - 1; j++){
			if(ventas[j].precio < ventas[j + 1].precio){
				aux = ventas[j];
				ventas[j] = ventas[j + 1];
				ventas[j + 1] = aux;
			}
		}
	}

	printf("\n\n");

	for(i = 0; i < x; i++){
		printf("%s ", ventas[i].nombre);
	}
}

void mostrar_alfabetico(struct producto ventas[], int x){
	int i, j;
	struct producto aux;

	for(i = 0; i < x - 1; i++){
		for(j = 0; j < x - i - 1; j++){
			if(strcmpi(ventas[j].nombre, ventas[j + 1].nombre) > 0){
				aux = ventas[j];
				ventas[j] = ventas[j + 1];
				ventas[j + 1] = aux;
			}
		}
	}

	printf("\n\n");

	for(i = 0; i < x; i++){
		printf("%s ", ventas[i].nombre);
	}

	printf("\n\n");
}

float calcular_ventas_totales(struct producto ventas[], int x){
	int i, j, cant = 0;
	float total = 0;

	for(i = 0; i < x; i++){
		for(j = 0; j < 12; j++){
			cant += ventas[i].ventas_mes[j];
		}
		total += cant * ventas[i].precio;
		cant = 0;
	}

	return total;
}

void mostrar_mas_vendido(struct producto ventas[], int x){
	int i, j, mas, cant = 0,flag = 1;
	struct producto aux;

	for(i = 0; i < x; i++){
		for(j = 0; j < 12; j++){
			cant += ventas[i].ventas_mes[j];
		}
		if(flag){
			aux = ventas[i];
			mas = cant;
			cant = 0;
			flag = 0;
		}else if (cant > mas){
			aux = ventas[i];
			mas = cant;
			cant = 0;
		}else{
			cant = 0;
		}
	}

	printf("\n\n%s %d unidades", aux.nombre, mas);
}
