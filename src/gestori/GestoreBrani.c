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
#include "../gestori/GestoreAssociazioni.h"
#include "../gestori/GestoreFile.h"
#include "../gestori/GestoreBrani.h"
#include "../gestori/GestoreArtisti.h"
#include "../gestori/GestoreAlbum.h"
#include "../gestori/GestoreGeneri.h"
#include "../database/Brani.h"
#include "../database/Database.h"
#include "../database/DatabaseUtils.h"
#include "../sys/Utils.h"
#include "../sys/Impostazioni.h"

database inserimentoBranoGuidato(database db) {
	char *titolo = malloc(MAX_MEDIO);
	char *artista = malloc(MAX_MEDIO);
	int id_artista=0;
	char *album = malloc(MAX_MEDIO);
	int id_album=0;
	char *genere = malloc(MAX_MEDIO);
	int id_genere=0;
	int durata=0;
	int anno=0;
	int ascolti=0;
	// Registrazione
	pulisciBuffer();
	printf("\nInserisci titolo: ");
	titolo = inputStringaSicuro(MAX_MEDIO,titolo);
	printf("\nInserisci nome artista: ");
	artista = inputStringaSicuro(MAX_MEDIO,artista);
	db = creaArtistaSeNonEsiste(db, artista);
	id_artista = controlloEsistenzaArtista(db, artista);
	printf("\nInserisci nome album: ");
	album = inputStringaSicuro(MAX_MEDIO,album);
	db = creaAlbumSeNonEsiste(db, album);
	id_album = controlloEsistenzaAlbum(db, album);
	pulisciBuffer();
	printf("\nInserisci genere del brano: ");
	genere = inputStringaSicuro(MAX_MEDIO,genere);
	db = creaGenereSeNonEsiste(db, genere);
	id_genere = controlloEsistenzaGenere(db, genere);
	pulisciBuffer();
	while (durata<=0||durata>9999) {
		printf("\nInserisci durata del brano in secondi: ");
		scanf("%d", &durata);
	}
	while (anno<=1950||anno>2020) {
		printf("\nInserisci anno d'uscita del brano: ");
		scanf("%d", &anno);
	}
	while (ascolti<=0) {
		printf("\nInserisci numero d'ascolti del brano: ");
		scanf("%d", &ascolti);
	}
	db = inserireBrano(db, creaBrano(db, titolo, id_album, durata, anno, ascolti), id_artista, id_genere);
	free(titolo); free(artista); free(album); free(genere);
	printf("\n\nBrano Inserito.");
	return db;
}

struct brani creaBrano(database db, char titolo[], int id_album, int durata, int anno, int ascolti) {
	struct brani brano;
	brano.id = trovaUltimoId(db, 0)+1;
	strcpy(brano.titolo,titolo);
	brano.durata = durata;
	brano.album = id_album;
	brano.anno = anno;
	brano.ascolti = ascolti;
	return brano;
}

database inserireBrano(database db, struct brani brano, int id_artista, int id_genere) {
	db_modificato=1;
	int n=contaNelDatabase(db,0);
	db.brano[n] = brano;

	// Associazioni
	inserireAssociazioneArtista(db,creaAssociazioneArtista(brano.id, id_artista));
	inserireAssociazioneAlbum(db,creaAssociazioneAlbum(brano.id, brano.album));
	inserireAssociazioneGenere(db,creaAssociazioneGenere(brano.id, id_genere));

	return db;
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

database modificaBrano(database db) {
	int id=0, modalita=-1, controllo=0;
	char scelta='a';
	mostraTuttiBrani(db);
	while (ottieniPosDaID(db, 0,id)==-1) {
		printf("\n\nInserire l'identificativo del brano da modificare: ");
		scanf("%d", &id);
		if (ottieniPosDaID(db, 0,id)==-1) {
			printf("\nBrano non trovato, riprovare");
		}
	}
	printf("\nHai scelto il brano:");
	mostraSingoloBrano(db, id);
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
			db = modificaSingoloBrano(db, modalita, id);
		}
	}
	return db;
}

database modificaSingoloBrano(database db, int modalita, int id) {
	pulisciBuffer();
	int pos = ottieniPosDaID(db, 0, id);
	if (modalita==1) {
		char *titolo = malloc(MAX_MEDIO);
		printf("\nInserisci nuovo titolo: ");
		titolo = inputStringaSicuro(MAX_MEDIO,titolo);
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
		while (anno<=1950||anno>2020) {
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
		char *album = malloc(MAX_MEDIO);
		int id_album=0;
		printf("\nInserisci nome album: ");
		album = inputStringaSicuro(MAX_MEDIO,album);
		db = creaAlbumSeNonEsiste(db, album);
		id_album = controlloEsistenzaAlbum(db, album);
		free(album);
		int n_album_brano=contaNelDatabase(db,6);
		int i=0;
		while (i<n_album_brano) {
			if (db.branoAlbum[i].idBrano==db.brano[pos].id) {
				db.branoAlbum[i].idAlbum = id_album;
			}
			i++;
		}
		db.brano[pos].album = id_album;
	} else if (modalita==6) {
		char *artista = malloc(MAX_MEDIO);
		int id_artista=0;
		printf("\nInserisci nome d'arte artista: ");
		artista = inputStringaSicuro(MAX_MEDIO,artista);
		db = creaArtistaSeNonEsiste(db, artista);
		id_artista = controlloEsistenzaArtista(db, artista);
		free(artista);
		int n_artista_brano=contaNelDatabase(db,5);
		int i=0;
		while(i<n_artista_brano) {
			if (db.branoArtista[i].idBrano==db.brano[pos].id) {
				db.branoArtista[i].idArtista = id_artista;
			}
		}
	}
	db_modificato = 1;
	printf("\nBrano aggiornato, ecco il risultato:\n");
	mostraSingoloBrano(db, id);
	return db;
}

database cancellaBrano(database db) {
	int id=0, controllo=0;
	char scelta='a';
	mostraTuttiBrani(db);
	while (ottieniPosDaID(db, 0,id)==-1) {
		printf("\n\nInserire l'identificativo del brano da cancellare: ");
		scanf("%d", &id);
		if (ottieniPosDaID(db, 0,id)==-1) {
			printf("\nBrano non trovato, riprovare");
		}
	}
	printf("\nHai scelto il brano:");
	mostraSingoloBrano(db, id);
	pulisciBuffer();
	while (controllo!=-1) {
		printf("\nSicuro di voler continuare? [Y/N]: ");
		scanf("%c", &scelta);
		if (scelta=='Y'||scelta=='y'||scelta=='N'||scelta=='n') {
			controllo=-1;
		}
	}
	if (scelta=='Y'||scelta=='y') {
		db = cancellaSingoloBrano(db, id);
		printf("\nBrano cancellato.");
	}
	return db;
}

database cancellaSingoloBrano(database db, int id) {
	int n = contaNelDatabase(db,0);
	int i = ottieniPosDaID(db, 0, id);
	while (i<n-1) {
		db.brano[i] = db.brano[i+1];
		i++;
	}
	db.brano[n-1].id = 0;
	db = cancellaAssociazioniBrano(db, id);

	db_modificato=1;
	return db;
}

database cancellaAssociazioniBrano(database db, int id) {
	//Cancella Associazioni
	int n = contaNelDatabase(db,5);
	int i = ottieniPosDaID(db, 5, id);

	while (i<n-1) {
		db.branoArtista[i] = db.branoArtista[i+1];
		i++;
	}
	db.branoArtista[n-1].idBrano = 0;
	db.branoArtista[n-1].idArtista = 0;

	n = contaNelDatabase(db,6);
	i = ottieniPosDaID(db, 6, id);
	while (i<n-1) {
		db.branoAlbum[i] = db.branoAlbum[i+1];
		i++;
	}
	db.branoAlbum[n-1].idBrano = 0;
	db.branoAlbum[n-1].idAlbum = 0;

	n = contaNelDatabase(db,7);
	i = ottieniPosDaID(db, 7, id);
	while (i<n-1) {
		db.branoGenere[i] = db.branoGenere[i+1];
		i++;
	}
	db.branoGenere[n-1].idBrano = 0;
	db.branoGenere[n-1].idGenere = 0;
	return db;
}

// TESTI

void apriTesto(int idBrano) {
	char *posizione_testo = malloc(MAX_ENORME);
	char *comando = malloc(MAX_ENORME+10);
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

void apriTestoDaRicerca(database db) {
	int scelta=-1, controllo=0, idbrano=0, esito=0;
	pulisciBuffer();
	printf("\nCerca brano del quale si vuole aprire il testo");
	while (controllo!=-1) {
		while (scelta<0||scelta>4) {
			printf("\nCerca per titolo[0], anno[1], artista[2], album[3], genere[4]: ");
			scanf("%d", &scelta);
		}
		if (scelta==0) {
			esito = mostraBrani(db, 0);
			controllo=-1;
		} else if (scelta==1) {
			esito = mostraBrani(db, 1);
			controllo=-1;
		} else if (scelta==2) {
			esito = mostraBraniArtista(db);
			controllo=-1;
		} else if (scelta==3) {
			esito = mostraBraniAlbum(db);
			controllo=-1;
		} else if (scelta==4) {
			esito = mostraBraniGenere(db);
			controllo=-1;
		} else {
			printf("Scelta sbagliata, riprovare.");
		}
	}
	if (esito==1) {
		while (ottieniPosDaID(db, 0,idbrano)==-1) {
			printf("\nInserisci id del brano selezionato: ");
			scanf("%d", &idbrano);
			if (ottieniPosDaID(db, 0,idbrano)==-1) {
				printf("\nBrano non trovato, riprovare");
			} else {
				apriTesto(idbrano);
			}
		}
	} else {
		printf("\n\nLa ricerca non ha prodotto risultati");
	}
}

void apriTestoDaID(database db) {
	int idbrano=0;
	pulisciBuffer();
	while (ottieniPosDaID(db, 0,idbrano)==-1) {
		printf("\nInserisci l'id del brano del quale si vuole aprire il testo: ");
		scanf("%d", &idbrano);
		if (ottieniPosDaID(db, 0,idbrano)==-1) {
			printf("\nBrano non trovato, riprovare");
		}
	}
}

