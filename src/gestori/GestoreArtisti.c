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

database inserimentoArtistaGuidato(database db) {
	char *nomeArte = calloc(MAX_MEDIO, sizeof(char));
	do {
		
		printf("\nInserisci nome d'arte dell'artista: ");
		nomeArte = inputStringa(MAX_MEDIO,nomeArte);
		db = creaArtistaSeNonEsiste(db,nomeArte);
	} while (db.ultimoEsito!=0);
	return db;
}

database creaArtistaGuidato(database db, char nomeArte[]) {
	char scelta='a';
	char *nome = calloc(MAX_MEDIO, sizeof(char));
	char *cognome = calloc(MAX_MEDIO, sizeof(char));
	char *linkBio = calloc(MAX_ENORME, sizeof(char));
	printf("\n===[Inserimento guidato di un artista]==="
	       "\nNome d'arte: %s", nomeArte);
	
	printf("\n[Premi invio per saltare] Inserisci nome ANAGRAFICO dell'artista: ");
	nome = inputStringa(MAX_MEDIO,nome);
	printf("\n[Premi invio per saltare] Inserisci cognome ANAGRAFICO dell'artista: ");
	cognome = inputStringa(MAX_MEDIO,cognome);
	printf("\n[Premi invio per saltare] Inserisci il link della biografia dell'artista: ");
	linkBio = inputStringa(MAX_ENORME,linkBio);
	struct Artista nuovoArtista = creaArtista(nome, cognome, nomeArte, linkBio);
	mostrareAnteprimaArtista(nuovoArtista);
	scelta = richiesta(0);
	if (scelta=='Y'||scelta=='y') {
		db = inserireArtista(db, nuovoArtista);
		printf("\nArtista inserito, continuiamo...");
		db.ultimoEsito=0;
	} else {
		db.ultimoEsito = -1;
	}
	return db;
}

database creaArtistaSeNonEsiste(database db, char nomeArte[]) {
	int id = controlloEsistenzaArtista(db, nomeArte);
	if (id==0) {
		printf("\nSembra che quest'artista non esista nel database, inseriamolo.");
		db = creaArtistaGuidato(db, nomeArte);
	} else {
		printf("\nArtista esistente.");
		db.ultimoEsito = 0;
	}
	return db;
}

struct Artista creaArtista(char nome[], char cognome[], char nomeArte[], char linkBio[]) {
	struct Artista nuovoArtista;
	nuovoArtista.id = -1;
	strcpy(nuovoArtista.nome,nome);
	strcpy(nuovoArtista.cognome,cognome);
	strcpy(nuovoArtista.nomeArte,nomeArte);
	strcpy(nuovoArtista.linkBio,linkBio);
	return nuovoArtista;
}

void mostrareAnteprimaArtista(struct Artista nuovoArtista) {
	printf("\nL'artista che stai per inserire ha questi dettagli:"
		   "\nNome: %s"
		   "\nCognome: %s"
		   "\nNome d'arte: %s"
		   "\nLink alla biografia: %s", nuovoArtista.nome, nuovoArtista.cognome,
		   nuovoArtista.nomeArte, nuovoArtista.linkBio);
}

database inserireArtista(database db, struct Artista nuovoArtista) {
	db_modificato=1;
	int n = contareNelDatabase(db, 2);
	nuovoArtista.id = trovareUltimoId(db, 2)+1;
	db.artista[n] = nuovoArtista;
	return db;
}

int controlloEsistenzaArtista(database db, char nomeArte[]) {
	int id=0, i=0, n=contareNelDatabase(db,2), controllo=0;
	while (i<n&&controllo!=-1) {
		if (comparaStringhe(db.artista[i].nomeArte, nomeArte)==0) {
			id = db.artista[i].id;
			controllo=-1;
		}
		i++;
	}
	return id;
}

void inserisciArtistiSuFile(struct Artista artista) {
	FILE* fp=fopen(file_artisti, "a");
	if (controllaSeFileVuoto(file_artisti)==1) {
		fprintf(fp, "%d|%s|%s|%s|%s", artista.id, artista.nome, artista.cognome, artista.nomeArte, artista.linkBio);
	} else {
		fprintf(fp, "\n%d|%s|%s|%s|%s", artista.id, artista.nome, artista.cognome, artista.nomeArte, artista.linkBio);
	}
	fclose(fp);
}

database modificareArtistaGuidato(database db) {
	int id=0, campo=-1, esiste=0;
	char scelta='a';
	do {
		esiste = mostraInfo(db, 0);
		if (esiste==0) {
			attenzione(101);
		}
	} while (esiste==0);
	while (ottenerePosDaID(db, 2, id)==-1) {
		printf("\n\nInserire l'identificativo dell'artista da modificare: ");
		id = inputNumero();
		if (ottenerePosDaID(db, 2,id)==-1) {
			printf("\nArtista non trovato, riprovare");
		}
	}
	printf("\nHai scelto l'artista:");
	mostraSingoloArtista(db, id);
	
	scelta = richiesta(0);
	if (scelta=='Y'||scelta=='y') {
		do {
			printf("\n===[Sistema di modifica artista]==="
				   "\n[1] Modifica il Nome"
				   "\n[2] Modifica il Cognome"
				   "\n[3] Modifica il Nome d'arte"
				   "\n[4] Modifica il link della biografia"
				   "\n[0] Esci");
			while (campo<0||campo>4) {
				printf("\n"C_VERDE"Inserisci la tua scelta"C_RESET": ");
				campo = inputNumero();
			}
			if (campo!=0) {
				db = creareArtistaModificato(db, campo, id);
				if (db.ultimoEsito==0) {
					printf("\nArtista modificato");
				}
			} else {
				db.ultimoEsito=-2;
			}
		} while (db.ultimoEsito==-1);
	}
	return db;
}

database creareArtistaModificato(database db, int campo, int id) {
	char scelta='a';
	int pos = ottenerePosDaID(db, 2,id);
	struct Artista artistaModificato = db.artista[pos];
	do {
		
		if (campo==1) {
			char *nome = calloc(MAX_MEDIO, sizeof(char));
			printf("\nInserisci nuovo nome: ");
			nome = inputStringa(MAX_MEDIO,nome);
			strcpy(artistaModificato.nome, nome);
			free(nome);
		} else if (campo==2) {
			char *cognome = calloc(MAX_MEDIO, sizeof(char));
			printf("\nInserisci nuovo cognome: ");
			cognome = inputStringa(MAX_MEDIO,cognome);
			strcpy(artistaModificato.cognome, cognome);
			free(cognome);
		} else if (campo==3) {
			char *nomeArte = calloc(MAX_MEDIO, sizeof(char));
			printf("\nInserisci nuovo nome d'arte: ");
			nomeArte = inputStringa(MAX_MEDIO,nomeArte);
			strcpy(artistaModificato.nomeArte, nomeArte);
			free(nomeArte);
		} else if (campo==4) {
			char *linkBio = calloc(MAX_ENORME, sizeof(char));
			printf("\nInserisci nuovo link della biografia: ");
			linkBio = inputStringa(MAX_ENORME, linkBio);
			strcpy(artistaModificato.linkBio, linkBio);
			free(linkBio);
		}
		printf("\nArtista ORIGINALE: ");
		mostraSingoloArtista(db, id);
		printf("\n");
		mostrareAnteprimaArtista(artistaModificato);
		scelta = richiesta(0);
		if (scelta=='Y'||scelta=='y') {
			db = modificareArtista(db, id, artistaModificato);
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

database modificareArtista(database db, int idArtista, struct Artista artistaModificato) {
	int posArtista = ottenerePosDaID(db, 2, idArtista);
	db.artista[posArtista] = artistaModificato;
	db_modificato=1;
	return db;
}

database cancellaArtista(database db) {
	int id=0;
	char scelta='N';
	mostraTuttiArtisti(db);
	while (ottenerePosDaID(db, 2,id)==-1) {
		printf("\n\nInserire l'identificativo dell'artista da cancellare: ");
		id = inputNumero();
		if (ottenerePosDaID(db, 2,id)==-1) {
			printf("\nArtista non trovato, riprovare");
		}

	}
	printf("\nHai scelto l'artista: ");
	mostraSingoloArtista(db, id);
	
	scelta = richiesta(5);
	if (scelta=='Y'||scelta=='y') {
		db = cancellaSingoloArtista(db, id);
	}
	return db;
}

database cancellaSingoloArtista(database db, int id) {
	int n=contareNelDatabase(db,2);
	int i=ottenerePosDaID(db, 2, id);
	while(i<n-1) {
		db.artista[i] = db.artista[i+1];
		i++;
	}
	db.artista[n-1].id = 0;

	int nBrani=contareNelDatabase(db,5);
	i=0;
	while (i<nBrani) {
		if(db.branoArtista[i].idArtista==id) {
			db = cancellaSingoloBrano(db, db.branoArtista[i].idBrano);
			i=-1;
		}
		i++;
	}
	db_modificato=1;
	printf("\nArtista cancellato.");
	return db;
}

void visualizzaBiografiaArtista(database db) {
	int id=0, pos=0, esito=0;
	printf("\nCerca biografia dell'artista: ");
	esito = mostraInfo(db, 0);
	if (esito==1) {
		
		while(ottenerePosDaID(db, 2,id)==-1) {
			printf("\n\nInserisci l'identificativo dell'artista: ");
			id = inputNumero();
			if (ottenerePosDaID(db, 2,id)==1) {
				printf("\nArtista non trovato, riprovare");
			}
		}
		pos=ottenerePosDaID(db, 2,id);
		apriLink(db.artista[pos].linkBio);
	} else {
		printf("\n\nNessun artista trovato.");
	}
}
