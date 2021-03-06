/*
 * UNIBA/Ampere 1.3
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di Informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

// C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// WINDOWS
#ifdef _WIN32
	#include <strings.h>
	#include <io.h>
	#include <shlwapi.h>
#elif __unix__ || __APPLE__ // UNIX
	#include <sys/stat.h>
	#include <unistd.h>
#endif
// AMPERE
#include "../gestori/GestoreBrani.h"
#include "../gestori/GestoreAlbum.h"
#include "../gestori/GestoreArtisti.h"
#include "../ricerca/MotoreRicerca.h"
#include "../database/Database.h"
#include "../sys/Messaggi.h"
#include "../sys/Utils.h"
#include "../sys/Impostazioni.h"

void logo() {
	printf("    ___                     "C_GIALLO"_/  /"C_RESET
		"\n   /   |  ____ ___  ____   "C_GIALLO"/  _/"C_RESET"_  ________"
		"\n  / /| | / __ `__ \\/ __ \\"C_GIALLO"_/  /"C_RESET" _ \\/ ___/ _ \\"
		"\n / ___ |/ / / / / / /_/ "C_GIALLO"/ __/"C_RESET"  __/ /  /  __/"
		"\n/_/  |_/_/ /_/ /_/ .___"C_GIALLO"/ /  "C_RESET"\\___/_/   \\___/ "C_CIANO"perennemente in pre-alpha!"C_RESET
		"\n                /_/   "C_GIALLO"/_/      "
		"\n                     //"
		"\n                    /,"C_RESET"\n\n");
}

void info() {
	logo();
	printf("UNIBA/"C_GIALLO"Ampere "CB_ROSSO"1.3"C_RESET
	"\nGruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino"
	"\nProgetto universitario di gruppo intento alla creazione di un gestore dati per la musica\n");
}

void aspetta() {
	printf("\nPremere invio per continuare...");
	int c;
	while ((c = getchar()) != EOF && c != '\n') {}
}

void aprireLink(char link[]) {
	char *comando = calloc(MAX_ENORME, sizeof(char));
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
	if (comando!=NULL) {
		free(comando);
		comando=NULL;
	}
}

void creareCartella(char nome[], bool silenzioso) {
	// Utilizzo di ifdef perch� mkdir e' una funzione che ha un omonimo
	int risultato=0;
	#ifdef _WIN32
		risultato=0;
		risultato = _mkdir(nome);
		if(risultato!=0) {
			if (!silenzioso) {
				printf("\nLa cartella '%s' esiste gia' oppure e' impossibile crearla", nome);
			}
		}
	#elif __unix__ || __APPLE__
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

char* inputStringa(int lunghezza, char stringa[]) {
    int i=0, lunghezzaStringa=0;
    char *stringaSicura;
    do {
        stringaSicura = calloc(lunghezza, sizeof(char));
        fgets(stringa, lunghezza, stdin);
        //rimuoviamo ogni whitespace iniziale
        sscanf(stringa, " %[^\r\v\f\t\n]", stringaSicura);
        lunghezzaStringa = rimuovereSpaziFinali(stringaSicura);
        //utilizziamo una variabile che possiamo ritornare
        strcpy(stringa, stringaSicura);
        if (lunghezzaStringa==lunghezza-1) {
            attenzione(3);
            pulireBuffer();
        }
        free(stringaSicura);
    } while (lunghezzaStringa==lunghezza-1);
    while (i<lunghezzaStringa) {
        if (stringa[i]=='|') {
            stringa[i] = ',';
        }
        i++;
    }
    // Controlla se l'utente non inserisce niente
    if (stringa[0]=='\0') {
        strcpy(stringa, "N/A");
    }
    return stringa;
}

int rimuovereSpaziFinali(char *stringa){
	int posizioneUltimoCarattereValido = -1;
	int i=0;

	while(stringa[i] != '\0'){
		if(stringa[i] != ' '){
			posizioneUltimoCarattereValido = i;
		}
		i++;
	}

	//tronchiamo la stringa
	stringa[posizioneUltimoCarattereValido + 1] = '\0';
	return posizioneUltimoCarattereValido+1;
}

int inputNumero(){
	char numero[MAX_ENORME];
	char *notanumber;
	int scelta=-1;
	do {
		scanf(" %s", numero);
		scelta = strtol(numero, &notanumber, 10);
		if (numero == notanumber) {
			attenzione(-2);
		}
		pulireBuffer();
	} while (numero == notanumber);
	return scelta;
}

char inputCarattere(){
	char carattere;
	scanf(" %c", &carattere);
	pulireBuffer();
	return carattere;
}

int comparareStringhe(const char *s1, const char *s2) {
	int risultato=0;
	if (os==0) {
		risultato = _stricmp(s1, s2);
	} else {
		risultato = strcasecmp(s1, s2);
	}
	return risultato;
}

bool comparareStringheParziale(const char *s1, const char *s2) {
	bool risultato=0;
	if (os==0) {
		risultato = StrStrIA(s1, s2);
	} else {
		risultato = strstr(s1, s2);
	}
	return risultato;
}

void pulireBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF) { }
}

int controllareSeFileVuoto(char *file) {
	FILE* fp=fopen(file, "r");
	int c = fgetc(fp);
	fclose(fp);
	if (c == EOF) {
	    return 1;
	} else {
		return 0;
	}
}

void backupFile(char *file1, char *file2) {
	FILE *fp, *fp2;
	char c;
	fp = fopen(file1, "r");
	if (fp==NULL) {
		perror("\nImpossibile aprire il file d'origine: ");
	} else {
		fp2 = fopen(file2, "w");
		if (fp2==NULL) {
			perror("\nImpossibile creare il file di backup: ");
		} else {
			c=fgetc(fp);
			while (c!=EOF) {
				fputc(c, fp2);
				c=fgetc(fp);
			}
		}
	}
	fclose(fp); fclose(fp2);
}

char *convertireSecondiInTempo(int secondi) {
	int h=secondi/3600;
	int m=(secondi -(3600*h))/60;
	int s=(secondi -(3600*h)-(m*60));
	char *hhmmss = calloc(MAX_MEDIO, sizeof(char));
	sprintf(hhmmss, "%d ore, %d minuti, %d secondi", h, m, s);
	return hhmmss;
}

void abilitareColori() {
	system("color 07");
}
