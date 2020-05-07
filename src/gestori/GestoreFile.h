/*
 * Ampere 0.1 rev. 2377 - 07.05.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef GESTORI_GESTOREFILE_H_
#define GESTORI_GESTOREFILE_H_

void cancellaDatabaseFile();
void salvaModificheSuFile();
void salvaBraniSuFile();
void salvaAlbumSuFile();
void salvaArtistiSuFile();
void salvaGeneriSuFile();
void salvaPlaylistSuFile();
void salvaUtentiSuFile();
// Associazioni
void salvaCollezioneSuFile();
void salvaAssociazioniArtistiSuFile();
void salvaTipiBraniSuFile();
void salvaRaccoltaSuFile();

#endif /* GESTORI_GESTOREFILE_H_ */
