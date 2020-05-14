/*
 * Ampere 0.1 rev. 4074 - 15.05.2020
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */


#ifndef GESTORI_GESTOREPLAYLIST_H_
#define GESTORI_GESTOREPLAYLIST_H_
#include <stdbool.h>
#include "../database/Database.h"

bool isUserPlaylist(database db, int idPlaylist, int idUtente);
bool isPublicPlaylist(database db, int idPlaylist);
int contaPlaylistUtente(database db, int idUtente);
int contaBraniPlaylist(database db, int idPlaylist);
struct playlists creaPlaylist(database db, int idUtente, char nome[], char descrizione[], bool pubblica);
database inserirePlaylist(database db, struct playlists playlist);
database creaPlaylistGuidato(database db);
database inserimentoBraniPlaylistGuidato(database db);
void inserisciPlaylistSuFile(char id[], char idUtente[], char nome[], char descrizione[], char pubblica[]);
void inserisciRaccoltaSuFile(char idplaylist[], char idbrano[]);
int controlloEsistenzaPlaylist(database db, char playlist[]);
database modificaPlaylist(database db);
database modificaSingolaPlaylist(database db, int modalita, int id);
database cancellaPlaylist(database db);
database cancellaSingolaPlaylist(database db, int id);
database cancellaAssociazionePlaylist(database db, int id);
#endif /* GESTORI_GESTOREPLAYLIST_H_ */
