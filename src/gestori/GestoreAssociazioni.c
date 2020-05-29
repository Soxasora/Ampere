/*
 * Ampere 0.2 rev. 5 - 29.05.2020
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../gestori/GestoreAssociazioni.h"
#include "../gestori/GestoreFile.h"
#include "../gestori/GestoreBrani.h"
#include "../gestori/GestoreArtisti.h"
#include "../gestori/GestoreAlbum.h"
#include "../gestori/GestoreGeneri.h"
#include "../database/Albums.h"
#include "../database/Artisti.h"
#include "../database/Generi.h"
#include "../database/Brani.h"
#include "../database/Database.h"
#include "../database/DatabaseUtils.h"
#include "../sys/Utils.h"
#include "../sys/Impostazioni.h"

struct associazioneArtisti creaAssociazioneArtista(int idBrano, int idArtista) {
	struct associazioneArtisti branoArtista;
	branoArtista.idBrano = idBrano;
	branoArtista.idArtista = idArtista;
	return branoArtista;
}

database inserireAssociazioneArtista(database db, struct associazioneArtisti branoArtista) {
	db_modificato=1;
	int n = contareNelDatabase(db,5);
	db.branoArtista[n] = branoArtista;
	return db;
}

struct collezione creaAssociazioneAlbum(int idBrano, int idAlbum) {
	struct collezione branoAlbum;
	branoAlbum.idBrano = idBrano;
	branoAlbum.idAlbum = idAlbum;
	return branoAlbum;
}

database inserireAssociazioneAlbum(database db, struct collezione branoAlbum) {
	db_modificato=1;
	int n = contareNelDatabase(db,6);
	db.branoAlbum[n] = branoAlbum;
	return db;
}

struct tipoBrano creaAssociazioneGenere(int idBrano, int idGenere) {
	struct tipoBrano branoGenere;
	branoGenere.idBrano = idBrano;
	branoGenere.idGenere = idGenere;
	return branoGenere;
}

database inserireAssociazioneGenere(database db, struct tipoBrano branoGenere) {
	db_modificato=1;
	int n=contareNelDatabase(db,7);
	db.branoGenere[n] = branoGenere;
	return db;
}

struct raccolta creaAssociazionePlaylist(int idPlaylist, int idBrano) {
	struct raccolta playlistBrano;
	playlistBrano.idPlaylist = idPlaylist;
	playlistBrano.idBrano = idBrano;
	return playlistBrano;
}

database inserireAssociazionePlaylist(database db, struct raccolta playlistBrano) {
	db_modificato=1;
	int n = contareNelDatabase(db, 8);
	db.playlistBrano[n] = playlistBrano;
	return db;
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
