/*
 * Ampere 0.1 rev. 2931 - 10.05.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#include <stdbool.h>
#include "../sys/Impostazioni.h"

#ifndef GESTORI_GESTOREUTENTI_H_
#define GESTORI_GESTOREUTENTI_H_

bool isAdmin();
bool isGivenUserAdmin(int id);
void infoUtenteConnesso();
void login();
int controllaDatiUtente(char username[], char password[]);
void registrazioneUtente();
void inserimentoUtenteGuidato();
void inserisciUtente(char username[], char password[]);
bool controllaEsistenzaUtente(char username[]);
void inserisciUtenteSuFile(char id[], char username[], char password[], char admin[]);
void modificaUtente();
void modificaSingoloUtente(int modalita, int id);
void cancellaUtente();
void cancellaSingoloUtente(int id);

#endif /* GESTORI_GESTOREUTENTI_H_ */
