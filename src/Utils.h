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

#ifndef UTILS_H_
#define UTILS_H_

/**
 * Stampa delle informazioni sul programma
 */
void info();

/**
 * Pulisce il buffer stdin per evitare comportamenti inaspettati al momento dell'inserimento
 */
void pulisciBuffer();

/**
 * Macro per rendere portatile la funzione di pausa
 */
void aspetta();

/**
 * Funzione di controllo del contenuto del file
 * @return 0 se il file contiene informazioni, 1 se il file è vuoto
 */
int controllaSeFileVuoto();

/**
 * Funzione di conteggio dei caratteri presenti nel file
 * @return numero di caratteri presenti nel file
 */
int conteggiaCaratteriFile(FILE* fp);

/**
 * Sistema di backup del database attraverso la copia del database file-based principale carattere per carattere
 */
void backupDatabase(char *file2);

/**
 * Funzione di stampa del Menu Principale
 */
void menu();

/**
 * Funzione di stampa del menu dedicato alle funzioni relative al Database
 */
void menuDatabase();

/**
 * Funzione di stampa del menu dedicato alle funzioni relative al Motore di Ricerca
 */
void menuRicerca();

/**
 * Funzione di stampa del menu dedicato alle funzioni relative alla modifica delle informazioni dei brani
 */
void menuModifica();

/**
 * Funzione di stampa del menu dedicato alle funzioni di DEBUG per agevolare una programmazione pulita
 */
void menuDebug();


#endif /* UTILS_H_ */
