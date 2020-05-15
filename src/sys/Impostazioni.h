/*
 * Ampere 0.1 rev. 4075 - 19.05.2020
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#ifndef SRC_SYS_IMPOSTAZIONI_H_
#define SRC_SYS_IMPOSTAZIONI_H_

// Costanti di lunghezza
#define MAX_ENORME 1000
#define MAX_GRANDE 256
#define MAX_MEDIO 60

// File del database
#define cartella_database "database"
#define cartella_testi "database\\testi"
#define file_brani "database\\brani.txt"
#define file_albums "database\\albums.txt"
	#define file_associazioneartisti "database\\associazioneartisti.txt"
#define file_artisti "database\\artisti.txt"
	#define file_collezione "database\\collezione.txt"
#define file_generi "database\\generi.txt"
	#define file_tipobrano "database\\tipobrano.txt"
#define file_playlists "database\\playlists.txt"
	#define file_raccolta "database\\raccolta.txt"
#define file_utenti "database\\utenti.txt"

// Sistema operativo attualmente in uso
int os;

// Funzione di rilevamento del sistema operativo attualmente in uso
int rivelaOS();


#endif /* SRC_SYS_IMPOSTAZIONI_H_ */
