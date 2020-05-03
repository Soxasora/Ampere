/*
 * Utils.c
 *
 *  Created on: 2 mag 2020
 *      Author: soxas
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// WINDOWS
#include <strings.h>
#include <io.h>
// UNIX
#include <sys/stat.h>
#include <unistd.h>
#include "../gestori/GestoreBrani.h"
#include "../gestori/GestoreAlbum.h"
#include "../gestori/GestoreArtisti.h"
#include "../ricerca/MotoreRicerca.h"
#include "../database/Database.h"
#include "../sys/Utils.h"
#include "../sys/Impostazioni.h"

void info() {
	printf("    ___                                 \n");
	printf("   /   |  ____ ___  ____  ___  ________ \n");
	printf("  / /| | / __ `__ \\/ __ \\/ _ \\/ ___/ _ \\\n");
	printf(" / ___ |/ / / / / / /_/ /  __/ /  /  __/\n");
	printf("/_/  |_/_/ /_/ /_/ .___/\\___/_/   \\___/ \n");
	printf("                /_/                     \n");
	//printf("\nAmpere 0.1 rev. 501 - 27.04.2020\n");
	printf("\nGruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino");
	printf("\nProgetto universitario di gruppo intento alla creazione di un gestore dati per la musica\n");
}

void aspetta() {
	if(os==0) {
		printf("\n");
		system("PAUSE");
	} else {
		printf("\nPremere qualunque tasto per continuare...");
		char w = scanf("%c", &w);
	}
}

void creaCartella(char nome[]) {
	#ifdef _WIN32
		int risultato=0;
		risultato = _mkdir(nome);
		if(risultato!=0)
			printf("\nLa cartella '%s' esiste gia' oppure e' impossibile crearla", nome);
	#elif __unix__
		struct stat st = {0};
		if (stat(nome, &st) == -1) {
			mkdir(nome, 0700);
		} else {
			printf("\nLa cartella '%s' esiste gia'", nome);
		}
	#endif
}

char* inputStringaSicuro(char stringa[]) {
	//char* stringa = malloc(MAX_CHAR);
	fgets(stringa, MAX_CHAR, stdin);
	strtok(stringa, "\n");
	if (stringa[0]=='\n') {
		stringa = "N/A";
	}
	return stringa;
}

int comparaStringhe(const char *s1, const char *s2) {
	int risultato=0;
	if (os==0) {
		risultato = _stricmp(s1, s2);
	} else {
		risultato = strcasecmp(s1, s2);
	}
	return risultato;
}

char *chiediFile() {
	pulisciBuffer();
	char *nome_file = malloc(MAX_TEMP);
	printf("\nInserisci locazione e nome file [esempio\\esempio.extension] da utilizzare: ");
	scanf("%s", nome_file);
	return nome_file;
}

void pulisciBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF) { }
}

int controllaSeFileVuoto(char *file) {
	FILE* fp=fopen(file, "r");
	// Proof of concept, cambiare in qualcosa di più sicuro
	int c = fgetc(fp);
	fclose(fp);
	if (c == EOF) {
	    return 1;
	} else {
		return 0;
	}
}

void backupFile(char *file1, char *file2) {
	int controllo=0;
	FILE *fp, *fp2;
	char c;
	fp = fopen(file1, "r");
	if (fp==NULL) {
		perror("\nImpossibile aprire il file d'origine: ");
		controllo=-1;
	}

	fp2 = fopen(file2, "w");
	if (fp2==NULL&&controllo!=-1) {
		perror("\nImpossibile creare il file di backup: ");
		controllo=-1;
	}

	// Proof of concept, cambiare in qualcosa di più sicuro
	if (controllo!=-1) {
		c=fgetc(fp);
		while (c!=EOF) {
			fputc(c, fp2);
			c=fgetc(fp);
		}
		printf("\nBackup del database effettuato.");
	}
	fclose(fp); fclose(fp2);
}

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
		//TODO
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
	printf("\n[4] TODO Ricerca per Album");
	printf("\n[5] TODO Ricerca per Genere");
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
		//TODO
	} else if (scelta==5) {
		//TODO
	} else if (scelta==0) {
		menu();
	} else {
		printf("\nInserita scelta non riconosciuta, riprovare. ");
		menuRicerca();
	}
}
