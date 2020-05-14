/*
 * Ampere 0.1 rev. 4074 - 15.05.2020
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef GESTORE_DATABASE_H_
#define GESTORE_DATABASE_H_
#include "../database/Database.h"
#include "../sys/Impostazioni.h"
#include "Brani.h"
#include "Artisti.h"
#include "Albums.h"
#include "Generi.h"
#include "Playlists.h"
#include "Utenti.h"

/**
 * Struttura 'database' contenente
 * brano: Struttura 'brani'
 * artista: Struttura 'artisti'
 * branoArtista: Struttura 'associazioneArtisti' di supporto
 * album: Struttura 'albums'
 * branoAlbum: Struttura 'collezione' di supporto
 * genere: Struttura 'generi'
 * branoGenere: Struttura 'tipoBrano' di supporto
 * playlist: Struttura 'playlists'
 * playlistBrano: Struttura 'raccolta' di supporto
 * utente: Struttura 'utenti'
 * utenteCorrente: Identificativo dell'utente che sta usando il database
 */
typedef struct database_locale {
	struct brani* brano;
	struct artisti* artista;
		struct associazioneArtisti* branoArtista;
	struct albums* album;
		struct collezione* branoAlbum;
	struct generi* genere;
		struct tipoBrano* branoGenere;
	struct playlists* playlist;
		struct raccolta* playlistBrano;
	struct utenti* utente;
	int utenteCorrente;
} database;

// Variabile GLOBALE che indica se il database e' stato modificato o meno
int db_modificato;

/**
 *
 */
int creaDatabaseSeNonEsiste();

/**
 *
 */
database ottieniDatabaseParziale(database db);

/**
 *
 */
database ottieniDatabase(database db);

/**
 *
 */
database ottieniBrani(database db);

/**
 *
 */
database ottieniAlbums(database db);

/**
 *
 */
database ottieniArtisti(database db);

/**
 *
 */
database ottieniGeneri(database db);

/**
 *
 */
database ottieniPlaylists(database db);

/**
 *
 */
database ottieniUtenti(database db);

/**
 *
 */
database associaArtisti(database db);

/**
 *
 */
database associaAlbum(database db);

/**
 *
 */
database associaGeneri(database db);

/**
 *
 */
database associaPlaylist(database db);

/**
 *
 */
database inizializzaDatabase(database db, int modalita);

#endif /* GESTORE_DATABASE_H_ */
