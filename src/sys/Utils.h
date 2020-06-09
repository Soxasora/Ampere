/*
 * UNIBA/Ampere 1.3
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di Informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef SRC_SYS_UTILS_H_
#define SRC_SYS_UTILS_H_
#include <stdbool.h>

/**
 * 	Logo di Ampere
 */
void logo();

/**
 * 	Informazioni su Ampere
 */
void info();

/**
 *	Funzione universale per mettere in pausa Ampere
 */
void aspetta();

/**
 * 	@input stringa link
 * 	Funzione universale per l'apertura di un link con browser
 */
void aprireLink(char link[]);

/**
 * 	@input stringa nome cartella, booleano silenzioso
 * 	Funzione di creazione cartella universale
 * 	Se impostato silenzioso, non mostra messaggi
 */
void creareCartella(char nome[], bool silenzioso);

/**
 * 	@input numero intero lunghezza, stringa
 * 	Funzione sicura per l'input da tastiera
 * 	Controlla se sono presenti pipes ("|") e le sostituisce con virgole per evitare problemi
 * 	Controlla se l'utente ha schiacciato "invio" senza inserire niente e sostituisce con "N/A"
 * 	@output stringa corretta
 */
char* inputStringa(int lunghezza, char stringa[]);

/**
 * 	@input stringa s1;
 * 	Ripulisce dai caratteri "spazio" al termine della stringa.
 * 	Non rimuove ulteriori whitespace come \n, \r, etc.
 * 	@output lunghezza della stringa finale
 */
int rimuovereSpaziFinali(char *stringa);

/**
 * 	Funzione sicura per l'input da tastiera di un intero senza segno fino a MAX_MEDIO cifre
 * 	Resistituisce -1 in caso di input non valido
 * 	@output numero inserito
 */
int inputNumero();

/**
 * 	Funzione sicura per l'input da tastiera di un carattere ignorando caratteri vuoti
 * 	@output carattere inserito
 */
char inputCarattere();

/**
 * 	@input stringa s1, stringa s2
 * 	Funzione universale per la comparazione di stringhe senza distinzione di caratteri
 * 	@output risultato comparazione, 0 se uguali
 */

int comparareStringhe(const char *s1, const char *s2);

/**
 * 	@input stringa s1, stringa s2
 * 	Funzione universale per la comparazione di stringhe anche se non complete
 * 	@output risultato booleano della comparazione
 */
bool comparareStringheParziale(const char *s1, const char *s2);

/**
 * 	Funzione universale per la pulizia del buffer in input
 * 	@output buffer pulito
 */
void pulireBuffer();

/**
 * 	@input stringa file
 * 	Funzione universale per il controllo del contenuto di un file
 * 	@output esito controllo
 */
int controllareSeFileVuoto(char *file);

void backupFile(char *file1, char *file2);

/**
 * 	Funzione per la conversione dei secondi in ore, minuti e secondi
 * 	@output stringa hh:mm:ss
 */
char *convertireSecondiInTempo(int secondi);

/**
 *	Abilita i colori ANSI per la linea di comando attraverso il comando color
 *	Funziona solo su Windows.
 */
void abilitareColori();

#endif /* SRC_SYS_UTILS_H_ */
