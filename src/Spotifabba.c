/*
 * Spotifabba 0.0.1 rev.40 - 13.04.2020
 * Copyright (c) 2020, Simone Cervino.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CHAR 256
//#include <gestorefile.h>

// Struttura per mantenere in memoria la Libreria Musicale di Spotifabba
// TODO: Passare ad allocazione dinamica
typedef struct libreriaMusicale {
	char titolo[MAX_CHAR];
	char artista[MAX_CHAR];
	char album[MAX_CHAR];
	char durata[MAX_CHAR];
	int anno;
} database;

void inizializzazione();
void creaDatabaseSeNonEsiste();
void inserimento(int scelta);
void inserisciBrano(char titolo[], char artista[], char album[], char durata[], char anno[]);
void inserisciBranoDiretto(char stringa[]);
void ricercaBrani(int modalita);
void elencaSingoloBrano(database *brani, int i);
void elencaBrani();
database* ottieniDatabase();
void menu(int scelta);
void menuDatabase();
void menuRicerca();

int numero_brani=0; // TODO: Trovare un metodo migliore

int main() {
	// Inizializza il programma
	inizializzazione();
	// Mostra il menu
	menu(-1);

	//TODO: Cambiare in un sistema multipiattaforma.
	printf("Spotifabba terminato.\n");
	#ifdef _WIN32
		system("PAUSE");
	#endif
	return 0;
}

void inizializzazione() {
	// Visualizza informazioni su Spotifabba
	printf("Spotifabba 0.0.1 rev.40\n");
	printf("\nBenvenuto su Spotifabba.");
	// Crea database se esso non ï¿½ presente nella cartella.
	creaDatabaseSeNonEsiste();
}

// Funzione di controllo e creazione del database
// TODO: Creare legenda del database ad inizio file
void creaDatabaseSeNonEsiste() {
	FILE* fp;
	char* file = "database.txt";
	fp=fopen(file, "ab+");
	// Se non ha i permessi per scrivere nella cartella:
	if(fp == NULL)
		printf("Impossibile aprire e/o creare il database.");
	fclose(fp);
}

// Inserimento di informazioni direttamente nel database file-based
void inserimento(int scelta) {
	if(scelta==0) { // Inserimento guidato di un brano
		// Flush per evitare indesiderati comportamenti dell'input
		int c;
		while ((c = getchar()) != '\n' && c != EOF) { }
		// Allocazione della memoria
		char *titolo = malloc(MAX_CHAR);
		char *artista = malloc(MAX_CHAR);
		char *album = malloc(MAX_CHAR);
		char *durata = malloc(MAX_CHAR);
		char *anno = malloc(MAX_CHAR);
		// Registrazione informazioni
		printf("\nInserisci titolo: ");
		fgets(titolo, MAX_CHAR, stdin); // Al posto di scanf per gestire gli spazi, evitare overflow
		strtok(titolo, "\n"); // In modo da evitare indesiderati newline
		printf("\nInserisci artista: ");
		fgets(artista, MAX_CHAR, stdin);
		strtok(artista, "\n");
		printf("\nInserisci titolo dell'album: ");
		fgets(album, MAX_CHAR, stdin);
		strtok(album, "\n");
		printf("\nInserisci durata: ");
		fgets(durata, MAX_CHAR, stdin);
		strtok(durata, "\n");
		printf("\nInserisci anno di incisione: ");
		fgets(anno, MAX_CHAR, stdin);
		strtok(anno, "\n");
		// Memorizzo le informazioni direttamente nel file
		// TODO: Passare ad un sistema esclusivamente struct per poi memorizzare nel file
		inserisciBrano(titolo, artista, album, durata, anno);
		// Libero la memoria
		free(titolo); free(artista); free(album); free(durata); free(anno);
		// Possibilitï¿½ di scelta da parte dell'utente
		int scelta_2=0;
		printf("\nVuoi inserire un altro brano? [0/1]: ");
		scanf("%d", &scelta_2);
		if(scelta_2==1)
			inserimento(0);
		else
			menu(-1);
	} else if (scelta==1) {
		// Flush per evitare indesiderati comportamenti dell'input
		int c;
		while ((c = getchar()) != '\n' && c != EOF) { }
		char *stringa = malloc(MAX_CHAR*5); // MAX_CHAR*5 poiché ci sono 5 informazioni alle quali precedentemente abbiamo dato solo un MAX_CHAR
		printf("\nBenvenuto nell'inserimento diretto di un brano.");
		printf("\nIl modello per inserire un brano è il seguente:");
		printf("\nTITOLO,ARTISTA,ALBUM,DUR:ATA,ANNO");
		printf("\nEsempio: Get Lucky,Daft Punk,Random Access Memories,4:09,2013");
		printf("\nInserisci ora il tuo brano: ");
		fgets(stringa, MAX_CHAR*5, stdin);
		strtok(stringa, "\n");
		inserisciBranoDiretto(stringa);
		free(stringa);
		int scelta_2=0;
		printf("\nVuoi inserire un altro brano? [0/1]: ");
		scanf("%d", &scelta_2);
		if(scelta_2==1)
			inserimento(0);
		else
			menu(-1);
	}
}

// Inserimento del brano su base Titolo/Artista/Album/Durata/Anno di incisione
void inserisciBrano(char titolo[], char artista[], char album[], char durata[], char anno[]) {
	FILE* fp=fopen("database.txt", "a");
	fprintf(fp, "%s,%s,%s,%s,%s\n", titolo, artista, album, durata, anno);
	fclose(fp);
	printf("\nBrano inserito.");
}

// Funzione DEV per l'inserimento diretto di un brano
void inserisciBranoDiretto(char stringa[]) {
	FILE* fp=fopen("database.txt", "a");
	fprintf(fp, "%s\n", stringa);
	fclose(fp);
	printf("\nBrano inserito.");
}

// Funzione di ricerca brani in base alla loro anagrafica
void ricercaBrani(int modalita) {
	database *brani = ottieniDatabase();
	int scelta=0;
	if (modalita==0) {
		// Flush per evitare indesiderati comportamenti dell'input
		int c;
		while ((c = getchar()) != '\n' && c != EOF) { }
		char *titolo = malloc(MAX_CHAR);
		printf("\nInserisci titolo: ");
		fgets(titolo, MAX_CHAR, stdin);
		strtok(titolo, "\n");
		int i=0;
		printf("\nTrovate le seguenti occorrenze:\n\n");
		while(i<numero_brani) {
			if (strcmp(titolo, brani[i].titolo)==0) {
				elencaSingoloBrano(brani, i);
			}
			i++;
		}
		free(titolo);
		printf("\nCercare un altro brano per Titolo[0] oppure ritornare al Menu di ricerca[1]? ");
		scanf("%d", &scelta);
		if (scelta==0) {
			ricercaBrani(0);
		} else {
			menuRicerca();
		}
	// Ricerca per Artista
	} else if (modalita==1) {
		int c;
		while ((c = getchar()) != '\n' && c != EOF) { }
		char *artista = malloc(MAX_CHAR);
		printf("\nInserisci artista: ");
		fgets(artista, MAX_CHAR, stdin);
		strtok(artista, "\n");
		int i=0;
		printf("\nTrovate le seguenti occorrenze:\n\n");
		while(i<numero_brani) {
			if (strcmp(artista, brani[i].artista)==0) {
				elencaSingoloBrano(brani, i);
			}
			i++;
		}
		free(artista);
		printf("\nCercare un altro brano per Artista[0] oppure ritornare al Menu di ricerca[1]? ");
		scanf("%d", &scelta);
		if (scelta==0) {
			ricercaBrani(1);
		} else {
			menuRicerca();
		}
	// Ricerca per Album
	} else if (modalita==2) {
		int c;
		while ((c = getchar()) != '\n' && c != EOF) { }
		char *album = malloc(MAX_CHAR);
		printf("\nInserisci album: ");
		fgets(album, MAX_CHAR, stdin);
		strtok(album, "\n");
		int i=0;
		printf("\nTrovate le seguenti occorrenze:\n\n");
		while(i<numero_brani) {
			if (strcmp(album, brani[i].album)==0) {
				elencaSingoloBrano(brani, i);
			}
			i++;
		}
		free(album);
		printf("\nCercare un altro brano per Album[0] oppure ritornare al Menu di ricerca[1]? ");
		scanf("%d", &scelta);
		if (scelta==0) {
			ricercaBrani(2);
		} else {
			menuRicerca();
		}
	} else if (modalita==3) {
		int c;
		while ((c = getchar()) != '\n' && c != EOF) { }
		char *durata = malloc(MAX_CHAR);
		printf("\nInserisci durata: ");
		fgets(durata, MAX_CHAR, stdin);
		strtok(durata, "\n");
		int i=0;
		printf("\nTrovate le seguenti occorrenze:\n\n");
		while(i<numero_brani) {
			if (strcmp(durata, brani[i].durata)==0) {
				elencaSingoloBrano(brani, i);
			}
			i++;
		}
		free(durata);
		printf("\nCercare un altro brano per Durata[0] oppure ritornare al Menu di ricerca[1]? ");
		scanf("%d", &scelta);
		if (scelta==0) {
			ricercaBrani(3);
		} else {
			menuRicerca();
		}
	} else if (modalita==4) {
		int anno=0;
		printf("\nInserisci anno: ");
		scanf("%d", &anno);
		int i=0;
		printf("\nTrovate le seguenti occorrenze:\n\n");
		while(i<numero_brani) {
			if (anno==brani[i].anno) {
				elencaSingoloBrano(brani, i);
			}
			i++;
		}
		printf("\nCercare un altro brano per Anno[0] oppure ritornare al Menu di ricerca[1]? ");
		scanf("%d", &scelta);
		if (scelta==0) {
			ricercaBrani(4);
		} else {
			menuRicerca();
		}
	}
}

// Funzione di elencazione di tutte le informazioni di un brano
void elencaSingoloBrano(database *brani, int pos) {
	printf("\nTitolo: %s\n", brani[pos].titolo);
	printf("Artista: %s\n", brani[pos].artista);
	printf("Album: %s\n", brani[pos].album);
	printf("Durata: %s\n", brani[pos].durata);
	printf("Anno: %d\n", brani[pos].anno);
}

// Funzione di elencazione di tutti i brani presenti nel database file-based
void elencaBrani() {
	database *brani = ottieniDatabase();

	printf("Elenco dei brani:\n");
	int i=0;
	while (i<numero_brani) {
		printf("\nBrano n.%d\n", i+1);
		printf("Titolo: %s\n", brani[i].titolo);
		printf("Artista: %s\n", brani[i].artista);
		printf("Album: %s\n", brani[i].album);
		printf("Durata: %s\n", brani[i].durata);
		printf("Anno: %d\n", brani[i].anno);
		i++;
	}
}

// Funzione per trasferire in memoria il database file-based velocizzando la sua lettura.
// TODO: Rendere disponibile lo struct riempito a tutto il programma per evitare inutili ri-accessi
database* ottieniDatabase() {
	printf("\nOttengo il database...");
	//Allocazione di memoria
	database *brani = malloc(sizeof(brani)*1000);
	FILE* fp=fopen("database.txt", "r"); // Apro database
	char temp[1000]; // Variabile temporanea per ottenere i dati
	char dati[1000][1000]; // Array temporaneo per trasportare i dati
	char spaziatore[] = ","; // Il database divide i dati utilizzando lo spaziatore ,
	int i, j;
	i=0;
	while(!feof(fp)) { // Fino a quando non arriva alla fine del file
		fgets(temp, 1000, fp); // Ottiene la linea
		char *ptr = strtok(temp, spaziatore); // Imposta lo spaziatore
		j=0;
		while(ptr!=NULL) { // Fino a quando il puntatore non ha piï¿½ niente da trasportare
			strcpy(dati[j], ptr); // Copia informazione nel punto i dell'array temporaneo
			ptr=strtok(NULL, spaziatore); // Passa al prossimo spaziatore
			j++;
		}
		// Blocco di organizzazione dei dati dall'array temporaneo allo struct finale
		strcpy(brani[i].titolo, dati[0]);
		strcpy(brani[i].artista, dati[1]);
		strcpy(brani[i].album, dati[2]);
		strcpy(brani[i].durata, dati[3]);
		brani[i].anno = atoi(dati[4]); // Conversione da char a int del valore Anno
		i++;
	}
	numero_brani=i; // TODO: Trovare un metodo migliore per far sapere al programma il numero dei brani
	fclose(fp);
	printf(" Fatto.\n");
	return brani;
}

// Menu principale di Spotifabba
void menu(int scelta) {
	do {
		printf("\n[1] Gestisci il database");
		printf("\n[2] Ricerca nel database");
		printf("\n[3] TODO: Condividi un brano");
		printf("\n[4] TODO: Riproduci un brano");
		printf("\n[0] Esci dal programma");
		printf("\n[11] DEBUG");
		printf("\nInserisci la tua scelta: ");
		scanf("%d", &scelta);
	} while (scelta==-1);

	if(scelta==1) {
		menuDatabase();
	} else if (scelta==2) {
		menuRicerca();
	} else if (scelta==3) {
		// TODO
	} else if (scelta==4) {
		// TODO
		#ifdef _WIN32
			system("example.mp3");
		#elif __APPLE__
			system("open example.mp3");
		#elif __linux__
			system("vlc example.mp3");
		#endif
	} else if (scelta==0) {
		printf("\nUscendo dal programma...\n");
	} else if (scelta==11) {
		// DA USARE PER DEBUG

	}
}

void menuDatabase() {
	int scelta=0;
	printf("\n===Menu gestione database===");
	printf("\n[1] Inserimento brano nel database");
	printf("\n[2] TODO: Modifica un brano");
	printf("\n[3] TODO: Cancella un brano");
	printf("\n[0] Torna al menu principale");
	printf("\nInserisci la tua scelta: ");
	scanf("%d", &scelta);
	if (scelta==1) {
		// TODO: Dargli un menu separato
		int sotto_scelta=0;
		printf("\n[1] Inserimento guidato");
		printf("\n[2] Inserimento diretto per utenti avanzati");
		printf("\n[0] Ritorna al menu precedente");
		printf("\nInserisci la tua scelta: ");
		scanf("%d", &sotto_scelta);
		if (sotto_scelta==1)
			inserimento(0);
		else if (sotto_scelta==2)
			inserimento(1);
		else if (sotto_scelta==0)
			menuDatabase();
	} else if (scelta==2) {
		// TODO
	} else if (scelta==3) {
		// TODO
	} else if (scelta==0) {
		menu(-1);
	}
}

void menuRicerca() {
	int scelta=0;
	printf("\n===Menu di ricerca===");
	printf("\n[1] Mostra i miei brani");
	printf("\n[2] Ricerca per Titolo");
	printf("\n[3] Ricerca per Artista");
	printf("\n[4] Ricerca per Album");
	printf("\n[5] Ricerca per Durata");
	printf("\n[6] Ricerca per Anno");
	printf("\n[0] Torna al menu principale");
	printf("\nInserisci la tua scelta: ");
	scanf("%d", &scelta);
	if (scelta==1) {
		elencaBrani();
		int sotto_scelta=0;
		printf("\nRitornare al menu precedente? [0/1]: ");
		scanf("%d", &sotto_scelta);
		if (sotto_scelta==1) {
			menuRicerca();
		}
	} else if (scelta==2) {
		ricercaBrani(0);
	} else if (scelta==3) {
		ricercaBrani(1);
	} else if (scelta==4) {
		ricercaBrani(2);
	} else if (scelta==5) {
		ricercaBrani(3);
	} else if (scelta==6) {
		ricercaBrani(4);
	} else if (scelta==0) {
		menu(-1);
	}
}
