/*
 * Ampere 0.1 rev. 4075 - 19.05.2020
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef GESTORI_GESTOREASSOCIAZIONI_H_
#define GESTORI_GESTOREASSOCIAZIONI_H_
#include "../database/Database.h"

/**
 * 	@input istanza database, numero intero identificativo brano, numero intero identificativo artista
 *	Funzione logica per la creazione di un record "associazioneArtisti", prende le informazioni date in input
 *	e crea un record con esse. Si avvale del database in input per ottenere l'ultimo identificativo
 *	@output record associazioneArtisti compilato
 */
struct associazioneArtisti creaAssociazioneArtista(int idBrano, int idArtista);

/**
 *	@input istanza database, record associazioneArtisti branoArtista
 *	Ottiene in input il record branoArtista gia' compilato con creaAssociazioneArtista e gli assegna l'ultima posizione
 *	@output database modificato
 */
database inserireAssociazioneArtista(database db, struct associazioneArtisti branoArtista);

/**
 * 	@input istanza database, numero intero identificativo brano, numero intero identificativo album
 *	Funzione logica per la creazione di un record "collezione", prende le informazioni date in input
 *	e crea un record con esse. Si avvale del database in input per ottenere l'ultimo identificativo
 *	@output record collezione compilato
 */
struct collezione creaAssociazioneAlbum(int idBrano, int idAlbum);

/**
 *	@input istanza database, record collezione branoAlbum
 *	Ottiene in input il record branoAlbum gia' compilato con creaAssociazioneAlbum e gli assegna l'ultima posizione
 *	@output database modificato
 */
database inserireAssociazioneAlbum(database db, struct collezione branoAlbum);

/**
 * 	@input istanza database, numero intero identificativo brano, numero intero identificativo genere
 *	Funzione logica per la creazione di un record "tipoBrano", prende le informazioni date in input
 *	e crea un record con esse. Si avvale del database in input per ottenere l'ultimo identificativo
 *	@output record tipoBrano compilato
 */
struct tipoBrano creaAssociazioneGenere(int idBrano, int idGenere);

/**
 *	@input istanza database, record tipoBrano branoGenere
 *	Ottiene in input il record branoGenere gia' compilato con inserireAssociazioneGenere e gli assegna l'ultima posizione
 *	@output database modificato
 */
database inserireAssociazioneGenere(database db, struct tipoBrano branoGenere);

/**
 * 	@input istanza database, numero intero identificativo playlist, numero intero identificativo brano
 *	Funzione logica per la creazione di un record "raccolta", prende le informazioni date in input
 *	e crea un record con esse. Si avvale del database in input per ottenere l'ultimo identificativo
 *	@output record raccolta compilato
 */
struct raccolta creaAssociazionePlaylist(int idPlaylist, int idBrano);

/**
 *	@input istanza database, record raccolta playlistBrano
 *	Ottiene in input il record playlistBrano gia' compilato con inserireAssociazionePlaylist e gli assegna l'ultima posizione
 *	@output database modificato
 */
database inserireAssociazionePlaylist(database db, struct raccolta playlistBrano);

#endif /* GESTORI_GESTOREASSOCIAZIONI_H_ */
