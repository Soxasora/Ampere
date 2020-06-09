/*
 * UNIBA/Ampere 1.2
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di Informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ricerca/MotoreRicerca.h"
#include "../gestori/GestoreFile.h"
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

void inserireGenereGuidato(database *db) {
	char *nome = calloc(MAX_MEDIO, sizeof(char));
	do {
		printf("\nInserisci nome del genere: ");
		nome = inputStringa(MAX_MEDIO,nome);
		creareGenereSeNonEsiste(db, nome);
	} while (db->ultimoEsito!=0);
	
}

void creareGenereSeNonEsiste(database *db, char nome[]) {
	char scelta='a';
	int id = controllareEsistenzaGenere(db, nome);
	if (id==0) {
		printf("\nSembra che questo genere non esista nel database");
		struct Genere nuovoGenere = creareGenere(nome);
		mostrareAnteprimaGenere(nuovoGenere);
		scelta = richiesta(0);
		if (scelta=='Y'||scelta=='y') {
			inserireGenere(db, nuovoGenere);
			db->ultimoEsito=0;
		} else {
			db->ultimoEsito=-1;
		}
	} else {
		attenzione(204);
		db->ultimoEsito=0;
	}
	
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

void inserireGenere(database *db, struct Genere nuovoGenere) {
	int n = contareNelDatabase(db, 3);
	nuovoGenere.id = trovareUltimoId(db, 3)+1;
	db->genere[n] = nuovoGenere;
	successo(4);
	if (salvataggioDiretto) {
		salvareGeneriSuFile(db);
	} else {
		db->modificato=true;
	}
	
}

void inserireGenereSuFile(struct Genere genere) {
	FILE* fp=fopen(file_generi, "a");
	if (controllareSeFileVuoto(file_generi)==1) {
		fprintf(fp, "%d|%s", genere.id, genere.nome);
	} else {
		fprintf(fp, "\n%d|%s", genere.id, genere.nome);
	}
	fclose(fp);
}

int controllareEsistenzaGenere(database *db, char genere[]) {
	int id=0, i=0, n=contareNelDatabase(db,3), controllo=0;
	while (i<n&&controllo!=-1) {
		if (comparareStringhe(db->genere[i].nome, genere)==0) {
			id = db->genere[i].id;
			controllo=-1;
		}
		i++;
	}
	return id;
}

void modificareGenereGuidato(database *db) {
	int id=0, campo=-1, esiste=0;
	char scelta='a';
	do {
		esiste = ricercareInfo(db, 2);
		if (esiste==0) {
			attenzione(101);
		}
	} while (esiste==0);
	while(ottenerePosDaID(db, 3,id)==-1) {
		printf("\n\nInserire l'identificativo del genere da modificare: ");
		id = inputNumero();
		if (ottenerePosDaID(db, 3,id)==-1) {
			printf("\nGenere non trovato, riprovare");
		}
	}
	printf("\nHai scelto il genere:");
	mostrareSingoloGenere(db, id);
	
	scelta = richiesta(0);
	if (scelta=='Y'||scelta=='y') {
		do {
			printf("\n===[Sistema di modifica genere]===");
			printf("\n[1] Modifica il Nome");
			printf("\n[0] Esci");
			while (campo<0||campo>1) {
				printf("\n"C_VERDE"Inserisci la tua scelta"C_RESET": ");
				campo = inputNumero();
			}
			if (campo!=0) {
				creareGenereModificato(db, id);
			} else {
				db->ultimoEsito=-2;
			}
		} while (db->ultimoEsito==-1);
	}
	
}

void creareGenereModificato(database *db, int id) {
	char scelta='a';
	int pos = ottenerePosDaID(db, 3,id);
	struct Genere genereModificato = db->genere[pos];
	do {
		
		char *nome = calloc(MAX_MEDIO, sizeof(char));
		printf("\nInserisci nuovo nome: ");
		nome = inputStringa(MAX_MEDIO,nome);
		strcpy(genereModificato.nome, nome);
		free(nome);
		printf("\nGenere ORIGINALE:");
		mostrareSingoloGenere(db, id);
		printf("\n");
		mostrareAnteprimaGenere(genereModificato);
		scelta = richiesta(0);
		if (scelta=='Y'||scelta=='y') {
			modificareGenere(db, id, genereModificato);
			db->ultimoEsito=0;
		} else {
			scelta = richiesta(3);
			if (scelta=='Y'||scelta=='y') {
				db->ultimoEsito=-2;
			} else {
				db->ultimoEsito=-1;
			}
		}
	} while (db->ultimoEsito==-2);
	
}

void modificareGenere(database *db, int idGenere, struct Genere genereModificato) {
	int posGenere = ottenerePosDaID(db, 3, idGenere);
	db->genere[posGenere] = genereModificato;
	successo(10);
	if (salvataggioDiretto) {
		salvareGeneriSuFile(db);
	} else {
		db->modificato=true;
	}
	
}

void cancellareGenereGuidato(database *db) {
	int id=0;
	char scelta='a';
	mostrareTuttiGeneri(db);
	while(ottenerePosDaID(db, 3,id)==-1) {
		printf("\n\nInserire l'identificativo del genere da cancellare: ");
		id = inputNumero();
		if (ottenerePosDaID(db, 3,id)==-1) {
			printf("\nGenere non trovato, riprovare");
		}
	}
	printf("\nHai scelto il genere: ");
	mostrareSingoloGenere(db, id);
	
	scelta = richiesta(5);
	if (scelta=='Y'||scelta=='y') {
		cancellareGenere(db, id);
	}
	
}

void cancellareGenere(database *db, int id) {
	int n=contareNelDatabase(db,3);
	int i=ottenerePosDaID(db, 3, id);
	while(i<n-1) {
		db->genere[i] = db->genere[i+1];
		i++;
	}
	db->genere[n-1].id = 0;
	int nBrani=contareNelDatabase(db,7);
	i=0;
	while (i<nBrani) {
		if(db->branoGenere[i].idGenere==id) {
			cancellareBrano(db, db->branoGenere[i].idBrano);
			i=-1;
		}
		i++;
	}
	successo(16);
	if (salvataggioDiretto) {
		salvareGeneriSuFile(db);
	} else {
		db->modificato=true;
	}
	
}
