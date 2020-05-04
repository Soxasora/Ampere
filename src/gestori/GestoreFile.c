/*
 * Ampere 0.1 rev. 1250 - 04.05.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../gestori/GestoreBrani.h"
#include "../gestori/GestoreArtisti.h"
#include "../gestori/GestoreAlbum.h"
#include "../gestori/GestoreGeneri.h"
#include "../gestori/GestoreFile.h"
#include "../database/DatabaseUtils.h"
#include "../database/Database.h"
#include "../sys/Utils.h"
#include "../sys/Impostazioni.h"

void salvaModificheSuFile() {
	printf("\nSalvando tutte le modifiche effettuate al database, su file...");
	salvaBraniSuFile();
	salvaAlbumSuFile();
	salvaArtistiSuFile();
	salvaGeneriSuFile();

	// Blocco associazioni
	salvaCollezioneSuFile();
	salvaAssociazioniArtistiSuFile();
	salvaTipiBraniSuFile();


//	backupFile("temp_playlists.txt", file_playlists);
//	backupFile("temp_raccolta.txt", file_raccolta);
//	backupFile("temp_utenti.txt", file_utenti);


//	remove(file_playlists);
//	remove(file_raccolta);
//	remove(file_utenti);
	printf("\nSalvato.");
}

void salvaBraniSuFile() {
	printf("\nSalvando i brani...");
	backupFile(file_brani, "temp_brani.txt");
	remove(file_brani);
	int i=0;
	int n=contaNelDatabase(0);
	while (i<n) {
		char id[MAX_CHAR], durata[MAX_CHAR], album[MAX_CHAR], anno[5], ascolti[MAX_CHAR];
		sprintf(id, "%d", db.brano[i].id);
		sprintf(durata, "%d", db.brano[i].durata);
		sprintf(album, "%d", db.brano[i].album);
		sprintf(anno, "%d", db.brano[i].anno);
		sprintf(ascolti, "%d", db.brano[i].ascolti);
		inserisciBranoSuFile(id, db.brano[i].titolo, durata, album, anno, ascolti);
		i++;
	}
	remove("temp_brani.txt");
	printf(" Brani salvati.");
}

void salvaAlbumSuFile() {
	printf("\nSalvando gli album...");
	backupFile(file_albums, "temp_albums.txt");
	remove(file_albums);
	int i=0;
	int n=contaNelDatabase(1);
	while (i<n) {
		char id[MAX_CHAR], anno[5];
		sprintf(id, "%d", db.album[i].id);
		sprintf(anno, "%d", db.album[i].anno);
		inserisciAlbumSuFile(id, db.album[i].titolo, anno);
		i++;
	}
	remove("temp_albums.txt");
	printf(" Album salvati.");
}

void salvaArtistiSuFile() {
	printf("\nSalvando gli artisti...");
	backupFile(file_artisti, "temp_artisti.txt");
	remove(file_artisti);
	int i=0;
	int n=contaNelDatabase(2);
	while (i<n) {
		char id[MAX_CHAR];
		sprintf(id, "%d", db.artista[i].id);
		inserisciArtistiSuFile(id, db.artista[i].nome, db.artista[i].cognome, db.artista[i].nomearte);
		i++;
	}
	remove("temp_artisti.txt");
	printf(" Artisti salvati.");
}

void salvaGeneriSuFile() {
	printf("\nSalvando i generi...");
	backupFile(file_generi, "temp_generi.txt");
	remove(file_generi);
	int i=0;
	int n=contaNelDatabase(3);
	while (i<n) {
		char id[MAX_CHAR];
		sprintf(id, "%d", db.genere[i].id);
		inserisciGenereSuFile(id, db.genere[i].nome);
		i++;
	}
	remove("temp_generi.txt");
	printf(" Generi salvati.");
}

//BLOCCO ASSOCIAZIONI

void salvaCollezioneSuFile() {
	printf("\nSalvando le associazioni album-brano su file...");
	backupFile(file_collezione, "temp_collezione.txt");
	remove(file_collezione);
	int i=0;
	int n=contaNelDatabase(6);
	while (i<n) {
		char idAlbum[MAX_CHAR], idBrano[MAX_CHAR];
		sprintf(idAlbum, "%d", db.albumBrano[i].idAlbum);
		sprintf(idBrano, "%d", db.albumBrano[i].idBrano);
		inserisciCollezioneSuFile(idAlbum, idBrano);
		i++;
	}
	remove("temp_collezione.txt");
	printf(" Associazioni album-brano salvate.");
}

void salvaAssociazioniArtistiSuFile() {
	printf("\nSalvando le associazioni artista-brano su file...");
	backupFile(file_associazioneartisti, "temp_associazioneartisti.txt");
	remove(file_associazioneartisti);
	int i=0;
	int n=contaNelDatabase(5);
	while(i<n) {
		char idBrano[MAX_CHAR], idArtista[MAX_CHAR];
		sprintf(idBrano, "%d", db.artistaBrano[i].idBrano);
		sprintf(idArtista, "%d", db.artistaBrano[i].idArtista);
		inserisciAssociazioneArtistiSuFile(idBrano, idArtista);
		i++;
	}
	remove("temp_associazioneartisti.txt");
	printf(" Associazioni artista-brano salvate.");
}

void salvaTipiBraniSuFile() {
	printf("\nSalvando le associazioni genere-brano su file...");
	backupFile(file_tipobrano, "temp_tipobrano.txt");
	remove(file_tipobrano);
	int i=0;
	int n=contaNelDatabase(7);
	while(i<n) {
		char idBrano[MAX_CHAR], idGenere[MAX_CHAR];
		sprintf(idBrano, "%d", db.branoGenere[i].idBrano);
		sprintf(idGenere, "%d", db.branoGenere[i].idGenere);
		inserisciTipiBraniSuFile(idBrano, idGenere);
		i++;
	}
	remove("temp_tipobrano.txt");
	printf(" Associazioni genere-brano salvate.");
}
