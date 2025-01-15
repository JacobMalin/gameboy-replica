/* 
 * File:   lcd.h
 * Author: Jacob Malin
 *
 * Created on November 10, 2024, 12:54 AM
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifndef F_CPU
#define F_CPU 20000000
#endif

#include <avr/io.h>
#include <util/delay.h>

#include "FreeRTOS.h"
#include "task.h"

#include "cell.h"
#include "spi_client.h"

#define LCD_SLEEP_WAIT_MS 120
#define LCD_ROWS 240
#define LCD_COLS 320

// Battery indication "LED"
#define LED_X 0
#define LED_Y 73
#define LED_WIDTH 18

#define LCD_CMD_SLPOUT   0x11 // Sleep out
#define LCD_CMD_DISPON   0x29 // Display on
#define LCD_CMD_CASET    0x2a // Column address set
#define LCD_CMD_PASET    0x2b // Page address set
#define LCD_CMD_RAMWR    0x2c // Memory write
#define LCD_CMD_MADCTL   0x36 // Memory access control
#define LCD_CMD_PIXSET   0x3a // Pixel format set

#define LCD_PIXSET_DBI_16 0b00000101 // 16-bit color format
#define LCD_MADCTL_MV 0b00100000 // Exchange col and row

    typedef struct {
        spi_client_t *SPI_Client;
        output_t *DCX;
    } lcd_t;

    /**
     * Initializes the lcd.
     * @param spi_t *SPI An SPI object.
     * @param PORT_t *cs_port The CS port for SPI.
     * @param uint8_t cs_pin The CS pin for SPI.
     * @param PORT_t *dcx_port The DCX port for data/command selection.
     * @param uint8_t dcx_pin The DCX pin for data/command selection.
     * @return Returns an lcd_t pointer.
     */
    lcd_t *LCD(spi_t *SPI, PORT_t *cs_port, uint8_t cs_pin,
            PORT_t *dcx_port, uint8_t dcx_pin);

    /**
     * Write a command to the LCD.
     * @param lcd_t *this A pointer to the lcd object.
     * @param uint8_t cmd The command.
     */
    void _LCD_write_cmd(lcd_t * this, uint8_t cmd);

    /**
     * Write one byte of data to the LCD.
     * @param lcd_t *this A pointer to the lcd object.
     * @param uint8_t data The data.
     */
    void _LCD_write_data(lcd_t * this, uint8_t data);

    /**
     * Write multiple bytes of data to the LCD.
     * @param lcd_t *this A pointer to the lcd object.
     * @param uint8_t data[] The data list.
     * @param uint8_t len The length of the data list.
     */
    void _LCD_write_datas(lcd_t * this, uint8_t data[], uint8_t len);

    /**
     * Setup the LCD. Sends various commands.
     * @param lcd_t *this A pointer to the lcd object.
     */
    void _LCD_setup(lcd_t * this);

    /**
     * Writes one color to the LCD.
     * @param color_e color The color to write.
     */
    void _LCD_write_color(color_e color);

    /**
     * Writes red to the LCD.
     */
    void _LCD_write_red(void);

    /**
     * Makes the writing area smaller.
     * @param lcd_t *this A pointer to the lcd object.
     * @param uint16_t start_row The starting row to restrict to.
     * @param uint16_t num_rows The number of rows to restrict to.
     * @param uint16_t start_col The starting column to restrict to.
     * @param uint16_t num_cols The number of columns to restrict to.
     */
    void _LCD_restrict_region(lcd_t * this,
            uint16_t start_row, uint16_t num_rows,
            uint16_t start_col, uint16_t num_cols);

    /**
     * Writes to one region of the lcd.
     * @param lcd_t *this A pointer to the lcd object.
     * @param uint16_t start_row The starting row to write to.
     * @param uint16_t num_rows The number of rows to write to.
     * @param uint16_t start_col The starting column to write to.
     * @param uint16_t num_cols The number of columns to write to.
     * @param color_e *colors An array of colors of size num_rows X num_cols.
     */
    void LCD_write_region(lcd_t * this, uint16_t start_row, uint16_t num_rows,
            uint16_t start_col, uint16_t num_cols, 
            const color_e *colors);

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

