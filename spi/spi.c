    #include <inttypes.h>
    #include <avr/io.h>
    #include <spi_pins.h>
    #include <spi.h>

    //initialize the SPI bus
    //  uint8_t lsbfirst - if 0: most significant bit is transmitted first
    //  uint8_t master - if 1: use master mode, if 0: slave mode is used
    //  uint8_t mode - sets the transfer mode:
    //                 mode   leading clock edge   trailing clock edge
    //                 -----------------------------------------------
    //                 0      sample (rising)      setup  (falling)
    //                 1      setup  (rising)      sample (falling)
    //                 2      sample (falling)     setup  (rising)
    //                 3      setup  (falling)     sample (rising)
    //  uint8_t clkrate - spi bus clock rate, valid speeds are 0-3
    //                    rate   speed
    //                    ------------
    //                    0      CPUCLK/4
    //                    1      CPUCLK/16
    //                    2      CPUCLK/64
    //                    3      CPUCLK/128
    //  uint8_t dblclk - if 1: doubles the SPI clock rate in master mode
    //  EXAMPLE: spi_init(0, 1, 0, 3, 0)
    void spi_init(void ) {

      // All connections assumed on PORT D
      PORTD.DIRSET  = SPI_SCK_bm|SPI_MOSI_bm|SPI_SS_bm| (1 << TFT_DC) | (1 << TFT_LED) | (1 << TFT_RST);
      PORTD.DIRCLR  = SPI_MISO_bm;

      // turn the backlight LED on and /SS HIGH
      PORTD.OUTSET = (1 << TFT_LED) | SPI_SS_bm;

      SPID.CTRL = SPI_ENABLE_bm   |       // enable SPI
                  SPI_MASTER_bm   |       // Act as MAster
                  SPI_CLK2X_bm    |       // double clock speed
                  //SPI_DORD_bm   |       // MSB first
                  SPI_MODE_0_gc   |       // SPI mode 0
                  SPI_PRESCALER_DIV4_gc;  // prescaling 4
    }

    /**
     * Transfer data over SPI
     * @param data
     * @return
     */
    uint8_t spi_transfer(uint8_t data) {
      SPID.DATA = data;                       // fill SPI data register
      while (!(SPID.STATUS & (SPI_IF_bm)));   // wait until transferred
      return SPID.DATA;                       // return sent data
    }

    /**
     * write data but do chip select first and deselect when sent
     * @param data
     */
    void spi_write(uint8_t data) {
      PORTD.OUTCLR = 1 << TFT_CS;
      spi_transfer(data);
      PORTD.OUTSET = 1 << TFT_CS;
    }

    uint8_t spi_read(void){
      uint8_t data;

      PORTD.OUTCLR = 1 << TFT_CS;
      data = spi_transfer(FOO);
      PORTD.OUTSET = 1 << TFT_CS;

      return data;
    }
