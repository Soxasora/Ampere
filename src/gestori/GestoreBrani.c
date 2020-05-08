/*
 * Ampere 0.1 rev. 2420 - 08.05.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ricerca/MotoreRicerca.h"
#include "../gestori/GestoreFile.h"
#include "../gestori/GestoreBrani.h"
#include "../gestori/GestoreArtisti.h"
#include "../gestori/GestoreAlbum.h"
#include "../gestori/GestoreGeneri.h"
#include "../database/Database.h"
#include "../database/DatabaseUtils.h"
#include "../sys/Utils.h"
#include "../sys/Impostazioni.h"

void inserimentoBranoGuidato() {
	char *titolo = malloc(MAX_CHAR);
	char *artista = malloc(MAX_CHAR);
	int id_artista=0;
	char *album = malloc(MAX_CHAR);
	int id_album=0;
	char *genere = malloc(MAX_CHAR);
	int id_genere=0;
	int durata=0;
	int anno=0;
	int ascolti=0;
	// Registrazione
	pulisciBuffer();
	printf("\nInserisci titolo: ");
	titolo = inputStringaSicuro(titolo);
	printf("\nInserisci nome artista: ");
	artista = inputStringaSicuro(artista);
	id_artista = creaArtistaSeNonEsiste(artista);
	printf("\nInserisci nome album: ");
	album = inputStringaSicuro(album);
	id_album = creaAlbumSeNonEsiste(album);
	printf("\nInserisci genere del brano: ");
	genere = inputStringaSicuro(genere);
	id_genere = creaGenereSeNonEsiste(genere);
	pulisciBuffer();
	printf("\nInserisci durata del brano in secondi: ");
	scanf("%d", &durata);
	printf("\nInserisci anno d'uscita del brano: ");
	scanf("%d", &anno);
	printf("\nInserisci numero d'ascolti del brano: ");
	scanf("%d", &ascolti);
	inserisciBrano(titolo, id_artista, id_album, id_genere, durata, anno, ascolti);
	free(titolo); free(artista); free(album); free(genere);
	printf("\n\nBrano Inserito.");
}

void inserisciBrano(char titolo[], int id_artista, int id_album, int id_genere, int durata, int anno, int ascolti) {
	db_modificato=1;
	// Inserimento brano nel database
	int n=contaNelDatabase(0);
	db.brano[n].id = trovaUltimoId(0)+1;
	strcpy(db.brano[n].titolo,titolo);
	db.brano[n].durata = durata;
	db.brano[n].album = id_album;
	db.brano[n].anno = anno;
	db.brano[n].ascolti = ascolti;

	// Associazioni
	int n_artista_brano=contaNelDatabase(5);
	int n_album_brano=contaNelDatabase(6);
	int n_genere_brano=contaNelDatabase(7);
	db.artistaBrano[n_artista_brano].idBrano = db.brano[n].id;
	db.artistaBrano[n_artista_brano].idArtista = id_artista;
	db.albumBrano[n_album_brano].idAlbum = id_album;
	db.albumBrano[n_album_brano].idBrano = db.brano[n].id;
	db.branoGenere[n_genere_brano].idGenere = id_genere;
	db.branoGenere[n_genere_brano].idBrano = db.brano[n].id;

}

void inserisciBranoSuFile(char id[], char titolo[], char durata[], char id_album[], char anno[], char ascolti[]) {
	FILE* fp=fopen(file_brani, "a");
	if (controllaSeFileVuoto(file_brani)==1) {
		fprintf(fp, "%s,%s,%s,%s,%s,%s", id, titolo, durata, id_album, anno, ascolti);
	} else {
		fprintf(fp, "\n%s,%s,%s,%s,%s,%s", id, titolo, durata, id_album, anno, ascolti);
	}
	fclose(fp);
}

void modificaBrano() {
	int id=0, modalita=0;
	char scelta='N';
	mostraTuttiBrani();
	printf("\n\nInserire l'identificativo del brano da modificare: ");
	scanf("%d", &id);
	printf("\nHai scelto il brano:");
	mostraSingoloBrano(id);
	pulisciBuffer();
	printf("\nSicuro di voler continuare? [Y/N]: ");
	scanf("%c", &scelta);
	if (scelta=='Y'||scelta=='y') {
		printf("\n===[Sistema di modifica brani]===");
		printf("\n[1] Modifica il Titolo");
		printf("\n[2] Modifica la Durata");
		printf("\n[3] Modifica l'Anno");
		printf("\n[4] Modifica gli Ascolti");
		printf("\n[5] Modifica l'album d'appartenenza");
		printf("\n[0] Esci");
		printf("\nInserisci la tua scelta: ");
		scanf("%d", &modalita);
		if (modalita!=0) {
			modificaSingoloBrano(modalita, id);
		}
	}
}

void modificaSingoloBrano(int modalita, int id) {
	pulisciBuffer();
	int pos = ottieniPosDaID(0, id);
	if (modalita==1) {
		char *titolo = malloc(MAX_CHAR);
		printf("\nInserisci nuovo titolo: ");
		titolo = inputStringaSicuro(titolo);
		strcpy(db.brano[pos].titolo, titolo);
		free(titolo);
	} else if (modalita==2) {
		int durata=0;
		printf("\nInserisci nuova durata (in secondi): ");
		scanf("%d", &durata);
		db.brano[pos].durata = durata;
	} else if (modalita==3) {
		int anno=0;
		printf("\nInserisci nuovo anno: ");
		scanf("%d", &anno);
		db.brano[pos].anno = anno;
	} else if (modalita==4) {
		int ascolti=0;
		printf("\nInserisci nuovi ascolti: ");
		scanf("%d", &ascolti);
		db.brano[pos].durata = ascolti;
	}
	db_modificato = 1;
	printf("\nBrano aggiornato, ecco il risultato:\n");
	mostraSingoloBrano(id);
}

void cancellaBrano() {
	int id=0;
	char scelta='N';
	mostraTuttiBrani();
	printf("\n\nInserire l'identificativo del brano da cancellare: ");
	scanf("%d", &id);
	printf("\nHai scelto il brano:");
	mostraSingoloBrano(id);
	pulisciBuffer();
	printf("\nSicuro di voler continuare? [Y/N]: ");
	scanf("%c", &scelta);
	if (scelta=='Y'||scelta=='y') {
		cancellaSingoloBrano(id);
		printf("\nBrano cancellato.");
	}
}

void cancellaSingoloBrano(int id) {
	int n = contaNelDatabase(0);
	int i = ottieniPosDaID(0, id);
	while (i<n-1) {
		db.brano[i] = db.brano[i+1];
		i++;
	}
	db.brano[n-1].id = 0;
	cancellaAssociazioniBrano(id);

	db_modificato=1;
}

void cancellaAssociazioniBrano(int id) {
	//Cancella Associazioni
	int n = contaNelDatabase(5);
	int i = ottieniPosDaID(5, id);

	while (i<n-1) {
		db.artistaBrano[i] = db.artistaBrano[i+1];
		i++;
	}
	db.artistaBrano[n-1].idBrano = 0;
	db.artistaBrano[n-1].idArtista = 0;

	n = contaNelDatabase(6);
	i = ottieniPosDaID(6, id);
	while (i<n-1) {
		db.albumBrano[i] = db.albumBrano[i+1];
		i++;
	}
	db.albumBrano[n-1].idBrano = 0;
	db.albumBrano[n-1].idAlbum = 0;

	n = contaNelDatabase(7);
	i = ottieniPosDaID(7, id);
	while (i<n-1) {
		db.branoGenere[i] = db.branoGenere[i+1];
		i++;
	}
	db.branoGenere[n-1].idBrano = 0;
	db.branoGenere[n-1].idGenere = 0;
}

// TESTI

void apriTesto(int idBrano) {
	char *posizione_testo = malloc(MAX_TEMP);
	char *comando = malloc(MAX_TEMP+10);
	if(os==0) {
		sprintf(posizione_testo, "%s\\%d%s", cartella_testi, idBrano, ".txt");
		system(posizione_testo);
	} else if (os==1) {
		sprintf(posizione_testo, "%s/%d%s", cartella_testi, idBrano, ".txt");
		strcpy(comando, "open ");
		strcat(comando, posizione_testo);
		system(comando);
	} else if (os==2) {
		sprintf(posizione_testo, "%s/%d%s", cartella_testi, idBrano, ".txt");
		strcpy(comando, "nano ");
		strcat(comando, posizione_testo);
		system(comando);
	}
	free(posizione_testo); free(comando);
}

void apriTestoDaRicerca() {
	int scelta=0, controllo=0, idbrano=0;
	pulisciBuffer();
	printf("\nCerca brano del quale si vuole aprire il testo");
	while (controllo!=-1) {
		printf("\nCerca per titolo[0], anno[1], artista[2], album[3], genere[4]: ");
		scanf("%d", &scelta);
		if (scelta==0) {
			mostraBrani(0);
			controllo=-1;
		} else if (scelta==1) {
			mostraBrani(1);
			controllo=-1;
		} else if (scelta==2) {
			mostraBraniArtista();
			controllo=-1;
		} else if (scelta==3) {
			mostraBraniAlbum();
			controllo=-1;
		} else if (scelta==4) {
			mostraBraniGenere();
			controllo=-1;
		} else {
			printf("Scelta sbagliata, riprovare.");
		}
	}
	printf("\nInserisci id del brano selezionato: ");
	scanf("%d", &idbrano);
	apriTesto(idbrano);
}

void apriTestoDaID() {
	int idbrano=0;
	pulisciBuffer();
	printf("\nInserisci l'id del brano del quale si vuole aprire il testo: ");
	scanf("%d", &idbrano);
}

