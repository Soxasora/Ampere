/*
 * UNIBA/Ampere 1.3
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di Informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#include <stdbool.h>
#include "../sys/Impostazioni.h"
#ifndef DATABASE_PLAYLISTS_H_
#define DATABASE_PLAYLISTS_H_

/**
 * Struttura 'playlists' contenente
 * id: Identificativo della playlist
 * idUtente: Identificativo dell'autore della playlist
 * nome: Nome della playlist
 * descrizione: Descrizione della playlist
 * pubblica: Privacy booleana della playlist
 */
struct Playlist {
	int id;
	int idUtente;
	char nome[MAX_MEDIO];
	char descrizione[MAX_GRANDE];
	bool pubblica;
};

/**
 * Serve a collegare i brani alle playlist
 * Struttura 'PlaylistBrano' contenente
 * idPlaylist: Identificativo della playlist
 * idBrano: Identificativo del brano
 */
struct PlaylistBrano {
	int idPlaylist;
	int idBrano;
};

#endif /* DATABASE_PLAYLISTS_H_ */
