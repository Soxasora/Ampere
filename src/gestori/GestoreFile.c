/*
 * UNIBA/Ampere 1.2
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di Informatica, a.a. 2019/20.
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
#include "../sys/Messaggi.h"
#include "../sys/Utils.h"
#include "../sys/Impostazioni.h"

void cancellareDatabaseFile() {
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

void salvareModificheSuFile(database *db) {
	salvareBraniSuFile(db);
	salvareAlbumSuFile(db);
	salvareArtistiSuFile(db);
	salvareGeneriSuFile(db);
	salvarePlaylistSuFile(db);
	salvareUtentiSuFile(db);
	// Blocco associazioni
	salvareBranoAlbumSuFile(db);
	salvareAssociazioniArtistiSuFile(db);
	salvareBranoGenereSuFile(db);
	salvarePlaylistBranoSuFile(db);
	if (controllareSeAdmin(db))
		printf("\nSalvate tutte le modifiche effettuate al void su file.");
}

void salvareBraniSuFile(database *db) {
	backupFile(file_brani, "temp_brani.txt");
	remove(file_brani);
	int i=0;
	int n=contareNelDatabase(db,0);
	while (i<n) {
		inserireBranoSuFile(db->brano[i]);
		i++;
	}
	remove("temp_brani.txt");
	if (controllareSeAdmin(db))
		successo(201);
}

void salvareAlbumSuFile(database *db) {
	backupFile(file_albums, "temp_albums.txt");
	remove(file_albums);
	int i=0;
	int n=contareNelDatabase(db,1);
	while (i<n) {
		inserireAlbumSuFile(db->album[i]);
		i++;
	}
	remove("temp_albums.txt");
	if (controllareSeAdmin(db))
		successo(202);
}

void salvareArtistiSuFile(database *db) {
	backupFile(file_artisti, "temp_artisti.txt");
	remove(file_artisti);
	int i=0;
	int n=contareNelDatabase(db,2);
	while (i<n) {
		inserireArtistiSuFile(db->artista[i]);
		i++;
	}
	remove("temp_artisti.txt");
	if (controllareSeAdmin(db))
		successo(203);
}

void salvareGeneriSuFile(database *db) {
	backupFile(file_generi, "temp_generi.txt");
	remove(file_generi);
	int i=0;
	int n=contareNelDatabase(db,3);
	while (i<n) {
		inserireGenereSuFile(db->genere[i]);
		i++;
	}
	remove("temp_generi.txt");
	if (controllareSeAdmin(db))
		successo(204);
}

void salvarePlaylistSuFile(database *db) {
	backupFile(file_playlists, "temp_playlists.txt");
	remove(file_playlists);
	int i=0;
	int n=contareNelDatabase(db,4);
	while (i<n) {
		char pubblica[6];
		if (db->playlist[i].pubblica==true) {
			strcpy(pubblica,"true");
		} else {
			strcpy(pubblica,"false");
		}
		inserirePlaylistSuFile(db->playlist[i], pubblica);
		i++;
	}
	remove("temp_playlists.txt");
	if (controllareSeAdmin(db))
		successo(205);
}

void salvareUtentiSuFile(database *db) {
	backupFile(file_utenti, "temp_utenti.txt");
	remove(file_utenti);
	int i=0;
	int n=contareNelDatabase(db,-1);
	while(i<n) {
		char admin[6];
		if (db->utente[i].admin==true) {
			strcpy(admin,"true");
		} else {
			strcpy(admin,"false");
		}
		inserireUtenteSuFile(db->utente[i], admin);
		i++;
	}
	remove("temp_utenti.txt");
	if (controllareSeAdmin(db))
		successo(200);
}

//BLOCCO ASSOCIAZIONI

void salvareBranoAlbumSuFile(database *db) {
	backupFile(file_BranoAlbum, "temp_BranoAlbum.txt");
	remove(file_BranoAlbum);
	int i=0;
	int n=contareNelDatabase(db,6);
	while (i<n) {
		inserireBranoAlbumSuFile(db->branoAlbum[i]);
		i++;
	}
	remove("temp_BranoAlbum.txt");
	if (controllareSeAdmin(db))
		printf("\nAssociazioni album-brano salvate.");
}

void salvareAssociazioniArtistiSuFile(database *db) {
	backupFile(file_BranoArtista, "temp_BranoArtista.txt");
	remove(file_BranoArtista);
	int i=0;
	int n=contareNelDatabase(db,5);
	while(i<n) {
		inserireBranoArtistaSuFile(db->branoArtista[i]);
		i++;
	}
	remove("temp_BranoArtista.txt");
	if (controllareSeAdmin(db))
		printf("\nAssociazioni artista-brano salvate.");
}

void salvareBranoGenereSuFile(database *db) {
	backupFile(file_BranoGenere, "temp_BranoGenere.txt");
	remove(file_BranoGenere);
	int i=0;
	int n=contareNelDatabase(db,7);
	while(i<n) {
		inserireBranoGenereSuFile(db->branoGenere[i]);
		i++;
	}
	remove("temp_BranoGenere.txt");
	if (controllareSeAdmin(db))
		printf("\nAssociazioni genere-brano salvate.");
}

void salvarePlaylistBranoSuFile(database *db) {
	backupFile(file_PlaylistBrano, "temp_PlaylistBrano.txt");
	remove(file_PlaylistBrano);
	int i=0;
	int n=contareNelDatabase(db,8);
	while(i<n) {
		inserirePlaylistBranoSuFile(db->playlistBrano[i]);
		i++;
	}
	remove("temp_PlaylistBrano.txt");
	if (controllareSeAdmin(db))
		printf("\nAssociazioni playlist-brano salvate.");
}
