/*
 * Ampere 0.1 rev. 2223 - 06.05.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../gestori/GestorePlaylist.h"
#include "../gestori/GestoreUtenti.h"
#include "../gestori/GestoreBrani.h"
#include "../gestori/GestoreAlbum.h"
#include "../gestori/GestoreArtisti.h"
#include "../gestori/GestoreGeneri.h"
#include "../ricerca/RicercaGenerale.h"
#include "../ricerca/MotoreRicerca.h"
#include "../database/Database.h"
#include "../database/DatabaseUtils.h"
#include "../sys/Utils.h"
#include "../sys/Impostazioni.h"

void inserisciPlaylist(int idUtente, char nome[], char descrizione[]) {
	db_modificato=1;
	int n=contaNelDatabase(4);
	db.playlist[n].id = trovaUltimoId(4)+1;
	db.playlist[n].idUtente = idUtente;
	strcpy(db.playlist[n].nome, nome);
	strcpy(db.playlist[n].descrizione, descrizione);
}

void inserisciBraniPlaylist(int idPlaylist, int idBrano) {
	db_modificato=1;
	int n=contaNelDatabase(8);
	db.playlistBrano[n].idPlaylist = idPlaylist;
	db.playlistBrano[n].idBrano = idBrano;
}

void creaPlaylistGuidato() {
	char scelta='n';
	int idUtente = db.utente_connesso;
	char *nome = malloc(MAX_CHAR);
	char *descrizione = malloc(MAX_CHAR);
	printf("\n===[Creazione guidata di una playlist]===");
	pulisciBuffer();
	printf("\nInserisci nome della playlist: ");
	nome = inputStringaSicuro(nome);
	printf("\nInserisci descrizione della playlist: ");
	descrizione = inputStringaSicuro(descrizione);
	inserisciPlaylist(idUtente, nome, descrizione);
	printf("\nVuoi inserire brani nella tua playlist? [Y/N]: ");
	scanf("%c", &scelta);
	if (scelta=='Y'||scelta=='y') {
		inserimentoBraniPlaylistGuidato();
	}
}

void inserimentoBraniPlaylistGuidato() {
	pulisciBuffer();
	int scelta=0, id=0, n=0, i=0, branoscelto=0;
	int nbrani = contaNelDatabase(0);
	printf("\n===[Inserimento guidato di brani in una playlist]===");
	printf("\nScegli la playlist da modificare: ");
	mostraPlaylistUtente(-1,db.utente_connesso);
	printf("\nInserisci id della playlist: ");
	scanf("%d", &id);
	printf("\nInserisci fino a %d brani nella playlist %s", nbrani, db.playlist[ottieniPosDaID(4,id)].nome);
	while (n<=0||n>nbrani) {
		printf("\nQuanti brani vuoi inserire? ");
		scanf("%d", &n);
	}
	int idbrani[n];
	i=0;
	while (i<n) {
		printf("Cercare per titolo[0], anno[1], artista[2], album[3], genere[4]?");
		scanf("%d", &scelta);
		if (scelta==0) {
			mostraBrani(0);
		} else if (scelta==1) {
			mostraBrani(1);
		} else if (scelta==2) {
			mostraBraniArtista();
		} else if (scelta==3) {
			mostraBraniAlbum();
		} else if (scelta==4) {
			mostraBraniGenere();
		}
		printf("\nInserire id del brano da inserire nella playlist: ");
		scanf("%d", &branoscelto);
		idbrani[i] = branoscelto;
		i++;
	}

	i=0;
	while (i<n) {
		inserisciBraniPlaylist(id, idbrani[i]);
		i++;
	}

	printf("\nBrani inseriti nella playlist %s", db.playlist[ottieniPosDaID(4, id)].nome);

}

void inserisciPlaylistSuFile(char id[], char idUtente[], char nome[], char descrizione[]) {
	FILE* fp=fopen(file_playlists,"a");
	if (controllaSeFileVuoto(file_playlists)==1) {
		fprintf(fp, "%s,%s,%s,%s", id, idUtente, nome, descrizione);
	} else {
		fprintf(fp, "\n%s,%s,%s,%s", id, idUtente, nome, descrizione);
	}
	fclose(fp);
}

void inserisciRaccoltaSuFile(char idplaylist[], char idbrano[]) {
	FILE* fp=fopen(file_raccolta,"a");
	if (controllaSeFileVuoto(file_raccolta)==1) {
		fprintf(fp, "%s,%s", idplaylist, idbrano);
	} else {
		fprintf(fp, "\n%s,%s", idplaylist, idbrano);
	}
	fclose(fp);
}

void modificaPlaylist() {
	int id=0, modalita=0;
	char scelta='N';
	if (isAdmin()) {
		mostraTuttePlaylist(-1);
	} else {
		mostraPlaylistUtente(-1, db.utente_connesso);
	}
	printf("\n\nInserire l'identificativo della playlist da modificare: ");
	scanf("%d", &id);
	printf("\nHai scelto la playlist");
	mostraSingolaPlaylist(-1, id);
	pulisciBuffer();
	printf("\nSicuro di voler continuare? [Y/N]: ");
	scanf("%c", &scelta);
	if (scelta=='Y'||scelta=='y') {
		printf("\n===[Sistema di modifica playlist]===");
		printf("\n[1] Modifica il nome");
		printf("\n[2] Modifica la descrizione");
		if (isAdmin())
			printf("\n[3] Modifica l'autore della playlist");
		printf("\n[0] Esci");
		scanf("%d", &modalita);
		if (modalita!=0) {
			modificaSingolaPlaylist(modalita, id);
		}
	}
}

void modificaSingolaPlaylist(int modalita, int id) {
	pulisciBuffer();
	int pos = ottieniPosDaID(4,id);
	if (modalita==1) {
		char *nome = malloc(MAX_CHAR);
		printf("\nInserisci nuovo nome: ");
		nome = inputStringaSicuro(nome);
		strcpy(db.playlist[pos].nome, nome);
		free(nome);
	} else if (modalita==2) {
		char *descrizione = malloc(MAX_CHAR);
		printf("\nInserisci nuova descrizione: ");
		descrizione = inputStringaSicuro(descrizione);
		strcpy(db.playlist[pos].descrizione, descrizione);
		free(descrizione);
	}
	db_modificato=1;
	printf("Playlist aggiornata, ecco il risultato:\n");
	mostraSingolaPlaylist(-1,id);
}

void cancellaPlaylist() {
	int id=0;
	char scelta='N';
	if (isAdmin()) {
		mostraTuttePlaylist(-1);
	} else {
		mostraPlaylistUtente(-1, db.utente_connesso);
	}
	printf("\n\nInserire l'identificativo della playlist: ");
	scanf("%d", &id);
	printf("\nHai scelto la playlist: ");
	mostraSingolaPlaylist(-1, id);
	pulisciBuffer();
	printf("\nSicuro di voler continuare? [Y/N]: ");
	scanf("%c", &scelta);
	if(scelta=='Y'||scelta=='y') {
		cancellaSingolaPlaylist(id);
	}
}

void cancellaSingolaPlaylist(int id) {
	int n=contaNelDatabase(4);
	int i=ottieniPosDaID(4, id);
	while (i<n-1) {
		db.playlist[i] = db.playlist[i+1];
		i++;
	}
	db.playlist[n-1].id = 0;
	cancellaAssociazioniPlaylist(id);
}

void cancellaAssociazioniPlaylist(int id) {
	int n=contaNelDatabase(8);
	int i=ottieniPosDaID(8, id);
	while (i<n-1) {
		db.playlistBrano[i] = db.playlistBrano[i+1];
		i++;
	}
	db.playlistBrano[n-1].idPlaylist = 0;
	db.playlistBrano[n-1].idBrano = 0;
	db_modificato=1;
	printf("\nPlaylist cancellata.");
}
