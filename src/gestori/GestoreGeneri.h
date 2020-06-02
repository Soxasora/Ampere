/*
 * Ampere 0.2 rev. 17 - 02.06.2020
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef GESTORI_GESTOREGENERI_H_
#define GESTORI_GESTOREGENERI_H_
#include "../database/Database.h"

/**
 * 	@input istanza database
 *	Interfaccia utente stand-alone per l'inserimento di un genere, può essere chiamata
 *	senza dipendere da altre funzioni
 *	Chiama creareGenereSeNonEsiste
 *	@output database modificato
 */
database inserireGenereGuidato(database db);

/**
 *	@input istanza database, stringa nome del genere
 *	Controlla se il genere inserito esiste gia' grazie a controllareEsistenzaGenere
 *	e se non esiste, crea il genere con creareGenere e lo passa a inserireGenere
 *	altrimenti comunica all'utente che l'artista esiste gia', dunque non procedendo con l'inserimento
 *	@output database modificato
 */
database creareGenereSeNonEsiste(database db, char nome[]);

/**
 * 	@input istanza database, stringa nome del genere
 *	Funzione logica per la creazione di un record "generi", prende le informazioni date in input
 *	e crea un record con esse. Si avvale del database in input per ottenere l'ultimo identificativo
 *	@output record genere compilato
 */
struct Genere creareGenere(char nome[]);

void mostrareAnteprimaGenere(struct Genere nuovoGenere);

/**
 *	@input istanza database, record generi genere
 *	Ottiene in input il record genere gia' compilato con creareGenere e gli assegna l'ultima posizione
 *	@output database modificato
 */
database inserireGenere(database db, struct Genere nuovoGenere);

/**
 *	@input struct Genere genere
 *	Scrive sul file "file_generi", le informazioni date in input, separate con separatore pipe "|"
 *	@output FILE modificato
 */
void inserireGenereSuFile(struct Genere genere);

/**
 *	@input istanza database, stringa nome del genere
 *	Cerca all'interno del database, attraverso un ciclo, almeno un'occorrenza del nome del genere
 *	dato in input e se esiste allora esce dal ciclo dando in output l'identificativo di esso
 *	@output identificativo genere
 */
int controllareEsistenzaGenere(database db, char genere[]);

/**
 *	TODO: adeguare modifica allo standard imposto dalle specifiche
 *	@input istanza database
 *	Interfaccia utente per modificare informazioni del genere presente nel database
 *	Si avvale di ottenerePosDaID per controllare l'esistenza di esso attraverso l'identificativo
 *	Se il genere e' presente, procede alla modifica dell'informazione scelta con modificareGenere
 *	@output database modificato
 */
database modificareGenereGuidato(database db);

/**
 *	TODO: adeguare modifica allo standard imposto dalle specifiche
 *	@input istanza database, numero intero modalita' di esecuzione, numero intero identificativo
 *	In base alla modalita' scelta e data in input da modificareGenereGuidato, chiede all'utente la nuova informazione
 *	da inserire al posto della vecchia, sovrascrivendola
 *	Successivamente procede a mostrare all'utente il risultato delle modifiche effettuate
 *	@output database modificato
 */
database modificareGenere(database db, int id);

/**
 *	TODO: adeguare cancellazione allo standard imposto dalle specifiche
 *	@input istanza database
 *	Interfaccia utente per la cancellazione di un genere presente nel database
 *	Si avvale di ottenerePosDaID per controllare l'esistenza di esso attraverso l'identificativo
 *	Se il genere e' presente, procede alla cancellazione del genere con cancellareGenere
 *	@output database modificato
 */
database cancellareGenereGuidato(database db);

/**
 *	TODO: adeguare cancellazione allo standard imposto dalle specifiche
 *	@input istanza database, numero intero identificativo genere
 *	Operazioni per la cancellazione del genere all'interno del database presente in memoria
 *	Scala il database di n=1 posizione indietro e lo spazio rimanente alla fine assume valore zero,
 *	effettivamente causando la cancellazione del genere all'interno del database presente in memoria.
 *	La cancellazione del genere provvede anche a cancellare i brani collegati ad esso e, dunque, anche
 *	qualunque associazione effettuata con i brani appartenenti al genere
 *	@output database modificato
 */
database cancellareGenere(database db, int id);

database cancellaAssociazioniGenere(database db, int idBrano);

#endif /* GESTORI_GESTOREGENERI_H_ */
