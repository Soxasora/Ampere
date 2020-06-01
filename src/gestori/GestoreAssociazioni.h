/*
 * Ampere 0.2 rev. 12 -01.06.2020
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
 *	Funzione logica per la creazione di un record "BranoArtista", prende le informazioni date in input
 *	e crea un record con esse. Si avvale del database in input per ottenere l'ultimo identificativo
 *	@output record BranoArtista compilato
 */
struct BranoArtista creaAssociazioneArtista(int idBrano, int idArtista);

/**
 *	@input istanza database, record BranoArtista branoArtista
 *	Ottiene in input il record branoArtista gia' compilato con creaAssociazioneArtista e gli assegna l'ultima posizione
 *	@output database modificato
 */
database inserireAssociazioneArtista(database db, struct BranoArtista branoArtista);

/**
 * 	@input istanza database, numero intero identificativo brano, numero intero identificativo album
 *	Funzione logica per la creazione di un record "BranoAlbum", prende le informazioni date in input
 *	e crea un record con esse. Si avvale del database in input per ottenere l'ultimo identificativo
 *	@output record BranoAlbum compilato
 */
struct BranoAlbum creaAssociazioneAlbum(int idBrano, int idAlbum);

/**
 *	@input istanza database, record BranoAlbum branoAlbum
 *	Ottiene in input il record branoAlbum gia' compilato con creaAssociazioneAlbum e gli assegna l'ultima posizione
 *	@output database modificato
 */
database inserireAssociazioneAlbum(database db, struct BranoAlbum branoAlbum);

/**
 * 	@input istanza database, numero intero identificativo brano, numero intero identificativo genere
 *	Funzione logica per la creazione di un record "BranoGenere", prende le informazioni date in input
 *	e crea un record con esse. Si avvale del database in input per ottenere l'ultimo identificativo
 *	@output record BranoGenere compilato
 */
struct BranoGenere creaAssociazioneGenere(int idBrano, int idGenere);

/**
 *	@input istanza database, record BranoGenere branoGenere
 *	Ottiene in input il record branoGenere gia' compilato con inserireAssociazioneGenere e gli assegna l'ultima posizione
 *	@output database modificato
 */
database inserireAssociazioneGenere(database db, struct BranoGenere branoGenere);

/**
 * 	@input istanza database, numero intero identificativo playlist, numero intero identificativo brano
 *	Funzione logica per la creazione di un record "PlaylistBrano", prende le informazioni date in input
 *	e crea un record con esse. Si avvale del database in input per ottenere l'ultimo identificativo
 *	@output record PlaylistBrano compilato
 */
struct PlaylistBrano creaAssociazionePlaylist(int idPlaylist, int idBrano);

/**
 *	@input istanza database, record PlaylistBrano playlistBrano
 *	Ottiene in input il record playlistBrano gia' compilato con inserireAssociazionePlaylist e gli assegna l'ultima posizione
 *	@output database modificato
 */
database inserireAssociazionePlaylist(database db, struct PlaylistBrano playlistBrano);

/**
 *	@input struct BranoAlbum branoAlbum
 *	Scrive sul file "file_BranoAlbum", le informazioni date in input, separate con separatore pipe "|"
 *	@output FILE modificato
 */
void inserisciBranoAlbumSuFile(struct BranoAlbum branoAlbum);

/**
 *	@input struct BranoArtista branoArtista
 *	Scrive sul file "file_BranoArtista", le informazioni date in input, separate con separatore pipe "|"
 *	@output FILE modificato
 */
void inserisciBranoArtistaSuFile(struct BranoArtista branoArtista);

/**
 *	@input struct BranoGenere branoGenere
 *	Scrive sul file "file_BranoGenere", le informazioni date in input, separate con separatore pipe "|"
 *	@output FILE modificato
 */
void inserireBranoGenereSuFile(struct BranoGenere branoGenere);

/**
 *	@input struct PlaylistBrano playlistBrano
 *	Scrive sul file "file_PlaylistBrano", le informazioni date in input, separate con separatore pipe "|"
 *	@output FILE modificato
 */
void inserisciPlaylistBranoSuFile(struct PlaylistBrano playlistBrano);


database cancellaAssociazioniBrano(database db, int id);
database cancellaAssociazioniArtisti(database db, int id);
database cancellaAssociazioniAlbum(database db, int idBrano);
database cancellaAssociazioniGenere(database db, int idBrano);

#endif /* GESTORI_GESTOREASSOCIAZIONI_H_ */
