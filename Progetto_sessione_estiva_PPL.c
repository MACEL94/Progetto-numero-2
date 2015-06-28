/*************************************************/
/* Progetto per la sessione estiva del 2014/2015 */
/*************************************************/

/*****************************/
/* inclusione delle librerie */
/*****************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*********************************/
/* dichiarazione delle strutture */
/*********************************/

typedef struct Operazione
{
  double			*operando_a;
  double			*operando_b;
  double			*risultati;

} operazione_t;

typedef struct RelBin
{
  /* coppia numerica */

  double 	*primo_termine;
  double	*secondo_termine;

  /* variabile per sapere il numero delle coppie */

  int dimensione;
} rel_bin;

typedef struct Insieme
{
  double* elementi_insieme;
  int numero_elementi;
} insieme_t;

/********************************/
/* dichiarazione delle funzioni */
/********************************/

void errore(void);
void svuota_buffer(void);
insieme_t acquisisci_insieme(void);
void stampa_insieme(insieme_t);
insieme_t crea_insieme_vuoto(void);
rel_bin acquisisci_rel_bin(insieme_t);
int acquisisci_elemento(insieme_t);
void stampa_rel_bin(rel_bin);
operazione_t acquisisci_operazione(insieme_t);
int controllo_simmetria(rel_bin);
int controllo_riflessivita(rel_bin);
int controllo_transitivita(rel_bin);
int relazione_equivalenza(rel_bin);
int controllo_chiusura(insieme_t,
                       operazione_t);
void controllo_congruenza(rel_bin,
                          insieme_t,
                          operazione_t,
                          int);
void informazioni_sul_programma(void);
void scelta_operazione(void);
int ripeti(void);

/*****************/
/* funzione main */
/*****************/

int main()
{
  /*variabile per dare la possibilita'
  all'utente di utilizzare il programma
  ricorsivamente*/
  int ripetere;
  ripetere = 1;

  informazioni_sul_programma();

  while (ripetere == 1)
  {

    scelta_operazione();
    ripetere = ripeti();

  }

  return 0;
}

/*funzione per poter riportare un segnale di errore dopo un acquisizione da tastiera errata*/
void errore()
{
  printf("\n\n  Hai inserito un valore errato.");
  printf("\n  Inserire un valore corretto: ");

  return;
}

/*funzione per poter pulire il buffer*/
void svuota_buffer()
{
  /*variabile per svuotare il buffer*/
  char carattere_non_letto;
  do
  {
    carattere_non_letto = getchar();
  }
  while (carattere_non_letto != '\n');

  return;
}

/*informazioni sul programma*/
void informazioni_sul_programma()
{
  printf("\n **************************************");
  printf("*************************\n");
  printf("\n  Questo programma acquisisce nel seguente");
  printf(" ordine:\n");
  printf("\n  1) Un insieme;\n  2) Una relazione binaria su ");
  printf("quell'insieme;\n  3) Un'operazione binaria su quell");
  printf("'insieme.\n\n  Poi verifica se l'insieme e' chiuso ");
  printf("rispetto all'operazione \n ");
  printf(" e se la relazione e' una");
  printf(" congruenza rispetto all'operazione.\n");

  return;
}

/*Funzione per chiedere all'utente cosa vuole fare*/
void scelta_operazione()
{
  /*variabile per il controllo della scelta*/
  int scelta;
  /*variabile per controllare che la
  lettura sia avvenuta correttamente*/
  int lettura_effettuata;
  /*variabile per il salvataggio del
  risultato della verifica della chiusura*/
  int chiusura;

  /* variabili per insieme, relazione
  e operazione*/
  operazione_t operazione;
  insieme_t insieme;
  rel_bin relazione;

  /*inizializzo le variabili*/
  scelta = 0;
  lettura_effettuata = 0;
  chiusura = 1;

  printf("\n **********************************");
  printf("*****************************\n");
  printf("\n\n  Digitare:\n   1 - se si vuole iniziare con");
  printf(" l'acquisizione dell'insieme,\n   2 - se si vuole ");
  printf("inserire l'insieme vuoto,");
  printf("\n   3 - se si vogliono avere ");
  printf("informazioni sul programma ");
  printf("\n   4 - uscire da questo menu': ");

  do
  {
    lettura_effettuata = scanf("%d",&scelta);
    if ((lettura_effettuata != 1)
      || (scelta != 1 && scelta != 2
      && scelta != 3 && scelta != 4)
      || (lettura_effettuata != 1))
    {
      errore();
      svuota_buffer();
      scelta=5;
    }

  }while ((scelta != 1 && scelta != 2
          && scelta != 3 && scelta != 4) || lettura_effettuata != 1);

  if (scelta == 1)
  {

    insieme = acquisisci_insieme();
    stampa_insieme(insieme);
    if (insieme.numero_elementi != 0)
    {
      relazione = acquisisci_rel_bin(insieme);
      stampa_rel_bin(relazione);
      operazione = acquisisci_operazione(insieme);
      chiusura = controllo_chiusura(insieme,
                                    operazione);
      controllo_congruenza(relazione,
                           insieme,
                           operazione,
                           chiusura);
    }
  }
  if (scelta == 2 || insieme.numero_elementi == 0)
  {

    printf("\n\n ************** INSIEME");
    printf(" VUOTO **********************\n");
    insieme = crea_insieme_vuoto();
    printf("\n  L'insieme che si e' scelto e' vuoto,");
    printf(" quindi  qualsiasi \n  sia la relazione");
    printf(", simmetria, riflessivita' e transitivita'\n");
    printf("  sono sempre verificate.\n  Per convenzione ");
    printf("diciamo anche che qualsiasi sia\n  l'operazione");
    printf(" e' chiusa rispetto all'insieme");
  }

  if (scelta == 3)
    informazioni_sul_programma();

  return;
}


/*Funzione per ripetere il procedimento*/
int ripeti()
{
  int ripetere;
  int lettura_effettuata;

  ripetere = 0;

  printf("\n\n  Digitare:\n   1 - se si vuole eseguire");
  printf(" un altra operazione,");
  printf("\n   2 - se si vuole terminare il programma: ");
  do
  {
    lettura_effettuata = scanf("%d",&ripetere);
    if (lettura_effettuata != 1 || (ripetere != 1 && ripetere != 2))
    {
      errore();
      svuota_buffer();
    }
  }
  while (lettura_effettuata != 1 || (ripetere != 1 && ripetere != 2));


  return (ripetere);
}


/*****************************/
/* acquisizione dell'insieme */
/*****************************/

insieme_t acquisisci_insieme()
{
  /*dichiaro la struttura insieme*/

  insieme_t insieme;

  /*variabile contatore */
  int 	i;
  /*variabile per il controllo di doppioni*/
  int buffer_vuoto;
  /*variabile contatore*/
  int 	j;
  /*variabile per controllare la fine dell acquisizione*/
  int controllo;
  /*variabile per terminare l'acquisizione*/
  int 	finisci_di_acquisire;
  /*variabile per verificare che la
  acquisizione vada a buon fine*/
  int 	elemento_acquisito;
  /*variabile necessaria allo
  svuotamento del buffer*/
  char	carattere_non_letto;
  /*variabile per acquisire ogni
  elemento temporaneamente*/
  double temporaneo;

  /*inizializzo le variabili*/
  elemento_acquisito = 0;
  j = 0;
  i = 0;
  temporaneo = 0;
  insieme.numero_elementi = 50;
  finisci_di_acquisire = 0;
  controllo = 0;
  buffer_vuoto = 1;
  /*alloco memoria*/
  insieme.elementi_insieme = (double *)
                             malloc (insieme.numero_elementi);

  /*inizio la vera e propria acquisizione*/

  printf("\n\n  Si e' scelto di acquisire un'insieme\n");

  /*chiedo se l'utente vuole inserire lo 0*/

  printf("\n\n ************** ACQUISIZIONE DELL'");
  printf("INSIEME **********************\n");

  printf("\n\n  Per terminare l'acquisizione digitare a\n\n");

  while (finisci_di_acquisire != 1)
  {
    controllo = 0;
    insieme.elementi_insieme = (double *)
                               realloc (insieme.elementi_insieme,
                                        (i+1) * sizeof (double));
    printf("\n  Digitare ora il %d elemento: ",i+1);
    /*svuoto il buffer prima di acquisire*/
    if (buffer_vuoto != 1)
      svuota_buffer();

    buffer_vuoto = 0;
    elemento_acquisito = scanf("%lf",&temporaneo);
    if (i >= 0 && finisci_di_acquisire != 1 )
      insieme.elementi_insieme[i] = temporaneo;

    /*controllo se c'e' stato un errore nell'acquisizione*/
    if (elemento_acquisito != 1)
    {
      do
      {
        carattere_non_letto = getchar();
        /*controllo se l utente ha digitato il carattere di terminazione*/
        if ((carattere_non_letto == 'a') && (controllo == 0))
        {
          finisci_di_acquisire = 1;
          insieme.numero_elementi = i;
        }
        /*controllo che mi permette di verificare se e' stato digitato solo un carattere */
        if (controllo > 1)
          finisci_di_acquisire = 0;
        controllo++;

      }
      while (carattere_non_letto != '\n');
      /*mi segno che il buffer e' gia' vuoto per non andarlo a svuotare una seconda volta*/
      buffer_vuoto = 1;
      i--;
    }

    /*controllo che l'elemento non sia gia presente nell insieme*/

    for (j = i-1; j >= 0; j--)
    {
      if (temporaneo == insieme.elementi_insieme[j])
      {
        i--;
        j = 0;
      }
    }
    i++;
  }

  return (insieme);
}

/***********************/
/* stampa dell'insieme */
/***********************/

void stampa_insieme(insieme_t insieme)
{
  /*variabile contatore*/
  int i;

  printf("\n\n ************** STAMPA DELL'");
  printf("INSIEME ***************************\n");
  printf("\n\n  L'insieme acquisito e':");
  printf("\n\n  { ");
  i=0;

  while (i < insieme.numero_elementi)
  {
    printf("%.2lf",insieme.elementi_insieme[i]);
    if (i+1 < insieme.numero_elementi)
      printf(" ; ");
    i++;
  }
  printf(" }\n\n");

  return;
}

insieme_t crea_insieme_vuoto()
{
  /*variabile per la struttura insieme*/
  insieme_t insieme;

  insieme.elementi_insieme = (double *) malloc (1);
  insieme.numero_elementi = 0;
  return (insieme);
}

/*Funzione che acquisisce la relazione binaria*/

rel_bin acquisisci_rel_bin(insieme_t insieme)
{

  rel_bin relazione;

  /*variabile utile ad uscire dal ciclo
  di acquisizione*/
  int acquisizione_finita,
      /*variabile per il controllo
      dell'acquisizione*/
      risultato_lettura,
      /*variabile contatore*/
      i,
      /*relazione vuota*/
      relazione_vuota,
      /*variabile per il primo termine*/
      primo_termine_acquisito;

  printf("\n\n ********* ACQUISIZIONE DELLA");
  printf("RELAZIONE BINARIA ****************\n");
  printf("\n\n   Si vuole acquisire una relazione vuota?");
  printf("\n\n  Digitare:\n   0 - si\n");
  printf("   1 - no:  ");
  do
  {
    risultato_lettura = scanf("%d",&relazione_vuota);
    if ((risultato_lettura != 1 || relazione_vuota != 0) && relazione_vuota != 1)
    {
      errore();
      svuota_buffer();
    }
  }
  while ((risultato_lettura != 1  || relazione_vuota != 0) && relazione_vuota != 1);
  if (relazione_vuota == 0)
    printf("  si e' scelto di inserire una relazione vuota");

  /*inizializzo le variabili*/
  acquisizione_finita = 1;
  primo_termine_acquisito = 0;
  relazione.dimensione = 0;
  /*alloco memoria*/
  relazione.primo_termine = (double *) malloc (2);
  relazione.secondo_termine = (double *) malloc (2);
  if (relazione_vuota == 1)
  {
    while (acquisizione_finita == 1)
    {
      primo_termine_acquisito = 0;
      relazione.dimensione++;
      acquisizione_finita = 2;

      /*Acquisisco i termini della coppia*/

      printf ("\n\n  Inserisci i termini della coppia \n ");

      relazione.primo_termine = (double *)
                                realloc (relazione.primo_termine,
                                         (relazione.dimensione+1)
                                         * sizeof (double));

      relazione.secondo_termine = (double *)
                                  realloc (relazione.secondo_termine,
                                           (relazione.dimensione+1)
                                           * sizeof (double));
      risultato_lettura = 0;


      /*Acquisisco il primo termine*/
      if (primo_termine_acquisito == 0)
      {
        printf ("   Primo Termine: ");
        relazione.primo_termine[relazione.dimensione - 1] =
          acquisisci_elemento(insieme);
      }
      primo_termine_acquisito = 1;

      /*Acquisisco il secondo termine*/
      if (primo_termine_acquisito == 1)
      {
        printf ("    Secondo Termine: ");
        relazione.secondo_termine[relazione.dimensione - 1]
          = acquisisci_elemento(insieme);

        for (i=relazione.dimensione-2; i>=0; i--)
          if (relazione.primo_termine[relazione.dimensione - 1]
              == relazione.primo_termine[i])
            if (relazione.secondo_termine[relazione.dimensione -1]
                == relazione.secondo_termine[i])
            {
              relazione.dimensione--;
              i = 0;
            }
      }

      /*Chiedo all'utente se ci sono altre coppie*/

      do
      {
        printf("\n\n  Digitare:\n   0 - per");
        printf(" terminare l'acquisizione,");
        printf("\n   1 - se si vuole acquisire un altra coppia: ");
        risultato_lettura = scanf ("%d",
                                   &acquisizione_finita);
        if (acquisizione_finita < 0 ||
            acquisizione_finita > 1 || risultato_lettura != 1)
        {
          errore();
          svuota_buffer();
        }
      }
      while (acquisizione_finita < 0 || acquisizione_finita > 1 );
    }
  }
  svuota_buffer();
  return (relazione);
}

/************FUNZIONE DI STAMPA****************/

void stampa_rel_bin(rel_bin stampa)
{
  /*variabile contatore*/
  int i = 0;

  printf("\n\n ********* STAMPA DELLA RELAZIONE BINARIA *****");
  printf ("****************\n\n  La relazione binaria e':");
  printf ("\n\n   {");

  /******Stampa per coppie numeriche *****/

  while (i < stampa.dimensione)
  {
    printf ("(%.2lf,%.2lf)",
            stampa.primo_termine[i],
            stampa.secondo_termine[i]);
    if (i+1 != stampa.dimensione)
      printf (" ; ");
    i++;
  }
  printf("}\n");
  return;
}

int acquisisci_elemento(insieme_t insieme)
{
  /*variabile per il controllare che
  gli elementi acquisiti siano stati
  letti correttamente*/
  int lettura_corretta,
      /*variabile contatore*/
      i,
      /*variabile di controllo per verificare
      la non ripetizione di elementi*/
      elemento_trovato;

  double elemento;
  /* inizializzo le variabili */
  elemento = 0;
  lettura_corretta = 1;

  do
  {
    /* controllo che i valori siano
        stati letti correttamente
     e nel caso svuoto il buffer */

    if (lettura_corretta != 1)
    {
      svuota_buffer();
      printf ("\n  Verificare che l'elemento");
      printf (" appartenga \n  all'insieme");
      printf (" precedentemente inserito. \n ");
      errore();
    }
    lettura_corretta = scanf("%lf",&elemento);

    /* verifico se l'elemento che si
       vuole utilizzare nella relazione
     e' presente nell'insieme inserito */

    elemento_trovato = 0;

    for (i=0; i < insieme.numero_elementi; i++)
      if (elemento == insieme.elementi_insieme[i])
        elemento_trovato = 1;

    if (elemento_trovato == 0)
      lettura_corretta = 0;
  }
  while (lettura_corretta == 0);

  svuota_buffer();
  return (elemento);
}


/* Acquisisco l'operazione*/

operazione_t acquisisci_operazione(insieme_t insieme)
{
  /*variabile per acquisire l operazione*/
  operazione_t operazione;
  /*variabile contatore*/
  int i,
      j,
      /*variabile che stabilisce la dimensione dell'array*/
      dimensione,
      /*variabile per il controllo*/
      controllo;

  i = 0;
  j = 0;
  dimensione = 0;

  operazione.risultati = (double *) malloc (2);
  operazione.operando_a = (double *) malloc (2);
  operazione.operando_b = (double *) malloc (2);
  printf("\n\n ********* ACQUISIZIONE ");
  printf("DELL'OPERAZIONE ************************\n");
  printf(" \n\n  Inserire ora i risultati dell'operazioni: \n");
  printf(" \n  Digitare 999 per risultati ");
  printf("impossibili o indeterminati. \n");

  for (i = 0; i < insieme.numero_elementi; i++)
  {
    for (j = 0; j < insieme.numero_elementi; j++)
    {
      operazione.risultati = (double *)
                             realloc (operazione.risultati,
                                      (dimensione+1)
                                      * sizeof (double));
      operazione.operando_a = (double *)
                              realloc (operazione.operando_a,
                                       (dimensione+1)
                                       * sizeof (double));
      operazione.operando_b = (double *)
                              realloc (operazione.operando_b,
                                       (dimensione+1)
                                       * sizeof (double));
      operazione.operando_a[dimensione] = insieme.elementi_insieme[i];
      operazione.operando_b[dimensione] = insieme.elementi_insieme[j];
      printf("\n  %f * %f = ",insieme.elementi_insieme[i],
             insieme.elementi_insieme[j]);
      do
      {

        controllo = scanf("%lf",
                          &operazione.risultati[dimensione]);
        if (controllo != 1)
        {
          errore();
          svuota_buffer();
        }
      }

      while (controllo != 1);
      dimensione++;
    }
  }
  svuota_buffer();
  return (operazione);
}

int controllo_chiusura(insieme_t insieme,
                       operazione_t operazione)
{
  int i,
      j,
      chiusura;

  i = 0;
  j = 0;
  chiusura = 0;

  for (i = 0;
       i<(insieme.numero_elementi*insieme.numero_elementi);
       i++)
  {
    chiusura = 0;
    if (operazione.risultati[i] != 999)
      for (j=0; j<insieme.numero_elementi; j++)
        if (operazione.risultati[i] ==
            insieme.elementi_insieme[j])
        {
          chiusura = 1;
          j = insieme.numero_elementi+1;
        }
    if (chiusura == 0)
      i = (insieme.numero_elementi*insieme.numero_elementi);
  }
  printf("\n\n ************ CHIUSURA **********************");
  printf("*******************\n");
  if (chiusura == 0)
    printf("\n\n  La chiusura non e' verificata\n");
  if (chiusura == 1)
    printf("\n\n  La chiusura e' verificata\n");

  return (chiusura);
}

int controllo_riflessivita(rel_bin verifica)
{
  /*variabile contatore*/
  int i,
      j,
      k,
      /*variabili per contare i riscontri*/
      riscontro,
      secondo_riscontro,
      /*variabile per vedere se e' stata verificata la riflessivita'*/
      riflessivita;

  riflessivita = 1;
  i = 0;
  j = 0;
  k = 0;
  riscontro = 0;
  secondo_riscontro = 0;

  /*Verifica riflessivita'*/

  /*Definizione: una relazione per la quale
   esiste almeno un elemento che non e'in relazione
  con se' stesso non soddisfa la definizione di riflessivita'*/

  while ( (i < verifica.dimensione) && (k < verifica.dimensione))
  {

    /*Verifica riflessivita' per numeri*/

    riscontro = 0;
    secondo_riscontro = 0;
    if (verifica.primo_termine[i] == verifica.secondo_termine[i])
      riscontro++;/*Controllo se c'e' stato un riscontro a,a*/
    secondo_riscontro++;
    if (riscontro != 0)
    {
      i++;
      k++;
    }
    /**/
    else
    {
      j = 0;
      riscontro = 0;
      secondo_riscontro = 0;

      /* Controllo la riflessivita' per
      gli elementi del primo insieme */

      while (j < verifica.dimensione)
      {
        if (j == i)
          j++;
        else
        {
          if (verifica.primo_termine[i] ==
              verifica.primo_termine[j])
            if (verifica.primo_termine[j] ==
                verifica.secondo_termine[j])
              riscontro++;

          j++;
        }
      }

      j = 0;

      /*Controllo la riflessivita' per gli
      elementi del secondo insieme*/

      while (j < verifica.dimensione)
      {
        if (j == k)
          j++;
        else
        {
          if (verifica.secondo_termine[k] ==
              verifica.secondo_termine[j])
            if (verifica.primo_termine[j] ==
                verifica.secondo_termine[j])
              secondo_riscontro++;

          j++;
        }
      }
      if (riscontro != 0)
        i++;

      /**** Se non c'e' stato un riscontro di riflessivita'
       esco e imposto la riflessivita' a 0 *****/

      else
      {
        i = verifica.dimensione;
        riflessivita = 0;
      }

      if (secondo_riscontro != 0)
        k++;

      else
      {
        k = verifica.dimensione;
        riflessivita = 0;
      }
    }

  }


  /*********** Fine riflessivita ***********************/
  return (riflessivita);
}

int controllo_transitivita(rel_bin verifica)
{
  /*variabile contatore*/
  int i,
      j,
      k,
      /*variabile per controllare la transitivita'*/
      transitivita;

  /*IMPOSTO LA TRANSITIVITA' INIZIALMENTE COME VERA
   E AZZERO I CONTATORI*/

  transitivita = 1;
  i = 0;
  j = 0;
  k = 0;

  /*VERIFICA TRANSITIVITa' PER NUMERI*/


  while (i < verifica.dimensione)
  {
    j = 0;

    while (j < verifica.dimensione)
    {
      k = 0;

      if (verifica.secondo_termine[i] ==
          verifica.primo_termine[j])
      {
        transitivita = 0;

        while (k < verifica.dimensione)
        {
          if (verifica.primo_termine[i] ==
              verifica.primo_termine[k])
          {
            if (verifica.secondo_termine[k] ==
                verifica.secondo_termine[j])
            {
              transitivita = 1;
              k = verifica.dimensione;
            }
          }

          k++;
        }

        if (transitivita==0)
        {
          j = verifica.dimensione;
          i = verifica.dimensione;
        }
      }

      j++;
    }

    i++;
  }

  /************ Fine controllo Transitivita' ************/

  return (transitivita);

}

int controllo_simmetria(rel_bin verifica)
{
  /*variabili contatore*/
  int i,
      j,
      /*variabile per controllare se c'e' stato un riscontro*/
      riscontro,
      /*variabile per controllare la simmetria*/
      simmetria;

  simmetria = 1;


  i = 0;
  j = 0;
  riscontro = 0;

  /*controllo della simmetria per numeri*/

  while ( i < verifica.dimensione)
  {

    j = 0;
    while ( j < verifica.dimensione)
    {

      if (verifica.primo_termine[i] ==
          verifica.secondo_termine[j])
        if (verifica.primo_termine[j] ==
            verifica.secondo_termine[i])
          riscontro++;
      j++;
    }

    if (riscontro == 0)
    {
      j = verifica.dimensione;
      i = verifica.dimensione;
      simmetria = 0;
    }
    riscontro = 0;
    i++;
  }

  return (simmetria);
}


int relazione_equivalenza(rel_bin verifica)
{

  /*variabili per controllare le propieta' dell'equivalenza*/
  int riflessivita,
      simmetria,
      transitivita,
      equivalenza;

  equivalenza = 0;
  riflessivita = controllo_riflessivita(verifica);
  simmetria = controllo_simmetria(verifica);
  transitivita = controllo_transitivita(verifica);

  if (riflessivita == 1 && simmetria == 1 && transitivita == 1)
  {
    printf ("\n  E' una relazione di equivalenza\n");
    equivalenza = 1;
  }

  if (riflessivita == 0)
  {
    printf ("\n  Non e'una relazione di equivalenza ");
    printf ("perche' non e' riflessiva\n");
  }
  if (simmetria == 0)
  {
    printf ("\n  Non e'una relazione di equivalenza ");
    printf ("perche' non e' simmetrica\n");
  }
  if (transitivita == 0)
  {
    printf ("\n  Non e'una relazione di equivalenza ");
    printf ("perche' non e' transitiva\n");
  }
  return (equivalenza);
}


void controllo_congruenza(rel_bin relazione,
                          insieme_t insieme,
                          operazione_t operazione,
                          int chiusura)
{
  printf("\n\n ********* CONTROLLO LA CONGRUENZA");
  printf(" ***************************\n");
  /*variabile per il controllo dell'equivalenza*/
  int equivalenza,
      /*variabile di controllo*/
      controllo,
      /*variabili contatori*/
      i,
      j,
      k;
  if (relazione.dimensione != 0)
    equivalenza = relazione_equivalenza(relazione);
  else
  {
    printf("\n\n  La relazione vuota ");
    printf("non e' una relazione di equivalenza");
    equivalenza = 0;
  }
  i = 0;
  j = 0;
  k = 0;
  controllo = 1;

  for (i = 0; i<relazione.dimensione; i++)
  {
    for (j = 0;
         j<(insieme.numero_elementi*insieme.numero_elementi);
         j++)
    {
      if (relazione.primo_termine[i] ==
          operazione.operando_a[j])
        for (k = 0;
             k<(insieme.numero_elementi*insieme.numero_elementi);
             k++)
          if (relazione.secondo_termine[i] ==
              operazione.operando_a[k] &&
              operazione.operando_b[j] ==
              operazione.operando_b[k])

            if (operazione.risultati[j]
                != operazione.risultati[k])
            {
              controllo = 0;
              k = (insieme.numero_elementi*
                   insieme.numero_elementi);

              j = (insieme.numero_elementi*
                   insieme.numero_elementi);

              i = relazione.dimensione;
            }
      if (relazione.primo_termine[i] ==
          operazione.operando_b[j])
        for (k = 0;
             k < insieme.numero_elementi*insieme.numero_elementi;
             k++)
          if (relazione.secondo_termine[i] ==
              operazione.operando_b[k] &&
              operazione.operando_a[j] ==
              operazione.operando_a[k])

            if (operazione.risultati[j] !=
                operazione.risultati[k])
            {
              controllo = 0;
              k =  insieme.numero_elementi*
                   insieme.numero_elementi;

              j =  insieme.numero_elementi*
                   insieme.numero_elementi;

              i = relazione.dimensione;
            }
    }
  }


  if (equivalenza == 0 || controllo == 0 || chiusura == 0)
    printf("\n\n  La congruenza non e' verificata\n");
  else
    printf("\n\n  La congruenza e' verificata\n");

  return;
}
