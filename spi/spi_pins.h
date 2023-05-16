/**
 * @brief definitions of the SPI pin connections between the
 * tft screen and the XMega as well as which SPI port is used
 */
#ifndef SPI_PINS_H
#define SPI_PINS_H

#define TFT_CS    4      // chip select
#define TFT_RST   3      // reset
#define TFT_SCK   7      // Serial Clock
#define TFT_MISO  6      // not used
#define TFT_MOSI  5      // Master out Slave in
#define TFT_DC    2      // data / command
#define TFT_LED   1      // Backlight LED

#endif // SPI_PINS_H
