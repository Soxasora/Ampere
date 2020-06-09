/*
 * UNIBA/Ampere 1.2.2
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di Informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef SRC_GESTORI_GESTOREARTISTI_H_
#define SRC_GESTORI_GESTOREARTISTI_H_
#include "../database/Database.h"

/**
 * 	@input istanza database
 *	Interfaccia utente stand-alone per l'inserimento di un artista, pu� essere chiamata
 *	senza dipendere da altre funzioni
 *	Chiama creareArtistaSeNonEsiste -> creareArtistaGuidato
 *	@output database modificato
 */
void inserireArtistaGuidato(database *db);

/**
 *	@input istanza database, stringa nome d'arte dell'artista
 *	Interfaccia utente che guida l'inserimento di altre informazioni aggiuntive dell'artista
 *	Crea l'artista con creareArtista e lo passa a inserireArtista
 *	@output database modificato
 */
void creareArtistaGuidato(database *db, char nomeArte[]);

/**
 *	@input istanza database, stringa nome d'arte dell'artista
 *	Controlla se l'artista inserito esiste gia' grazie a controllareEsistenzaArtista
 *	e se non esiste, chiama creareArtistaGuidato per proseguire con l'inserimento
 *	altrimenti comunica all'utente che l'artista esiste gia', dunque non procedendo con l'inserimento
 *	@output database modificato
 */
void creareArtistaSeNonEsiste(database *db, char nomeArte[]);

/**
 * 	@input istanza database, stringa nome, cognome, nome d'arte e link biografia dell'album
 *	Funzione logica per la creazione di un record "artisti", prende le informazioni date in input
 *	e crea un record con esse. Si avvale del database in input per ottenere l'ultimo identificativo
 *	@output record album compilato
 */
struct Artista creareArtista(char nome[], char cognome[], char nomeArte[], char linkBio[]);

void mostrareAnteprimaArtista(struct Artista nuovoArtista);

/**
 *	@input istanza database, record artisti artista
 *	Ottiene in input il record artista gia' compilato con creareArtista e gli assegna l'ultima posizione
 *	@output database modificato
 */
void inserireArtista(database *db, struct Artista nuovoArtista);

/**
 *	@input istanza database, stringa nome d'arte dell'artista
 *	Cerca all'interno del database, attraverso un ciclo, almeno un'occorrenza del nome d'arte
 *	dell'artista dato in input e se esiste allora esce dal ciclo dando in output l'identificativo di esso
 *	@output identificativo artista
 */
int controllareEsistenzaArtista(database *db, char nomeArte[]);

/**
 *	@input struct Artista artista
 *	Scrive sul file "file_artisti", le informazioni date in input, separate con separatore pipe "|"
 *	@output FILE modificato
 */
void inserireArtistiSuFile(struct Artista artista);

/**
 *	TODO: adeguare modifica allo standard imposto dalle specifiche
 *	@input istanza database
 *	Interfaccia utente per modificare informazioni dell'artista presente nel database
 *	Si avvale di ottenerePosDaID per controllare l'esistenza di esso attraverso l'identificativo
 *	Se l'artista e' presente, procede alla modifica dell'informazione scelta con modificaSingoloArtista
 *	@output database modificato
 */
void modificareArtistaGuidato(database *db);

/**
 *	TODO: adeguare modifica allo standard imposto dalle specifiche
 *	@input istanza database, numero intero modalita' di esecuzione, numero intero identificativo
 *	In base alla modalita' scelta e data in input da modificaArtista, chiede all'utente la nuova informazione
 *	da inserire al posto della vecchia, sovrascrivendola
 *	Successivamente procede a mostrare all'utente il risultato delle modifiche effettuate
 *	@output database modificato
 */
void creareArtistaModificato(database *db, int campo, int id);
void modificareArtista(database *db, int idArtista, struct Artista artistaModificato);
/**
 *	TODO: adeguare cancellazione allo standard imposto dalle specifiche
 *	@input istanza database
 *	Interfaccia utente per la cancellazione di un artista presente nel database
 *	Si avvale di ottenerePosDaID per controllare l'esistenza di esso attraverso l'identificativo
 *	Se l'artista e' presente, procede alla cancellazione dell'artista con cancellareArtista
 *	@output database modificato
 */
void cancellareArtistaGuidato(database *db);

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
void cancellareArtista(database *db, int id);

void cancellareAssociazioniArtisti(database *db, int id);

/**
 *	TODO: Trovare un posto migliore
 *	Funzione di ricerca dell'artista allo scopo di ottenere il link della biografia
 *	per poi aprirlo con il browser predefinito di sistema attraverso
 *	aprireLink senza alcun intervento da parte dell'utente
 */
void visualizzareBiografiaArtista(database *db);

#endif /* SRC_GESTORI_GESTOREARTISTI_H_ */
