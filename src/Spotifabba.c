/*
 * Spotifabba 0.0.1 rev.2 - 09.04.2020
 * Copyright (c) 2020, Simone Cervino.
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <gestorefile.h>
void inizializzazione();

int main() {
	inizializzazione();

	printf("hey!");
	return 0;
}

void inizializzazione() {
	// Visualizza informazioni su Spotifabba
	printf("Spotifabba 0.0.1 rev.2 - nightly build 3\n");
	printf("\nBenvenuto su Spotifabba.");
	// Controllo configurazione


	/*
	//TODO: Creazione di utenti
	// Effettua login per poter accedere alla propria libreria
	login();*/
}

void inserimento_Database() {

}

void database() {
	FILE* fp;
	char* file = "database.txt";
	fp=fopen(file, "r");
	if(fp=="NULL")
		printf("Database non trovato, creazione in corso.");

}

//TODO: Creazione di utenti
/*
void login() {
	int scelta=0;
	printf("Vuoi creare un utente[0] oppure effettuare il login[1]? [0/1]: ");
	scanf("%d", scelta);
	if(scelta==0)
		creazioneUtente();
	else if(scelta==1)

		printf("\nInserisci nome utente: ");
}

void creazioneUtente() {
	printf("Inserisci ");
}
*/
