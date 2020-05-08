/*
 * Ampere 0.1 rev. 2432 - 08.05.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
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
	printf("\nAmpere 0.1 rev. 2432 - 08.05.2020\n");
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

void cercaSuWikipedia(char interrogazione[]) {
	char *comando = malloc(MAX_TEMP);
	int i=0;
	while(i<strlen(interrogazione)) {
		if (interrogazione[i]==' ') {
			interrogazione[i]='+';
		}
		i++;
	}
	if (os==0) {
		sprintf(comando, "start https://it.wikipedia.org/w/index.php?search=%s", interrogazione);
		int a = system(comando);
	} else if (os==1||os==3) {
		sprintf(comando, "firefox https://it.wikipedia.org/w/index.php?search=%s", interrogazione);
		int a = system(comando);
	} else if (os==2) {
		sprintf(comando, "open https://it.wikipedia.org/w/index.php?search=%s", interrogazione);
		int a = system(comando);
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

char* inputStringaSicuro(char stringa[]) {
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
	}
	fclose(fp); fclose(fp2);
}

