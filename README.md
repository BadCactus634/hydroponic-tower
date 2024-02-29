ENGLISH USERS [READ HERE](english.md)!

# Serra idroponica
Crea una serra idroponica stampata in 3D con Arduino/ESP32!  

<img src="https://github.com/BadCactus634/hydroponic-tower/assets/68558172/b1987811-1263-4c2e-ad06-7a666f1c531b" width="600">

## Overview
Questa serra idroponica modulare è stata interamente stampata in 3D utilizzando del [PLA della PolyTerra](https://amzn.eu/d/4JCfyR1). Per stampare i pezzi marroni ho utilizzato poco meno di 1kg di filamento, mentre per quelli verdi circa 400g.  
C'è da dire però che **non ho avuto stampe fallite** e che **tutti i modelli sono stati ridotti del 10%** perché non ci stavano sul piatto della mia stampante (Flsun Q5).  
Se non l'hai ancora fatto, clicca qui (WIP!) per vedere il video che ho fatto dove mostro la serra in generale e spiego come l'ho costruita.

Questi sono alcuni dei componenti stampati:  

<img src="https://github.com/BadCactus634/hydroponic-tower/assets/68558172/6685b945-aa3b-4e42-a553-f0862979546f" width="600"> <br>

Lista della spesa:
- 1kg filamento marrone
- 1kg filamento verde
- stampante 3D (ovviamente)
- pompa 12V
- ESP32/Arduino (qualsiasi)
- sensore di livello dell'acqua
- un vaso (se non è presente nei modelli già fatti, devi crearti un modello del coperchio su misura)
- nutrimento per coltivazioni idroponiche
- piantine da mettere nella serra
- step-up 5V-12V
- potenziometro, cavi, LED
 
Opzionale:
- millefori, stagno, stagnatore
- sensori per pH, CE e temperatura dell'acqua (io non li ho usati)

## Modelli 3D
I modelli che ho utilizzato io e che vedi nel mio video li trovi tutti nella cartella **File STL utilizzati**, inclusa la scatoletta che contiene i componenti.  
Non c'è il file del coperchio del vaso perché l'ho costruito in legno, visto che il mio vaso aveva delle misure particolari.

Nel caso ti servissero puoi scaricare lo zip contenente i modelli originali cliccando [qui](https://t.me/makersITA/907372) (non ci sono più su Thingiverse).

## Circuito
Il cuore di questo progetto è un semplicissimo **ESP32** che fa da timer che accende la pompa dell'acqua per 5 minuti e poi attende un tempo variabile (regolabile dal potenziometro) che può andare da 10 a 60 minuti.  
Ci sono due LED che indicano lo stato del sistema (verde acceso = pompa attiva; rosso lampeggiante = mancanza di acqua nel serbatoio).  
L'ESP32 attiva un relè tramite un transistor, e il relè a sua volta attiva uno step-up che converte i 5V dell'alimentazione a 12V per la pompa dell'acqua, accendendola.  
Lo step-up è stato collegato a valle del relè in modo da essere attivato solo quando la pompa deve essere alimentata, risparmiando qualche mA del circuito di conversione e allungando quindi la durata della batteria (anche se io lo alimento tramite un alimentatore a muro).  

<img src="https://github.com/BadCactus634/hydroponic-tower/assets/68558172/ad248261-0450-4d58-aa0b-4c03accaca73" width="300">

Questo è lo schema del circuito:  

![Circuito_schem](https://github.com/BadCactus634/hydroponic-tower/assets/68558172/36fbfe34-5de7-4bf4-98cb-40de06bd7c8f)

## Codice
Il codice è nel file **Codice_SerraIdroponica.ino** e questo è il suo funzionamento di base:  
- C'è acqua nel serbatoio?  
  Allora se è passato il tempo di attesa (regolabile tramite potenziometro da 10min a 60min) attiva la pompa per 5min.
  Durante il tempo di attivazione della pompa (che funziona tramite millis) verifica ogni secondo se è ancora presente acqua nel serbatoio, altrimenti fermala.
  
**ATTENZIONE**  
I pin nel codice e lo schema del circuito si riferiscono a ESP32. Se volete utilizzare un Arduino dovete modificare i pin nel codice e nel circuito.
