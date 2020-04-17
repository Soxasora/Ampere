/*
 * FabbAmp 0.1 rev.99 - 17.04.2020
 * Copyright (c) 2020, Michele Barile, Nicolo' Cucinotta, Simone Cervino.
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
#include "GestoreBrani.h"
#include "Database.h"
#include "FabbAmp.h"
#include "MotoreRicerca.h"
#include "Utils.h"

// FUNZIONI FILE
// Inserimento di informazioni direttamente nel database file-based
void inserimentoGuidato() {
	// Flush per evitare indesiderati comportamenti dell'input
	pulisciBuffer();
	// Allocazione della memoria
	char *titolo = malloc(MAX_CHAR);
	char *artista = malloc(MAX_CHAR);
	char *album = malloc(MAX_CHAR);
	char *durata = malloc(MAX_CHAR);
	char *anno = malloc(MAX_CHAR);
	char *ascolti = malloc(MAX_CHAR);
	char *gradimento = malloc(MAX_CHAR);
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
	printf("\nInserisci numero di ascolti: ");
	fgets(ascolti, MAX_CHAR, stdin);
	strtok(ascolti, "\n");
	printf("\nInserisci gradimento: ");
	fgets(gradimento, MAX_CHAR, stdin);
	strtok(gradimento, "\n");
	// Memorizzo le informazioni direttamente nel file
	// TODO: Passare ad un sistema esclusivamente struct per poi memorizzare nel file
	inserisciBranoGuidato(0, titolo, artista, album, durata, anno, ascolti, gradimento);
	// Libero la memoria
	free(titolo); free(artista); free(album); free(durata); free(anno); free(ascolti); free(gradimento);
	// Possibilitï¿½ di scelta da parte dell'utente
	int scelta_2=0;
	printf("\nVuoi inserire un altro brano? [0/1]: ");
	scanf("%d", &scelta_2);
	if(scelta_2==1)
		inserimentoGuidato();
	else
		menu();
}

// Inserimento del brano su base Titolo/Artista/Album/Durata/Anno di incisione
void inserisciBranoGuidato(int modalita, char titolo[], char artista[], char album[], char durata[], char anno[], char ascolti[], char gradimento[]) {
	FILE* fp=fopen("database.txt", "a");
	if (controllaSeFileVuoto()==1) {
		fprintf(fp, "%s,%s,%s,%s,%s,%s,%s", titolo, artista, album, durata, anno, ascolti, gradimento);
	} else {
		fprintf(fp, "\n%s,%s,%s,%s,%s,%s,%s", titolo, artista, album, durata, anno, ascolti, gradimento);
	}
	fclose(fp);
	if (modalita==0) {
		free(brani);
		brani = ottieniDatabase();
		printf("\nBrano inserito.");
	}
}

void inserimentoDiretto() {
	// Flush per evitare indesiderati comportamenti dell'input
	pulisciBuffer();
	char *stringa = malloc(MAX_CHAR*5); // MAX_CHAR*5 poiché ci sono 5 informazioni alle quali precedentemente abbiamo dato solo un MAX_CHAR
	printf("\nInserisci ora il tuo brano: ");
	fgets(stringa, MAX_CHAR*5, stdin);
	strtok(stringa, "\n");
	inserisciBranoDiretto(stringa);
	free(stringa);
	int scelta_2=0;
	printf("\nVuoi inserire un altro brano? [0/1]: ");
	scanf("%d", &scelta_2);
	if(scelta_2==1)
		inserimentoDiretto();
	else
		menu();
}

// Funzione DEV per l'inserimento diretto di un brano
void inserisciBranoDiretto(char stringa[]) {
	FILE* fp=fopen("database.txt", "a");
	if (controllaSeFileVuoto()==1) {
		fprintf(fp, "%s", stringa);
	} else {
		fprintf(fp, "\n%s", stringa);
	}
	fclose(fp);
	free(brani);
	brani = ottieniDatabase();
	printf("\nBrano inserito.");
}

void modifica(int scelta) {
	int pos;
	printf("\n===Sistema di modifica dei brani===");
	printf("\nScegliere il brano da modificare");
	aspetta();
	elencaTuttiBrani();
	printf("\n\nInserire il numero del brano da modificare: ");
	scanf("%d", &pos);
	pos--;
	printf("\nHai scelto il brano: ");
	elencaSingoloBrano(pos);
	modificaSingoloBrano(pos, scelta);
	aggiornaDatabase();
}

void modificaSingoloBrano(int pos, int modalita) {
	if (modalita==1) {
		pulisciBuffer();
		char *titolo = malloc(MAX_CHAR);
		printf("\nInserisci nuovo titolo: ");
		fgets(titolo, MAX_CHAR, stdin); // Al posto di scanf per gestire gli spazi, evitare overflow
		strtok(titolo, "\n"); // In modo da evitare indesiderati newline
		strcpy(brani[pos].titolo, titolo);
		free(titolo);
	} else if (modalita==2) {
		pulisciBuffer();
		char *artista = malloc(MAX_CHAR);
		printf("\nInserisci nuovo artista: ");
		fgets(artista, MAX_CHAR, stdin); // Al posto di scanf per gestire gli spazi, evitare overflow
		strtok(artista, "\n"); // In modo da evitare indesiderati newline
		strcpy(brani[pos].artista, artista);
		free(artista);
	} else if (modalita==3) {
		pulisciBuffer();
		char *album = malloc(MAX_CHAR);
		printf("\nInserisci nuovo album: ");
		fgets(album, MAX_CHAR, stdin); // Al posto di scanf per gestire gli spazi, evitare overflow
		strtok(album, "\n"); // In modo da evitare indesiderati newline
		strcpy(brani[pos].album, album);
		free(album);
	} else if (modalita==4) {
		pulisciBuffer();
		char *durata = malloc(MAX_CHAR);
		printf("\nInserisci nuova durata: ");
		fgets(durata, MAX_CHAR, stdin); // Al posto di scanf per gestire gli spazi, evitare overflow
		strtok(durata, "\n"); // In modo da evitare indesiderati newline
		strcpy(brani[pos].durata, durata);
		free(durata);
	} else if (modalita==5) {
		pulisciBuffer();
		int anno=0;
		printf("\nInserisci nuovo anno: ");
		scanf("%d", &anno);
		brani[pos].anno=anno;
	} else if (modalita==6) {
		pulisciBuffer();
		int ascolti=0;
		printf("\nInserisci nuovo numero di ascolti: ");
		scanf("%d", &ascolti);
		brani[pos].ascolti=ascolti;
	} else if (modalita==7) {
		pulisciBuffer();
		float gradimento=0.0;
		printf("\nInserisci nuovo gradimento: ");
		scanf("%f", &gradimento);
		brani[pos].gradimento=gradimento;
	}

	printf("\nBrano aggiornato. Ecco il risultato:");
	elencaSingoloBrano(pos);
}
