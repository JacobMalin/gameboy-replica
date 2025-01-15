/* 
 * File:   display.h
 * Author: Jacob Malin
 *
 * Created on November 10, 2024, 12:54 AM
 */

#ifndef DISPLAY_H
#define	DISPLAY_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <avr/io.h>

#include "FreeRTOS.h"
#include "task.h"

#include "cell.h"
#include "lcd.h"
    
#define DISPLAY_ROWS 18
#define DISPLAY_COLS 20
#define DISPLAY_START_ROW 2
#define DISPLAY_START_COL 57
    
    typedef cell_e display_row[DISPLAY_COLS];

    typedef struct {
        sd_t *SD;
        lcd_t *LCD;
    } display_t;

    /**
     * Initializes the display for the GameBoy.
     * @param sd_t *this A pointer to the sd object.
     * @param spi_t *SPI An SPI object.
     * @param PORT_t *cs_port The CS port for SPI.
     * @param uint8_t cs_pin The CS pin for SPI.
     * @param PORT_t *dcx_port The DCX port for data/command selection.
     * @param uint8_t dcx_pin The DCX pin for data/command selection.
     * @return Returns a display_t pointer.
     */
    display_t *Display(sd_t *SD, spi_t *SPI, PORT_t *cs_port, uint8_t cs_pin, 
        PORT_t *dcx_port, uint8_t dcx_pin);

    /**
     * Writes to the display.
     * @param display_t *this A pointer to the display object.
     * @param display_row row A row of cells to display.
     * @param uint8_t row_num The index of the row in the grid.
     */
    void Display_display_row(display_t * this, display_row row, 
            uint8_t row_num);

    /**
     * Writes a cell to the display.
     * @param display_t *this A pointer to the display object.
     * @param uint8_t row_num The row index of the cell.
     * @param uint8_t col_num The column index of the cell.
     * @param cell_e cell The index of the cell in the CELL_LIST.
     */
    void Display_write_cell(display_t * this, uint8_t row_num, uint8_t col_num, 
        cell_e cell);

    /**
     * Writes a cell to the display, shifted up by a number of rows on the LCD.
     * Used to display the starting logo.
     * @param display_t *this A pointer to the display object.
     * @param int8_t row_num The row index of the cell.
     * @param uint8_t row_shift The number of LCD rows up from the normal cell 
     * row.
     * @param uint8_t col_num The column index of the cell.
     * @param cell_e cell The index of the cell in the CELL_LIST.
     */
    void Display_write_cell_shift(display_t * this, int8_t row_num, 
        uint8_t row_shift, uint8_t col_num, cell_e cell);

#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAY_H */

