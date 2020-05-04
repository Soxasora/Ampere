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
#include "../gestori/GestoreBrani.h"
#include "../gestori/GestoreArtisti.h"
#include "../gestori/GestoreAlbum.h"
#include "../gestori/GestoreGeneri.h"
#include "../database/Database.h"
#include "../database/DatabaseUtils.h"
#include "../sys/Utils.h"
#include "../sys/Impostazioni.h"

void inserimentoBranoGuidato() {
	char *titolo = malloc(MAX_CHAR);
	char *artista = malloc(MAX_CHAR);
	int id_artista=0;
	char *album = malloc(MAX_CHAR);
	int id_album=0;
	char *genere = malloc(MAX_CHAR);
	int id_genere=0;
	int durata=0;
	int anno=0;
	int ascolti=0;
	// Registrazione
	pulisciBuffer();
	printf("\nInserisci titolo: ");
	titolo = inputStringaSicuro(titolo);
	printf("\nInserisci nome artista: ");
	artista = inputStringaSicuro(artista);
	id_artista = creaArtistaSeNonEsiste(artista);
	printf("\nInserisci nome album: ");
	album = inputStringaSicuro(album);
	id_album = creaAlbumSeNonEsiste(album);
	printf("\nInserisci genere del brano: ");
	pulisciBuffer();
	genere = inputStringaSicuro(genere);
	id_genere = creaGenereSeNonEsiste(genere);
	printf("\nInserisci durata del brano in secondi: ");
	scanf("%d", &durata);
	printf("\nInserisci anno d'uscita del brano: ");
	scanf("%d", &anno);
	printf("\nInserisci numero d'ascolti del brano: ");
	scanf("%d", &ascolti);
	inserisciBrano(titolo, id_artista, id_album, id_genere, durata, anno, ascolti);
	free(titolo); free(artista); free(album); free(genere);
	printf("\n\nBrano Inserito.");
}

void inserisciBrano(char titolo[], int id_artista, int id_album, int id_genere, int durata, int anno, int ascolti) {
	db_modificato=1;
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
	int n_genere_brano=contaNelDatabase(7);
	db.artistaBrano[n_artista_brano].idBrano = db.brano[n].id;
	db.artistaBrano[n_artista_brano].idArtista = id_artista;
	db.albumBrano[n_album_brano].idAlbum = id_album;
	db.albumBrano[n_album_brano].idBrano = db.brano[n].id;
	db.branoGenere[n_genere_brano].idGenere = id_genere;
	db.branoGenere[n_genere_brano].idBrano = db.brano[n].id;

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

