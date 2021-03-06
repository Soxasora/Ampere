/*
 * UNIBA/Ampere 1.3
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di Informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef SRC_GESTORI_GESTOREBRANI_H_
#define SRC_GESTORI_GESTOREBRANI_H_
#include "../database/Database.h"

/**
 * 	@input istanza database
 *	Interfaccia utente stand-alone per l'inserimento di un brano, pu� essere chiamata
 *	senza dipendere da altre funzioni
 *	Oltre alle informazioni di un brano, chiede all'utente anche l'artista, l'album ed il genere
 *	essi, se non gi� presenti nel database, procedono a creare le suddette informazioni avvalendosi
 *	di, ad esempio, creareArtistaSeNonEsiste, ottenendo poi l'id di essi con, ad esempio, controllareEsistenzaArtista
 *	Crea il brano con creareBrano e lo passa a inserireBrano
 *	@output database modificato
 */
void inserireBranoGuidato(database *db);

/**
 * 	@input istanza database, stringa titolo, numero intero identificativo album, numero intero
 * 	durata in secondi, numero intero anno di uscita, numero intero ascolti del brano
 *	Funzione logica per la creazione di un record "brani", prende le informazioni date in input
 *	e crea un record con esse. Si avvale del database in input per ottenere l'ultimo identificativo
 *	@output record brano compilato
 */
struct Brano creareBrano(char titolo[], int durata, int anno, int ascolti);

void mostrareAnteprimaBrano(database *db, struct Brano nuovoBrano, int idArtisti[], int idAlbum[], int idGeneri[]);
/**
 *	@input istanza database, record brani brano
 *	Ottiene in input il record brano gia' compilato con creareBrano e gli assegna l'ultima posizione
 *	Provvede, inoltre, a creare le associazioni con creaAssociazione... e le passa alle rispettive
 *	inserireAssociazione...
 *	@output database modificato
 */
void inserireBrano(database *db, struct Brano nuovoBrano, int idArtisti[], int idAlbum[], int idGeneri[]);
void controllareSimilitudineBrano(database *db, struct Brano nuovoBrano);

/**
 *	@input struct Brano brano
 *	Scrive sul file "file_brani", le informazioni date in input, separate con separatore pipe "|"
 *	@output FILE modificato
 */
void inserireBranoSuFile(struct Brano brano);

/**
 *	@input istanza database
 *	Interfaccia utente per modificare informazioni del brano presente nel database
 *	Si avvale di ottenerePosDaID per controllare l'esistenza di esso attraverso l'identificativo
 *	Se il brano e' presente, procede alla modifica dell'informazione scelta con modificaSingoloBrano
 *	@output database modificato
 */
void modificareBranoGuidato(database *db);
void creareBranoModificato(database *db, int campo, int id);
void mostrareAnteprimaModificaBrano(database *db, int idBrano, int campo, struct Brano branoModificato, int idAssociazioni[]);
void modificareBrano(database *db, int idBrano, int campo, struct Brano branoModificato, int idAssociazioni[]);

/**
 *	TODO: adeguare cancellazione allo standard imposto dalle specifiche
 *	@input istanza database
 *	Interfaccia utente per la cancellazione di un brano presente nel database
 *	Si avvale di ottenerePosDaID per controllare l'esistenza di esso attraverso l'identificativo
 *	Se il brano  e' presente, procede alla cancellazione di esso con cancellareBrano
 *	@output database modificato
 */
void cancellareBranoGuidato(database *db);

/**
 *	TODO: adeguare cancellazione allo standard imposto dalle specifiche
 *	@input istanza database, numero intero identificativo brano
 *	Operazioni per la cancellazione del brano all'interno del database presente in memoria
 *	Scala il database di n=1 posizione indietro e lo spazio rimanente alla fine assume valore zero,
 *	effettivamente causando la cancellazione del brano all'interno del database presente in memoria.
 *	La cancellazione del brano, provvede anche alla cancellazione dei dati collegati ad esso, dunque, anche
 *	qualunque associazione con cancellareAssociazioniBrano
 *	@output database modificato
 */
void cancellareBrano(database *db, int id);

/**
 *	TODO: adeguare cancellazione allo standard imposto dalle specifiche
 *	@input istanza database, numero intero identificativo brano
 *	Operazioni per la cancellazione delle associazioni del brano (dunque i dati collegati ad esso) dal database
 *	Si tratta, dunque, delle quattro associazioni: brano-artista, brano-album, brano-genere, playlist-brano
 *	@output database modificato
 */
void cancellareAssociazioniBrano(database *db, int id);

/**
 * 	@input identificativo del brano
 *	Operazioni per l'apertura del file contenete il testo (lyrics) appartenente all'identificativo del brano
 *	passato in input.
 *	Si avvale di "system" per aprire il file di testo con l'editor predefinito di sistema.
 */
void apriTesto(int idBrano);

/**
 *	@input istanza database
 *	Interfaccia utente per la ricerca di un brano del quale aprire il file di testo contenente il testo (lyrics)
 *	del brano.
 *	Si avvale di apriTesto per poter eseguire le operazioni di apertura del file
 */
void apriTestoDaRicerca(database *db);

#endif /* SRC_GESTORI_GESTOREBRANI_H_ */
