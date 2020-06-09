/*
 * UNIBA/Ampere 1.2.2
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di Informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#include "Messaggi.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../sys/Utils.h"
#include "../sys/Impostazioni.h"

/**
 * Tabella errori critici:
 * DATABASE:
 * 1: Nessun brano presente
 * 2: Nessun album presente
 *
 * 16: Non puoi accedere a questa funzione in quanto utente normale.
 * 17: Impossibile creare la cartella.
 * 18: Impossibile aprire il file selezionato.
 * 19: Impossibile creare un file di sistema.
 * 20: Impossibile creare il database.
 * -1: Errore critico di sistema.
 */
void errore(int codice) {
	printf(COLOR_ERRORE);
	if (codice==-1) {
		printf(" Si e' verificato un errore critico interno.");
	}else if (codice==16) {
		printf(" Non puoi accedere a questa funzione in quanto utente normale.");
	} else if (codice==20) {
		printf(" Impossibile creare il database.");
	}
}

void attenzione(int codice) {
	printf(COLOR_ATTENZIONE);
	if (codice==0) {
		printf(" Questo utente esiste gia'! Scegline un altro.");
	} else if (codice==1) {
		printf(" Combinazione username/password sbagliata. Riprovare.");
	} else if (codice==2) {
		printf(" Inseriti valori non validi. Riprovare.");
	} else if (codice==-2) {
		printf(" Inseriti valori non validi. Riprovare: ");
	} else if (codice==3) {
		printf(" Raggiunto il limite di caratteri. Re-inserisci: ");
	} else if (codice==20) {
		printf(" Inserita scelta non riconosciuta, riprovare.");
	} else if (codice==100) {
		printf(" Preparazione alla chiusura...");
	} else if (codice==101) {
		printf(" La ricerca non ha restituito risultati, riprovare.");
	} else if (codice==210) {
		printf(" Utente non trovato, riprovare");
	} else if (codice==211) {
		printf(" Brano non trovato, riprovare");
	} else if (codice==212) {
		printf(" Album non trovato, riprovare");
	} else if (codice==213) {
		printf(" Artista non trovato, riprovare");
	} else if (codice==214) {
		printf(" Genere non trovato, riprovare");
	} else if (codice==215) {
		printf(" Playlist non trovata, riprovare");
	}
}

void informazione(int codice) {
	printf(COLOR_INFO);
	if (codice==202) {
		printf(" Album esistente, dunque non c'e' bisogno di crearlo");
	} else if (codice==203) {
		printf(" Artista esistente, dunque non c'e' bisogno di crearlo");
	} else if (codice==204) {
		printf(" Genere esistente, dunque non c'e' bisogno di crearlo");
	} else if (codice==300) {
		printf(" Trovata similitudine");
	}
}


/**
 * 	Tabella successi:
 * 	// Inserimenti
 * 	0: Inserimento utente
 * 	1: Inserimento brano
 * 	2: Inserimento album
 * 	3: Inserimento artista
 * 	4: Inserimento genere
 * 	5: Inserimento playlist
 *
 * 	// Modifiche
 *	6: Modifica utente
 *	7: Modifica brano
 *	8: Modifica album
 *	9: Modifica artista
 *	10: Modifica genere
 *	11: Modifica playlist
 *
 *	// Cancellazioni
 *	12: Cancellazione utente
 *	13: Cancellazione brano
 *	14: Cancellazione album
 *	15: Cancellazione artista
 *	16: Cancellazione genere
 *	17: Cancellazione playlist
 *
 *	// Ottenimenti
 *	100: Ottenimento database
 *	101: Ottenimento utenti
 *	102: Ottenimento brani
 *	103: Ottenimento albums
 *	104: Ottenimento artisti
 *	105: Ottenimento generi
 *	106: Ottenimento playlists
 *	107: Ottenimento associazioni artisti
 *	108: Ottenimento associazioni albums
 *	109: Ottenimento associazioni generi
 *	110: Ottenimento associazioni playlist
 *
 *	// Sistema
 *	111: Ampere pronto
 *	112: Pronto per essere chiuso
 *
 *	// Stampe
 *	150: Stampa di brani selezionati
 *	151: Stampa di tutti i brani
 *
 *	// Salvataggi
 *	200: Utente
 *	201: Brano
 *	202: Album
 *	203: Artista
 *	204: Genere
 *	205: Playlist
 */

void successo(int codice) {
	printf(COLOR_SUCCESSO);
	if (codice==0) {
		printf(" Utente inserito nel database correttamente");
	} else if (codice==1) {
		printf(" Brano inserito nel database correttamente");
	} else if (codice==2) {
		printf(" Album inserito nel database correttamente");
	} else if (codice==3) {
		printf(" Artista inserito nel database correttamente");
	} else if (codice==4) {
		printf(" Genere inserito nel database correttamente");
	} else if (codice==5) {
		printf(" Playlist inserita nel database correttamente");
	} else if (codice==6) {
		printf(" Utente modificato correttamente");
	} else if (codice==7) {
		printf(" Brano modificato correttamente");
	} else if (codice==8) {
		printf(" Album modificato correttamente");
	} else if (codice==9) {
		printf(" Artista modificato correttamente");
	} else if (codice==10) {
		printf(" Genere modificato correttamente");
	} else if (codice==11) {
		printf(" Playlist modificato correttamente");
	} else if (codice==12) {
		printf(" Utente cancellato correttamente");
	} else if (codice==13) {
		printf(" Brano cancellato correttamente");
	} else if (codice==14) {
		printf(" Album cancellato correttamente");
	} else if (codice==15) {
		printf(" Artista cancellato correttamente");
	} else if (codice==16) {
		printf(" Genere cancellato correttamente");
	} else if (codice==17) {
		printf(" Playlist cancellato correttamente");
	} else if (codice==111) {
		printf(" Ampere pronto.");
	} else if (codice==112) {
		printf(" Pronto per essere chiuso.");
	} else if (codice==150) {
		printf(" Brani selezionati stampati correttamente");
	} else if (codice==151) {
		printf(" Tutti i brani della libreria musicale di Ampere stampati correttamente");
	} else if (codice==200) {
		printf(" Utente salvato su file correttamente");
	} else if (codice==201) {
		printf(" Brano salvato su file correttamente");
	} else if (codice==202) {
		printf(" Album salvato su file correttamente");
	} else if (codice==-202) {
		printf(" Associazione Brano-Album salvata su file correttamente");
	} else if (codice==203) {
		printf(" Artista salvato su file correttamente");
	} else if (codice==-203) {
		printf(" Associazione Brano-Artista salvata su file correttamente");
	} else if (codice==204) {
		printf(" Genere salvato su file correttamente");
	} else if (codice==-204) {
		printf(" Associazione Brano-Genere salvata su file correttamente");
	} else if (codice==205) {
		printf (" Playlist salvata su file correttamente");
	} else if (codice==300) {
		printf(" Nessuna similitudine trovata! Procediamo");
	}
}

char richiesta(int codice) {
	int controllo=0;
	char scelta='a';
	printf("\n");
	printf(COLOR_ATTENZIONE);
	if (codice==0) {
		printf(" Sicuro di voler continuare?");
	} else if (codice==1) {
		printf(" Sei uscito dalla ricerca, vuoi ancora inserire brani nella playlist?");
	} else if (codice==-1) {
		printf(" Sei uscito dalla ricerca, vuoi ancora selezionare brani da stampare?");
	} else if (codice==2) {
		printf(" Sei uscito dalla ricerca, vuoi ancora aprire il testo del brano?");
	} else if (codice==3) {
		printf(" Vuoi ancora continuare a modificare?");
	} else if (codice==4) {
		printf(" Sicuro di voler continuare con il ripristino?");
	} else if (codice==5) {
		printf(" Sicuro di voler continuare? Cancellera' anche i brani collegati ad esso.");
	} else if (codice==6) {
		printf(" Sulla base delle suddette scoperte, vuoi continuare ugualmente con l'inserimento?");
	} else if (codice==7) {
		printf(" Vorresti inserire dei brani in questa playlist?");
	} else if (codice==8) {
		printf(" Elencare i prossimi 5 brani?");
	} else if (codice==9) {
		printf(" Elencare i prossimi 5 album?");
	} else if (codice==10) {
		printf(" Elencare i prossimi 5 artisti?");
	} else if (codice==11) {
		printf(" Elencare i prossimi 5 generi?");
	} else if (codice==12) {
		printf(" Elencare le prossime 5 playlist?");
	} else if (codice==13) {
		printf(" Mostrare i brani della playlist?");
	} else if (codice==14) {
		printf(" Mostrare i brani di un album?");
	} else if (codice==15) {
		printf(" Mostrare i brani di un artista?");
	} else if (codice==16) {
		printf(" Mostrare i brani di un genere?");
	} else if (codice==17) {
		printf(" Mostrare i brani di una playlist?");
	} else if (codice==18) {
		printf(" Mostrare le playlist di un utente?");
	}
	while (controllo!=-1) {
		printf(" ["C_VERDE"Y"C_RESET"/"C_ROSSO"N"C_RESET"]: ");
		scelta = inputCarattere();
		if (scelta=='Y'||scelta=='y'||scelta=='N'||scelta=='n') {
			controllo=-1;
		}
	}
	return scelta;
}

void cPrintf(const char *colore, const char *messaggio) {
	printf("%s%s"C_RESET, colore, messaggio);
}
