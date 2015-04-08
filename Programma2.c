/***************************************************/
/* Progetto per la sessione estiva del 2014/2015 */
/***************************************************/

/*****************************/
/* inclusione delle librerie */
/*****************************/

#include<stdio.h>

/********************************/
/* dichiarazione delle funzioni */
/********************************/

int acquisisci_insieme(void);

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
	printf("  su quell'insieme.\n\n Poi verifica se l'insieme e' chiuso rispetto all'operazione");
	printf(" e se la relazione\n e' una congruenza rispetto all'operazione.\n");
	printf("\n Digitare 1 se si vuole iniziare con l'acquisizione dell'insieme o 2 se si vuole");
	printf(" terminare il programma: ");
	while((scelta != 1 && scelta != 2) || lettura_effettuata != 1)
		lettura_effettuata = scanf("%d",&scelta);
	if(scelta==1)
		acquisisci_insieme();
	if(scelta==2)
		return 0;
}



/* acquisizione dell'insieme */

int acquisisci_insieme(){
	int 	i;			//variabile contatore
	i=0;
printf("\n\n\nSi e' scelto di acquisire l'insieme.\n");

return 0;
}

