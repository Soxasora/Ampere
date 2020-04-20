/*
 * FabbAmp 0.1 rev. 137 - 19.04.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/FabbAmp/blob/master/LICENSE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "MotoreRicerca.h"
#include "Utils.h"
#include "GestoreBrani.h"
#include "Impostazioni.h"

void info() {
	printf("   ____     __   __   ___            \n");
	printf("  / __/__ _/ /  / /  / _ | __ _  ___ \n");
	printf(" / _// _ `/ _ \\/ _ \\/ __ |/  ' \\/ _ \\\n");
	printf("/_/  \\_,_/_.__/_.__/_/ |_/_/_/_/ .__/\n");
	printf("                              /_/    \n");
	printf("\nFabbAmp 0.1 rev.137\n");
}

void pulisciBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF) { }
	printf("\nBuffer pulito.");
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

int controllaSeFileVuoto() {
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
	printf("\n[0] Torna al menu principale");
	printf("\nInserisci la tua scelta: ");
	scanf("%d", &scelta);
	if (scelta==1) {
		elencaTuttiBrani();
		aspetta();
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
	} else if (scelta==7) {
		ricercaBrani(5);
	} else if (scelta==8) {
		ricercaBrani(6);
	} else if (scelta==9) {
		ricercaBrani(7);
	} else if (scelta==10) {
		ricercaBrani(8);
	} else if (scelta==11) {
		ricercaBrani(9);
	} else if (scelta==12) {
		ricercaBrani(10);
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
	char scelta='0';
	printf("\n===Menu DEBUG===");
	printf("\n[1] Conteggia caratteri presenti nel database");
	printf("\n[2] Trasferisci database da file alla memoria");
	printf("\n[3] Trasferisci database dalla memoria al file");
	printf("\n[4] Inserisci un brano in modalità diretta");
	printf("\n[5] Pulisci buffer stdin");
	printf("\n[6] Carica impostazioni");
	printf("\n[0] Torna al menu principale");
	printf("\nInserisci la tua scelta: ");
	scanf("%c", &scelta);
	if (scelta=='1') {
		FILE* fp=fopen(file_database, "r");
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
		printf("\nTITOLO,ARTISTA,FEAT,PRODUTTORE,SCRITTORE,ALBUM,DUR:ATA,ANNO,LINGUA,ASCOLTI,GRADI.MENTO");
		printf("\nEsempio: Get Lucky,Daft Punk,Pharrell Williams,Daft Punk,Daft Punk,Random Access Memories,4:09,2013,0,34,5.0");
		inserimentoDiretto();
		aspetta();
		menuDebug();
	} else if (scelta=='5') {
		pulisciBuffer();
		aspetta();
		menuDebug();
	} else if (scelta=='6') {
		caricaImpostazioni();
		aspetta();
		menuDebug();
	} else if (scelta=='0') {
		menu();
	} else {
		printf("\nInserita scelta non riconosciuta, riprovare. ");
		menuDebug();
	}
}
