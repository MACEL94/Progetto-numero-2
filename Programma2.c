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

int* acquisisci_insieme(void);
void crea_insieme_vuoto(void);

/*****************/
/* funzione main */
/*****************/

int main(){
	int *insieme[],
		scelta,
		lettura_effettuata;
		
	//inizializzo le variabili
	scelta=0;
	lettura_effettuata=0;
	
	
	printf(" Questo programma acquisisce nel seguente ordine: \n\n 1) Un insieme; ");
	printf(" \n 2) Una relazione binaria su quell'insieme; \n 3) Un'operazione binaria");
	printf(" su quell'insieme.\n\n Poi verifica se l'insieme e' chiuso rispetto all'operazione");
	printf(" e se la relazione\n e' una congruenza rispetto all'operazione.\n");
	printf("\n Digitare:\n 1 - se si vuole iniziare con l'acquisizione dell'insieme,\n 2 - se si vuole");
	printf(" inserire l'insieme vuoto,\n 3 - terminare il programma: ");
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

int* acquisisci_insieme(){
	int 	i,							//variabile contatore
			finisci_di_acquisire,		//variabile per terminare l'acquisizione
			dimensione,					//variabile per la dimensione dell'array
			temporaneo;					//variabile per acquisire ogni elemento temporaneamente
	//inizializzo le variabili
	
	i = 0;
	temporaneo=0;
	dimensione=50;
	finisci_di_acquisire = 0;
	
	//dichiaro l'array insieme
	
	int *insieme;							
	
	//alloco memoria
	insieme = (int *) malloc (dimensione);
	
	//inizio la vera e propria acquisizione
	
	printf("\n\n Si e' scelto di acquisire un'insieme");
	
	//chiedo se l'utente vuole inserire lo 0
	
	printf("\n Premere il numero di zeri presenti nell'insieme: ");
	scanf("%d",&temporaneo);
	while (i < temporaneo && temporaneo > 0){
		insieme = (int *) realloc (insieme, (i+1) * sizeof (int));
		insieme[i]=0;
		i++;
	}
	
	//faccio partire i da temporaneo
	
	i=temporaneo;
	
	printf("\n Per terminare l'acquisizione digitare 0\n");
	while(finisci_di_acquisire != 1){
		insieme = (int *) realloc (insieme, (i+1) * sizeof (int));
		printf("\n Digitare ora il %d elemento: ",i+1);
		scanf("%d",&temporaneo);
		if(temporaneo == 0){
			finisci_di_acquisire = 1;
			dimensione = i;
		}
		else
		insieme[i] = temporaneo;
		i++;
	}
	

	
	//stampo l'insieme acquisito
	
	printf("\n L'insieme acquisito e':");
	printf("\n\n { ");
	i=0;
	while(i < dimensione){
		printf("%d",insieme[i]);
		if(i+1 < dimensione)
			printf(" ; ");
		i++;
	}
	printf(" }");



return 0;
}

void crea_insieme_vuoto(){
}
