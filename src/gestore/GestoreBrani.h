/*
 * Ampere 0.1 rev. 420 - 26.04.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef GESTORE_GESTOREBRANI_H_
#define GESTORE_GESTOREBRANI_H_

/**
 * Mostra all'utente una procedura guidata per inserire brani nel database file-based
 */
void inserimentoGuidato();

/**
 * Funzione di supporto a inserimentoGuidato(), effettua le operazioni di inserimento del brano nel database file-based
 */
void inserisciBranoGuidato(int modalita, char id[], char titolo[], char artista[], char feat[], char produttore[], char scrittore[], char album[], char durata[], char anno[], char lingua[], char ascolti[], char gradimento[]);

/**
 * Funzione DEV per inserire un brano direttamente e senza procedura guidata
 */
void inserimentoDiretto();

/**
 * Funzione di supporto a inserimentoDiretto(), effettua l'operazione di inserimento del brano nel database file-based
 */
void inserisciBranoDiretto(char stringa[]);

/**
 * Sistema guidato per la modifica di informazioni di un brano
 */
void modifica(int scelta);

/**
 * Funzione di supporto a modifica(), effettua le operazioni di modifica di brani direttamente nello struct globale
 */
void modificaSingoloBrano(int pos, int modalita);

/**
 * Sistema guidato per la cancellazione di un brano
 */
void cancella();

/**
 * Funzione di supporto a cancella(), effettua le operazioni di cancellazione di brani direttamente nello struct globale
 */
void cancellaSingoloBrano(int pos);

#endif /* GESTORE_GESTOREBRANI_H_ */
