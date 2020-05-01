/*
 * Ampere 0.1 rev. 501 - 27.04.2020
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

typedef struct database_locale {
	struct brani brano;
	struct artisti artista;
	struct albums album;
	struct generi genere;
	struct playlists playlist;
	struct utenti utente;
} db;

// Struttura per mantenere in memoria la Libreria Musicale di Ampere
typedef struct libreriaMusicale {
	int id;
	char titolo[MAX_CHAR];
	char artista[MAX_CHAR];
	char feat[MAX_CHAR];
	char produttore[MAX_CHAR];
	char scrittore[MAX_CHAR];
	char album[MAX_CHAR];
	char durata[MAX_CHAR];
	int anno;
	int lingua;
	int ascolti;
	float gradimento;
} database;

// Database struct globale per evitare inutili accessi al database file-based
database* brani;

/**
 * Creazione del database
 */
void creaDatabase();

/**
 * Carica il database file-based in memoria riempiendo, dunque, lo struct globale libreriaMusicale
 * @return database* brani riempito
 */
database* ottieniDatabase();

/**
 * Salva le modifiche effettuate allo struct in memoria nel database file-based,
 * effettuando il backup e la riscrittura del database
 */
void aggiornaDatabase();

#endif /* GESTORE_DATABASE_H_ */
