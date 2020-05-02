/ * *
 * Firmware della stampante 3D Marlin
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Basato su Sprinter e grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * Questo programma è un software gratuito: puoi ridistribuirlo e / o modificarlo
 * secondo i termini della GNU General Public License come pubblicato da
 * la Free Software Foundation, versione 3 della Licenza o
 * (a tua scelta) qualsiasi versione successiva.
 *
 * Questo programma è distribuito nella speranza che possa essere utile,
* ma SENZA ALCUNA GARANZIA; senza nemmeno la garanzia implicita di
* COMMERCIABILITÀ o IDONEITÀ PER UNO SCOPO PARTICOLARE. Vedi il
 * Licenza GNU General Public per maggiori dettagli.
 *
 * Dovresti aver ricevuto una copia della GNU General Public License
* insieme a questo programma. In caso contrario, consultare <http://www.gnu.org/licenses/>.
 *
 * /
# pragma una volta

# define  REVERSE_TEMP_SENSOR_RANGE

// Sensore di temperatura Marlin tipo 24
//
// Questo è stato creato per consentire l'uso dell'amplificatore E3D PT100 su BigTreeTech e schede simili
// senza richiedere mod hardware (resistori di taglio, ecc.).
// Le schede BigTreeTech hanno un riferimento ADC a 3,3 V e una resistenza pullup da 4,7 K.
// collegato agli ingressi del termistore, quindi non possiamo utilizzare i tipi di sensore di temperatura standard Marlin.
//
// INSTALLAZIONE HARDWARE:
//
// Poiché la scheda BigTreeTech non è tollerante a 5 V, è necessario utilizzare
// E3D PT100 a 3.3V. Sì, questa scheda funzionerà a 3,3 V ma non segnalerà
// temperature oltre i 360 ° C circa.
// 3,3 V possono essere trovati su alcuni connettori BTT (connettore WIFI su SKR 1.4)
// Collegare l'uscita dell'amplificatore PT100 all'ingresso termistore standard sulla scheda BTT.
//
// INSTALLAZIONE SOFTWARE:
//
// Questa tabella deve essere compilata nel firmware Marlin 2.0.x. Individua e apri il
// termistors.h e aggiungi il seguente testo:
//
// #if ANY_THERMISTOR_IS (24) // Pt100 con amplificatore E3D @ pullup 3.3vw / 4.7K (BigTreeTech GTR v1.0) Novità
//    #include "thermistor_24.h"
// #endif
//
// In configuration.h:
//       #define TEMP_SENSOR_0 24 // usa 0 o 1
//       #define HEATER_0_MAXTEMP 310 // imposta la temperatura massima su meno di 360
//
// CALCOLI:
//
// I valori di matrice seguenti sono stati derivati ​​dalle tabelle di resistenza PT100 e temperatura.
//
// Costanti:
//     Vref = 3.30V
//     Rb = 4400 (resistenza di due resistori a ponte nel circuito INA826)
//     Rpu = 4700 (resistenza pullup sull'ingresso termistore)
//     Rampa = 100 (resistenza di uscita amp INA826)
//     RTD = Resistenza @ temperatura. Esempio 111 ohm a 25 ° C.
//      
// Calcola Vo: uscita dell'amplificatore INA826 nel PCB E3D
//     Vo = ((Vref / (RTD + Rb)) * RTD) * 10
// Successivamente calcola Vadc: tensione di uscita con un pullup di 4,7 K sull'ingresso del termistore.
//     Vadc = (((Vref - Vo) / Rpu) * Rampa) + Vo
// Calcola infine il valore digitale ADC per ciascun punto dell'array sottostante (ADC a 10 bit, 0-1023).
//     ADC = (Vadc / Vref) * 1024
//
// Abby @ Abbycus 2020
//
const  short temptable_24 [] [ 2 ] PROGMEM = {
  { OV (   0 ),     0 },
  { OV ( 245 ),     1 },
  { OV ( 261 ),    10 },
  { OV ( 269 ),    20 },
  { OV ( 277 ),    30 },
  { OV ( 286 ),    40 },
  { OV ( 294 ),    50 },
  { OV ( 302 ),    60 },
  { OV ( 311 ),    70 },
  { OV ( 319 ),    80 },
  { OV ( 327 ),    90 },
  { OV ( 335 ),   100 },
  { OV ( 343 ),   110 },
  { OV ( 351 ),   120 },
  { OV ( 359 ),   130 },
  { OV ( 367 ),   140 },
  { OV ( 375 ),   150 },
  { OV ( 383 ),   160 },
  { OV ( 391 ),   170 },
  { OV ( 398 ),   180 },
  { OV ( 406 ),   190 },
  { OV ( 414 ),   200 },
  { OV ( 422 ),   210 },
  { OV ( 429 ),   220 },
  { OV ( 437 ),   230 },
  { OV ( 444 ),   240 },
  { OV ( 452 ),   250 },
  { OV ( 459 ),   260 },
  { OV ( 467 ),   270 },
  { OV ( 474 ),   280 },
  { OV ( 482 ),   290 },
  { OV ( 489 ),   300 },
  { OV ( 497 ),   310 },
  { OV ( 504 ),   320 },
  { OV ( 511 ),   330 },
  { OV ( 518 ),   340 },
  { OV ( 525 ),   350 },
  { OV ( 533 ),   360 },
  { OV ( 540 ),   370 },
  { OV ( 547 ),   380 },
  { OV ( 554 ),   390 },
  { OV ( 561 ),   400 },
  { OV ( 629 ),   500 },
  { OV ( 694 ),   600 },
  { OV ( 755 ),   700 },
  { OV ( 815 ),   800 },
  { OV ( 854 ),   900 },
  { OV ( 914 ), 1000 },
  { OV ( 964 ), 1100 }
};
