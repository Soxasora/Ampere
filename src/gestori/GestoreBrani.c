/*
 * Ampere 0.2.1 rev.1 - 04.06.2020
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

#include "../database/Brano.h"
#include "../gestori/GestoreArtisti.h"
#include "../gestori/GestoreAlbum.h"
#include "../gestori/GestoreGeneri.h"
#include "../database/Database.h"
#include "../database/DatabaseUtils.h"
#include "../sys/Messaggi.h"
#include "../sys/Utils.h"
#include "../sys/Impostazioni.h"

database inserimentoBranoGuidato(database db) {
	char scelta='a';
	int i=0, controllo=0, nArtisti=0, nAlbum=0, nGeneri=0;
	int* idArtisti = calloc(MAX_MEDIO, sizeof(int));
	int* idAlbum = calloc(MAX_MEDIO, sizeof(int));
	int* idGeneri = calloc(MAX_MEDIO, sizeof(int));
	char *titolo, *artista, *album, *genere;
	int durata=0, anno=0, ascolti=0;
	// Registrazione
	do {
		if ((titolo=malloc(MAX_MEDIO))) {
			//pulisciBuffer();
			printf("\nInserisci titolo: ");
			titolo = inputStringaSicuro(MAX_MEDIO,titolo);
		}
		while (nArtisti<1||nArtisti>MAX_MEDIO) {
			printf("\nQuanti artisti hanno lavorato su questo brano? ");
			nArtisti = inputNumero();
		}
		i=0;
		while (i<nArtisti) {
			do {
				if ((artista=malloc(MAX_MEDIO))) {
					//pulisciBuffer();
					printf("\nInserisci nome artista n.%d: ", i+1);
					artista = inputStringaSicuro(MAX_MEDIO,artista);
					db = creaArtistaSeNonEsiste(db, artista);
				}
			} while (db.ultimoEsito!=0);
			idArtisti[i] = controlloEsistenzaArtista(db, artista);
			free(artista); artista=NULL;
			i++;
		}
		while (nAlbum<1||nAlbum>MAX_MEDIO) {
			printf("\nDi quanti album fa parte questa canzone? ");
			nAlbum = inputNumero();
		}
		i=0;
		while (i<nAlbum) {
			do {
				if ((album=malloc(MAX_MEDIO))) {
					//pulisciBuffer();
					printf("\nInserisci nome album n.%d: ", i+1);
					album = inputStringaSicuro(MAX_MEDIO,album);
					db = creaAlbumSeNonEsiste(db, album);
				}
			} while (db.ultimoEsito!=0);
			idAlbum[i] = controlloEsistenzaAlbum(db, album);
			free(album); album=NULL;
			i++;
		}
		while (nGeneri<1||nGeneri>MAX_MEDIO) {
			printf("\nQuanti generi ha questa canzone? ");
			nGeneri = inputNumero();
		}
		i=0;
		while (i<nGeneri) {
			do {
				if ((genere=malloc(MAX_MEDIO))) {
					//pulisciBuffer();
					printf("\nInserisci genere n.%d del brano: ", i+1);
					genere = inputStringaSicuro(MAX_MEDIO,genere);
					db = creareGenereSeNonEsiste(db, genere);
				}
			} while (db.ultimoEsito!=0);
			idGeneri[i] = controllareEsistenzaGenere(db, genere);
			free(genere); genere=NULL;
			i++;
		}
		//pulisciBuffer();
		while (durata<=0) {
			printf("\nInserisci durata del brano in secondi: ");
			durata = inputNumero();
		}
		while (anno<=1950) {
			printf("\nInserisci anno d'uscita del brano: ");
			anno = inputNumero();
		}
		while (ascolti<=0) {
			printf("\nInserisci numero d'ascolti del brano: ");
			ascolti = inputNumero();
		}
		struct Brano nuovoBrano = creaBrano(titolo, durata, anno, ascolti);
		free(titolo); titolo=NULL;
		// Mostra anteprima del brano
		mostrareAnteprimaBrano(db, nuovoBrano, idArtisti, idAlbum, idGeneri);
		//pulisciBuffer();
		while (controllo!=-1) {
			printf("\nSicuro di voler continuare? [Y/N]: ");
			scelta = inputCarattere();
			if (scelta=='Y'||scelta=='y'||scelta=='N'||scelta=='n') {
				controllo=-1;
			}
		}
		if (scelta=='Y'||scelta=='y') {
			// Ricerca similitudini
			db = controllaEsistenzaBrano(db, nuovoBrano);
			if (db.ultimoEsito==0) {
				db = inserireBrano(db, nuovoBrano, idArtisti, idAlbum, idGeneri);
				printf("\n\nBrano Inserito.");
			}
			db.ultimoEsito=0;
		} else {
			db.ultimoEsito=-1;
		}
	} while (db.ultimoEsito!=0);
	return db;
}

struct Brano creaBrano(char titolo[], int durata, int anno, int ascolti) {
	struct Brano nuovoBrano;
	nuovoBrano.id = -1;
	strcpy(nuovoBrano.titolo,titolo);
	nuovoBrano.durata = durata;
	nuovoBrano.anno = anno;
	nuovoBrano.ascolti = ascolti;
	return nuovoBrano;
}

void mostrareAnteprimaBrano(database db, struct Brano nuovoBrano, int* idArtisti, int* idAlbum, int* idGeneri) {
	int i=0;
	int posAlbum = 0, posArtista = 0, posGenere = 0;
	printf("\nIl brano che stai per inserire ha questi dettagli:"
		   "\nTitolo: %s"
		   "\nDurata: %s"
		   "\nArtisti: ", nuovoBrano.titolo, convertiSecondiInTempo(nuovoBrano.durata));
	i=0;
	while (idArtisti[i]!=0) {
		posArtista = ottenerePosDaID(db, 2, idArtisti[i]);
		if (i!=0)
			printf(", ");
		printf("%s", db.artista[posArtista].nomeArte);
		i++;
	}
	printf("\nAlbum: ");
	i=0;
	while (idAlbum[i]!=0) {
		posAlbum = ottenerePosDaID(db, 1, idAlbum[i]);
		if (i!=0)
			printf(", ");
		printf("%s", db.album[posAlbum].titolo);
		i++;
	}
	printf("\nGeneri: ");
	i=0;
	while (idGeneri[i]!=0) {
		posGenere = ottenerePosDaID(db, 3, idGeneri[i]);
		if (i!=0)
			printf(", ");
		printf("%s", db.genere[posGenere].nome);
		i++;
	}
	printf("\nAnno: %d"
		   "\nAscolti: %d", nuovoBrano.anno, nuovoBrano.ascolti);
}

database inserireBrano(database db, struct Brano nuovoBrano, int idArtisti[], int idAlbum[], int idGeneri[]) {
	int i=0;
	db_modificato=1;
	int n=contareNelDatabase(db,0);
	nuovoBrano.id = trovareUltimoId(db, 0)+1;
	db.brano[n] = nuovoBrano;

	// Associazioni
	i=0;
	while (idArtisti[i]!=0) {
		inserireAssociazioneArtista(db,creaAssociazioneArtista(nuovoBrano.id, idArtisti[i]));
		i++;
	}
	i=0;
	while (idAlbum[i]!=0) {
		inserireAssociazioneAlbum(db,creaAssociazioneAlbum(nuovoBrano.id, idAlbum[i]));
		i++;
	}
	i=0;
	while (idGeneri[i]!=0) {
		inserireAssociazioneGenere(db,creaAssociazioneGenere(nuovoBrano.id, idGeneri[i]));
		i++;
	}

	return db;
}

database controllaEsistenzaBrano(database db, struct Brano nuovoBrano) {
	// Ricerca su base
	printf("\nRicerco eventuali similitudini con i brani gia' presenti...");
	char scelta='a';
	int controllo=0, occorrenze=0, i=0, n=contareNelDatabase(db, 0);
	bool trovato=false;
	while (i<n) {
		occorrenze=0;
		if (comparaStringheParziale(db.brano[i].titolo, nuovoBrano.titolo)==0) {
			occorrenze++;
			if (db.brano[i].anno == nuovoBrano.anno) {
				occorrenze++;
			}
			if (db.brano[i].durata == nuovoBrano.durata) {
				occorrenze++;
			}
		}
		if (occorrenze>0) {
			printf("\n\nTrovata similitudine"
				   "\nBrano simile: ");
			mostraSingoloBrano(db, db.brano[i].id);
			trovato=true;
		}
		i++;
	}

	if (trovato) {
		while (controllo!=-1) {
			//pulisciBuffer();
			printf("\n\nSulla base delle suddette scoperte, vuoi continuare ugualmente con l'inserimento? [Y/N]: ");
			scelta = inputCarattere();
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

void inserisciBranoSuFile(struct Brano brano) {
	FILE* fp=fopen(file_brani, "a");
	if (controllaSeFileVuoto(file_brani)==1) {
		fprintf(fp, "%d|%s|%d|%d|%d", brano.id, brano.titolo, brano.durata, brano.anno, brano.ascolti);
	} else {
		fprintf(fp, "\n%d|%s|%d|%d|%d", brano.id, brano.titolo, brano.durata, brano.anno, brano.ascolti);
	}
	fclose(fp);
}

database modificareBranoGuidato(database db) {
	int id=0, campo=-1;
	char scelta='a';
	db = moduloRicercaBrani(db);
	while (ottenerePosDaID(db, 0,id)==-1) {
		printf("\n\nInserire l'identificativo del brano da modificare: ");
		id = inputNumero();
		if (ottenerePosDaID(db, 0,id)==-1) {
			printf("\nBrano non trovato, riprovare");
		}
	}
	printf("\nHai scelto il brano:");
	mostraSingoloBrano(db, id);
	//pulisciBuffer();
	scelta = richiesta(0);
	if (scelta=='Y'||scelta=='y') {
		do {
			printf("\n===[Sistema di modifica brani]===");
			printf("\n[1] Modifica il Titolo");
			printf("\n[2] Modifica la Durata");
			printf("\n[3] Modifica l'Anno");
			printf("\n[4] Modifica gli Ascolti");
			printf("\n[5] Modifica gli artisti d'appartenenza");
			printf("\n[6] Modifica gli album d'appartenenza");
			printf("\n[7] Modifica i generi d'appartenenza");
			printf("\n[0] Esci");
			while (campo<0||campo>7) {
				printf("\nInserisci la tua scelta: ");
				campo = inputNumero();
			}
			if (campo!=0) {
				db = creareBranoModificato(db, campo, id);
				if (db.ultimoEsito==0) {
					printf("\nBrano modificato.");
				}
			} else {
				db.ultimoEsito=-2;
			}
		} while (db.ultimoEsito==-1);
	}
	return db;
}

database creareBranoModificato(database db, int campo, int id) {
	char scelta='a';
	int pos = ottenerePosDaID(db, 0, id);
	struct Brano branoModificato = db.brano[pos];
	int* idAssociazioni = calloc(MAX_MEDIO, sizeof(int));
	do {
		//pulisciBuffer();
		if (campo==1) {
			char *titolo = malloc(MAX_MEDIO);
			printf("\nInserisci nuovo titolo: ");
			titolo = inputStringaSicuro(MAX_MEDIO,titolo);
			strcpy(branoModificato.titolo, titolo);
			free(titolo);
		} else if (campo==2) {
			int durata=0;
			while (durata<1) {
				printf("\nInserisci nuova durata (in secondi): ");
				durata = inputNumero();
			}
			branoModificato.durata = durata;
		} else if (campo==3) {
			int anno=0;
			while (anno<=1950) {
				printf("\nInserisci nuovo anno: ");
				anno = inputNumero();
			}
			branoModificato.anno = anno;
		} else if (campo==4) {
			int ascolti=0;
			while (ascolti<=0) {
				printf("\nInserisci nuovi ascolti: ");
				ascolti = inputNumero();
			}
			branoModificato.ascolti = ascolti;
		} else if (campo==5) {
			char *artista;
			int i=0, nArtisti=0;
			idAssociazioni = calloc(MAX_MEDIO, sizeof(int));
			printf("\nQuanti artisti ha il brano? ");
			nArtisti = inputNumero();
			i=0;
			while (i<nArtisti) {
				do {
					if ((artista = malloc(MAX_MEDIO))) {
						printf("\nInserisci nome d'arte artista n.%d: ", i+1);
						artista = inputStringaSicuro(MAX_MEDIO,artista);
						db = creaArtistaSeNonEsiste(db, artista);
						idAssociazioni[i] = controlloEsistenzaArtista(db, artista);
					}
				} while (db.ultimoEsito!=0);
				free(artista); artista=NULL;
				i++;
			}
		} else if (campo==6) {
			char *album;
			int i=0, nAlbum=0;
			idAssociazioni = calloc(MAX_MEDIO, sizeof(int));
			printf("\nQuanti album ha il brano? ");
			nAlbum = inputNumero();
			i=0;
			while (i<nAlbum) {
				do {
					if ((album = malloc(MAX_MEDIO))) {
						printf("\nInserisci nome album n.%d: ", i+1);
						album = inputStringaSicuro(MAX_MEDIO,album);
						db = creaAlbumSeNonEsiste(db, album);
						idAssociazioni[i] = controlloEsistenzaAlbum(db, album);
					}
				} while (db.ultimoEsito!=0);
				free(album); album=NULL;
				i++;
			}
		} else if (campo==7) {
			char *genere;
			int i=0, nGeneri=0;
			idAssociazioni = calloc(MAX_MEDIO, sizeof(int));
			printf("\nQuanti generi ha il brano? ");
			nGeneri = inputNumero();
			i=0;
			while (i<nGeneri) {
				do {
					if ((genere = malloc(MAX_MEDIO))) {
						printf("\nInserisci nome del genere n.%d: ", i+1);
						genere = inputStringaSicuro(MAX_MEDIO, genere);
						db = creareGenereSeNonEsiste(db, genere);
						idAssociazioni[i] = controllareEsistenzaGenere(db, genere);
					}
				} while (db.ultimoEsito!=0);
				free(genere); genere=NULL;
				i++;
			}
		}
		mostrareAnteprimaModificaBrano(db, id, campo, branoModificato, idAssociazioni);
		scelta = richiesta(0);
		if (scelta=='Y'||scelta=='y') {
			db = modificareBrano(db, id, campo, branoModificato, idAssociazioni);
			db.ultimoEsito=0;
		} else {
			scelta = richiesta(3);
			if (scelta=='Y'||scelta=='y') {
				db.ultimoEsito=-2;
			} else {
				db.ultimoEsito=-1;
			}
		}
	} while (db.ultimoEsito==-2);
	return db;
}

void mostrareAnteprimaModificaBrano(database db, int idBrano, int campo, struct Brano branoModificato, int idAssociazioni[]) {
	printf("\n===[Brano ORIGINALE]===");
	mostraSingoloBrano(db, idBrano);
	printf("\n\n===[Brano MODIFICATO]===");
	int i=0;
	printf("\nTitolo: %s"
		   "\nDurata: %s", branoModificato.titolo, convertiSecondiInTempo(branoModificato.durata));
	if (campo==5) {
		printf(C_VERDE"\n[MODIFICATO]"C_RESET" Artisti: ");
		int posArtista=0;
		while (idAssociazioni[i]!=0) {
			posArtista = ottenerePosDaID(db, 2, idAssociazioni[i]);
			if (i!=0)
				printf(", ");
			printf("%s", db.artista[posArtista].nomeArte);
			i++;
		}
	} else {
		mostrareAssociazioni(db, 0, idBrano);
	}
	if (campo==6) {
		printf(C_VERDE"\n[MODIFICATO]"C_RESET" Album: ");
		int posAlbum = 0;
		while (idAssociazioni[i]!=0) {
			posAlbum = ottenerePosDaID(db, 1, idAssociazioni[i]);
			if (i!=0)
				printf(", ");
			printf("%s", db.album[posAlbum].titolo);
			i++;
		}
	} else {
		mostrareAssociazioni(db, 1, idBrano);
	}
	if (campo==7) {
		printf(C_VERDE"\n[MODIFICATO]"C_RESET" Generi: ");
		int posGenere = 0;
		while (idAssociazioni[i]!=0) {
			posGenere = ottenerePosDaID(db, 3, idAssociazioni[i]);
			if (i!=0)
				printf(", ");
			printf("%s", db.genere[posGenere].nome);
			i++;
		}
	} else {
		mostrareAssociazioni(db, 2, idBrano);
	}
	printf("\nAnno: %d"
		   "\nAscolti: %d", branoModificato.anno, branoModificato.ascolti);
}

database modificareBrano(database db, int idBrano, int campo, struct Brano branoModificato, int idAssociazioni[]) {
	int posBrano = ottenerePosDaID(db, 0, idBrano);
	db.brano[posBrano] = branoModificato;
	// Associazioni
	int i=0;
	if (campo==5) {
		db = cancellaAssociazioniArtisti(db, idBrano);
		i=0;
		while (idAssociazioni[i]!=0) {
			inserireAssociazioneArtista(db,creaAssociazioneArtista(branoModificato.id, idAssociazioni[i]));
			i++;
		}
	} else if (campo==6) {
		db = cancellaAssociazioniAlbum(db, idBrano);
		i=0;
		while (idAssociazioni[i]!=0) {
			inserireAssociazioneAlbum(db,creaAssociazioneAlbum(branoModificato.id, idAssociazioni[i]));
			i++;
		}
	} else if (campo==7) {
		db = cancellaAssociazioniGenere(db, idBrano);
		i=0;
		while (idAssociazioni[i]!=0) {
			inserireAssociazioneGenere(db,creaAssociazioneGenere(branoModificato.id, idAssociazioni[i]));
			i++;
		}
	}
	db_modificato=1;
	return db;
}

database cancellaBrano(database db) {
	int id=0, controllo=0;
	char scelta='a';
	mostraTuttiBrani(db);
	while (ottenerePosDaID(db, 0,id)==-1) {
		printf("\n\nInserire l'identificativo del brano da cancellare: ");
		id = inputNumero();
		if (ottenerePosDaID(db, 0,id)==-1) {
			printf("\nBrano non trovato, riprovare");
		}
	}
	printf("\nHai scelto il brano:");
	mostraSingoloBrano(db, id);
	//pulisciBuffer();
	while (controllo!=-1) {
		printf("\nSicuro di voler continuare? [Y/N]: ");
		scelta = inputCarattere();
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
	int scelta=-1, idBrano=0;
	do {
		printf("\nCerca brano del quale si vuole aprire il testo");
		db = moduloRicercaBrani(db);
		if (db.ultimoEsito==-1) {
			scelta = richiesta(2);
			if (scelta=='Y'||scelta=='y') {
				printf("\nContinuo con l'apertura del testo.");
				db.ultimoEsito=0;
			} else {
				printf("\nUscito dall'apertura del testo.");
			}
		} else if (db.ultimoEsito==1) {
			do {
				//pulisciBuffer();
				printf("\nInserisci id del brano selezionato, altrimenti [-1] per cercare di nuovo: ");
				idBrano = inputNumero();
				if (idBrano==-1) {
					db.ultimoEsito=2;
				} else {
					if (ottenerePosDaID(db, 0,idBrano)==-1) {
						printf("\nBrano non trovato, riprovare");
						db.ultimoEsito=0;
					} else {
						apriTesto(idBrano);
						db.ultimoEsito=-1;
					}
				}
			} while (db.ultimoEsito==0);
		}
	} while (db.ultimoEsito!=-1);

}

