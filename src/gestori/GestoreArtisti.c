/*
 * Ampere 0.1 rev. 4074 - 15.05.2020
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

database inserimentoArtistaGuidato(database db) {
	pulisciBuffer();
	char *nomearte = malloc(MAX_MEDIO);
	printf("\nInserisci nome d'arte dell'artista: ");
	nomearte = inputStringaSicuro(MAX_MEDIO,nomearte);
	db = creaArtistaSeNonEsiste(db,nomearte);
	free(nomearte);
	return db;
}

database creaArtistaGuidato(database db, char nomearte[]) {
	char *nome = malloc(MAX_MEDIO);
	char *cognome = malloc(MAX_MEDIO);
	char *linkbio = malloc(MAX_ENORME);
	printf("\nSembra che quest'artista non esista nel database, inseriamolo.");
	printf("\n===[Inserimento guidato di un artista]===");
	printf("\nNome d'arte: %s", nomearte);
	pulisciBuffer();
	printf("\nInserisci nome ANAGRAFICO dell'artista: ");
	nome = inputStringaSicuro(MAX_MEDIO,nome);
	printf("\nInserisci cognome ANAGRAFICO dell'artista: ");
	cognome = inputStringaSicuro(MAX_MEDIO,cognome);
	printf("\nInserisci il link della biografia dell'artista: ");
	linkbio = inputStringaSicuro(MAX_ENORME,linkbio);
	db = inserireArtista(db, creaArtista(db,nome, cognome, nomearte, linkbio));
	free(nome); free(cognome);
	return db;
}

database creaArtistaSeNonEsiste(database db, char nomearte[]) {
	int id = controlloEsistenzaArtista(db, nomearte);
	if (id==0) {
		db = creaArtistaGuidato(db, nomearte);
		printf("\nArtista inserito, continuiamo...");
	} else {
		printf("\nArtista esistente.");
	}
	return db;
}

struct artisti creaArtista(database db, char nome[], char cognome[], char nomearte[], char linkbio[]) {
	struct artisti artista;
	artista.id = trovaUltimoId(db, 2)+1;
	strcpy(artista.nome,nome);
	strcpy(artista.cognome,cognome);
	strcpy(artista.nomearte,nomearte);
	strcpy(artista.linkbio,linkbio);
	return artista;
}

database inserireArtista(database db, struct artisti artista) {
	db_modificato=1;
	int n = contaNelDatabase(db, 2);
	db.artista[n] = artista;
	return db;
}

int controlloEsistenzaArtista(database db, char nomearte[]) {
	int id=0, i=0, n=contaNelDatabase(db,2), controllo=0;
	while (i<n&&controllo!=-1) {
		if (comparaStringhe(db.artista[i].nomearte, nomearte)==0) {
			id = db.artista[i].id;
			controllo=-1;
		}
		i++;
	}
	return id;
}

void inserisciArtistiSuFile(char id[], char nome[], char cognome[], char nomearte[], char linkbio[]) {
	FILE* fp=fopen(file_artisti, "a");
	if (controllaSeFileVuoto(file_artisti)==1) {
		fprintf(fp, "%s|%s|%s|%s|%s", id, nome, cognome, nomearte, linkbio);
	} else {
		fprintf(fp, "\n%s|%s|%s|%s|%s", id, nome, cognome, nomearte, linkbio);
	}
	fclose(fp);
}

void inserisciAssociazioneArtistiSuFile(char idbrano[], char idartista[]) {
	FILE* fp=fopen(file_associazioneartisti, "a");
	if (controllaSeFileVuoto(file_associazioneartisti)==1) {
		fprintf(fp, "%s|%s", idbrano, idartista);
	} else {
		fprintf(fp, "\n%s|%s", idbrano, idartista);
	}
	fclose(fp);
}

database modificaArtista(database db) {
	int id=0, modalita=-1, controllo=0;
	char scelta='a';
	mostraTuttiArtisti(db);
	while (ottieniPosDaID(db, 2, id)==-1) {
		printf("\n\nInserire l'identificativo dell'artista da modificare: ");
		scanf("%d", &id);
		if (ottieniPosDaID(db, 2,id)==-1) {
			printf("\nArtista non trovato, riprovare");
		}
	}
	printf("\nHai scelto l'artista:");
	mostraSingoloArtista(db, id);
	pulisciBuffer();
	while (controllo!=-1) {
		printf("\nSicuro di voler continuare? [Y/N]: ");
		scanf("%c", &scelta);
		if (scelta=='Y'||scelta=='y'||scelta=='N'||scelta=='n') {
			controllo=-1;
		}
	}
	if (scelta=='Y'||scelta=='y') {
		printf("\n===[Sistema di modifica artista]===");
		printf("\n[1] Modifica il Nome");
		printf("\n[2] Modifica il Cognome");
		printf("\n[3] Modifica il Nome d'arte");
		printf("\n[4] Modifica il link della biografia");
		printf("\n[0] Esci");
		while (modalita<0||modalita>3) {
			printf("\nInserisci la tua scelta: ");
			scanf("%d", &modalita);
		}
		if (modalita!=0) {
			db = modificaSingoloArtista(db, modalita, id);
		}
	}
	return db;
}

database modificaSingoloArtista(database db, int modalita, int id) {
	pulisciBuffer();
	int pos = ottieniPosDaID(db, 2,id);
	if (modalita==1) {
		char *nome = malloc(MAX_MEDIO);
		printf("\nInserisci nuovo nome: ");
		nome = inputStringaSicuro(MAX_MEDIO,nome);
		strcpy(db.artista[pos].nome, nome);
		free(nome);
	} else if (modalita==2) {
		char *cognome = malloc(MAX_MEDIO);
		printf("\nInserisci nuovo cognome: ");
		cognome = inputStringaSicuro(MAX_MEDIO,cognome);
		strcpy(db.artista[pos].cognome, cognome);
		free(cognome);
	} else if (modalita==3) {
		char *nomearte = malloc(MAX_MEDIO);
		printf("\nInserisci nuovo nome d'arte: ");
		nomearte = inputStringaSicuro(MAX_MEDIO,nomearte);
		strcpy(db.artista[pos].nomearte, nomearte);
		free(nomearte);
	} else if (modalita==4) {
		char *linkbio = malloc(MAX_ENORME);
		printf("\nInserisci nuovo link della biografia: ");
		linkbio = inputStringaSicuro(MAX_ENORME, linkbio);
		strcpy(db.artista[pos].linkbio, linkbio);
		free(linkbio);
	}
	db_modificato=1;
	printf("\nArtista aggiornato, ecco il risultato:\n");
	mostraSingoloArtista(db, id);
	return db;
}

database cancellaArtista(database db) {
	int id=0;
	char scelta='N';
	mostraTuttiArtisti(db);
	while (ottieniPosDaID(db, 2,id)==-1) {
		printf("\n\nInserire l'identificativo dell'artista da cancellare: ");
		scanf("%d", &id);
		if (ottieniPosDaID(db, 2,id)==-1) {
			printf("\nArtista non trovato, riprovare");
		}

	}
	printf("\nHai scelto l'artista: ");
	mostraSingoloArtista(db, id);
	pulisciBuffer();
	printf("\nSicuro di voler continuare? Cancellera' anche i brani collegati ad esso. [Y/N]: ");
	scanf("%c", &scelta);
	if (scelta=='Y'||scelta=='y') {
		db = cancellaSingoloArtista(db, id);
	}
	return db;
}

database cancellaSingoloArtista(database db, int id) {
	int n=contaNelDatabase(db,2);
	int i=ottieniPosDaID(db, 2, id);
	while(i<n-1) {
		db.artista[i] = db.artista[i+1];
		i++;
	}
	db.artista[n-1].id = 0;

	int nbrani=contaNelDatabase(db,5);
	i=0;
	while (i<nbrani) {
		if(db.branoArtista[i].idArtista==id) {
			db = cancellaSingoloBrano(db, db.branoArtista[i].idBrano);
			i=-1;
		}
		i++;
	}
	db_modificato=1;
	printf("\nAlbum cancellato.");
	return db;
}

void visualizzaBiografiaArtista(database db) {
	int id=0, pos=0, esito=0;
	printf("\nCerca biografia dell'artista: ");
	esito = mostraInfo(db, 0);
	if (esito==1) {
		pulisciBuffer();
		while(ottieniPosDaID(db, 2,id)==-1) {
			printf("\n\nInserisci l'identificativo dell'artista: ");
			scanf("%d", &id);
			if (ottieniPosDaID(db, 2,id)==1) {
				printf("\nArtista non trovato, riprovare");
			}
		}
		pos=ottieniPosDaID(db, 2,id);
		apriLink(db.artista[pos].linkbio);
	} else {
		printf("\n\nNessun artista trovato.");
	}
}
