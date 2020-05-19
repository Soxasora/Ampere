/*
 * Ampere 0.2 rev. 1 - 28.05.2020
 * Gruppo n.16 - Marco Furone, Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/Ampere/blob/master/LICENSE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ricerca/MotoreRicerca.h"
#include "../gestori/GestoreAssociazioni.h"
#include "../gestori/GestoreFile.h"
#include "../gestori/GestoreBrani.h"
#include "../gestori/GestoreArtisti.h"
#include "../gestori/GestoreAlbum.h"
#include "../gestori/GestoreGeneri.h"
#include "../database/Brani.h"
#include "../database/Database.h"
#include "../database/DatabaseUtils.h"
#include "../sys/Utils.h"
#include "../sys/Impostazioni.h"

database inserimentoBranoGuidato(database db) {
	char scelta='a';
	int i=0, controllo=0, n_artisti=0, n_album=0, n_generi=0;
	int* id_artisti = calloc(10, sizeof(int));
	int* id_album = calloc(10, sizeof(int));
	int* id_generi = calloc(10, sizeof(int));
	char *titolo, *artista, *album, *genere;
	int durata=0, anno=0, ascolti=0;
	// Registrazione
	do {
		if ((titolo=malloc(MAX_MEDIO))) {
			pulisciBuffer();
			printf("\nInserisci titolo: ");
			titolo = inputStringaSicuro(MAX_MEDIO,titolo);
		}
		printf("\nQuanti artisti hanno lavorato su questo brano? ");
		scanf("%d", &n_artisti);
		i=0;
		while (i<n_artisti) {
			do {
				if ((artista=malloc(MAX_MEDIO))) {
					pulisciBuffer();
					printf("\nInserisci nome artista n.%d: ", i+1);
					artista = inputStringaSicuro(MAX_MEDIO,artista);
					db = creaArtistaSeNonEsiste(db, artista);
				}
			} while (db.ultimoEsito!=0);
			id_artisti[i] = controlloEsistenzaArtista(db, artista);
			free(artista); artista=NULL;
			i++;
		}
		printf("\nDi quanti album fa parte questa canzone? ");
		scanf("%d", &n_album);
		i=0;
		while (i<n_album) {
			do {
				if ((album=malloc(MAX_MEDIO))) {
					pulisciBuffer();
					printf("\nInserisci nome album n.%d: ", i+1);
					album = inputStringaSicuro(MAX_MEDIO,album);
					db = creaAlbumSeNonEsiste(db, album);
				}
			} while (db.ultimoEsito!=0);
			id_album[i] = controlloEsistenzaAlbum(db, album);
			free(album); album=NULL;
			i++;
		}
		printf("\nQuanti generi ha questa canzone? ");
		scanf("%d", &n_generi);
		i=0;
		while (i<n_generi) {
			do {
				if ((genere=malloc(MAX_MEDIO))) {
					pulisciBuffer();
					printf("\nInserisci genere n.%d del brano: ", i+1);
					genere = inputStringaSicuro(MAX_MEDIO,genere);
					db = creareGenereSeNonEsiste(db, genere);
				}
			} while (db.ultimoEsito!=0);
			id_generi[i] = controllareEsistenzaGenere(db, genere);
			free(genere); genere=NULL;
			i++;
		}
		pulisciBuffer();
		while (durata<=0||durata>9999) {
			printf("\nInserisci durata del brano in secondi: ");
			scanf("%d", &durata);
		}
		while (anno<=1950||anno>2020) {
			printf("\nInserisci anno d'uscita del brano: ");
			scanf("%d", &anno);
		}
		while (ascolti<=0) {
			printf("\nInserisci numero d'ascolti del brano: ");
			scanf("%d", &ascolti);
		}
		// Mostra anteprima del brano
		struct brani nuovoBrano = creaBrano(titolo, durata, anno, ascolti);
		mostrareAnteprimaBrano(db, nuovoBrano, id_artisti, id_album, id_generi);
		db = controllaEsistenzaBrano(db, nuovoBrano);
		if (db.ultimoEsito==0) {
			pulisciBuffer();
			while (controllo!=-1) {
				printf("\nSicuro di voler continuare? [Y/N]: ");
				scanf("%c", &scelta);
				if (scelta=='Y'||scelta=='y'||scelta=='N'||scelta=='n') {
					controllo=-1;
				}
			}
			if (scelta=='Y'||scelta=='y') {
				db = inserireBrano(db, nuovoBrano, id_artisti, id_album, id_generi);
				printf("\n\nBrano Inserito.");
				db.ultimoEsito=0;
			} else {
				db.ultimoEsito=-1;
			}
		}
	} while (db.ultimoEsito!=0);
	return db;
}

struct brani creaBrano(char titolo[], int durata, int anno, int ascolti) {
	struct brani nuovoBrano;
	nuovoBrano.id = -1;
	strcpy(nuovoBrano.titolo,titolo);
	nuovoBrano.durata = durata;
	nuovoBrano.anno = anno;
	nuovoBrano.ascolti = ascolti;
	return nuovoBrano;
}

void mostrareAnteprimaBrano(database db, struct brani nuovoBrano, int* id_artisti, int* id_album, int* id_generi) {
	int i=0;
	int posalbum = 0, posartista = 0, posgenere = 0;
	printf("\nIl brano che stai per inserire ha questi dettagli:"
		   "\nTitolo: %s"
		   "\nDurata: %s"
		   "\nArtisti: ", nuovoBrano.titolo, convertiSecondiInTempo(nuovoBrano.durata));
	i=0;
	while (id_artisti[i]!=0) {
		posartista = ottenerePosDaID(db, 2, id_artisti[i]);
		if (i!=0)
			printf(", ");
		printf("%s", db.artista[posartista].nomearte);
		i++;
	}
	printf("\nAlbum: ");
	i=0;
	while (id_album[i]!=0) {
		posalbum = ottenerePosDaID(db, 1, id_album[i]);
		if (i!=0)
			printf(", ");
		printf("%s", db.album[posalbum].titolo);
		i++;
	}
	printf("\nGeneri: ");
	i=0;
	while (id_generi[i]!=0) {
		posgenere = ottenerePosDaID(db, 3, id_generi[i]);
		if (i!=0)
			printf(", ");
		printf("%s", db.genere[posgenere].nome);
		i++;
	}
	printf("\nAnno: %d"
		   "\nAscolti: %d", nuovoBrano.anno, nuovoBrano.ascolti);
}

database inserireBrano(database db, struct brani nuovoBrano, int id_artisti[], int id_album[], int id_generi[]) {
	int i=0;
	db_modificato=1;
	int n=contareNelDatabase(db,0);
	nuovoBrano.id = trovareUltimoId(db, 0)+1;
	db.brano[n] = nuovoBrano;

	// Associazioni
	i=0;
	while (id_artisti[i]!=0) {
		inserireAssociazioneArtista(db,creaAssociazioneArtista(nuovoBrano.id, id_artisti[i]));
		i++;
	}
	i=0;
	while (id_album[i]!=0) {
		inserireAssociazioneAlbum(db,creaAssociazioneAlbum(nuovoBrano.id, id_album[i]));
		i++;
	}
	i=0;
	while (id_generi[i]!=0) {
		inserireAssociazioneGenere(db,creaAssociazioneGenere(nuovoBrano.id, id_generi[i]));
		i++;
	}

	return db;
}

database controllaEsistenzaBrano(database db, struct brani nuovoBrano) {
	// Ricerca su base
	printf("\nRicerco eventuali similitudini con i brani gia' presenti...");
	char scelta='a';
	int controllo=0, occorrenze=0, i=0, n=contareNelDatabase(db, 0);
	bool trovato=false;
	while (i<n) {
		occorrenze=0;
		if (comparaStringhe(db.brano[i].titolo, nuovoBrano.titolo)==0) {
			occorrenze++;
		}
		if (db.brano[i].anno == nuovoBrano.anno) {
			occorrenze++;
		}
		if (db.brano[i].durata == nuovoBrano.durata) {
			occorrenze++;
		}
		if (occorrenze>0) {
			printf("\nTrovata similitudine");
			trovato=true;
			printf("\n\nBrano simile: ");
			mostraSingoloBrano(db, db.brano[i].id);
		}
		i++;
	}

	if (trovato) {
		pulisciBuffer();
		while (controllo!=-1) {
			printf("\nSulla base delle suddette scoperte, vuoi continuare ugualmente con l'inserimento? [Y/N]: ");
			scanf("%c", &scelta);
			if (scelta=='Y'||scelta=='y'||scelta=='N'||scelta=='n') {
				controllo=-1;
			}
		}
		if (scelta=='N'||scelta=='n') {
			db.ultimoEsito=-1;
		} else {
			db.ultimoEsito=0;
		}
	} else {
		printf("\nNessuna similitudine trovata, procediamo");
		db.ultimoEsito=0;
	}
	return db;
}

void inserisciBranoSuFile(char id[], char titolo[], char durata[], char anno[], char ascolti[]) {
	FILE* fp=fopen(file_brani, "a");
	if (controllaSeFileVuoto(file_brani)==1) {
		fprintf(fp, "%s|%s|%s|%s|%s", id, titolo, durata, anno, ascolti);
	} else {
		fprintf(fp, "\n%s|%s|%s|%s|%s", id, titolo, durata, anno, ascolti);
	}
	fclose(fp);
}

database modificaBrano(database db) {
	int id=0, modalita=-1, controllo=0;
	char scelta='a';
	mostraTuttiBrani(db);
	while (ottenerePosDaID(db, 0,id)==-1) {
		printf("\n\nInserire l'identificativo del brano da modificare: ");
		scanf("%d", &id);
		if (ottenerePosDaID(db, 0,id)==-1) {
			printf("\nBrano non trovato, riprovare");
		}
	}
	printf("\nHai scelto il brano:");
	mostraSingoloBrano(db, id);
	pulisciBuffer();
	while (controllo!=-1) {
		printf("\nSicuro di voler continuare? [Y/N]: ");
		scanf("%c", &scelta);
		if (scelta=='Y'||scelta=='y'||scelta=='N'||scelta=='n') {
			controllo=-1;
		}
	}
	if (scelta=='Y'||scelta=='y') {
		printf("\n===[Sistema di modifica brani]===");
		printf("\n[1] Modifica il Titolo");
		printf("\n[2] Modifica la Durata");
		printf("\n[3] Modifica l'Anno");
		printf("\n[4] Modifica gli Ascolti");
		printf("\n[5] Modifica gli album d'appartenenza");
		printf("\n[6] Modifica gli artisti d'appartenenza");
		printf("\n[7] Modifica i generi d'appartenenza");
		printf("\n[0] Esci");
		while (modalita<0||modalita>7) {
			printf("\nInserisci la tua scelta: ");
			scanf("%d", &modalita);
		}
		if (modalita!=0) {
			db = modificaSingoloBrano(db, modalita, id);
		}
	}
	return db;
}

database modificaSingoloBrano(database db, int modalita, int id) {
	pulisciBuffer();
	int pos = ottenerePosDaID(db, 0, id);
	if (modalita==1) {
		char *titolo = malloc(MAX_MEDIO);
		printf("\nInserisci nuovo titolo: ");
		titolo = inputStringaSicuro(MAX_MEDIO,titolo);
		strcpy(db.brano[pos].titolo, titolo);
		free(titolo);
	} else if (modalita==2) {
		int durata=0;
		while (durata<=0||durata>9999) {
			printf("\nInserisci nuova durata (in secondi): ");
			scanf("%d", &durata);
		}
		db.brano[pos].durata = durata;
	} else if (modalita==3) {
		int anno=0;
		while (anno<=1950||anno>2020) {
			printf("\nInserisci nuovo anno: ");
			scanf("%d", &anno);
		}
		db.brano[pos].anno = anno;
	} else if (modalita==4) {
		int ascolti=0;
		while (ascolti<=0) {
			printf("\nInserisci nuovi ascolti: ");
			scanf("%d", &ascolti);
		}
		db.brano[pos].durata = ascolti;
	} else if (modalita==5) {
		char *album;
		int i=0, n_album=0;
		int id_album[10];
		printf("\nQuanti album ha il brano? ");
		scanf("%d", &n_album);
		i=0;
		while (i<n_album) {
			do {
				if ((album = malloc(MAX_MEDIO))) {
					printf("\nInserisci nome album n.%d: ", i+1);
					album = inputStringaSicuro(MAX_MEDIO,album);
					db = creaAlbumSeNonEsiste(db, album);
					id_album[i] = controlloEsistenzaAlbum(db, album);
				}
			} while (db.ultimoEsito!=0);
			free(album); album=NULL;
			i++;
		}
		db = cancellaAssociazioniAlbum(db, id);
		i=0;
		while (id_album[i]!=0) {
			inserireAssociazioneAlbum(db,creaAssociazioneAlbum(id, id_album[i]));
			i++;
		}
	} else if (modalita==6) {
		char *artista;
		int i=0, n_artisti=0;
		int id_artista[10];
		printf("\nQuanti artisti ha il brano? ");
		scanf("%d", &n_artisti);
		i=0;
		while (i<n_artisti) {
			do {
				if ((artista = malloc(MAX_MEDIO))) {
					printf("\nInserisci nome d'arte artista n.%d: ", i+1);
					artista = inputStringaSicuro(MAX_MEDIO,artista);
					db = creaArtistaSeNonEsiste(db, artista);
					id_artista[i] = controlloEsistenzaArtista(db, artista);
				}
			} while (db.ultimoEsito!=0);
			free(artista); artista=NULL;
			i++;
		}
		db = cancellaAssociazioniArtisti(db, id);
		i=0;
		while (id_artista[i]!=0) {
			inserireAssociazioneArtista(db,creaAssociazioneArtista(id, id_artista[i]));
			i++;
		}
	} else if (modalita==7) {
		char *genere;
		int i=0, n_generi=0;
		int id_genere[10];
		printf("\nQuanti generi ha il brano? ");
		scanf("%d", &n_generi);
		i=0;
		while (i<n_generi) {
			do {
				if ((genere = malloc(MAX_MEDIO))) {
					printf("\nInserisci nome del genere n.%d: ", i+1);
					genere = inputStringaSicuro(MAX_MEDIO, genere);
					db = creareGenereSeNonEsiste(db, genere);
					id_genere[i] = controllareEsistenzaGenere(db, genere);
				}
			} while (db.ultimoEsito!=0);
			free(genere); genere=NULL;
			i++;
		}
		db = cancellaAssociazioniGenere(db, id);
		i=0;
		while (id_genere[i]!=0) {
			inserireAssociazioneGenere(db, creaAssociazioneGenere(id, id_genere[i]));
			i++;
		}
	}
	db_modificato = 1;
	printf("\nBrano aggiornato, ecco il risultato:\n");
	mostraSingoloBrano(db, id);
	return db;
}

database cancellaBrano(database db) {
	int id=0, controllo=0;
	char scelta='a';
	mostraTuttiBrani(db);
	while (ottenerePosDaID(db, 0,id)==-1) {
		printf("\n\nInserire l'identificativo del brano da cancellare: ");
		scanf("%d", &id);
		if (ottenerePosDaID(db, 0,id)==-1) {
			printf("\nBrano non trovato, riprovare");
		}
	}
	printf("\nHai scelto il brano:");
	mostraSingoloBrano(db, id);
	pulisciBuffer();
	while (controllo!=-1) {
		printf("\nSicuro di voler continuare? [Y/N]: ");
		scanf("%c", &scelta);
		if (scelta=='Y'||scelta=='y'||scelta=='N'||scelta=='n') {
			controllo=-1;
		}
	}
	if (scelta=='Y'||scelta=='y') {
		db = cancellaSingoloBrano(db, id);
		printf("\nBrano cancellato.");
	}
	return db;
}

database cancellaSingoloBrano(database db, int id) {
	int n = contareNelDatabase(db,0);
	int i = ottenerePosDaID(db, 0, id);
	while (i<n-1) {
		db.brano[i] = db.brano[i+1];
		i++;
	}
	db.brano[n-1].id = 0;
	db = cancellaAssociazioniBrano(db, id);

	db_modificato=1;
	return db;
}

database cancellaAssociazioniBrano(database db, int id) {
	//Cancella Associazioni
	db = cancellaAssociazioniArtisti(db, id);

	db = cancellaAssociazioniAlbum(db, id);

	db = cancellaAssociazioniGenere(db, id);
	int n=0, i=0;
	n = contareNelDatabase(db,8);
	i = ottenerePosDaID(db, 8, id);
	while (i<n-1) {
		db.playlistBrano[i] = db.playlistBrano[i+1];
		i++;
	}
	db.playlistBrano[n-1].idPlaylist = 0;
	db.playlistBrano[n-1].idBrano = 0;
	return db;
}

// TESTI

void apriTesto(int idBrano) {
	char *posizione_testo = malloc(MAX_ENORME);
	char *comando = malloc(MAX_ENORME+10);
	FILE *fp;
	if(os==0) {
		sprintf(posizione_testo, "%s\\%d%s", cartella_testi, idBrano, ".txt");
		fp=fopen(posizione_testo, "r");
		if (fp==NULL) {
			printf("\nIl brano scelto non possiede al momento del testo.");
		} else {
			system(posizione_testo);
		}
		fclose(fp);
	} else if (os==1) {
		sprintf(posizione_testo, "%s/%d%s", cartella_testi, idBrano, ".txt");
		fp=fopen(posizione_testo, "r");
		if (fp==NULL) {
			printf("\nIl brano scelto non possiede al momento del testo.");
		} else {
			strcpy(comando, "open ");
			strcat(comando, posizione_testo);
			system(comando);
		}
		fclose(fp);
	} else if (os==2) {
		sprintf(posizione_testo, "%s/%d%s", cartella_testi, idBrano, ".txt");
		fp=fopen(posizione_testo, "r");
		if (fp==NULL) {
			printf("\nIl brano scelto non possiede al momento del testo.");
		} else {
			strcpy(comando, "nano ");
			strcat(comando, posizione_testo);
			system(comando);
		}
		fclose(fp);
	}
}

void apriTestoDaRicerca(database db) {
	int scelta=-1, controllo=0, idbrano=0, esito=0;
	pulisciBuffer();
	printf("\nCerca brano del quale si vuole aprire il testo");
	while (controllo!=-1) {
		while (scelta<0||scelta>4) {
			printf("\nCerca per titolo[0], anno[1], artista[2], album[3], genere[4]: ");
			scanf("%d", &scelta);
		}
		if (scelta==0) {
			esito = mostraBrani(db, 0);
			controllo=-1;
		} else if (scelta==1) {
			esito = mostraBrani(db, 1);
			controllo=-1;
		} else if (scelta==2) {
			esito = mostraBraniArtista(db);
			controllo=-1;
		} else if (scelta==3) {
			esito = mostraBraniAlbum(db);
			controllo=-1;
		} else if (scelta==4) {
			esito = mostraBraniGenere(db);
			controllo=-1;
		} else {
			printf("Scelta sbagliata, riprovare.");
		}
	}
	if (esito==1) {
		while (ottenerePosDaID(db, 0,idbrano)==-1) {
			printf("\nInserisci id del brano selezionato: ");
			scanf("%d", &idbrano);
			if (ottenerePosDaID(db, 0,idbrano)==-1) {
				printf("\nBrano non trovato, riprovare");
			} else {
				apriTesto(idbrano);
			}
		}
	} else {
		printf("\n\nLa ricerca non ha prodotto risultati");
	}
}

void apriTestoDaID(database db) {
	int idbrano=0;
	pulisciBuffer();
	while (ottenerePosDaID(db, 0,idbrano)==-1) {
		printf("\nInserisci l'id del brano del quale si vuole aprire il testo: ");
		scanf("%d", &idbrano);
		if (ottenerePosDaID(db, 0,idbrano)==-1) {
			printf("\nBrano non trovato, riprovare");
		}
	}
}

