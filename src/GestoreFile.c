/*
 * Spotifabba 0.1 rev.50 - 13.04.2020
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
#include "Spotifabba.h"
#include "GestoreFile.h"
#include "Database.h"

// FUNZIONI FILE
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
	fprintf(fp, "\n%s,%s,%s,%s,%s", titolo, artista, album, durata, anno);
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
