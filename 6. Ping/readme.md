### Introduzione
- Il ping misura il tempo di andata e ritorno di un pacchetto
- Per fare questo inviamo un pacchetto con l'orario di invio e ci segniamo l'orario di arrivo nel processo receiver, facciamo la differenze tra i due valori (espressi entrambi in millisecondi).

---------------------------------------------------------------------------

### Due alternative

A. Chiamiamo fork() a monte
Necessità di avere due socket diversi per processo sendere e receiver del client --> obbligati ad indicare un parametro in input in più e chiamare il bind(). Il server necessita di un parametro in più che è la porta del client sulla quale ha avviato il socket di ascolto.

B. Chiamiamo fork() dopo avere inizializzato un socket
socket condiviso tra i due processi (fork crea un duplicato del valore delle variabili), così facendo viene usata una sola porta per invio e risposta dei pacchetti. Il server conosce la porta e scambia mittente e destinatario.


