/*
 * Ampere 0.2 rev. 1 - 28.05.2020
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef SRC_GESTORI_GESTOREARTISTI_H_
#define SRC_GESTORI_GESTOREARTISTI_H_
#include "../database/Database.h"

/**
 * 	@input istanza database
 *	Interfaccia utente stand-alone per l'inserimento di un artista, può essere chiamata
 *	senza dipendere da altre funzioni
 *	Chiama creaArtistaSeNonEsiste -> creaArtistaGuidato
 *	@output database modificato
 */
database inserimentoArtistaGuidato(database db);

/**
 *	@input istanza database, stringa nome d'arte dell'artista
 *	Interfaccia utente che guida l'inserimento di altre informazioni aggiuntive dell'artista
 *	Crea l'artista con creaArtista e lo passa a inserireArtista
 *	@output database modificato
 */
database creaArtistaGuidato(database db, char nomearte[]);

/**
 *	@input istanza database, stringa nome d'arte dell'artista
 *	Controlla se l'artista inserito esiste gia' grazie a controlloEsistenzaArtista
 *	e se non esiste, chiama creaArtistaGuidato per proseguire con l'inserimento
 *	altrimenti comunica all'utente che l'artista esiste gia', dunque non procedendo con l'inserimento
 *	@output database modificato
 */
database creaArtistaSeNonEsiste(database db, char nomearte[]);

/**
 * 	@input istanza database, stringa nome, cognome, nome d'arte e link biografia dell'album
 *	Funzione logica per la creazione di un record "artisti", prende le informazioni date in input
 *	e crea un record con esse. Si avvale del database in input per ottenere l'ultimo identificativo
 *	@output record album compilato
 */
struct artisti creaArtista(char nome[], char cognome[], char nomearte[], char linkbio[]);

void mostrareAnteprimaArtista(struct artisti nuovoArtista);

/**
 *	@input istanza database, record artisti artista
 *	Ottiene in input il record artista gia' compilato con creaArtista e gli assegna l'ultima posizione
 *	@output database modificato
 */
database inserireArtista(database db, struct artisti nuovoArtista);

/**
 *	@input istanza database, stringa nome d'arte dell'artista
 *	Cerca all'interno del database, attraverso un ciclo, almeno un'occorrenza del nome d'arte
 *	dell'artista dato in input e se esiste allora esce dal ciclo dando in output l'identificativo di esso
 *	@output identificativo artista
 */
int controlloEsistenzaArtista(database db, char nomearte[]);

/**
 * 	TODO: passare a valori veri e non tutte stringhe
 *	@input numero intero identificativo, stringa nome, cognome, nome d'arte e link biografia
 *	Scrive sul file "file_artisti", le informazioni date in input, separate con separatore pipe "|"
 *	@output FILE modificato
 */
void inserisciArtistiSuFile(char id[], char nome[], char cognome[], char nomearte[], char linkbio[]);

/**
 *	TODO: passare a valori veri e non tutte stringhe
 *	@input numero intero identificativo brano, numero intero identificativo artista
 *	Scrive sul file "file_associazioneartisti", le informazioni date in input, separate con separatore pipe "|"
 *	@output FILE modificato
 */
void inserisciAssociazioneArtistiSuFile(char idbrano[], char idartista[]);

/**
 *	TODO: adeguare modifica allo standard imposto dalle specifiche
 *	@input istanza database
 *	Interfaccia utente per modificare informazioni dell'artista presente nel database
 *	Si avvale di ottenerePosDaID per controllare l'esistenza di esso attraverso l'identificativo
 *	Se l'artista e' presente, procede alla modifica dell'informazione scelta con modificaSingoloArtista
 *	@output database modificato
 */
database modificaArtista(database db);

/**
 *	TODO: adeguare modifica allo standard imposto dalle specifiche
 *	@input istanza database, numero intero modalita' di esecuzione, numero intero identificativo
 *	In base alla modalita' scelta e data in input da modificaArtista, chiede all'utente la nuova informazione
 *	da inserire al posto della vecchia, sovrascrivendola
 *	Successivamente procede a mostrare all'utente il risultato delle modifiche effettuate
 *	@output database modificato
 */
database modificaSingoloArtista(database db, int modalita, int id);

/**
 *	TODO: adeguare cancellazione allo standard imposto dalle specifiche
 *	@input istanza database
 *	Interfaccia utente per la cancellazione di un artista presente nel database
 *	Si avvale di ottenerePosDaID per controllare l'esistenza di esso attraverso l'identificativo
 *	Se l'artista e' presente, procede alla cancellazione dell'artista con cancellaSingoloArtista
 *	@output database modificato
 */
database cancellaArtista(database db);

/**
 *	TODO: adeguare cancellazione allo standard imposto dalle specifiche
 *	@input istanza database, numero intero identificativo artista
 *	Operazioni per la cancellazione dell'artista all'interno del database presente in memoria
 *	Scala il database di n=1 posizione indietro e lo spazio rimanente alla fine assume valore zero,
 *	effettivamente causando la cancellazione dell'artista all'interno del database presente in memoria.
 *	La cancellazione dell'artista provvede anche a cancellare i brani collegati ad esso e, dunque, anche
 *	qualunque associazione effettuata con i brani appartenenti all'artista
 *	@output database modificato
 */
database cancellaSingoloArtista(database db, int id);

database cancellaAssociazioniArtisti(database db, int id);

/**
 *	TODO: Trovare un posto migliore
 *	Funzione di ricerca dell'artista allo scopo di ottenere il link della biografia
 *	per poi aprirlo con il browser predefinito di sistema attraverso
 *	apriLink senza alcun intervento da parte dell'utente
 */
void visualizzaBiografiaArtista(database db);

#endif /* SRC_GESTORI_GESTOREARTISTI_H_ */
