/*
 * Ampere 0.0.1 rev. 1000 - 02.05.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/XX/blob/master/LICENSE
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
		struct preferiti* utenteBrano;
} database;

database db;

int db_modificato;

/**
 * TODO spiegazione di questo blocco
 */
database ottieniDatabase();
void ottieniBrani();
void ottieniAlbums();
void ottieniArtisti();
void ottieniGeneri();
void ottieniPlaylists();
void ottieniUtenti();
void associaArtisti();
void associaAlbum();
void associaGeneri();
void associaPlaylist();
void ottieniPreferitiDagliUtenti();

#endif /* GESTORE_DATABASE_H_ */
