/*
 * Ampere 0.1 rev. 2420 - 08.05.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
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
struct playlists {
	int id;
	int idUtente;
	char nome[MAX_CHAR];
	char descrizione[MAX_CHAR];
	bool pubblica;
};

/**
 * Serve a collegare i brani alle playlist
 * Struttura 'raccolta' contenente
 * idPlaylist: Identificativo della playlist
 * idBrano: Identificativo del brano
 */
struct raccolta {
	int idPlaylist;
	int idBrano;
};

#endif /* DATABASE_PLAYLISTS_H_ */
