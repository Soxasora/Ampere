/*
 * Ampere 0.1 rev. 2377 - 07.05.2020
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

void modificaAlbum() {
	int id=0, modalita=0;
	char scelta='N';
	mostraTuttiAlbum();
	printf("\n\nInserire l'identificativo dell'album da modificare: ");
	scanf("%d", &id);
	printf("\nHai scelto l'album:");
	mostraSingoloAlbum(id);
	pulisciBuffer();
	printf("\nSicuro di voler continuare? [Y/N]: ");
	scanf("%c", &scelta);
	if (scelta=='Y'||scelta=='y') {
		printf("\n===[Sistema di modifica album]===");
		printf("\n[1] Modifica il Titolo");
		printf("\n[2] Modificare l'anno di uscita");
		printf("\n[0] Esci");
		printf("\nInserisci la tua scelta");
		if (modalita!=0) {
			modificaSingoloAlbum(modalita, id);
		}
	}
}

void modificaSingoloAlbum(int modalita, int id) {
	pulisciBuffer();
	int pos = ottieniPosDaID(1,id);
	if (modalita==1) {
		char *titolo = malloc(MAX_CHAR);
		printf("\nInserisci nuovo titolo: ");
		titolo = inputStringaSicuro(titolo);
		strcpy(db.album[pos].titolo, titolo);
		free(titolo);
	} else if (modalita==2) {
		int anno=0;
		printf("\nInserisci nuovo anno: ");
		scanf("%d", &anno);
		db.album[pos].anno=anno;
	}
	db_modificato=1;
	printf("\nAlbum aggiornato, ecco il risultato:\n");
	mostraSingoloAlbum(id);
}

void cancellaAlbum() {
	int id=0;
	char scelta='N';
	mostraTuttiAlbum();
	printf("\n\nInserire l'identificativo dell'album da cancellare: ");
	scanf("%d", &id);
	printf("\nHai scelto l'album: ");
	mostraSingoloAlbum(id);
	pulisciBuffer();
	printf("\nSicuro di voler continuare? Cancellera' anche i brani collegati ad esso. [Y/N]: ");
	scanf("%c", &scelta);
	if (scelta=='Y'||scelta=='y') {
		cancellaSingoloAlbum(id);
	}
}

void cancellaSingoloAlbum(int id) {
	int n=contaNelDatabase(1);
	int i=ottieniPosDaID(1, id);
	while(i<n-1) {
		db.album[i] = db.album[i+1];
		i++;
	}
	db.album[n-1].id = 0;

	int nbrani=contaNelDatabase(6);
	i=0;
	while (i<nbrani) {
		if(db.albumBrano[i].idAlbum==id) {
			cancellaSingoloBrano(db.albumBrano[i].idBrano);
			i=-1;
		}
		i++;
	}
	db_modificato=1;
	printf("\nAlbum cancellato.");
}
