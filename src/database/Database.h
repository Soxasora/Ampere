/*
 * Ampere 0.1 rev. 2420 - 08.05.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef GESTORE_DATABASE_H_
#define GESTORE_DATABASE_H_
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
 * artistaBrano: Struttura 'associazioneArtisti' di supporto
 * album: Struttura 'albums'
 * albumBrano: Struttura 'collezione' di supporto
 * genere: Struttura 'generi'
 * branoGenere: Struttura 'tipoBrano' di supporto
 * playlist: Struttura 'playlists'
 * playlistBrano: Struttura 'raccolta' di supporto
 * utente: Struttura 'utenti'
 * utente_connesso: Identificativo dell'utente che sta usando il database
 */
typedef struct database_locale {
	struct brani* brano;
	struct artisti* artista;
		struct associazioneArtisti* artistaBrano;
	struct albums* album;
		struct collezione* albumBrano;
	struct generi* genere;
		struct tipoBrano* branoGenere;
	struct playlists* playlist;
		struct raccolta* playlistBrano;
	struct utenti* utente;
	int utente_connesso;
} database;

// Variabile GLOBALE del database TODO: Da rendere passabile
database db;

// Variabile GLOBALE che indica se il database e' stato modificato o meno
int db_modificato;

/**
 *
 */
int creaDatabaseSeNonEsiste();

/**
 *
 */
database ottieniDatabaseParziale();

/**
 *
 */
database ottieniDatabase();

/**
 *
 */
void ottieniBrani();

/**
 *
 */
void ottieniAlbums();

/**
 *
 */
void ottieniArtisti();

/**
 *
 */
void ottieniGeneri();

/**
 *
 */
void ottieniPlaylists();

/**
 *
 */
void ottieniUtenti();

/**
 *
 */
void associaArtisti();

/**
 *
 */
void associaAlbum();

/**
 *
 */
void associaGeneri();

/**
 *
 */
void associaPlaylist();

/**
 *
 */
void ottieniPreferitiDagliUtenti();

/**
 *
 */
void inizializzaDatabase(int modalita);

#endif /* GESTORE_DATABASE_H_ */
