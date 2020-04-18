/*
 * FabbAmp 0.1 rev.99 - 17.04.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/FabbAmp/blob/master/LICENSE
 */

#ifndef DATABASE_H_
#define DATABASE_H_
#define MAX_CHAR 256

// Struttura per mantenere in memoria la Libreria Musicale di FabbAmp
// TODO: Passare ad allocazione dinamica
typedef struct libreriaMusicale {
	char titolo[MAX_CHAR];
	char artista[MAX_CHAR];
	char album[MAX_CHAR];
	char durata[MAX_CHAR];
	int anno;
	int ascolti;
	float gradimento;
} database;

// Database struct globale per evitare inutili accessi al database file-based
database* brani;

/**
 * Controlla l'esistenza del database e se esso non esiste, viene creato automaticamente
 */
void creaDatabaseSeNonEsiste();

/**
 * Carica il database file-based in memoria riempiendo, dunque, lo struct globale libreriaMusicale
 * @return database* brani riempito
 */
database* ottieniDatabase();

/**
 * Salva le modifiche effettuate allo struct in memoria nel database file-based,
 * effettuando il backup e la riscrittura del database
 */
void aggiornaDatabase();

#endif /* DATABASE_H_ */
