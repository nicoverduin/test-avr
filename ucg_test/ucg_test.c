/**
 * @file      ucg_voorbeeld.c
 * @project   start_voorbeeld
 * @brief     Testen om ucglib te gebruiken met de XMega
 * @author		Nico Verduin
 * @date			14-3-2023
*/
#define F_CPU 32000000

// includes
#include <stdlib.h>

// Door de call-back te includen krijg je automatisch de rest erbij
#include "ucglib_xmega.h"    // interface between xmega and ucglib

/**
 * Tekent een rechthoek met een enkel punts lijn
 * @param x x coordinaat
 * @param y y coordinaat
 * @param w breedte
 * @param h hoogte
 */
void DrawRect(ucg_t *ucg, uint16_t x, uint16_t y, uint16_t w, uint16_t h){
  ucg_DrawLine(ucg, x, y, x+w, y);
  ucg_DrawLine(ucg, x, y+h, x+w, y+h);
  ucg_DrawLine(ucg, x, y, x, y+h);
  ucg_DrawLine(ucg, x+w, y, x+w, y+h);
}

/**
 * Hoofd programma
 * @return 0
 */
int main() {

  // creer een ucg object
  ucg_t ucg;                  // dit is hetgene dat praat met het TFT scherm

  char teksten[4][15] = {
          {"Dit is een"},
          {"eenvoudig"},
          {"programma met"},
          {"de XMega"}
  };

  // creer een functie pointer naar de callback
  ucg_com_fnptr ucg_xmega_func = &ucg_com_xmega_cb;

  // initialiseer de UCG
  ucg_Init(&ucg, ucg_dev_st7735_18x128x160, ucg_ext_st7735_18, ucg_xmega_func);

  // en laat eens wat zien
  ucg_SetFontMode(&ucg, UCG_FONT_MODE_TRANSPARENT);
  ucg_ClearScreen(&ucg);
  ucg_SetFont(&ucg, ucg_font_8x13_mr);
  ucg_SetColor(&ucg, 0, 0, 255, 0);
  ucg_SetRotate90(&ucg);

  for (uint8_t i = 0; i < 4; i++) {
    ucg_DrawString (&ucg, 0,((i + 1) * 15), 0, teksten[i]);
  }

  // de afmetingen van het scherm
  ucg_wh_t dimensions;
  dimensions.w = ucg_GetWidth(&ucg);
  dimensions.h = ucg_GetHeight(&ucg);

  while(1) {

    for (int16_t color = 0; color < 255; color+=50) {

      // teken een rechthoek en ga vanuit de buitenkant naar het midden
      // werken met een kleine ruimte ertussen

      // start coordinaten
      int16_t x = 0;                  // start punt
      int16_t y = 0;
      int16_t w = dimensions.w - 1;   // afmetingen van het scherm
      int16_t h = dimensions.h - 1;

      ucg_ClearScreen(&ucg);

      // stel de kleur in
      if (color == 0 ) {
        ucg_SetColor(&ucg, 0, 255, 255, 255);
      } else {
        ucg_SetColor(&ucg, 0, 0, 0, color);
      }

      // nu elke tweede pixel een kleinere rechthoek maken
      while (w > 2) {
        // teken de rechthoek
        DrawRect(&ucg, x, y, w, h);
        // verklein de maat en verplaats de rechthoek
        y += 2;     // x en y schuiven 2 posities op
        x += 2;
        w -= 4;     // breedte en hoogte met 4 verkleinen
        h -= 4;
      }
    }
  }
  return 0;
}
