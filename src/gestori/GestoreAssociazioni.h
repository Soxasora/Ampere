/*
 * Ampere 0.1 rev. 4074 - 15.05.2020
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef GESTORI_GESTOREASSOCIAZIONI_H_
#define GESTORI_GESTOREASSOCIAZIONI_H_
#include "../database/Database.h"

struct associazioneArtisti creaAssociazioneArtista(int idBrano, int idArtista);
database inserireAssociazioneArtista(database db, struct associazioneArtisti branoArtista);
struct collezione creaAssociazioneAlbum(int idBrano, int idAlbum);
database inserireAssociazioneAlbum(database db, struct collezione branoAlbum);
struct tipoBrano creaAssociazioneGenere(int idBrano, int idGenere);
database inserireAssociazioneGenere(database db, struct tipoBrano branoGenere);
struct raccolta creaAssociazionePlaylist(int idPlaylist, int idBrano);
database inserireAssociazionePlaylist(database db, struct raccolta playlistBrano);

#endif /* GESTORI_GESTOREASSOCIAZIONI_H_ */
