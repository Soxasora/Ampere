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

#include "FabbAmp.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Database.h"
#include "GestoreBrani.h"
#include "MotoreRicerca.h"
#include "Utils.h"

int main() {
	// Inizializza il programma
	inizializzazione();
	// Mostra il menu
	printf("\nPremere invio per andare al menu.");
	menu();
	// Esegui le ultime funzioni di aggiornamento prima di chiudere
	//terminazione();

	printf("\nFabbAmp terminato.\n");
	aspetta();
	return 0;
}

void inizializzazione() {
	// Visualizza informazioni su FabbAmp
	info();
	printf("\nBenvenuto su FabbAmp.");
	// Crea database se esso non e' presente nella cartella.
	creaDatabaseSeNonEsiste();
	// Trasferimento in memoria del database file-based
	brani = ottieniDatabase();
}

/*void terminazione() {
	aggiornaDatabase();
}*/

