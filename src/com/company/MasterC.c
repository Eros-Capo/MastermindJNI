#include<jni.h>
#include "com_company_MetodiNativi.h" //Header contenente le definizioni delle funzioni java
#include<stdio.h>
#include<stdlib.h>

//Definizione delle costanti richiamando il preprocessore per risparmiare memoria 
#define ARRAY_LENGHT 4
#define MIN_VAL 0
#define MAX_VAL 9

// Funzione Nativa di tipo jintArray (In quanto restituirà un array java, in ingresso riceve il puntatore alla struttura contenente i puntatori alle funzioni JNI e la classe java a cui appartiene)
JNIEXPORT jintArray JNICALL Java_com_company_MetodiNativi_CreateCode(JNIEnv *env, jclass ThisClass){
  	int codice[ARRAY_LENGHT];
  	srand(time(NULL)); //Inizializzazione del generatore di numeri casuali
  	int i;
  	//Ciclo for che riempie un array con numeri random compresi tra 0 e 9 (modMAX_VAL+1)
    for(i=0;i<ARRAY_LENGHT;i++){
        codice[i] = (rand()%MAX_VAL+1);
	}
	setbuf(stdout, NULL); //Inizializzazione del buffer output
	printf("Il codice **** e\' stato creato utilizza i tuoi 10 tentativi per romperlo!\n");
	fflush(stdout); //Svuotamento del buffer
	//Dichiarazione di un array di tipo java
	jintArray codi;
	//Creazione dell'array che verrà restituito richiamando un metodo appartenente alla JNI tramite (*env)->NewIntArray
	codi=(*env)->NewIntArray(env,ARRAY_LENGHT);
	//TEST per verificare la creazione dell'array
	if(codi==NULL){
		return NULL;
	}
	//Dichiarazione di un java array di interi temporaneo utilizzato per lo scambio di contenuto con l'array C 
	jint temp[ARRAY_LENGHT];
	//Riempimento array temporaneo
	for(i=0;i<ARRAY_LENGHT;i++){
		temp[i]=codice[i];
	}
	//Copia dell'array temporaneo nel array che verrà restituito
	(*env)->SetIntArrayRegion(env, codi, 0, ARRAY_LENGHT, temp);
	return codi;
  }
  
// Funzione Nativa di tipo jintArray (In quanto restituirà un array java, in ingresso riceve il puntatore alla struttura contenente i puntatori alle funzioni JNI e la classe java a cui appartiene)
JNIEXPORT jintArray JNICALL Java_com_company_MetodiNativi_UserInput(JNIEnv *env, jclass ThisClass){
	int CodiceInserito[ARRAY_LENGHT];
	int i;
	//Input del codice inserito dall'utente salvato in un array con controllo inserimento
	for(i=0;i<ARRAY_LENGHT;i++){
		printf("Inserisci la %d cifra del tuo codice! Deve essere un intero compreso tra 0 e 9\n",i);
		fflush(stdout);
		while(scanf("%d",&CodiceInserito[i])!=1 || CodiceInserito[i]<MIN_VAL || CodiceInserito[i]>MAX_VAL){
			printf("Inserisci un intero compreso tra 0 e 9\n");
			while(getchar() != '\n'); //flush dello stdin in modo da non lasciare caratteri nel buffer
		}
	}
	//Stampa codice inserito
	printf("Il numero da te inserito e\':\t");
	for(i=0;i<ARRAY_LENGHT;i++){
		printf("%d",CodiceInserito[i]);
	}
	printf("\n");
	//Dichiarazione di un array di tipo java
	jintArray cod;
	//Creazione dell'array che verrà restituito richiamando un metodo appartenente alla JNI tramite (*env)->NewIntArray
	cod=(*env)->NewIntArray(env,ARRAY_LENGHT);
	//TEST per verificare la creazione dell'array
	if(cod==NULL){
		return NULL;
	}
	//Dichiarazione di un java array di interi temporaneo utilizzato per lo scambio di contenuto con l'array C
	jint temp[ARRAY_LENGHT];
	//Riempimento array temporaneo
	for(i=0;i<ARRAY_LENGHT;i++){
		temp[i]=CodiceInserito[i];
	}
	//Copia dell'array temporaneo nel array che verrà restituito
	(*env)->SetIntArrayRegion(env, cod, 0, ARRAY_LENGHT, temp);
	return cod;
}

// Funzione Nativa di tipo jint (In quanto restituirà un intero java, in ingresso riceve il puntatore alla struttura contenente i puntatori alle funzioni JNI, la classe java a cui appartiene e due java array)
JNIEXPORT jint JNICALL Java_com_company_MetodiNativi_Controllo(JNIEnv *env, jclass ThisClass, jintArray codice, jintArray codUtente){
	int i;
	int cod[ARRAY_LENGHT], InsertedCod[ARRAY_LENGHT];
	//Dichiarazione di due puntatori java interi  utilizzati per accedere agli elementi dei Java array ottenuti in ingresso
	jint *p=(*env)->GetIntArrayElements(env,codice,0);
	jint *pun=(*env)->GetIntArrayElements(env,codUtente,0);
	//Due cicli utilizzati per riempire gli array C con gli elementi dei Java array passati alla funzione
	for(i=0;i<ARRAY_LENGHT;i++){
		cod[i]=p[i];
	}
	for(i=0;i<ARRAY_LENGHT;i++){
		InsertedCod[i]=pun[i];
	}
	//Rilascio della memoria allocata per il contenuto degli array (In quanto non presente il Garbage Collector dobbiamo liberare la memoria)
	(*env)->ReleaseIntArrayElements(env, codice, p, JNI_ABORT);
	(*env)->ReleaseIntArrayElements(env, codUtente, pun, JNI_ABORT);
	
	int corretti = 0; //Quantita' di numeri corretti nella posizione corretta
    int PosDiverse = 0; //Quantita' di numeri corretti nella posizione errata  
	int errati = 0; //Quantita' di numeri errati
	//Dichiarazione di due array utilizzati per definire il numero di elementi corretti in posizione errata ed errati
	int PosizioniDiverse[ARRAY_LENGHT];
    int controllo[ARRAY_LENGHT];
    int k,h;
    //Ciclo for utilizzato per eliminare le celle in cui il codice è corretto e in posizione corretta
    for(k=0;k<ARRAY_LENGHT;k++){
        if(InsertedCod[k]==cod[k]){
        	corretti++; // Incremento i numeri corretti trovati
			PosizioniDiverse[k] = 10; 
			controllo[k] = 11; 
       }else{
	   		PosizioniDiverse[k] = cod[k];
			controllo[k] = InsertedCod[k];
        }
    }
    //Se i numeri sono tutti corretti ritorna 1 (Vittoria)
    if(corretti==ARRAY_LENGHT){
    	return 1;
	}
	//Ciclo for utilizzato per determinare il numero di numeri errati e corretti in posizioni diverse
	for(k=0;k<ARRAY_LENGHT;k++){
    	for(h=0;h<ARRAY_LENGHT;h++){
    		if(controllo[k]==PosizioniDiverse[h]){
            	PosizioniDiverse[h] = 99; 
				PosDiverse++;
        	}
    	}
	}

	errati=ARRAY_LENGHT-(corretti+PosDiverse);
	printf("I numeri indovinati sono %d, quelli corretti ma in posizione errata sono  %d e quelli errati sono %d\n\n",corretti, PosDiverse, errati);
	fflush(stdout);
	//Ritorno 0 nel caso in cui il tentativo dell'utente non sia andato a buon fine
	return 0;
}
