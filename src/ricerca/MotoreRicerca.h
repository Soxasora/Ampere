/*
 * Ampere 0.1 rev. 4074 - 15.05.2020
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef SRC_RICERCA_MOTORERICERCA_H_
#define SRC_RICERCA_MOTORERICERCA_H_
#include "../database/Database.h"

void mostraSingoloBrano(database db, int id);
void mostraTuttiBrani(database db);
void mostraSingoloAlbum(database db, int id);
void mostraTuttiAlbum(database db);
void mostraSingoloArtista(database db, int id);
void mostraTuttiArtisti(database db);
void mostraSingoloGenere(database db, int id);
void mostraTuttiGeneri(database db);
void mostraSingolaPlaylist(database db, int modalita, int id);
void mostraPlaylistUtente(database db, int modalita, int idUtente);
void mostraTuttePlaylist(database db, int modalita);
void mostraTuttePlaylistPubbliche(database db, int modalita);
void mostraSingoloUtente(database db, int modalita, int id);
void mostraTuttiUtenti(database db);
int mostraInfo(database db, int modalita);
int mostraBrani(database db, int modalita);
int mostraBraniArtista(database db);
int mostraBraniAlbum(database db);
int mostraBraniGenere(database db);
int mostraBraniPlaylist(database db);
int mostraPlaylistUtenteGuidato(database db);

#endif /* SRC_RICERCA_MOTORERICERCA_H_ */
