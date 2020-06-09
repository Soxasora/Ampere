/*
 * UNIBA/Ampere 1.2.2
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

void inserireArtistaGuidato(database *db) {
	char *nomeArte = calloc(MAX_MEDIO, sizeof(char));
	do {
		printf("\nInserisci nome d'arte dell'artista: ");
		nomeArte = inputStringa(MAX_MEDIO,nomeArte);
		creareArtistaSeNonEsiste(db,nomeArte);
	} while (db->ultimoEsito!=0);
	
}

void creareArtistaGuidato(database *db, char nomeArte[]) {
	char scelta='a';
	char *nome = calloc(MAX_MEDIO, sizeof(char));
	char *cognome = calloc(MAX_MEDIO, sizeof(char));
	char *linkBio = calloc(MAX_ENORME, sizeof(char));
	printf("\n===[Inserimento guidato di un artista]==="
	       "\nNome d'arte: %s", nomeArte);
	
	printf("\n"C_GIALLO"[Premi invio per saltare]"C_RESET" Inserisci nome ANAGRAFICO dell'artista: ");
	nome = inputStringa(MAX_MEDIO,nome);
	printf("\n"C_GIALLO"[Premi invio per saltare]"C_RESET" Inserisci cognome ANAGRAFICO dell'artista: ");
	cognome = inputStringa(MAX_MEDIO,cognome);
	printf("\n"C_GIALLO"[Premi invio per saltare]"C_RESET" Inserisci il link della biografia dell'artista: ");
	linkBio = inputStringa(MAX_ENORME,linkBio);
	struct Artista nuovoArtista = creareArtista(nome, cognome, nomeArte, linkBio);
	mostrareAnteprimaArtista(nuovoArtista);
	scelta = richiesta(0);
	if (scelta=='Y'||scelta=='y') {
		inserireArtista(db, nuovoArtista);
		db->ultimoEsito=0;
	} else {
		db->ultimoEsito = -1;
	}
	
}

void creareArtistaSeNonEsiste(database *db, char nomeArte[]) {
	int id = controllareEsistenzaArtista(db, nomeArte);
	if (id==0) {
		printf("\nSembra che quest'artista non esista nel database, inseriamolo.");
		creareArtistaGuidato(db, nomeArte);
	} else {
		informazione(203);
		db->ultimoEsito = 0;
	}
	
}

struct Artista creareArtista(char nome[], char cognome[], char nomeArte[], char linkBio[]) {
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

void inserireArtista(database *db, struct Artista nuovoArtista) {
	int n = contareNelDatabase(db, 2);
	nuovoArtista.id = trovareUltimoId(db, 2)+1;
	db->artista[n] = nuovoArtista;
	successo(3);
	if (salvataggioDiretto) {
		salvareArtistiSuFile(db);
	} else {
		db->modificato=true;
	}
	
}

int controllareEsistenzaArtista(database *db, char nomeArte[]) {
	int id=0, i=0, n=contareNelDatabase(db,2), controllo=0;
	while (i<n&&controllo!=-1) {
		if (comparareStringhe(db->artista[i].nomeArte, nomeArte)==0) {
			id = db->artista[i].id;
			controllo=-1;
		}
		i++;
	}
	return id;
}

void inserireArtistiSuFile(struct Artista artista) {
	FILE* fp=fopen(file_artisti, "a");
	if (controllareSeFileVuoto(file_artisti)==1) {
		fprintf(fp, "%d|%s|%s|%s|%s", artista.id, artista.nome, artista.cognome, artista.nomeArte, artista.linkBio);
	} else {
		fprintf(fp, "\n%d|%s|%s|%s|%s", artista.id, artista.nome, artista.cognome, artista.nomeArte, artista.linkBio);
	}
	fclose(fp);
}

void modificareArtistaGuidato(database *db) {
	int id=0, campo=-1, esiste=0;
	char scelta='a';
	do {
		esiste = ricercareInfo(db, 0);
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
	mostrareSingoloArtista(db, id);
	
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
				creareArtistaModificato(db, campo, id);
			} else {
				db->ultimoEsito=-2;
			}
		} while (db->ultimoEsito==-1);
	}
	
}

void creareArtistaModificato(database *db, int campo, int id) {
	char scelta='a';
	int pos = ottenerePosDaID(db, 2,id);
	struct Artista artistaModificato = db->artista[pos];
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
		mostrareSingoloArtista(db, id);
		printf("\n");
		mostrareAnteprimaArtista(artistaModificato);
		scelta = richiesta(0);
		if (scelta=='Y'||scelta=='y') {
			modificareArtista(db, id, artistaModificato);
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

void modificareArtista(database *db, int idArtista, struct Artista artistaModificato) {
	int posArtista = ottenerePosDaID(db, 2, idArtista);
	db->artista[posArtista] = artistaModificato;
	successo(9);
	if (salvataggioDiretto) {
		salvareArtistiSuFile(db);
	} else {
		db->modificato=true;
	}
	
}

void cancellareArtistaGuidato(database *db) {
	int id=0;
	char scelta='N';
	mostrareTuttiArtisti(db);
	while (ottenerePosDaID(db, 2,id)==-1) {
		printf("\n\nInserire l'identificativo dell'artista da cancellare: ");
		id = inputNumero();
		if (ottenerePosDaID(db, 2,id)==-1) {
			printf("\nArtista non trovato, riprovare");
		}

	}
	printf("\nHai scelto l'artista: ");
	mostrareSingoloArtista(db, id);
	
	scelta = richiesta(5);
	if (scelta=='Y'||scelta=='y') {
		cancellareArtista(db, id);
	}
	
}

void cancellareArtista(database *db, int id) {
	int n=contareNelDatabase(db,2);
	int i=ottenerePosDaID(db, 2, id);
	while(i<n-1) {
		db->artista[i] = db->artista[i+1];
		i++;
	}
	db->artista[n-1].id = 0;

	int nBrani=contareNelDatabase(db,5);
	i=0;
	while (i<nBrani) {
		if(db->branoArtista[i].idArtista==id) {
			cancellareBrano(db, db->branoArtista[i].idBrano);
			i=-1;
		}
		i++;
	}
	successo(15);
	if (salvataggioDiretto) {
		salvareArtistiSuFile(db);
	} else {
		db->modificato=true;
	}
	
}

void visualizzareBiografiaArtista(database *db) {
	int id=0, pos=0, esito=0;
	printf("\nCerca biografia dell'artista: ");
	esito = ricercareInfo(db, 0);
	if (esito==1) {
		while(ottenerePosDaID(db, 2,id)==-1) {
			printf("\n\nInserisci l'identificativo dell'artista: ");
			id = inputNumero();
			if (ottenerePosDaID(db, 2,id)==1) {
				printf("\nArtista non trovato, riprovare");
			}
		}
		pos=ottenerePosDaID(db, 2,id);
		if (strcmp(db->artista[pos].linkBio, "N/A")==0) {
			printf("\nL'artista selezionato non ha una biografia nel database.");
		} else {
			aprireLink(db->artista[pos].linkBio);
		}
	} else {
		printf("\n\nNessun artista trovato.");
	}
}
