    #ifndef __SPI_H
    #define __SPI_H

    #include <inttypes.h>

    #define SPI_SS_bm   0x10
    #define SPI_MOSI_bm 0x20
    #define SPI_MISO_bm 0x40
    #define SPI_SCK_bm  0x80

    #define FOO         0x00

    // prototypes
    void    spi_init(void);                   // init spi
    uint8_t spi_transfer(uint8_t data);       // transfer data to slave
    void    spi_write(uint8_t data);          // write (register?)
    uint8_t spi_read(void);                   // read spi slave

    #endif
