/*
 * UNIBA/Ampere 1.3
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di Informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef SYS_MESSAGGI_H_
#define SYS_MESSAGGI_H_

void errore(int codice);
void attenzione(int codice);
void informazione(int codice);
void successo(int codice);
char richiesta(int codice);
void cPrintf(const char *colore, const char *messaggio);

#endif /* SYS_MESSAGGI_H_ */
