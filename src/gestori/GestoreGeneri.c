/*
 * Ampere 0.1 rev. 2420 - 08.05.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ricerca/MotoreRicerca.h"
#include "../gestori/GestoreUtenti.h"
#include "../gestori/GestoreBrani.h"
#include "../gestori/GestoreAlbum.h"
#include "../gestori/GestoreArtisti.h"
#include "../gestori/GestoreGeneri.h"
#include "../database/Database.h"
#include "../database/DatabaseUtils.h"
#include "../sys/Utils.h"
#include "../sys/Impostazioni.h"

void inserimentoGenereGuidato() {
	pulisciBuffer();
	char *nome = malloc(MAX_CHAR);
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
	int id = controlloEsistenzaGenere(nome);
	if (id==0) {
		id = creaGenereGuidato(nome);
		printf("\nGenere inserito, continuiamo...");
	} else {
		printf("\nGenere esistente.");
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

int controlloEsistenzaGenere(char genere[]) {
	int id=0, i=0, n=contaNelDatabase(3), controllo=0;
	while (i<n&&controllo!=-1) {
		if (comparaStringhe(db.genere[i].nome, genere)==0) {
			id = db.genere[i].id;
			controllo=-1;
		}
		i++;
	}
	return id;
}

void modificaGenere() {
	int id=0, modalita=0;
	char scelta='N';
	mostraTuttiGeneri();
	printf("\n\nInserire l'identificativo del genere da modificare: ");
	scanf("%d", &id);
	printf("\nHai scelto il genere:");
	mostraSingoloGenere(id);
	pulisciBuffer();
	printf("\nSicuro di voler continuare? [Y/N]: ");
	scanf("%c", &scelta);
	if (scelta=='Y'||scelta=='y') {
		printf("\n===[Sistema di modifica genere]===");
		printf("\n[1] Modifica il Nome");
		printf("\n[0] Esci");
		printf("\nInserisci la tua scelta");
		if (modalita!=0) {
			modificaSingoloGenere(id);
		}
	}
}

void modificaSingoloGenere(int id) {
	pulisciBuffer();
	int pos = ottieniPosDaID(3,id);
	char *nome = malloc(MAX_CHAR);
	printf("\nInserisci nuovo nome: ");
	nome = inputStringaSicuro(nome);
	strcpy(db.genere[pos].nome, nome);
	free(nome);
	db_modificato=1;
	printf("\nGenere aggiornato, ecco il risultato:\n");
	mostraSingoloGenere(id);
}

void cancellaGenere() {
	int id=0;
	char scelta='N';
	mostraTuttiGeneri();
	printf("\n\nInserire l'identificativo del genere da cancellare: ");
	scanf("%d", &id);
	printf("\nHai scelto il genere: ");
	mostraSingoloGenere(id);
	pulisciBuffer();
	printf("\nSicuro di voler continuare? Cancellera' anche i brani collegati ad esso. [Y/N]: ");
	scanf("%c", &scelta);
	if (scelta=='Y'||scelta=='y') {
		cancellaSingoloGenere(id);
	}
}

void cancellaSingoloGenere(int id) {
	printf("prova1");
	int n=contaNelDatabase(3);
	int i=ottieniPosDaID(3, id);
	while(i<n-1) {
		db.genere[i] = db.genere[i+1];
		i++;
	}
	db.genere[n-1].id = 0;
	printf("prova2");
	int nbrani=contaNelDatabase(7);
	i=0;
	printf("prova3");
	while (i<nbrani) {
		if(db.branoGenere[i].idGenere==id) {
			cancellaSingoloBrano(db.branoGenere[i].idBrano);
			i=-1;
		}
		i++;
	}
	db_modificato=1;
	printf("\nGenere cancellato.");
}
