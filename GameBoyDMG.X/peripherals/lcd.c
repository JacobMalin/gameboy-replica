/* 
 * File:   lcd.c
 * Author: Jacob Malin
 *
 * Created on November 10, 2024, 12:54 AM
 */

#include "lcd.h"

uint8_t LCD_RGB_colors[4][3] = {
//  {rrr, ggg, bbb} out of 255
    
    // Whites
//    {248, 248, 248}, // White
//    {168, 168, 168}, // Gray
//    { 96,  96,  96}, // Dark Gray
//    {  0,   0,   0}, // Black
    
    // Greens
    {159, 171,   5}, // White
    {113, 134,   4}, // Gray
    { 38,  81,   6}, // Dark Gray
    {  0,  40,   0}, // Black
};

uint16_t LCD_colors[4];

lcd_t *LCD(spi_t *SPI, PORT_t *cs_port, uint8_t cs_pin, 
        PORT_t *dcx_port, uint8_t dcx_pin) {
    static lcd_t LCD;

    LCD.SPI_Client = SPI_Client(SPI, cs_port, cs_pin);
    LCD.DCX = Output(dcx_port, dcx_pin);
    
    _LCD_setup(&LCD);

    return &LCD;
}

void _LCD_write_cmd(lcd_t *this, uint8_t cmd) {
    Output_CLR(this->DCX);
    _SPI_write(cmd);
}

void _LCD_write_data(lcd_t *this, uint8_t data) {
    Output_SET(this->DCX);
    _SPI_write(data);
}

void _LCD_write_datas(lcd_t *this, uint8_t data[], uint8_t len) {
    Output_SET(this->DCX);
    for (uint8_t i = 0; i < len; i++) {
        _SPI_write(data[i]);
    }
}

void _LCD_setup(lcd_t *this) {
    // Color setup
    for (uint8_t i = 0; i < 4; i++) {
        uint8_t red, green, blue;
        uint16_t code = 0, r, g, b;

        red   = LCD_RGB_colors[i][0];
        green = LCD_RGB_colors[i][1];
        blue  = LCD_RGB_colors[i][2];

        r = (red * 63 / 255) >> 1;
        g = (green * 63 / 255) << 5;
        b = ((blue * 63 / 255) >> 1) << 11;
        code = r | g | b;
        
        LCD_colors[i] = code;
    }
    
    _SPI_Client_select(this->SPI_Client);
    
    // Exit sleep
    // Must wait 50 ms before sleep OFF
    _delay_ms(50);
    _LCD_write_cmd(this, LCD_CMD_SLPOUT);
    // Must wait 120 ms after sleep OFF
    _delay_ms(LCD_SLEEP_WAIT_MS);
    
    // Set memory access control
    _LCD_write_cmd(this, LCD_CMD_MADCTL);
    _LCD_write_data(this, LCD_MADCTL_MV); // Exchange col and row
    
    // Set pixel format
    _LCD_write_cmd(this, LCD_CMD_PIXSET);
    _LCD_write_data(this, LCD_PIXSET_DBI_16); // Set pixel format to 16-bit
    
    // Restrict region to full screen
    _LCD_restrict_region(this, 0x0000, LCD_ROWS, 0x0000, LCD_COLS);
    
    // Clear the display
    _LCD_write_cmd(this, LCD_CMD_RAMWR);
    Output_SET(this->DCX);
    for (uint16_t i = 0; i < LCD_ROWS; i++) {
        for (uint16_t j = 0; j < LCD_COLS; j++) {
            _LCD_write_color(B);
        }
    }
    
    // Battery LED
    // Restrict region led
    _LCD_restrict_region(this, LED_Y, LED_WIDTH, LED_X, LED_WIDTH);
    
    // Set red
    _LCD_write_cmd(this, LCD_CMD_RAMWR);
    Output_SET(this->DCX);
    for (uint16_t i = 0; i < LED_WIDTH; i++) {
        for (uint16_t j = 0; j < LED_WIDTH; j++) {
            _LCD_write_red();
        }
    }
    
    // Turn on display
    _LCD_write_cmd(this, LCD_CMD_DISPON);
    
    _SPI_Client_deselect(this->SPI_Client);
}

void _LCD_write_color(color_e color) {
    uint16_t code = LCD_colors[color];
    _SPI_write(code >> 8);
    _SPI_write(code);
}

void _LCD_write_red() {
    uint16_t code = 0b0000000000011111;
    _SPI_write(code >> 8);
    _SPI_write(code);
}

void _LCD_restrict_region(lcd_t * this, uint16_t start_row, uint16_t num_rows, 
            uint16_t start_col, uint16_t num_cols) {
    uint16_t end_col, end_row;
    
    // Column address set
    _LCD_write_cmd(this, LCD_CMD_CASET);
    end_col = start_col + num_cols - 1;
    _LCD_write_data(this, start_col >> 8);
    _LCD_write_data(this, start_col);
    _LCD_write_data(this, end_col >> 8);
    _LCD_write_data(this, end_col);
    
    // Page address set (rows)
    _LCD_write_cmd(this, LCD_CMD_PASET);
    end_row = start_row + num_rows - 1;
    _LCD_write_data(this, start_row >> 8);
    _LCD_write_data(this, start_row);
    _LCD_write_data(this, end_row >> 8);
    _LCD_write_data(this, end_row);
}

void LCD_write_region(lcd_t * this, uint16_t start_row, uint16_t num_rows, 
            uint16_t start_col, uint16_t num_cols, 
        const color_e *colors) {
    _SPI_Client_select(this->SPI_Client);
    
    _LCD_restrict_region(this, start_row, num_rows, start_col, num_cols);
    
    _LCD_write_cmd(this, LCD_CMD_RAMWR);
    Output_SET(this->DCX);
    for (uint16_t i = 0; i < num_rows; i++) {
        for (uint16_t j = 0; j < num_cols; j++) {
            _LCD_write_color(colors[i * CELL_WIDTH + j]);
        }
    }
    
    _SPI_Client_deselect(this->SPI_Client);
}