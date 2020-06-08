# Ampere
Gruppo 16
## Progetto UNIBA/Laboratorio di Informatica di gruppo
Progetto universitario di gruppo intento alla creazione di un gestore dati per la musica, es: WinAmp/Spotify, da realizzare nell'ambito del corso di studi di Laboratorio di Informatica, a.a. 2019/20.

## Come funziona
Obiettivo del progetto è la gestione di una base dati musicale, al fine di fornire agli appassionati uno strumento per la ricerca di informazioni di qualunque genere riguardanti i brani e gli artisti di loro gradimento.

## Specifiche e funzionalità
### Compatibilità:
Ampere è stato scritto tenendo a mente la portabilità del codice. Testato con successo sulle 3 principali piattaforme, è compatibile con:

* Windows (testato su Windows 10 1909+)
* macOS	(testato su macOS 10.15.4)
* GNU/Linux (testato sulla distribuzione Ubuntu 20.04)

### UX/UI:
Linea di comando

### Funzionalità chiave del sistema:
Ampere si suddivide in 2 classi:
Gestione dei dati:
* Database con supporto fino a 1000 inserimenti per categoria (brani, artisti, album, generi, playlist, utenti...)
* Salvataggio dei File inerenti al database su scelta dell'utente: ad ogni modifica oppure alla chiusura di Ampere
* Inserimento di brani con risoluzione dipendenze al volo (Artisti, Album e Generi)
* Supporto a più di un inserimento per categoria (Artisti, Album e Generi)
* Modifica e Cancellazione dei dati presenti nel Database
* Playlist con descrizione, condivisione di esse in base alla loro privacy
* Supporto agli utenti per garantire la personalizzazione di Ampere
* Riconoscimento di lyrics per i brani in base al loro id
* Visualizzazione della biografia di un artista sul browser predefinito di sistema
* Backup e Ripristino del Database

Ricerca di informazioni:
* Ricerca generale interrogando il database, mostrando tutti i risultati in una sola schermata
* Ricerca di tutte le informazioni in base ad un criterio ad esempio: tutti i brani, artisti, album, generi...
* Ricerca di una precisa informazione in base ad un criterio ad esempio: Daft Punk o Random Access Memories
* Ricerca di brani in base al titolo, l'anno di uscita, l'artista, l'album...
* Ricerca di Playlist pubbliche (nonché personali)
* Ricerca del testo di un brano
* Ricerca della biografia di un artista

### Sotto al cofano
Ampere si avvale di funzioni fondamentali per svolgere il suo lavoro, come:
* Pausa del programma multi-piattaforma
* Creazione di cartelle multi-piattaforma
* Input sicuro di una stringa evitando qualsivoglia errore da parte dell'utente
* Input sicuro di un numero evitando input non numerici e input successivi saltati
* Input sicuro di un carattere evitando input non voluti come spazi ecc...
* Comparazione stringhe senza distinzioni di caratteri, indipendentemente dal sistema operativo
* Comparazione stringhe parziali senza distinzioni di caratteri, indipendentemente dal sistema operativo
* Pulizia del buffer di sistema
* Gestore messaggi e richieste

### Team (in ordine di nome):
* Marco Furone
* Michele Barile
* Nicolo' Cucinotta
* Simone Cervino

