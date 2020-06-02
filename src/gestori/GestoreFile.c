/*
 * Ampere 0.2 rev. 17 - 02.06.2020
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../gestori/GestoreAssociazioni.h"
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
	remove(file_BranoArtista);
	remove(file_artisti);
	remove(file_BranoAlbum);
	remove(file_generi);
	remove(file_BranoGenere);
	remove(file_playlists);
	remove(file_PlaylistBrano);
	remove(file_utenti);
}

void salvaModificheSuFile(database db) {
	salvaBraniSuFile(db);
	salvaAlbumSuFile(db);
	salvaArtistiSuFile(db);
	salvaGeneriSuFile(db);
	salvaPlaylistSuFile(db);
	salvaUtentiSuFile(db);
	// Blocco associazioni
	salvaBranoAlbumSuFile(db);
	salvaAssociazioniArtistiSuFile(db);
	salvaBranoGenereSuFile(db);
	salvaPlaylistBranoSuFile(db);
	if (controllareSeAdmin(db))
		printf("\nSalvate tutte le modifiche effettuate al database su file.");
}

void salvaBraniSuFile(database db) {
	backupFile(file_brani, "temp_brani.txt");
	remove(file_brani);
	int i=0;
	int n=contareNelDatabase(db,0);
	while (i<n) {
		inserisciBranoSuFile(db.brano[i]);
		i++;
	}
	//TODO
	remove("temp_brani.txt");
	if (controllareSeAdmin(db))
		printf("\nBrani salvati.");
}

void salvaAlbumSuFile(database db) {
	backupFile(file_albums, "temp_albums.txt");
	remove(file_albums);
	int i=0;
	int n=contareNelDatabase(db,1);
	while (i<n) {
		inserisciAlbumSuFile(db.album[i]);
		i++;
	}
	remove("temp_albums.txt");
	if (controllareSeAdmin(db))
		printf("\nAlbum salvati.");
}

void salvaArtistiSuFile(database db) {
	backupFile(file_artisti, "temp_artisti.txt");
	remove(file_artisti);
	int i=0;
	int n=contareNelDatabase(db,2);
	while (i<n) {
		inserisciArtistiSuFile(db.artista[i]);
		i++;
	}
	remove("temp_artisti.txt");
	if (controllareSeAdmin(db))
		printf("\nArtisti salvati.");
}

void salvaGeneriSuFile(database db) {
	backupFile(file_generi, "temp_generi.txt");
	remove(file_generi);
	int i=0;
	int n=contareNelDatabase(db,3);
	while (i<n) {
		inserireGenereSuFile(db.genere[i]);
		i++;
	}
	remove("temp_generi.txt");
	if (controllareSeAdmin(db))
		printf("\nGeneri salvati.");
}

void salvaPlaylistSuFile(database db) {
	backupFile(file_playlists, "temp_playlists.txt");
	remove(file_playlists);
	int i=0;
	int n=contareNelDatabase(db,4);
	while (i<n) {
		char pubblica[6];
		if (db.playlist[i].pubblica==true) {
			strcpy(pubblica,"true");
		} else {
			strcpy(pubblica,"false");
		}
		inserisciPlaylistSuFile(db.playlist[i], pubblica);
		i++;
	}
	remove("temp_playlists.txt");
	if (controllareSeAdmin(db))
		printf("\nPlaylist salvate.");
}

void salvaUtentiSuFile(database db) {
	backupFile(file_utenti, "temp_utenti.txt");
	remove(file_utenti);
	int i=0;
	int n=contareNelDatabase(db,-1);
	while(i<n) {
		char admin[6];
		if (db.utente[i].admin==true) {
			strcpy(admin,"true");
		} else {
			strcpy(admin,"false");
		}
		inserireUtenteSuFile(db.utente[i], admin);
		i++;
	}
	remove("temp_utenti.txt");
	if (controllareSeAdmin(db))
		printf("\nUtenti salvati.");
}

//BLOCCO ASSOCIAZIONI

void salvaBranoAlbumSuFile(database db) {
	backupFile(file_BranoAlbum, "temp_BranoAlbum.txt");
	remove(file_BranoAlbum);
	int i=0;
	int n=contareNelDatabase(db,6);
	while (i<n) {
		inserisciBranoAlbumSuFile(db.branoAlbum[i]);
		i++;
	}
	remove("temp_BranoAlbum.txt");
	if (controllareSeAdmin(db))
		printf("\nAssociazioni album-brano salvate.");
}

void salvaAssociazioniArtistiSuFile(database db) {
	backupFile(file_BranoArtista, "temp_BranoArtista.txt");
	remove(file_BranoArtista);
	int i=0;
	int n=contareNelDatabase(db,5);
	while(i<n) {
		inserisciBranoArtistaSuFile(db.branoArtista[i]);
		i++;
	}
	remove("temp_BranoArtista.txt");
	if (controllareSeAdmin(db))
		printf("\nAssociazioni artista-brano salvate.");
}

void salvaBranoGenereSuFile(database db) {
	backupFile(file_BranoGenere, "temp_BranoGenere.txt");
	remove(file_BranoGenere);
	int i=0;
	int n=contareNelDatabase(db,7);
	while(i<n) {
		inserireBranoGenereSuFile(db.branoGenere[i]);
		i++;
	}
	remove("temp_BranoGenere.txt");
	if (controllareSeAdmin(db))
		printf("\nAssociazioni genere-brano salvate.");
}

void salvaPlaylistBranoSuFile(database db) {
	backupFile(file_PlaylistBrano, "temp_PlaylistBrano.txt");
	remove(file_PlaylistBrano);
	int i=0;
	int n=contareNelDatabase(db,8);
	while(i<n) {
		inserisciPlaylistBranoSuFile(db.playlistBrano[i]);
		i++;
	}
	remove("temp_PlaylistBrano.txt");
	if (controllareSeAdmin(db))
		printf("\nAssociazioni playlist-brano salvate.");
}
