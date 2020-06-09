/*
 * UNIBA/Ampere 1.3
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di Informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef GESTORI_GESTOREFILE_H_
#define GESTORI_GESTOREFILE_H_
#include "../database/Database.h"

/**
 *	Funzione logica per la cancellazione di tutti i file del database
 *	Si avvale della funzione "remove"
 */
void cancellareDatabaseFile();

/**
 * 	@input istanza database
 *	Serve a chiamare le varie funzioni stand-alone per il salvataggio delle modifiche effettuate al database
 */
void salvareModificheSuFile(database *db);

/**
 *	@input istanza database
 *	Operazioni per il salvataggio dei brani nel file "file_brani"
 *	Si avvale di backupFile per salvare, temporaneamente, "file_brani" su "temp_brani.txt"
 *	Cancella "file_brani" attraverso "remove"
 *	Esegue inserireBranoSuFile, ricreando, dunque, "file_brani" ed inserendo record per record le informazioni
 *	Cancella "temp_brani.txt" attraverso "remove" una volta finito il processo di inserimento
 */
void salvareBraniSuFile(database *db);

/**
 *	@input istanza database
 *	Operazioni per il salvataggio degli album nel file "file_albums"
 *	Si avvale di backupFile per salvare, temporaneamente, "file_albums" su "temp_albums.txt"
 *	Cancella "file_albums" attraverso "remove"
 *	Esegue inserireAlbumSuFile, ricreando, dunque, "file_albums" ed inserendo record per record le informazioni
 *	Cancella "temp_albums.txt" attraverso "remove" una volta finito il processo di inserimento
 */
void salvareAlbumSuFile(database *db);

/**
 *	@input istanza database
 *	Operazioni per il salvataggio degli artisti nel file "file_artisti"
 *	Si avvale di backupFile per salvare, temporaneamente, "file_artisti" su "temp_artisti.txt"
 *	Cancella "file_artisti" attraverso "remove"
 *	Esegue inserisciArtistaSuFile, ricreando, dunque, "file_artisti" ed inserendo record per record le informazioni
 *	Cancella "temp_artisti.txt" attraverso "remove" una volta finito il processo di inserimento
 */
void salvareArtistiSuFile(database *db);

/**
 *	@input istanza database
 *	Operazioni per il salvataggio dei generi nel file "file_generi"
 *	Si avvale di backupFile per salvare, temporaneamente, "file_generi" su "temp_generi.txt"
 *	Cancella "file_generi" attraverso "remove"
 *	Esegue inserireGenereSuFile, ricreando, dunque, "file_generi" ed inserendo record per record le informazioni
 *	Cancella "temp_generi.txt" attraverso "remove" una volta finito il processo di inserimento
 */
void salvareGeneriSuFile(database *db);

/**
 *	@input istanza database
 *	Operazioni per il salvataggio delle playlist nel file "file_playlists"
 *	Si avvale di backupFile per salvare, temporaneamente, "file_playlists" su "temp_playlists.txt"
 *	Cancella "file_playlists" attraverso "remove"
 *	Esegue inserirePlaylistSuFile, ricreando, dunque, "file_playlists" ed inserendo record per record le informazioni
 *	Cancella "temp_playlists.txt" attraverso "remove" una volta finito il processo di inserimento
 */
void salvarePlaylistSuFile(database *db);

/**
 *	@input istanza database
 *	Operazioni per il salvataggio degli utenti nel file "file_utenti"
 *	Si avvale di backupFile per salvare, temporaneamente, "file_utenti" su "temp_utenti.txt"
 *	Cancella "file_utenti" attraverso "remove"
 *	Esegue inserireUtenteSuFile, ricreando, dunque, "file_utenti" ed inserendo record per record le informazioni
 *	Cancella "temp_utenti.txt" attraverso "remove" una volta finito il processo di inserimento
 */
void salvareUtentiSuFile(database *db);

// Associazioni
/**
 *	@input istanza database
 *	Operazioni per il salvataggio delle associazioni brano-album nel file "file_BranoAlbum"
 *	Si avvale di backupFile per salvare, temporaneamente, "file_BranoAlbum" su "temp_BranoAlbum.txt"
 *	Cancella "file_BranoAlbum" attraverso "remove"
 *	Esegue inserireBranoArtistaSuFile, ricreando, dunque, "file_BranoAlbum" ed inserendo record per record le informazioni
 *	Cancella "temp_BranoAlbum.txt" attraverso "remove" una volta finito il processo di inserimento
 */
void salvareBranoAlbumSuFile(database *db);

/**
 *	@input istanza database
 *	Operazioni per il salvataggio delle associazioni brano-artista nel file "file_BranoArtista"
 *	Si avvale di backupFile per salvare, temporaneamente, "file_BranoArtista" su "temp_BranoArtista.txt"
 *	Cancella "file_BranoArtista" attraverso "remove"
 *	Esegue inserireBranoArtistaSuFile, ricreando, dunque, "file_BranoArtista"
 *	ed inserendo record per record le informazioni
 *	Cancella "temp_BranoArtista.txt" attraverso "remove" una volta finito il processo di inserimento
 */
void salvareAssociazioniArtistiSuFile(database *db);

/**
 *	@input istanza database
 *	Operazioni per il salvataggio delle associazioni brano-genere nel file "file_BranoGenere"
 *	Si avvale di backupFile per salvare, temporaneamente, "file_BranoGenere" su "temp_BranoGenere.txt"
 *	Cancella "file_BranoGenere" attraverso "remove"
 *	Esegue inserireBranoGenereSuFile, ricreando, dunque, "file_BranoGenere" ed inserendo record per record le informazioni
 *	Cancella "temp_BranoGenere.txt" attraverso "remove" una volta finito il processo di inserimento
 */
void salvareBranoGenereSuFile(database *db);

/**
 *	@input istanza database
 *	Operazioni per il salvataggio delle associazioni playlist-brano nel file "file_PlaylistBrano"
 *	Si avvale di backupFile per salvare, temporaneamente, "file_PlaylistBrano" su "temp_PlaylistBrano.txt"
 *	Cancella "file_PlaylistBrano" attraverso "remove"
 *	Esegue inserirePlaylistBranoSuFile, ricreando, dunque, "file_PlaylistBrano" ed inserendo record per record le informazioni
 *	Cancella "temp_PlaylistBrano.txt" attraverso "remove" una volta finito il processo di inserimento
 */
void salvarePlaylistBranoSuFile(database *db);

#endif /* GESTORI_GESTOREFILE_H_ */
