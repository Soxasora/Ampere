/*
 * Ampere 0.1 rev. 2420 - 08.05.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef SRC_GESTORI_GESTOREBRANI_H_
#define SRC_GESTORI_GESTOREBRANI_H_

void inserimentoBranoGuidato();
void inserisciBrano(char titolo[], int id_artista, int id_album, int id_genere, int durata, int anno, int ascolti);
void inserisciBranoSuFile(char id[], char titolo[], char durata[], char id_album[], char anno[], char ascolti[]);
void modificaBrano();
void modificaSingoloBrano(int modalita, int id);
void cancellaBrano();
void cancellaSingoloBrano(int id);
void cancellaAssociazioniBrano(int id);
void apriTesto(int idBrano);
void apriTestoDaRicerca();
void apriTestoDaID();

#endif /* SRC_GESTORI_GESTOREBRANI_H_ */
