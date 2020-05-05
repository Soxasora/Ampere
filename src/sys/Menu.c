/*
 * Ampere 0.1 rev. 1250 - 04.05.2020
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
	printf("\nUtente connesso: %s", db.utente[ottieniPosDaID(-1, db.utente_connesso)].username);
	printf("\nRuolo utente: ");
	if (isAdmin()==true) {
		printf("Amministratore");
	} else {
		printf("Utente normale");
	}
	printf("\n[1] Menu di Ricerca");
	if (isAdmin()==true)
		printf("\n[9] [ADMIN] Menu Manipolazione Database");
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
	// Creare sottomenu di inserimento
	printf("\n[1] Inserisci un brano nel database");
	printf("\n[2] Inserisci un artista nel database");
	printf("\n[3] Inserisci un album nel database");
	printf("\n[4] Inserisci un genere nel database");
	// Creare sottomenu di modifica
	printf("\n[5] Modifica un brano");
	printf("\n[6] Modifica un artista");
	printf("\n[7] Modifica un album");
	printf("\n[8] Modifica un genere");
	// Creare sottomenu di cancellazione
	printf("\n[9] Cancella un brano");
	printf("\n[10] Cancella un artista");
	printf("\n[11] Cancella un album");
	printf("\n[12] Cancella un genere");
	printf("\n[13] TODO Cancella l'intera libreria musicale");
	// Creare sottomenu di backup
	printf("\n[14] Effettua un backup del database");
	printf("\n[15] Effettua un ripristino del database da un backup");
	printf("\n[0] Ritorna al menu principale");
	printf("\nInserisci la tua scelta: ");
	scanf("%d", &scelta);
	if (scelta==1) {
		inserimentoBranoGuidato();
		aspetta();
		menuDatabase();
	} else if (scelta==2) {
		inserimentoArtistaGuidato();
		aspetta();
		menuDatabase();
	} else if (scelta==3) {
		inserimentoAlbumGuidato();
		aspetta();
		menuDatabase();
	} else if (scelta==4) {
		inserimentoGenereGuidato();
		aspetta();
		menuDatabase();
	} else if (scelta==5) {
		modificaBrano();
		aspetta();
		menuDatabase();
	} else if (scelta==6) {
		modificaArtista();
		aspetta();
		menuDatabase();
	} else if (scelta==7) {
		modificaAlbum();
		aspetta();
		menuDatabase();
	} else if (scelta==8) {
		modificaGenere();
		aspetta();
		menuDatabase();
	} else if (scelta==9) {
		cancellaBrano();
		aspetta();
		menuDatabase();
	} else if (scelta==10) {
		cancellaArtista();
		aspetta();
		menuDatabase();
	} else if (scelta==11) {
		cancellaAlbum();
		aspetta();
		menuDatabase();
	} else if (scelta==12) {
		cancellaGenere();
		aspetta();
		menuDatabase();
	} else if (scelta==13) {
		//TODO
	} else if (scelta==14) {
		backupDatabase();
		aspetta();
		menuDatabase();
	} else if (scelta==15) {
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

void menuRicerca() {
	pulisciBuffer();
	int scelta=0;
	printf("\n===[Menu Ricerca]===");
	printf("\n[1] Mostra tutti i brani");
	printf("\n[2] Mostra tutti gli artisti");
	printf("\n[3] Mostra tutti gli album");
	printf("\n[4] Mostra tutti i generi");

	printf("\n[5] TODO Ricerca per Titolo");
	printf("\n[6] Ricerca per Artista");
	printf("\n[7] Ricerca per Album");
	printf("\n[8] Ricerca per Genere");
	printf("\n[0] Ritorna al menu principale");
	printf("\nInserisci la tua scelta: ");
	scanf("%d", &scelta);
	if (scelta==1) {
		mostraTuttiBrani();
		aspetta();
		menuRicerca();
	} else if (scelta==2) {
		mostraTuttiArtisti();
		aspetta();
		menuRicerca();
	} else if (scelta==3) {
		mostraTuttiAlbum();
		aspetta();
		menuRicerca();
	} else if (scelta==4) {
		mostraTuttiGeneri();
		aspetta();
		menuRicerca();
	} else if (scelta==5) {
		//TODO
	} else if (scelta==6) {
		mostraBraniArtista();
		aspetta();
		menuRicerca();
	} else if (scelta==7) {
		mostraBraniAlbum();
		aspetta();
		menuRicerca();
	} else if (scelta==8) {
		mostraBraniGenere();
		aspetta();
		menuRicerca();
	} else if (scelta==0) {
		menu();
	} else {
		printf("\nInserita scelta non riconosciuta, riprovare. ");
		menuRicerca();
	}
}


