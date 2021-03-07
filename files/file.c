#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct atleta {
		char NOMBRE[50];
		char PAIS[30];
		int ORO;
		int PLATA;
		int BRONCE;
};
struct pais {
		char NOMBRE[30];
		int ORO;
		int PLATA;
		int BRONCE;
};

int main(){

    FILE * FP,*FA;
	struct atleta A;
	struct pais P,X;
	int cant = -1, medallas = -1;

    if ( (FP = fopen ("ATLETAS","rb")) == NULL ) {
        printf("\n\n Error apertura de archivo \n\n") ;
        exit(1);
    };
	if ( (FA = fopen ("PAISES","r+b")) == NULL ) {
        printf("\n\n Error apertura de archivo \n\n") ;
        exit(1);
    };
	// Punto 1

    printf("\n%-30s %20s %10s %10s %10s\n","NOMBRE","PAIS","ORO","PLATA","BRONCE");
	fread(&A,sizeof(A),1,FP);
	while(!feof(FP)){
        printf("\n %-30s %20s %10d %10d %10d",A.NOMBRE,A.PAIS,A.ORO,A.PLATA,A.BRONCE);
        fread(&A,sizeof(A),1,FP);
    }

    //Punto 2

    fseek(FP,0,0);
    fread(&P,sizeof(P),1,FA);
    X.BRONCE=0;
    X.ORO=0;
    X.PLATA=0;

	while(!feof(FA)){
        fread(&A,sizeof(A),1,FP);
        while(!feof(FP)){
             if(!strcmp(P.NOMBRE,A.PAIS)){
             X.BRONCE+=A.BRONCE;
             X.ORO+=A.ORO;
             X.PLATA+=A.PLATA;
             }
             fread(&A,sizeof(A),1,FP);
        }
        strcpy(X.NOMBRE,P.NOMBRE);
        fseek(FA, (long)-1*sizeof(X), 1);
        fwrite ( &X , sizeof(X) , 1 , FA );
        fseek(FP,0,0);
        fseek(FA, (long)0*sizeof(X), 1);
        X.BRONCE=0;
        X.ORO=0;
        X.PLATA=0;
        fread(&P,sizeof(P),1,FA);
    }

    fclose(FP);
    fclose(FA);

    //Punto 3
    if ( (FA = fopen ("PAISES","rb")) == NULL ) {
        printf("\n\n Error apertura de archivo \n\n") ;
        exit(1);}

    printf("\n\n\n%-30s %10s %10s %10s\n","NOMBRE","ORO","PLATA","BRONCE");
	fread(&P,sizeof(P),1,FA);
	while(!feof(FA)){
        printf("\n%-30s %10d %10d %10d",P.NOMBRE,P.ORO,P.PLATA,P.BRONCE);
        fread(&P,sizeof(P),1,FA);
    }

    //Punto 4
    rewind(FP);
    fread(&X,sizeof(X),1,FP);
    cant=X.ORO+X.PLATA+X.BRONCE;
    fseek(FP,0L,0);
    fread(&P,sizeof(P),1,FP);
    while(!feof(FP)){
        medallas=P.ORO+P.PLATA+P.BRONCE;
        if(cant<medallas){
            cant=medallas;
            strcpy(X.NOMBRE,P.NOMBRE);
        }
        fread(&P,sizeof(P),1,FP);
    }
    printf("\n\n\t\t %s (%d Medallas)", X.NOMBRE, cant);


    fclose(FA);

    printf("\n\nFin del programa");
    getchar();
    getchar();
    return 0;
}
