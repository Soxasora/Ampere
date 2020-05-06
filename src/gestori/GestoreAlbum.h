/*
 * Ampere 0.1 rev. 2223 - 06.05.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef SRC_GESTORI_GESTOREALBUM_H_
#define SRC_GESTORI_GESTOREALBUM_H_

void inserimentoAlbumGuidato();
int creaAlbumGuidato(char titolo_album[]);
int creaAlbumSeNonEsiste(char titolo_album[]);
int inserisciAlbum(char titolo[], int anno);
void inserisciAlbumSuFile(char id[], char titolo[], char anno[]);
void inserisciCollezioneSuFile(char idalbum[], char idbrano[]);
int controlloEsistenzaAlbum(char album[]);
void modificaAlbum();
void modificaSingoloAlbum(int modalita, int id);
void cancellaAlbum();
void cancellaSingoloAlbum(int id);

#endif /* SRC_GESTORI_GESTOREALBUM_H_ */
