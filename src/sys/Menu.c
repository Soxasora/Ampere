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
#include "../gestori/GestoreBrani.h"
#include "../gestori/GestoreAlbum.h"
#include "../gestori/GestoreArtisti.h"
#include "../gestori/GestoreGeneri.h"
#include "../ricerca/MotoreRicerca.h"
#include "../database/DatabaseUtils.h"
#include "../sys/Utils.h"
#include "../sys/Menu.h"
#include "../sys/Impostazioni.h"

// Nuovo Menu di Ampere
void menu() {
	pulisciBuffer();
	int scelta=0;
	printf("\n===[Menu Principale]===");
	printf("\n[1] OK Menu Database");
	printf("\n[2] OK Menu di Ricerca");
	printf("\n[0] Esci dal programma");
	printf("\nInserisci la tua scelta: ");
	scanf("%d", &scelta);
	if (scelta==1) {
		menuDatabase();
	} else if (scelta==2) {
		menuRicerca();
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
	printf("\n===[Menu Database]===");
	// Creare sottomenu di inserimento
	printf("\n[1] OK Inserisci un brano nel database");
	printf("\n[2] OK Inserisci un artista nel database");
	printf("\n[3] OK Inserisci un album nel database");
	printf("\n[4] OK Inserisci un genere nel database");
	// Creare sottomenu di modifica
	printf("\n[4] TODO Modifica un brano");
	// Creare sottomenu di cancellazione
	printf("\n[5] TODO Cancella un brano");
	printf("\n[6] TODO Cancella l'intera libreria musicale");
	// Creare sottomenu di backup
	printf("\n[7] TODO Effettua un backup del database");
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
		//TODO
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
	printf("\n[1] OK Mostra tutti i brani");
	printf("\n[2] TODO Ricerca per Titolo");
	printf("\n[3] TODO Ricerca per Artista");
	printf("\n[4] OK Ricerca per Album");
	printf("\n[5] OK Ricerca per Genere");
	printf("\n[0] Ritorna al menu principale");
	printf("\nInserisci la tua scelta: ");
	scanf("%d", &scelta);
	if (scelta==1) {
		mostraTuttiBrani();
		aspetta();
		menuRicerca();
	} else if (scelta==2) {
		//TODO
	} else if (scelta==3) {
		//TODO
	} else if (scelta==4) {
		mostraBraniAlbum();
		aspetta();
		menuRicerca();
	} else if (scelta==5) {
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


