/*
 * Ampere 0.1 rev. 2720 - 09.05.2020
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
#include "../gestori/GestoreArtisti.h"
#include "../gestori/GestoreAlbum.h"
#include "../gestori/GestoreGeneri.h"
#include "../gestori/GestoreFile.h"
#include "../database/DatabaseUtils.h"
#include "../database/Database.h"
#include "../sys/Utils.h"
#include "../sys/Impostazioni.h"

void cancellaDatabaseFile() {
	remove(file_brani);
	remove(file_albums);
	remove(file_associazioneartisti);
	remove(file_artisti);
	remove(file_collezione);
	remove(file_generi);
	remove(file_tipobrano);
	remove(file_playlists);
	remove(file_raccolta);
	remove(file_utenti);
}

void salvaModificheSuFile() {
	salvaBraniSuFile();
	salvaAlbumSuFile();
	salvaArtistiSuFile();
	salvaGeneriSuFile();
	salvaPlaylistSuFile();
	salvaUtentiSuFile();
	// Blocco associazioni
	salvaCollezioneSuFile();
	salvaAssociazioniArtistiSuFile();
	salvaTipiBraniSuFile();
	salvaRaccoltaSuFile();
	if (isAdmin())
		printf("\nSalvate tutte le modifiche effettuate al database su file.");
}

void salvaBraniSuFile() {
	backupFile(file_brani, "temp_brani.txt");
	remove(file_brani);
	int i=0;
	int n=contaNelDatabase(0);
	while (i<n) {
		char id[MAX_CHAR], durata[MAX_CHAR], album[MAX_CHAR], anno[5], ascolti[MAX_CHAR];
		sprintf(id, "%d", db.brano[i].id);
		sprintf(durata, "%d", db.brano[i].durata);
		sprintf(album, "%d", db.brano[i].album);
		sprintf(anno, "%d", db.brano[i].anno);
		sprintf(ascolti, "%d", db.brano[i].ascolti);
		inserisciBranoSuFile(id, db.brano[i].titolo, durata, album, anno, ascolti);
		i++;
	}
	remove("temp_brani.txt");
	if (isAdmin())
		printf("\nBrani salvati.");
}

void salvaAlbumSuFile() {
	backupFile(file_albums, "temp_albums.txt");
	remove(file_albums);
	int i=0;
	int n=contaNelDatabase(1);
	while (i<n) {
		char id[MAX_CHAR], anno[5];
		sprintf(id, "%d", db.album[i].id);
		sprintf(anno, "%d", db.album[i].anno);
		inserisciAlbumSuFile(id, db.album[i].titolo, anno);
		i++;
	}
	remove("temp_albums.txt");
	if (isAdmin())
		printf("\nAlbum salvati.");
}

void salvaArtistiSuFile() {
	backupFile(file_artisti, "temp_artisti.txt");
	remove(file_artisti);
	int i=0;
	int n=contaNelDatabase(2);
	while (i<n) {
		char id[MAX_CHAR];
		sprintf(id, "%d", db.artista[i].id);
		inserisciArtistiSuFile(id, db.artista[i].nome, db.artista[i].cognome, db.artista[i].nomearte);
		i++;
	}
	remove("temp_artisti.txt");
	if (isAdmin())
		printf("\nArtisti salvati.");
}

void salvaGeneriSuFile() {
	backupFile(file_generi, "temp_generi.txt");
	remove(file_generi);
	int i=0;
	int n=contaNelDatabase(3);
	while (i<n) {
		char id[MAX_CHAR];
		sprintf(id, "%d", db.genere[i].id);
		inserisciGenereSuFile(id, db.genere[i].nome);
		i++;
	}
	remove("temp_generi.txt");
	if (isAdmin())
		printf("\nGeneri salvati.");
}

void salvaPlaylistSuFile() {
	backupFile(file_playlists, "temp_playlists.txt");
	remove(file_playlists);
	int i=0;
	int n=contaNelDatabase(4);
	while (i<n) {
		char id[MAX_CHAR];
		char idUtente[MAX_CHAR];
		char pubblica[MAX_CHAR];
		sprintf(id, "%d", db.playlist[i].id);
		sprintf(idUtente, "%d", db.playlist[i].idUtente);
		if (db.playlist[i].pubblica==true) {
			strcpy(pubblica,"true");
		} else {
			strcpy(pubblica,"false");
		}
		inserisciPlaylistSuFile(id, idUtente, db.playlist[i].nome, db.playlist[i].descrizione, pubblica);
		i++;
	}
	remove("temp_playlists.txt");
	if (isAdmin())
		printf("\nPlaylist salvate.");
}

void salvaUtentiSuFile() {
	backupFile(file_utenti, "temp_utenti.txt");
	remove(file_utenti);
	int i=0;
	int n=contaNelDatabase(-1);
	while(i<n) {
		char id[MAX_CHAR];
		char admin[MAX_CHAR];
		sprintf(id, "%d", db.utente[i].id);
		if (db.utente[i].admin==true) {
			strcpy(admin,"true");
		} else {
			strcpy(admin,"false");
		}
		inserisciUtenteSuFile(id, db.utente[i].username, db.utente[i].password, admin);
		i++;
	}
	remove("temp_utenti.txt");
	if (isAdmin())
		printf("\nUtenti salvati.");
}

//BLOCCO ASSOCIAZIONI

void salvaCollezioneSuFile() {
	backupFile(file_collezione, "temp_collezione.txt");
	remove(file_collezione);
	int i=0;
	int n=contaNelDatabase(6);
	while (i<n) {
		char idAlbum[MAX_CHAR], idBrano[MAX_CHAR];
		sprintf(idAlbum, "%d", db.albumBrano[i].idAlbum);
		sprintf(idBrano, "%d", db.albumBrano[i].idBrano);
		inserisciCollezioneSuFile(idAlbum, idBrano);
		i++;
	}
	remove("temp_collezione.txt");
	if (isAdmin())
		printf("\nAssociazioni album-brano salvate.");
}

void salvaAssociazioniArtistiSuFile() {
	backupFile(file_associazioneartisti, "temp_associazioneartisti.txt");
	remove(file_associazioneartisti);
	int i=0;
	int n=contaNelDatabase(5);
	while(i<n) {
		char idBrano[MAX_CHAR], idArtista[MAX_CHAR];
		sprintf(idBrano, "%d", db.artistaBrano[i].idBrano);
		sprintf(idArtista, "%d", db.artistaBrano[i].idArtista);
		inserisciAssociazioneArtistiSuFile(idBrano, idArtista);
		i++;
	}
	remove("temp_associazioneartisti.txt");
	if (isAdmin())
		printf("\nAssociazioni artista-brano salvate.");
}

void salvaTipiBraniSuFile() {
	backupFile(file_tipobrano, "temp_tipobrano.txt");
	remove(file_tipobrano);
	int i=0;
	int n=contaNelDatabase(7);
	while(i<n) {
		char idBrano[MAX_CHAR], idGenere[MAX_CHAR];
		sprintf(idBrano, "%d", db.branoGenere[i].idBrano);
		sprintf(idGenere, "%d", db.branoGenere[i].idGenere);
		inserisciTipiBraniSuFile(idBrano, idGenere);
		i++;
	}
	remove("temp_tipobrano.txt");
	if (isAdmin())
		printf("\nAssociazioni genere-brano salvate.");
}

void salvaRaccoltaSuFile() {
	backupFile(file_raccolta, "temp_raccolta.txt");
	remove(file_raccolta);
	int i=0;
	int n=contaNelDatabase(8);
	while(i<n) {
		char idPlaylist[MAX_CHAR];
		char idBrano[MAX_CHAR];
		sprintf(idPlaylist, "%d", db.playlistBrano[i].idPlaylist);
		sprintf(idBrano, "%d", db.playlistBrano[i].idBrano);
		inserisciRaccoltaSuFile(idPlaylist, idBrano);
		i++;
	}
	remove("temp_raccolta.txt");
	if (isAdmin())
		printf("\nAssociazioni playlist-brano salvate.");
}
