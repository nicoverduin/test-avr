#ifndef UCGLIB_MEGA_H
#define UCGLIB_MEGA_H

/**
 * @file      ucglib_xmega.h.c
 * @project   ucglib
 * @brief     callback function to interface between ucglib and XMega
 * @author	  Nico Verduin
 * @date			3-4-2023
*/


// includes
#include <avr/io.h>
#include <time.h>
#include "spi.h"
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>

#include "ucg.h"              // ucglib interface
#include "spi_pins.h"         // shows the connections of the tft screen to SPI
                              // and SPI port used

/**
 * Callback function from ucglib. This function is called from the ucglib functions
 * when interfacing with the SPI bus. This allows ucglib to perform with different
 * controller platforms.
 * @param ucg 	pointer to an ucg object within the application
 * @param msg 	command that needs to be performed
 * @param arg 	see the switch case for meaning of arg
 * @param data 	see the switch case for meaning of data
 * @return 1 		fixed value is returned
 */
int16_t ucg_com_xmega_cb(ucg_t *ucg, int16_t msg, uint16_t arg, uint8_t *data)
{
  uint8_t *savePtr = data;    // save the data pointer
  uint8_t *ptr = 0;

  switch(msg)
	{
		case UCG_COM_MSG_POWER_UP:
			/* "data" is a pointer to ucg_com_info_t structure with the following information: */
			/*	((ucg_com_info_t *)data)->serial_clk_speed value in nanoseconds */
			/*	((ucg_com_info_t *)data)->parallel_clk_speed value in nanoseconds */
			/* "arg" is not used */

			/* This message is sent once at the uC startup and for power up. */
			/* setup i/o or do any other setup */

			// intialiseer the SPI
			spi_init();

			break;

		case UCG_COM_MSG_POWER_DOWN:
			/* "data" and "arg" are not used*/
			/* This message is sent for a power down request */

			break;
		case UCG_COM_MSG_DELAY:
			/* "data" is not used */
			/* "arg" contains the number of microseconds for the delay */
			/* By receiving this message, the following code should delay by */
			/* "arg" microseconds. One microsecond is 0.000001 second */
			_delay_us((arg));
			break;

		case UCG_COM_MSG_CHANGE_RESET_LINE:
			/* "data" is not used */
			/* "arg" = 1: set the reset output line to 1 */
			/* "arg" = 0: set the reset output line to 0 */
            if (arg) {
              PORTD.OUTSET = 1 << TFT_RST;
            } else {
              PORTD.OUTCLR = 1 << TFT_RST;
            }
            break;

		case UCG_COM_MSG_CHANGE_CD_LINE:
			/* "ucg->com_status"  bit 0 contains the old level for the CD line */
			/* "data" is not used */
			/* "arg" = 1: set the command/data (a0) output line to 1 */
			/* "arg" = 0: set the command/data (a0) output line to 0 */
            if (arg) {
              PORTD.OUTSET = 1 << TFT_DC;
            } else {
              PORTD.OUTCLR = 1 << TFT_DC;
            }
			break;

		case UCG_COM_MSG_CHANGE_CS_LINE:
			/* "ucg->com_status"  bit 1 contains the old level for the CS line */
			/* "data" is not used */
			/* "arg" = 1: set the chipselect output line to 1 */
			/* "arg" = 0: set the chipselect output line to 0 */
            if (arg) {
              PORTD.OUTSET = 1 << TFT_CS;
            } else {
              PORTD.OUTCLR = 1 << TFT_CS;
            }
			break;

		case UCG_COM_MSG_SEND_BYTE:
			/* "data" is not used */
			/* "arg" contains one byte, which should be sent to the display */
			/* The current status of the CD line is available */
			/* in bit 0 of u8g->com_status */

            spi_write(arg);
			break;

		case UCG_COM_MSG_REPEAT_1_BYTE:
			/* "data[0]" contains one byte */
			/* repeat sending the byte in data[0] "arg" times */
			/* The current status of the CD line is available */
			/* in bit 0 of u8g->com_status */

			while (arg--){
              spi_write(*data);
			}

			break;
		case UCG_COM_MSG_REPEAT_2_BYTES:
			/* "data[0]" contains first byte */
			/* "data[1]" contains second byte */
			/* repeat sending the two bytes "arg" times */
			/* The current status of the CD line is available */
			/* in bit 0 of u8g->com_status */
			while (arg--) {
              ptr = savePtr;
			  spi_write(*ptr);
              ptr++;
              spi_write(*ptr);
			}
			break;
		case UCG_COM_MSG_REPEAT_3_BYTES:
			/* "data[0]" contains first byte */
			/* "data[1]" contains second byte */
			/* "data[2]" contains third byte */
			/* repeat sending the three bytes "arg" times */
			/* The current status of the CD line is available */
			/* in bit 0 of u8g->com_status */

			while (arg--) {
              ptr = savePtr;
              spi_write(*ptr);
              ptr++;
              spi_write(*ptr);
              ptr++;
              spi_write(*ptr);
            }
			break;
		case UCG_COM_MSG_SEND_STR:
			/* "data" is an array with "arg" bytes */
			/* send "arg" bytes to the display */
			/* "data" is an array with "arg" bytes */
			/* send "arg" bytes to the display */
			while (arg--) {
				spi_write(*data);
				data++;
			}

			break;
		case UCG_COM_MSG_SEND_CD_DATA_SEQUENCE:
			/* "data" is a pointer to two bytes, which contain the cd line */
			/* status and display data */
			/* "arg" contains the number of these two byte tuples which need to */
			/* be analysed and sent. Bellow is a example sequence */
			/* The content of bit 0 in u8g->com_status is undefined for this message */

			while(arg > 0)
			{
				if ( *data != 0 )
				{
					if ( *data == 1 )
					{
                      PORTD.OUTCLR = 1 << TFT_DC;
					  /* set CD (=D/C=A0) line to low */
					}
					else
					{
					  PORTD.OUTSET = 1 << TFT_DC;
					  /* set CD (=D/C=A0) line to high */
					}
				}
				data++;
				/* send *data to the display */
                spi_write(*data);
				data++;
				arg--;
			}
			break;
	}
	return 1;
}
#endif

