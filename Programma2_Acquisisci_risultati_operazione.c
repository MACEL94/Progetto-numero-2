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
insieme_t acquisisci_risultati_operazione();
void controllo_chiusura(insieme_t, insieme_t);

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

    insieme_t insieme,risultati_operazione;
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
            printf("\n\n Si e' scelto di acquisire un'insieme");
            insieme = acquisisci_insieme();
            relazione = acquisisci_rel_bin(insieme);
            stampa(relazione);
            printf("\n\n Acquisisci l'insieme dei risultati dell operazione");
            risultati_operazione = acquisisci_insieme();
            controllo_chiusura(insieme,risultati_operazione);
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
    temporaneo = 1;
    insieme.numero_elementi = 50;
    finisci_di_acquisire = 0;

    /*alloco memoria*/
    insieme.elementi_insieme = (double *) malloc (insieme.numero_elementi);


    /*chiedo se l'utente vuole inserire lo 0*/

    printf("\n\n Premere il numero di zeri presenti nell'insieme: ");
    do
    {
        elemento_acquisito = scanf("%d",&zeri);
        if(elemento_acquisito != 1)
        {
            do
                carattere_non_letto = getchar();
            while (carattere_non_letto != '\n');
        }
    }
    while(elemento_acquisito != 1);
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
        elemento_acquisito = scanf("%lf",&temporaneo);

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
        else if(i >= 0)
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
        printf("%lf",insieme.elementi_insieme[i]);
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
        printf ("(%lf,%lf)",stampa.primo_termine[i],stampa.secondo_termine[i]);
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
        lettura_corretta = scanf("%lf",&elemento);
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

insieme_t acquisisci_risultati_operazione()
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
    temporaneo = 1;
    insieme.numero_elementi = 50;
    finisci_di_acquisire = 0;

    /*alloco memoria*/
    insieme.elementi_insieme = (double *) malloc (insieme.numero_elementi);

    /*inizio la vera e propria acquisizione*/


    /*chiedo se l'utente vuole inserire lo 0*/

    printf("\n\n Premere il numero di zeri presenti nell'insieme: ");
    do
    {
        elemento_acquisito = scanf("%d",&zeri);
        if(elemento_acquisito != 1)
        {
            do
                carattere_non_letto = getchar();
            while (carattere_non_letto != '\n');
        }
    }
    while(elemento_acquisito != 1);
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
        elemento_acquisito = scanf("%lf",&temporaneo);

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
        else if(i >= 0)
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
        printf("%lf",insieme.elementi_insieme[i]);
        if(i+1 < insieme.numero_elementi)
            printf(" ; ");
        i++;
    }
    printf(" }");



    return insieme;
}

/*controllo che l'elemento appartenga all'insieme*/

void controllo_chiusura (insieme_t insieme, insieme_t risultati)
{
    printf("\n\n Verifico la chiusura dell'insieme rispetto l'operazione..");
    int i,j,chiusura;
    chiusura = 0;

    for( j = 0; j < risultati.numero_elementi; j++)
    {
        chiusura=0;
        for( i = 0; i < insieme.numero_elementi; i++)
        {
            if(risultati.elementi_insieme[j] == insieme.elementi_insieme[i])
            {
                chiusura = 1;
                i = insieme.numero_elementi;
            }
        }
        if(chiusura == 0)
            j = risultati.numero_elementi;
    }

    if(chiusura == 1)
        printf("\n\nl'insieme e' chiuso rispetto l'operazione\n\n");
    else
        printf("\n\nl'insieme non e' chiuso rispetto l'operazione\n\n");
    return;
}

