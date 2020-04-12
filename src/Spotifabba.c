/*
 * Spotifabba 0.0.1 rev.2 - 09.04.2020
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
void elencaBrani();
database* ottieniDatabase();
void menu();

int numero_brani=0;

int main() {
	// Inizializza il programma
	inizializzazione();
	// Mostra il menu
	menu();

	//TODO: Cambiare in un sistema multipiattaforma.
	system("PAUSE");
	return 0;
}

void inizializzazione() {
	// Visualizza informazioni su Spotifabba
	printf("Spotifabba 0.0.1 rev.27\n");
	printf("\nBenvenuto su Spotifabba.");
	// Crea database se esso non è presente nella cartella.
	creaDatabaseSeNonEsiste();
}

// Funzione di controllo e creazione del database
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
	if(scelta==0) { //dunque brano
		// Flush per evitare indesiderati comportamenti dell'input
		int c;
		while ((c = getchar()) != '\n' && c != EOF) { }
		// Allocazione della memoria
		char *titolo = malloc(MAX_CHAR);
		char *artista = malloc(MAX_CHAR);
		char *album = malloc(MAX_CHAR);
		char *durata = malloc(MAX_CHAR);
		char *anno = malloc(MAX_CHAR);
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
		inserisciBrano(titolo, artista, album, durata, anno);
		// Libero la memoria
		free(titolo); free(artista); free(album); free(durata); free(anno);
		// Possibilità di scelta da parte dell'utente
		int scelta_2=0;
		printf("\nVuoi inserire un altro brano? [0/1]: ");
		scanf("%d", &scelta_2);
		if(scelta_2==1)
			inserimento(0);
		else
			menu();
	}
}

// Inserimento del brano su base Titolo/Artista/Album/Durata/Anno di incisione
void inserisciBrano(char titolo[], char artista[], char album[], char durata[], char anno[]) {
	FILE* fp=fopen("database.txt", "a");
	fprintf(fp, "%s,%s,%s,%s,%s\n", titolo, artista, album, durata, anno);
	fclose(fp);
	printf("\nBrano inserito.");
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
database* ottieniDatabase() {
	printf("\nOttengo il database");
	//Allocazione di memoria
	database *brani = malloc(sizeof(brani)*1000);
	FILE* fp=fopen("database.txt", "r"); // Apro database
	printf(".");
	char temp[1000]; // Variabile temporanea per ottenere i dati
	char dati[1000][1000]; // Array temporaneo per trasportare i dati
	char spaziatore[] = ","; // Il database divide i dati utilizzando lo spaziatore ,
	int i, j;
	i=0;
	while(!feof(fp)) { // Fino a quando non arriva alla fine del file
		fgets(temp, 1000, fp); // Ottiene la linea
		char *ptr = strtok(temp, spaziatore); // Imposta lo spaziatore
		j=0;
		while(ptr!=NULL) { // Fino a quando il puntatore non ha più niente da trasportare
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
	printf(".");
	numero_brani=i; // TODO: Trovare un metodo migliore per far sapere al programma il numero dei brani
	fclose(fp);
	printf(". Fatto.\n");
	return brani;
}

// Menu principale di Spotifabba
void menu() {
	int scelta=-1;
	do {
		printf("\n[1] Inserimento brano nel database");
		printf("\n[2] TODO: Ricerca brano nel database");
		printf("\n[3] Mostra i miei brani");
		printf("\n[4] TODO: Condividi un mio brano");
		printf("\n[5] TODO: Riproduci un mio brano");
		printf("\n[0] Esci dal programma");
		printf("\n[11] DEBUG");
		printf("\nInserisci la tua scelta: ");
		scanf("%d", &scelta);
	} while (scelta==-1);

	if(scelta==1) {
		inserimento(0);
	} else if (scelta==2) {
		//cercaBrano();
	} else if (scelta==3) {
		elencaBrani();
	} else if (scelta==4) {
		//TODO
	} else if (scelta==5) {
		// TODO
	} else if (scelta==11) {
		// Da usare per debuggare
	} else if (scelta==0) {
		printf("\nUscendo dal programma...\n");
	}
}

//TODO: Creazione di utenti
/*
void login() {
	int scelta=0;
	printf("Vuoi creare un utente[0] oppure effettuare il login[1]? [0/1]: ");
	scanf("%d", scelta);
	if(scelta==0)
		creazioneUtente();
	else if(scelta==1)

		printf("\nInserisci nome utente: ");
}

void creazioneUtente() {
	printf("Inserisci ");
}
*/
