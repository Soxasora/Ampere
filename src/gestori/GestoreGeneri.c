/*
 * Ampere 0.2.1 rev.1 - 04.06.2020
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
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

database inserireGenereGuidato(database db) {
	char *nome = malloc(MAX_MEDIO);
	do {
		pulisciBuffer();
		printf("\nInserisci nome del genere: ");
		nome = inputStringaSicuro(MAX_MEDIO,nome);
		db = creareGenereSeNonEsiste(db, nome);
	} while (db.ultimoEsito!=0);
	return db;
}

database creareGenereSeNonEsiste(database db, char nome[]) {
	char scelta='a';
	int controllo=0;
	int id = controllareEsistenzaGenere(db, nome);
	if (id==0) {
		printf("\nSembra che questo genere non esista nel database");
		struct Genere nuovoGenere = creareGenere(nome);
		mostrareAnteprimaGenere(nuovoGenere);
		pulisciBuffer();
		while (controllo!=-1) {
			printf("\nSicuro di voler continuare? [Y/N]: ");
			scanf("%c", &scelta);
			if (scelta=='Y'||scelta=='y'||scelta=='N'||scelta=='n') {
				controllo=-1;
			}
		}
		if (scelta=='Y'||scelta=='y') {
			db = inserireGenere(db, nuovoGenere);
			printf("\nGenere inserito, continuiamo...");
			db.ultimoEsito=0;
		} else {
			db.ultimoEsito=-1;
		}
	} else {
		printf("\nGenere esistente.");
		db.ultimoEsito=0;
	}
	return db;
}

struct Genere creareGenere(char nome[]) {
	struct Genere nuovoGenere;
	nuovoGenere.id = -1;
	strcpy(nuovoGenere.nome, nome);
	return nuovoGenere;
}

void mostrareAnteprimaGenere(struct Genere nuovoGenere) {
	printf("\nIl genere che stai per inserire ha questi dettagli:"
		   "\nNome: %s", nuovoGenere.nome);
}

database inserireGenere(database db, struct Genere nuovoGenere) {
	db_modificato=1;
	int n = contareNelDatabase(db, 3);
	nuovoGenere.id = trovareUltimoId(db, 3)+1;
	db.genere[n] = nuovoGenere;
	return db;
}

void inserireGenereSuFile(struct Genere genere) {
	FILE* fp=fopen(file_generi, "a");
	if (controllaSeFileVuoto(file_generi)==1) {
		fprintf(fp, "%d|%s", genere.id, genere.nome);
	} else {
		fprintf(fp, "\n%d|%s", genere.id, genere.nome);
	}
	fclose(fp);
}

int controllareEsistenzaGenere(database db, char genere[]) {
	int id=0, i=0, n=contareNelDatabase(db,3), controllo=0;
	while (i<n&&controllo!=-1) {
		if (comparaStringhe(db.genere[i].nome, genere)==0) {
			id = db.genere[i].id;
			controllo=-1;
		}
		i++;
	}
	return id;
}

database modificareGenereGuidato(database db) {
	int id=0, campo=-1;
	char scelta='a';
	mostraInfo(db, 2);
	while(ottenerePosDaID(db, 3,id)==-1) {
		printf("\n\nInserire l'identificativo del genere da modificare: ");
		scanf("%d", &id);
		if (ottenerePosDaID(db, 3,id)==-1) {
			printf("\nGenere non trovato, riprovare");
		}
	}
	printf("\nHai scelto il genere:");
	mostraSingoloGenere(db, id);
	pulisciBuffer();
	scelta = richiesta(0);
	if (scelta=='Y'||scelta=='y') {
		do {
			printf("\n===[Sistema di modifica genere]===");
			printf("\n[1] Modifica il Nome");
			printf("\n[0] Esci");
			while (campo<0||campo>1) {
				printf("\n"C_VERDE"Inserisci la tua scelta"C_RESET": ");
				scanf("%d", &campo);
			}
			if (campo!=0) {
				db = creareGenereModificato(db, id);
				if (db.ultimoEsito==0) {
					printf("\nGenere modificato.");
				}
			} else {
				db.ultimoEsito=-2;
			}
		} while (db.ultimoEsito==-1);
	}
	return db;
}

database creareGenereModificato(database db, int id) {
	char scelta='a';
	int pos = ottenerePosDaID(db, 3,id);
	struct Genere genereModificato = db.genere[pos];
	do {
		pulisciBuffer();
		char *nome = malloc(MAX_MEDIO);
		printf("\nInserisci nuovo nome: ");
		nome = inputStringaSicuro(MAX_MEDIO,nome);
		strcpy(genereModificato.nome, nome);
		free(nome);
		printf("\nGenere ORIGINALE:");
		mostraSingoloGenere(db, id);
		printf("\n");
		mostrareAnteprimaGenere(genereModificato);
		scelta = richiesta(0);
		if (scelta=='Y'||scelta=='y') {
			db = modificareGenere(db, id, genereModificato);
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

database modificareGenere(database db, int idGenere, struct Genere genereModificato) {
	int posGenere = ottenerePosDaID(db, 3, idGenere);
	db.genere[posGenere] = genereModificato;
	db_modificato=1;
	return db;
}

database cancellareGenereGuidato(database db) {
	int id=0, controllo=0;
	char scelta='a';
	mostraTuttiGeneri(db);
	while(ottenerePosDaID(db, 3,id)==-1) {
		printf("\n\nInserire l'identificativo del genere da cancellare: ");
		scanf("%d", &id);
		if (ottenerePosDaID(db, 3,id)==-1) {
			printf("\nGenere non trovato, riprovare");
		}
	}
	printf("\nHai scelto il genere: ");
	mostraSingoloGenere(db, id);
	pulisciBuffer();
	while (controllo!=-1) {
		printf("\nSicuro di voler continuare? [Y/N]: ");
		scanf("%c", &scelta);
		if (scelta=='Y'||scelta=='y'||scelta=='N'||scelta=='n') {
			controllo=-1;
		}
	}
	if (scelta=='Y'||scelta=='y') {
		db = cancellareGenere(db, id);
	}
	return db;
}

database cancellareGenere(database db, int id) {
	int n=contareNelDatabase(db,3);
	int i=ottenerePosDaID(db, 3, id);
	while(i<n-1) {
		db.genere[i] = db.genere[i+1];
		i++;
	}
	db.genere[n-1].id = 0;
	int nBrani=contareNelDatabase(db,7);
	i=0;
	while (i<nBrani) {
		if(db.branoGenere[i].idGenere==id) {
			db = cancellaSingoloBrano(db, db.branoGenere[i].idBrano);
			i=-1;
		}
		i++;
	}
	db_modificato=1;
	printf("\nGenere cancellato.");
	return db;
}
