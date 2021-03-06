/*
 * UNIBA/Ampere 1.3
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di Informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../gestori/GestorePlaylist.h"
#include "../gestori/GestoreUtenti.h"
#include "../gestori/GestoreBrani.h"
#include "../gestori/GestoreAlbum.h"
#include "../gestori/GestoreArtisti.h"
#include "../gestori/GestoreGeneri.h"
#include "../ricerca/RicercaGenerale.h"
#include "../ricerca/MotoreRicerca.h"
#include "../database/Database.h"
#include "../database/DatabaseUtils.h"
#include "../sys/Utils.h"
#include "../sys/Menu.h"
#include "../sys/Impostazioni.h"
#include "../Ampere.h"
#include "Messaggi.h"

void menuLogin(database *db) {
	int scelta;
	do {
		scelta=-1;
		while (scelta<0||scelta>1) {
				printf("\nDesideri effettuare: il "C_VERDE"Login[0]"C_RESET" oppure "C_GIALLO"Registrarti[1]"C_RESET" ad Ampere? ");
				scelta = inputNumero();
			}
			if (scelta==0) {
				loginUtente(db);
			} else {
				registrareUtente(db);
			}
	} while (db->ultimoEsito==-1);
	
}

// Nuovo Menu di Ampere
void menu(database *db) {
	int scelta=-1;
	printf("\n===["C_CIANO"Menu Principale"C_RESET"]===");
	printf("\n[1] Effettua una "C_CIANO"Ricerca"C_RESET);
	printf("\n[2] Effettua una "C_CIANO"Ricerca Avanzata"C_RESET);
	printf("\n[3] "C_CIANO"La mia libreria musicale"C_RESET);
	printf("\n[4] "C_GIALLO"Gestisci il tuo account"C_RESET);
	if (controllareSeAdmin(db)==true) {
		printf("\n[9] "C_ROSSO"Menu Manipolazione Database"C_RESET);
		printf("\n[10] "C_ROSSO"Menu Debug"C_RESET);
	}
	printf("\n[0] "C_ROSSO"Esci dal programma"C_RESET);
	while (scelta<0||scelta==5||scelta==6||scelta==7||scelta==8||scelta>10) {
		printf("\n"C_VERDE"Inserisci la tua scelta"C_RESET": ");
		scelta = inputNumero();
	}
	if (scelta==1) {
		eseguireRicerca(db);
		aspetta();
		menu(db);
	} else if (scelta==2) {
		menuRicercaAvanzata(db);
	} else if (scelta==3) {
		menuPlaylist(db);
	} else if (scelta==4) {
		menuAccount(db);
	} else if (scelta==9) {
		if (controllareSeAdmin(db))
			menuDatabase(db);
		else
			errore(16);
	} else if (scelta==10) {
		if (controllareSeAdmin(db))
			menuDebug(db);
		else
			errore(16);
	} else if (scelta==0) {
		printf("\nUscendo dal programma...\n");
	} else {
		attenzione(20);
		menu(db);
	}
	
}

void menuAccount(database *db) {
	
	int scelta=-1;
	printf("\n===["C_GIALLO"Menu Account"C_RESET"]===");
	printf("\n[1] "C_GIALLO"Modifica"C_RESET" il tuo account");
	printf("\n[2] "C_ROSSO"Cancella"C_RESET" il tuo account");
	printf("\n[0] "C_BLU"Ritorna al menu precedente"C_RESET);
	while (scelta<0||scelta>2) {
		printf("\n"C_VERDE"Inserisci la tua scelta"C_RESET": ");
		scelta = inputNumero();
	}
	if (scelta==1) {
		modificareUtenteGuidato(db);
		aspetta();
		menuAccount(db);
	} else if (scelta==2) {
		cancellareUtenteGuidato(db);
		aspetta();
		menuAccount(db);
	} else if (scelta==0) {
		menu(db);
	} else {
		attenzione(20);
		menuAccount(db);
	}
	
}

void menuPlaylist(database *db) {
	
	int scelta=-1;
	printf("\n===["C_CIANO"Menu Playlist"C_RESET"]===");
	printf("\n[1] "C_CIANO"Le mie playlist"C_RESET);
	printf("\n[2] "C_VERDE"Crea"C_RESET" playlist");
	printf("\n[3] "C_VERDE"Inserisci"C_RESET" brani in una playlist");
	printf("\n[4] "C_GIALLO"Modifica"C_RESET" playlist");
	printf("\n[5] "C_ROSSO"Cancella"C_RESET" playlist");
	printf("\n[0] "C_BLU"Ritorna al menu precedente"C_RESET);
	while (scelta<0||scelta>6) {
		printf("\n"C_VERDE"Inserisci la tua scelta"C_RESET": ");
		scelta = inputNumero();
	}
	if (scelta==1) {
		mostrarePlaylistUtente(db, 0,db->utenteCorrente);
		aspetta();
		menuPlaylist(db);
	} else if (scelta==2) {
		crearePlaylistGuidato(db);
		aspetta();
		menuPlaylist(db);
	} else if (scelta==3) {
		inserireBraniPlaylistGuidato(db);
		aspetta();
		menuPlaylist(db);
	} else if (scelta==4) {
		modificarePlaylistGuidato(db);
		aspetta();
		menuPlaylist(db);
	} else if (scelta==5) {
		cancellarePlaylistGuidato(db);
		aspetta();
		menuPlaylist(db);
	} else if (scelta==0) {
		menu(db);
	} else {
		attenzione(20);
		menuPlaylist(db);
	}
	
}

void menuDatabase(database *db) {
	
	int scelta=-1;
	printf("\n===["C_ROSSO"Menu Database"C_RESET"]===");
	printf("\n[1] "C_VERDE"Inserisci"C_RESET" nel database");
	printf("\n[2] "C_ROSSO"Cancella"C_RESET" nel database");
	printf("\n[3] "C_GIALLO"Modifica"C_RESET" nel database");
	printf("\n[4] "C_VERDE"Effettua un backup"C_RESET" del database");
	printf("\n[5] "C_VERDE"Effettua un ripristino"C_RESET" del database da un backup");
	printf("\n[0] "C_BLU"Ritorna al menu principale"C_RESET);
	while (scelta<0||scelta>5) {
		printf("\n"C_VERDE"Inserisci la tua scelta"C_RESET": ");
		scelta = inputNumero();
	}
	if (scelta==1) {
		menuDBInserimento(db);
	} else if (scelta==2) {
		menuDBCancella(db);
	} else if (scelta==3) {
		menuDBModifica(db);
	} else if (scelta==4) {
		backupDatabase();
		aspetta();
		menuDatabase(db);
	} else if (scelta==5) {
		ripristinareDatabase(db);
		printf("\nPer rendere effettive le modifiche, ora chiudero' Ampere.");
		aspetta();
		terminazione(db);
		exit(0);
	} else if (scelta==0) {
		menu(db);
	} else {
		attenzione(20);
		menuDatabase(db);
	}
	
}

void menuDBInserimento(database *db) {
	
	int scelta=-1;
	printf("\n===["C_VERDE"Menu di Inserimento nel Database"C_RESET"]===");
	printf("\n[1] "C_VERDE"Inserisci"C_RESET" un brano");
	printf("\n[2] "C_VERDE"Inserisci"C_RESET" un artista");
	printf("\n[3] "C_VERDE"Inserisci"C_RESET" un album");
	printf("\n[4] "C_VERDE"Inserisci"C_RESET" un genere");
	printf("\n[5] "C_VERDE"Inserisci"C_RESET" un utente");
	printf("\n[0] "C_BLU"Ritorna al menu precedente"C_RESET);
	while (scelta<0||scelta>5) {
		printf("\n"C_VERDE"Inserisci la tua scelta"C_RESET": ");
		scelta = inputNumero();
	}
	if (scelta==1) {
		inserireBranoGuidato(db);
		aspetta();
		menuDBInserimento(db);
	} else if (scelta==2) {
		inserireArtistaGuidato(db);
		aspetta();
		menuDBInserimento(db);
	} else if (scelta==3) {
		inserireAlbumGuidato(db);
		aspetta();
		menuDBInserimento(db);
	} else if (scelta==4) {
		inserireGenereGuidato(db);
		aspetta();
		menuDBInserimento(db);
	} else if (scelta==5) {
		registrareUtente(db);
		aspetta();
		menuDBInserimento(db);
	} else if (scelta==0) {
		menuDatabase(db);
	} else {
		attenzione(20);
		menuDBInserimento(db);
	}
	
}

void menuDBModifica(database *db) {
	
	int scelta=-1;
	printf("\n===["C_GIALLO"Menu di Modifica nel Database"C_RESET"]===");
	printf("\n[1] "C_GIALLO"Modifica"C_RESET" un brano");
	printf("\n[2] "C_GIALLO"Modifica"C_RESET" un artista");
	printf("\n[3] "C_GIALLO"Modifica"C_RESET" un album");
	printf("\n[4] "C_GIALLO"Modifica"C_RESET" un genere");
	printf("\n[5] "C_GIALLO"Modifica"C_RESET" una playlist");
	printf("\n[6] "C_GIALLO"Modifica"C_RESET" un utente");
	printf("\n[0] "C_BLU"Ritorna al menu precedente"C_RESET);
	while (scelta<0||scelta>6) {
		printf("\n"C_VERDE"Inserisci la tua scelta"C_RESET": ");
		scelta = inputNumero();
	}
	if (scelta==1) {
		modificareBranoGuidato(db);
		aspetta();
		menuDBModifica(db);
	} else if (scelta==2) {
		modificareArtistaGuidato(db);
		aspetta();
		menuDBModifica(db);
	} else if (scelta==3) {
		modificareAlbumGuidato(db);
		aspetta();
		menuDBModifica(db);
	} else if (scelta==4) {
		modificareGenereGuidato(db);
		aspetta();
		menuDBModifica(db);
	} else if (scelta==5) {
		modificarePlaylistGuidato(db);
		aspetta();
		menuDBModifica(db);
	} else if (scelta==6) {
		modificareUtenteGuidato(db);
		aspetta();
		menuDBModifica(db);
	} else if (scelta==0) {
		menuDatabase(db);
	} else {
		attenzione(20);
		menuDBModifica(db);
	}
	
}

void menuDBCancella(database *db) {
	
	int scelta=-1;
	printf("\n===["C_ROSSO"Menu di Cancellazione nel Database"C_RESET"]===");
	printf("\n[1] "C_ROSSO"Cancella"C_RESET" un brano");
	printf("\n[2] "C_ROSSO"Cancella"C_RESET" un artista");
	printf("\n[3] "C_ROSSO"Cancella"C_RESET" un album");
	printf("\n[4] "C_ROSSO"Cancella"C_RESET" un genere");
	printf("\n[5] "C_ROSSO"Cancella"C_RESET" una playlist");
	printf("\n[6] "C_ROSSO"Cancella"C_RESET" un utente");
	printf("\n[0] "C_BLU"Ritorna al menu precedente"C_RESET);
	while (scelta<0||scelta>6) {
		printf("\n"C_VERDE"Inserisci la tua scelta"C_RESET": ");
		scelta = inputNumero();
	}
	if (scelta==1) {
		cancellareBranoGuidato(db);
		aspetta();
		menuDBCancella(db);
	} else if (scelta==2) {
		cancellareArtistaGuidato(db);
		aspetta();
		menuDBCancella(db);
	} else if (scelta==3) {
		cancellareAlbumGuidato(db);
		aspetta();
		menuDBCancella(db);
	} else if (scelta==4) {
		cancellareGenereGuidato(db);
		aspetta();
		menuDBCancella(db);
	} else if (scelta==5) {
		cancellarePlaylistGuidato(db);
		aspetta();
		menuDBCancella(db);
	} else if (scelta==6) {
		cancellareUtenteGuidato(db);
		aspetta();
		menuDBCancella(db);
	} else if (scelta==0) {
		menuDatabase(db);
	} else {
		attenzione(20);
		menuDBCancella(db);
	}
	
}

void menuRicercaAvanzata(database *db) {
	
	int scelta=-1;
	printf("\n===["C_CIANO"Menu Ricerca Avanzata"C_RESET"]===");
	printf("\n[1] Mostra tutte le "C_CIANO"informazioni"C_RESET" in base ad un criterio");
	printf("\n[2] Ricerca "C_CIANO"brani"C_RESET" in base ad un criterio");
	printf("\n[3] Ricerca "C_CIANO"informazioni"C_RESET" in base ad un criterio");
	printf("\n[4] Mostra le "C_CIANO"playlist"C_RESET C_VERDE" pubbliche"C_RESET);
	printf("\n[5] Mostra le "C_CIANO"playlist"C_RESET C_VERDE" pubbliche ed i loro brani"C_RESET);
	printf("\n[6] Mostra "C_CIANO"testo"C_RESET" di un brano");
	printf("\n[7] Mostra "C_CIANO"biografia"C_RESET" di un artista");
	printf("\n[8] "C_CIANO"Stampare su File"C_RESET" la libreria dei brani di Ampere");
	printf("\n[0] "C_BLU"Ritorna al menu principale"C_RESET);
	while (scelta<0||scelta>8) {
		printf("\n"C_VERDE"Inserisci la tua scelta"C_RESET": ");
		scelta = inputNumero();
	}
	if (scelta==1) {
		menuRicercaInfo(db);
	} else if (scelta==2) {
		menuRicercaBraniCriterio(db);
	} else if (scelta==3) {
		menuRicercaInfoCriterio(db);
	} else if (scelta==4) {
		mostrareTuttePlaylistPubbliche(db, -1);
		aspetta();
		menuRicercaAvanzata(db);
	} else if (scelta==5) {
		mostrareTuttePlaylistPubbliche(db, 0);
		aspetta();
		menuRicercaAvanzata(db);
	} else if (scelta==6) {
		apriTestoDaRicerca(db);
		aspetta();
		menuRicercaAvanzata(db);
	} else if (scelta==7) {
		visualizzareBiografiaArtista(db);
		aspetta();
		menuRicercaAvanzata(db);
	} else if (scelta==8) {
		stampareBraniGuidato(db);
		aspetta();
		menuRicercaAvanzata(db);
	} else if (scelta==0) {
		menu(db);
	} else {
		attenzione(20);
		menuRicercaAvanzata(db);
	}
}

void menuRicercaInfo(database *db) {
	
	int scelta=-1;
	printf("\n===["C_CIANO"Menu Ricerca su Criterio"C_RESET"]===");
	printf("\n[1] Tutti i "C_CIANO"brani"C_RESET);
	printf("\n[2] Tutti gli "C_CIANO"artisti"C_RESET);
	printf("\n[3] Tutti gli "C_CIANO"album"C_RESET);
	printf("\n[4] Tutti i "C_CIANO"generi"C_RESET);
	printf("\n[5] Tutte le tue "C_CIANO"playlist"C_RESET);
	if (controllareSeAdmin(db)) {
		printf("\n[6] "C_ROSSO"Tutte le playlist"C_RESET);
		printf("\n[7] "C_ROSSO"Tutti gli utenti"C_RESET);
	}
	printf("\n[0] "C_BLU"Ritorna al menu precedente"C_RESET);
	while (scelta<0||scelta>7) {
		printf("\n"C_VERDE"Inserisci la tua scelta"C_RESET": ");
		scelta = inputNumero();
	}
	if (scelta==1) {
		mostrareTuttiBrani(db);
		aspetta();
		menuRicercaInfo(db);
	} else if (scelta==2) {
		mostrareTuttiArtisti(db);
		aspetta();
		menuRicercaInfo(db);
	} else if (scelta==3) {
		mostrareTuttiAlbum(db);
		aspetta();
		menuRicercaInfo(db);
	} else if (scelta==4) {
		mostrareTuttiGeneri(db);
		aspetta();
		menuRicercaInfo(db);
	} else if (scelta==5) {
		mostrarePlaylistUtente(db, 0, db->utenteCorrente);
		aspetta();
		menuRicercaInfo(db);
	} else if (scelta==6) {
		if (controllareSeAdmin(db)) {
			mostrareTuttePlaylist(db, 0);
			aspetta();
			menuRicercaInfo(db);
		} else {
			errore(16);
		}
	} else if (scelta==7) {
		if (controllareSeAdmin(db)) {
			mostrareTuttiUtenti(db);
			aspetta();
			menuRicercaInfo(db);
		} else {
			errore(16);
		}
	} else if (scelta==0) {
		menuRicercaAvanzata(db);
	} else {
		attenzione(20);
		menuRicercaInfo(db);
	}
}

void menuRicercaBraniCriterio(database *db) {
	
	int scelta=-1;
	printf("\n===["C_CIANO"Menu Ricerca Brani su Criterio]===");
	printf("\n[1] Ricerca brani in base al "C_CIANO"titolo"C_RESET);
	printf("\n[2] Ricerca brani in base all'"C_CIANO"anno di uscita"C_RESET);
	printf("\n[3] Ricerca brani in base all'"C_CIANO"artista"C_RESET);
	printf("\n[4] Ricerca brani in base all'"C_CIANO"album"C_RESET);
	printf("\n[5] Ricerca brani in base al "C_CIANO"genere"C_RESET);
	printf("\n[6] Ricerca brani in base alla "C_CIANO"playlist"C_RESET);
	printf("\n[0] "C_BLU"Ritorna al menu precedente"C_RESET);
	while (scelta<0||scelta>6) {
		printf("\n"C_VERDE"Inserisci la tua scelta"C_RESET": ");
		scelta = inputNumero();
	}
	if (scelta==1) {
		ricercareBrani(db, 0);
		aspetta();
		menuRicercaBraniCriterio(db);
	} else if (scelta==2) {
		ricercareBrani(db, 1);
		aspetta();
		menuRicercaBraniCriterio(db);
	} else if (scelta==3) {
		ricercareBraniArtista(db);
		aspetta();
		menuRicercaBraniCriterio(db);
	} else if (scelta==4) {
		ricercareBraniAlbum(db);
		aspetta();
		menuRicercaBraniCriterio(db);
	} else if (scelta==5) {
		ricercareBraniGenere(db);
		aspetta();
		menuRicercaBraniCriterio(db);
	} else if (scelta==6) {
		ricercareBraniPlaylist(db);
		aspetta();
		menuRicercaBraniCriterio(db);
	} else if (scelta==0) {
		menuRicercaAvanzata(db);
	} else {
		attenzione(20);
		menuRicercaBraniCriterio(db);
	}
}

void menuRicercaInfoCriterio(database *db) {
	
	int scelta=-1, esiste=0;
	printf("\n===["C_CIANO"Menu Ricerca Info su Criterio"C_RESET"]===");
	printf("\n[1] Ricerca info su un "C_CIANO"Artista"C_RESET);
	printf("\n[2] Ricerca info su un "C_CIANO"Album"C_RESET);
	printf("\n[3] Ricerca info su un "C_CIANO"Genere"C_RESET);
	printf("\n[4] Ricerca info su una "C_CIANO"playlist"C_RESET);
	if (controllareSeAdmin(db)) {
		printf("\n[5] "C_ROSSO"Ricerca info su un Utente"C_RESET);
	}
	printf("\n[0] "C_BLU"Ritorna al menu precedente"C_RESET);
	while (scelta<0||scelta>5) {
		printf("\n"C_VERDE"Inserisci la tua scelta"C_RESET": ");
		scelta = inputNumero();
	}
	if (scelta==1) {
		do {
			esiste = ricercareInfo(db, 0);
			if (esiste==0) {
				attenzione(101);
			}
		} while (esiste==0);
		aspetta();
		menuRicercaInfoCriterio(db);
	} else if (scelta==2) {
		do {
			esiste = ricercareInfo(db, 1);
			if (esiste==0) {
				attenzione(101);
			}
		} while (esiste==0);
		aspetta();
		menuRicercaInfoCriterio(db);
	} else if (scelta==3) {
		do {
			esiste = ricercareInfo(db, 2);
			if (esiste==0) {
				attenzione(101);
			}
		} while (esiste==0);
		aspetta();
		menuRicercaInfoCriterio(db);
	} else if (scelta==4) {
		do {
			esiste = ricercareInfo(db, 3);
			if (esiste==0) {
				attenzione(101);
			}
		} while (esiste==0);
		aspetta();
		menuRicercaInfoCriterio(db);
	} else if (scelta==5) {
		if (controllareSeAdmin(db)) {
			do {
				esiste = ricercareInfo(db, 4);
				if (esiste==0) {
					attenzione(101);
				}
			} while (esiste==0);
			aspetta();
			menuRicercaInfoCriterio(db);
		} else {
			errore(16);
		}
	} else if (scelta==0) {
		menuRicercaAvanzata(db);
	} else {
		attenzione(20);
		menuRicercaInfoCriterio(db);
	}
}

void menuDebug(database *db) {
	
	int scelta=-1;
	printf("\n===[Menu Debug]===");
	printf("\n[1] Funzione di debug on the fly");
	printf("\n[0] "C_BLU"Ritorna al menu principale"C_RESET);
	while (scelta<0||scelta>5) {
		printf("\n"C_VERDE"Inserisci la tua scelta"C_RESET": ");
		scelta = inputNumero();
	}
	if (scelta==1) {
		aspetta();
		menuDebug(db);
	} else if (scelta==0) {
		menu(db);
	} else {
		attenzione(20);
		menuDebug(db);
	}
	
}
