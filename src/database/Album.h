/*
 * UNIBA/Ampere 1.0.1
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di Informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef DATABASE_ALBUM_H_
#define DATABASE_ALBUM_H_
#include "../sys/Impostazioni.h"

/**
 * Struttura 'album' contenente
 * id: Identificativo dell'album
 * titolo: Titolo dell'album
 * anno: Anno di uscita dell'album
 */
struct Album {
	int id;
	char titolo[MAX_MEDIO];
	int anno;
};

/**
 * E' una struttura che serve a collegare i brani agli album
 * Struttura 'BranoAlbum' contenente
 * idAlbum: Identificativo dell'album
 * idBrano: Identificativo del brano
 */
struct BranoAlbum {
	int idAlbum;
	int idBrano;
};

#endif /* DATABASE_ALBUM_H_ */
