/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#pragma once

# define  REVERSE_TEMP_SENSOR_RANGE

// Sensore di temperatura Marlin tipo 22
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
// #if ANY_THERMISTOR_IS (22) // Pt100 con amplificatore E3D @ pullup 3.3vw / 4.7K (BigTreeTech, ecc.). Abbycus 2020
//    #include "thermistor_22.h"
// #endif
//
// In configuration.h:
//       #define TEMP_SENSOR_0 22 // usa 0 o 1
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
const  short temptable_22 [] [ 2 ] PROGMEM = {
  { OV (   0 ),     0 },
  { OV ( 245 ),     1 },
  { OV ( 253 ),    10 },
  { OV ( 261 ),    20 },
  { OV ( 270 ),    30 },
  { OV ( 278 ),    40 },
  { OV ( 287 ),    50 },
  { OV ( 295 ),    60 },
  { OV ( 303 ),    70 },
  { OV ( 311 ),    80 },
  { OV ( 319 ),    90 },
  { OV ( 328 ),   100 },
  { OV ( 336 ),   110 },
  { OV ( 344 ),   120 },
  { OV ( 352 ),   130 },
  { OV ( 360 ),   140 },
  { OV ( 368 ),   150 },
  { OV ( 376 ),   160 },
  { OV ( 384 ),   170 },
  { OV ( 391 ),   180 },
  { OV ( 399 ),   190 },
  { OV ( 407 ),   200 },
  { OV ( 415 ),   210 },
  { OV ( 422 ),   220 },
  { OV ( 430 ),   230 },
  { OV ( 438 ),   240 },
  { OV ( 445 ),   250 },
  { OV ( 453 ),   260 },
  { OV ( 460 ),   270 },
  { OV ( 468 ),   280 },
  { OV ( 475 ),   290 },
  { OV ( 483 ),   300 },
  { OV ( 490 ),   310 },
  { OV ( 497 ),   320 },
  { OV ( 505 ),   330 },
  { OV ( 512 ),   340 },
  { OV ( 519 ),   350 },
  { OV ( 526 ),   360 },
  { OV ( 533 ),   370 },
  { OV ( 541 ),   380 },
  { OV ( 548 ),   390 },
  { OV ( 554 ),   400 },
  { OV ( 623 ),   500 },
  { OV ( 689 ),   600 },
  { OV ( 751 ),   700 },
  { OV ( 810 ),   800 },
  { OV ( 850 ),   900 },
  { OV ( 910 ), 1000 },
  { OV ( 960 ), 1100 }
};
