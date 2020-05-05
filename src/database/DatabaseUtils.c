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
#include "../gestori/GestoreFile.h"
#include "../database/DatabaseUtils.h"
#include "../database/Database.h"
#include "../sys/Utils.h"
#include "../sys/Impostazioni.h"

/**
 * Le modalità sono le seguenti:
 * -1: Utente
 * 0: Brano
 * 1: Album
 * 2: Artista
 * 3: Genere
 * 4: Playlist
 * 5: Associazione artista-brano
 * 6: Associazione album-brano
 * 7: Associazione genere-brano
 */

int contaNelDatabase(int modalita) {
	int i=0;
	if (modalita==-1) {
		while(db.utente[i].id!=0) {
			i++;
		}
	} else if (modalita==0) { // Brano
		while(db.brano[i].id!=0) {
			i++;
		}
	} else if (modalita==1) { // Conta Album
		while(db.album[i].id!=0) {
			i++;
		}
	} else if (modalita==2) { // Conta Artisti
		while(db.artista[i].id!=0) {
			i++;
		}
	} else if (modalita==3) { // Conta Generi
		while(db.genere[i].id!=0) {
			i++;
		}
	} else if (modalita==4) { // Conta Playlist
		while(db.playlist[i].id!=0) {
			i++;
		}
	} else if (modalita==5) { // Conta associazioniArtisti
		while(db.artistaBrano[i].idBrano!=0) {
			i++;
		}
	} else if (modalita==6) { // Conta collezione
		while(db.albumBrano[i].idAlbum!=0) {
			i++;
		}
	} else if (modalita==7) { // Conta tipi brano
		while(db.branoGenere[i].idBrano!=0) {
			i++;
		}
	}

	return i;
}

int trovaUltimoId(int modalita) {
	int i=0, n=0, max=0;
	n = contaNelDatabase(modalita);
	if (modalita==-1) {
		if (controllaSeFileVuoto(file_utenti)==0) {
			while(i<n) {
				if (db.utente[i].id>max) {
					max=db.utente[i].id;
				}
				i++;
			}
		} else {
			max=0;
		}
	} else if (modalita==0) {
		if (controllaSeFileVuoto(file_brani)==0) {
			while(i<n) {
				if (db.brano[i].id>max) {
					max=db.brano[i].id;
				}
				i++;
			}
		} else {
			max=0;
		}
	} else if (modalita==1) {
		if (controllaSeFileVuoto(file_albums)==0) {
			while(i<n) {
				if (db.album[i].id>max) {
					max=db.album[i].id;
				}
				i++;
			}
		} else {
			max=0;
		}
	} else if (modalita==2) {
		if (controllaSeFileVuoto(file_artisti)==0) {
			while(i<n) {
				if (db.artista[i].id>max) {
					max=db.artista[i].id;
				}
				i++;
			}
		} else {
			max=0;
		}
	} else if (modalita==3) {
		if (controllaSeFileVuoto(file_generi)==0) {
			while(i<n) {
				if (db.genere[i].id>max) {
					max=db.genere[i].id;
				}
				i++;
			}
		} else {
			max=0;
		}
	} else if (modalita==4) {
		if (controllaSeFileVuoto(file_playlists)==0) {
			while(i<n) {
				if (db.playlist[i].id>max) {
					max=db.playlist[i].id;
				}
				i++;
			}
		} else {
			max=0;
		}
	}
	return max;
}

int ottieniPosDaID(int modalita, int id) {
	int pos=0, i=0, controllo=0, n=0;
	n = contaNelDatabase(modalita);
	if (modalita==-1) { // Utente
		while(i<n&&controllo!=-1) {
			if (db.utente[i].id == id) {
				pos=i;
				controllo=-1;
			}
			i++;
		}
	} else if (modalita==0) { // Brano
		while(i<n&&controllo!=-1) {
			if (db.brano[i].id == id) {
				pos=i;
				controllo=-1;
			}
			i++;
		}
	} else if (modalita==1) { // Album
		while(i<n&&controllo!=-1) {
			if (db.album[i].id == id) {
				pos=i;
				controllo=-1;
			}
			i++;
		}
	} else if (modalita==2) { // Artisti
		while(i<n&&controllo!=-1) {
			if (db.artista[i].id == id) {
				pos=i;
				controllo=-1;
			}
			i++;
		}
	} else if (modalita==3) { // Generi
		while(i<n&&controllo!=-1) {
			if (db.genere[i].id == id) {
				pos=i;
				controllo=-1;
			}
			i++;
		}
	} else if (modalita==4) { // Playlist
		while(i<n&&controllo!=-1) {
			if (db.playlist[i].id == id) {
				pos=i;
				controllo=-1;
			}
			i++;
		}
	} else if (modalita==5) { // Associazione artista-brano
		while(i<n&&controllo!=-1) {
			if (db.artistaBrano[i].idBrano==id) {
				pos = i;
				controllo=-1;
			}
			i++;
		}
	} else if (modalita==6) { //Associazione album-brano
		while(i<n&&controllo!=-1) {
			if (db.albumBrano[i].idBrano==id) {
				pos = i;
				controllo=-1;
			}
			i++;
		}
	} else if (modalita==7) { // Associazione genere-brano
		while(i<n&&controllo!=-1) {
			if (db.branoGenere[i].idBrano==id) {
				pos = i;
				controllo=-1;
			}
			i++;
		}
	}

	return pos;
}

void backupDatabase() {
	pulisciBuffer();
	char *nome_backup = malloc(MAX_CHAR);
	char *percorso_backup = malloc(MAX_CHAR);
	creaCartella("backup");
	// Inserire sistema di ottenimento automatico della data
	printf("\nInserire il nome della cartella del nuovo backup (es. 05052020): ");
	nome_backup = inputStringaSicuro(nome_backup);
	sprintf(percorso_backup, "backup\\%s", nome_backup);
	creaCartella(percorso_backup);
	printf("\nBackup del database in corso...");
	sprintf(percorso_backup, "backup\\%s\\brani.txt", nome_backup);
	backupFile(file_brani, percorso_backup);
	sprintf(percorso_backup, "backup\\%s\\albums.txt", nome_backup);
	backupFile(file_albums, percorso_backup);
	sprintf(percorso_backup, "backup\\%s\\associazioneartisti.txt", nome_backup);
	backupFile(file_associazioneartisti, percorso_backup);
	sprintf(percorso_backup, "backup\\%s\\artisti.txt", nome_backup);
	backupFile(file_artisti, percorso_backup);
	sprintf(percorso_backup, "backup\\%s\\collezione.txt", nome_backup);
	backupFile(file_collezione, percorso_backup);
	sprintf(percorso_backup, "backup\\%s\\generi.txt", nome_backup);
	backupFile(file_generi, percorso_backup);
	sprintf(percorso_backup, "backup\\%s\\tipobrano.txt", nome_backup);
	backupFile(file_tipobrano, percorso_backup);
	sprintf(percorso_backup, "backup\\%s\\playlists.txt", nome_backup);
	backupFile(file_playlists, percorso_backup);
	sprintf(percorso_backup, "backup\\%s\\raccolta.txt", nome_backup);
	backupFile(file_raccolta, percorso_backup);
	sprintf(percorso_backup, "backup\\%s\\utenti.txt", nome_backup);
	backupFile(file_utenti, percorso_backup);
	printf(" Backup effettuato.");
	free(nome_backup); free(percorso_backup);
}

void ripristinaDatabase() {
	pulisciBuffer();
	char *nome_backup = malloc(MAX_CHAR);
	char *percorso_backup = malloc(MAX_CHAR);
	printf("\nInserire il nome del backup dal quale ripristinare il database (es. 05052020): ");
	nome_backup = inputStringaSicuro(nome_backup);
	sprintf(percorso_backup, "backup\\%s\\brani.txt", nome_backup);
	FILE* fp=fopen(percorso_backup, "r");
	if (fp==NULL) {
		perror("Impossibile continuare con il ripristino, motivazione: ");
		fclose(fp);
	} else {
		fclose(fp);
		char scelta='N';
		printf("\nSicuro di voler continuare con il ripristino? [Y/N]: ");
		scanf("%c", &scelta);
		if (scelta=='Y'||scelta=='y') {
			printf("\nRipristino del database in corso...");
			cancellaDatabaseFile();
			sprintf(percorso_backup, "backup\\%s\\brani.txt", nome_backup);
			backupFile(percorso_backup, file_brani);
			sprintf(percorso_backup, "backup\\%s\\albums.txt", nome_backup);
			backupFile(percorso_backup, file_albums);
			sprintf(percorso_backup, "backup\\%s\\associazioneartisti.txt", nome_backup);
			backupFile(percorso_backup, file_associazioneartisti);
			sprintf(percorso_backup, "backup\\%s\\artisti.txt", nome_backup);
			backupFile(percorso_backup, file_artisti);
			sprintf(percorso_backup, "backup\\%s\\collezione.txt", nome_backup);
			backupFile(percorso_backup, file_collezione);
			sprintf(percorso_backup, "backup\\%s\\generi.txt", nome_backup);
			backupFile(percorso_backup, file_generi);
			sprintf(percorso_backup, "backup\\%s\\tipobrano.txt", nome_backup);
			backupFile(percorso_backup, file_tipobrano);
			sprintf(percorso_backup, "backup\\%s\\playlists.txt", nome_backup);
			backupFile(percorso_backup, file_playlists);
			sprintf(percorso_backup, "backup\\%s\\raccolta.txt", nome_backup);
			backupFile(percorso_backup, file_raccolta);
			sprintf(percorso_backup, "backup\\%s\\utenti.txt", nome_backup);
			backupFile(percorso_backup, file_utenti);
			db = ottieniDatabase();
			printf(" Ripristino dal backup %s effettuato.", nome_backup);
		} else {
			printf("\nUscendo dal ripristino...");
		}
	}
}
