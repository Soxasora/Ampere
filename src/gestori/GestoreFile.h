/*
 * Ampere 0.1 rev. 4074 - 15.05.2020
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef GESTORI_GESTOREFILE_H_
#define GESTORI_GESTOREFILE_H_
#include "../database/Database.h"

void cancellaDatabaseFile();
void salvaModificheSuFile(database db);
void salvaBraniSuFile(database db);
void salvaAlbumSuFile(database db);
void salvaArtistiSuFile(database db);
void salvaGeneriSuFile(database db);
void salvaPlaylistSuFile(database db);
void salvaUtentiSuFile(database db);
// Associazioni
void salvaCollezioneSuFile(database db);
void salvaAssociazioniArtistiSuFile(database db);
void salvaTipiBraniSuFile(database db);
void salvaRaccoltaSuFile(database db);

#endif /* GESTORI_GESTOREFILE_H_ */
