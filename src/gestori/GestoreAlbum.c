/*
 * Ampere 0.1 rev. 4075 - 19.05.2020
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
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



database inserimentoAlbumGuidato(database db) {
	pulisciBuffer();
	char *titolo = malloc(MAX_MEDIO);
	printf("\nInserisci titolo dell'album: ");
	titolo = inputStringaSicuro(MAX_MEDIO,titolo);
	db = creaAlbumSeNonEsiste(db, titolo);
	free(titolo);
	return db;
}

database creaAlbumGuidato(database db, char titolo_album[]) {
	int anno=0;
	printf("\nSembra che quest'album non esista nel database, inseriamolo.");
	printf("\n===[Inserimento guidato di un album]===");
	printf("\nTitolo: %s", titolo_album);
	pulisciBuffer();
	while (anno<=1950||anno>2020) {
		printf("\nInserisci l'anno di uscita di quest'album: ");
		scanf("%d", &anno);
	}
	db = inserireAlbum(db,creaAlbum(db,titolo_album, anno));
	return db;
}

database creaAlbumSeNonEsiste(database db, char titolo_album[]) {
	int id = controlloEsistenzaAlbum(db, titolo_album);
	if (id==0) {
		db = creaAlbumGuidato(db, titolo_album);
		printf("\nAlbum inserito, continuiamo...");
	} else {
		printf("\nAlbum esistente.");
	}
	return db;
}

struct albums creaAlbum(database db, char titolo[], int anno) {
	struct albums album;
	album.id = trovaUltimoId(db,1)+1;
	strcpy(album.titolo, titolo);
	album.anno = anno;
	return album;
}

database inserireAlbum(database db, struct albums album) {
	db_modificato=1;
	int n = contaNelDatabase(db, 1);
	db.album[n] = album;
	return db;
}

void inserisciAlbumSuFile(char id[], char titolo[], char anno[]) {
	FILE* fp=fopen(file_albums, "a");
	if (controllaSeFileVuoto(file_albums)==1) {
		fprintf(fp, "%s|%s|%s", id, titolo, anno);
	} else {
		fprintf(fp, "\n%s|%s|%s", id, titolo, anno);
	}
	fclose(fp);
}

void inserisciCollezioneSuFile(char idalbum[], char idbrano[]) {
	FILE* fp=fopen(file_collezione, "a");
	if (controllaSeFileVuoto(file_collezione)==1) {
		fprintf(fp, "%s|%s", idalbum, idbrano);
	} else {
		fprintf(fp, "\n%s|%s", idalbum, idbrano);
	}
	fclose(fp);
}

int controlloEsistenzaAlbum(database db, char album[]) {
	int id=0, i=0, n=contaNelDatabase(db,1), controllo=0;
	while (i<n&&controllo!=-1) {
		if (comparaStringhe(db.album[i].titolo, album)==0) {
			id = db.album[i].id;
			controllo=-1;
		}
		i++;
	}
	return id;
}

database modificaAlbum(database db) {
	int id=0, modalita=-1, controllo=0;
	char scelta='a';
	mostraTuttiAlbum(db);
	while (ottieniPosDaID(db, 1,id)==-1) {
		printf("\n\nInserire l'identificativo dell'album da modificare: ");
		scanf("%d", &id);
		if (ottieniPosDaID(db, 1,id)==-1) {
			printf("\nNessun album trovato, riprovare");
		}
	}
	printf("\nHai scelto l'album:");
	mostraSingoloAlbum(db, id);
	pulisciBuffer();
	while (controllo!=-1) {
		printf("\nSicuro di voler continuare? [Y/N]: ");
		scanf("%c", &scelta);
		if (scelta=='Y'||scelta=='y'||scelta=='N'||scelta=='n') {
			controllo=-1;
		}
	}
	if (scelta=='Y'||scelta=='y') {
		printf("\n===[Sistema di modifica album]===");
		printf("\n[1] Modifica il Titolo");
		printf("\n[2] Modificare l'anno di uscita");
		printf("\n[0] Esci");
		while (modalita<0||modalita>2) {
			printf("\nInserisci la tua scelta: ");
			scanf("%d", &modalita);
		}
		if (modalita!=0) {
			db = modificaSingoloAlbum(db, modalita, id);
		}
	}
	return db;
}

database modificaSingoloAlbum(database db, int modalita, int id) {
	pulisciBuffer();
	int pos = ottieniPosDaID(db, 1,id);
	if (modalita==1) {
		char *titolo = malloc(MAX_MEDIO);
		printf("\nInserisci nuovo titolo: ");
		titolo = inputStringaSicuro(MAX_MEDIO,titolo);
		strcpy(db.album[pos].titolo, titolo);
		free(titolo);
	} else if (modalita==2) {
		int anno=0;
		while (anno<=1950||anno>2020) {
			printf("\nInserisci nuovo anno: ");
			scanf("%d", &anno);
		}
		db.album[pos].anno=anno;
	}
	db_modificato=1;
	printf("\nAlbum aggiornato, ecco il risultato:\n");
	mostraSingoloAlbum(db, id);
	return db;
}

database cancellaAlbum(database db) {
	int id=0;
	char scelta='N';
	mostraTuttiAlbum(db);
	while (ottieniPosDaID(db, 1,id)==-1) {
		printf("\n\nInserire l'identificativo dell'album da cancellare: ");
		scanf("%d", &id);
		if (ottieniPosDaID(db, 1,id)==-1) {
			printf("\nNessun album trovato, riprovare");
		}
	}
	printf("\nHai scelto l'album: ");
	mostraSingoloAlbum(db, id);
	pulisciBuffer();
	printf("\nSicuro di voler continuare? Cancellera' anche i brani collegati ad esso. [Y/N]: ");
	scanf("%c", &scelta);
	if (scelta=='Y'||scelta=='y') {
		db = cancellaSingoloAlbum(db,id);
	}
	return db;
}

database cancellaSingoloAlbum(database db, int id) {
	int n=contaNelDatabase(db,1);
	int i=ottieniPosDaID(db, 1, id);
	while(i<n-1) {
		db.album[i] = db.album[i+1];
		i++;
	}
	db.album[n-1].id = 0;

	int nbrani=contaNelDatabase(db,6);
	i=0;
	while (i<nbrani) {
		if(db.branoAlbum[i].idAlbum==id) {
			db = cancellaSingoloBrano(db, db.branoAlbum[i].idBrano);
			i=-1;
		}
		i++;
	}
	db_modificato=1;
	printf("\nAlbum cancellato.");
	return db;
}
