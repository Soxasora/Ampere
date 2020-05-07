/*
 * Ampere 0.1 rev. 2223 - 06.05.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#include <stdbool.h>
#ifndef GESTORI_GESTOREPLAYLIST_H_
#define GESTORI_GESTOREPLAYLIST_H_

bool isUserPlaylist(int idPlaylist, int idUtente);
int contaPlaylistUtente(int idUtente);
int contaBraniPlaylist(int idPlaylist);
void inserisciPlaylist(int idUtente, char nome[], char descrizione[]);
void inserisciBraniPlaylist(int idPlaylist, int idBrano);
void creaPlaylistGuidato();
void inserimentoBraniPlaylistGuidato();
void inserisciPlaylistSuFile(char id[], char idUtente[], char nome[], char descrizione[]);
void inserisciRaccoltaSuFile(char idplaylist[], char idbrano[]);
void modificaPlaylist();
void modificaSingolaPlaylist(int modalita, int id);
void cancellaPlaylist();
void cancellaSingolaPlaylist(int id);
void cancellaAssociazionePlaylist(int id);
#endif /* GESTORI_GESTOREPLAYLIST_H_ */
