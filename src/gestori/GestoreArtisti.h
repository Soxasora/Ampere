/*
 * Ampere 0.1 rev. 1250 - 04.05.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef SRC_GESTORI_GESTOREARTISTI_H_
#define SRC_GESTORI_GESTOREARTISTI_H_

void inserimentoArtistaGuidato();
int creaArtistaGuidato(char nomearte[]);
int creaArtistaSeNonEsiste(char artista[]);
int inserisciArtista(char nome[], char cognome[], char nomearte[]);
void inserisciArtistiSuFile(char id[], char nome[], char cognome[], char nomearte[]);
void inserisciAssociazioneArtistiSuFile(char idbrano[], char idartista[]);

#endif /* SRC_GESTORI_GESTOREARTISTI_H_ */
