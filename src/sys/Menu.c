/*
 * Ampere 0.1 rev. 2040 - 06.05.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void menuLogin() {
	int scelta=0;
	pulisciBuffer();
	printf("\nDesideri effettuare il login[0] o registrarti[1] ad Ampere? ");
	scanf("%d", &scelta);
	if (scelta==0) {
		login();
	} else {
		registrazioneUtente();
	}
}

// Nuovo Menu di Ampere
void menu() {
	pulisciBuffer();
	int scelta=0;
	printf("\n===[AMPERE: Menu Principale]===");
	printf("\n[1] Menu di Ricerca");
	if (isAdmin()==true)
		printf("\n[9] Menu Manipolazione Database");
	printf("\n[0] Esci dal programma");
	printf("\nInserisci la tua scelta: ");
	scanf("%d", &scelta);
	if (scelta==1) {
		menuRicerca();
	} else if (scelta==9) {
		menuDatabase();
	} else if (scelta==0) {
		printf("\nUscendo dal programma...\n");
	} else {
		printf("\nInserita scelta non riconosciuta, riprovare. ");
		menu();
	}
}

void menuDatabase() {
	pulisciBuffer();
	int scelta=0;
	printf("\n===[AMPERE: Menu Database]===");
	printf("\n[1] Inserisci nel database");
	printf("\n[2] Cancella nel database");
	printf("\n[3] Modifica nel database");
	printf("\n[4] Effettua un backup del database");
	printf("\n[5] Effettua un ripristino del database da un backup");
	printf("\n[0] Ritorna al menu principale");
	printf("\nInserisci la tua scelta: ");
	scanf("%d", &scelta);
	if (scelta==1) {
		menuDBInserimento();
	} else if (scelta==2) {
		menuDBCancella();
	} else if (scelta==3) {
		menuDBModifica();
	} else if (scelta==4) {
		backupDatabase();
		aspetta();
		menuDatabase();
	} else if (scelta==5) {
		ripristinaDatabase();
		aspetta();
		menuDatabase();
	} else if (scelta==0) {
		menu();
	} else {
		printf("\nInserita scelta non riconosciuta, riprovare. ");
		menuDatabase();
	}
}

void menuDBInserimento() {
	pulisciBuffer();
	int scelta=0;
	printf("\n===[Menu di Inserimento nel Database]===");
	printf("\n[1] Inserisci un brano");
	printf("\n[2] Inserisci un artista");
	printf("\n[3] Inserisci un album");
	printf("\n[4] Inserisci un genere");
	printf("\n[0] Ritorna al menu precedente");
	printf("\nInserisci la tua scelta: ");
	scanf("%d", &scelta);
	if (scelta==1) {
		inserimentoBranoGuidato();
		aspetta();
		menuDBInserimento();
	} else if (scelta==2) {
		inserimentoArtistaGuidato();
		aspetta();
		menuDBInserimento();
	} else if (scelta==3) {
		inserimentoAlbumGuidato();
		aspetta();
		menuDBInserimento();
	} else if (scelta==4) {
		inserimentoGenereGuidato();
		aspetta();
		menuDBInserimento();
	} else if (scelta==0) {
		menuDatabase();
	} else {
		printf("\nInserita scelta non riconosciuta, riprovare. ");
		menuDBInserimento();
	}
}

void menuDBModifica() {
	pulisciBuffer();
	int scelta=0;
	printf("\n===[Menu di Modifica nel Database]===");
	printf("\n[1] Modifica un brano");
	printf("\n[2] Modifica un artista");
	printf("\n[3] Modifica un album");
	printf("\n[4] Modifica un genere");
	printf("\n[0] Ritorna al menu precedente");
	printf("\nInserisci la tua scelta: ");
	scanf("%d", &scelta);
	if (scelta==1) {
		modificaBrano();
		aspetta();
		menuDBModifica();
	} else if (scelta==2) {
		modificaArtista();
		aspetta();
		menuDBModifica();
	} else if (scelta==3) {
		modificaAlbum();
		aspetta();
		menuDBModifica();
	} else if (scelta==4) {
		modificaGenere();
		aspetta();
		menuDBModifica();
	} else if (scelta==0) {
		menuDatabase();
	} else {
		printf("\nInserita scelta non riconosciuta, riprovare. ");
		menuDBModifica();
	}
}

void menuDBCancella() {
	pulisciBuffer();
	int scelta=0;
	printf("\n===[Menu di Cancellazione nel Database]===");
	printf("\n[1] Cancella un brano");
	printf("\n[2] Cancella un artista");
	printf("\n[3] Cancella un album");
	printf("\n[4] Cancella un genere");
	printf("\n[0] Ritorna al menu precedente");
	printf("\nInserisci la tua scelta: ");
	scanf("%d", &scelta);
	if (scelta==1) {
		cancellaBrano();
		aspetta();
		menuDBCancella();
	} else if (scelta==2) {
		cancellaArtista();
		aspetta();
		menuDBCancella();
	} else if (scelta==3) {
		cancellaAlbum();
		aspetta();
		menuDBCancella();
	} else if (scelta==4) {
		cancellaGenere();
		aspetta();
		menuDBCancella();
	} else if (scelta==0) {
		menuDatabase();
	} else {
		printf("\nInserita scelta non riconosciuta, riprovare. ");
		menuDBCancella();
	}
}

void menuRicerca() {
	pulisciBuffer();
	int scelta=0;
	printf("\n===[Menu Ricerca]===");
	printf("\n[1] Mostra tutte le info in base ad un criterio");
	printf("\n[2] Ricerca brani in base ad un criterio");
	printf("\n[3] Ricerca info in base ad un criterio");
	printf("\n[4] TEST Ricerca Generale");
	printf("\n[0] Ritorna al menu principale");
	printf("\nInserisci la tua scelta: ");
	scanf("%d", &scelta);
	if (scelta==1) {
		menuRicercaInfo();
		aspetta();
		menuRicerca();
	} else if (scelta==2) {
		menuRicercaBraniCriterio();
		aspetta();
		menuRicerca();
	} else if (scelta==3) {
		menuRicercaInfoCriterio();
		aspetta();
		menuRicerca();
	} else if (scelta==4) {
		eseguiRicerca();
		aspetta();
		menuRicerca();
	} else if (scelta==0) {
		menu();
	} else {
		printf("\nInserita scelta non riconosciuta, riprovare. ");
		menuRicerca();
	}
}

void menuRicercaInfo() {
	pulisciBuffer();
	int scelta=0;
	printf("\n===[Menu Ricerca su Criterio]===");
	printf("\n[1] Mostra info su tutti i brani");
	printf("\n[2] Mostra info su tutti gli artisti");
	printf("\n[3] Mostra info su tutti gli album");
	printf("\n[4] Mostra info su tutti i generi");
	printf("\n[0] Ritorna al menu precedente");
	printf("\nInserisci la tua scelta: ");
	scanf("%d", &scelta);
	if (scelta==1) {
		mostraTuttiBrani();
		aspetta();
		menuRicercaInfo();
	} else if (scelta==2) {
		mostraTuttiArtisti();
		aspetta();
		menuRicercaInfo();
	} else if (scelta==3) {
		mostraTuttiAlbum();
		aspetta();
		menuRicercaInfo();
	} else if (scelta==4) {
		mostraTuttiGeneri();
		aspetta();
		menuRicercaInfo();
	} else if (scelta==0) {
		menuRicerca();
	} else {
		printf("\nInserita scelta non riconosciuta, riprovare. ");
		menuRicercaInfo();
	}
}

void menuRicercaBraniCriterio() {
	pulisciBuffer();
	int scelta=0;
	printf("\n===[Menu Ricerca Brani su Criterio]===");
	printf("\n[1] Ricerca brani in base al titolo");
	printf("\n[2] Ricerca brani in base all'anno di uscita");
	printf("\n[3] Ricerca brani in base all'Artista");
	printf("\n[4] Ricerca brani in base all'Album");
	printf("\n[5] Ricerca brani in base al Genere");
	printf("\n[0] Ritorna al menu precedente");
	printf("\nInserisci la tua scelta: ");
	scanf("%d", &scelta);
	if (scelta==1) {
		mostraBrani(0);
		aspetta();
		menuRicercaBraniCriterio();
	} else if (scelta==2) {
		mostraBrani(1);
		aspetta();
		menuRicercaBraniCriterio();
	} else if (scelta==3) {
		mostraBraniArtista();
		aspetta();
		menuRicercaBraniCriterio();
	} else if (scelta==4) {
		mostraBraniAlbum();
		aspetta();
		menuRicercaBraniCriterio();
	} else if (scelta==5) {
		mostraBraniGenere();
		aspetta();
		menuRicercaBraniCriterio();
	} else if (scelta==0) {
		menuRicerca();
	} else {
		printf("\nInserita scelta non riconosciuta, riprovare. ");
		menuRicercaBraniCriterio();
	}
}

void menuRicercaInfoCriterio() {
	pulisciBuffer();
	int scelta=0;
	printf("\n===[Menu Ricerca Info su Criterio]===");
	printf("\n[1] Ricerca info su un Artista");
	printf("\n[2] Ricerca info su un Album");
	printf("\n[3] Ricerca info su un Genere");
	printf("\n[0] Ritorna al menu precedente");
	printf("\nInserisci la tua scelta: ");
	scanf("%d", &scelta);
	if (scelta==1) {
		mostraInfo(0);
		aspetta();
		menuRicercaInfoCriterio();
	} else if (scelta==2) {
		mostraInfo(1);
		aspetta();
		menuRicercaInfoCriterio();
	} else if (scelta==3) {
		mostraInfo(2);
		aspetta();
		menuRicercaInfoCriterio();
	} else if (scelta==0) {
		menuRicerca();
	} else {
		printf("\nInserita scelta non riconosciuta, riprovare. ");
		menuRicercaInfoCriterio();
	}
}


