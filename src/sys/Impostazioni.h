/*
 * UNIBA/Ampere 1.1
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di Informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef SRC_SYS_IMPOSTAZIONI_H_
#define SRC_SYS_IMPOSTAZIONI_H_
#include <stdbool.h>

// Costanti di lunghezza
#define MAX_ENORME 1000
#define MAX_GRANDE 256
#define MAX_MEDIO 60

// File del database
#define cartella_database "database"
#define cartella_testi "database/testi"
#define file_brani "database/brani.txt"
#define file_albums "database/albums.txt"
	#define file_BranoArtista "database/BranoArtista.txt"
#define file_artisti "database/artisti.txt"
	#define file_BranoAlbum "database/BranoAlbum.txt"
#define file_generi "database/generi.txt"
	#define file_BranoGenere "database/BranoGenere.txt"
#define file_playlists "database/playlists.txt"
	#define file_PlaylistBrano "database/PlaylistBrano.txt"
#define file_utenti "database/utenti.txt"

/**
 * 	COLORI
 * 	L'utilizzo dei colori e' il seguente:
 * 	C_COLORE"testo"C_RESET
 * 	In questo modo dai colore al testo e ritorni allo schema colori originale alla fine
 * 	per evitare problemi di colori in seguito, un esempio con printf:
 * 	printf(C_ROSSO"Errore critico! Contattare l'amministratore"C_RESET);
 */
#define C_ROSSO		"\x1b[31m"
#define CB_ROSSO	"\x1b[1;31m"
#define C_VERDE   	"\x1b[32m"
#define C_GIALLO  	"\x1b[33m"
#define C_CIANO	  	"\x1b[36m"
#define C_BLU    	"\x1b[34m"
#define C_MAGENTA	"\x1b[35m"
#define C_RESET   	"\x1b[0m"

// Messaggi di default
#define ADMIN "Amministratore"
#define COLOR_ADMIN C_ROSSO ADMIN C_RESET
#define UTENTE "Utente normale"
#define COLOR_UTENTE C_CIANO UTENTE C_RESET

#define ERRORE "\n[ERRORE]"
#define COLOR_ERRORE C_ROSSO ERRORE C_RESET
#define ATTENZIONE "\n[ATTENZIONE]"
#define COLOR_ATTENZIONE C_GIALLO ATTENZIONE C_RESET
#define SUCCESSO "\n[SUCCESSO]"
#define COLOR_SUCCESSO C_VERDE SUCCESSO C_RESET

// Stampe utili
#define DIVISORE "\n----------------------------------------"

// Modalità di salvataggio
bool salvataggioDiretto;

// Sistema operativo attualmente in uso
int os;

// Funzione di rilevamento del sistema operativo attualmente in uso
int rilevareOS();


#endif /* SRC_SYS_IMPOSTAZIONI_H_ */
