# NDTM
Simulatore di macchine di Turing non deterministiche.

L'alfabeto di ingresso si compone di tutti i caratteri alfanumerici, più il carattere _ che rappresenta il BLANK. Per ogni altro carattere, il comportamento non è definito.
La macchina riceve tramite stdin le caratteristiche della macchina e le stringhe di ingresso nel seguente formato. 
Una prima area, preceduta dalla riga "Tr", descrive le transizioni ammesse, una per riga, che avranno il formato:
statoDiPartenza carattereLetto carattereScritto movimentoTestina statoDiArrivo

Gli stati sono entrambi numeri interi positivi. I caratteri sono stati precedentemente descritti. Il movimento della testina è descritto con i caratteri L (left), R (right) o S (stand).

A questa sezione segue la riga "Acc" e l'elenco di stati di accettazione, uno per riga.
Segue la riga "Max", e il numero di mosse massimo che la macchina deve simulare. Esso può essere al massimo un long.

Segue la riga "Run" e l'elenco delle stringhe da analizzare, una per riga. Per ognuna di esse sarà stampato, uno per riga, un carattere che ne indica l'esito. Sarà 1 se la stringa viene accettata, 0 se viene rifiutata, U se non viene rifiutata entro le mosse massime.



Note: ho a disposizione una versione leggermente più veloce, tuttavia mancano molti commenti. Preferisco rilasciare questa, sia perchè più leggibile, sia perchè la differenza non è eccessiva. Inoltre, la versione da me definitivamente consegnata ai fini del progetto è questa.
