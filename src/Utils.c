/*
 * Spotifabba 0.1 rev.70 - 13.04.2020
 * Copyright (c) 2020, Simone Cervino.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GestoreFile.h"
#include "MotoreRicerca.h"
#include "Utils.h"

void info() {
	printf("   ____          __  _ ___     __   __       \n");
	printf("  / __/__  ___  / /_(_) _/__ _/ /  / /  ___ _\n");
	printf(" _\\ \\/ _ \\/ _ \\/ __/ / _/ _ `/ _ \\/ _ \\/ _ `/\n");
	printf("/___/ .__/\\___/\\__/_/_/ \\_,_/_.__/_.__/\\_,_/ \n");
	printf("   /_/                                       \n");
	printf("\nSpotifabba 0.0.1 rev.70\n");
}

void pulisciBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF) { }
}

void aspetta() {
	#ifdef _WIN32
		printf("\n");
		system("PAUSE");
	#elif __unix__
		printf("\nPremere qualunque tasto per continuare...");
		char w = scanf("%c", &w);
	#endif
}

// Menu principale di Spotifabba
void menu() {
	pulisciBuffer();
	char scelta='0';
	printf("\n===Menu principale===");
	printf("\n[1] Gestisci il database");
	printf("\n[2] Ricerca nel database");
	printf("\n[3] TODO: Condividi un brano");
	printf("\n[4] TODO: Riproduci un brano");
	printf("\n[5] Informazioni su Spotifabba");
	printf("\n[0] Esci dal programma");
	printf("\n[9] DEBUG");
	printf("\nInserisci la tua scelta: ");
	scanf("%c", &scelta);

	if(scelta=='1') {
		menuDatabase();
	} else if (scelta=='2') {
		menuRicerca();
	} else if (scelta=='3') {
		// TODO
	} else if (scelta=='4') {
		// TODO
		#ifdef _WIN32
			system("example.mp3");
		#elif __APPLE__
			system("open example.mp3");
		#elif __linux__
			system("vlc example.mp3");
		#endif
	} else if (scelta=='5') {
		info();
		aspetta();
		menu();
	} else if (scelta=='0') {
		printf("\nUscendo dal programma...\n");
	} else if (scelta=='9') {
		// DA USARE PER DEBUG
	} else {
		printf("\nInserita scelta non riconosciuta, riprovare. ");
		menu();
	}
}

void menuDatabase() {
	pulisciBuffer();
	char scelta='0';
	printf("\n===Menu gestione database===");
	printf("\n[1] Inserimento brano nel database");
	printf("\n[2] TODO: Modifica un brano");
	printf("\n[3] TODO: Cancella un brano");
	printf("\n[0] Torna al menu principale");
	printf("\nInserisci la tua scelta: ");
	scanf("%c", &scelta);
	if (scelta=='1') {
		menuInserimento();
	} else if (scelta=='2') {
		// TODO
	} else if (scelta=='3') {
		// TODO
	} else if (scelta=='0') {
		menu();
	} else {
		printf("\nInserita scelta non riconosciuta, riprovare. ");
		menuDatabase();
	}
}

void menuInserimento() {
	pulisciBuffer();
	char scelta='0';
	printf("\n===Menu Inserimento===");
	printf("\n[1] Inserimento guidato");
	printf("\n[2] Inserimento diretto per utenti avanzati");
	printf("\n[0] Ritorna al menu precedente");
	printf("\nInserisci la tua scelta: ");
	scanf("%c", &scelta);
	if (scelta=='1') {
		inserimento(0);
	} else if (scelta=='2') {
		inserimento(1);
	} else if (scelta=='0') {
		menuDatabase();
	} else {
		printf("\nInserita scelta non riconosciuta, riprovare. ");
		menuInserimento();
	}
}

void menuRicerca() {
	pulisciBuffer();
	char scelta='0';
	printf("\n===Menu di ricerca===");
	printf("\n[1] Mostra i miei brani");
	printf("\n[2] Ricerca per Titolo");
	printf("\n[3] Ricerca per Artista");
	printf("\n[4] Ricerca per Album");
	printf("\n[5] Ricerca per Durata");
	printf("\n[6] Ricerca per Anno");
	printf("\n[0] Torna al menu principale");
	printf("\nInserisci la tua scelta: ");
	scanf("%c", &scelta);
	if (scelta=='1') {
		elencaTuttiBrani();
		aspetta();
		menuRicerca();
	} else if (scelta=='2') {
		ricercaBrani(0);
	} else if (scelta=='3') {
		ricercaBrani(1);
	} else if (scelta=='4') {
		ricercaBrani(2);
	} else if (scelta=='5') {
		ricercaBrani(3);
	} else if (scelta=='6') {
		ricercaBrani(4);
	} else if (scelta=='0') {
		menu();
	} else {
		printf("\nInserita scelta non riconosciuta, riprovare. ");
		menuRicerca();
	}
}

void menuModifica() {
	pulisciBuffer();
	char scelta='0';
	printf("\n===Menu di modifica===");
	printf("\n[1] Modifica il Titolo");
	printf("\n[2] Modifica l'Artista");
	printf("\n[3] Modifica l'Album");
	printf("\n[4] Modifica la Durata");
	printf("\n[5] Modifica l'Anno");
	printf("\n[0] Torna al menu principale");
	printf("\nInserisci la tua scelta: ");
	scanf("%c", &scelta);
	if (scelta=='1') {
		modifica(1);
	} else if (scelta=='2') {
		modifica(2);
	} else if (scelta=='3') {
		modifica(3);
	} else if (scelta=='4') {
		modifica(4);
	} else if (scelta=='5') {
		modifica(5);
	} else if (scelta=='0') {
		menu();
	} else {
		printf("\nInserita scelta non riconosciuta, riprovare. ");
		menuModifica();
	}
}
