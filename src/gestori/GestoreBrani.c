/*
 * Ampere 0.1 rev. 2931 - 10.05.2020
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
	pulisciBuffer();
	printf("\nInserisci genere del brano: ");
	genere = inputStringaSicuro(genere);
	id_genere = creaGenereSeNonEsiste(genere);
	pulisciBuffer();
	while (durata<=0||durata>9999) {
		printf("\nInserisci durata del brano in secondi: ");
		scanf("%d", &durata);
	}
	while (anno<=0||anno>3000) {
		printf("\nInserisci anno d'uscita del brano: ");
		scanf("%d", &anno);
	}
	while (ascolti<=0) {
		printf("\nInserisci numero d'ascolti del brano: ");
		scanf("%d", &ascolti);
	}
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
		fprintf(fp, "%s|%s|%s|%s|%s|%s", id, titolo, durata, id_album, anno, ascolti);
	} else {
		fprintf(fp, "\n%s|%s|%s|%s|%s|%s", id, titolo, durata, id_album, anno, ascolti);
	}
	fclose(fp);
}

void modificaBrano() {
	int id=0, modalita=-1, controllo=0;
	char scelta='a';
	mostraTuttiBrani();
	while (ottieniPosDaID(0,id)==-1) {
		printf("\n\nInserire l'identificativo del brano da modificare: ");
		scanf("%d", &id);
		if (ottieniPosDaID(0,id)==-1) {
			printf("\nBrano non trovato, riprovare");
		}
	}
	printf("\nHai scelto il brano:");
	mostraSingoloBrano(id);
	pulisciBuffer();
	while (controllo!=-1) {
		printf("\nSicuro di voler continuare? [Y/N]: ");
		scanf("%c", &scelta);
		if (scelta=='Y'||scelta=='y'||scelta=='N'||scelta=='n') {
			controllo=-1;
		}
	}
	if (scelta=='Y'||scelta=='y') {
		printf("\n===[Sistema di modifica brani]===");
		printf("\n[1] Modifica il Titolo");
		printf("\n[2] Modifica la Durata");
		printf("\n[3] Modifica l'Anno");
		printf("\n[4] Modifica gli Ascolti");
		printf("\n[5] Modifica l'album d'appartenenza");
		printf("\n[6] Modifica artista d'appartenenza");
		printf("\n[0] Esci");
		while (modalita<0||modalita>6) {
			printf("\nInserisci la tua scelta: ");
			scanf("%d", &modalita);
		}
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
		while (durata<=0||durata>9999) {
			printf("\nInserisci nuova durata (in secondi): ");
			scanf("%d", &durata);
		}
		db.brano[pos].durata = durata;
	} else if (modalita==3) {
		int anno=0;
		while (anno<=0||anno>3000) {
			printf("\nInserisci nuovo anno: ");
			scanf("%d", &anno);
		}
		db.brano[pos].anno = anno;
	} else if (modalita==4) {
		int ascolti=0;
		while (ascolti<=0) {
			printf("\nInserisci nuovi ascolti: ");
			scanf("%d", &ascolti);
		}
		db.brano[pos].durata = ascolti;
	} else if (modalita==5) {
		char *album = malloc(MAX_CHAR);
		int id_album=0;
		printf("\nInserisci nome album: ");
		album = inputStringaSicuro(album);
		id_album = creaAlbumSeNonEsiste(album);
		free(album);
		int n_album_brano=contaNelDatabase(6);
		int i=0;
		while (i<n_album_brano) {
			if (db.albumBrano[i].idBrano==db.brano[pos].id) {
				db.albumBrano[i].idAlbum = id_album;
			}
		}
		db.brano[pos].album = id_album;
	} else if (modalita==6) {
		char *artista = malloc(MAX_CHAR);
		int id_artista=0;
		printf("\nInserisci nome d'arte artista: ");
		artista = inputStringaSicuro(artista);
		id_artista = creaArtistaSeNonEsiste(artista);
		free(artista);
		int n_artista_brano=contaNelDatabase(5);
		int i=0;
		while(i<n_artista_brano) {
			if (db.artistaBrano[i].idBrano==db.brano[pos].id) {
				db.artistaBrano[i].idArtista = id_artista;
			}
		}
	}
	db_modificato = 1;
	printf("\nBrano aggiornato, ecco il risultato:\n");
	mostraSingoloBrano(id);
}

void cancellaBrano() {
	int id=0, controllo=0;
	char scelta='a';
	mostraTuttiBrani();
	while (ottieniPosDaID(0,id)==-1) {
		printf("\n\nInserire l'identificativo del brano da cancellare: ");
		scanf("%d", &id);
		if (ottieniPosDaID(0,id)==-1) {
			printf("\nBrano non trovato, riprovare");
		}
	}
	printf("\nHai scelto il brano:");
	mostraSingoloBrano(id);
	pulisciBuffer();
	while (controllo!=-1) {
		printf("\nSicuro di voler continuare? [Y/N]: ");
		scanf("%c", &scelta);
		if (scelta=='Y'||scelta=='y'||scelta=='N'||scelta=='n') {
			controllo=-1;
		}
	}
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
	FILE *fp;
	if(os==0) {
		sprintf(posizione_testo, "%s\\%d%s", cartella_testi, idBrano, ".txt");
		fp=fopen(posizione_testo, "r");
		if (fp==NULL) {
			printf("\nIl brano scelto non possiede al momento del testo.");
		} else {
			system(posizione_testo);
		}
		fclose(fp);
	} else if (os==1) {
		sprintf(posizione_testo, "%s/%d%s", cartella_testi, idBrano, ".txt");
		fp=fopen(posizione_testo, "r");
		if (fp==NULL) {
			printf("\nIl brano scelto non possiede al momento del testo.");
		} else {
			strcpy(comando, "open ");
			strcat(comando, posizione_testo);
			system(comando);
		}
		fclose(fp);
	} else if (os==2) {
		sprintf(posizione_testo, "%s/%d%s", cartella_testi, idBrano, ".txt");
		fp=fopen(posizione_testo, "r");
		if (fp==NULL) {
			printf("\nIl brano scelto non possiede al momento del testo.");
		} else {
			strcpy(comando, "nano ");
			strcat(comando, posizione_testo);
			system(comando);
		}
		fclose(fp);
	}
	free(posizione_testo); free(comando);
}

void apriTestoDaRicerca() {
	int scelta=-1, controllo=0, idbrano=0, esito=0;
	pulisciBuffer();
	printf("\nCerca brano del quale si vuole aprire il testo");
	while (controllo!=-1) {
		while (scelta<0||scelta>4) {
			printf("\nCerca per titolo[0], anno[1], artista[2], album[3], genere[4]: ");
			scanf("%d", &scelta);
		}
		if (scelta==0) {
			esito = mostraBrani(0);
			controllo=-1;
		} else if (scelta==1) {
			esito = mostraBrani(1);
			controllo=-1;
		} else if (scelta==2) {
			esito = mostraBraniArtista();
			controllo=-1;
		} else if (scelta==3) {
			esito = mostraBraniAlbum();
			controllo=-1;
		} else if (scelta==4) {
			esito = mostraBraniGenere();
			controllo=-1;
		} else {
			printf("Scelta sbagliata, riprovare.");
		}
	}
	if (esito==1) {
		while (ottieniPosDaID(0,idbrano)==-1) {
			printf("\nInserisci id del brano selezionato: ");
			scanf("%d", &idbrano);
			if (ottieniPosDaID(0,idbrano)==-1) {
				printf("\nBrano non trovato, riprovare");
			} else {
				apriTesto(idbrano);
			}
		}
	} else {
		printf("\n\nLa ricerca non ha prodotto risultati");
	}
}

void apriTestoDaID() {
	int idbrano=0;
	pulisciBuffer();
	while (ottieniPosDaID(0,idbrano)==-1) {
		printf("\nInserisci l'id del brano del quale si vuole aprire il testo: ");
		scanf("%d", &idbrano);
		if (ottieniPosDaID(0,idbrano)==-1) {
			printf("\nBrano non trovato, riprovare");
		}
	}
}

