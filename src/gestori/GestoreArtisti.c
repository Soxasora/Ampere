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

void inserimentoArtistaGuidato() {
	pulisciBuffer();
	char *nomearte = malloc(MAX_CHAR);
	printf("\nInserisci nome d'arte dell'artista: ");
	nomearte = inputStringaSicuro(nomearte);
	creaArtistaSeNonEsiste(nomearte);
	free(nomearte);
}

int creaArtistaGuidato(char nomearte[]) {
	int id=0;
	char *nome = malloc(MAX_CHAR);
	char *cognome = malloc(MAX_CHAR);
	printf("\nSembra che quest'artista non esista nel database, inseriamolo.");
	printf("\n===[Inserimento guidato di un artista]===");
	printf("\nNome d'arte: %s", nomearte);
	printf("\nInserisci nome dell'artista: ");
	nome = inputStringaSicuro(nome);
	printf("\nInserisci cognome dell'artista: ");
	cognome = inputStringaSicuro(cognome);
	id = inserisciArtista(nome, cognome, nomearte);
	free(nome); free(cognome);
	return id;
}

int creaArtistaSeNonEsiste(char nomearte[]) {
	int id = controlloEsistenzaArtista(nomearte);
	if (id==0) {
		id = creaArtistaGuidato(nomearte);
		printf("\nArtista inserito, continuiamo...");
	} else {
		printf("\nArtista esistente.");
	}
	return id;
}

int inserisciArtista(char nome[], char cognome[], char nomearte[]) {
	db_modificato=1;
	int n=contaNelDatabase(2);
	db.artista[n].id = trovaUltimoId(2)+1;
	strcpy(db.artista[n].nome,nome);
	strcpy(db.artista[n].cognome,cognome);
	strcpy(db.artista[n].nomearte,nomearte);
	return db.artista[n].id;
}

int controlloEsistenzaArtista(char nomearte[]) {
	int id=0, i=0, n=contaNelDatabase(2), controllo=0;
	while (i<n&&controllo!=-1) {
		if (comparaStringhe(db.artista[i].nomearte, nomearte)==0) {
			id = db.artista[i].id;
			controllo=-1;
		}
		i++;
	}
	return id;
}

void inserisciArtistiSuFile(char id[], char nome[], char cognome[], char nomearte[]) {
	FILE* fp=fopen(file_artisti, "a");
	if (controllaSeFileVuoto(file_artisti)==1) {
		fprintf(fp, "%s,%s,%s,%s", id, nome, cognome, nomearte);
	} else {
		fprintf(fp, "\n%s,%s,%s,%s", id, nome, cognome, nomearte);
	}
	fclose(fp);
}

void inserisciAssociazioneArtistiSuFile(char idbrano[], char idartista[]) {
	FILE* fp=fopen(file_associazioneartisti, "a");
	if (controllaSeFileVuoto(file_associazioneartisti)==1) {
		fprintf(fp, "%s,%s", idbrano, idartista);
	} else {
		fprintf(fp, "\n%s,%s", idbrano, idartista);
	}
	fclose(fp);
}

void modificaArtista() {
	int id=0, modalita=0;
	char scelta='N';
	mostraTuttiArtisti();
	printf("\n\nInserire l'identificativo dell'artista da modificare: ");
	scanf("%d", &id);
	printf("\nHai scelto l'artista:");
	mostraSingoloArtista(id);
	pulisciBuffer();
	printf("\nSicuro di voler continuare? [Y/N]: ");
	scanf("%c", &scelta);
	if (scelta=='Y'||scelta=='y') {
		printf("\n===[Sistema di modifica artista]===");
		printf("\n[1] Modifica il Nome");
		printf("\n[2] Modifica il Cognome");
		printf("\n[3] Modifica il Nome d'arte");
		printf("\n[0] Esci");
		printf("\nInserisci la tua scelta");
		if (modalita!=0) {
			modificaSingoloArtista(modalita, id);
		}
	}
}

void modificaSingoloArtista(int modalita, int id) {
	pulisciBuffer();
	int pos = ottieniPosDaID(2,id);
	if (modalita==1) {
		char *nome = malloc(MAX_CHAR);
		printf("\nInserisci nuovo nome: ");
		nome = inputStringaSicuro(nome);
		strcpy(db.artista[pos].nome, nome);
		free(nome);
	} else if (modalita==2) {
		char *cognome = malloc(MAX_CHAR);
		printf("\nInserisci nuovo cognome: ");
		cognome = inputStringaSicuro(cognome);
		strcpy(db.artista[pos].cognome, cognome);
		free(cognome);
	} else if (modalita==3) {
		char *nomearte = malloc(MAX_CHAR);
		printf("\nInserisci nuovo nome d'arte: ");
		nomearte = inputStringaSicuro(nomearte);
		strcpy(db.artista[pos].nomearte, nomearte);
		free(nomearte);
	}
	db_modificato=1;
	printf("\nArtista aggiornato, ecco il risultato:\n");
	mostraSingoloArtista(id);
}

void cancellaArtista() {
	int id=0;
	char scelta='N';
	mostraTuttiArtisti();
	printf("\n\nInserire l'identificativo dell'artista da cancellare: ");
	scanf("%d", &id);
	printf("\nHai scelto l'artista: ");
	mostraSingoloArtista(id);
	pulisciBuffer();
	printf("\nSicuro di voler continuare? Cancellera' anche i brani collegati ad esso. [Y/N]: ");
	scanf("%c", &scelta);
	if (scelta=='Y'||scelta=='y') {
		cancellaSingoloArtista(id);
	}
}

void cancellaSingoloArtista(int id) {
	int n=contaNelDatabase(2);
	int i=ottieniPosDaID(2, id);
	while(i<n-1) {
		db.artista[i] = db.artista[i+1];
		i++;
	}
	db.artista[n-1].id = 0;

	int nbrani=contaNelDatabase(5);
	i=0;
	while (i<nbrani) {
		if(db.artistaBrano[i].idArtista==id) {
			cancellaSingoloBrano(db.artistaBrano[i].idBrano);
			i=-1;
		}
		i++;
	}
	db_modificato=1;
	printf("\nAlbum cancellato.");
}
