/*
 * Ampere 0.1 rev. 1250 - 04.05.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
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
	pulisciBuffer();
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
	printf("\nSembra che quest'artista non esista nel database, inseriamolo.");
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
		printf("\n%s", db.artista[i].nomearte);
		if (comparaStringhe(db.artista[i].nomearte, nomearte)==0) {
			id = db.artista[i].id;
			printf("\nArtista presente nel database.");
			controllo=-1;
		}
		i++;
	}
	if (controllo!=-1) {
		id = creaArtistaGuidato(nomearte);
		printf("\nArtista inserito, continuiamo...");
	}
	return id;
}

int inserisciArtista(char nome[], char cognome[], char nomearte[]) {
	db_modificato=1;
	int n=contaNelDatabase(2);
	db.artista[n].id = trovaUltimoId(2)+1;
	strcpy(db.artista[n].nome,nome);
	strcpy(db.artista[n].cognome,cognome);
	strcpy(db.artista[n].nomearte,nomearte);
	return db.artista[n].id;
}

void inserisciArtistiSuFile(char id[], char nome[], char cognome[], char nomearte[]) {
	FILE* fp=fopen(file_artisti, "a");
	if (controllaSeFileVuoto(file_artisti)==1) {
		fprintf(fp, "%s,%s,%s,%s", id, nome, cognome, nomearte);
	} else {
		fprintf(fp, "\n%s,%s,%s,%s", id, nome, cognome, nomearte);
	}
	fclose(fp);
}

void inserisciAssociazioneArtistiSuFile(char idbrano[], char idartista[]) {
	FILE* fp=fopen(file_associazioneartisti, "a");
	if (controllaSeFileVuoto(file_associazioneartisti)==1) {
		fprintf(fp, "%s,%s", idbrano, idartista);
	} else {
		fprintf(fp, "\n%s,%s", idbrano, idartista);
	}
	fclose(fp);
}
