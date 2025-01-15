/* 
 * File:   display.c
 * Author: Jacob Malin
 *
 * Created on November 10, 2024, 12:54 AM
 */

#include "display.h"

display_t *Display(sd_t *SD, spi_t *SPI, PORT_t *cs_port, uint8_t cs_pin,
            PORT_t *dcx_port, uint8_t dcx_pin) {
    static display_t Display;

    Display.SD = SD;
    Display.LCD = LCD(SPI, cs_port, cs_pin, dcx_port, dcx_pin);

    return &Display;
}

void Display_display_row(display_t * this, display_row row, uint8_t row_num) {
    for (uint8_t col_num = 0; col_num < DISPLAY_COLS; col_num++) {
        Display_write_cell(this, row_num, col_num, row[col_num]);
    }
}

void Display_write_cell(display_t * this, uint8_t row_num, uint8_t col_num, 
        cell_e cell) {
    uint16_t start_row = row_num * CELL_WIDTH + DISPLAY_START_ROW;
    uint16_t start_col = col_num * CELL_WIDTH + DISPLAY_START_COL;
    LCD_write_region(this->LCD, start_row, CELL_WIDTH, 
            start_col, CELL_WIDTH, Cell_get(this->SD, cell));
}

void Display_write_cell_shift(display_t * this, int8_t row_num, 
        uint8_t row_shift, uint8_t col_num, cell_e cell) {
    int16_t start_row = row_num * CELL_WIDTH + DISPLAY_START_ROW + row_shift;
    uint16_t start_col = col_num * CELL_WIDTH + DISPLAY_START_COL;
    if (start_row < DISPLAY_START_ROW) {
        int16_t offset = DISPLAY_START_ROW-start_row;
        
        if (offset < CELL_WIDTH) {
            const color_e *colors = Cell_get(this->SD, cell);
            colors = &colors[(CELL_WIDTH - row_shift) * CELL_WIDTH];
            LCD_write_region(this->LCD, DISPLAY_START_ROW, row_shift, start_col, CELL_WIDTH, 
                    colors);
        }
    } else {
        LCD_write_region(this->LCD, start_row, CELL_WIDTH, 
                start_col, CELL_WIDTH, Cell_get(this->SD, cell));
    }
}