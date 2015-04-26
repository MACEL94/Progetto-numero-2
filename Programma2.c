/***************************************************/
/* Progetto per la sessione estiva del 2014/2015 */
/***************************************************/

/*****************************/
/* inclusione delle librerie */
/*****************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*********************************/
/* dichiarazione delle strutture */
/*********************************/

typedef struct relBin
{

    /* coppia numerica */

    double 	*primo_termine,
            *secondo_termine;

    /* variabile per sapere il numero delle coppie */

    int dimensione;

} rel_bin;

typedef struct divisione
{
    double risultato;
    int buon_fine;
} divisione_t;

typedef struct Insieme
{
    double* elementi_insieme;
    int numero_elementi;
} insieme_t;

/********************************/
/* dichiarazione delle funzioni */
/********************************/

insieme_t acquisisci_insieme(void);
rel_bin acquisisci_rel_bin(insieme_t);
insieme_t crea_insieme_vuoto(void);
int acquisisci_elemento(insieme_t);
void stampa(rel_bin);
int acquisisci_operazione();
void controllo_chiusura(int,insieme_t);
double somma(double,double);
divisione_t divisione(double,double);
double sottrazione(double,double);
double moltiplicazione(double,double);
int controllo(insieme_t, double);

/*****************/
/* funzione main */
/*****************/

int main()
{
    char carattere_non_letto;
    int scelta,
        operazione,
        lettura_effettuata;

    /* variabili per insieme e relazione */

    insieme_t insieme;
    rel_bin relazione;

    /*inizializzo le variabili*/
    scelta=0;
    lettura_effettuata=0;


    printf(" Questo programma acquisisce nel seguente ordine: \n\n 1) Un insieme; ");
    printf(" \n 2) Una relazione binaria su quell'insieme; \n 3) Un'operazione binaria");
    printf(" su quell'insieme.\n\n Poi verifica se l'insieme e' chiuso rispetto all'operazione");
    printf(" e se la relazione\n e' una congruenza rispetto all'operazione.\n");
    printf("\n Digitare:\n 1 - se si vuole iniziare con l'acquisizione dell'insieme,\n 2 - se si vuole");
    printf(" inserire l'insieme vuoto,\n 3 - terminare il programma: ");
    while((scelta != 1 && scelta != 2 && scelta != 3) || lettura_effettuata != 1)
    {
        lettura_effettuata = scanf("%d",&scelta);
        if(lettura_effettuata != 1)
        {
            do
                carattere_non_letto = getchar();
            while (carattere_non_letto != '\n');
            scelta=4;
        }
        if(scelta==1)
        {
            insieme = acquisisci_insieme();
            relazione = acquisisci_rel_bin(insieme);
            stampa(relazione);
            operazione = acquisisci_operazione();
            controllo_chiusura(operazione,insieme);
        }
        if(scelta==2)
            crea_insieme_vuoto();
    }
    return 0;
}


/*****************************/
/* acquisizione dell'insieme */
/*****************************/

insieme_t acquisisci_insieme()
{
    /*dichiaro la struttura insieme*/
    insieme_t insieme;

    int 	i,							/*variabile contatore*/
            finisci_di_acquisire,       /*variabile per terminare l'acquisizione*/
            zeri,
            elemento_acquisito;			/*variabile per verificare che la acquisizione vada a buon fine*/

    char	carattere_non_letto;		/*variabile necessaria allo svuotamento del buffer*/

    double temporaneo;					/*variabile per acquisire ogni elemento temporaneamente*/
    /*inizializzo le variabili*/

    elemento_acquisito = 0;
    i = 0;
    zeri = 0;
    temporaneo = 0;
    insieme.numero_elementi = 50;
    finisci_di_acquisire = 0;

    /*alloco memoria*/
    insieme.elementi_insieme = (double *) malloc (insieme.numero_elementi);

    /*inizio la vera e propria acquisizione*/

    printf("\n\n Si e' scelto di acquisire un'insieme");

    /*chiedo se l'utente vuole inserire lo 0*/

    printf("\n Premere il numero di zeri presenti nell'insieme: ");
    scanf("%d",&zeri);
    while (i < zeri && zeri > 0)
    {
        insieme.elementi_insieme = (double *) realloc (insieme.elementi_insieme, (i+1) * sizeof (double));
        insieme.elementi_insieme[i]=0;
        i++;
    }

    /*faccio partire i da temporaneo*/

    i=zeri;

    printf("\n Per terminare l'acquisizione digitare 0\n");
    while(finisci_di_acquisire != 1)
    {
        insieme.elementi_insieme = (double *) realloc (insieme.elementi_insieme, (i+1) * sizeof (double));
        printf("\n Digitare ora il %d elemento: ",i+1);
        elemento_acquisito = scanf("%d",&temporaneo);

        if(elemento_acquisito != 1)
        {
            do
                carattere_non_letto = getchar();
            while (carattere_non_letto != '\n');
            i--;
        }
        if(temporaneo == 0)
        {
            finisci_di_acquisire = 1;
            insieme.numero_elementi = i;
        }
        else
            insieme.elementi_insieme[i] = temporaneo;
        i++;
    }


    /***********************/
    /* stampa dell'insieme */
    /***********************/

    printf("\n L'insieme acquisito e':");
    printf("\n\n { ");
    i=0;
    while(i < insieme.numero_elementi)
    {
        printf("%d",insieme.elementi_insieme[i]);
        if(i+1 < insieme.numero_elementi)
            printf(" ; ");
        i++;
    }
    printf(" }");



    return insieme;
}

insieme_t crea_insieme_vuoto()
{
    insieme_t insieme;
    insieme.elementi_insieme = (double *) malloc (1);
    insieme.numero_elementi = 0;
    return insieme;
}

rel_bin acquisisci_rel_bin(insieme_t insieme)
{
    rel_bin relazione;

    int acquisizione_finita,
        risultato_lettura,
        primo_termine_acquisito;

    char carattere_non_letto;

    acquisizione_finita = 0;
    primo_termine_acquisito = 0;

    relazione.dimensione = 0;
    relazione.primo_termine = (double *) malloc (2);
    relazione.secondo_termine = (double *) malloc (2);
    while (acquisizione_finita == 0)
    {
        primo_termine_acquisito = 0;
        relazione.dimensione++;
        acquisizione_finita = 2;

        /*Acquisisco i termini della coppia*/

        printf ("\n Inserisci i termini della coppia \n ");
        relazione.primo_termine = (double *) realloc (relazione.primo_termine,
                                  (relazione.dimensione+1) * sizeof (double));
        relazione.secondo_termine = (double *) realloc (relazione.secondo_termine,
                                    (relazione.dimensione+1) * sizeof (double));
        risultato_lettura = 0;


        /*Acquisisco il primo termine*/
        if (primo_termine_acquisito == 0)
        {
            printf ("  Primo Termine: ");
            relazione.primo_termine[relazione.dimensione - 1] = acquisisci_elemento(insieme);
        }
        primo_termine_acquisito = 1;

        /*Acquisisco il secondo termine*/
        if (primo_termine_acquisito == 1)
        {
            printf ("   Secondo Termine: ");
            relazione.secondo_termine[relazione.dimensione - 1] = acquisisci_elemento(insieme);
        }

        /*Chiedo all'utente se ci sono altre coppie*/

        do
        {
            printf ("\n Vuoi acquisire un'altra coppia? immetti 1 per uscire, 0 per continuare\n ");
            printf ("\n scelta: ");
            risultato_lettura = scanf ("%d",
                                       &acquisizione_finita);
            if (acquisizione_finita < 0 || acquisizione_finita > 1 || risultato_lettura != 1)
                do
                    carattere_non_letto = getchar();
                while (carattere_non_letto != '\n');
        }
        while (acquisizione_finita < 0 || acquisizione_finita > 1 );
    }
    return relazione;
}

/******************************FUNZIONE DI STAMPA********************************/

void stampa (rel_bin stampa)
{

    int i = 0;

    printf ("\n La relazione binaria e':");
    printf ("\n\n  {");

    /******Stampa per coppie numeriche *****/

    while (i < stampa.dimensione)
    {
        printf ("(%d,%d)",stampa.primo_termine[i],stampa.secondo_termine[i]);
        if (i+1 != stampa.dimensione)
            printf (" ; ");
        i++;
    }
    printf("}\n");
    return ;
}

int acquisisci_elemento(insieme_t insieme)
{
    /* dichiaro le variabili */
    char carattere_non_letto;

    int lettura_corretta,
        i,
        elemento_trovato;

    double elemento;
    /* inizializzo le variabili */
    elemento=0;
    lettura_corretta=1;
    do
    {
        /* controllo che i valori siano stati letti correttamente */
        /* e nel caso non sia cosi svuoto il buffer */
        if(lettura_corretta != 1)
        {
            do
                carattere_non_letto = getchar();
            while (carattere_non_letto != '\n');
            printf ("\n C'e'un errore, reinserire il termine e verificare\n");
            printf(" che appartenga all'insieme precedentemente inserito: \n ");
        }
        lettura_corretta = scanf("%d",&elemento);
        /* verifico se l'elemento che si vuole utilizzare nella relazione */
        /* e' presente nell'insieme inserito */
        elemento_trovato = 0;
        for(i=0; i < insieme.numero_elementi; i++)
            if(elemento == insieme.elementi_insieme[i])
                elemento_trovato = 1;

        if(elemento_trovato == 0)
            lettura_corretta = 0;
    }
    while(lettura_corretta == 0);

    return elemento;
}


/* Acquisisco l'operazione*/

int acquisisci_operazione()
{
    char carattere_non_letto;
    int scelta,
        lettura_corretta;
    printf("\n Inserire ora il numero corrispondente all' operazione desiderata:\n");
    printf("\n 1 - Somma\n 2 - Differenza\n 3 - Moltiplicazione\n 4 - Divisione\n\n");
    scelta = 0;
    do
    {
        printf(" Scelta: ");
        lettura_corretta = scanf("%d",&scelta);
        if(lettura_corretta == 0)
        {
            do
                carattere_non_letto = getchar();
            while (carattere_non_letto != '\n');
        }
    }
    while(lettura_corretta == 0 || (scelta != 1 && scelta != 2 && scelta != 3 && scelta != 4));
    switch(scelta)
    {
    case 1:
        printf("\n E' stata scelta la Somma\n");
        break;
    case 2:
        printf("\n E' stata scelta la Differenza\n");
        break;
    case 3:
        printf("\n E' stata scelta la Moltiplicazione\n");
        break;
    case 4:
        printf("\n E' stata scelta la Divisione\n");
        break;
    }
    return(scelta);
}

/*inizio il controllo della chiusura*/

void controllo_chiusura(int operazione, insieme_t insieme)
{
    int i,j,k,chiusura;
    double risultato;
    divisione_t div;

    chiusura = 0;

    switch(operazione)
    {

    case 1:
        for( i = 0; i < insieme.numero_elementi; i++)
            for( j = 0; j < insieme.numero_elementi; j++)
            {
                risultato = somma(insieme.elementi_insieme[i],insieme.elementi_insieme[j]);
                chiusura = controllo(insieme,risultato);
                if(chiusura == 0){
                    j = insieme.numero_elementi;
                    i = insieme.numero_elementi;
                }
            }
        break;

    case 2:
        for( i = 0; i < insieme.numero_elementi; i++)
            for( j = 0; j < insieme.numero_elementi; j++)
            {
                risultato = sottrazione(insieme.elementi_insieme[i],insieme.elementi_insieme[j]);
                chiusura = controllo(insieme,risultato);
                if(chiusura == 0){
                    j = insieme.numero_elementi;
                    i = insieme.numero_elementi;
                }
            }
        break;

    case 3:
        for( i = 0; i < insieme.numero_elementi; i++)
            for( j = 0; j < insieme.numero_elementi; j++)
            {
                risultato = moltiplicazione(insieme.elementi_insieme[i],insieme.elementi_insieme[j]);
                chiusura = controllo(insieme,risultato);
                if(chiusura == 0){
                    j = insieme.numero_elementi;
                    i = insieme.numero_elementi;
            }
            }

        break;

    case 4:
        for( i = 0; i < insieme.numero_elementi; i++)
            for( j = 0; j < insieme.numero_elementi; j++)
            {
                div.risultato = divisione(insieme.elementi_insieme[i],insieme.elementi_insieme[j]).risultato;
                chiusura = controllo(insieme,div.risultato);
                if(chiusura == 0 || div.buon_fine == 0){
                    j = insieme.numero_elementi;
                    i = insieme.numero_elementi;
                }
            }

        break;
    }


    if(chiusura == 0)
        printf("\n l'insieme non e' chiuso rispetto all'operazione");
    else
        printf("\n l'insieme e' chiuso rispetto all'operazione");

    return;
}



double somma (double primo_termine, double secondo_termine)
{
    int somma;

    somma = primo_termine + secondo_termine;


}

double sottrazione (double primo_termine, double secondo_termine)
{
    int sottrazione;

    sottrazione = primo_termine - secondo_termine;

    return(sottrazione);
}


double moltiplicazione (double primo_termine, double secondo_termine)
{
    int moltiplicazione;

    moltiplicazione = primo_termine * secondo_termine;

    return(moltiplicazione);
}

divisione_t divisione (double primo_termine, double secondo_termine)
{
    divisione_t div;

    if(secondo_termine != 0){
        div.buon_fine = 1;
        div.risultato = primo_termine / secondo_termine;
    }
    else{
        div.buon_fine = 0;
        printf( "\n errore, un denominatore risulta essere uguale a 0\n");
    }
    return(div);
}

/*controllo che l'elemento appartenga all'insieme*/

int controllo (insieme_t insieme, double risultato)
{
    int i,chiusura;
    chiusura = 0;

    for( i = 0; i < insieme.numero_elementi; i++)
        if(risultato == insieme.elementi_insieme[i])
        {
            chiusura = 1;
            i = insieme.numero_elementi;
        }

    return(chiusura);
}

