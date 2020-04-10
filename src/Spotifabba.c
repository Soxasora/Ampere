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
void inizializzazione();
void creaDatabaseSeNonEsiste();
void inserimento(int scelta);
void inserisciBrano(char titolo[], char artista[], char anno[], char album[]);
void menu();

int main() {
	inizializzazione();
	menu();

	system("PAUSE");
	return 0;
}

void inizializzazione() {
	// Visualizza informazioni su Spotifabba
	printf("Spotifabba 0.0.1 rev.2 - nightly build 3\n");
	printf("\nBenvenuto su Spotifabba.");
	creaDatabaseSeNonEsiste();
	// Controllo configurazione

	// Test database


	/*
	//TODO: Creazione di utenti
	// Effettua login per poter accedere alla propria libreria
	login();*/
}

void creaDatabaseSeNonEsiste() {
	FILE* fp;
	char* file = "database.txt";
	fp=fopen(file, "ab+");
	if(fp == NULL)
		printf("Impossibile aprire e/o creare il database.");
	fclose(fp);
}

void inserimento(int scelta) {
	if(scelta==0) { //dunque brano
		// Flush per evitare indesiderati comportamenti dell'input
		int c;
		while ((c = getchar()) != '\n' && c != EOF) { }
		// Allocazione della memoria
		char *titolo = malloc(MAX_CHAR);
		char *artista = malloc(MAX_CHAR);
		char *anno = malloc(MAX_CHAR);
		char *album = malloc(MAX_CHAR);
		printf("\nInserisci titolo: ");
		fgets(titolo, MAX_CHAR, stdin); // Al posto di scanf per gestire gli spazi, evitare overflow
		strtok(titolo, "\n"); // In modo da evitare indesiderati newline
		printf("\nInserisci artista: ");
		fgets(artista, MAX_CHAR, stdin);
		strtok(artista, "\n");
		printf("\nInserisci anno di incisione: ");
		fgets(anno, MAX_CHAR, stdin);
		strtok(anno, "\n");
		printf("\nInserisci titolo dell'album: ");
		fgets(album, MAX_CHAR, stdin);
		strtok(album, "\n");
		inserisciBrano(titolo, artista, anno, album);
		// Libero la memoria
		free(titolo); free(artista); free(anno); free(album);
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

// Inserimento del brano su base Titolo/Artista/Anno di incisione/Album
void inserisciBrano(char titolo[], char artista[], char anno[], char album[]) {
	FILE* fp=fopen("database.txt", "a");
	fprintf(fp, "Titolo: %s", titolo);
	fprintf(fp, "\nArtista: %s", artista);
	fprintf(fp, "\nAnno: %s", anno);
	fprintf(fp, "\nAlbum: %s", album);
	fputs("\n-\n", fp);
	fclose(fp);
	printf("\nBrano inserito.");
}

void cercaBrano() {
	FILE* fp=fopen("database.txt", "r");
	char temp[1000];
	char brani[1000][1000];
	fgets(temp, 1000, fp);
	fclose(fp);
	char spaziatore[] = "\n";
	char *ptr = strtok(temp, spaziatore);
	while(ptr != NULL)
		{
			printf("'%s'\n", ptr);
			ptr = strtok(NULL, spaziatore);
		}
}

// Menu principale di Spotifabba
void menu() {
	int scelta=-1;
	do {
		printf("\n[1] Inserimento brano nel database");
		printf("\n[2] TODO: Ricerca brano nel database");
		printf("\n[3] TODO: Mostra i miei brani");
		printf("\n[4] TODO: Condividi un mio brano");
		printf("\n[5] TODO: Riproduci un mio brano");
		printf("\n[0] Esci dal programma");
		printf("\nInserisci la tua scelta: ");
		scanf("%d", &scelta);
	} while (scelta==-1);

	if(scelta==1) {
		inserimento(0);
	} else if (scelta==2) {
		cercaBrano();
	} else if (scelta==3) {
		//TODO
	} else if (scelta==4) {
		//TODO
	} else if (scelta==5) {
		// TODO
	} else if (scelta==0) {
		printf("\nUscendo dal programma...");
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
