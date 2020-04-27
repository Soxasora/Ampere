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
#include "../gestore/GestoreBrani.h"
#include "../Ampere.h"
#include "../gestore/Database.h"
#include "../ricerca/MotoreRicerca.h"
#include "../sys/Utils.h"
#include "../sys/Impostazioni.h"

// FUNZIONI FILE
// Inserimento di informazioni direttamente nel database file-based
void inserimentoGuidato() {
	// Flush per evitare indesiderati comportamenti dell'input
	pulisciBuffer();
	// Allocazione della memoria
	char *id = malloc(MAX_CHAR);
	char *titolo = malloc(MAX_CHAR);
	char *artista = malloc(MAX_CHAR);
	char *feat = malloc(MAX_CHAR);
	char *produttore = malloc(MAX_CHAR);
	char *scrittore = malloc(MAX_CHAR);
	char *album = malloc(MAX_CHAR);
	char *durata = malloc(MAX_CHAR);
	char *anno = malloc(MAX_CHAR);
	char *lingua = malloc(MAX_CHAR);
	char *ascolti = malloc(MAX_CHAR);
	char *gradimento = malloc(MAX_CHAR);
	// Registrazione informazioni
	sprintf(id, "%d", trovaUltimoId()+1);
	printf("\nInserisci titolo: ");
	titolo = inputStringaSicuro(titolo);
	printf("\nInserisci artista: ");
	artista = inputStringaSicuro(artista);
	printf("\nInserisci feat: ");
	feat = inputStringaSicuro(feat);
	printf("\nInserisci produttore: ");
	produttore = inputStringaSicuro(produttore);
	printf("\nInserisci scrittore: ");
	scrittore = inputStringaSicuro(scrittore);
	printf("\nInserisci titolo dell'album: ");
	album = inputStringaSicuro(album);
	printf("\nInserisci durata: ");
	durata = inputStringaSicuro(durata);
	printf("\nInserisci anno di incisione: ");
	anno = inputStringaSicuro(anno);
	printf("\nInserisci lingua del brano: ");
	lingua = inputStringaSicuro(lingua);
	sprintf(lingua, "%d", linguaNumerica(lingua));
	printf("\nInserisci numero di ascolti: ");
	ascolti = inputStringaSicuro(ascolti);
	printf("\nInserisci gradimento: ");
	gradimento = inputStringaSicuro(gradimento);
	// Memorizzo le informazioni direttamente nel file
	// TODO: Passare ad un sistema esclusivamente struct per poi memorizzare nel file
	inserisciBranoGuidato(0, id, titolo, artista, feat, produttore, scrittore, album, durata, anno, lingua, ascolti, gradimento);
	// Libero la memoria
	free(id); free(titolo); free(artista); free(feat); free(produttore); free(scrittore); free(album); free(durata); free(anno); free(lingua); free(ascolti); free(gradimento);
	// Possibilitï¿½ di scelta da parte dell'utente
	int scelta_2=0;
	printf("\nVuoi inserire un altro brano? [0/1]: ");
	scanf("%d", &scelta_2);
	if(scelta_2==1)
		inserimentoGuidato();
	else
		menu();
}

// Inserimento del brano su base Titolo/Artista/Album/Durata/Anno di incisione
void inserisciBranoGuidato(int modalita, char id[], char titolo[], char artista[], char feat[], char produttore[], char scrittore[], char album[], char durata[], char anno[], char lingua[], char ascolti[], char gradimento[]) {
	FILE* fp=fopen(file_database, "a");
	if (controllaSeDatabaseVuoto()==1) {
		fprintf(fp, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s", id, titolo, artista, feat, produttore, scrittore, album, durata, anno, lingua, ascolti, gradimento);
	} else {
		fprintf(fp, "\n%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s", id, titolo, artista, feat, produttore, scrittore, album, durata, anno, lingua, ascolti, gradimento);
	}
	fclose(fp);
	if (modalita==0) {
		free(brani);
		brani = ottieniDatabase();
		printf("\nBrano inserito.");
	}
}

void inserimentoDiretto() {
	// Flush per evitare indesiderati comportamenti dell'input
	pulisciBuffer();
	char *stringa = malloc(MAX_CHAR*12); // MAX_CHAR*12 poiché ci sono 12 informazioni alle quali precedentemente abbiamo dato solo un MAX_CHAR
	printf("\nInserisci ora il tuo brano: ");
	fgets(stringa, MAX_CHAR*12, stdin);
	strtok(stringa, "\n");
	inserisciBranoDiretto(stringa);
	free(stringa);
	int scelta_2=0;
	printf("\nVuoi inserire un altro brano? [0/1]: ");
	scanf("%d", &scelta_2);
	if(scelta_2==1)
		inserimentoDiretto();
	else
		menu();
}

// Funzione DEV per l'inserimento diretto di un brano
void inserisciBranoDiretto(char stringa[]) {
	FILE* fp=fopen(file_database, "a");
	if (controllaSeDatabaseVuoto()==1) {
		fprintf(fp, "%s", stringa);
	} else {
		fprintf(fp, "\n%s", stringa);
	}
	fclose(fp);
	free(brani);
	brani = ottieniDatabase();
	printf("\nBrano inserito.");
}

void modifica(int scelta) {
	int pos;
	printf("\n===Sistema di modifica dei brani===");
	printf("\nScegliere il brano da modificare");
	aspetta();
	elencaTuttiBrani();
	printf("\n\nInserire il numero del brano da modificare: ");
	scanf("%d", &pos);
	pos--;
	printf("\nHai scelto il brano: ");
	elencaSingoloBrano(pos);
	modificaSingoloBrano(pos, scelta);
	aggiornaDatabase();
}

void modificaSingoloBrano(int pos, int modalita) {
	if (modalita==1) {
		pulisciBuffer();
		char *titolo = malloc(MAX_CHAR);
		printf("\nInserisci nuovo titolo: ");
		titolo = inputStringaSicuro(titolo);
		strcpy(brani[pos].titolo, titolo);
		free(titolo);
	} else if (modalita==2) {
		pulisciBuffer();
		char *artista = malloc(MAX_CHAR);
		printf("\nInserisci nuovo artista: ");
		artista = inputStringaSicuro(artista);
		strcpy(brani[pos].artista, artista);
		free(artista);
	} else if (modalita==3) {
		pulisciBuffer();
		char *feat = malloc(MAX_CHAR);
		printf("\nInserisci nuovo feat: ");
		feat = inputStringaSicuro(feat);
		strcpy(brani[pos].feat, feat);
		free(feat);
	} else if (modalita==4) {
		pulisciBuffer();
		char *produttore = malloc(MAX_CHAR);
		printf("\nInserisci nuovo produttore: ");
		produttore = inputStringaSicuro(produttore);
		strcpy(brani[pos].produttore, produttore);
		free(produttore);
	} else if (modalita==5) {
		pulisciBuffer();
		char *scrittore = malloc(MAX_CHAR);
		printf("\nInserisci nuovo scrittore: ");
		scrittore = inputStringaSicuro(scrittore);
		strcpy(brani[pos].scrittore, scrittore);
		free(scrittore);
	} else if (modalita==6) {
		pulisciBuffer();
		char *album = malloc(MAX_CHAR);
		printf("\nInserisci nuovo album: ");
		album = inputStringaSicuro(album);
		strcpy(brani[pos].album, album);
		free(album);
	} else if (modalita==7) {
		pulisciBuffer();
		char *durata = malloc(MAX_CHAR);
		printf("\nInserisci nuova durata: ");
		durata = inputStringaSicuro(durata);
		strcpy(brani[pos].durata, durata);
		free(durata);
	} else if (modalita==8) {
		pulisciBuffer();
		int anno=0;
		printf("\nInserisci nuovo anno: ");
		scanf("%d", &anno);
		brani[pos].anno=anno;
	} else if (modalita==9) {
		pulisciBuffer();
		char *lingua = malloc(MAX_CHAR);
		printf("\nInserisci nuova lingua: ");
		lingua = inputStringaSicuro(lingua);
		brani[pos].lingua=linguaNumerica(lingua);
		free(lingua);
	} else if (modalita==10) {
		pulisciBuffer();
		int ascolti=0;
		printf("\nInserisci nuovo numero di ascolti: ");
		scanf("%d", &ascolti);
		brani[pos].ascolti=ascolti;
	} else if (modalita==11) {
		pulisciBuffer();
		float gradimento=0.0;
		printf("\nInserisci nuovo gradimento: ");
		scanf("%f", &gradimento);
		brani[pos].gradimento=gradimento;
	}

	printf("\nBrano aggiornato. Ecco il risultato:");
	elencaSingoloBrano(pos);
}

void cancella() {
	int id = 0, controllo = 0;
	char scelta = 'N';
	while (controllo!=-1) {
		printf("\nInserisci id del brano da cancellare: ");
		scanf("%d", &id);
		elencaSingoloBrano(trovaPosizioneBranoId(id));
		pulisciBuffer();
		printf("\nConfermi che il brano da cancellare e' questo? [Y/N]: ");
		scanf("%c", &scelta);
		if (scelta=='Y'||scelta=='y') {
			cancellaSingoloBrano(trovaPosizioneBranoId(id));
			aggiornaDatabase();
			controllo=-1;
		}
	}
}

void cancellaSingoloBrano(int pos) {
	int nbrani = conteggiaBrani();
	int i = pos;
	while (i<nbrani-1) {
		brani[i] = brani[i+1];
		i++;
	}
	brani[nbrani-1].id=0;
}

void cancellaLibreria() {
	int controllo=0;
	char scelta='N';
	while (controllo!=-1) {
		pulisciBuffer();
		printf("\nStai per cancellare la tua intera libreria musicale, sei sicuro? [Y/N]: ");
		scanf("%c", &scelta);
		if (scelta=='Y'||scelta=='y') {
			pulisciBuffer();
			printf("\nVorresti effettuare un backup prima di procedere? [Y/N]: ");
			scanf("%c", &scelta);
			if (scelta=='Y'||scelta=='y') {
				pulisciBuffer();
				char* nome_backup = malloc(MAX_CHAR);
				printf("\nInserisci il file con estensione del backup (es. backup.txt): ");
				nome_backup = inputStringaSicuro(nome_backup);
				backupDatabase(nome_backup);
				free(nome_backup);
			}
			printf("\nCancellazione in corso...");
			cancellaTuttiBrani();
			printf("\nCancellazione effettuata con successo.");
			controllo=-1;
		} else {
			printf("\nCancellazione annullata.");
			controllo=-1;
		}
	}
}

void cancellaTuttiBrani() {
	remove(file_database);
	int i=0;
	while(i<conteggiaBrani()) {
		brani[i].id=0;
		i++;
	}
	creaDatabase();
}
