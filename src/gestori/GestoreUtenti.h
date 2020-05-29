/*
 * Ampere 0.2 rev. 5 - 29.05.2020
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef GESTORI_GESTOREUTENTI_H_
#define GESTORI_GESTOREUTENTI_H_
#include <stdbool.h>
#include "../database/Database.h"
#include "../sys/Impostazioni.h"

/**
 * 	@input istanza database
 *	Serve a controllare se l'utente connesso al momento e' un amministratore
 *	Restituisce vero se l'utente e' amministratore, altrimenti falso
 *	Si avvale di ottenerePosDaID per ottenere la posizione in base all'identificativo dell'utente connesso
 *	@output risultato booleano
 */
bool controllareSeAdmin(database db);

/**
 * 	@input istanza database, numero intero identificativo utente
 *	Serve a controllare se l'utente dato in input e' un amministratore
 *	Restituisce vero se l'utente e' amministratore, altrimenti falso
 *	Si avvale di ottenerePosDaID per ottenere la posizione in base all'identificativo dell'utente
 *	@output risultato booleano
 */
bool controllareSeAdminUtente(database db, int id);

bool controllareSePrescelto(database db);

/**
 *	@input istanza database
 *	Serie di stampe per mostrare un riepilogo breve dell'utente connesso al momento
 *	Si avvale di ottenerePosDaID per ottenere la posizione in base all'identificativo dell'utente connesso
 *	e serve unicamente per mostrare il nome utente.
 *	Si avvale, inoltre, di controllareSeAdmin per controllare se l'utente connesso e' amministratore
 */
void infoUtenteConnesso(database db);

/**
 *	@input istanza database
 *	Interfaccia utente per il login con nome utente e password
 *	Si avvale di controllareDatiUtente per controllare la veridicita' della combinazione nome utente/password
 *	Se il login viene eseguito con successo, assegna l'id, ottenuto attraverso controllareDatiUtente,
 *	dell'utente ad utente_connesso, altrimenti ripropone l'inserimento dei dati
 *	@output database modificato
 */
database loginUtente(database db);

/**
 *	@input istanza database, stringa nome utente, stringa password
 *	Funzione logica per controllare se i dati passati in input sono presenti nel database
 *	Per il nome utente viene utilizzata una comparazione stringhe senza distinzioni di maiuscole e minuscole
 *	per la password, invece, viene utilizzata la comparazione stringhe originale con distinzioni.
 *	Restituisce l'identificativo dell'utente trovato in base ai valori dati in input
 *	@output identificativo utente
 */
int controllareDatiUtente(database db, char username[], char password[]);

/**
 *	@input istanza database
 *	Interfaccia utente pubblica stand-alone per la registrazione guidata di un nuovo utente
 *	Se ad eseguire la funzione, e' un admin, non mostra le informazioni destinate ad un utente normale
 *	Si avvale di controllareEsistenzaUtente per evitare duplicati al momento dell'inserimento del nome utente.
 *	Crea l'utente con creareUtente ed utilizza l'output di esso per inserire l'utente con inserireUtente
 *	Alla fine della registrazione, se ad avviarla non e' stato un admin gia' connesso, manda l'utente al login.
 *	@output database modificato
 */
database registrareUtente(database db);

/**
 * 	@input istanza database, stringa nome utente, password
 *	Funzione logica per la creazione di un record "Utente", prende le informazioni date in input
 *	e crea un record con esse. Si avvale del database in input per ottenere l'ultimo identificativo
 *	@output record nuovoUtente compilato
 */
struct utenti creareUtente(database db, char username[], char password[], bool admin);

/**
 *	@input istanza database, record Utente nuovoUtente
 *	Ottiene in input il record nuovoUtente gia' compilato con creareUtente e gli assegna l'ultima posizione
 *	@output database modificato
 */
database inserireUtente(database db, struct utenti utente);

/**
 *	@input istanza database, stringa nome utente
 *	Cerca all'interno del database, attraverso un ciclo, almeno un'occorrenza del nome utente
 *  dato in input e se esiste allora esce dal ciclo dando in output vero o falso
 *	@output risultato booleano dell'esistenza dell'utente
 */
bool controllareEsistenzaUtente(database db, char username[]);

/**
 * 	TODO: passare a valori veri e non tutte stringhe
 *	@input numero intero identificativo utente, stringa nome utente, password, booleano admin
 *	Scrive sul file "file_utenti", le informazioni date in input, separate con separatore pipe "|"
 *	@output FILE modificato
 */
void inserireUtenteSuFile(int id, char username[], char password[], char admin[]);

/**
 *	TODO: adeguare modifica allo standard imposto dalle specifiche
 *	@input istanza database
 *	Interfaccia utente per modificare informazioni dell'utente presente nel database
 *	Si avvale di ottenerePosDaID per controllare l'esistenza di esso attraverso l'identificativo
 *	Se l'utente e' presente procede alla modifica dell'informazione scelta con modificaSingolaUtente
 *	@output database modificato
 */
database modificareUtenteGuidato(database db);

/**
 *	TODO: adeguare modifica allo standard imposto dalle specifiche
 *	@input istanza database, numero intero modalita' di esecuzione, numero intero identificativo
 *	In base alla modalita' scelta e data in input da modificareUtenteGuidato, chiede all'utente la nuova informazione
 *	da inserire al posto della vecchia, sovrascrivendola
 *	Presenta una modalita' utilizzabile unicamente da un amministratore,
 *	ovvero la modifica del suo ruolo (utente o admin)
 *	Successivamente procede a mostrare all'utente il risultato delle modifiche effettuate
 *	@output database modificato
 */
database modificareUtente(database db, int modalita, int id);

/**
 *	TODO: adeguare cancellazione allo standard imposto dalle specifiche
 *	@input istanza database
 *	Interfaccia utente per la cancellazione di un utente presente nel database
 *	Si avvale di ottenerePosDaID per controllare l'esistenza di esso attraverso l'identificativo
 *	Se a cancellare l'utente e' l'autore stesso oppure ad eseguire la funzione e' un admin,
 *	procede alla cancellazione dell'utente con cancellareUtente
 *	@output database modificato
 */
database cancellareUtenteGuidato(database db);

/**
 *	TODO: adeguare cancellazione allo standard imposto dalle specifiche
 *	@input istanza database, numero intero identificativo utente
 *	Operazioni per la cancellazione dell'utente all'interno del database presente in memoria
 *	Scala il database di n=1 posizione indietro e lo spazio rimanente alla fine assume valore zero,
 *	effettivamente causando la cancellazione dell'utente all'interno del database presente in memoria.
 *	@output database modificato
 */
database cancellareUtente(database db, int id);

#endif /* GESTORI_GESTOREUTENTI_H_ */
