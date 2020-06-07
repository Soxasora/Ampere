/*
 * Ampere 0.2.1 rev.1 - 04.06.2020
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
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

database menuLogin(database db) {
	printf("\n===[ESECUZIONE LOGIN AD AMPERE]===");
	int scelta=-1;
	while (scelta<0||scelta>1) {
		printf("\nDesideri effettuare: il "C_VERDE"Login[0]"C_RESET" oppure "C_GIALLO"Registrarti[1]"C_RESET" ad Ampere? ");
		scelta = inputNumero();
	}
	if (scelta==0) {
		db = loginUtente(db);
	} else {
		db = registrareUtente(db);
	}
	return db;
}

// Nuovo Menu di Ampere
database menu(database db) {
	////pulisciBuffer();
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
		eseguiRicerca(db);
		aspetta();
		db = menu(db);
	} else if (scelta==2) {
		menuRicercaAvanzata(db);
	} else if (scelta==3) {
		db = menuPlaylist(db);
	} else if (scelta==4) {
		db = menuAccount(db);
	} else if (scelta==9) {
		if (controllareSeAdmin(db))
			db = menuDatabase(db);
		else
			errore(16);
	} else if (scelta==10) {
		if (controllareSeAdmin(db))
			db = menuDebug(db);
		else
			errore(16);
	} else if (scelta==0) {
		printf("\nUscendo dal programma...\n");
	} else {
		attenzione(20);
		db = menu(db);
	}
	return db;
}

database menuAccount(database db) {
	//pulisciBuffer();
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
		db = modificareUtenteGuidato(db);
		aspetta();
		menuAccount(db);
	} else if (scelta==2) {
		db = cancellareUtenteGuidato(db);
		printf("\nPer rendere effettive le modifiche, ora chiudero' Ampere.");
		aspetta();
		terminazione(db);
		exit(0);
	} else if (scelta==0) {
		db = menu(db);
	} else {
		attenzione(20);
		db = menuAccount(db);
	}
	return db;
}

database menuPlaylist(database db) {
	//pulisciBuffer();
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
		mostraPlaylistUtente(db, 0,db.utenteCorrente);
		aspetta();
		db = menuPlaylist(db);
	} else if (scelta==2) {
		db = crearePlaylistGuidato(db);
		aspetta();
		db = menuPlaylist(db);
	} else if (scelta==3) {
		db = inserimentoBraniPlaylistGuidato(db);
		aspetta();
		db = menuPlaylist(db);
	} else if (scelta==4) {
		db = modificarePlaylistGuidato(db);
		aspetta();
		db = menuPlaylist(db);
	} else if (scelta==5) {
		db = cancellaPlaylist(db);
		aspetta();
		db = menuPlaylist(db);
	} else if (scelta==0) {
		db = menu(db);
	} else {
		attenzione(20);
		db = menuPlaylist(db);
	}
	return db;
}

database menuDatabase(database db) {
	//pulisciBuffer();
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
		db = menuDBInserimento(db);
	} else if (scelta==2) {
		db = menuDBCancella(db);
	} else if (scelta==3) {
		db = menuDBModifica(db);
	} else if (scelta==4) {
		backupDatabase();
		aspetta();
		db = menuDatabase(db);
	} else if (scelta==5) {
		db = ripristinaDatabase(db);
		printf("\nPer rendere effettive le modifiche, ora chiudero' Ampere.");
		aspetta();
		terminazione(db);
		exit(0);
	} else if (scelta==0) {
		db = menu(db);
	} else {
		attenzione(20);
		db = menuDatabase(db);
	}
	return db;
}

database menuDBInserimento(database db) {
	////pulisciBuffer();
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
		db = inserimentoBranoGuidato(db);
		aspetta();
		db = menuDBInserimento(db);
	} else if (scelta==2) {
		db = inserimentoArtistaGuidato(db);
		aspetta();
		db = menuDBInserimento(db);
	} else if (scelta==3) {
		db = inserimentoAlbumGuidato(db);
		aspetta();
		db = menuDBInserimento(db);
	} else if (scelta==4) {
		db = inserireGenereGuidato(db);
		aspetta();
		db = menuDBInserimento(db);
	} else if (scelta==5) {
		db = registrareUtente(db);
		aspetta();
		db = menuDBInserimento(db);
	} else if (scelta==0) {
		db = menuDatabase(db);
	} else {
		attenzione(20);
		db = menuDBInserimento(db);
	}
	return db;
}

database menuDBModifica(database db) {
	////pulisciBuffer();
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
		db = modificareBranoGuidato(db);
		aspetta();
		db = menuDBModifica(db);
	} else if (scelta==2) {
		db = modificareArtistaGuidato(db);
		aspetta();
		db = menuDBModifica(db);
	} else if (scelta==3) {
		db = modificareAlbumGuidato(db);
		aspetta();
		db = menuDBModifica(db);
	} else if (scelta==4) {
		db = modificareGenereGuidato(db);
		aspetta();
		db = menuDBModifica(db);
	} else if (scelta==5) {
		db = modificarePlaylistGuidato(db);
		aspetta();
		db = menuDBModifica(db);
	} else if (scelta==6) {
		db = modificareUtenteGuidato(db);
		aspetta();
		db = menuDBModifica(db);
	} else if (scelta==0) {
		db = menuDatabase(db);
	} else {
		attenzione(20);
		db = menuDBModifica(db);
	}
	return db;
}

database menuDBCancella(database db) {
	////pulisciBuffer();
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
		db = cancellaBrano(db);
		aspetta();
		db = menuDBCancella(db);
	} else if (scelta==2) {
		db = cancellaArtista(db);
		aspetta();
		db = menuDBCancella(db);
	} else if (scelta==3) {
		db = cancellaAlbum(db);
		aspetta();
		db = menuDBCancella(db);
	} else if (scelta==4) {
		db = cancellareGenereGuidato(db);
		aspetta();
		db = menuDBCancella(db);
	} else if (scelta==5) {
		db = cancellaPlaylist(db);
		aspetta();
		db = menuDBCancella(db);
	} else if (scelta==6) {
		db = cancellareUtenteGuidato(db);
		aspetta();
		db = menuDBCancella(db);
	} else if (scelta==0) {
		db = menuDatabase(db);
	} else {
		attenzione(20);
		db = menuDBCancella(db);
	}
	return db;
}

void menuRicercaAvanzata(database db) {
	////pulisciBuffer();
	int scelta=-1;
	printf("\n===["C_CIANO"Menu Ricerca Avanzata"C_RESET"]===");
	printf("\n[1] Mostra tutte le "C_CIANO"informazioni"C_RESET" in base ad un criterio");
	printf("\n[2] Ricerca "C_CIANO"brani"C_RESET" in base ad un criterio");
	printf("\n[3] Ricerca "C_CIANO"informazioni"C_RESET" in base ad un criterio");
	printf("\n[4] Mostra le "C_CIANO"playlist"C_RESET C_VERDE" pubbliche"C_RESET);
	printf("\n[5] Mostra le "C_CIANO"playlist"C_RESET C_VERDE" pubbliche ed i loro brani"C_RESET);
	printf("\n[6] Mostra "C_CIANO"testo"C_RESET" di un brano");
	printf("\n[7] Mostra "C_CIANO"biografia"C_RESET" di un artista");
	printf("\n[0] "C_BLU"Ritorna al menu principale"C_RESET);
	while (scelta<0||scelta>7) {
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
		mostraTuttePlaylistPubbliche(db, -1);
		aspetta();
		menuRicercaAvanzata(db);
	} else if (scelta==5) {
		mostraTuttePlaylistPubbliche(db, 0);
		aspetta();
		menuRicercaAvanzata(db);
	} else if (scelta==6) {
		apriTestoDaRicerca(db);
		aspetta();
		menuRicercaAvanzata(db);
	} else if (scelta==7) {
		visualizzaBiografiaArtista(db);
		aspetta();
		menuRicercaAvanzata(db);
	} else if (scelta==0) {
		menu(db);
	} else {
		attenzione(20);
		menuRicercaAvanzata(db);
	}
}

void menuRicercaInfo(database db) {
	//pulisciBuffer();
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
		mostraTuttiBrani(db);
		aspetta();
		menuRicercaInfo(db);
	} else if (scelta==2) {
		mostraTuttiArtisti(db);
		aspetta();
		menuRicercaInfo(db);
	} else if (scelta==3) {
		mostraTuttiAlbum(db);
		aspetta();
		menuRicercaInfo(db);
	} else if (scelta==4) {
		mostraTuttiGeneri(db);
		aspetta();
		menuRicercaInfo(db);
	} else if (scelta==5) {
		mostraPlaylistUtente(db, 0, db.utenteCorrente);
		aspetta();
		menuRicercaInfo(db);
	} else if (scelta==6) {
		if (controllareSeAdmin(db)) {
			mostraTuttePlaylist(db, 0);
			aspetta();
			menuRicercaInfo(db);
		} else {
			errore(16);
		}
	} else if (scelta==7) {
		if (controllareSeAdmin(db)) {
			mostraTuttiUtenti(db);
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

void menuRicercaBraniCriterio(database db) {
	//pulisciBuffer();
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
		mostraBrani(db, 0);
		aspetta();
		menuRicercaBraniCriterio(db);
	} else if (scelta==2) {
		mostraBrani(db, 1);
		aspetta();
		menuRicercaBraniCriterio(db);
	} else if (scelta==3) {
		mostraBraniArtista(db);
		aspetta();
		menuRicercaBraniCriterio(db);
	} else if (scelta==4) {
		mostraBraniAlbum(db);
		aspetta();
		menuRicercaBraniCriterio(db);
	} else if (scelta==5) {
		mostraBraniGenere(db);
		aspetta();
		menuRicercaBraniCriterio(db);
	} else if (scelta==6) {
		mostraBraniPlaylist(db);
		aspetta();
		menuRicercaBraniCriterio(db);
	} else if (scelta==0) {
		menuRicercaAvanzata(db);
	} else {
		attenzione(20);
		menuRicercaBraniCriterio(db);
	}
}

void menuRicercaInfoCriterio(database db) {
	//pulisciBuffer();
	int scelta=-1;
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
		mostraInfo(db, 0);
		aspetta();
		menuRicercaInfoCriterio(db);
	} else if (scelta==2) {
		mostraInfo(db, 1);
		aspetta();
		menuRicercaInfoCriterio(db);
	} else if (scelta==3) {
		mostraInfo(db, 2);
		aspetta();
		menuRicercaInfoCriterio(db);
	} else if (scelta==4) {
		mostraInfo(db, 3);
		aspetta();
		menuRicercaInfoCriterio(db);
	} else if (scelta==5) {
		if (controllareSeAdmin(db)) {
			mostraInfo(db, 4);
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

database menuDebug(database db) {
	//pulisciBuffer();
	int scelta=-1;
	printf("\n===[Menu Debug]===");
	printf("\n[1] Funzione di debug on the fly");
	printf("\n[0] "C_BLU"Ritorna al menu principale"C_RESET);
	while (scelta<0||scelta>5) {
		printf("\n"C_VERDE"Inserisci la tua scelta"C_RESET": ");
		scelta = inputNumero();
	}
	if (scelta==1) {
		cPrintf(C_BLU,"prova");
		aspetta();
		menuDebug(db);
	} else if (scelta==0) {
		menu(db);
	} else {
		attenzione(20);
		menuDebug(db);
	}
	return db;
}
