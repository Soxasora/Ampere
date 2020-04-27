/*
 * Ampere 0.1 rev. 420 - 26.04.2020
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
// Header Ampere
#include "../ricerca/MotoreRicerca.h"
#include "../sys/Utils.h"
#include "../gestore/GestoreBrani.h"
#include "../sys/Impostazioni.h"

void info() {
	printf("    ___                                 \n");
	printf("   /   |  ____ ___  ____  ___  ________ \n");
	printf("  / /| | / __ `__ \\/ __ \\/ _ \\/ ___/ _ \\\n");
	printf(" / ___ |/ / / / / / /_/ /  __/ /  /  __/\n");
	printf("/_/  |_/_/ /_/ /_/ .___/\\___/_/   \\___/ \n");
	printf("                /_/                     \n");
	printf("\nAmpere 0.1 rev. 420 - 26.04.2020\n");
	printf("\nGruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino");
	printf("\nProgetto universitario di gruppo intento alla creazione di un gestore dati per la musica\n");
}

void creaCartella(char nome[]) {
	#ifdef _WIN32
		int risultato=0;
		risultato = mkdir(nome);
		if(risultato!=0)
			printf("\nLa cartella '%s' esiste gia' oppure e' impossibile crearla", nome);
	#elif __linux__
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

void pulisciBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF) { }
	//printf("\nBuffer pulito.");
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

int comparaStringhe(const char *s1, const char *s2) {
	int risultato=0;
	#ifdef _WIN32
		risultato = _stricmp(s1, s2);
	#elif __unix__
		risultato = strcasecmp(s1, s2);
	#endif

	return risultato;
}

char *chiediFile() {
	pulisciBuffer();
	char *nome_file = malloc(MAX_CHAR);
	printf("Inserisci locazione e nome file [esempio\\esempio.extension] da analizzare: ");
	scanf("%s", nome_file);
	return nome_file;
}

int controllaSeDatabaseVuoto() {
	FILE* fp=fopen(file_database, "r");
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

int conteggiaLinee(FILE* fp) {
	int conta=1;
	char c = fgetc(fp);
	while (c!=EOF) {
		c=fgetc(fp);
		if (c=='\n') {
			conta++;
		}
	}
	return conta;
}

int conteggiaBrani() {
	int i = 0;
	while (brani[i].id!=0) {
		i++;
	}
	return i;
}

int trovaUltimoId() {
	if(controllaSeDatabaseVuoto()==1) {
		return 0;
	} else {
		int nbrani = conteggiaBrani();
		int i=0, max=0;
		while(i<nbrani) {
			if(brani[i].id>max) {
				max=brani[i].id;
			}
			i++;
		}
		return max;
	}
}

int trovaPosizioneBranoId(int id) {
	int nbrani = conteggiaBrani();
	int pos = 0, i=0;
	while (i<nbrani) {
		if (brani[i].id == id) {
			pos = i;
		}
		i++;
	}
	return pos;
}

int linguaNumerica(char linguaStringa[]) {
	int i=0, n_lingue=0, n_lingua=0;
	FILE* fp = fopen(file_lingue, "r");
	n_lingue = conteggiaLinee(fp);
	while (i<n_lingue) {
		if (comparaStringhe(linguaStringa, lingue[i])==0) {
			n_lingua=i;
		}
		i++;
	}
	fclose(fp);
	return n_lingua;
}

void backupDatabase(char *file2) {
	FILE *fp, *fp2;
	char c;
	fp = fopen(file_database, "r");
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

// Menu principale di Ampere
void menu() {
	pulisciBuffer();
	int scelta=0;
	printf("\n===Menu principale===");
	printf("\n[1] Gestisci il database");
	printf("\n[2] Ricerca nel database");
	printf("\n[3] TODO: Condividi un brano");
	printf("\n[4] TODO: Riproduci un brano");
	printf("\n[5] Informazioni su Ampere");
	printf("\n[0] Esci dal programma");
	printf("\n[9] MENU DEBUG");
	printf("\nInserisci la tua scelta: ");
	scanf("%d", &scelta);
	if(scelta==1) {
		menuDatabase();
	} else if (scelta==2) {
		menuRicerca();
	} else if (scelta==3) {
		// TODO
		menu();
	} else if (scelta==4) {
		// TODO
	} else if (scelta==5) {
		info();
		aspetta();
		menu();
	} else if (scelta==0) {
		printf("\nUscendo dal programma...\n");
	} else if (scelta==9) {
		// DA USARE PER DEBUG
		menuDebug();
	} else {
		printf("\nInserita scelta non riconosciuta, riprovare. ");
		menu();
	}
}

void menuDatabase() {
	pulisciBuffer();
	int scelta=0;
	printf("\n===Menu gestione database===");
	printf("\n[1] Inserisci un brano nel database");
	printf("\n[2] Modifica un brano");
	printf("\n[3] Cancella un brano");
	printf("\n[4] Effettua un backup del database");
	printf("\n[5] Cancella l'intera libreria musicale");
	printf("\n[0] Torna al menu principale");
	printf("\nInserisci la tua scelta: ");
	scanf("%d", &scelta);
	if (scelta==1) {
		inserimentoGuidato();
		aspetta();
		menuDatabase();
	} else if (scelta==2) {
		menuModifica();
	} else if (scelta==3) {
		cancella();
		aspetta();
		menuDatabase();
	} else if (scelta==4) {
		pulisciBuffer();
		char *nome = malloc(MAX_CHAR);
		printf("\nInserisci nome del backup, inclusa estensione: ");
		fgets(nome, MAX_CHAR, stdin);
		strtok(nome, "\n");
		backupDatabase(nome);
		free(nome);
		aspetta();
		menuDatabase();
	} else if (scelta==5) {
		cancellaLibreria();
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
	printf("\n===Menu di ricerca===");
	printf("\n[1] Mostra i miei brani");
	printf("\n[2] Ricerca per Titolo");
	printf("\n[3] Ricerca per Artista");
	printf("\n[4] Ricerca per Feat");
	printf("\n[5] Ricerca per Produttore");
	printf("\n[6] Ricerca per Scrittore");
	printf("\n[7] Ricerca per Album");
	printf("\n[8] Ricerca per Durata");
	printf("\n[9] Ricerca per Anno");
	printf("\n[10] Ricerca per Lingua");
	printf("\n[11] Ricerca per Ascolti");
	printf("\n[12] Ricerca per Gradimento");
	printf("\n[13] Ricerca per Identificativo");
	printf("\n[0] Torna al menu principale");
	printf("\nInserisci la tua scelta: ");
	scanf("%d", &scelta);
	if (scelta==1) {
		elencaTuttiBrani();
		aspetta();
		menuRicerca();
	} else if (scelta==2) {
		ricercaBrani(0);
		aspetta();
		menuRicerca();
	} else if (scelta==3) {
		ricercaBrani(1);
		aspetta();
		menuRicerca();
	} else if (scelta==4) {
		ricercaBrani(2);
		aspetta();
		menuRicerca();
	} else if (scelta==5) {
		ricercaBrani(3);
		aspetta();
		menuRicerca();
	} else if (scelta==6) {
		ricercaBrani(4);
		aspetta();
		menuRicerca();
	} else if (scelta==7) {
		ricercaBrani(5);
		aspetta();
		menuRicerca();
	} else if (scelta==8) {
		ricercaBrani(6);
		aspetta();
		menuRicerca();
	} else if (scelta==9) {
		ricercaBrani(7);
		aspetta();
		menuRicerca();
	} else if (scelta==10) {
		ricercaBrani(8);
		aspetta();
		menuRicerca();
	} else if (scelta==11) {
		ricercaBrani(9);
		aspetta();
		menuRicerca();
	} else if (scelta==12) {
		ricercaBrani(10);
		aspetta();
		menuRicerca();
	} else if (scelta==13) {
		ricercaBrani(11);
		aspetta();
		menuRicerca();
	} else if (scelta==0) {
		menu();
	} else {
		printf("\nInserita scelta non riconosciuta, riprovare. ");
		menuRicerca();
	}
}

void menuModifica() {
	pulisciBuffer();
	int scelta=0;
	printf("\n===Menu di modifica===");
	printf("\n[1] Modifica il Titolo");
	printf("\n[2] Modifica l'Artista");
	printf("\n[3] Modifica il Feat");
	printf("\n[4] Modifica il Produttore");
	printf("\n[5] Modifica lo Scrittore");
	printf("\n[6] Modifica l'Album");
	printf("\n[7] Modifica la Durata");
	printf("\n[8] Modifica l'Anno");
	printf("\n[9] Modifica la Lingua");
	printf("\n[10] Modifica il numero di ascolti");
	printf("\n[11] Modifica il gradimento");
	printf("\n[0] Torna al menu principale");
	printf("\nInserisci la tua scelta: ");
	scanf("%d", &scelta);
	if (scelta==1) {
		modifica(1);
		aspetta();
		menuModifica();
	} else if (scelta==2) {
		modifica(2);
		aspetta();
		menuModifica();
	} else if (scelta==3) {
		modifica(3);
		aspetta();
		menuModifica();
	} else if (scelta==4) {
		modifica(4);
		aspetta();
		menuModifica();
	} else if (scelta==5) {
		modifica(5);
		aspetta();
		menuModifica();
	} else if (scelta==6) {
		modifica(6);
		aspetta();
		menuModifica();
	} else if (scelta==7) {
		modifica(7);
		aspetta();
		menuModifica();
	} else if (scelta==8) {
		modifica(8);
		aspetta();
		menuModifica();
	} else if (scelta==9) {
		modifica(9);
		aspetta();
		menuModifica();
	} else if (scelta==10) {
		modifica(10);
		aspetta();
		menuModifica();
	} else if (scelta==11) {
		modifica(11);
		aspetta();
		menuModifica();
	} else if (scelta==0) {
		menu();
	} else {
		printf("\nInserita scelta non riconosciuta, riprovare. ");
		menuModifica();
	}
}


// DEBUG TOOLBOX Rimuovere a fine progetto
void menuDebug() {
	pulisciBuffer();
	int scelta=0;
	printf("\n===Menu DEBUG===");
	printf("\n[1] Conteggia caratteri presenti in un file");
	printf("\n[2] Conteggia linee presenti in un file");
	printf("\n[3] Trasferisci database da file alla memoria");
	printf("\n[4] Trasferisci database dalla memoria al file");
	printf("\n[5] Inserisci un brano in modalità diretta");
	printf("\n[6] Pulisci buffer stdin");
	printf("\n[7] Carica impostazioni");
	printf("\n[8] Conteggia brani");
	printf("\n[99] Tutto quello che vuoi che sia");
	printf("\n[0] Torna al menu principale");
	printf("\nInserisci la tua scelta: ");
	scanf("%d", &scelta);
	if (scelta==1) {
		FILE* fp=fopen(chiediFile(), "r");
		printf("\n%d caratteri", conteggiaCaratteriFile(fp));
		fclose(fp);
		aspetta();
		menuDebug();
	} else if (scelta==2) {
		FILE* fp=fopen(chiediFile(), "r");
		printf("\n%d linee", conteggiaLinee(fp));
		fclose(fp);
		aspetta();
		menuDebug();
	} else if (scelta==3) {
		brani = ottieniDatabase();
		aspetta();
		menuDebug();
	} else if (scelta==4) {
		aggiornaDatabase();
		aspetta();
		menuDebug();
	} else if (scelta==5) {
		printf("\nBenvenuto nell'inserimento diretto di un brano.");
		printf("\nIl modello per inserire un brano è il seguente:");
		printf("\nTITOLO,ARTISTA,FEAT,PRODUTTORE,SCRITTORE,ALBUM,DUR:ATA,ANNO,LINGUA,ASCOLTI,GRADI.MENTO");
		printf("\nEsempio: Get Lucky,Daft Punk,Pharrell Williams,Daft Punk,Daft Punk,Random Access Memories,4:09,2013,0,34,5.0");
		inserimentoDiretto();
		aspetta();
		menuDebug();
	} else if (scelta==6) {
		pulisciBuffer();
		aspetta();
		menuDebug();
	} else if (scelta==7) {
		caricaImpostazioni();
		aspetta();
		menuDebug();
	} else if (scelta==8) {
		printf("\n%d brani presenti nello struct.", conteggiaBrani());
		aspetta();
		menuDebug();
	} else if (scelta==99) {
		printf("\n%d", controllaSeDatabaseVuoto());
	} else if (scelta==0) {
		menu();
	} else {
		printf("\nInserita scelta non riconosciuta, riprovare. ");
		menuDebug();
	}
}
