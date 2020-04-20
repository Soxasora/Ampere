/*
 * FabbAmp 0.1 rev. 137 - 19.04.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/FabbAmp/blob/master/LICENSE
 */

#ifndef UTILS_H_
#define UTILS_H_

/**
 * Stampa delle informazioni sul programma
 */
void info();

/**
 * Pulisce il buffer stdin per evitare comportamenti inaspettati al momento dell'inserimento
 */
void pulisciBuffer();

/**
 * Macro per rendere portatile la funzione di pausa
 */
void aspetta();

/**
 * Macro per rendere portatile la funzione di comparazione di stringhe senza contare maiuscolo e minuscolo
 */
int comparaStringhe(const char *s1, const char *s2);

/**
 * Funzione di controllo del contenuto del file
 * @return 0 se il file contiene informazioni, 1 se il file è vuoto
 */
int controllaSeFileVuoto();

/**
 * Funzione di conteggio dei caratteri presenti nel file
 * @return numero di caratteri presenti nel file
 */
int conteggiaCaratteriFile(FILE* fp);

/**
 * Sistema di backup del database attraverso la copia del database file-based principale carattere per carattere
 */
void backupDatabase(char *file2);

/**
 * Funzione di stampa del Menu Principale
 */
void menu();

/**
 * Funzione di stampa del menu dedicato alle funzioni relative al Database
 */
void menuDatabase();

/**
 * Funzione di stampa del menu dedicato alle funzioni relative al Motore di Ricerca
 */
void menuRicerca();

/**
 * Funzione di stampa del menu dedicato alle funzioni relative alla modifica delle informazioni dei brani
 */
void menuModifica();

/**
 * Funzione di stampa del menu dedicato alle funzioni di DEBUG per agevolare una programmazione pulita
 */
void menuDebug();


#endif /* UTILS_H_ */
