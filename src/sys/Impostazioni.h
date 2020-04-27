/*
 * Ampere 0.1 rev. 501 - 27.04.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef SYS_IMPOSTAZIONI_H_
#define SYS_IMPOSTAZIONI_H_
#define MAX_TEMP 1000
#define MAX_CHAR 256
#define MAX_LINGUE 512

#define file_impostazioni "sistema\\impostazioni.ini"

char *file_database;
char *dir_testi;
char *file_lingue;

typedef struct lingueSistema {
	int id;
	char nome_umano[MAX_CHAR];
} lingua;

lingua* lingue;

/**
 * Impostazione guidata di Ampere
 */
void setup();

/**
 * Carica le impostazioni di sistema
 */
void caricaImpostazioni();

/**
 * Crea il file delle lingue e guida l'inserimento
 */
void creaLingue();

/**
 * Carica lingue disponibili per i brani
 */
lingua* caricaLingue();

#endif /* SYS_IMPOSTAZIONI_H_ */
