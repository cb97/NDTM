
																											//LIBRERIE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

																											//DEFINE

#define OFFSET1 'A'																									//offset dei caratteri maiuscoli
#define OFFSET2 'a' - 27																							//offset dei caratteri minuscoli
#define OFFSET3 '0' - 53																							//offset dei numeri
#define N_CHAR 63																									//numero totale di caratteri
#define true 1
#define false 0
#define MULTIPLIER 1.5
#define MINDIM 64


																											//TYPEDEF


typedef struct tr
{
	int p;
	char s, t;
	struct tr * next;
}	tr;

typedef struct stato
{
	tr * trans[N_CHAR];
	char acc;
}	stato;


typedef struct coda
{
	int i, stato, dim;
	char * nastro;
	struct coda * next, *prev;
}	coda;



																											//VARIABILI GLOBALI

long max;																											//numero massimo di mosse	
stato * ht = NULL;																									//indirizzo del vettore di memorizzazione degli stati
int length;
																											//PROTOTIPI FUNZIONI


void scan2();
void scan();
char * scanString(int *);																									
void calcola(char *, int);

																											//MAIN




int main ()
{
	int dim;
	char * start;
	scan();																										//leggi la configurazione della MT
	while(!feof(stdin))
	{
		start = scanString(&dim);
		if(start[0]!= '_' || !feof(stdin))
			calcola(start, dim);
	}
	return 0;	
}



																										//DEFINIZIONE FUNZIONI



void trInsert2(int q, int p, char l, char s, char tes)
{
	tr * temp = NULL;
	temp = malloc(sizeof(tr));																//crea un'altra cella
	temp->p = p;																				//copia i dati
	temp->s = s;
	temp->t = tes;
	if(l <= '9')																				//se il carattere da leggere è un numero
		l-=OFFSET3;																				//inseriscilo tra 53 e 62
	else if(l<= 'Z')																			//se è una lettera maiuscola
		l-=OFFSET1;																				//tra 0 e 25
		else if(l == '_')																		//se è '_'
			l = 26;																				//in 26
			else																				//altrimenti (lettera minuscola)
				l-= OFFSET2;																	//tra 27 e 52
	temp->next = ht[q].trans[l];																//collega
	ht[q].trans[l] = temp;																		//metti in testa
	return;	
}


tr * lookUp(int s, char c)
{
	tr * t;
	if(s >= length)																				//se lo stato è un pozzo fuori dalla tabella
		return NULL;																			//nessuna transizione
	if(c <= '9')																				//se è un numero
		c-=OFFSET3;																				//cerca tra 53 e 62
	else if(c<= 'Z')																			//se è una lettera maiuscola
		c-=OFFSET1;																				//tra 0 e 25
		else if(c == '_')																		//se è '_'
			c = 26;																				//26
			else																				//altrimenti (lettera minuscola)
				c-= OFFSET2;																	//tra 27 e 52
	t = ht[s].trans[c];																			//prendi il primo elemento
	return t;																					//restituiscilo
}


int extend(len)
{
	int h = len, k;
	len = len * MULTIPLIER;																		//aumenta le dimensioni
	ht = realloc(ht, len * sizeof(stato));
	for(	; h < len; h++)																		//inizializza le nuove caselle
	{
		for(k = 0; k < N_CHAR ; k++)
			ht[h].trans[k] = NULL;
		ht[h].acc = false;
	}
	return len;																					//ritorna le nuove dimensioni
}

int trScan()
{
	char c[11];																					//lunghezza in caratteri del massimo int + 1
	int q, p, max = 0;
	char l, s, t;
	scanf("%s\n", c);																			//leggo "tr"
	scanf("%s ", c);																			//acquisisco la prima stringa della riga seguente
	while(c[0]<='9')																			//finchè il primo carattere di una riga è un
	{																							//numero, le transizioni proseguono
		q = atoi(c);																			//converto la stringa in un intero
		if(q > max)																				//se è superiore al massimo stato attuale
			max = q;																			//diventa il nuovo massimo
		while(q >= length)																		//finchè q non rientra in tabella
			length	= extend(length);															//allarga la tabella
		scanf("%c %c %c %d", &l, &s, &t, &p);													//acquisisci il resto dei dati di transizione
		trInsert2(q, p, l, s, t);																//inserisci in tabella
		scanf("%c",&l);																			//brucia il \n
		scanf("%s ",c);																			//acquisisci una nuova stringa
	}
	return max;																					//restituisci il massimo stato
}


int accScan(int max)
{
	char c [11];																				//lunghezza del massimo int
	int i, h;		
	//"acc" è già stato letto																			
	scanf("%s",c);																				//leggo la stringa della riga seguente
	while(c[0]<='9')																			//finchè il primo carattere di una riga è un numero
	{	
		i = atoi(c);																			//converti la stringa in numero
		if(i > max)																				//se è superiore allo stato massimo
			max = i;																			//diventa lo stato massimo
		while(i >= length)																		//se lo stato supera la dimensione della tabella
		{
			length = extend(length);															//allarga
		}																	
		ht[i].acc = true;																		//segna come stato di accettazione
		scanf("%c%s",&i, c);
	}
	return max;																					//restituisci il massimo
}




void scan()
{
	char c[11];
	int i, j, maxstato;
	length = MINDIM;
	ht = malloc(sizeof(stato) * length);														//crea la tabella
	for(i = 0; i < length; i++)																	//inizializza
	{
		for(j = 0; j < N_CHAR; j++)																//imposta a NULL tutti i puntatori a transizioni
			ht[i].trans[j] = NULL;
		ht[i].acc = false;																		//imposta false allo stato
	}
	maxstato = trScan();																		//leggo e salvo tutte le transizioni
	maxstato = accScan(maxstato);																//leggo e segno tutti gli acc																						//lo ordino
	length = maxstato+1;																		//restringi la tabella al minimo indispensabile
	ht = realloc(ht, length * sizeof(stato));
	scanf("%ld\nrun", &max);																	//leggo il max + "run"
	scanf("%c",c);																				//brucio \n
	return;	

}


char * scanString(int * len)
{
	char * start = NULL;
	int i = 0, dim, done = 0;
	start = malloc(MINDIM);																		//crea il nastro
	start[0] = '_';																				//inizializza a blank la prima cella
	dim = MINDIM;
	if(fgets(start, MINDIM, stdin) != NULL);													//leggi la stringa
	{
		while(!done)																			//finchè non finisci
		{
			for(	; i < dim && !done ; i++)													//controlla i nuovi caratteri
				if(start[i] == '\n' || (i != dim-1 && start[i] =='\0'))							//se trovi un \n, o un \0 non in ultima posizione
				{
					if(i >= 1 && start[i-1] == '\r')											//se prima c'è un \r
						start[i-1] = '_';														//puliscilo
					start[i] = '_';																//pulisci i caratteri
					done = 1;																	//hai finito
				}
			if(!done)																			//se non hai finito
			{
				i--;																			//vai al carattere precedente (\0)
				dim = dim * MULTIPLIER;															//allarga il nastro
				start = realloc(start, dim);
				fgets(&start[i], dim-i, stdin);													//acquisisci nuovo input e mettilo sul carattere corrente
			}
			
		}
		for(	;i < dim; i++)																	//pulisci il resto del nastro
			start[i] = '_';
	}
	*len = dim;																					//segna le dimensioni del nastro
	return start;																				//restituisci il nastro
}


void store (coda * t)
{
	coda * temp = t->next;																		//segna l'elemento successivo a quello attuale
	t->next = malloc(sizeof(coda));																//sostituiscilo con un nuovo elemento
	memcpy(t->next, t, sizeof(coda));															//copia i dati
	t->next->prev = t;																			//collegalo
	t->next->nastro = malloc(t->dim);															//crea un nuovo nastro
	memcpy(t->next->nastro, t->nastro, t->dim);													//copia il vecchio nastro
	t->next->next = temp;																		//collega all'elemento successivo
	if(temp != NULL)																			//se esso esiste
		temp->prev = t->next;																	//collegalo
	return ;
}


void deleteAll(coda * h)
{	
	coda * temp;
	while(h != NULL)																			//finchè esistono rami di computazione
	{
		free(h->nastro);																		//libera il suo nastro
		temp = h->next;																			//segna il successivo ramo
		free(h);																				//libera il ramo corrente
		h = temp;																				//spostati sul ramo successivo
	}
	return ;
}


coda * pop (coda * h, coda * t)
{
	coda * temp, * temp2;
	free(t->nastro);																			//libera il nastro corrente
	if(h == t)																					//se l'elemento da cancellare è la testa di lista
	{
		h = t->next;																			//la testa diventa il successivo
		if(h != NULL)																			//se la testa esiste
			h->prev = NULL;																		//non ha precedenti
	}
	else																						//altrimenti
	{
		t->prev->next = t->next;																//scollega t dalla lista
		if(t->next != NULL)																		//se t aveva un successore
			t->next->prev = t->prev;															//collegalo
	}
	free(t);																					//libera t
	return h;																					//restituisci la testa, eventualmente modificata
}


void mossa(coda * c, tr * t)
{
	char * nastro = c->nastro;																	//copia i dati di transizione in un contesto locale (spreca memoria ma mi viene più comodo, e tanto questa memoria dura poco)
	int i = c->i, k;
	int stato = c->stato;
	int dim = c->dim;
	nastro[i] = t->s;																			//scrivi sul nastro
	stato = t->p;																				//cambia stato
	if(t->t == 'L')																				//se devi andare a sinistra
		if(i != 0)																				//se non sei sul primo carattere del nastro
			i--;																				//vai al carattere precedente
		else 																					//se sei sul primo carattere del nastro
		{
			i = (MULTIPLIER -1) * dim -1;														//spostati sulla nuova posizione
			dim = dim * MULTIPLIER;																//allarga il nastro
			nastro = realloc(nastro, dim);
			memmove(&nastro[i+1], nastro, dim -i-1);											//sposta il nastro a destra
			for(k = 0; k <= i; k++)																//pulisci le nuove celle
				nastro[k] = '_';
		}
	else if(t->t == 'R')																		//se devi andare a destra
		{
			i++;																				//aumenta i
			if(i == dim)																		//se hai sforato il nastro
			{
				dim = dim * MULTIPLIER;
				nastro = realloc(nastro, dim);													//allarga il nastro	
				for(k = i; k < dim; k++)														//pulisci le nuove caselle
					nastro[k] = '_';
			}
		}
	c->nastro = nastro;																			//scrivi sul ramo cosa hai cambiato
	c->i = i;
	c->stato = stato;
	c->dim = dim;
	return;
}

void calcola(char * nastro, int dim)
{
	long mosse = 0;
	int stato, i;
	tr * tr;
	coda * head = NULL, * temp = NULL, * curr = NULL;
	head = malloc(sizeof(coda));																//crea il primo ramo
	head->next = NULL;																			//inizializzalo
	head->nastro = nastro;
	head->stato = 0;
	head->i = 0;
	head->dim = dim;
	head->prev = NULL;
	do																							//esegui
	{
		while (mosse == max && head != NULL)													//quando raggiungi il limite di mosse, finchè hai rami
		{
			if(head->stato < length && ht[head->stato].acc == true)								//se il ramo è su uno stato di accettazione
			{
				deleteAll(head);																//cancella tutto
				printf("1\n");																	//stampa 1
				return ;																		//termina
			}
			else																				//altrimenti
				head = pop(head, head);															//cancella il ramo
		}
		if(mosse == max)																		//se hai raggiunto il limite di mosse
		{
			printf("U\n");																		//stampa U
			deleteAll(head);																	//cancella tutto
			return ;																			//termina
		}
		curr = head;																			//imposta il ramo corrente alla testa
		while(curr != NULL)																		//finchè ci sono rami		
		{
			temp = curr->next;																	//segna il ramo successivo
			stato = curr->stato;																//segna in locale lo stato e la posizione
			i = curr->i;
			if(ht[stato].acc == true)															//se sei su uno stato di accettazione
			{
				printf("1\n");																	//stampa 1
				deleteAll(head);																//cancella tutto
				return ;																		//termina
			}
			if((tr = lookUp(stato, curr->nastro[i])) == NULL)									//cerca una transizione, se non la trovi
				head = pop(head, curr);															//cancella il ramo
			else																				//altrimenti
			{
				while(tr->next != NULL)															//finchè c'è almeno un'altra transizione possibile
				{
					store(curr);																//crea un nuovo ramo
					mossa(curr, tr);															//esegui una mossa sul ramo corrente
					curr = curr->next;															//vai al ramo successivo
					tr = tr->next;																//vai alla transizione successiva
				}
				mossa(curr, tr);																//esegui la mossa
			}
			curr = temp;																		//vai al successivo ramo
		}
		//a questo punto ho fatto una mossa su tutti i rami
		mosse++;																				//aumenta le mosse			
	}
	while(head != NULL);																		//finchè hai rami																					//altrimenti stampa 0
	printf("0\n");																				//stampa 0
	if(head != NULL)																			//sono abbastanza sicuro che sia inutile ma lo metto lo stesso
		deleteAll(head);
	return;
}


