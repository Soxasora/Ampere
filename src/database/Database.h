/*
 * Ampere 0.2 rev. 5 - 29.05.2020
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
 * utenteCorrente: Identificativo dell'utente che sta usando il database
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
 * ultimoEsito: Codice di esito, se 0 allora nessun errore, altrimenti errore
 */
typedef struct database_locale {
	int utenteCorrente;
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
	int ultimoEsito;
} database;

// Variabile GLOBALE che indica se il database e' stato modificato o meno
int db_modificato;

/**
 *	Nel caso in cui non dovessero essere presenti i file del database, automaticamente vengono creati
 *	per garantire il funzionamento di Ampere
 *	In caso di errore, ritorna esito negativo
 *	@return esito
 */
int creaDatabaseSeNonEsiste();

/**
 * -1: caricamento solo utente
 * 0: caricamento iniziale
 * 1: caricamento completo
 *
 *	Carica in memoria l'intero database presente nei file
 *	@return database carico
 */
database ottieniDatabase(int modalita, database db);

/**
 * 	@input istanza database
 *	Operazioni di caricamento in memoria della parte brani del database file-based
 *	Se non sono presenti brani, assume valore zero
 *	@return database carico di brani
 */
database ottieniBrani(database db);

/**
 * 	@input istanza database
 *	Operazioni di caricamento in memoria della parte albums del database file-based
 *	Se non sono presenti album, assume valore zero
 *	@return database carico di album
 */
database ottieniAlbums(database db);

/**
 *	@input istanza database
 *	Operazioni di caricamento in memoria della parte artisti del database file-based
 *	Se non sono presenti artisti, assume valore zero
 *	@return database carico di artisti
 */
database ottieniArtisti(database db);

/**
 *	@input istanza database
 *	Operazioni di caricamento in memoria della parte generi del database file-based
 *	Se non sono presenti generi, assume valore zero
 *	@return database carico di generi
 */
database ottieniGeneri(database db);

/**
 *	@input istanza database
 *	Operazioni di caricamento in memoria della parte playlists del database file-based
 *	Se non sono presenti playlists, assume valore zero
 *	@return database carico di playlist
 */
database ottieniPlaylists(database db);

/**
 *	@input istanza database
 *	Operazioni di caricamento in memoria della parte utenti del database file-based
 *	Se non sono presenti utenti, assume valore zero
 *	@return database carico di utenti
 */
database ottieniUtenti(database db);

/**
 *	@input istanza database
 *	Operazioni di caricamento in memoria della parte di associazione artisti del database file-based
 *	Se non sono presenti associazioni di artisti, assume valore zero
 *	@return database carico di associazioni di artisti
 */
database associaArtisti(database db);

/**
 *	@input istanza database
 *	Operazioni di caricamento in memoria della parte di associazione album del database file-based
 *	Se non sono presenti associazioni di album, assume valore zero
 *	@return database carico di associazioni di album
 */
database associaAlbum(database db);

/**
 *	@input istanza database
 *	Operazioni di caricamento in memoria della parte di associazione generi del database file-based
 *	Se non sono presenti associazioni di generi, assume valore zero
 *	@return database carico di associazioni di generi
 */
database associaGeneri(database db);

/**
 *	@input istanza database
 *	Operazioni di caricamento in memoria della parte di associazione playlist del database file-based
 *	Se non sono presenti associazioni di playlist, assume valore zero
 *	@return database carico di associazioni di playlist
 */
database associaPlaylist(database db);

/**
 *	@input istanza database, modalita' di esecuzione
 *	In base alla modalita' di esecuzione data in input, inizializza la parte di database coinvolta
 *	in modo da evitare corruzioni e comportamenti inaspettati nel caso in cui la parte di database coinvolta
 *	non abbia effettivamente alcun dato da poter caricare, ad esempio quando il file di esso e' vuoto.
 *	@return database con parte inizializzata
 */
database inizializzaDatabase(database db, int modalita);

#endif /* GESTORE_DATABASE_H_ */
