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
	int n = contaNelDatabase(db,5);
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
	int n = contaNelDatabase(db,6);
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
	int n=contaNelDatabase(db,7);
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
	int n = contaNelDatabase(db, 8);
	db.playlistBrano[n] = playlistBrano;
	return db;
}
