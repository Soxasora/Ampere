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

#include "../database/Album.h"
#include "../database/Artista.h"
#include "../database/Brano.h"
#include "../gestori/GestoreFile.h"
#include "../gestori/GestoreBrani.h"
#include "../gestori/GestoreArtisti.h"
#include "../gestori/GestoreAlbum.h"
#include "../gestori/GestoreGeneri.h"
#include "../database/Database.h"
#include "../database/DatabaseUtils.h"
#include "../database/Genere.h"
#include "../sys/Utils.h"
#include "../sys/Impostazioni.h"

struct BranoArtista creaAssociazioneArtista(int idBrano, int idArtista) {
	struct BranoArtista branoArtista;
	branoArtista.idBrano = idBrano;
	branoArtista.idArtista = idArtista;
	return branoArtista;
}

database inserireAssociazioneArtista(database db, struct BranoArtista branoArtista) {
	db_modificato=1;
	int n = contareNelDatabase(db,5);
	db.branoArtista[n] = branoArtista;
	return db;
}

struct BranoAlbum creaAssociazioneAlbum(int idBrano, int idAlbum) {
	struct BranoAlbum branoAlbum;
	branoAlbum.idBrano = idBrano;
	branoAlbum.idAlbum = idAlbum;
	return branoAlbum;
}

database inserireAssociazioneAlbum(database db, struct BranoAlbum branoAlbum) {
	db_modificato=1;
	int n = contareNelDatabase(db,6);
	db.branoAlbum[n] = branoAlbum;
	return db;
}

struct BranoGenere creaAssociazioneGenere(int idBrano, int idGenere) {
	struct BranoGenere branoGenere;
	branoGenere.idBrano = idBrano;
	branoGenere.idGenere = idGenere;
	return branoGenere;
}

database inserireAssociazioneGenere(database db, struct BranoGenere branoGenere) {
	db_modificato=1;
	int n=contareNelDatabase(db,7);
	db.branoGenere[n] = branoGenere;
	return db;
}

struct PlaylistBrano creaAssociazionePlaylist(int idPlaylist, int idBrano) {
	struct PlaylistBrano playlistBrano;
	playlistBrano.idPlaylist = idPlaylist;
	playlistBrano.idBrano = idBrano;
	return playlistBrano;
}

database inserireAssociazionePlaylist(database db, struct PlaylistBrano playlistBrano) {
	db_modificato=1;
	int n = contareNelDatabase(db, 8);
	db.playlistBrano[n] = playlistBrano;
	return db;
}

void inserisciBranoAlbumSuFile(struct BranoAlbum branoAlbum) {
	FILE* fp=fopen(file_BranoAlbum, "a");
	if (controllaSeFileVuoto(file_BranoAlbum)==1) {
		fprintf(fp, "%d|%d", branoAlbum.idAlbum, branoAlbum.idBrano);
	} else {
		fprintf(fp, "\n%d|%d", branoAlbum.idAlbum, branoAlbum.idBrano);
	}
	fclose(fp);
}


void inserisciBranoArtistaSuFile(struct BranoArtista branoArtista) {
	FILE* fp=fopen(file_BranoArtista, "a");
	if (controllaSeFileVuoto(file_BranoArtista)==1) {
		fprintf(fp, "%d|%d", branoArtista.idBrano, branoArtista.idArtista);
	} else {
		fprintf(fp, "\n%d|%d", branoArtista.idBrano, branoArtista.idArtista);
	}
	fclose(fp);
}

void inserireBranoGenereSuFile(struct BranoGenere branoGenere) {
	FILE* fp=fopen(file_BranoGenere, "a");
	if (controllaSeFileVuoto(file_BranoGenere)==1) {
		fprintf(fp, "%d|%d", branoGenere.idBrano, branoGenere.idGenere);
	} else {
		fprintf(fp, "\n%d|%d", branoGenere.idBrano, branoGenere.idGenere);
	}
	fclose(fp);
}

void inserisciPlaylistBranoSuFile(struct PlaylistBrano playlistBrano) {
	FILE* fp=fopen(file_PlaylistBrano,"a");
	if (controllaSeFileVuoto(file_PlaylistBrano)==1) {
		fprintf(fp, "%d|%d", playlistBrano.idPlaylist, playlistBrano.idBrano);
	} else {
		fprintf(fp, "\n%d|%d", playlistBrano.idPlaylist, playlistBrano.idBrano);
	}
	fclose(fp);
}

database cancellaAssociazioniBrano(database db, int id) {
	//Cancella Associazioni
	db = cancellaAssociazioniArtisti(db, id);

	db = cancellaAssociazioniAlbum(db, id);

	db = cancellaAssociazioniGenere(db, id);
	int n=0, i=0;
	n = contareNelDatabase(db,8);
	i = ottenerePosDaID(db, 8, id);
	while (i<n-1) {
		db.playlistBrano[i] = db.playlistBrano[i+1];
		i++;
	}
	db.playlistBrano[n-1].idPlaylist = 0;
	db.playlistBrano[n-1].idBrano = 0;
	return db;
}

database cancellaAssociazioniArtisti(database db, int id) {
	int n = contareNelDatabase(db,5);
	int i = ottenerePosDaID(db, 5, id);

	while (i<n-1) {
		db.branoArtista[i] = db.branoArtista[i+1];
		i++;
	}
	db.branoArtista[n-1].idBrano = 0;
	db.branoArtista[n-1].idArtista = 0;
	return db;
}

database cancellaAssociazioniAlbum(database db, int idBrano) {
	int n = contareNelDatabase(db,6);
	int i = ottenerePosDaID(db, 6, idBrano);
	while (i<n-1) {
		db.branoAlbum[i] = db.branoAlbum[i+1];
		i++;
	}
	db.branoAlbum[n-1].idBrano = 0;
	db.branoAlbum[n-1].idAlbum = 0;
	return db;
}

database cancellaAssociazioniGenere(database db, int idBrano) {
	int n = contareNelDatabase(db,7);
	int i = ottenerePosDaID(db, 7, idBrano);
	while (i<n-1) {
		db.branoGenere[i] = db.branoGenere[i+1];
		i++;
	}
	db.branoGenere[n-1].idBrano = 0;
	db.branoGenere[n-1].idGenere = 0;
	return db;
}
