/*
 * UNIBA/Ampere 1.0.1
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di Informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef GESTORE_DATABASE_H_
#define GESTORE_DATABASE_H_
#include "../database/Database.h"
#include "../sys/Impostazioni.h"
#include "Album.h"
#include "Artista.h"
#include "Brano.h"
#include "Genere.h"
#include "Playlist.h"
#include "Utente.h"

/**
 * Struttura 'database' contenente
 * utenteCorrente: Identificativo dell'utente che sta usando il database
 * brano: Struttura 'brani'
 * artista: Struttura 'artisti'
 * branoArtista: Struttura 'BranoArtista' di supporto
 * album: Struttura 'albums'
 * branoAlbum: Struttura 'BranoAlbum' di supporto
 * genere: Struttura 'generi'
 * branoGenere: Struttura 'BranoGenere' di supporto
 * playlist: Struttura 'playlists'
 * playlistBrano: Struttura 'PlaylistBrano' di supporto
 * utente: Struttura 'utenti'
 * ultimoEsito: Codice di esito, se 0 allora nessun errore, altrimenti errore
 */
typedef struct database_locale {
	int utenteCorrente;
	struct Brano* brano;
	struct Artista* artista;
		struct BranoArtista* branoArtista;
	struct Album* album;
		struct BranoAlbum* branoAlbum;
	struct Genere* genere;
		struct BranoGenere* branoGenere;
	struct Playlist* playlist;
		struct PlaylistBrano* playlistBrano;
	struct Utente* utente;
	int ultimoEsito;
	bool modificato;
} database;

// Variabile GLOBALE che indica se il database e' stato modificato o meno
int db_modificato;

/**
 *	Nel caso in cui non dovessero essere presenti i file del database, automaticamente vengono creati
 *	per garantire il funzionamento di Ampere
 *	In caso di errore, ritorna esito negativo
 *	@return esito
 */
int creareDatabaseSeNonEsiste();

/**
 * -1: caricamento solo utente
 * 0: caricamento iniziale
 * 1: caricamento completo
 *
 *	Carica in memoria l'intero database presente nei file
 *	@return database carico
 */
database ottenereDatabase(int modalita, database db);

/**
 * 	@input istanza database
 *	Operazioni di caricamento in memoria della parte brani del database file-based
 *	Se non sono presenti brani, assume valore zero
 *	@return database carico di brani
 */
database ottenereBrani(database db);

/**
 * 	@input istanza database
 *	Operazioni di caricamento in memoria della parte albums del database file-based
 *	Se non sono presenti album, assume valore zero
 *	@return database carico di album
 */
database ottenereAlbums(database db);

/**
 *	@input istanza database
 *	Operazioni di caricamento in memoria della parte artisti del database file-based
 *	Se non sono presenti artisti, assume valore zero
 *	@return database carico di artisti
 */
database ottenereArtisti(database db);

/**
 *	@input istanza database
 *	Operazioni di caricamento in memoria della parte generi del database file-based
 *	Se non sono presenti generi, assume valore zero
 *	@return database carico di generi
 */
database ottenereGeneri(database db);

/**
 *	@input istanza database
 *	Operazioni di caricamento in memoria della parte playlists del database file-based
 *	Se non sono presenti playlists, assume valore zero
 *	@return database carico di playlist
 */
database ottenerePlaylists(database db);

/**
 *	@input istanza database
 *	Operazioni di caricamento in memoria della parte utenti del database file-based
 *	Se non sono presenti utenti, assume valore zero
 *	@return database carico di utenti
 */
database ottenereUtenti(database db);

/**
 *	@input istanza database
 *	Operazioni di caricamento in memoria della parte di associazione artisti del database file-based
 *	Se non sono presenti associazioni di artisti, assume valore zero
 *	@return database carico di associazioni di artisti
 */
database associareArtisti(database db);

/**
 *	@input istanza database
 *	Operazioni di caricamento in memoria della parte di associazione album del database file-based
 *	Se non sono presenti associazioni di album, assume valore zero
 *	@return database carico di associazioni di album
 */
database associareAlbums(database db);

/**
 *	@input istanza database
 *	Operazioni di caricamento in memoria della parte di associazione generi del database file-based
 *	Se non sono presenti associazioni di generi, assume valore zero
 *	@return database carico di associazioni di generi
 */
database associareGeneri(database db);

/**
 *	@input istanza database
 *	Operazioni di caricamento in memoria della parte di associazione playlist del database file-based
 *	Se non sono presenti associazioni di playlist, assume valore zero
 *	@return database carico di associazioni di playlist
 */
database associarePlaylists(database db);

/**
 *	@input istanza database, modalita' di esecuzione
 *	In base alla modalita' di esecuzione data in input, inizializza la parte di database coinvolta
 *	in modo da evitare corruzioni e comportamenti inaspettati nel caso in cui la parte di database coinvolta
 *	non abbia effettivamente alcun dato da poter caricare, ad esempio quando il file di esso e' vuoto.
 *	@return database con parte inizializzata
 */
database inizializzareDatabase(database db, int modalita);

database liberareDatabase(database db);

#endif /* GESTORE_DATABASE_H_ */
