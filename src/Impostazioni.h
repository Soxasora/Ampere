/*
 * Ampere 0.1 rev. 180 - 23.04.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef IMPOSTAZIONI_H_
#define IMPOSTAZIONI_H_
#define MAX_TEMP 1000
#define MAX_CHAR 256

char *file_database;
char *dir_testi;
char *file_lingue;
char lingue[10][MAX_CHAR];

/**
 * Carica le impostazioni di sistema
 */
void caricaImpostazioni();

/**
 * Carica lingue disponibili per i brani
 */
void caricaLingue();

#endif /* IMPOSTAZIONI_H_ */
