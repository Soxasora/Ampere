/*
 * Spotifabba 0.1 rev.50 - 13.04.2020
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
#include "Spotifabba.h"
#include "Database.h"
#include "GestoreFile.h"
#include "MotoreRicerca.h"

void inizializzazione();

int main() {
	// Inizializza il programma
	inizializzazione();
	// Mostra il menu
	menu(-1);

	//TODO: Cambiare in un sistema multipiattaforma.
	printf("Spotifabba terminato.\n");
	#ifdef _WIN32
		system("PAUSE");
	#endif
	return 0;
}

void inizializzazione() {
	// Visualizza informazioni su Spotifabba
	printf("Spotifabba 0.0.1 rev.40\n");
	printf("\nBenvenuto su Spotifabba.");
	// Crea database se esso non � presente nella cartella.
	creaDatabaseSeNonEsiste();
}

// Menu principale di Spotifabba
void menu(int scelta) {
	do {
		printf("\n[1] Gestisci il database");
		printf("\n[2] Ricerca nel database");
		printf("\n[3] TODO: Condividi un brano");
		printf("\n[4] TODO: Riproduci un brano");
		printf("\n[0] Esci dal programma");
		printf("\n[11] DEBUG");
		printf("\nInserisci la tua scelta: ");
		scanf("%d", &scelta);
	} while (scelta==-1);

	if(scelta==1) {
		menuDatabase();
	} else if (scelta==2) {
		menuRicerca();
	} else if (scelta==3) {
		// TODO
	} else if (scelta==4) {
		// TODO
		#ifdef _WIN32
			system("example.mp3");
		#elif __APPLE__
			system("open example.mp3");
		#elif __linux__
			system("vlc example.mp3");
		#endif
	} else if (scelta==0) {
		printf("\nUscendo dal programma...\n");
	} else if (scelta==11) {
		// DA USARE PER DEBUG

	}
}

void menuDatabase() {
	int scelta=0;
	printf("\n===Menu gestione database===");
	printf("\n[1] Inserimento brano nel database");
	printf("\n[2] TODO: Modifica un brano");
	printf("\n[3] TODO: Cancella un brano");
	printf("\n[0] Torna al menu principale");
	printf("\nInserisci la tua scelta: ");
	scanf("%d", &scelta);
	if (scelta==1) {
		// TODO: Dargli un menu separato
		int sotto_scelta=0;
		printf("\n[1] Inserimento guidato");
		printf("\n[2] Inserimento diretto per utenti avanzati");
		printf("\n[0] Ritorna al menu precedente");
		printf("\nInserisci la tua scelta: ");
		scanf("%d", &sotto_scelta);
		if (sotto_scelta==1)
			inserimento(0);
		else if (sotto_scelta==2)
			inserimento(1);
		else if (sotto_scelta==0)
			menuDatabase();
	} else if (scelta==2) {
		// TODO
	} else if (scelta==3) {
		// TODO
	} else if (scelta==0) {
		menu(-1);
	}
}

void menuRicerca() {
	int scelta=0;
	printf("\n===Menu di ricerca===");
	printf("\n[1] Mostra i miei brani");
	printf("\n[2] Ricerca per Titolo");
	printf("\n[3] Ricerca per Artista");
	printf("\n[4] Ricerca per Album");
	printf("\n[5] Ricerca per Durata");
	printf("\n[6] Ricerca per Anno");
	printf("\n[0] Torna al menu principale");
	printf("\nInserisci la tua scelta: ");
	scanf("%d", &scelta);
	if (scelta==1) {
		elencaBrani();
		menuRicerca();
	} else if (scelta==2) {
		ricercaBrani(0);
	} else if (scelta==3) {
		ricercaBrani(1);
	} else if (scelta==4) {
		ricercaBrani(2);
	} else if (scelta==5) {
		ricercaBrani(3);
	} else if (scelta==6) {
		ricercaBrani(4);
	} else if (scelta==0) {
		menu(-1);
	}
}
