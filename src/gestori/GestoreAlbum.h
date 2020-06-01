/*
 * Ampere 0.2 rev. 12 -01.06.2020
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef SRC_GESTORI_GESTOREALBUM_H_
#define SRC_GESTORI_GESTOREALBUM_H_
#include "../database/Database.h"

/**
 * 	@input istanza database
 *	Interfaccia utente stand-alone per l'inserimento di un album, pu� essere chiamata
 *	senza dipendere da altre funzioni
 *	Chiama creaAlbumSeNonEsiste -> creaAlbumGuidato
 *	@output database modificato
 */
database inserimentoAlbumGuidato(database db);

/**
 *	@input istanza database, stringa titolo dell'album
 *	Interfaccia utente che guida l'inserimento di altre informazioni aggiuntive dell'album
 *	Crea l'album con creaAlbum e lo passa a inserireAlbum
 *	@output database modificato
 */
database creaAlbumGuidato(database db, char titolo_album[]);

/**
 *	@input istanza database, stringa titolo dell'album
 *	Controlla se l'album inserito esiste gia' grazie a controlloEsistenzaAlbum
 *	e se non esiste, chiama creaAlbumGuidato per proseguire con l'inserimento
 *	altrimenti comunica all'utente che l'album esiste gia', dunque non procedendo con l'inserimento
 *	@output database modificato
 */
database creaAlbumSeNonEsiste(database db, char titolo_album[]);

/**
 * 	@input istanza database, stringa titolo dell'album, numero intero anno di uscita
 *	Funzione logica per la creazione di un record "albums", prende le informazioni date in input
 *	e crea un record con esse. Si avvale del database in input per ottenere l'ultimo identificativo
 *	@output record album compilato
 */
struct albums creaAlbum(char titolo[], int anno);

void mostrareAnteprimaAlbum(struct albums nuovoAlbum);

/**
 *	@input istanza database, record albums album
 *	Ottiene in input il record album gia' compilato con creaAlbum e gli assegna l'ultima posizione
 *	@output database modificato
 */
database inserireAlbum(database db, struct albums nuovoAlbum);

/**
 *	@input struct albums album
 *	Scrive sul file "file_albums", le informazioni date in input, separate con separatore pipe "|"
 *	@output FILE modificato
 */
void inserisciAlbumSuFile(struct albums album);

/**
 *	@input istanza database, stringa titolo album
 *	Cerca all'interno del database, attraverso un ciclo, almeno un'occorrenza del titolo
 *	dell'album dato in input e se esiste allora esce dal ciclo dando in output l'identificativo di esso
 *	@output identificativo album
 */
int controlloEsistenzaAlbum(database db, char album[]);

/**
 *	TODO: adeguare modifica allo standard imposto dalle specifiche
 *	@input istanza database
 *	Interfaccia utente per modificare informazioni dell'album presente nel database
 *	Si avvale di ottenerePosDaID per controllare l'esistenza di esso attraverso l'identificativo
 *	Se l'album e' presente, procede alla modifica dell'informazione scelta con modificaSingoloAlbum
 *	@output database modificato
 */
database modificaAlbum(database db);

/**
 *	TODO: adeguare modifica allo standard imposto dalle specifiche
 *	@input istanza database, numero intero modalita' di esecuzione, numero intero identificativo
 *	In base alla modalita' scelta e data in input da modificaAlbum, chiede all'utente la nuova informazione
 *	da inserire al posto della vecchia, sovrascrivendola
 *	Successivamente procede a mostrare all'utente il risultato delle modifiche effettuate
 *	@output database modificato
 */
database modificaSingoloAlbum(database db, int modalita, int id);

/**
 *	TODO: adeguare cancellazione allo standard imposto dalle specifiche
 *	@input istanza database
 *	Interfaccia utente per la cancellazione di un album presente nel database
 *	Si avvale di ottenerePosDaID per controllare l'esistenza di esso attraverso l'identificativo
 *	Se l'album e' presente, procede alla cancellazione dell'album con cancellaSingoloAlbum
 *	@output database modificato
 */
database cancellaAlbum(database db);

/**
 *	TODO: adeguare cancellazione allo standard imposto dalle specifiche
 *	@input istanza database, numero intero identificativo album
 *	Operazioni per la cancellazione dell'intero album all'interno del database presente in memoria
 *	Scala il database di n=1 posizione indietro e lo spazio rimanente alla fine assume valore zero,
 *	effettivamente causando la cancellazione dell'album all'interno del database presente in memoria.
 *	La cancellazione dell'album provvede anche a cancellare i brani collegati ad esso e, dunque, anche
 *	qualunque associazione effettuata con i brani presenti in quell'album
 *	@output database modificato
 */
database cancellaSingoloAlbum(database db, int id);

database cancellaAssociazioniAlbum(database db, int idBrano);

#endif /* SRC_GESTORI_GESTOREALBUM_H_ */
