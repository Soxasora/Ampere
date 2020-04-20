/*
 * FabbAmp 0.1 rev. 137 - 19.04.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/FabbAmp/blob/master/LICENSE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GestoreBrani.h"
#include "Database.h"
#include "FabbAmp.h"
#include "MotoreRicerca.h"
#include "Utils.h"
#include "Impostazioni.h"

// FUNZIONI FILE
// Inserimento di informazioni direttamente nel database file-based
void inserimentoGuidato() {
	// Flush per evitare indesiderati comportamenti dell'input
	pulisciBuffer();
	// Allocazione della memoria
	char *titolo = malloc(MAX_CHAR);
	char *artista = malloc(MAX_CHAR);
	char *feat = malloc(MAX_CHAR);
	char *produttore = malloc(MAX_CHAR);
	char *scrittore = malloc(MAX_CHAR);
	char *album = malloc(MAX_CHAR);
	char *durata = malloc(MAX_CHAR);
	char *anno = malloc(MAX_CHAR);
	char *lingua = malloc(MAX_CHAR);
	char *ascolti = malloc(MAX_CHAR);
	char *gradimento = malloc(MAX_CHAR);
	// Registrazione informazioni
	printf("\nInserisci titolo: ");
	fgets(titolo, MAX_CHAR, stdin); // Al posto di scanf per gestire gli spazi, evitare overflow
	strtok(titolo, "\n"); // In modo da evitare indesiderati newline
	printf("\nInserisci artista: ");
	fgets(artista, MAX_CHAR, stdin);
	strtok(artista, "\n");
	printf("\nInserisci feat: ");
	fgets(feat, MAX_CHAR, stdin);
	strtok(feat, "\n");
	printf("\nInserisci produttore: ");
	fgets(produttore, MAX_CHAR, stdin);
	strtok(produttore, "\n");
	printf("\nInserisci scrittore: ");
	fgets(scrittore, MAX_CHAR, stdin);
	strtok(scrittore, "\n");
	printf("\nInserisci titolo dell'album: ");
	fgets(album, MAX_CHAR, stdin);
	strtok(album, "\n");
	printf("\nInserisci durata: ");
	fgets(durata, MAX_CHAR, stdin);
	strtok(durata, "\n");
	printf("\nInserisci anno di incisione: ");
	fgets(anno, MAX_CHAR, stdin);
	strtok(anno, "\n");
	printf("\nInserisci lingua del brano: ");
	fgets(lingua, MAX_CHAR, stdin);
	strtok(lingua, "\n");
	printf("\nInserisci numero di ascolti: ");
	fgets(ascolti, MAX_CHAR, stdin);
	strtok(ascolti, "\n");
	printf("\nInserisci gradimento: ");
	fgets(gradimento, MAX_CHAR, stdin);
	strtok(gradimento, "\n");
	// Memorizzo le informazioni direttamente nel file
	// TODO: Passare ad un sistema esclusivamente struct per poi memorizzare nel file
	inserisciBranoGuidato(0, titolo, artista, feat, produttore, scrittore, album, durata, anno, lingua, ascolti, gradimento);
	// Libero la memoria
	free(titolo); free(artista); free(feat); free(produttore); free(scrittore); free(album); free(durata); free(anno); free(lingua); free(ascolti); free(gradimento);
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
void inserisciBranoGuidato(int modalita, char titolo[], char artista[], char feat[], char produttore[], char scrittore[], char album[], char durata[], char anno[], char lingua[], char ascolti[], char gradimento[]) {
	FILE* fp=fopen(file_database, "a");
	if (controllaSeFileVuoto()==1) {
		fprintf(fp, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s", titolo, artista, album, feat, produttore, scrittore, durata, anno, lingua, ascolti, gradimento);
	} else {
		fprintf(fp, "\n%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s", titolo, artista, album, feat, produttore, scrittore, durata, anno, lingua, ascolti, gradimento);
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
	char *stringa = malloc(MAX_CHAR*11); // MAX_CHAR*5 poiché ci sono 5 informazioni alle quali precedentemente abbiamo dato solo un MAX_CHAR
	printf("\nInserisci ora il tuo brano: ");
	fgets(stringa, MAX_CHAR*11, stdin);
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
	FILE* fp=fopen(file_database, "a");
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
		char *feat = malloc(MAX_CHAR);
		printf("\nInserisci nuovo feat: ");
		fgets(feat, MAX_CHAR, stdin); // Al posto di scanf per gestire gli spazi, evitare overflow
		strtok(feat, "\n"); // In modo da evitare indesiderati newline
		strcpy(brani[pos].feat, feat);
		free(feat);
	} else if (modalita==4) {
		pulisciBuffer();
		char *produttore = malloc(MAX_CHAR);
		printf("\nInserisci nuovo produttore: ");
		fgets(produttore, MAX_CHAR, stdin); // Al posto di scanf per gestire gli spazi, evitare overflow
		strtok(produttore, "\n"); // In modo da evitare indesiderati newline
		strcpy(brani[pos].produttore, produttore);
		free(produttore);
	} else if (modalita==5) {
		pulisciBuffer();
		char *scrittore = malloc(MAX_CHAR);
		printf("\nInserisci nuovo scrittore: ");
		fgets(scrittore, MAX_CHAR, stdin); // Al posto di scanf per gestire gli spazi, evitare overflow
		strtok(scrittore, "\n"); // In modo da evitare indesiderati newline
		strcpy(brani[pos].scrittore, scrittore);
		free(scrittore);
	} else if (modalita==6) {
		pulisciBuffer();
		char *album = malloc(MAX_CHAR);
		printf("\nInserisci nuovo album: ");
		fgets(album, MAX_CHAR, stdin); // Al posto di scanf per gestire gli spazi, evitare overflow
		strtok(album, "\n"); // In modo da evitare indesiderati newline
		strcpy(brani[pos].album, album);
		free(album);
	} else if (modalita==7) {
		pulisciBuffer();
		char *durata = malloc(MAX_CHAR);
		printf("\nInserisci nuova durata: ");
		fgets(durata, MAX_CHAR, stdin); // Al posto di scanf per gestire gli spazi, evitare overflow
		strtok(durata, "\n"); // In modo da evitare indesiderati newline
		strcpy(brani[pos].durata, durata);
		free(durata);
	} else if (modalita==8) {
		pulisciBuffer();
		int anno=0;
		printf("\nInserisci nuovo anno: ");
		scanf("%d", &anno);
		brani[pos].anno=anno;
	} else if (modalita==9) {
		pulisciBuffer();
		int lingua=0;
		printf("\nInserisci nuova lingua: ");
		scanf("%d", &lingua);
		brani[pos].lingua=lingua;
	} else if (modalita==10) {
		pulisciBuffer();
		int ascolti=0;
		printf("\nInserisci nuovo numero di ascolti: ");
		scanf("%d", &ascolti);
		brani[pos].ascolti=ascolti;
	} else if (modalita==11) {
		pulisciBuffer();
		float gradimento=0.0;
		printf("\nInserisci nuovo gradimento: ");
		scanf("%f", &gradimento);
		brani[pos].gradimento=gradimento;
	}

	printf("\nBrano aggiornato. Ecco il risultato:");
	elencaSingoloBrano(pos);
}
