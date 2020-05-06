/*
 * Ampere 0.1 rev. 2040 - 06.05.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef GESTORI_GESTOREGENERI_H_
#define GESTORI_GESTOREGENERI_H_

void inserimentoGenereGuidato();
int creaGenereGuidato(char nome[]);
int creaGenereSeNonEsiste(char nome[]);
int inserisciGenere(char nome[]);
void inserisciGenereSuFile(char id[], char nome[]);
void inserisciTipiBraniSuFile(char idbrano[], char idgenere[]);
int controlloEsistenzaGenere(char genere[]);
void modificaGenere();
void modificaSingoloGenere(int id);
void cancellaGenere();
void cancellaSingoloGenere(int id);
#endif /* GESTORI_GESTOREGENERI_H_ */
