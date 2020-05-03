/*
 * GestoreArtisti.c
 *
 *  Created on: 3 mag 2020
 *      Author: Simone
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../gestori/GestoreArtisti.h"
#include "../database/Database.h"
#include "../database/DatabaseUtils.h"
#include "../sys/Utils.h"
#include "../sys/Impostazioni.h"

void inserimentoArtistaGuidato() {
	char *nomearte = malloc(MAX_CHAR);
	printf("\nInserisci nome d'arte dell'artista: ");
	nomearte = inputStringaSicuro(nomearte);
	creaArtistaSeNonEsiste(nomearte);
	free(nomearte);
}

int creaArtistaGuidato(char nomearte[]) {
	int id=0;
	char *nome = malloc(MAX_CHAR);
	char *cognome = malloc(MAX_CHAR);
	printf("\nSembra che quest'artista non esiste nel database, inseriamolo.");
	printf("\n===[Inserimento guidato di un artista]===");
	printf("\nInserisci nome dell'artista: ");
	nome = inputStringaSicuro(nome);
	printf("\nInserisci cognome dell'artista: ");
	cognome = inputStringaSicuro(cognome);
	id = inserisciArtista(nome, cognome, nomearte);
	free(nome); free(cognome);
	return id;
}

int creaArtistaSeNonEsiste(char nomearte[]) {
	int id=0, i=0, n=contaNelDatabase(2), controllo=0;
	while (i<n&&controllo!=-1) {
		if (comparaStringhe(db.artista[i].nomearte, nomearte)==0) {
			id = db.artista[i].id;
			printf("\nArtista presente nel database.");
			controllo=-1;
		}
		i++;
	}
	if (controllo!=-1) {
		id = creaArtistaGuidato(nomearte);
	}
	return id;
}

int inserisciArtista(char nome[], char cognome[], char nomearte[]) {
	int n=contaNelDatabase(2);
	db.artista[n].id = trovaUltimoId(2)+1;
	strcpy(db.artista[n].nome,nome);
	strcpy(db.artista[n].cognome,cognome);
	strcpy(db.artista[n].nomearte,nomearte);
	return db.artista[n].id;
}
