/*
 * GestoreBrani.c
 *
 *  Created on: 2 mag 2020
 *      Author: soxas
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../gestori/GestoreBrani.h"
#include "../gestori/GestoreArtisti.h"
#include "../gestori/GestoreAlbum.h"
#include "../database/Database.h"
#include "../database/DatabaseUtils.h"
#include "../sys/Utils.h"
#include "../sys/Impostazioni.h"

void inserimentoBranoGuidato() {
	pulisciBuffer();
	char *titolo = malloc(MAX_CHAR);
	char *artista = malloc(MAX_CHAR);
	int id_artista=0;
	char *album = malloc(MAX_CHAR);
	int id_album=0;
	int durata=0;
	int anno=0;
	int ascolti=0;
	// Registrazione
	printf("\nInserisci titolo: ");
	titolo = inputStringaSicuro(titolo);
	printf("\nInserisci nome artista: ");
	artista = inputStringaSicuro(artista);
	id_artista = creaArtistaSeNonEsiste(artista);
	printf("\nInserisci nome album: ");
	album = inputStringaSicuro(album);
	id_album = creaAlbumSeNonEsiste(album);
	printf("\nInserisci durata del brano in secondi: ");
	scanf("%d", &durata);
	printf("\nInserisci anno d'uscita del brano: ");
	scanf("%d", &anno);
	printf("\nInserisci numero d'ascolti del brano: ");
	scanf("%d", &ascolti);
	inserisciBrano(titolo, id_artista, id_album, durata, anno, ascolti);
	free(titolo); free(artista); free(album);
	printf("\n\nBrano Inserito.");
}

void inserisciBrano(char titolo[], int id_artista, int id_album, int durata, int anno, int ascolti) {
	// Inserimento brano nel database
	int n=contaNelDatabase(0);
	db.brano[n].id = trovaUltimoId(0)+1;
	strcpy(db.brano[n].titolo,titolo);
	db.brano[n].durata = durata;
	db.brano[n].album = id_album;
	db.brano[n].anno = anno;
	db.brano[n].ascolti = ascolti;

	// Associazioni
	int n_artista_brano=contaNelDatabase(5);
	int n_album_brano=contaNelDatabase(6);
	db.artistaBrano[n_artista_brano].idBrano = db.brano[n].id;
	db.artistaBrano[n_artista_brano].idArtista = id_artista;
	db.albumBrano[n_album_brano].idAlbum = id_album;
	db.albumBrano[n_album_brano].idBrano = db.brano[n].id;
}

void inserisciBranoSuFile(char id[], char titolo[], char durata[], char id_album[], char anno[], char ascolti[]) {
	FILE* fp=fopen(file_brani, "a");
	if (controllaSeFileVuoto(file_brani)==1) {
		fprintf(fp, "%s,%s,%s,%s,%s,%s", id, titolo, durata, id_album, anno, ascolti);
	} else {
		fprintf(fp, "\n%s,%s,%s,%s,%s,%s", id, titolo, durata, id_album, anno, ascolti);
	}
	fclose(fp);
}

