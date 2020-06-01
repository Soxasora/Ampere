/*
 * Ampere 0.2 rev. 12 -01.06.2020
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef SRC_SYS_UTILS_H_
#define SRC_SYS_UTILS_H_

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
void apriLink(char link[]);

/**
 * 	@input stringa nome cartella, booleano silenzioso
 * 	Funzione di creazione cartella universale
 * 	Se impostato silenzioso, non mostra messaggi
 */
void creaCartella(char nome[], bool silenzioso);

/**
 * 	@input numero intero lunghezza, stringa
 * 	Funzione sicura per l'input da tastiera
 * 	Controlla se sono presenti pipes ("|") e le sostituisce con virgole per evitare problemi
 * 	Controlla se l'utente ha schiacciato "invio" senza inserire niente e sostituisce con "N/A"
 * 	@output stringa corretta
 */
char* inputStringaSicuro(int lunghezza, char stringa[]);

/**
 * 	@input stringa s1, stringa s2
 * 	Funzione universale per la comparazione di stringhe senza distinzione di caratteri
 * 	@output risultato comparazione, 0 se uguali
 */
int comparaStringhe(const char *s1, const char *s2);

/**
 * 	@input stringa s1, stringa s2
 * 	Funzione universale per la comparazione di stringhe anche se non complete
 * 	@output risultato booleano della comparazione
 */
bool comparaStringheParziale(const char *s1, const char *s2);

/**
 * 	Funzione di richiesta posizione e nome di un file
 * 	@output stringa risultante dall'input
 */
char *chiediFile();

/**
 * 	Funzione universale per la pulizia del buffer in input
 * 	@output buffer pulito
 */
void pulisciBuffer();

/**
 * 	@input stringa file
 * 	Funzione universale per il controllo del contenuto di un file
 * 	@output esito controllo
 */
int controllaSeFileVuoto(char *file);

/**
 * 	//TODO Da spostare
 * 	@input stringa file1, stringa file2
 * 	Funzione per la copia di un file in un altro file
 * 	@output nuovo file
 */
void backupFile(char *file1, char *file2);

/**
 * 	Funzione per la conversione dei secondi in ore, minuti e secondi
 * 	@output stringa hh:mm:ss
 */
char *convertiSecondiInTempo(int secondi);

/**
 *	Abilita i colori ANSI per la linea di comando attraverso il comando color
 *	Funziona solo su Windows.
 */
void abilitaColori();

#endif /* SRC_SYS_UTILS_H_ */
