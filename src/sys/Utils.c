/*
 * Ampere 0.2 rev. 17 - 02.06.2020
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// WINDOWS
#include <strings.h>
#include <io.h>
#include <shlwapi.h>
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
	printf("    ___                     "C_GIALLO"_/  /"C_RESET
	"\n   /   |  ____ ___  ____   "C_GIALLO"/  _/"C_RESET"_  ________"
	"\n  / /| | / __ `__ \\/ __ \\"C_GIALLO"_/  /"C_RESET" _ \\/ ___/ _ \\"
	"\n / ___ |/ / / / / / /_/ "C_GIALLO"/ __/"C_RESET"  __/ /  /  __/"
	"\n/_/  |_/_/ /_/ /_/ .___"C_GIALLO"/ /  "C_RESET"\\___/_/   \\___/ "C_CIANO"perennemente in pre-alpha!"C_RESET
	"\n                /_/   "C_GIALLO"/_/      "
	"\n                     //"
	"\n                    /,"C_RESET"\n"
	"\nAmpere 0.2 rev. 17 - 02.06.2020"
	"\nGruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino"
	"\nProgetto universitario di gruppo intento alla creazione di un gestore dati per la musica\n");
}

void aspetta() {
	printf("\nPremere invio per continuare...");
	char w = scanf("%c", &w);
}

void apriLink(char link[]) {
	char *comando = malloc(MAX_ENORME);
	printf("\nAprendo il browser predefinito...");
	if (os==0) {
		sprintf(comando, "start %s", link);
		system(comando);
	} else if (os==1||os==3) {
		sprintf(comando, "firefox %s", link);
		system(comando);
	} else if (os==2) {
		sprintf(comando, "open %s", link);
		system(comando);
	}
}

void creaCartella(char nome[], bool silenzioso) {
	#ifdef _WIN32
		int risultato=0;
		risultato = _mkdir(nome);
		if(risultato!=0) {
			if (!silenzioso) {
				printf("\nLa cartella '%s' esiste gia' oppure e' impossibile crearla", nome);
			}
		}
	#elif __unix__
		struct stat st = {0};
		if (stat(nome, &st) == -1) {
			risultato = mkdir(nome, 0700);
			if (risultato!=0) {
				if (!silenzioso) {
					printf("\nE' impossibile creare la cartella '%s'", nome);
				}
			}
		} else {
			if (!silenzioso) {
				printf("\nLa cartella '%s' esiste gia'", nome);
			}
		}
	#endif
}

char* inputStringaSicuro(int lunghezza, char stringa[]) {
	fgets(stringa, lunghezza, stdin);
	int i=0;
	while (i<strlen(stringa)) {
		if (stringa[i]=='|') {
			stringa[i] = ',';
		}
		i++;
	}
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

bool comparaStringheParziale(const char *s1, const char *s2) {
	bool risultato=0;
	if (os==0) {
		risultato = StrStrIA(s1, s2);
	} else {
		risultato = strstr(s1, s2);
	}
	return risultato;
}

char *chiediFile() {
	pulisciBuffer();
	char *nomeFile = malloc(MAX_ENORME);
	printf("\nInserisci locazione e nome file [esempio\\esempio.extension] da utilizzare: ");
	scanf("%s", nomeFile);
	return nomeFile;
}

void pulisciBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF) { }
}

int controllaSeFileVuoto(char *file) {
	FILE* fp=fopen(file, "r");
	// Proof of concept, cambiare in qualcosa di pi� sicuro
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

	// Proof of concept, cambiare in qualcosa di pi� sicuro
	if (controllo!=-1) {
		c=fgetc(fp);
		while (c!=EOF) {
			fputc(c, fp2);
			c=fgetc(fp);
		}
	}
	fclose(fp); fclose(fp2);
}

char *convertiSecondiInTempo(int secondi) {
	int h=secondi/3600;
	int m=(secondi -(3600*h))/60;
	int s=(secondi -(3600*h)-(m*60));
	char *hhmmss = malloc(MAX_MEDIO);
	sprintf(hhmmss, "%d:%d:%d", h, m, s);
	return hhmmss;
}

void abilitaColori() {
	system("color 07");
}
