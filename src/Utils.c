/*
 * FabbAmp 0.1 rev.84 - 14.04.2020
 * Copyright (c) 2020, Nicolo' Cucinotta, Simone Cervino.
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
#include "MotoreRicerca.h"
#include "Utils.h"
#include "GestoreBrani.h"

void info() {
	printf("   ____     __   __   ___            \n");
	printf("  / __/__ _/ /  / /  / _ | __ _  ___ \n");
	printf(" / _// _ `/ _ \\/ _ \\/ __ |/  ' \\/ _ \\\n");
	printf("/_/  \\_,_/_.__/_.__/_/ |_/_/_/_/ .__/\n");
	printf("                              /_/    \n");
	printf("\nFabbAmp 0.0.1 rev.84\n");
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

int controllaSeFileVuoto() {
	FILE* fp=fopen("database.txt", "r");
	// Proof of concept, cambiare in qualcosa di più sicuro
	int c = fgetc(fp);
	fclose(fp);
	if (c == EOF) {
	    return 1;
	} else {
		return 0;
	}
}

int conteggiaCaratteriFile(FILE* fp) {
	int conta=0;
	char c = fgetc(fp);
	while (c!=EOF) {
		c=fgetc(fp);
		conta++;
	}
	return conta;
}

void backupDatabase(char *file2) {
	FILE *fp, *fp2;
	char *file = "database.txt";
	char c;
	fp = fopen(file, "r");
	if (fp==NULL) {
		printf("Impossibile aprire il database file-based.");
	}

	fp2 = fopen(file2, "w");
	if (fp2==NULL) {
		printf("Impossibile creare un database file-based di backup.");
	}

	// Proof of concept, cambiare in qualcosa di più sicuro
	c=fgetc(fp);
	while (c!=EOF) {
		fputc(c, fp2);
		c=fgetc(fp);
	}
	fclose(fp); fclose(fp2);
	printf("\nBackup del database effettuato.");
}

// Menu principale di FabbAmp
void menu() {
	pulisciBuffer();
	char scelta='0';
	printf("\n===Menu principale===");
	printf("\n[1] Gestisci il database");
	printf("\n[2] Ricerca nel database");
	printf("\n[3] TODO: Condividi un brano");
	printf("\n[4] TODO: Riproduci un brano");
	printf("\n[5] Informazioni su FabbAmp");
	printf("\n[0] Esci dal programma");
	printf("\n[9] MENU DEBUG");
	printf("\nInserisci la tua scelta: ");
	scanf("%c", &scelta);

	if(scelta=='1') {
		menuDatabase();
	} else if (scelta=='2') {
		menuRicerca();
	} else if (scelta=='3') {
		// TODO
		menu();
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
		menuDebug();
	} else {
		printf("\nInserita scelta non riconosciuta, riprovare. ");
		menu();
	}
}

void menuDatabase() {
	pulisciBuffer();
	char scelta='0';
	printf("\n===Menu gestione database===");
	printf("\n[1] Inserisci un brano nel database");
	printf("\n[2] Modifica un brano");
	printf("\n[3] TODO: Cancella un brano");
	printf("\n[4] Effettua un backup del database");
	printf("\n[0] Torna al menu principale");
	printf("\nInserisci la tua scelta: ");
	scanf("%c", &scelta);
	if (scelta=='1') {
		inserimentoGuidato();
		aspetta();
		menuDatabase();
	} else if (scelta=='2') {
		// TODO
		menuModifica();
	} else if (scelta=='3') {
		// TODO
	} else if (scelta=='4') {
		pulisciBuffer();
		char *nome = malloc(MAX_CHAR);
		printf("\nInserisci nome del backup, inclusa estensione: ");
		fgets(nome, MAX_CHAR, stdin);
		strtok(nome, "\n");
		backupDatabase(nome);
		free(nome);
		aspetta();
		menuDatabase();
	} else if (scelta=='0') {
		menu();
	} else {
		printf("\nInserita scelta non riconosciuta, riprovare. ");
		menuDatabase();
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
		aspetta();
		menuModifica();
	} else if (scelta=='2') {
		modifica(2);
		aspetta();
		menuModifica();
	} else if (scelta=='3') {
		modifica(3);
		aspetta();
		menuModifica();
	} else if (scelta=='4') {
		modifica(4);
		aspetta();
		menuModifica();
	} else if (scelta=='5') {
		modifica(5);
		aspetta();
		menuModifica();
	} else if (scelta=='0') {
		menu();
	} else {
		printf("\nInserita scelta non riconosciuta, riprovare. ");
		menuModifica();
	}
}


// DEBUG TOOLBOX Rimuovere a fine progetto
void menuDebug() {
	pulisciBuffer();
	char scelta='0';
	printf("\n===Menu DEBUG===");
	printf("\n[1] Conteggia caratteri presenti nel database");
	printf("\n[2] Trasferisci database da file alla memoria");
	printf("\n[3] Trasferisci database dalla memoria al file");
	printf("\n[4] Inserisci un brano in modalità diretta");
	printf("\n[5] Pulisci buffer stdin");
	printf("\n[0] Torna al menu principale");
	printf("\nInserisci la tua scelta: ");
	scanf("%c", &scelta);
	if (scelta=='1') {
		FILE* fp=fopen("database.txt", "r");
		printf("\n%d caratteri", conteggiaCaratteriFile(fp));
		fclose(fp);
		aspetta();
		menuDebug();
	} else if (scelta=='2') {
		brani = ottieniDatabase();
		aspetta();
		menuDebug();
	} else if (scelta=='3') {
		aggiornaDatabase();
		aspetta();
		menuDebug();
	} else if (scelta=='4') {
		printf("\nBenvenuto nell'inserimento diretto di un brano.");
		printf("\nIl modello per inserire un brano è il seguente:");
		printf("\nTITOLO,ARTISTA,ALBUM,DUR:ATA,ANNO");
		printf("\nEsempio: Get Lucky,Daft Punk,Random Access Memories,4:09,2013");
		inserimentoDiretto();
		aspetta();
		menuDebug();
	} else if (scelta=='5') {
		pulisciBuffer();
		aspetta();
		menuDebug();
	}
}
