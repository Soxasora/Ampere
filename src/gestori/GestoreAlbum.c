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
#include "../gestori/GestoreAlbum.h"
#include "../database/Database.h"
#include "../database/DatabaseUtils.h"
#include "../sys/Utils.h"
#include "../sys/Impostazioni.h"

void inserimentoAlbumGuidato() {
	pulisciBuffer();
	char *titolo = malloc(MAX_CHAR);
	printf("\nInserisci titolo dell'album: ");
	titolo = inputStringaSicuro(titolo);
	creaAlbumSeNonEsiste(titolo);
	free(titolo);
}

int creaAlbumGuidato(char titolo_album[]) {
	int id=0;
	int anno=0;
	printf("\nSembra che quest'album non esista nel database, inseriamolo.");
	printf("\n===[Inserimento guidato di un album]===");
	printf("\nTitolo: %s", titolo_album);
	printf("\nInserisci l'anno di uscita di quest'album: ");
	scanf("%d", &anno);
	id = inserisciAlbum(titolo_album, anno);
	return id;
}

int creaAlbumSeNonEsiste(char titolo_album[]) {
	int id = controlloEsistenzaAlbum(titolo_album);
	if (id==0) {
		id = creaAlbumGuidato(titolo_album);
		printf("\nAlbum inserito, continuiamo...");
	} else {
		printf("\nAlbum esistente.");
	}
	return id;
}

int inserisciAlbum(char titolo[], int anno) {
	db_modificato=1;
	int n=contaNelDatabase(1);
	db.album[n].id = trovaUltimoId(1)+1;
	strcpy(db.album[n].titolo,titolo);
	db.album[n].anno = anno;
	return db.album[n].id;
}

void inserisciAlbumSuFile(char id[], char titolo[], char anno[]) {
	FILE* fp=fopen(file_albums, "a");
	if (controllaSeFileVuoto(file_albums)==1) {
		fprintf(fp, "%s,%s,%s", id, titolo, anno);
	} else {
		fprintf(fp, "\n%s,%s,%s", id, titolo, anno);
	}
	fclose(fp);
}

void inserisciCollezioneSuFile(char idalbum[], char idbrano[]) {
	FILE* fp=fopen(file_collezione, "a");
	if (controllaSeFileVuoto(file_collezione)==1) {
		fprintf(fp, "%s,%s", idalbum, idbrano);
	} else {
		fprintf(fp, "\n%s,%s", idalbum, idbrano);
	}
	fclose(fp);
}

int controlloEsistenzaAlbum(char album[]) {
	int id=0, i=0, n=contaNelDatabase(1), controllo=0;
	while (i<n&&controllo!=-1) {
		if (comparaStringhe(db.album[i].titolo, album)==0) {
			id = db.album[i].id;
			controllo=-1;
		}
		i++;
	}
	return id;
}
