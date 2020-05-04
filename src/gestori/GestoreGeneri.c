/*
 * Ampere 0.0.1 rev. 1000 - 02.05.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/XX/blob/master/LICENSE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../gestori/GestoreGeneri.h"
#include "../database/Database.h"
#include "../database/DatabaseUtils.h"
#include "../sys/Utils.h"
#include "../sys/Impostazioni.h"

void inserimentoGenereGuidato() {
	char *nome = malloc(MAX_CHAR);
	pulisciBuffer();
	printf("\nInserisci nome del genere: ");
	nome = inputStringaSicuro(nome);
	creaGenereSeNonEsiste(nome);
	free(nome);
}

int creaGenereGuidato(char nome[]) {
	int id=0;
	printf("\nSembra che questo genere non esista nel database, provvedo ad inserirlo...");
	id = inserisciGenere(nome);
	return id;
}

int creaGenereSeNonEsiste(char nome[]) {
	int id=0, i=0, n=contaNelDatabase(3), controllo=0;
	while (i<n&&controllo!=-1) {
		if (comparaStringhe(db.genere[i].nome, nome)==0) {
			id = db.genere[i].id;
			printf("\nGenere presente nel database.");
			controllo=-1;
		}
		i++;
	}
	if (controllo!=-1) {
		id = creaGenereGuidato(nome);
		printf("\nGenere inserito, continuiamo...");
	}
	return id;
}

int inserisciGenere(char nome[]) {
	db_modificato=1;
	int n=contaNelDatabase(3);
	db.genere[n].id = trovaUltimoId(3)+1;
	strcpy(db.genere[n].nome, nome);
	return db.genere[n].id;
}

void inserisciGenereSuFile(char id[], char nome[]) {
	FILE* fp=fopen(file_generi, "a");
	if (controllaSeFileVuoto(file_generi)==1) {
		fprintf(fp, "%s,%s", id, nome);
	} else {
		fprintf(fp, "\n%s,%s", id, nome);
	}
	fclose(fp);
}

void inserisciTipiBraniSuFile(char idbrano[], char idgenere[]) {
	FILE* fp=fopen(file_tipobrano, "a");
	if (controllaSeFileVuoto(file_tipobrano)==1) {
		fprintf(fp, "%s,%s", idbrano, idgenere);
	} else {
		fprintf(fp, "\n%s,%s", idbrano, idgenere);
	}
	fclose(fp);
}
