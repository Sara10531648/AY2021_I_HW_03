HW\_03
======

TOP DESIGN
----------

Uso due PWM per il controllo dei canali di rosso,verde e blu, collegati
rispettivamente ai pin 2.7,2.6,2.5 . La configurazione del LED RGB è di
anodo comune.

La UART è in modalità "full", quindi può ricevere e trasmettere, e ho
come sorgente di interrupt l'opzione " on byte recived" così che ogni
volta che arriva un byte alla UART vengano eseguiti i comandi di
interesse in essa contenuti.

Il timer ha un clock ad una frequenza di 51.2 Hz in modo da avere come
periodo 5s. Ho abilitato la interrupt "on Terminal Count" così arrivata
a 5s, dopo l'arrivo di un byte, svolgo i comandi nella relativa isr.

CODICE
------

I file sono:

- UARTisr.h e UARTisr.c
- timerisr.h e timerisr.c
- main.c



All'accensione del PSOC il LED è spento.

Premuto il carattere "v" si può iniziare a inviare nuove sequenze di
colori che verranno implementate e come risultato il LED assumerà i
colori scelti.

Tra un byte e l'altro non devono passare più di 5s : disattivo timer
quando arriva un byte, analizzo se sono passati i 5 s e se sono nella
condizione corretta faccio ripartire il timer ( resettato), analizzo il
byte ricevuto e esco dalla Interrupt della UART. Se tra un byte e il
seguente passano più di 5s bisogna partire nuovamente, inserendo i 5
byte partendo dalla Header. Questa condizione è vera anche se inserisco
header e/o tail non corretti (quindi 0xA0 e 0XC0).

Per analizzare il pacchetto di 5 byte che arriva ci sono 5 variabili in
cui vengono salvati. Il primo e l'ultimo vengono analizzati per capire
se corretti mentre i tre centrali vengono salvati nella struttura Color
e vengono utilizzati per fissare i valori di "PWM" compare.

Se invio i 5 byte (CORRETTI) insieme il LED si accende, se mando i byte separatamente (Da CoolTerm) il LED si accende solo se vengono inviati ad una distanza temporale inferiore ai 5s.

Durante la progettazione del codice inviavo dei messaggi ad ogni check del contenuto dei byte e se non veniva rispettato il requisito di tempo, in fase finale le ho tolte per snellire le tempistiche.

