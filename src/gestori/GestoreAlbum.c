/*
 * UNIBA/Ampere 1.0
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di Informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ricerca/MotoreRicerca.h"
#include "../gestori/GestoreAssociazioni.h"
#include "../gestori/GestoreUtenti.h"
#include "../gestori/GestoreBrani.h"
#include "../gestori/GestoreAlbum.h"
#include "../gestori/GestoreArtisti.h"
#include "../gestori/GestoreGeneri.h"
#include "../database/Database.h"
#include "../database/DatabaseUtils.h"
#include "../sys/Messaggi.h"
#include "../sys/Utils.h"
#include "../sys/Impostazioni.h"

database inserimentoAlbumGuidato(database db) {
	char *titolo = calloc(MAX_MEDIO, sizeof(char));
	do {
		
		if ((titolo = calloc(MAX_MEDIO, sizeof(char)))) {
			printf("\nInserisci titolo dell'album: ");
			titolo = inputStringa(MAX_MEDIO,titolo);
			db = creaAlbumSeNonEsiste(db, titolo);
		}
	} while (db.ultimoEsito!=0);
	free(titolo); titolo=NULL;
	return db;
}

database creaAlbumGuidato(database db, char titoloAlbum[]) {
	char scelta='a';
	int controllo=0;
	int anno=0;
	printf("\n===[Inserimento guidato di un album]===");
	printf("\nTitolo: %s", titoloAlbum);
	
	while (anno<1950) {
		printf("\nInserisci l'anno di uscita di quest'album: ");
		anno = inputNumero();
	}
	struct Album nuovoAlbum = creaAlbum(titoloAlbum, anno);
	mostrareAnteprimaAlbum(nuovoAlbum);
	
	while (controllo!=-1) {
		scelta = richiesta(0);
		if (scelta=='Y'||scelta=='y'||scelta=='N'||scelta=='n') {
			controllo=-1;
		}
	}
	if (scelta=='Y'||scelta=='y') {
		db = inserireAlbum(db, nuovoAlbum);
		printf("\nAlbum inserito, continuiamo...");
		db.ultimoEsito=0;
	} else {
		db.ultimoEsito = -1;
	}
	return db;
}

database creaAlbumSeNonEsiste(database db, char titoloAlbum[]) {
	int id = controlloEsistenzaAlbum(db, titoloAlbum);
	if (id==0) {
		printf("\nSembra che quest'album non esista nel database, inseriamolo.");
		db = creaAlbumGuidato(db, titoloAlbum);
	} else {
		printf("\nAlbum esistente.");
		db.ultimoEsito=0;
	}
	return db;
}

struct Album creaAlbum(char titolo[], int anno) {
	struct Album nuovoAlbum;
	nuovoAlbum.id = -1;
	strcpy(nuovoAlbum.titolo, titolo);
	nuovoAlbum.anno = anno;
	return nuovoAlbum;
}

void mostrareAnteprimaAlbum(struct Album nuovoAlbum) {
	printf("\nL'album che stai per inserire ha questi dettagli:"
		   "\nNome: %s"
		   "\nAnno: %d", nuovoAlbum.titolo, nuovoAlbum.anno);
}

database inserireAlbum(database db, struct Album nuovoAlbum) {
	db_modificato=1;
	int n = contareNelDatabase(db, 1);
	nuovoAlbum.id = trovareUltimoId(db,1)+1;
	db.album[n] = nuovoAlbum;
	return db;
}

void inserisciAlbumSuFile(struct Album album) {
	FILE* fp=fopen(file_albums, "a");
	if (controllaSeFileVuoto(file_albums)==1) {
		fprintf(fp, "%d|%s|%d", album.id, album.titolo, album.anno);
	} else {
		fprintf(fp, "\n%d|%s|%d", album.id, album.titolo, album.anno);
	}
	fclose(fp);
}

int controlloEsistenzaAlbum(database db, char album[]) {
	int id=0, i=0, n=contareNelDatabase(db,1), controllo=0;
	while (i<n&&controllo!=-1) {
		if (comparaStringhe(db.album[i].titolo, album)==0) {
			id = db.album[i].id;
			controllo=-1;
		}
		i++;
	}
	return id;
}

database modificareAlbumGuidato(database db) {
	int id=0, campo=-1, esiste=0;
	char scelta='a';
	do {
		esiste = mostraInfo(db, 1);
		if (esiste==0) {
			attenzione(101);
		}
	} while (esiste==0);
	while (ottenerePosDaID(db, 1,id)==-1) {
		printf("\n\nInserire l'identificativo dell'album da modificare: ");
		id = inputNumero();
		if (ottenerePosDaID(db, 1,id)==-1) {
			printf("\nNessun album trovato, riprovare");
		}
	}
	printf("\nHai scelto l'album:");
	mostraSingoloAlbum(db, id);
	
	scelta = richiesta(0);
	if (scelta=='Y'||scelta=='y') {
		do {
			printf("\n===[Sistema di modifica album]==="
			"\n[1] Modifica il Titolo"
			"\n[2] Modificare l'anno di uscita"
			"\n[0] Esci");
			while (campo<0||campo>2) {
				printf("\n"C_VERDE"Inserisci la tua scelta"C_RESET": ");
				campo = inputNumero();
			}
			if (campo!=0) {
				db = creareAlbumModificato(db, campo, id);
				if (db.ultimoEsito==0) {
					printf("\nAlbum modificato.");
				}
			} else {
				db.ultimoEsito=-2;
			}
		} while (db.ultimoEsito==-1);
	}
	return db;
}

database creareAlbumModificato(database db, int campo, int id) {
	char scelta='a';
	int pos = ottenerePosDaID(db, 1, id);
	struct Album albumModificato = db.album[pos];
	do {
		
		if (campo==1) {
			char *titolo = calloc(MAX_MEDIO, sizeof(char));
			printf("\nInserisci nuovo titolo: ");
			titolo = inputStringa(MAX_MEDIO,titolo);
			strcpy(albumModificato.titolo, titolo);
			free(titolo);
		} else if (campo==2) {
			int anno=0;
			while (anno<1950) {
				printf("\nInserisci nuovo anno: ");
				anno = inputNumero();
			}
			albumModificato.anno=anno;
		}
		printf("\nAlbum ORIGINALE:");
		mostraSingoloAlbum(db, id);
		printf("\n");
		mostrareAnteprimaAlbum(albumModificato);
		scelta = richiesta(0);
		if (scelta=='Y'||scelta=='y') {
			db = modificareAlbum(db, id, albumModificato);
			db.ultimoEsito=0;
		} else {
			scelta = richiesta(3);
			if (scelta=='Y'||scelta=='y') {
				db.ultimoEsito=-2;
			} else {
				db.ultimoEsito=-1;
			}
		}
	} while (db.ultimoEsito==-2);
	return db;
}

database modificareAlbum(database db, int idAlbum, struct Album albumModificato) {
	int posAlbum = ottenerePosDaID(db, 1, idAlbum);
	db.album[posAlbum] = albumModificato;
	db_modificato=1;
	return db;
}

database cancellaAlbum(database db) {
	int id=0;
	char scelta='N';
	mostraTuttiAlbum(db);
	while (ottenerePosDaID(db, 1,id)==-1) {
		printf("\n\nInserire l'identificativo dell'album da cancellare: ");
		id = inputNumero();
		if (ottenerePosDaID(db, 1,id)==-1) {
			printf("\nNessun album trovato, riprovare");
		}
	}
	printf("\nHai scelto l'album: ");
	mostraSingoloAlbum(db, id);
	scelta = richiesta(5);
	if (scelta=='Y'||scelta=='y') {
		db = cancellaSingoloAlbum(db,id);
	}
	return db;
}

database cancellaSingoloAlbum(database db, int id) {
	int n=contareNelDatabase(db,1);
	int i=ottenerePosDaID(db, 1, id);
	while(i<n-1) {
		db.album[i] = db.album[i+1];
		i++;
	}
	db.album[n-1].id = 0;

	int nBrani=contareNelDatabase(db,6);
	i=0;
	while (i<nBrani) {
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
