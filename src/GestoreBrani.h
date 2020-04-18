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

#ifndef GESTOREBRANI_H_
#define GESTOREBRANI_H_

/**
 * Mostra all'utente una procedura guidata per inserire brani nel database file-based
 */
void inserimentoGuidato();

/**
 * Funzione di supporto a inserimentoGuidato(), effettua le operazioni di inserimento del brano nel database file-based
 */
void inserisciBranoGuidato(int modalita, char titolo[], char artista[], char album[], char durata[], char anno[], char ascolti[], char gradimento[]);

/**
 * Funzione DEV per inserire un brano direttamente e senza procedura guidata
 */
void inserimentoDiretto();

/**
 * Funzione di supporto a inserimentoDiretto(), effettua l'operazione di inserimento del brano nel database file-based
 */
void inserisciBranoDiretto(char stringa[]);

/**
 * Sistema guidato per la modifica di informazioni di un brano
 */
void modifica(int scelta);

/**
 * Funzione di supporto a modifica(), effettua le operazioni di modifica di brani direttamente nello struct globale
 */
void modificaSingoloBrano(int pos, int modalita);

#endif /* GESTOREBRANI_H_ */
