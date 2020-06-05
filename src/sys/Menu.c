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
	int scelta=-1;
	while (scelta<0||scelta>1) {
		printf("\nDesideri effettuare il "C_VERDE"login[0]"C_RESET" o "C_GIALLO"registrarti[1]"C_RESET" ad Ampere? ");
		scanf("%d", &scelta);
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
	pulisciBuffer();
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
		printf("\nInserisci la tua scelta: ");
		scanf("%d", &scelta);
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
	pulisciBuffer();
	int scelta=-1;
	printf("\n===[Menu Account]===");
	printf("\n[1] Modifica il tuo account");
	printf("\n[2] Cancella il tuo account");
	printf("\n[0] Ritorna al menu precedente");
	while (scelta<0||scelta>2) {
		printf("\nInserisci la tua scelta: ");
		scanf("%d", &scelta);
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
	pulisciBuffer();
	int scelta=-1;
	printf("\n===[Menu Playlist]===");
	printf("\n[1] Le mie playlist");
	printf("\n[2] Crea playlist");
	printf("\n[3] Inserisci brani in una playlist");
	printf("\n[4] Modifica playlist");
	printf("\n[5] Cancella playlist");
	printf("\n[0] Ritorna al menu precedente");
	while (scelta<0||scelta>6) {
		printf("\nInserisci la tua scelta: ");
		scanf("%d", &scelta);
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
	pulisciBuffer();
	int scelta=-1;
	printf("\n===[AMPERE: Menu Database]===");
	printf("\n[1] Inserisci nel database");
	printf("\n[2] Cancella nel database");
	printf("\n[3] Modifica nel database");
	printf("\n[4] Effettua un backup del database");
	printf("\n[5] Effettua un ripristino del database da un backup");
	printf("\n[0] Ritorna al menu principale");
	while (scelta<0||scelta>5) {
		printf("\nInserisci la tua scelta: ");
		scanf("%d", &scelta);
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
	pulisciBuffer();
	int scelta=-1;
	printf("\n===[Menu di Inserimento nel Database]===");
	printf("\n[1] Inserisci un brano");
	printf("\n[2] Inserisci un artista");
	printf("\n[3] Inserisci un album");
	printf("\n[4] Inserisci un genere");
	printf("\n[5] Inserisci un utente");
	printf("\n[0] Ritorna al menu precedente");
	while (scelta<0||scelta>5) {
		printf("\nInserisci la tua scelta: ");
		scanf("%d", &scelta);
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
	pulisciBuffer();
	int scelta=-1;
	printf("\n===[Menu di Modifica nel Database]===");
	printf("\n[1] Modifica un brano");
	printf("\n[2] Modifica un artista");
	printf("\n[3] Modifica un album");
	printf("\n[4] Modifica un genere");
	printf("\n[5] Modifica una playlist");
	printf("\n[6] Modifica un utente");
	printf("\n[0] Ritorna al menu precedente");
	while (scelta<0||scelta>6) {
		printf("\nInserisci la tua scelta: ");
		scanf("%d", &scelta);
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
	pulisciBuffer();
	int scelta=-1;
	printf("\n===[Menu di Cancellazione nel Database]===");
	printf("\n[1] Cancella un brano");
	printf("\n[2] Cancella un artista");
	printf("\n[3] Cancella un album");
	printf("\n[4] Cancella un genere");
	printf("\n[5] Cancella una playlist");
	printf("\n[6] Cancella un utente");
	printf("\n[0] Ritorna al menu precedente");
	while (scelta<0||scelta>6) {
		printf("\nInserisci la tua scelta: ");
		scanf("%d", &scelta);
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
	pulisciBuffer();
	int scelta=-1;
	printf("\n===[Menu Ricerca Avanzata]===");
	printf("\n[1] Mostra tutte le info in base ad un criterio");
	printf("\n[2] Ricerca brani in base ad un criterio");
	printf("\n[3] Ricerca info in base ad un criterio");
	printf("\n[4] Mostra le playlist pubbliche");
	printf("\n[5] Mostra le playlist pubbliche ed i loro brani");
	printf("\n[6] Mostra testo di un brano");
	printf("\n[7] Mostra biografia di un artista");
	printf("\n[0] Ritorna al menu principale");
	while (scelta<0||scelta>7) {
		printf("\nInserisci la tua scelta: ");
		scanf("%d", &scelta);
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
	pulisciBuffer();
	int scelta=-1;
	printf("\n===[Menu Ricerca su Criterio]===");
	printf("\n[1] Mostra info su tutti i brani");
	printf("\n[2] Mostra info su tutti gli artisti");
	printf("\n[3] Mostra info su tutti gli album");
	printf("\n[4] Mostra info su tutti i generi");
	printf("\n[5] Mostra info su tutte le tue playlist");
	if (controllareSeAdmin(db)) {
		printf("\n[6] Mostra info su tutte le playlist");
		printf("\n[7] Mostra info su tutti gli utenti");
	}
	printf("\n[0] Ritorna al menu precedente");
	while (scelta<0||scelta>7) {
		printf("\nInserisci la tua scelta: ");
		scanf("%d", &scelta);
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
	pulisciBuffer();
	int scelta=-1;
	printf("\n===[Menu Ricerca Brani su Criterio]===");
	printf("\n[1] Ricerca brani in base al titolo");
	printf("\n[2] Ricerca brani in base all'anno di uscita");
	printf("\n[3] Ricerca brani in base all'artista");
	printf("\n[4] Ricerca brani in base all'album");
	printf("\n[5] Ricerca brani in base al genere");
	printf("\n[6] Ricerca brani in base alla playlist");
	printf("\n[0] Ritorna al menu precedente");
	while (scelta<0||scelta>6) {
		printf("\nInserisci la tua scelta: ");
		scanf("%d", &scelta);
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
	pulisciBuffer();
	int scelta=-1;
	printf("\n===[Menu Ricerca Info su Criterio]===");
	printf("\n[1] Ricerca info su un Artista");
	printf("\n[2] Ricerca info su un Album");
	printf("\n[3] Ricerca info su un Genere");
	printf("\n[4] Ricerca info su una playlist");
	if (controllareSeAdmin(db)) {
		printf("\n[5] Ricerca info su un Utente");
	}
	printf("\n[0] Ritorna al menu precedente");
	while (scelta<0||scelta>5) {
		printf("\nInserisci la tua scelta: ");
		scanf("%d", &scelta);
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
	pulisciBuffer();
	int scelta=-1;
	printf("\n===[AMPERE: Menu Debug]===");
	printf("\n[1] Funzione di debug on the fly");
	printf("\n[0] Ritorna al menu principale");
	while (scelta<0||scelta>5) {
		printf("\nInserisci la tua scelta: ");
		scanf("%d", &scelta);
	}
	if (scelta==1) {
		//TODO
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
