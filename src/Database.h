/*
 * FabbAmp 0.1 rev.99 - 17.04.2020
 * Copyright (c) 2020, Michele Barile, Nicolo' Cucinotta, Simone Cervino.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
