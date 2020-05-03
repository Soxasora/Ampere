/*
 * Ampere 0.0.1 rev. 1000 - 02.05.2020
 * Gruppo n.16 - Michele Barile, Nicolo' Cucinotta, Simone Cervino
 * Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp
 * da realizzare nell'ambito del corso di studi di Laboratorio di informatica, a.a. 2019/20.
 * Maggiori informazioni sul copyright su https://github.com/Soxasora/XX/blob/master/LICENSE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Ampere.h"
#include "gestori/GestoreFile.h"
#include "database/Database.h"
#include "sys/Utils.h"
#include "sys/Impostazioni.h"

int main() {

	inizializzazione();

	menu();

	terminazione();
	system("PAUSE");
	return 0;
}

void inizializzazione() {
	// Mostra info su Ampere
	info();
	// Rilevo il sistema operativo in uso al momento dell'esecuzione del programma
	os = rivelaOS();
	// Ottengo il database e tutti i sotto database con esso
	db = ottieniDatabase();
}

void terminazione() {
	salvaModificheSuFile();
}
