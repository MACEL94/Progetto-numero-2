/***************************************************/
/* Progetto per la sessione estiva del 2014/2015 */
/***************************************************/

/*****************************/
/* inclusione delle librerie */
/*****************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/********************************/
/* dichiarazione delle funzioni */
/********************************/

int acquisisci_insieme(void);
void crea_insieme_vuoto(void);

/*****************/
/* funzione main */
/*****************/

int main(){
	int scelta,
		lettura_effettuata;
		
	//inizializzo le variabili
	scelta=0;
	lettura_effettuata=0;
	
	
	printf(" Questo programma acquisisce nel seguente ordine: \n\n 1) Un insieme; ");
	printf(" \n 2) Una relazione binaria su quell'insieme; \n 3) Un'operazione binaria");
	printf(" su quell'insieme.\n\n Poi verifica se l'insieme e' chiuso rispetto all'operazione");
	printf(" e se la relazione\n e' una congruenza rispetto all'operazione.\n");
	printf("\n Digitare:\n 1 se si vuole iniziare con l'acquisizione dell'insieme,\n 2 se si vuole");
	printf(" inserire l'insieme vuoto,\n 3 terminare il programma: ");
	while((scelta != 1 && scelta != 2 && scelta != 3) || lettura_effettuata != 1)
		lettura_effettuata = scanf("%d",&scelta);
	if(scelta==1)
		acquisisci_insieme();
	if(scelta==2)
		crea_insieme_vuoto();
	else
	return 0;
}


/*****************************/
/* acquisizione dell'insieme */
/*****************************/

int acquisisci_insieme(){
	int 	i,							//variabile contatore
			finisci_di_acquisire,		//variabile per terminare l'acquisizione
			dimensione;					//variabile per la dimensione dell'array
	
	//inizializzo le variabili
	
	i = 0;
	dimensione=50;
	finisci_di_acquisire = 0;
	
	//dichiaro l'array insieme
	
	int *insieme;							
	
	//alloco memoria
	insieme = (int *) malloc (dimensione);
	
	//inizio la vera e propria acquisizione
	
	printf("\n\n Si e' scelto di acquisire un'insieme");
	printf("\n Per terminare l'acquisizione digitare 0\n");
	while(finisci_di_acquisire != 1){
		insieme = (int *) realloc (insieme, (i+1) * sizeof (int));
		printf("\n Digitare ora il %d elemento: ",i+1);
		scanf("%d",&insieme[i]);
		if(insieme[i] == 0){
			finisci_di_acquisire = 1;
			dimensione = i;
		}
		i++;
	}
	
	//stampo l'insieme acquisito
	
	printf("\n L'insieme acquisito e':");
	printf("\n\n { ");
	for(i=0;i < dimensione; i++){
		printf("%d",insieme[i]);
		if(i+1 != dimensione)
			printf(" ; ");
	}
	printf(" }");



return 0;
}

void crea_insieme_vuoto(){
}
