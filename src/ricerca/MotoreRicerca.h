/*
 * Ampere 0.1 rev. 2223 - 06.05.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef SRC_RICERCA_MOTORERICERCA_H_
#define SRC_RICERCA_MOTORERICERCA_H_

void mostraSingoloBrano(int id);
void mostraTuttiBrani();
void mostraSingoloAlbum(int id);
void mostraTuttiAlbum();
void mostraSingoloArtista(int id);
void mostraTuttiArtisti();
void mostraSingoloGenere(int id);
void mostraTuttiGeneri();
void mostraSingolaPlaylist(int modalita, int id);
void mostraPlaylistUtente(int modalita, int idUtente);
void mostraTuttePlaylist(int modalita);
void mostraSingoloUtente(int modalita, int id);
void mostraTuttiUtenti();
void mostraInfo(int modalita);
void mostraBrani(int modalita);
void mostraBraniArtista();
void mostraBraniAlbum();
void mostraBraniGenere();

#endif /* SRC_RICERCA_MOTORERICERCA_H_ */
