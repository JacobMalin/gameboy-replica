/* 
 * File:   cell.c
 * Author: Jacob Malin
 *
 * Created on November 14, 2024, 5:37 AM
 */

#include "cell.h"

static uint32_t block_last = CELL_E_LEN;
static cell_e last = CELL_E_LEN;
static cell_t buf;
static uint8_t sd_buf[((CELLS_PER_BLOCK * CELL_WIDTH * CELL_WIDTH) / 4) + 1];

void Cell(sd_t *SD) {
    // Must stay commented out, as these are all already loaded in SD memory
//    cell_e first = ___; const color_e *cells[] = {*Cell____, *Cell_BK_, *Cell_WH_, *Cell_GY_, *Cell_OVL, *Cell_UDL, *Cell_LLN, *Cell_VLN, *Cell_LWL, *Cell_A__, *Cell_B__, *Cell_C__,};
//    cell_e first = D__; const color_e *cells[] = {*Cell_D__, *Cell_E__, *Cell_F__, *Cell_G__, *Cell_H__, *Cell_I__, *Cell_J__, *Cell_K__, *Cell_L__, *Cell_M__, *Cell_N__, *Cell_O__,};
//    cell_e first = P__; const color_e *cells[] = {*Cell_P__, *Cell_Q__, *Cell_R__, *Cell_S__, *Cell_T__, *Cell_U__, *Cell_V__, *Cell_W__, *Cell_X__, *Cell_Y__, *Cell_Z__, *Cell_A_G,};
//    cell_e first = B_G; const color_e *cells[] = {*Cell_B_G, *Cell_C_G, *Cell_E_G, *Cell_F_G, *Cell_O_G, *Cell_P_G, *Cell_T_G, *Cell_Y_G, *Cell_NB0, *Cell_NB1, *Cell_NB2, *Cell_NB3,};
//    cell_e first = NB4; const color_e *cells[] = {*Cell_NB4, *Cell_NB5, *Cell_NB6, *Cell_NB7, *Cell_NB8, *Cell_NB9, *Cell_G_0, *Cell_G_1, *Cell_G_2, *Cell_G_3, *Cell_G_4, *Cell_G_5,};
//    cell_e first = G_6; const color_e *cells[] = {*Cell_G_6, *Cell_G_7, *Cell_G_8, *Cell_G_9, *Cell_CPY, *Cell_PLY, *Cell_DSH, *Cell_DSG, *Cell_DT1, *Cell_DT2, *Cell_DT3, *Cell_PRD,};
//    cell_e first = CMA; const color_e *cells[] = {*Cell_CMA, *Cell_QOT, *Cell_PDQ, *Cell_XXX, *Cell_FM1, *Cell_FM2, *Cell_FM3, *Cell_FM4, *Cell_FM5, *Cell_FM6, *Cell_FM7, *Cell_FM8,};
//    cell_e first = TS1; const color_e *cells[] = {*Cell_TS1, *Cell_TS2, *Cell_TS3, *Cell_TS4, *Cell_TS5, *Cell_TS6, *Cell_TS7, *Cell_TS8, *Cell_TS9, *Cell_T10, *Cell_T11, *Cell_T12,};
//    cell_e first = T13; const color_e *cells[] = {*Cell_T13, *Cell_T14, *Cell_T15, *Cell_T16, *Cell_T17, *Cell_T18, *Cell_T19, *Cell_T20, *Cell_T21, *Cell_T22, *Cell_T23, *Cell_T24,};
//    cell_e first = T25; const color_e *cells[] = {*Cell_T25, *Cell_T26, *Cell_T27, *Cell_T28, *Cell_T29, *Cell_T30, *Cell_T31, *Cell_T32, *Cell_T33, *Cell_T34, *Cell_T35, *Cell_T36,};
//    cell_e first = T37; const color_e *cells[] = {*Cell_T37, *Cell_T38, *Cell_T39, *Cell_T40, *Cell_T41, *Cell_T42, *Cell_T43, *Cell_T44, *Cell_T45, *Cell_T46, *Cell_T47, *Cell_T48,};
//    cell_e first = SKY; const color_e *cells[] = {*Cell_SKY, *Cell_ST1, *Cell_ST2, *Cell_MN1, *Cell_MN2, *Cell_MN3, *Cell_MN4, *Cell_MW1, *Cell_MW2, *Cell_MW3, *Cell_MW4, *Cell_MW5,};
//    cell_e first = MW6; const color_e *cells[] = {*Cell_MW6, *Cell_MW7, *Cell_MW8, *Cell_MW9, *Cell_M10, *Cell_M11, *Cell_M12, *Cell_M13, *Cell_M14, *Cell_M15, *Cell_M16, *Cell_M17,};
//    cell_e first = M18; const color_e *cells[] = {*Cell_M18, *Cell_M19, *Cell_M20, *Cell_M21, *Cell_M22, *Cell_BG1, *Cell_BG2, *Cell_BG3, *Cell_BG4, *Cell_BG5, *Cell_BG6, *Cell_ND1,};
//    cell_e first = ND2; const color_e *cells[] = {*Cell_ND2, *Cell_ND3, *Cell_ND4, *Cell_ND5, *Cell_ND6, *Cell_MBG, *Cell_MB1, *Cell_MB2, *Cell_MB3, *Cell_MB4, *Cell_MB5, *Cell_MB6,};
//    cell_e first = MB7; const color_e *cells[] = {*Cell_MB7, *Cell_MB8, *Cell_RB1, *Cell_RB2, *Cell_RB3, *Cell_RB4, *Cell_RB5, *Cell_RB6, *Cell_RB7, *Cell_RB8, *Cell_RB9, *Cell_R10,};
//    cell_e first = R11; const color_e *cells[] = {*Cell_R11, *Cell_R12, *Cell_SB1, *Cell_SB2, *Cell_SB3, *Cell_SB4, *Cell_SB5, *Cell_SB6, *Cell_SB7, *Cell_SB8, *Cell_SB9, *Cell_S10,};
//    cell_e first = S11; const color_e *cells[] = {*Cell_S11, *Cell_GB1, *Cell_GB2, *Cell_GB3, *Cell_GB4, *Cell_GB5, *Cell_TI1, *Cell_TI2, *Cell_TI3, *Cell_TI4, *Cell_TI5, *Cell_TI6,};
//    cell_e first = TMJ; const color_e *cells[] = {*Cell_TMJ, *Cell_TML, *Cell_TMO, *Cell_TMS, *Cell_TMT, *Cell_TMZ, *Cell_BK1, *Cell_BK2, *Cell_BK3, *Cell_BK4, *Cell_BK5, *Cell_BK6,};
//    cell_e first = BK7; const color_e *cells[] = {*Cell_BK7, *Cell_BK8, *Cell_DB1, *Cell_DB2, *Cell_DB3, *Cell_DB4, *Cell_DB5, *Cell_DB6, *Cell_DB7, *Cell_DB8, *Cell_DB9, *Cell_D10,};
//    cell_e first = D11; const color_e *cells[] = {*Cell_D11, *Cell_PB1, *Cell_PB2, *Cell_PB3, *Cell_PB4, *Cell_PB5, *Cell_PB6, *Cell_PB7, *Cell_PB8, *Cell_SF1, *Cell_SF2, *Cell_SF3,};
//    cell_e first = SF4; const color_e *cells[] = {*Cell_SF4, *Cell_SF5, *Cell_SF6, *Cell_TSN, *Cell_OB1, *Cell_OB2, *Cell_OB3, *Cell_OB4, *Cell_OB5, *Cell_OB6, *Cell_OB7, *Cell_OB8,};
//    cell_e first = DL1; const color_e *cells[] = {*Cell_DL1, *Cell_DL2, *Cell_DL3, *Cell_HRT, *Cell_BN1, *Cell_BN2, *Cell_BN3, *Cell_BN4, *Cell_BN5, *Cell_BN6, *Cell_BN7, *Cell_BN8,};
//    cell_e first = BN9; const color_e *cells[] = {*Cell_BN9, *Cell_B10, *Cell_B11, *Cell_B12, *Cell_B13, *Cell_B14, *Cell_B15, *Cell_B16, *Cell_B17, *Cell_B18, *Cell_B19, *Cell_B20,};
//    cell_e first = B21; const color_e *cells[] = {*Cell_B21, *Cell_B22, *Cell_B23, *Cell_B24, *Cell_TDM, };
//    Cell_set(SD, first, cells);
}

const color_e *Cell_get(sd_t *SD, cell_e index) {
    uint32_t block_index = FIRST_CELL_BLOCK + index / CELLS_PER_BLOCK;
    
    if (block_index != block_last) { // Check block cache
        SD_read_block(SD, block_index, (uint8_t *)sd_buf, 
                sizeof(sd_buf));

        block_last = block_index;
    }
    
    if (index != last) { // Check cache
        // Unpack the cells; 4 colors per byte to 1 color per byte
        uint8_t bit, byte;
        uint16_t byte_count;
        uint8_t local_index = index % CELLS_PER_BLOCK;
        
        uint32_t bit_tot = local_index * 2 * CELL_WIDTH * CELL_WIDTH;
        byte_count = bit_tot / 8;
        byte = sd_buf[++byte_count];
        bit = bit_tot % 8;
        
        for (uint8_t i = 0; i < CELL_WIDTH; i++) {
            for (uint8_t j = 0; j < CELL_WIDTH; j++) {
                uint8_t mask = 0b00000011;
                color_e color = (byte >> bit) & mask;
                buf[i][j] = color;

                bit += 2;
                if (bit >= 8) {
                    byte = sd_buf[++byte_count];
                    bit = 0;
                }
            }
        }
        
        last = index;
    }

    return *buf;
}

void Cell_set(sd_t *SD, cell_e first_index, const color_e *cells[]) {
    uint32_t block_index = FIRST_CELL_BLOCK + first_index / CELLS_PER_BLOCK;
    
    // Pack the CELLS_PER_BLOCK cells into roughly a quarter the size
    uint8_t bit = 0;
    uint8_t byte = 0x00;
    uint16_t byte_count = 0;
    for (uint8_t k = 0; k < CELLS_PER_BLOCK; k++) {
        for (uint8_t i = 0; i < CELL_WIDTH; i++) {
            for (uint8_t j = 0; j < CELL_WIDTH; j++) {
                byte |= cells[k][i * CELL_WIDTH + j] << bit;
                bit += 2;
                if (bit >= 8) {
                    sd_buf[++byte_count] = byte;
                    
                    byte = 0x00;
                    bit = 0;
                }
            }
        }
    }
    
    SD_write_block(SD, block_index, (uint8_t *)sd_buf, sizeof(sd_buf));
}

const cell_t Cell____ = { // ___
    {D, W, W, W, W, W, W, W, W, W, W, W, W},
    {D, W, W, W, W, W, W, W, W, W, W, W, W},
    {D, W, W, W, W, W, W, W, W, W, W, W, W},
    {D, W, W, W, W, W, W, W, W, W, W, W, W},
    {D, W, W, W, W, W, W, W, W, W, W, W, W},
    {D, W, W, W, W, W, W, W, W, W, W, W, W},
    {D, W, W, W, W, W, W, W, W, W, W, W, W},
    {D, W, W, W, W, W, W, W, W, W, W, W, W},
    {D, W, W, W, W, W, W, W, W, W, W, W, W},
    {D, W, W, W, W, W, W, W, W, W, W, W, W},
    {D, W, W, W, W, W, W, W, W, W, W, W, W},
    {D, W, W, W, W, W, W, W, W, W, W, W, W},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
};

const cell_t Cell_BK_ = { // BK_
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
};

const cell_t Cell_WH_ = { // WH_
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_GY_ = { // GY_
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
};

const cell_t Cell_OVL = { // OVL
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_UDL = { // UDL
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_LLN = { // LLN
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_VLN = { // VLN
    {W, W, W, W, W, W, B, B, W, W, W, W, W},
    {W, W, W, W, W, W, B, B, W, W, W, W, W},
    {W, W, W, W, W, W, B, B, W, W, W, W, W},
    {W, W, W, W, W, W, B, B, W, W, W, W, W},
    {W, W, W, W, W, W, B, B, W, W, W, W, W},
    {W, W, W, W, W, W, B, B, W, W, W, W, W},
    {W, W, W, W, W, W, B, B, W, W, W, W, W},
    {W, W, W, W, W, W, B, B, W, W, W, W, W},
    {W, W, W, W, W, W, B, B, W, W, W, W, W},
    {W, W, W, W, W, W, B, B, W, W, W, W, W},
    {W, W, W, W, W, W, B, B, W, W, W, W, W},
    {W, W, W, W, W, W, B, B, W, W, W, W, W},
    {W, W, W, W, W, W, B, B, W, W, W, W, W},
};

const cell_t Cell_LWL = { // LWL
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
};

const cell_t Cell_A__ = { // A__
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, B, B, B, B, B, B, W, W, W, W},
    {W, W, B, B, B, B, B, B, B, B, W, W, W},
    {W, B, B, W, W, W, W, B, B, B, B, W, W},
    {W, B, B, W, W, W, W, B, B, B, B, B, W},
    {W, B, B, W, W, W, W, B, B, B, B, B, W},
    {W, B, B, W, W, W, W, B, B, B, B, B, W},
    {W, B, B, B, B, B, B, B, B, B, B, B, W},
    {W, B, B, B, B, B, B, B, B, B, B, B, W},
    {W, B, B, W, W, W, W, B, B, B, B, B, W},
    {W, B, B, W, W, W, W, B, B, B, B, B, W},
    {W, B, B, W, W, W, W, B, B, B, B, B, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_B__ = { // B__
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, B, B, B, B, W, W, W, W},
    {W, B, B, B, B, B, B, B, B, B, W, W, W},
    {W, B, B, B, W, W, W, W, B, B, B, W, W},
    {W, B, B, B, W, W, W, W, B, B, B, W, W},
    {W, B, B, B, B, B, B, B, B, B, W, W, W},
    {W, B, B, B, B, B, B, B, B, B, B, W, W},
    {W, B, B, B, W, W, W, W, B, B, B, B, W},
    {W, B, B, B, W, W, W, W, W, B, B, B, W},
    {W, B, B, B, W, W, W, W, B, B, B, B, W},
    {W, B, B, B, B, B, B, B, B, B, B, W, W},
    {W, B, B, B, B, B, B, B, B, B, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_C__ = { // C__
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, B, B, B, B, B, B, B, W, W, W},
    {W, W, B, B, B, B, B, B, B, B, B, W, W},
    {W, B, B, B, B, W, W, W, W, B, B, B, W},
    {W, B, B, B, B, W, W, W, W, B, B, B, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, W, W, W, W, B, B, B, W},
    {W, B, B, B, B, W, W, W, W, B, B, B, W},
    {W, W, B, B, B, B, B, B, B, B, B, W, W},
    {W, W, W, B, B, B, B, B, B, B, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_D__ = { // D__
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, B, B, B, B, B, W, W, W},
    {W, B, B, B, B, B, B, B, B, B, B, W, W},
    {W, B, B, W, W, W, B, B, B, B, B, B, W},
    {W, B, B, W, W, W, W, B, B, B, B, B, W},
    {W, B, B, W, W, W, W, B, B, B, B, B, W},
    {W, B, B, W, W, W, W, B, B, B, B, B, W},
    {W, B, B, W, W, W, W, B, B, B, B, B, W},
    {W, B, B, W, W, W, W, B, B, B, B, B, W},
    {W, B, B, W, W, W, B, B, B, B, B, B, W},
    {W, B, B, B, B, B, B, B, B, B, B, W, W},
    {W, B, B, B, B, B, B, B, B, B, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_E__ = { // E__
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, B, B, B, B, B, B, B, W},
    {W, B, B, B, B, B, B, B, B, B, B, B, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, B, B, B, B, B, W, W, W},
    {W, B, B, B, B, B, B, B, B, B, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, B, B, B, B, B, B, B, W},
    {W, B, B, B, B, B, B, B, B, B, B, B, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_F__ = { // F__
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, B, B, B, B, B, B, B, W},
    {W, B, B, B, B, B, B, B, B, B, B, B, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, B, B, B, B, B, W, W, W},
    {W, B, B, B, B, B, B, B, B, B, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_G__ = { // G__
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, B, B, B, B, B, B, B, W, W, W},
    {W, W, B, B, B, B, B, B, B, B, B, W, W},
    {W, B, B, B, B, W, W, W, B, B, B, B, W},
    {W, B, B, B, B, W, W, W, W, B, B, B, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, W, B, B, B, B, B, B, W},
    {W, B, B, B, B, W, B, B, B, B, B, B, W},
    {W, B, B, B, B, W, W, W, W, B, B, B, W},
    {W, B, B, B, B, W, W, W, W, B, B, B, W},
    {W, W, B, B, B, B, B, B, B, B, B, B, W},
    {W, W, W, B, B, B, B, B, B, B, B, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_H__ = { // H__
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, B, B, B, W, W, W, W, B, B, B, B, W},
    {W, B, B, B, W, W, W, W, B, B, B, B, W},
    {W, B, B, B, W, W, W, W, B, B, B, B, W},
    {W, B, B, B, W, W, W, W, B, B, B, B, W},
    {W, B, B, B, B, B, B, B, B, B, B, B, W},
    {W, B, B, B, B, B, B, B, B, B, B, B, W},
    {W, B, B, B, W, W, W, W, B, B, B, B, W},
    {W, B, B, B, W, W, W, W, B, B, B, B, W},
    {W, B, B, B, W, W, W, W, B, B, B, B, W},
    {W, B, B, B, W, W, W, W, B, B, B, B, W},
    {W, B, B, B, W, W, W, W, B, B, B, B, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_I__ = { // I__
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, B, B, B, B, B, B, B, B, B, W, W},
    {W, W, B, B, B, B, B, B, B, B, B, W, W},
    {W, W, W, W, W, B, B, B, W, W, W, W, W},
    {W, W, W, W, W, B, B, B, W, W, W, W, W},
    {W, W, W, W, W, B, B, B, W, W, W, W, W},
    {W, W, W, W, W, B, B, B, W, W, W, W, W},
    {W, W, W, W, W, B, B, B, W, W, W, W, W},
    {W, W, W, W, W, B, B, B, W, W, W, W, W},
    {W, W, W, W, W, B, B, B, W, W, W, W, W},
    {W, W, B, B, B, B, B, B, B, B, B, W, W},
    {W, W, B, B, B, B, B, B, B, B, B, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_J__ = { // J__
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, B, B, B, B, B, B, B, W},
    {W, W, W, W, W, B, B, B, B, B, B, B, W},
    {W, W, W, W, W, W, W, B, B, B, W, W, W},
    {W, W, W, W, W, W, W, B, B, B, W, W, W},
    {W, W, W, W, W, W, W, B, B, B, W, W, W},
    {W, W, W, W, W, W, W, B, B, B, W, W, W},
    {W, B, B, B, W, W, W, B, B, B, W, W, W},
    {W, B, B, B, W, W, W, B, B, B, W, W, W},
    {W, B, B, B, W, W, B, B, B, B, W, W, W},
    {W, W, B, B, B, B, B, B, B, W, W, W, W},
    {W, W, W, B, B, B, B, B, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_K__ = { // K__
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, B, B, B, W, W, W, W, W, B, B, B, W},
    {W, B, B, B, W, W, W, W, B, B, B, B, W},
    {W, B, B, B, W, W, W, B, B, B, B, W, W},
    {W, B, B, B, W, W, B, B, B, B, W, W, W},
    {W, B, B, B, B, B, B, B, B, W, W, W, W},
    {W, B, B, B, B, B, B, B, W, W, W, W, W},
    {W, B, B, B, B, B, B, B, B, W, W, W, W},
    {W, B, B, B, W, W, B, B, B, B, W, W, W},
    {W, B, B, B, W, W, W, B, B, B, B, W, W},
    {W, B, B, B, W, W, W, W, B, B, B, B, W},
    {W, B, B, B, W, W, W, W, W, B, B, B, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_L__ = { // L__
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, B, B, B, B, B, B, B, W},
    {W, B, B, B, B, B, B, B, B, B, B, B, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_M__ = { // M__
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, B, B, W, W, W, W, W, W, B, B, B, W},
    {W, B, B, W, W, W, W, W, W, B, B, B, W},
    {W, B, B, B, W, W, W, W, B, B, B, B, W},
    {W, B, B, B, B, W, W, B, B, B, B, B, W},
    {W, B, B, B, B, B, B, B, B, B, B, B, W},
    {W, B, B, B, B, B, B, B, B, B, B, B, W},
    {W, B, B, W, B, B, B, B, W, B, B, B, W},
    {W, B, B, W, W, B, B, W, W, B, B, B, W},
    {W, B, B, W, W, W, W, W, W, B, B, B, W},
    {W, B, B, W, W, W, W, W, W, B, B, B, W},
    {W, B, B, W, W, W, W, W, W, B, B, B, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_N__ = { // N__
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, B, B, W, W, W, W, W, W, B, B, B, W},
    {W, B, B, B, W, W, W, W, W, B, B, B, W},
    {W, B, B, B, B, W, W, W, W, B, B, B, W},
    {W, B, B, B, B, B, W, W, W, B, B, B, W},
    {W, B, B, B, B, B, B, W, W, B, B, B, W},
    {W, B, B, W, B, B, B, B, W, B, B, B, W},
    {W, B, B, W, W, B, B, B, B, B, B, B, W},
    {W, B, B, W, W, W, B, B, B, B, B, B, W},
    {W, B, B, W, W, W, W, B, B, B, B, B, W},
    {W, B, B, W, W, W, W, W, B, B, B, B, W},
    {W, B, B, W, W, W, W, W, W, B, B, B, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_O__ = { // O__
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, B, B, B, B, B, B, B, W, W, W},
    {W, W, B, B, B, B, B, B, B, B, B, W, W},
    {W, B, B, B, B, W, W, W, B, B, B, B, W},
    {W, B, B, B, W, W, W, W, W, B, B, B, W},
    {W, B, B, B, W, W, W, W, W, B, B, B, W},
    {W, B, B, B, W, W, W, W, W, B, B, B, W},
    {W, B, B, B, W, W, W, W, W, B, B, B, W},
    {W, B, B, B, W, W, W, W, W, B, B, B, W},
    {W, B, B, B, B, W, W, W, B, B, B, B, W},
    {W, W, B, B, B, B, B, B, B, B, B, W, W},
    {W, W, W, B, B, B, B, B, B, B, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_P__ = { // P__
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, B, B, B, B, B, W, W, W},
    {W, B, B, B, B, B, B, B, B, B, B, W, W},
    {W, B, B, B, B, W, W, W, B, B, B, B, W},
    {W, B, B, B, B, W, W, W, W, B, B, B, W},
    {W, B, B, B, B, W, W, W, W, B, B, B, W},
    {W, B, B, B, B, W, W, W, B, B, B, B, W},
    {W, B, B, B, B, B, B, B, B, B, B, W, W},
    {W, B, B, B, B, B, B, B, B, B, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_Q__ = { // Q__
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, B, B, B, B, B, B, B, W, W, W},
    {W, W, B, B, B, B, B, B, B, B, B, W, W},
    {W, B, B, B, B, W, W, W, W, B, B, B, W},
    {W, B, B, B, W, W, W, W, W, W, B, B, W},
    {W, B, B, B, W, W, W, W, W, W, B, B, W},
    {W, B, B, B, W, W, B, B, W, W, B, B, W},
    {W, B, B, B, W, W, B, B, B, W, B, B, W},
    {W, B, B, B, W, W, W, B, B, B, B, W, W},
    {W, B, B, B, B, W, W, W, B, B, B, W, W},
    {W, W, B, B, B, B, B, B, B, B, B, B, W},
    {W, W, W, B, B, B, B, B, W, W, B, B, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_R__ = { // R__
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, B, B, B, B, B, W, W, W},
    {W, B, B, B, B, B, B, B, B, B, B, W, W},
    {W, B, B, B, B, W, W, W, B, B, B, B, W},
    {W, B, B, B, B, W, W, W, W, B, B, B, W},
    {W, B, B, B, B, W, W, W, W, B, B, B, W},
    {W, B, B, B, B, W, W, W, B, B, B, B, W},
    {W, B, B, B, B, B, B, B, B, B, B, W, W},
    {W, B, B, B, B, B, B, B, B, B, W, W, W},
    {W, B, B, B, B, W, W, B, B, W, W, W, W},
    {W, B, B, B, B, W, W, B, B, B, B, B, W},
    {W, B, B, B, B, W, W, W, B, B, B, B, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_S__ = { // S__
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, B, B, B, B, B, B, B, W, W, W},
    {W, W, B, B, B, B, B, B, B, B, B, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, W, B, B, B, B, B, B, B, B, W, W, W},
    {W, W, W, B, B, B, B, B, B, B, B, W, W},
    {W, W, W, W, W, W, W, B, B, B, B, B, W},
    {W, B, B, W, W, W, W, W, B, B, B, B, W},
    {W, B, B, W, W, W, W, B, B, B, B, B, W},
    {W, W, B, B, B, B, B, B, B, B, B, W, W},
    {W, W, W, B, B, B, B, B, B, B, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_T__ = { // T__
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, B, B, B, B, B, B, B, W},
    {W, B, B, B, B, B, B, B, B, B, B, B, W},
    {W, B, B, B, B, B, B, B, B, B, B, B, W},
    {W, W, W, W, W, B, B, B, W, W, W, W, W},
    {W, W, W, W, W, B, B, B, W, W, W, W, W},
    {W, W, W, W, W, B, B, B, W, W, W, W, W},
    {W, W, W, W, W, B, B, B, W, W, W, W, W},
    {W, W, W, W, W, B, B, B, W, W, W, W, W},
    {W, W, W, W, W, B, B, B, W, W, W, W, W},
    {W, W, W, W, W, B, B, B, W, W, W, W, W},
    {W, W, W, W, W, B, B, B, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_U__ = { // U__
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, B, B, B, W, W, W, W, W, B, B, B, W},
    {W, B, B, B, W, W, W, W, W, B, B, B, W},
    {W, B, B, B, W, W, W, W, W, B, B, B, W},
    {W, B, B, B, W, W, W, W, W, B, B, B, W},
    {W, B, B, B, W, W, W, W, W, B, B, B, W},
    {W, B, B, B, W, W, W, W, W, B, B, B, W},
    {W, B, B, B, W, W, W, W, W, B, B, B, W},
    {W, B, B, B, B, W, W, W, B, B, B, B, W},
    {W, B, B, B, B, B, B, B, B, B, B, B, W},
    {W, W, B, B, B, B, B, B, B, B, B, W, W},
    {W, W, W, B, B, B, B, B, B, B, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_V__ = { // V__
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, B, B, W, W, W, W, W, B, B, B, B, W},
    {W, B, B, W, W, W, W, W, B, B, B, B, W},
    {W, B, B, W, W, W, W, W, B, B, B, B, W},
    {W, B, B, W, W, W, W, W, B, B, B, B, W},
    {W, B, B, W, W, W, W, W, B, B, B, B, W},
    {W, B, B, W, W, W, W, W, B, B, B, B, W},
    {W, B, B, B, W, W, W, B, B, B, B, B, W},
    {W, B, B, B, B, W, B, B, B, B, B, W, W},
    {W, W, B, B, B, B, B, B, B, B, W, W, W},
    {W, W, W, B, B, B, B, B, B, W, W, W, W},
    {W, W, W, W, B, B, B, B, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_W__ = { // W__
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, B, B, W, W, W, W, W, W, B, B, B, W},
    {W, B, B, W, W, W, W, W, W, B, B, B, W},
    {W, B, B, W, W, W, W, W, W, B, B, B, W},
    {W, B, B, W, W, W, W, W, W, B, B, B, W},
    {W, B, B, W, W, B, B, W, W, B, B, B, W},
    {W, B, B, W, B, B, B, B, W, B, B, B, W},
    {W, B, B, B, B, B, B, B, B, B, B, B, W},
    {W, B, B, B, B, B, B, B, B, B, B, B, W},
    {W, B, B, B, B, W, W, B, B, B, B, B, W},
    {W, B, B, B, W, W, W, W, B, B, B, B, W},
    {W, B, B, W, W, W, W, W, W, B, B, B, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_X__ = { // X__
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, B, B, W, W, W, W, W, W, B, B, B, W},
    {W, B, B, B, W, W, W, W, B, B, B, B, W},
    {W, W, B, B, B, W, W, B, B, B, B, W, W},
    {W, W, W, B, B, B, B, B, B, B, W, W, W},
    {W, W, W, W, B, B, B, B, B, W, W, W, W},
    {W, W, W, W, B, B, B, B, B, W, W, W, W},
    {W, W, W, B, B, B, B, B, B, W, W, W, W},
    {W, W, B, B, B, B, B, B, B, B, W, W, W},
    {W, B, B, B, B, W, W, W, B, B, B, W, W},
    {W, B, B, B, W, W, W, W, W, B, B, B, W},
    {W, B, B, W, W, W, W, W, W, W, B, B, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_Y__ = { // Y__
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, B, B, B, W, W, W, B, B, B, W, W},
    {W, W, B, B, B, W, W, W, B, B, B, W, W},
    {W, W, B, B, B, W, W, W, B, B, B, W, W},
    {W, W, B, B, B, B, W, B, B, B, B, W, W},
    {W, W, W, B, B, B, B, B, B, B, W, W, W},
    {W, W, W, W, B, B, B, B, B, W, W, W, W},
    {W, W, W, W, W, B, B, B, W, W, W, W, W},
    {W, W, W, W, W, B, B, B, W, W, W, W, W},
    {W, W, W, W, W, B, B, B, W, W, W, W, W},
    {W, W, W, W, W, B, B, B, W, W, W, W, W},
    {W, W, W, W, W, B, B, B, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_Z__ = { // Z__
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, B, B, B, B, B, B, B, W},
    {W, B, B, B, B, B, B, B, B, B, B, B, W},
    {W, W, W, W, W, W, W, B, B, B, B, B, W},
    {W, W, W, W, W, W, B, B, B, B, B, W, W},
    {W, W, W, W, W, B, B, B, B, B, W, W, W},
    {W, W, W, W, B, B, B, B, B, W, W, W, W},
    {W, W, W, B, B, B, B, B, W, W, W, W, W},
    {W, W, B, B, B, B, B, W, W, W, W, W, W},
    {W, B, B, B, B, B, W, W, W, W, W, W, W},
    {W, B, B, B, B, B, B, B, B, B, B, B, W},
    {W, B, B, B, B, B, B, B, B, B, B, B, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_A_G = { // A_G
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, G, G, G, G, G, G, W, W, W, W},
    {W, W, G, G, G, G, G, G, G, G, W, W, W},
    {W, G, G, W, W, W, W, G, G, G, G, W, W},
    {W, G, G, W, W, W, W, G, G, G, G, G, W},
    {W, G, G, W, W, W, W, G, G, G, G, G, W},
    {W, G, G, W, W, W, W, G, G, G, G, G, W},
    {W, G, G, G, G, G, G, G, G, G, G, G, W},
    {W, G, G, G, G, G, G, G, G, G, G, G, W},
    {W, G, G, W, W, W, W, G, G, G, G, G, W},
    {W, G, G, W, W, W, W, G, G, G, G, G, W},
    {W, G, G, W, W, W, W, G, G, G, G, G, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_B_G = { // B_G
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, G, G, G, G, G, G, G, G, W, W, W, W},
    {W, G, G, G, G, G, G, G, G, G, W, W, W},
    {W, G, G, G, W, W, W, W, G, G, G, W, W},
    {W, G, G, G, W, W, W, W, G, G, G, W, W},
    {W, G, G, G, G, G, G, G, G, G, W, W, W},
    {W, G, G, G, G, G, G, G, G, G, G, W, W},
    {W, G, G, G, W, W, W, W, G, G, G, G, W},
    {W, G, G, G, W, W, W, W, W, G, G, G, W},
    {W, G, G, G, W, W, W, W, G, G, G, G, W},
    {W, G, G, G, G, G, G, G, G, G, G, W, W},
    {W, G, G, G, G, G, G, G, G, G, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_C_G = { // C_G
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, G, G, G, G, G, G, G, W, W, W},
    {W, W, G, G, G, G, G, G, G, G, G, W, W},
    {W, G, G, G, G, W, W, W, W, G, G, G, W},
    {W, G, G, G, G, W, W, W, W, G, G, G, W},
    {W, G, G, G, G, W, W, W, W, W, W, W, W},
    {W, G, G, G, G, W, W, W, W, W, W, W, W},
    {W, G, G, G, G, W, W, W, W, W, W, W, W},
    {W, G, G, G, G, W, W, W, W, G, G, G, W},
    {W, G, G, G, G, W, W, W, W, G, G, G, W},
    {W, W, G, G, G, G, G, G, G, G, G, W, W},
    {W, W, W, G, G, G, G, G, G, G, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_E_G = { // E_G
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, G, G, G, G, G, G, G, G, G, G, G, W},
    {W, G, G, G, G, G, G, G, G, G, G, G, W},
    {W, G, G, G, G, W, W, W, W, W, W, W, W},
    {W, G, G, G, G, W, W, W, W, W, W, W, W},
    {W, G, G, G, G, G, G, G, G, G, W, W, W},
    {W, G, G, G, G, G, G, G, G, G, W, W, W},
    {W, G, G, G, G, W, W, W, W, W, W, W, W},
    {W, G, G, G, G, W, W, W, W, W, W, W, W},
    {W, G, G, G, G, W, W, W, W, W, W, W, W},
    {W, G, G, G, G, G, G, G, G, G, G, G, W},
    {W, G, G, G, G, G, G, G, G, G, G, G, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_F_G = { // F_G
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, G, G, G, G, G, G, G, G, G, G, G, W},
    {W, G, G, G, G, G, G, G, G, G, G, G, W},
    {W, G, G, G, G, W, W, W, W, W, W, W, W},
    {W, G, G, G, G, W, W, W, W, W, W, W, W},
    {W, G, G, G, G, W, W, W, W, W, W, W, W},
    {W, G, G, G, G, G, G, G, G, G, W, W, W},
    {W, G, G, G, G, G, G, G, G, G, W, W, W},
    {W, G, G, G, G, W, W, W, W, W, W, W, W},
    {W, G, G, G, G, W, W, W, W, W, W, W, W},
    {W, G, G, G, G, W, W, W, W, W, W, W, W},
    {W, G, G, G, G, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_O_G = { // O_G
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, G, G, G, G, G, G, G, W, W, W},
    {W, W, G, G, G, G, G, G, G, G, G, W, W},
    {W, G, G, G, G, W, W, W, G, G, G, G, W},
    {W, G, G, G, W, W, W, W, W, G, G, G, W},
    {W, G, G, G, W, W, W, W, W, G, G, G, W},
    {W, G, G, G, W, W, W, W, W, G, G, G, W},
    {W, G, G, G, W, W, W, W, W, G, G, G, W},
    {W, G, G, G, W, W, W, W, W, G, G, G, W},
    {W, G, G, G, G, W, W, W, G, G, G, G, W},
    {W, W, G, G, G, G, G, G, G, G, G, W, W},
    {W, W, W, G, G, G, G, G, G, G, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_P_G = { // P_G
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, G, G, G, G, G, G, G, G, G, W, W, W},
    {W, G, G, G, G, G, G, G, G, G, G, W, W},
    {W, G, G, G, G, W, W, W, G, G, G, G, W},
    {W, G, G, G, G, W, W, W, W, G, G, G, W},
    {W, G, G, G, G, W, W, W, W, G, G, G, W},
    {W, G, G, G, G, W, W, W, G, G, G, G, W},
    {W, G, G, G, G, G, G, G, G, G, G, W, W},
    {W, G, G, G, G, G, G, G, G, G, W, W, W},
    {W, G, G, G, G, W, W, W, W, W, W, W, W},
    {W, G, G, G, G, W, W, W, W, W, W, W, W},
    {W, G, G, G, G, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_T_G = { // T_G
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, G, G, G, G, G, G, G, G, G, G, G, W},
    {W, G, G, G, G, G, G, G, G, G, G, G, W},
    {W, G, G, G, G, G, G, G, G, G, G, G, W},
    {W, W, W, W, W, G, G, G, W, W, W, W, W},
    {W, W, W, W, W, G, G, G, W, W, W, W, W},
    {W, W, W, W, W, G, G, G, W, W, W, W, W},
    {W, W, W, W, W, G, G, G, W, W, W, W, W},
    {W, W, W, W, W, G, G, G, W, W, W, W, W},
    {W, W, W, W, W, G, G, G, W, W, W, W, W},
    {W, W, W, W, W, G, G, G, W, W, W, W, W},
    {W, W, W, W, W, G, G, G, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_Y_G = { // Y_G
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, G, G, G, W, W, W, G, G, G, W, W},
    {W, W, G, G, G, W, W, W, G, G, G, W, W},
    {W, W, G, G, G, W, W, W, G, G, G, W, W},
    {W, W, G, G, G, G, W, G, G, G, G, W, W},
    {W, W, W, G, G, G, G, G, G, G, W, W, W},
    {W, W, W, W, G, G, G, G, G, W, W, W, W},
    {W, W, W, W, W, G, G, G, W, W, W, W, W},
    {W, W, W, W, W, G, G, G, W, W, W, W, W},
    {W, W, W, W, W, G, G, G, W, W, W, W, W},
    {W, W, W, W, W, G, G, G, W, W, W, W, W},
    {W, W, W, W, W, G, G, G, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_NB0 = { // NB0
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, B, B, B, B, B, B, B, W, W, W},
    {W, W, B, B, B, B, B, B, B, B, B, W, W},
    {W, B, B, B, B, W, W, W, B, B, B, B, W},
    {W, B, B, B, B, W, W, W, B, B, B, B, W},
    {W, B, B, B, B, W, W, W, B, B, B, B, W},
    {W, B, B, B, B, W, W, W, B, B, B, B, W},
    {W, B, B, B, B, W, W, W, B, B, B, B, W},
    {W, B, B, B, B, W, W, W, B, B, B, B, W},
    {W, B, B, B, B, W, W, W, B, B, B, B, W},
    {W, W, B, B, B, B, B, B, B, B, B, W, W},
    {W, W, W, B, B, B, B, B, B, B, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_NB1 = { // NB1
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, B, B, B, B, W, W, W, W, W},
    {W, W, W, W, B, B, B, B, W, W, W, W, W},
    {W, W, B, B, B, B, B, B, W, W, W, W, W},
    {W, W, B, B, B, B, B, B, W, W, W, W, W},
    {W, W, W, W, B, B, B, B, W, W, W, W, W},
    {W, W, W, W, B, B, B, B, W, W, W, W, W},
    {W, W, W, W, B, B, B, B, W, W, W, W, W},
    {W, W, W, W, B, B, B, B, W, W, W, W, W},
    {W, W, W, W, B, B, B, B, W, W, W, W, W},
    {W, W, B, B, B, B, B, B, B, B, W, W, W},
    {W, W, B, B, B, B, B, B, B, B, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_NB2 = { // NB2
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, B, B, B, B, B, B, B, W, W, W},
    {W, W, B, B, B, B, B, B, B, B, B, W, W},
    {W, B, B, B, W, W, W, B, B, B, B, B, W},
    {W, B, B, W, W, W, W, W, B, B, B, B, W},
    {W, W, W, W, W, W, W, W, B, B, B, B, W},
    {W, W, W, W, W, W, W, B, B, B, B, B, W},
    {W, W, W, B, B, B, B, B, B, B, B, W, W},
    {W, W, B, B, B, B, B, W, W, W, W, W, W},
    {W, B, B, B, B, B, W, W, W, W, W, W, W},
    {W, B, B, B, B, B, B, B, B, B, B, B, W},
    {W, B, B, B, B, B, B, B, B, B, B, B, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_NB3 = { // NB3
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, B, B, B, B, B, W, W, W},
    {W, B, B, B, B, B, B, B, B, B, B, W, W},
    {W, W, W, W, W, W, W, B, B, B, B, B, W},
    {W, W, W, W, W, W, W, W, B, B, B, B, W},
    {W, W, B, B, B, B, B, B, B, B, B, W, W},
    {W, W, B, B, B, B, B, B, B, B, B, B, W},
    {W, W, W, W, W, W, W, B, B, B, B, B, W},
    {W, W, W, W, W, W, W, W, B, B, B, B, W},
    {W, W, W, W, W, W, W, B, B, B, B, B, W},
    {W, B, B, B, B, B, B, B, B, B, B, W, W},
    {W, B, B, B, B, B, B, B, B, B, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_NB4 = { // NB4
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, B, B, B, B, B, B, W, W, W},
    {W, W, W, B, B, B, B, B, B, B, W, W, W},
    {W, W, B, B, B, W, B, B, B, B, W, W, W},
    {W, B, B, B, W, W, B, B, B, B, W, W, W},
    {W, B, B, W, W, W, B, B, B, B, W, W, W},
    {W, B, B, W, W, W, B, B, B, B, B, B, W},
    {W, B, B, W, W, W, B, B, B, B, B, B, W},
    {W, B, B, B, B, B, B, B, B, B, B, B, W},
    {W, B, B, B, B, B, B, B, B, B, B, B, W},
    {W, W, W, W, W, W, B, B, B, B, W, W, W},
    {W, W, W, W, W, W, B, B, B, B, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_NB5 = { // NB5
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, B, B, B, B, B, B, W, W},
    {W, B, B, B, B, B, B, B, B, B, B, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, B, B, B, B, B, W, W, W},
    {W, W, W, W, W, B, B, B, B, B, B, W, W},
    {W, W, W, W, W, W, B, B, B, B, B, B, W},
    {W, B, B, W, W, W, B, B, B, B, B, B, W},
    {W, B, B, W, W, W, B, B, B, B, B, B, W},
    {W, W, B, B, B, B, B, B, B, B, B, W, W},
    {W, W, W, B, B, B, B, B, B, B, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_NB6 = { // NB6
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, B, B, B, B, B, B, B, W, W, W},
    {W, W, B, B, B, B, B, B, B, B, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, B, B, B, B, B, W, W, W},
    {W, B, B, B, B, B, B, B, B, B, B, W, W},
    {W, B, B, B, B, W, W, W, B, B, B, B, W},
    {W, B, B, B, B, W, W, W, B, B, B, B, W},
    {W, B, B, B, B, W, W, W, B, B, B, B, W},
    {W, W, B, B, B, B, B, B, B, B, B, W, W},
    {W, W, W, B, B, B, B, B, B, B, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_NB7 = { // NB7
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, B, B, B, B, B, B, W, W},
    {W, B, B, B, B, B, B, B, B, B, B, W, W},
    {W, W, W, W, W, W, W, W, B, B, B, W, W},
    {W, W, W, W, W, W, W, W, B, B, B, W, W},
    {W, W, W, W, W, W, W, B, B, B, B, W, W},
    {W, W, W, W, W, W, B, B, B, B, W, W, W},
    {W, W, W, W, W, B, B, B, B, W, W, W, W},
    {W, W, W, W, B, B, B, B, W, W, W, W, W},
    {W, W, W, B, B, B, B, B, W, W, W, W, W},
    {W, W, W, B, B, B, B, B, W, W, W, W, W},
    {W, W, W, B, B, B, B, B, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_NB8 = { // NB8
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, B, B, B, B, B, B, B, W, W, W},
    {W, W, B, B, B, B, B, B, B, B, B, W, W},
    {W, B, B, B, W, W, W, B, B, B, B, B, W},
    {W, B, B, B, W, W, W, B, B, B, B, B, W},
    {W, W, B, B, B, B, B, B, B, B, B, W, W},
    {W, W, B, B, B, B, B, B, B, B, B, W, W},
    {W, B, B, B, W, W, W, B, B, B, B, B, W},
    {W, B, B, B, W, W, W, B, B, B, B, B, W},
    {W, B, B, B, W, W, W, B, B, B, B, B, W},
    {W, W, B, B, B, B, B, B, B, B, B, W, W},
    {W, W, W, B, B, B, B, B, B, B, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_NB9 = { // NB9
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, B, B, B, B, B, B, B, B, W, W, W},
    {W, B, B, B, B, B, B, B, B, B, B, W, W},
    {W, B, B, W, W, W, W, B, B, B, B, B, W},
    {W, B, B, W, W, W, W, B, B, B, B, B, W},
    {W, B, B, W, W, W, W, B, B, B, B, B, W},
    {W, B, B, B, B, B, B, B, B, B, B, B, W},
    {W, W, B, B, B, B, B, B, B, B, B, B, W},
    {W, W, W, W, W, W, W, B, B, B, B, B, W},
    {W, W, W, W, W, W, W, B, B, B, B, B, W},
    {W, W, W, B, B, B, B, B, B, B, B, W, W},
    {W, W, W, B, B, B, B, B, B, B, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_G_0 = { // G_0
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, G, G, G, G, G, G, G, W, W, W},
    {W, W, G, G, G, G, G, G, G, G, G, W, W},
    {W, G, G, G, G, W, W, W, G, G, G, G, W},
    {W, G, G, G, G, W, W, W, G, G, G, G, W},
    {W, G, G, G, G, W, W, W, G, G, G, G, W},
    {W, G, G, G, G, W, W, W, G, G, G, G, W},
    {W, G, G, G, G, W, W, W, G, G, G, G, W},
    {W, G, G, G, G, W, W, W, G, G, G, G, W},
    {W, G, G, G, G, W, W, W, G, G, G, G, W},
    {W, W, G, G, G, G, G, G, G, G, G, W, W},
    {W, W, W, G, G, G, G, G, G, G, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_G_1 = { // G_1
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, G, G, G, G, W, W, W, W, W},
    {W, W, W, W, G, G, G, G, W, W, W, W, W},
    {W, W, G, G, G, G, G, G, W, W, W, W, W},
    {W, W, G, G, G, G, G, G, W, W, W, W, W},
    {W, W, W, W, G, G, G, G, W, W, W, W, W},
    {W, W, W, W, G, G, G, G, W, W, W, W, W},
    {W, W, W, W, G, G, G, G, W, W, W, W, W},
    {W, W, W, W, G, G, G, G, W, W, W, W, W},
    {W, W, W, W, G, G, G, G, W, W, W, W, W},
    {W, W, G, G, G, G, G, G, G, G, W, W, W},
    {W, W, G, G, G, G, G, G, G, G, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_G_2 = { // G_2
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, G, G, G, G, G, G, G, W, W, W},
    {W, W, G, G, G, G, G, G, G, G, G, W, W},
    {W, G, G, G, W, W, W, G, G, G, G, G, W},
    {W, G, G, W, W, W, W, W, G, G, G, G, W},
    {W, W, W, W, W, W, W, W, G, G, G, G, W},
    {W, W, W, W, W, W, W, G, G, G, G, G, W},
    {W, W, W, G, G, G, G, G, G, G, G, W, W},
    {W, W, G, G, G, G, G, W, W, W, W, W, W},
    {W, G, G, G, G, G, W, W, W, W, W, W, W},
    {W, G, G, G, G, G, G, G, G, G, G, G, W},
    {W, G, G, G, G, G, G, G, G, G, G, G, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_G_3 = { // G_3
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, G, G, G, G, G, G, G, G, G, W, W, W},
    {W, G, G, G, G, G, G, G, G, G, G, W, W},
    {W, W, W, W, W, W, W, G, G, G, G, G, W},
    {W, W, W, W, W, W, W, W, G, G, G, G, W},
    {W, W, G, G, G, G, G, G, G, G, G, W, W},
    {W, W, G, G, G, G, G, G, G, G, G, G, W},
    {W, W, W, W, W, W, W, G, G, G, G, G, W},
    {W, W, W, W, W, W, W, W, G, G, G, G, W},
    {W, W, W, W, W, W, W, G, G, G, G, G, W},
    {W, G, G, G, G, G, G, G, G, G, G, W, W},
    {W, G, G, G, G, G, G, G, G, G, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_G_4 = { // G_4
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, G, G, G, G, G, G, W, W, W},
    {W, W, W, G, G, G, G, G, G, G, W, W, W},
    {W, W, G, G, G, W, G, G, G, G, W, W, W},
    {W, G, G, G, W, W, G, G, G, G, W, W, W},
    {W, G, G, W, W, W, G, G, G, G, W, W, W},
    {W, G, G, W, W, W, G, G, G, G, G, G, W},
    {W, G, G, W, W, W, G, G, G, G, G, G, W},
    {W, G, G, G, G, G, G, G, G, G, G, G, W},
    {W, G, G, G, G, G, G, G, G, G, G, G, W},
    {W, W, W, W, W, W, G, G, G, G, W, W, W},
    {W, W, W, W, W, W, G, G, G, G, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_G_5 = { // G_5
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, G, G, G, G, G, G, G, G, G, G, W, W},
    {W, G, G, G, G, G, G, G, G, G, G, W, W},
    {W, G, G, G, G, W, W, W, W, W, W, W, W},
    {W, G, G, G, G, W, W, W, W, W, W, W, W},
    {W, G, G, G, G, G, G, G, G, G, W, W, W},
    {W, W, W, W, W, G, G, G, G, G, G, W, W},
    {W, W, W, W, W, W, G, G, G, G, G, G, W},
    {W, G, G, W, W, W, G, G, G, G, G, G, W},
    {W, G, G, W, W, W, G, G, G, G, G, G, W},
    {W, W, G, G, G, G, G, G, G, G, G, W, W},
    {W, W, W, G, G, G, G, G, G, G, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_G_6 = { // G_6
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, G, G, G, G, G, G, G, W, W, W},
    {W, W, G, G, G, G, G, G, G, G, W, W, W},
    {W, G, G, G, G, W, W, W, W, W, W, W, W},
    {W, G, G, G, G, W, W, W, W, W, W, W, W},
    {W, G, G, G, G, G, G, G, G, G, W, W, W},
    {W, G, G, G, G, G, G, G, G, G, G, W, W},
    {W, G, G, G, G, W, W, W, G, G, G, G, W},
    {W, G, G, G, G, W, W, W, G, G, G, G, W},
    {W, G, G, G, G, W, W, W, G, G, G, G, W},
    {W, W, G, G, G, G, G, G, G, G, G, W, W},
    {W, W, W, G, G, G, G, G, G, G, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_G_7 = { // G_7
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, G, G, G, G, G, G, G, G, G, G, W, W},
    {W, G, G, G, G, G, G, G, G, G, G, W, W},
    {W, W, W, W, W, W, W, W, G, G, G, W, W},
    {W, W, W, W, W, W, W, W, G, G, G, W, W},
    {W, W, W, W, W, W, W, G, G, G, G, W, W},
    {W, W, W, W, W, W, G, G, G, G, W, W, W},
    {W, W, W, W, W, G, G, G, G, W, W, W, W},
    {W, W, W, W, G, G, G, G, W, W, W, W, W},
    {W, W, W, G, G, G, G, G, W, W, W, W, W},
    {W, W, W, G, G, G, G, G, W, W, W, W, W},
    {W, W, W, G, G, G, G, G, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_G_8 = { // G_8
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, G, G, G, G, G, G, G, W, W, W},
    {W, W, G, G, G, G, G, G, G, G, G, W, W},
    {W, G, G, G, W, W, W, G, G, G, G, G, W},
    {W, G, G, G, W, W, W, G, G, G, G, G, W},
    {W, W, G, G, G, G, G, G, G, G, G, W, W},
    {W, W, G, G, G, G, G, G, G, G, G, W, W},
    {W, G, G, G, W, W, W, G, G, G, G, G, W},
    {W, G, G, G, W, W, W, G, G, G, G, G, W},
    {W, G, G, G, W, W, W, G, G, G, G, G, W},
    {W, W, G, G, G, G, G, G, G, G, G, W, W},
    {W, W, W, G, G, G, G, G, G, G, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_G_9 = { // G_9
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, G, G, G, G, G, G, G, G, W, W, W},
    {W, G, G, G, G, G, G, G, G, G, G, W, W},
    {W, G, G, W, W, W, W, G, G, G, G, G, W},
    {W, G, G, W, W, W, W, G, G, G, G, G, W},
    {W, G, G, W, W, W, W, G, G, G, G, G, W},
    {W, G, G, G, G, G, G, G, G, G, G, G, W},
    {W, W, G, G, G, G, G, G, G, G, G, G, W},
    {W, W, W, W, W, W, W, G, G, G, G, G, W},
    {W, W, W, W, W, W, W, G, G, G, G, G, W},
    {W, W, W, G, G, G, G, G, G, G, G, W, W},
    {W, W, W, G, G, G, G, G, G, G, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_CPY = { // CPY
    {W, W, W, W, B, B, B, B, W, W, W, W, W},
    {W, W, B, B, B, B, B, B, B, B, W, W, W},
    {W, B, B, B, W, W, W, W, B, B, B, W, W},
    {W, B, B, W, B, B, B, B, W, B, B, W, W},
    {B, B, W, B, B, W, W, B, B, W, B, B, W},
    {B, B, W, B, B, W, W, W, W, W, B, B, W},
    {B, B, W, B, B, W, W, W, W, W, B, B, W},
    {B, B, W, B, B, W, W, B, B, W, B, B, W},
    {W, B, B, W, B, B, B, B, W, B, B, W, W},
    {W, B, B, B, W, W, W, W, B, B, B, W, W},
    {W, W, B, B, B, B, B, B, B, B, W, W, W},
    {W, W, W, W, B, B, B, B, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_PLY = { // PLY
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, B, B, W, W, W, W, W, W},
    {W, B, B, B, B, B, B, W, W, W, W, W, W},
    {W, B, B, B, B, B, B, B, B, W, W, W, W},
    {W, B, B, B, B, B, B, B, B, W, W, W, W},
    {W, B, B, B, B, B, B, B, B, W, W, W, W},
    {W, B, B, B, B, B, B, W, W, W, W, W, W},
    {W, B, B, B, B, B, B, W, W, W, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_DSH = { // DSH
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, B, B, B, B, B, B, B, W, W, W},
    {W, W, W, B, B, B, B, B, B, B, W, W, W},
    {W, W, W, B, B, B, B, B, B, B, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_DSG = { // DSG
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, G, G, G, G, G, G, G, W, W, W},
    {W, W, W, G, G, G, G, G, G, G, W, W, W},
    {W, W, W, G, G, G, G, G, G, G, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_DT1 = { // DT1
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, W, B, B, W, B, B, W, B, B, W, B},
    {B, B, W, B, B, W, B, B, W, B, B, W, B},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_DT2 = { // DT2
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, W, B, B, W, B, B, W, B, B, W, B, B},
    {B, W, B, B, W, B, B, W, B, B, W, B, B},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_DT3 = { // DT3
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, B, B, W, B, B, W, B, B, W, B, B, W},
    {W, B, B, W, B, B, W, B, B, W, B, B, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_PRD = { // PRD
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_CMA = { // CMA
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, W, W, B, B, W, W, W, W, W, W, W, W},
    {W, W, W, B, B, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_QOT = { // QOT
    {W, W, W, W, W, W, B, B, B, W, B, B, B},
    {W, W, W, W, W, W, B, B, B, W, B, B, B},
    {W, W, W, W, W, W, B, B, B, W, B, B, B},
    {W, W, W, W, W, W, W, B, B, W, W, B, B},
    {W, W, W, W, W, W, W, W, B, W, W, W, B},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_PDQ = { // PDQ
    {W, W, W, W, W, W, B, B, B, W, B, B, B},
    {W, W, W, W, W, W, B, B, B, W, B, B, B},
    {W, W, W, W, W, W, B, B, B, W, B, B, B},
    {W, W, W, W, W, W, W, B, B, W, W, B, B},
    {W, W, W, W, W, W, W, W, B, W, W, W, B},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_XXX = { // XXX
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, B, B, W, W, W, W, W, W, W, B, B, W},
    {W, B, B, W, W, W, W, W, W, W, B, B, W},
    {W, W, W, B, B, W, W, W, B, B, W, W, W},
    {W, W, W, B, B, W, W, W, B, B, W, W, W},
    {W, W, W, W, W, B, B, B, W, W, W, W, W},
    {W, W, W, W, W, B, B, B, W, W, W, W, W},
    {W, W, W, W, W, B, B, B, W, W, W, W, W},
    {W, W, W, B, B, W, W, W, B, B, W, W, W},
    {W, W, W, B, B, W, W, W, B, B, W, W, W},
    {W, B, B, W, W, W, W, W, W, W, B, B, W},
    {W, B, B, W, W, W, W, W, W, W, B, B, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_FM1 = { // FM1
    {B, B, B, B, B, W, W, W, W, W, W, W, W},
    {B, B, B, B, B, W, W, W, W, W, W, W, W},
    {B, B, B, B, B, G, W, W, W, W, W, W, W},
    {B, B, B, B, B, G, G, W, W, G, G, G, G},
    {B, B, B, B, B, G, G, G, W, G, G, G, G},
    {B, B, B, B, B, G, G, G, G, W, W, W, W},
    {B, B, B, B, B, G, G, G, G, W, W, D, D},
    {B, B, B, B, B, G, G, G, G, W, W, D, D},
    {B, B, B, B, B, G, G, G, G, W, W, D, D},
    {B, B, B, B, B, G, G, G, G, W, W, D, D},
    {B, B, B, B, B, G, G, G, G, W, W, D, D},
    {B, B, B, B, B, G, G, G, G, W, W, D, D},
    {B, B, B, B, B, G, G, G, G, W, W, D, D},
};

const cell_t Cell_FM2 = { // FM2
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_FM3 = { // FM3
    {W, W, W, W, W, W, W, W, B, B, B, B, B},
    {W, W, W, W, W, W, W, W, B, B, B, B, B},
    {W, W, W, W, W, W, W, G, B, B, B, B, B},
    {G, G, G, G, W, W, G, G, B, B, B, B, B},
    {G, G, G, G, W, G, G, G, B, B, B, B, B},
    {W, W, W, W, G, G, G, G, B, B, B, B, B},
    {D, D, W, W, G, G, G, G, B, B, B, B, B},
    {D, D, W, W, G, G, G, G, B, B, B, B, B},
    {D, D, W, W, G, G, G, G, B, B, B, B, B},
    {D, D, W, W, G, G, G, G, B, B, B, B, B},
    {D, D, W, W, G, G, G, G, B, B, B, B, B},
    {D, D, W, W, G, G, G, G, B, B, B, B, B},
    {D, D, W, W, G, G, G, G, B, B, B, B, B},
};

const cell_t Cell_FM4 = { // FM4
    {B, B, B, B, B, G, G, G, G, W, W, D, D},
    {B, B, B, B, B, G, G, G, G, W, W, D, D},
    {B, B, B, B, B, G, G, G, G, W, W, D, D},
    {B, B, B, B, B, G, G, G, G, W, W, D, D},
    {B, B, B, B, B, G, G, G, G, W, W, D, D},
    {B, B, B, B, B, G, G, G, G, W, W, D, D},
    {B, B, B, B, B, G, G, G, G, W, W, D, D},
    {B, B, B, B, B, G, G, G, G, W, W, D, D},
    {B, B, B, B, B, G, G, G, G, W, W, D, D},
    {B, B, B, B, B, G, G, G, G, W, W, D, D},
    {B, B, B, B, B, G, G, G, G, W, W, D, D},
    {B, B, B, B, B, G, G, G, G, W, W, D, D},
    {B, B, B, B, B, G, G, G, G, W, W, D, D},
};

const cell_t Cell_FM5 = { // FM5
    {D, D, W, W, G, G, G, G, B, B, B, B, B},
    {D, D, W, W, G, G, G, G, B, B, B, B, B},
    {D, D, W, W, G, G, G, G, B, B, B, B, B},
    {D, D, W, W, G, G, G, G, B, B, B, B, B},
    {D, D, W, W, G, G, G, G, B, B, B, B, B},
    {D, D, W, W, G, G, G, G, B, B, B, B, B},
    {D, D, W, W, G, G, G, G, B, B, B, B, B},
    {D, D, W, W, G, G, G, G, B, B, B, B, B},
    {D, D, W, W, G, G, G, G, B, B, B, B, B},
    {D, D, W, W, G, G, G, G, B, B, B, B, B},
    {D, D, W, W, G, G, G, G, B, B, B, B, B},
    {D, D, W, W, G, G, G, G, B, B, B, B, B},
    {D, D, W, W, G, G, G, G, B, B, B, B, B},
};

const cell_t Cell_FM6 = { // FM6
    {B, B, B, B, B, G, G, G, G, W, W, D, D},
    {B, B, B, B, B, G, G, G, G, W, W, D, D},
    {B, B, B, B, B, G, G, G, G, W, W, D, D},
    {B, B, B, B, B, G, G, G, G, W, W, D, D},
    {B, B, B, B, B, G, G, G, G, W, W, D, D},
    {B, B, B, B, B, G, G, G, G, W, W, D, D},
    {B, B, B, B, B, G, G, G, G, W, W, D, D},
    {B, B, B, B, B, G, G, G, G, W, W, W, W},
    {B, B, B, B, B, G, G, G, B, B, B, B, B},
    {B, B, B, B, B, G, G, B, B, B, B, B, B},
    {B, B, B, B, B, G, B, B, B, B, B, B, B},
    {B, B, B, B, B, D, D, D, D, D, D, D, D},
    {B, B, B, B, B, D, D, D, D, D, D, D, D},
};

const cell_t Cell_FM7 = { // FM7
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
};

const cell_t Cell_FM8 = { // FM8
    {D, D, W, W, G, G, G, G, B, B, B, B, B},
    {D, D, W, W, G, G, G, G, B, B, B, B, B},
    {D, D, W, W, G, G, G, G, B, B, B, B, B},
    {D, D, W, W, G, G, G, G, B, B, B, B, B},
    {D, D, W, W, G, G, G, G, B, B, B, B, B},
    {D, D, W, W, G, G, G, G, B, B, B, B, B},
    {D, D, W, W, G, G, G, G, B, B, B, B, B},
    {W, W, W, W, G, G, G, G, B, B, B, B, B},
    {B, B, B, B, B, G, G, G, B, B, B, B, B},
    {B, B, B, B, B, B, G, G, B, B, B, B, B},
    {B, B, B, B, B, B, B, G, B, B, B, B, B},
    {D, D, D, D, D, D, D, D, B, B, B, B, B},
    {D, D, D, D, D, D, D, D, B, B, B, B, B},
};

const cell_t Cell_TS1 = { // TS1
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, B, B, B},
    {W, W, W, W, W, W, W, W, W, W, B, B, B},
    {W, W, W, W, W, W, W, W, W, W, B, B, W},
    {W, W, W, W, W, W, W, W, W, W, B, B, W},
    {W, W, W, W, W, W, W, W, W, W, B, B, W},
    {W, W, W, W, W, W, W, W, W, W, B, B, W},
    {W, W, W, W, W, W, W, W, W, W, B, B, W},
    {W, W, W, W, W, W, W, W, W, W, B, B, W},
    {W, W, W, W, W, W, W, W, W, W, B, B, W},
    {W, W, W, W, W, W, W, W, W, W, B, B, W},
    {W, W, W, W, W, W, W, W, W, W, B, B, W},
    {W, W, W, W, W, W, W, W, W, W, B, B, G},
};

const cell_t Cell_TS2 = { // TS2
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, B, W, W, B, B, B},
    {B, B, B, B, B, B, B, B, W, W, B, B, B},
    {W, W, W, W, W, W, B, B, W, W, B, B, W},
    {W, W, W, W, W, W, B, W, W, W, B, B, W},
    {W, W, W, W, W, B, B, W, W, W, B, B, W},
    {W, W, W, W, W, B, W, W, W, W, B, B, W},
    {W, W, W, W, B, B, W, W, W, W, B, B, W},
    {W, W, W, W, B, W, W, W, W, W, B, B, W},
    {W, W, W, B, B, W, W, W, W, W, B, B, W},
    {W, W, W, B, W, W, W, W, W, W, B, B, W},
    {W, W, B, B, W, W, W, W, W, W, B, B, W},
    {G, G, B, W, W, W, W, W, W, W, B, B, G},
};

const cell_t Cell_TS3 = { // TS3
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, W, B, B},
    {B, B, B, B, B, B, B, B, B, B, W, B, B},
    {W, W, W, W, W, W, W, B, B, B, W, B, B},
    {W, W, W, W, W, W, W, B, B, B, W, W, B},
    {W, W, W, W, W, W, W, B, B, B, W, W, B},
    {W, W, W, W, W, W, W, B, B, B, W, W, W},
    {W, W, W, W, W, W, W, B, B, B, W, W, W},
    {W, W, W, W, W, W, W, B, B, B, W, W, W},
    {W, W, W, W, W, W, W, B, B, B, W, W, W},
    {W, W, W, W, W, W, W, B, B, B, W, W, W},
    {W, W, W, W, W, W, W, B, B, B, W, W, W},
    {G, G, G, G, G, G, G, B, B, B, W, W, W},
};

const cell_t Cell_TS4 = { // TS4
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, W, W, W},
    {W, W, W, W, W, W, W, B, B, B, W, W, W},
    {B, W, W, W, W, W, W, B, B, B, W, W, W},
    {B, W, W, W, W, W, W, B, B, B, W, W, W},
    {B, B, W, W, W, W, W, B, B, B, W, W, W},
    {B, B, W, W, W, W, W, B, B, B, W, W, W},
    {W, B, B, W, W, W, W, B, B, B, W, W, W},
    {W, B, B, W, W, W, W, B, B, B, W, W, W},
    {W, W, B, B, W, W, W, B, B, B, W, W, W},
    {W, W, B, B, W, W, W, B, B, B, W, W, W},
    {W, W, W, B, B, G, G, B, B, B, W, W, W},
};

const cell_t Cell_TS5 = { // TS5
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, W, W, W, W, W, W, W, W, B, B, B},
    {B, B, W, W, W, W, W, W, W, W, B, B, B},
    {B, B, W, W, W, W, W, W, W, W, B, B, B},
    {B, B, W, W, W, W, W, W, W, W, B, B, B},
    {B, B, W, W, W, W, W, W, W, W, B, B, B},
    {B, B, W, W, W, W, W, W, W, W, B, B, B},
    {B, B, W, W, W, W, W, W, W, W, B, B, B},
    {B, B, W, W, W, W, W, W, W, W, B, B, B},
    {B, B, W, W, W, W, W, W, W, W, B, B, B},
    {B, B, G, G, G, G, G, G, G, G, B, B, B},
};

const cell_t Cell_TS6 = { // TS6
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, B, B, B, B, B, B, B, B},
    {W, B, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, W, W, W, W, W, W, W, W, W},
    {W, W, W, B, B, W, W, W, W, W, W, W, W},
    {W, W, W, W, B, B, W, W, W, W, W, W, W},
    {W, W, W, W, W, B, B, W, W, W, W, W, W},
    {W, W, W, W, W, W, B, B, W, W, W, W, W},
    {W, W, W, W, W, W, W, B, B, W, W, W, W},
    {W, W, W, W, W, W, W, W, B, B, W, W, W},
    {W, W, W, W, W, W, W, W, W, B, B, W, W},
    {W, W, W, W, W, W, W, W, W, W, B, B, W},
    {W, W, W, W, W, W, W, W, W, W, W, B, B},
};

const cell_t Cell_TS7 = { // TS7
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, W, W, W, B, B, B},
    {B, B, B, B, B, B, B, W, W, W, B, B, B},
    {W, W, W, W, B, B, B, W, W, W, B, B, W},
    {W, W, W, W, B, B, B, W, W, W, B, B, W},
    {W, W, W, W, B, B, B, W, W, W, B, B, W},
    {W, W, W, W, B, B, B, W, W, W, B, B, W},
    {W, W, W, W, B, B, B, W, W, W, B, B, W},
    {W, W, W, W, B, B, B, W, W, W, B, B, W},
    {W, W, W, W, B, B, B, W, W, W, B, B, W},
    {W, W, W, W, B, B, B, W, W, W, B, B, W},
    {W, W, W, W, B, B, B, W, W, W, B, B, W},
    {G, G, G, G, B, B, B, W, W, W, B, B, G},
};

const cell_t Cell_TS8 = { // TS8
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, B, B, B, B, B, B, B, W, W, W, W},
    {W, W, B, B, B, B, B, B, B, B, W, W, W},
    {W, W, B, B, W, W, W, W, B, B, B, B, W},
    {W, W, B, B, W, W, W, W, W, B, B, B, B},
    {W, W, B, B, W, W, W, W, W, W, W, B, B},
    {W, W, B, B, W, W, W, W, W, W, W, W, B},
    {W, W, B, B, W, W, W, W, W, W, W, W, W},
    {W, W, B, B, W, W, W, W, W, W, W, W, W},
    {W, W, B, B, W, W, W, W, W, W, W, W, W},
    {W, W, B, B, W, W, W, W, W, W, W, W, W},
    {W, W, B, B, W, W, W, W, W, W, W, W, W},
    {W, W, B, B, G, G, G, G, G, G, G, G, G},
};

const cell_t Cell_TS9 = { // TS9
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, B, B},
    {W, W, W, W, W, W, W, W, W, W, W, B, B},
    {W, W, W, W, W, W, W, W, W, W, W, B, B},
    {W, W, W, W, W, W, W, W, W, W, W, B, B},
    {B, W, W, W, W, W, W, W, W, W, W, B, B},
    {B, B, W, W, W, W, W, W, W, W, W, B, B},
    {B, B, B, W, W, W, W, W, W, W, W, B, B},
    {W, B, B, W, W, W, W, W, W, W, W, B, B},
    {W, W, B, B, W, W, W, W, W, W, W, B, B},
    {W, W, B, B, W, W, W, W, W, W, W, B, B},
    {W, W, B, B, B, W, W, W, W, W, W, B, B},
    {G, G, B, B, B, W, W, W, W, W, W, B, B},
};

const cell_t Cell_T10 = { // T10
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, B, W, W},
    {B, B, B, B, B, B, B, B, B, B, B, W, W},
    {W, W, W, W, W, W, W, W, B, B, B, W, W},
    {W, W, W, W, W, W, W, W, B, B, B, W, W},
    {W, W, W, W, W, W, W, W, B, B, B, W, W},
    {W, W, W, W, W, W, W, W, B, B, B, W, W},
    {W, W, W, W, W, W, W, W, B, B, B, W, W},
    {W, W, W, W, W, W, W, W, B, B, B, W, W},
    {W, W, W, W, W, W, W, W, B, B, B, W, W},
    {W, W, W, W, W, W, W, W, B, B, B, W, W},
    {W, W, W, W, W, W, W, W, B, B, B, W, W},
    {G, G, G, G, G, G, G, G, B, B, B, W, W},
};

const cell_t Cell_T11 = { // T11
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, B, B, B, W, W, B, B, B},
    {W, W, W, B, B, B, B, W, W, W, B, B, B},
    {W, W, B, B, B, B, B, W, W, W, B, B, B},
    {W, B, B, B, W, B, B, B, W, W, W, B, B},
    {W, B, B, W, W, W, B, B, B, W, W, W, B},
    {B, B, W, W, W, W, W, B, B, B, W, W, W},
    {B, B, W, W, W, W, W, B, B, B, W, W, W},
    {B, B, W, W, W, W, W, W, B, B, W, W, W},
    {B, B, W, W, W, W, W, W, B, B, B, W, W},
    {B, B, W, W, W, W, W, W, W, B, B, B, W},
    {B, B, G, G, G, G, G, G, G, G, B, B, W},
};

const cell_t Cell_T12 = { // T12
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, W, W, W, W, W, W, W, W, W, W, B},
    {W, W, W, W, W, W, W, W, W, W, W, W, B},
    {B, W, W, W, W, W, W, W, W, W, W, W, B},
    {B, B, W, W, W, W, W, W, W, W, W, W, B},
    {B, B, B, W, W, W, W, W, W, W, W, W, B},
    {W, B, B, W, W, W, W, W, W, W, W, W, B},
    {W, W, B, B, W, W, W, W, W, W, W, W, B},
    {W, W, W, B, B, W, W, W, W, W, W, W, B},
    {W, W, W, W, B, B, G, G, G, G, G, G, B},
};

const cell_t Cell_T13 = { // T13
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, W, W, B, B, B, B, B, B, B, W, W},
    {B, B, W, W, B, B, B, B, B, B, B, W, W},
    {B, B, W, W, W, W, W, B, B, W, W, W, W},
    {B, B, W, W, W, W, W, B, B, W, W, W, W},
    {B, B, W, B, B, W, W, B, B, W, W, W, W},
    {B, B, W, B, B, W, W, B, B, W, W, W, W},
    {B, B, W, B, B, B, B, B, B, W, W, W, W},
    {B, B, W, W, B, B, B, B, W, W, W, W, W},
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_T14 = { // T14
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, W, W, W, W, B, B, W, W, W, W, W},
    {B, B, B, W, W, B, B, B, W, W, W, W, W},
    {B, B, B, B, B, B, B, B, W, W, W, W, W},
    {B, B, B, B, B, B, B, B, W, W, W, W, W},
    {B, B, W, B, B, W, B, B, W, W, W, W, W},
    {B, B, W, W, W, W, B, B, W, W, W, W, W},
    {B, B, W, W, W, W, B, B, W, W, W, W, W},
    {B, B, W, W, W, W, B, B, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_T15 = { // T15
    {W, W, W, W, W, W, W, W, W, W, B, B, G},
    {W, W, W, W, W, W, W, W, W, W, B, B, G},
    {W, W, W, W, W, W, W, W, W, W, B, B, G},
    {W, W, W, W, W, W, W, W, W, W, B, B, G},
    {W, W, W, W, W, W, W, W, W, W, B, B, B},
    {W, W, W, W, W, W, W, W, W, W, B, B, B},
    {W, W, W, W, W, W, W, W, W, W, B, B, W},
    {W, W, W, W, W, W, W, W, W, W, B, B, W},
    {W, W, W, W, W, W, W, W, W, W, B, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_T16 = { // T16
    {G, B, B, W, W, W, W, W, W, W, B, B, G},
    {G, B, W, W, W, W, W, W, W, W, B, B, G},
    {B, B, W, W, W, W, W, W, W, W, B, B, G},
    {B, W, W, W, W, W, W, W, W, W, B, B, G},
    {B, W, W, W, W, W, W, W, W, W, B, B, G},
    {W, W, W, W, W, W, W, W, W, W, B, B, G},
    {W, W, W, W, W, W, W, W, W, W, B, B, G},
    {W, W, W, W, W, W, W, W, W, W, B, B, G},
    {W, W, W, W, W, W, W, W, W, W, B, B, G},
    {W, W, W, W, W, W, W, W, W, W, B, B, G},
    {W, W, W, W, W, W, W, W, W, W, B, B, G},
    {W, W, W, W, W, W, W, W, W, W, B, B, G},
    {W, W, W, W, W, W, W, W, W, W, B, B, D},
};

const cell_t Cell_T17 = { // T17
    {G, G, G, G, G, G, G, B, B, B, W, W, W},
    {G, G, G, G, G, G, G, B, B, B, W, W, W},
    {G, G, G, G, G, G, G, B, B, B, W, W, W},
    {G, G, G, G, G, G, G, B, B, B, W, W, W},
    {G, G, G, G, G, G, G, B, B, B, W, W, W},
    {G, G, G, G, G, G, G, B, B, B, W, W, W},
    {G, G, G, G, G, G, G, B, B, B, W, W, W},
    {G, G, G, G, G, G, G, B, B, B, W, W, W},
    {G, G, G, G, G, G, G, B, B, B, W, W, W},
    {G, G, G, G, G, G, G, B, B, B, W, W, W},
    {G, G, G, G, G, G, G, B, B, B, W, W, W},
    {G, G, G, G, G, G, G, B, B, B, W, W, W},
    {D, D, D, D, D, D, D, B, B, B, W, W, W},
};

const cell_t Cell_T18 = { // T18
    {W, W, W, B, B, G, G, B, B, B, W, W, W},
    {W, W, W, W, B, B, G, B, B, B, W, W, W},
    {W, W, W, W, B, B, G, B, B, B, W, W, W},
    {W, W, W, W, W, B, B, B, B, B, W, W, W},
    {W, W, W, W, W, B, B, B, B, B, W, W, W},
    {W, W, W, W, W, W, B, B, B, B, W, W, W},
    {W, W, W, W, W, W, W, B, B, B, W, W, W},
    {W, W, W, W, W, W, W, B, B, B, W, W, W},
    {W, W, W, W, W, W, W, W, B, B, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_T19 = { // T19
    {B, B, G, G, G, G, G, G, G, G, B, B, B},
    {B, B, G, G, G, G, G, G, G, G, B, B, B},
    {B, B, G, G, G, G, G, G, G, G, B, B, B},
    {B, B, G, G, G, G, G, G, G, G, B, B, B},
    {B, B, G, G, G, G, G, G, G, G, B, B, B},
    {B, B, G, G, G, G, G, G, G, G, B, B, B},
    {B, B, G, G, G, G, G, G, G, G, B, B, B},
    {B, B, G, G, G, G, G, G, G, G, B, B, B},
    {B, B, G, G, G, G, G, G, G, G, B, B, B},
    {B, B, G, G, G, G, G, G, G, G, B, B, B},
    {B, B, G, G, G, G, G, G, G, G, B, B, B},
    {B, B, G, G, G, G, G, G, G, G, B, B, B},
    {B, B, D, D, D, D, D, D, D, D, B, B, B},
};

const cell_t Cell_T20 = { // T20
    {W, W, W, W, W, W, W, W, W, W, W, W, B},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, B, B},
    {W, W, W, W, W, W, W, W, W, W, B, B, B},
    {W, W, W, W, W, W, W, W, W, B, B, B, B},
    {W, W, W, W, W, W, W, W, B, B, B, B, B},
    {W, W, W, W, W, W, W, B, B, G, B, B, B},
    {W, W, W, W, W, W, B, B, G, G, B, B, B},
    {W, W, W, W, W, B, B, G, G, G, B, B, B},
    {W, W, W, W, B, B, G, G, G, G, B, B, B},
    {W, W, W, B, B, G, G, G, G, G, B, B, B},
    {W, W, B, B, D, D, D, D, D, D, B, B, B},
};

const cell_t Cell_T21 = { // T21
    {B, G, G, G, B, B, B, W, W, W, B, B, G},
    {B, B, G, G, B, B, B, W, W, W, B, B, G},
    {W, B, B, G, B, B, B, W, W, W, B, B, G},
    {W, W, B, B, B, B, B, W, W, W, B, B, G},
    {W, W, W, B, B, B, B, W, W, W, B, B, B},
    {W, W, W, W, B, B, B, W, W, W, B, B, B},
    {W, W, W, W, W, B, B, W, W, W, B, B, W},
    {W, W, W, W, W, W, B, W, W, W, B, B, W},
    {W, W, W, W, W, W, W, W, W, W, B, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_T22 = { // T22
    {W, W, B, B, G, G, G, G, G, G, G, G, G},
    {W, W, B, B, G, G, G, G, G, G, G, G, G},
    {W, W, B, B, G, G, G, G, G, G, G, G, G},
    {W, W, B, B, G, G, G, G, G, G, G, G, G},
    {W, W, B, B, G, G, G, G, G, G, G, G, G},
    {W, W, B, B, G, G, G, G, G, G, G, G, G},
    {W, W, B, B, G, G, G, G, G, G, G, G, G},
    {W, W, B, B, G, G, G, G, G, G, G, G, G},
    {W, W, B, B, G, G, G, G, G, G, G, G, G},
    {W, W, B, B, G, G, G, G, G, G, G, G, G},
    {W, W, B, B, G, G, G, G, G, G, G, G, G},
    {W, W, B, B, G, G, G, G, G, G, G, G, B},
    {W, W, B, B, D, D, D, D, B, B, B, B, B},
};

const cell_t Cell_T23 = { // T23
    {G, G, B, B, B, W, W, W, W, W, W, B, B},
    {G, G, B, B, B, W, W, W, W, W, W, B, B},
    {G, G, B, B, B, W, W, W, W, W, W, B, B},
    {G, G, B, B, B, W, W, W, W, W, W, B, B},
    {G, G, B, B, B, W, W, W, W, W, W, B, B},
    {G, G, B, B, B, W, W, W, W, W, W, B, B},
    {G, G, B, B, B, W, W, W, W, W, W, B, B},
    {G, G, B, B, W, W, W, W, W, W, W, B, B},
    {G, G, B, B, W, W, W, W, W, W, W, B, B},
    {G, B, B, W, W, W, W, W, W, W, W, B, B},
    {B, B, B, W, W, W, W, W, W, W, W, B, B},
    {B, B, W, W, W, W, W, W, W, W, W, B, B},
    {B, W, W, W, W, W, W, W, W, W, W, B, B},
};

const cell_t Cell_T24 = { // T24
    {G, G, G, G, G, G, G, G, B, B, B, W, W},
    {G, G, G, G, G, G, G, G, B, B, B, W, W},
    {G, G, G, G, G, G, G, G, B, B, B, W, W},
    {G, G, G, G, G, G, G, G, B, B, B, W, W},
    {G, G, G, G, G, G, G, G, B, B, B, W, W},
    {G, G, G, G, G, G, G, G, B, B, B, W, W},
    {G, G, G, G, G, G, G, G, B, B, B, W, W},
    {G, G, G, G, G, G, G, G, B, B, B, W, W},
    {G, G, G, G, G, G, G, G, B, B, B, W, W},
    {G, G, G, G, G, G, G, G, B, B, B, W, W},
    {G, G, G, G, G, G, G, G, B, B, B, W, W},
    {G, G, G, G, G, G, G, G, B, B, B, W, W},
    {D, D, D, D, D, D, D, D, B, B, B, W, W},
};

const cell_t Cell_T25 = { // T25
    {B, B, G, G, G, G, G, G, G, G, B, B, B},
    {B, B, G, G, G, G, G, G, G, G, G, B, B},
    {B, B, G, G, G, G, G, G, G, G, G, G, B},
    {B, B, B, G, G, G, G, G, G, G, G, G, B},
    {W, B, B, G, G, G, G, G, G, G, G, G, G},
    {W, B, B, G, G, G, G, G, G, G, G, G, G},
    {W, B, B, B, G, G, G, G, G, G, G, G, G},
    {W, W, B, B, G, G, G, G, G, G, G, G, G},
    {W, W, B, B, B, G, G, G, G, G, G, G, G},
    {W, W, W, B, B, G, G, G, G, G, G, G, G},
    {W, W, W, B, B, B, G, G, G, G, G, G, G},
    {W, W, W, W, B, B, B, G, G, G, G, G, G},
    {W, W, W, W, W, B, B, D, D, D, D, D, D},
};

const cell_t Cell_T26 = { // T26
    {W, W, W, W, B, B, G, G, G, G, G, G, B},
    {B, W, W, W, W, B, B, G, G, G, G, G, B},
    {B, W, W, W, W, W, B, B, G, G, G, G, B},
    {B, B, W, W, W, W, W, B, B, G, G, G, B},
    {B, B, B, W, W, W, W, W, B, B, G, G, B},
    {G, B, B, W, W, W, W, W, B, B, B, G, B},
    {G, B, B, B, W, W, W, W, W, B, B, B, B},
    {G, G, B, B, B, W, W, W, W, W, B, B, B},
    {G, G, G, B, B, B, W, W, W, W, W, B, B},
    {G, G, G, G, B, B, W, W, W, W, W, W, B},
    {G, G, G, G, G, B, B, W, W, W, W, W, B},
    {G, G, G, G, G, G, B, B, W, W, W, W, W},
    {D, D, D, D, D, D, B, B, B, W, W, W, W},
};

const cell_t Cell_T27 = { // T27
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
    {W, B, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_T28 = { // T28
    {W, W, W, W, W, W, W, W, W, W, B, B, D},
    {W, W, W, W, W, W, W, W, W, W, B, B, D},
    {W, W, W, W, W, W, W, W, W, W, B, B, D},
    {W, W, W, W, W, W, W, W, W, W, B, B, D},
    {W, W, W, W, W, W, W, W, W, W, B, B, D},
    {W, W, W, W, W, W, W, W, W, W, B, B, D},
    {W, W, W, W, W, W, W, W, W, W, B, B, D},
    {W, W, W, W, W, W, W, W, W, W, B, B, D},
    {W, W, W, W, W, W, W, W, W, W, B, B, D},
    {W, W, W, W, W, W, W, W, W, W, B, B, D},
    {W, W, W, W, W, W, W, W, W, W, B, B, D},
    {W, W, W, W, W, W, W, W, W, W, B, B, D},
    {W, W, W, W, W, W, W, W, W, W, B, B, B},
};

const cell_t Cell_T29 = { // T29
    {D, D, D, D, D, D, D, B, B, B, W, W, W},
    {D, D, D, D, D, D, D, B, B, B, W, W, W},
    {D, D, D, D, D, D, D, B, B, B, W, W, W},
    {D, D, D, D, D, D, D, B, B, B, W, W, W},
    {D, D, D, D, D, D, D, B, B, B, W, W, W},
    {D, D, D, D, D, D, D, B, B, B, W, W, W},
    {D, D, D, D, D, D, D, B, B, B, W, W, W},
    {D, D, D, D, D, D, D, B, B, B, W, W, W},
    {D, D, D, D, D, D, D, B, B, B, W, W, W},
    {D, D, D, D, D, D, D, B, B, B, W, W, W},
    {D, D, D, D, D, D, D, B, B, B, W, W, W},
    {D, D, D, D, D, D, D, B, B, B, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, W, W, W},
};

const cell_t Cell_T30 = { // T30
    {B, B, D, D, D, D, D, D, D, D, B, B, B},
    {B, B, D, D, D, D, D, D, D, D, B, B, B},
    {B, B, D, D, D, D, D, D, D, D, B, B, B},
    {B, B, D, D, D, D, D, D, D, D, B, B, B},
    {B, B, D, D, D, D, D, D, D, D, B, B, B},
    {B, B, D, D, D, D, D, D, D, D, B, B, B},
    {B, B, D, D, D, D, D, D, D, D, B, B, B},
    {B, B, D, D, D, D, D, D, D, D, B, B, B},
    {B, B, D, D, D, D, D, D, D, D, B, B, B},
    {B, B, D, D, D, D, D, D, D, D, B, B, B},
    {B, B, D, D, D, D, D, D, D, D, B, B, B},
    {B, B, D, D, D, D, D, D, D, D, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
};

const cell_t Cell_T31 = { // T31
    {W, B, B, D, D, D, D, D, D, D, B, B, B},
    {W, W, B, B, D, D, D, D, D, D, B, B, B},
    {W, W, W, B, B, D, D, D, D, D, B, B, B},
    {W, W, W, W, B, B, D, D, D, D, B, B, B},
    {W, W, W, W, W, B, B, D, D, D, B, B, B},
    {W, W, W, W, W, W, B, B, D, D, B, B, B},
    {W, W, W, W, W, W, W, B, B, D, B, B, B},
    {W, W, W, W, W, W, W, W, B, B, B, B, B},
    {W, W, W, W, W, W, W, W, W, B, B, B, B},
    {W, W, W, W, W, W, W, W, W, W, B, B, B},
    {W, W, W, W, W, W, W, W, W, W, W, B, B},
    {W, W, W, W, W, W, W, W, W, W, W, W, B},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_T32 = { // T32
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, B, W, W, W, W, W, W},
    {W, W, W, W, W, B, B, W, W, W, W, W, W},
    {W, W, W, W, B, B, B, W, W, W, W, W, W},
    {W, W, W, B, B, B, B, W, W, W, W, W, W},
    {W, W, B, B, B, B, B, W, W, W, W, W, W},
    {W, B, B, B, B, B, B, W, W, W, W, W, W},
};

const cell_t Cell_T33 = { // T33
    {W, W, B, B, D, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, W, W},
    {W, W, B, B, B, B, B, B, W, W, W, W, W},
    {W, W, B, B, B, W, W, W, W, W, W, W, W},
    {W, W, B, B, B, W, W, W, W, W, W, W, W},
    {W, W, B, B, B, B, W, W, W, W, W, W, W},
    {W, W, B, B, D, B, W, W, W, W, W, W, W},
    {W, W, B, B, D, B, B, W, W, W, W, W, W},
    {W, W, B, B, D, D, B, B, W, W, W, W, W},
    {W, W, B, B, D, D, D, B, B, W, W, W, W},
    {W, W, B, B, D, D, D, D, B, W, W, W, W},
    {W, W, B, B, D, D, D, D, B, B, W, W, W},
    {W, W, B, B, B, B, B, B, B, B, B, W, W},
};

const cell_t Cell_T34 = { // T34
    {W, W, W, W, W, W, W, W, W, W, W, B, B},
    {W, W, W, W, W, W, W, W, W, W, W, B, B},
    {W, W, W, W, W, W, W, W, W, W, W, B, B},
    {W, W, W, W, W, W, W, W, W, W, W, B, B},
    {W, W, W, W, W, W, W, W, W, W, W, B, B},
    {W, W, W, W, W, W, W, W, W, W, W, B, B},
    {W, W, W, W, W, W, W, W, W, W, W, B, B},
    {W, W, W, W, W, W, W, W, W, W, W, B, B},
    {W, W, W, W, W, W, W, W, W, W, W, B, B},
    {W, W, W, W, W, W, W, W, W, W, W, B, B},
    {W, W, W, W, W, W, W, W, W, W, W, B, B},
    {W, W, W, W, W, W, W, W, W, W, W, B, B},
    {W, W, W, W, W, W, W, W, W, W, W, B, B},
};

const cell_t Cell_T35 = { // T35
    {D, D, D, D, D, D, D, D, B, B, B, W, W},
    {D, D, D, D, D, D, D, D, B, B, B, W, W},
    {D, D, D, D, D, D, D, D, B, B, B, W, W},
    {D, D, D, D, D, D, D, D, B, B, B, W, W},
    {D, D, D, D, D, D, D, D, B, B, B, W, W},
    {D, D, D, D, D, D, D, D, B, B, B, W, W},
    {D, D, D, D, D, D, D, D, B, B, B, W, W},
    {D, D, D, D, D, D, D, D, B, B, B, W, W},
    {D, D, D, D, D, D, D, D, B, B, B, W, W},
    {D, D, D, D, D, D, D, D, B, B, B, W, W},
    {D, D, D, D, D, D, D, D, B, B, B, W, W},
    {B, B, B, B, B, B, B, B, B, B, B, W, W},
    {B, B, B, B, B, B, B, B, B, B, B, W, W},
};

const cell_t Cell_T36 = { // T36
    {W, W, W, W, W, B, B, B, D, D, D, D, D},
    {W, W, W, W, W, W, B, B, D, D, D, D, D},
    {W, W, B, W, W, W, W, B, B, D, D, D, D},
    {W, W, B, B, W, W, W, W, B, B, D, D, D},
    {W, W, B, B, W, W, W, W, B, B, B, D, D},
    {W, W, B, B, B, W, W, W, W, B, B, D, D},
    {W, W, B, B, B, B, W, W, W, W, B, B, D},
    {W, W, B, B, D, B, B, W, W, W, W, B, B},
    {W, W, B, B, D, B, B, W, W, W, W, B, B},
    {W, W, B, B, D, D, B, B, W, W, W, W, B},
    {W, W, B, B, D, D, B, B, B, W, W, W, W},
    {W, W, B, B, D, D, D, B, B, B, W, W, W},
    {W, W, B, B, B, B, B, B, B, B, W, W, W},
};

const cell_t Cell_T37 = { // T37
    {D, D, D, D, D, D, D, B, B, B, W, W, W},
    {D, D, D, D, D, D, D, B, B, B, W, W, W},
    {D, D, D, D, D, D, D, D, B, B, B, W, W},
    {D, D, D, D, D, D, D, D, D, B, B, B, W},
    {D, D, D, D, D, D, D, D, D, D, B, B, B},
    {D, D, D, D, D, D, D, D, D, D, D, B, B},
    {D, D, D, D, D, D, D, D, D, D, D, B, B},
    {D, D, D, D, D, D, D, D, D, D, D, D, B},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {B, D, D, D, D, D, D, D, D, D, D, D, D},
    {B, B, B, D, D, D, D, D, D, D, D, D, D},
    {B, B, B, B, D, D, D, D, D, D, D, D, D},
    {W, B, B, B, B, B, B, B, B, B, B, B, B},
};

const cell_t Cell_T38 = { // T38
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, B, W, W, W, W, W, W, W, W, W, W},
    {B, B, B, B, W, W, W, W, W, W, W, W, W},
    {B, B, B, B, W, W, W, W, W, W, W, W, W},
    {D, B, B, B, B, W, W, W, W, W, W, W, W},
    {B, B, B, B, B, W, W, W, W, W, W, W, W},
};

const cell_t Cell_T39 = { // T39
    {W, W, W, W, W, W, W, W, W, W, B, B, B},
    {W, W, W, W, W, W, W, W, W, W, B, B, B},
    {W, W, W, W, W, W, W, W, W, W, B, B, B},
    {W, W, W, W, W, W, W, W, W, W, B, B, B},
    {W, W, W, W, W, W, W, W, W, W, B, B, B},
    {W, W, W, W, W, W, W, W, W, W, B, B, B},
    {W, W, W, W, W, W, W, W, W, W, B, B, B},
    {W, W, W, W, W, W, W, W, W, W, B, B, B},
    {W, W, W, W, W, W, W, W, W, W, B, B, B},
    {W, W, W, W, W, W, W, W, W, W, B, B, B},
    {W, W, W, W, W, W, W, W, W, W, B, B, B},
    {W, W, W, W, W, W, W, W, W, W, B, B, B},
    {W, W, W, W, W, W, W, W, W, W, B, B, B},
};

const cell_t Cell_T40 = { // T40
    {B, B, B, B, B, B, B, B, B, B, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, W, W, W},
};

const cell_t Cell_T41 = { // T41
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, B},
    {W, W, W, W, W, W, W, W, W, W, W, B, B},
    {W, W, W, W, W, W, W, W, W, W, B, B, B},
    {W, W, W, W, W, W, W, W, W, B, B, B, B},
    {W, W, W, W, W, W, W, W, B, B, B, B, B},
    {W, W, W, W, W, W, W, B, B, B, B, B, B},
    {W, W, W, W, W, W, B, B, B, B, B, B, B},
    {W, W, W, W, W, B, B, B, B, B, B, B, B},
    {W, W, W, W, B, B, B, B, B, B, B, B, B},
    {W, W, W, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, B, B, B, B, B, B, B, B, B, B, B, B},
};

const cell_t Cell_T42 = { // T42
    {B, B, B, B, B, B, B, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, W, W, W, W, W, W},
};

const cell_t Cell_T43 = { // T43
    {W, W, B, B, B, B, B, B, B, B, B, B, W},
    {W, W, B, B, B, B, B, B, B, B, B, B, W},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
};

const cell_t Cell_T44 = { // T44
    {W, W, W, W, W, W, W, W, W, W, W, B, B},
    {W, W, W, W, W, W, W, W, W, W, W, B, B},
    {W, W, W, W, W, W, W, W, W, W, W, B, B},
    {B, W, W, W, W, W, W, W, W, W, W, B, B},
    {B, B, W, W, W, W, W, W, W, W, W, B, B},
    {B, B, B, W, W, W, W, W, W, W, W, B, B},
    {B, B, B, W, W, W, W, W, W, W, W, B, B},
    {B, B, B, B, W, W, W, W, W, W, W, B, B},
    {B, B, B, B, B, W, W, W, W, W, W, B, B},
    {B, B, B, B, B, B, W, W, W, W, W, B, B},
    {B, B, B, B, B, B, W, W, W, W, W, B, B},
    {B, B, B, B, B, B, B, W, W, W, W, B, B},
    {B, B, B, B, B, B, B, B, W, W, W, B, B},
};

const cell_t Cell_T45 = { // T45
    {B, B, B, B, B, B, B, B, B, B, B, W, W},
    {B, B, B, B, B, B, B, B, B, B, B, W, W},
    {B, B, B, B, B, B, B, B, B, B, B, W, W},
    {B, B, B, B, B, B, B, B, B, B, B, W, W},
    {B, B, B, B, B, B, B, B, B, B, B, W, W},
    {B, B, B, B, B, B, B, B, B, B, B, W, W},
    {B, B, B, B, B, B, B, B, B, B, B, W, W},
    {B, B, B, B, B, B, B, B, B, B, B, W, W},
    {B, B, B, B, B, B, B, B, B, B, B, W, W},
    {B, B, B, B, B, B, B, B, B, B, B, W, W},
    {B, B, B, B, B, B, B, B, B, B, B, W, W},
    {B, B, B, B, B, B, B, B, B, B, B, W, W},
    {B, B, B, B, B, B, B, B, B, B, B, W, W},
};

const cell_t Cell_T46 = { // T46
    {W, W, B, B, B, B, B, B, B, B, B, W, W},
    {W, W, B, B, B, B, B, B, B, B, B, B, W},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
};

const cell_t Cell_T47 = { // T47
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, W, B, B, B, B, B, B, B, B, B, B},
    {W, W, W, W, B, B, B, B, B, B, B, B, B},
    {B, W, W, W, W, B, B, B, B, B, B, B, B},
    {B, B, W, W, W, W, B, B, B, B, B, B, B},
    {B, B, B, W, W, W, B, B, B, B, B, B, B},
    {B, B, B, W, W, W, W, B, B, B, B, B, B},
    {B, B, B, B, W, W, W, B, B, B, B, B, B},
    {B, B, B, B, B, W, W, W, B, B, B, B, B},
    {B, B, B, B, B, B, W, W, W, B, B, B, B},
    {B, B, B, B, B, B, B, W, W, B, B, B, B},
    {B, B, B, B, B, B, B, W, B, B, B, B, B},
};

const cell_t Cell_T48 = { // T48
    {B, B, B, B, B, W, W, W, W, W, W, W, W},
    {B, B, B, B, B, W, W, W, W, W, W, W, W},
    {B, B, B, B, B, W, W, W, W, W, W, W, W},
    {B, B, B, B, B, W, W, W, W, W, W, W, W},
    {B, B, B, B, B, W, W, W, W, W, W, W, W},
    {B, B, B, B, B, W, W, W, W, W, W, W, W},
    {B, B, B, B, B, W, W, W, W, W, W, W, W},
    {B, B, B, B, B, W, W, W, W, W, W, W, W},
    {B, B, B, B, B, W, W, W, W, W, W, W, W},
    {B, B, B, B, W, W, W, W, W, W, W, W, W},
    {B, B, B, B, W, W, W, W, W, W, W, W, W},
    {B, B, B, W, W, W, W, W, W, W, W, W, W},
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_SKY = { // SKY
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
};

const cell_t Cell_ST1 = { // ST1
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, W, W, G, G, G, G, G, G},
    {G, G, G, G, G, W, W, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
};

const cell_t Cell_ST2 = { // ST2
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, W, W, W, G, G, G, G, G},
    {G, G, G, G, G, W, W, W, G, G, G, G, G},
    {G, G, G, G, G, W, W, W, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
};

const cell_t Cell_MN1 = { // MN1
    {G, G, G, G, G, G, G, G, G, W, W, W, W},
    {G, G, G, G, G, G, W, W, W, W, W, W, W},
    {G, G, G, G, G, W, W, W, W, W, W, W, W},
    {G, G, G, G, W, W, W, W, W, W, W, W, W},
    {G, G, G, W, W, W, W, W, W, W, W, W, W},
    {G, G, W, W, W, W, W, W, W, W, W, W, W},
    {G, W, W, W, W, W, W, W, W, W, W, W, W},
    {G, W, W, W, W, W, W, W, W, W, W, W, W},
    {G, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_MN2 = { // MN2
    {W, G, G, G, G, G, G, G, G, G, G, G, G},
    {W, W, W, W, G, G, G, G, G, G, G, G, G},
    {W, W, W, W, W, G, G, G, G, G, G, G, G},
    {W, W, W, W, W, W, G, G, G, G, G, G, G},
    {W, W, W, W, W, W, W, G, G, G, G, G, G},
    {W, W, W, W, W, W, W, W, G, G, G, G, G},
    {W, W, W, W, W, W, W, W, W, G, G, G, G},
    {W, W, W, W, W, W, W, W, W, G, G, G, G},
    {W, W, W, W, W, W, W, W, W, G, G, G, G},
    {W, W, W, W, W, W, W, W, W, W, G, G, G},
    {W, W, W, W, W, W, W, W, W, W, G, G, G},
    {W, W, W, W, W, W, W, W, W, W, G, G, G},
    {W, W, W, W, W, W, W, W, W, W, G, G, G},
};

const cell_t Cell_MN3 = { // MN3
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {G, W, W, W, W, W, W, W, W, W, W, W, W},
    {G, W, W, W, W, W, W, W, W, W, W, W, W},
    {G, W, W, W, W, W, W, W, W, W, W, W, W},
    {G, G, W, W, W, W, W, W, W, W, W, W, W},
    {G, G, G, W, W, W, W, W, W, W, W, W, W},
    {G, G, G, G, W, W, W, W, W, W, W, W, W},
    {G, G, G, G, G, W, W, W, W, W, W, W, W},
    {G, G, G, G, G, G, W, W, W, W, W, W, W},
    {G, G, G, G, G, G, G, G, G, W, W, W, W},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
};

const cell_t Cell_MN4 = { // MN4
    {W, W, W, W, W, W, W, W, W, W, G, G, G},
    {W, W, W, W, W, W, W, W, W, G, G, G, G},
    {W, W, W, W, W, W, W, W, W, G, G, G, G},
    {W, W, W, W, W, W, W, W, W, G, G, G, G},
    {W, W, W, W, W, W, W, W, G, G, G, G, G},
    {W, W, W, W, W, W, W, G, G, G, G, G, G},
    {W, W, W, W, W, W, G, G, G, G, G, G, G},
    {W, W, W, W, W, G, G, G, G, G, G, G, G},
    {W, W, W, W, G, G, G, G, G, G, G, G, G},
    {W, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
};

const cell_t Cell_MW1 = { // MW1
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {D, D, D, D, D, D, D, D, D, D, D, B, B},
    {D, D, D, D, D, D, D, D, D, D, B, B, W},
    {D, D, D, D, D, D, D, D, D, D, B, W, W},
    {G, G, G, G, G, G, G, G, G, B, B, W, W},
    {G, G, G, G, G, G, G, G, G, B, B, W, W},
    {D, D, D, D, D, D, D, D, B, B, W, W, W},
    {D, D, D, D, D, D, D, D, B, B, W, W, W},
    {G, G, G, G, G, G, G, G, B, B, W, W, W},
    {G, G, G, G, G, G, G, G, B, B, W, W, W},
    {G, G, G, G, G, G, G, G, G, B, W, W, G},
};

const cell_t Cell_MW2 = { // MW2
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, D, D, D, D, D, D, D, D, D, D, D},
    {W, B, B, D, D, D, D, D, D, D, D, D, D},
    {W, W, B, D, D, D, D, D, D, D, D, D, D},
    {W, W, B, B, G, G, G, G, G, G, G, G, G},
    {W, G, B, B, G, G, G, G, G, G, G, G, G},
    {W, G, G, B, B, D, D, D, D, D, D, D, D},
    {W, G, G, B, B, D, D, D, D, D, D, D, D},
    {G, G, G, B, B, G, G, G, G, G, G, G, G},
    {G, G, D, B, B, G, G, G, G, G, G, G, G},
    {G, G, D, B, G, G, G, G, G, G, G, G, G},
};

const cell_t Cell_MW3 = { // MW3
    {G, G, G, G, G, G, G, G, G, B, B, G, G},
    {G, G, G, G, G, G, G, G, G, G, B, G, G},
    {G, G, G, G, G, G, G, G, G, G, B, B, B},
    {G, G, G, G, G, G, G, G, G, G, G, B, B},
    {G, G, G, G, G, G, G, G, G, G, G, B, B},
    {G, G, G, G, G, G, G, G, G, G, G, B, B},
    {G, G, G, G, G, G, G, G, G, G, G, B, B},
    {G, G, G, G, G, G, G, G, G, G, G, B, B},
    {G, G, G, G, G, G, G, G, G, G, G, B, B},
    {G, G, G, G, G, G, G, G, G, G, G, B, B},
    {G, G, G, G, G, G, G, G, G, G, G, B, B},
    {G, G, G, G, G, G, G, G, G, G, G, B, B},
    {G, G, G, G, G, G, G, G, G, G, B, B, B},
};

const cell_t Cell_MW4 = { // MW4
    {G, D, B, B, G, G, G, G, G, G, G, G, G},
    {D, D, B, G, G, G, G, G, G, G, G, G, G},
    {B, B, B, G, G, G, G, G, G, G, G, G, G},
    {B, B, G, G, G, G, G, G, G, G, G, G, G},
    {B, B, G, G, G, G, G, G, G, G, G, G, G},
    {B, B, G, G, G, G, G, G, G, G, G, G, G},
    {B, B, G, G, G, G, G, G, G, G, G, G, G},
    {B, B, G, G, G, G, G, G, G, G, G, G, G},
    {B, B, G, G, G, G, G, G, G, G, G, G, G},
    {B, B, G, G, G, G, G, G, G, G, G, G, G},
    {B, B, G, G, G, G, G, G, G, G, G, G, G},
    {B, B, G, G, G, G, G, G, G, G, G, G, G},
    {B, B, B, G, G, G, G, G, G, G, G, G, G},
};

const cell_t Cell_MW5 = { // MW5
    {G, G, G, G, G, G, G, G, G, B, B, W, W},
    {G, G, G, G, G, G, G, G, G, B, B, W, W},
    {G, G, G, G, G, G, G, G, G, B, B, W, W},
    {G, G, G, G, G, G, G, G, G, B, B, W, W},
    {G, G, G, G, G, G, G, G, G, B, B, B, B},
    {G, G, G, G, G, G, G, G, B, B, W, D, D},
    {G, G, G, G, G, G, G, B, B, W, W, D, D},
    {G, G, G, G, G, G, B, B, W, W, D, D, D},
    {G, G, G, G, G, B, B, W, W, W, D, D, D},
    {G, G, G, G, B, B, W, W, W, D, D, D, G},
    {G, G, G, B, B, W, W, W, D, D, D, G, G},
    {G, G, B, B, W, W, W, D, D, D, G, G, G},
    {G, B, B, W, W, W, D, D, D, G, G, G, G},
};

const cell_t Cell_MW6 = { // MW6
    {D, D, B, B, G, G, G, G, G, G, G, G, G},
    {D, D, B, B, G, G, G, G, G, G, G, G, G},
    {D, D, B, B, G, G, G, G, G, G, G, G, G},
    {D, D, B, B, G, G, G, G, G, G, G, G, G},
    {B, B, B, B, G, G, G, G, G, G, G, G, G},
    {G, G, D, B, B, G, G, G, G, G, G, G, G},
    {G, G, D, B, B, B, G, G, G, G, G, G, G},
    {G, G, D, D, D, B, B, G, G, G, G, G, G},
    {G, G, D, G, G, D, B, B, G, G, G, G, G},
    {G, D, D, G, G, D, D, B, B, G, G, G, G},
    {D, D, D, G, G, D, D, D, B, B, G, G, G},
    {D, D, D, G, G, G, D, D, D, B, B, G, G},
    {D, D, D, G, G, G, G, D, D, D, B, B, G},
};

const cell_t Cell_MW7 = { // MW7
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, B},
    {G, G, G, G, G, G, G, G, G, G, G, B, B},
    {G, G, G, G, G, G, G, G, G, G, B, B, W},
    {G, G, G, G, G, G, G, G, G, B, B, W, W},
    {G, G, G, G, G, G, G, G, B, B, W, W, W},
    {G, G, G, G, G, G, G, B, B, W, W, W, W},
    {G, G, G, G, G, G, B, B, W, W, W, W, D},
    {G, G, G, G, G, B, B, W, W, W, W, D, D},
    {G, G, G, G, B, B, W, W, W, W, D, D, D},
    {G, G, G, B, B, W, W, W, W, D, D, D, D},
    {G, G, B, B, W, W, W, W, D, D, D, D, D},
    {G, G, B, B, W, W, W, D, D, D, D, D, D},
};

const cell_t Cell_MW8 = { // MW8
    {B, B, W, W, W, D, D, D, G, G, G, G, G},
    {B, W, W, W, D, D, D, D, G, G, G, G, D},
    {W, W, W, D, D, D, D, D, G, G, G, G, D},
    {W, W, W, D, D, D, D, G, G, G, G, G, D},
    {W, W, D, D, D, D, G, G, G, G, G, G, D},
    {W, D, D, D, D, G, G, G, G, G, G, D, D},
    {D, D, D, D, G, G, G, G, G, G, G, D, D},
    {D, D, D, G, G, G, G, G, G, G, D, D, D},
    {D, D, D, G, G, G, G, G, G, G, D, D, D},
    {D, D, D, G, G, G, G, G, G, D, D, D, D},
    {D, D, G, G, G, G, G, G, D, D, D, D, D},
    {D, D, G, G, G, G, G, G, D, D, D, D, D},
    {D, G, G, G, G, G, G, G, D, D, D, D, D},
};

const cell_t Cell_MW9 = { // MW9
    {D, D, D, G, G, G, G, D, G, D, D, B, B},
    {D, D, D, G, G, G, G, D, D, G, D, D, B},
    {D, D, D, G, G, G, G, D, D, G, G, D, D},
    {D, D, D, G, G, G, G, G, D, D, G, G, D},
    {D, D, D, G, G, G, G, G, D, D, G, G, D},
    {D, D, G, G, G, G, G, G, D, D, D, G, G},
    {D, D, G, G, G, G, G, G, D, D, D, D, G},
    {D, D, G, G, G, G, G, G, D, D, D, D, D},
    {D, D, G, G, G, G, G, G, D, D, D, D, D},
    {D, G, G, G, G, G, G, G, G, D, D, D, D},
    {D, G, G, G, G, G, G, G, G, G, D, D, D},
    {D, G, G, G, G, G, G, G, G, G, D, D, D},
    {D, G, G, G, G, G, G, G, G, G, D, D, D},
};

const cell_t Cell_M10 = { // M10
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {B, G, G, G, G, G, G, G, G, G, G, G, G},
    {B, B, G, G, G, G, G, G, G, G, G, G, G},
    {D, B, B, G, G, G, G, G, G, G, G, G, G},
    {D, D, B, B, G, G, G, G, G, G, G, G, G},
    {D, D, D, B, B, G, G, G, G, G, G, G, G},
    {G, D, D, D, B, B, G, G, G, G, G, G, G},
    {G, G, D, D, D, B, B, G, G, G, G, G, G},
    {D, G, G, D, D, D, B, B, G, G, G, G, G},
    {D, G, G, G, D, D, D, B, B, G, G, G, G},
    {D, D, G, G, G, D, D, D, B, B, G, G, G},
    {D, D, G, G, G, G, D, D, D, B, G, G, G},
    {D, D, D, G, G, G, G, D, D, B, B, G, G},
};

const cell_t Cell_M11 = { // M11
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, B},
    {G, G, G, G, G, G, G, G, G, G, G, B, B},
    {G, G, G, G, G, G, G, G, G, G, B, B, W},
    {G, G, G, G, G, G, G, G, G, G, B, W, W},
    {G, G, G, G, G, G, G, G, G, B, B, W, W},
    {G, G, G, G, G, G, G, G, G, B, B, W, W},
    {G, G, G, G, G, G, G, G, B, B, W, W, W},
    {G, G, G, G, G, G, G, G, B, B, W, W, W},
    {G, G, G, G, G, G, G, G, B, B, W, W, W},
    {G, G, G, G, G, G, G, G, B, B, W, W, W},
    {G, G, G, G, G, G, G, G, G, B, W, W, G},
};

const cell_t Cell_M12 = { // M12
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {B, G, G, G, G, G, G, G, G, G, G, G, G},
    {B, B, G, G, G, G, G, G, G, G, G, G, G},
    {W, B, B, G, G, G, G, G, G, G, G, G, G},
    {W, W, B, G, G, G, G, G, G, G, G, G, G},
    {W, W, B, B, G, G, G, G, G, G, G, G, G},
    {W, G, B, B, G, G, G, G, G, G, G, G, G},
    {W, G, G, B, B, G, G, G, G, G, G, G, G},
    {W, G, G, B, B, G, G, G, G, G, G, G, G},
    {G, G, G, B, B, G, G, G, G, G, G, G, G},
    {G, G, D, B, B, G, G, G, G, G, G, G, G},
    {G, G, D, B, G, G, G, G, G, G, G, G, G},
};

const cell_t Cell_M13 = { // M13
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, B},
    {G, G, G, G, G, G, G, G, G, G, G, G, B},
    {G, G, G, G, G, G, G, G, G, G, G, G, B},
    {G, G, G, G, G, G, G, G, G, G, G, G, B},
    {G, G, G, G, G, G, G, G, G, G, G, G, B},
    {G, G, G, G, G, G, G, G, G, G, G, G, B},
    {G, G, G, G, G, G, G, G, G, G, G, G, B},
    {G, G, G, G, G, G, G, G, G, G, G, G, B},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
};

const cell_t Cell_M14 = { // M14
    {G, B, B, W, W, W, W, D, D, D, D, D, D},
    {G, B, W, W, W, W, W, D, D, D, D, D, D},
    {B, B, W, W, W, W, D, D, D, D, D, D, D},
    {B, B, W, W, W, W, D, D, D, D, D, D, D},
    {B, W, W, W, W, D, D, D, D, D, D, D, D},
    {B, W, W, W, W, D, D, D, D, D, D, D, D},
    {B, W, W, W, W, D, D, D, D, D, D, D, D},
    {B, W, W, W, W, D, D, D, D, D, D, D, D},
    {B, W, W, W, W, D, D, D, D, D, D, D, D},
    {B, W, W, W, W, D, D, D, D, D, D, D, D},
    {B, W, W, W, W, D, D, D, D, D, D, D, D},
    {B, W, W, W, W, D, D, D, D, D, D, D, D},
    {B, B, W, W, W, D, D, D, D, D, D, D, D},
};

const cell_t Cell_M15 = { // M15
    {G, G, G, G, G, G, G, G, D, D, D, D, D},
    {G, G, G, G, G, G, G, G, D, D, D, D, D},
    {G, G, G, G, G, G, G, D, D, D, D, D, D},
    {G, G, G, G, G, G, G, D, D, D, D, D, D},
    {G, G, G, G, G, G, G, D, D, D, D, D, D},
    {G, G, G, G, G, G, G, D, D, D, D, D, D},
    {G, G, G, G, G, G, G, D, D, D, D, D, D},
    {G, G, G, G, G, G, G, D, D, D, D, D, D},
    {G, G, G, G, G, G, G, D, D, D, D, D, D},
    {G, G, G, G, G, G, G, D, D, D, D, D, D},
    {G, G, G, G, G, G, G, D, D, D, D, D, D},
    {G, G, G, G, G, G, G, G, D, D, D, D, D},
    {G, G, G, G, G, G, G, G, D, D, D, D, D},
};

const cell_t Cell_M16 = { // M16
    {D, G, G, G, G, G, G, G, G, G, D, D, D},
    {D, G, G, G, G, G, G, G, G, G, G, D, D},
    {D, G, G, G, G, G, G, G, G, G, G, D, D},
    {D, G, G, G, G, G, G, G, G, G, G, D, D},
    {D, D, G, G, G, G, G, G, G, G, G, D, D},
    {D, D, D, G, G, G, G, G, G, G, G, D, D},
    {D, D, D, G, G, G, G, G, G, G, G, G, D},
    {D, D, D, G, G, G, G, G, G, G, G, G, G},
    {D, D, D, D, G, G, G, G, G, G, G, G, G},
    {D, D, D, D, D, G, G, G, G, G, G, G, G},
    {D, D, D, D, D, G, G, G, G, G, G, G, G},
    {D, D, D, D, D, G, G, G, G, G, G, G, G},
    {D, D, D, D, D, G, G, G, G, G, G, G, G},
};

const cell_t Cell_M17 = { // M17
    {D, D, D, G, G, G, G, D, D, D, B, B, G},
    {D, D, D, D, G, G, G, G, D, D, B, B, G},
    {D, D, D, D, D, G, G, G, D, D, D, B, G},
    {D, D, D, D, D, G, G, G, D, D, D, B, B},
    {D, D, D, D, D, D, G, G, G, D, D, B, B},
    {D, D, D, D, D, D, G, G, G, G, D, B, B},
    {D, D, D, D, D, D, G, G, G, G, D, B, B},
    {D, D, D, D, D, D, G, G, G, G, D, B, B},
    {D, D, D, D, D, D, G, G, G, G, D, B, B},
    {D, D, D, D, D, D, G, G, G, G, D, B, B},
    {D, D, D, D, D, D, G, G, G, G, D, B, B},
    {D, D, D, D, D, D, G, G, G, D, D, B, B},
    {D, D, D, D, D, D, G, G, D, D, D, B, B},
};

const cell_t Cell_M18 = { // M18
    {D, G, G, G, G, G, G, G, D, D, D, D, D},
    {D, D, G, G, G, G, G, G, G, D, D, D, D},
    {D, D, G, G, G, G, G, G, G, G, D, D, D},
    {D, D, D, G, G, G, G, G, G, G, D, D, D},
    {D, D, D, D, G, G, G, G, G, G, D, D, D},
    {D, D, D, D, D, G, G, G, G, G, G, D, D},
    {D, D, D, D, D, G, G, G, G, G, G, G, G},
    {D, D, D, D, D, D, D, G, G, G, G, G, G},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
};

const cell_t Cell_M19 = { // M19
    {D, D, D, D, D, D, G, G, G, G, G, G, G},
    {D, D, D, D, D, D, G, G, G, G, G, G, G},
    {D, D, D, D, D, D, G, G, G, G, G, G, G},
    {D, D, D, D, D, D, G, G, G, G, G, G, D},
    {D, D, D, D, D, D, G, G, G, G, G, D, D},
    {D, D, D, D, D, D, G, G, G, G, G, D, D},
    {D, D, D, D, D, D, D, G, G, G, G, D, D},
    {D, D, D, D, D, D, D, G, G, G, G, D, D},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {G, G, D, D, D, D, D, B, B, D, D, B, B},
    {G, G, D, D, D, D, D, B, B, D, D, B, B},
    {G, G, D, D, D, D, D, B, B, D, D, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
};

const cell_t Cell_M20 = { // M20
    {D, D, D, D, D, G, G, G, D, D, D, B, G},
    {D, D, D, D, D, G, G, G, D, D, B, B, G},
    {D, D, D, D, D, G, G, D, D, D, B, B, G},
    {D, D, D, D, G, G, G, D, D, B, B, G, G},
    {D, D, D, G, G, G, G, D, D, B, G, G, G},
    {D, D, D, G, G, D, D, D, B, B, G, G, G},
    {D, D, G, G, G, D, D, B, B, B, G, G, G},
    {D, D, G, D, D, D, B, B, B, G, G, G, G},
    {B, B, B, B, B, B, B, B, G, G, G, G, G},
    {B, B, G, B, B, B, B, G, G, G, D, D, D},
    {B, B, G, B, B, B, G, G, G, G, D, D, D},
    {B, B, G, B, B, B, G, G, G, G, D, D, D},
    {B, B, B, B, B, B, D, D, D, D, D, D, D},
};

const cell_t Cell_M21 = { // M21
    {G, G, G, G, G, G, G, G, G, B, B, W, W},
    {G, G, G, G, G, G, G, G, G, B, B, W, W},
    {G, G, G, G, G, G, G, G, G, B, B, W, W},
    {G, G, D, D, G, G, G, G, G, B, B, W, W},
    {G, G, D, D, G, G, G, G, G, B, B, B, B},
    {D, D, D, D, D, D, G, G, B, B, W, D, D},
    {D, D, D, D, D, D, G, B, B, W, W, D, D},
    {G, G, D, D, G, G, B, B, W, W, D, D, D},
    {G, G, D, D, G, B, B, W, W, W, D, D, D},
    {G, G, D, D, B, B, W, W, W, D, D, D, G},
    {G, G, D, B, B, W, W, W, D, D, D, G, G},
    {G, G, B, B, W, W, W, D, D, D, G, G, G},
    {D, B, B, W, W, W, D, D, D, D, G, G, D},
};

const cell_t Cell_M22 = { // M22
    {D, D, B, B, G, G, G, G, G, G, G, G, G},
    {D, D, B, B, G, G, G, G, G, G, G, G, G},
    {D, D, B, B, G, G, G, G, G, G, G, G, G},
    {D, D, B, B, G, G, G, G, G, G, G, G, G},
    {B, B, B, B, G, G, G, G, G, G, G, G, G},
    {G, D, D, B, B, G, G, G, G, G, G, G, G},
    {G, D, D, D, B, B, G, G, G, G, G, G, G},
    {G, G, D, G, D, B, B, G, G, G, G, G, G},
    {G, G, D, G, D, D, B, B, G, G, G, G, G},
    {G, D, D, G, G, D, D, B, B, G, G, G, G},
    {G, D, D, G, G, D, D, D, B, B, G, G, G},
    {D, D, D, G, G, G, D, D, D, B, B, G, G},
    {D, D, D, G, G, G, G, D, D, D, B, B, G},
};

const cell_t Cell_BG1 = { // BG1
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, D, D, G, G, G, G, G, G},
    {G, G, G, G, G, D, D, G, G, G, G, G, G},
    {G, G, G, D, D, D, D, D, D, G, G, G, G},
    {G, G, G, D, D, D, D, D, D, G, G, G, G},
};

const cell_t Cell_BG2 = { // BG2
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, D, D, G, G, G},
    {G, G, G, G, G, G, G, G, D, D, G, G, G},
    {G, G, G, G, G, G, G, G, D, D, G, G, G},
    {G, G, G, G, G, G, G, G, D, D, G, G, G},
    {G, G, G, G, G, G, G, G, D, D, G, G, G},
    {G, G, G, G, G, G, G, G, D, D, G, G, G},
    {G, G, G, G, G, G, G, D, D, D, D, G, G},
    {G, G, G, G, G, G, G, D, D, D, D, G, G},
    {G, G, G, G, G, G, G, D, D, D, D, G, G},
    {G, G, G, G, G, G, G, D, D, D, D, G, G},
    {G, G, G, G, G, G, G, D, D, D, D, G, G},
};

const cell_t Cell_BG3 = { // BG3
    {G, D, D, D, D, D, D, D, D, D, D, G, G},
    {G, D, D, D, D, D, D, D, D, D, D, G, G},
    {D, D, D, D, D, D, D, D, D, D, D, D, G},
    {D, D, D, D, D, D, D, D, D, D, D, D, G},
    {D, D, D, D, D, D, D, D, D, D, D, D, G},
    {D, D, D, D, D, D, D, D, D, D, D, D, G},
    {G, G, D, D, D, D, D, D, D, D, G, G, G},
    {G, G, D, D, D, D, D, D, D, D, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, D, D, D, D, D, D, D, D, G, G, G},
    {G, G, D, D, D, D, D, D, D, D, G, G, G},
    {G, G, D, D, D, D, D, D, D, D, G, G, G},
};

const cell_t Cell_BG4 = { // BG4
    {G, G, G, G, G, G, G, D, D, D, D, G, G},
    {G, G, G, G, G, G, G, D, D, D, D, G, G},
    {G, G, G, G, G, D, D, D, D, D, D, D, D},
    {G, G, G, G, G, D, D, D, D, D, D, D, D},
    {G, G, G, G, G, D, D, D, D, D, D, D, D},
    {G, G, G, G, G, D, D, D, D, D, D, D, D},
    {G, G, G, G, G, D, D, D, D, D, D, D, D},
    {G, G, G, G, G, D, D, D, D, D, D, D, D},
    {G, G, G, G, G, D, D, D, D, D, D, D, D},
    {G, G, G, G, G, D, D, D, D, D, D, D, D},
    {G, G, D, D, D, D, D, D, D, D, D, D, D},
    {G, G, D, D, D, D, D, D, D, D, D, D, D},
    {G, G, D, D, D, D, D, D, D, D, D, D, D},
};

const cell_t Cell_BG5 = { // BG5
    {G, G, G, G, G, G, G, D, D, G, G, G, G},
    {G, G, G, G, G, G, G, D, D, G, G, G, G},
    {G, G, G, G, G, D, D, G, G, D, D, G, G},
    {G, G, G, G, G, D, D, G, G, D, D, G, G},
    {G, G, G, G, G, G, G, D, D, G, G, G, G},
    {G, G, G, G, G, G, G, D, D, G, G, G, G},
    {G, G, G, G, G, G, G, D, D, G, G, G, G},
    {G, G, G, G, G, G, D, D, D, D, G, G, G},
    {G, G, G, G, G, G, D, D, D, D, G, G, G},
    {G, G, G, G, G, G, D, D, D, D, G, G, G},
    {D, D, G, G, G, G, D, D, D, D, G, G, G},
    {D, D, G, G, G, G, D, D, D, D, G, G, G},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
};

const cell_t Cell_BG6 = { // BG6
    {B, B, W, W, W, D, D, D, D, D, D, D, D},
    {G, B, B, W, W, W, D, D, D, D, D, D, D},
    {G, B, B, W, W, W, W, D, D, D, D, D, D},
    {G, G, B, B, W, W, W, D, D, D, D, D, D},
    {G, G, G, B, W, W, W, W, D, D, D, D, D},
    {G, G, G, B, B, W, W, W, W, D, D, D, D},
    {G, G, G, G, B, W, W, W, W, W, W, D, D},
    {G, G, G, G, B, B, W, W, W, W, W, D, D},
    {G, D, D, G, G, B, B, B, B, B, B, B, B},
    {G, D, D, G, G, G, B, B, B, W, W, W, G},
    {D, D, D, D, D, D, G, B, B, W, W, W, G},
    {D, D, D, D, D, D, G, B, B, W, W, W, G},
    {D, D, D, D, D, D, D, B, B, B, B, B, B},
};

const cell_t Cell_ND1 = { // ND1
    {B, B, B, W, W, W, W, W, B, B, B, W, W},
    {B, B, B, W, W, W, W, W, B, B, B, W, W},
    {B, B, B, B, B, W, W, W, B, B, B, W, W},
    {B, B, B, B, B, W, W, W, B, B, B, W, W},
    {B, B, B, B, B, B, W, W, B, B, B, W, W},
    {B, B, B, W, B, B, W, W, B, B, B, W, W},
    {B, B, B, W, B, B, B, W, B, B, B, W, W},
    {B, B, B, W, W, B, B, W, B, B, B, W, W},
    {B, B, B, W, W, B, B, B, B, B, B, W, W},
    {B, B, B, W, W, W, B, B, B, B, B, W, W},
    {B, B, B, W, W, W, B, B, B, B, B, W, W},
    {B, B, B, W, W, W, W, W, B, B, B, W, W},
    {B, B, B, W, W, W, W, W, B, B, B, W, W},
};

const cell_t Cell_ND2 = { // ND2
    {B, B, B, W, W, W, W, W, W, W, W, W, W},
    {B, B, B, W, W, W, W, W, W, W, W, W, W},
    {B, B, B, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, B, W, W, B, B, B, W, W, B, B, B},
    {B, B, B, W, W, B, B, B, W, B, B, B, B},
    {B, B, B, W, W, B, B, B, B, B, W, B, B},
    {B, B, B, W, W, B, B, B, B, W, W, B, B},
    {B, B, B, W, W, B, B, B, W, W, W, B, B},
    {B, B, B, W, W, B, B, B, W, W, W, B, B},
    {B, B, B, W, W, B, B, B, W, W, W, B, B},
    {B, B, B, W, W, B, B, B, W, W, W, B, B},
};

const cell_t Cell_ND3 = { // ND3
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, B, B, B, W, W, W, W, W, W, W},
    {W, W, W, B, B, B, W, W, W, W, W, W, W},
    {W, B, B, B, B, B, B, B, W, W, W, W, W},
    {W, B, B, B, B, B, B, B, W, W, W, W, W},
    {W, W, W, B, B, B, W, W, W, W, B, B, B},
    {B, W, W, B, B, B, W, W, W, B, B, B, B},
    {B, W, W, B, B, B, W, W, B, B, B, B, W},
    {B, W, W, B, B, B, W, W, B, B, B, W, W},
    {B, W, W, B, B, B, W, W, B, B, B, B, B},
    {B, W, W, B, B, B, W, W, B, B, B, W, W},
    {B, W, W, B, B, B, W, W, W, B, B, B, B},
    {B, W, W, B, B, B, W, W, W, W, B, B, B},
};

const cell_t Cell_ND4 = { // ND4
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, B, B, W, W, W, B, B, B, W, W, B},
    {B, B, B, B, B, W, W, B, B, B, W, B, B},
    {W, W, B, B, B, W, W, B, B, B, B, B, W},
    {W, W, W, B, B, W, W, B, B, B, B, W, W},
    {B, B, B, B, W, W, W, B, B, B, W, W, W},
    {W, W, W, W, W, W, W, B, B, B, W, W, W},
    {B, B, B, B, B, W, W, B, B, B, W, W, W},
    {B, B, B, B, B, W, W, B, B, B, W, W, W},
};

const cell_t Cell_ND5 = { // ND5
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, B, B},
    {W, W, W, W, W, W, W, W, W, W, W, B, B},
    {W, W, W, W, W, W, W, W, W, W, W, B, B},
    {W, W, W, W, W, W, W, W, W, W, W, B, B},
    {B, B, W, W, W, W, W, B, B, B, W, B, B},
    {B, B, B, W, W, W, B, B, B, B, B, B, B},
    {B, B, B, W, W, B, B, B, B, W, W, B, B},
    {B, B, B, W, W, B, B, B, W, W, W, B, B},
    {B, B, B, W, W, B, B, B, W, W, W, B, B},
    {B, B, B, W, W, B, B, B, B, W, W, B, B},
    {B, B, B, W, W, W, B, B, B, B, B, B, B},
    {B, B, B, W, W, W, W, B, B, B, W, B, B},
};

const cell_t Cell_ND6 = { // ND6
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, W, W, W, W, B, B, B, B, B, B, W, W},
    {B, W, W, W, B, B, B, W, W, B, B, B, W},
    {B, W, W, B, B, B, W, W, W, W, B, B, B},
    {B, W, W, B, B, B, W, W, W, W, B, B, B},
    {B, W, W, B, B, B, W, W, W, W, B, B, B},
    {B, W, W, B, B, B, W, W, W, W, B, B, B},
    {B, W, W, W, B, B, B, W, W, B, B, B, W},
    {B, W, W, W, W, B, B, B, B, B, B, W, W},
};

const cell_t Cell_MBG = { // MBG
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, B, B, G, G, G, G, G, G, G, G, G},
    {G, G, B, B, G, G, G, G, G, G, B, B, G},
    {G, G, G, G, G, G, G, G, G, G, B, B, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, B, B, G, G, G, G, G, G},
    {G, G, G, G, G, B, B, G, G, G, G, G, G},
    {B, B, G, G, G, G, G, G, G, G, G, G, G},
    {B, B, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, B, B, G},
    {G, G, G, G, G, G, G, G, G, G, B, B, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
};

const cell_t Cell_MB1 = { // MB1
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, B, B, B, B, B, B, B, B, B, B},
    {W, W, W, B, B, B, B, B, B, B, B, B, B},
    {W, W, W, B, B, B, B, B, B, B, B, B, B},
    {W, W, W, B, B, B, W, W, W, W, W, W, W},
    {W, W, W, B, B, B, W, W, W, W, W, W, W},
    {W, W, W, B, B, B, W, W, W, W, W, W, W},
    {W, W, W, B, B, B, W, W, W, W, W, W, W},
    {W, W, W, B, B, B, W, W, W, W, B, B, G},
    {W, W, W, B, B, B, W, W, W, W, B, B, G},
    {W, W, W, B, B, B, W, W, W, W, G, G, G},
};

const cell_t Cell_MB2 = { // MB2
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {G, G, G, G, G, G, G, G, G, G, B, B, G},
    {G, G, G, B, B, G, G, G, G, G, B, B, G},
    {G, G, G, B, B, G, G, G, G, G, G, G, G},
};

const cell_t Cell_MB3 = { // MB3
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, W, W, W},
    {W, W, W, W, W, W, B, B, B, B, W, W, W},
    {W, W, W, W, W, W, B, B, B, B, W, W, W},
    {W, W, W, W, W, W, B, B, B, B, W, W, W},
    {W, W, W, W, W, W, B, B, B, B, W, W, W},
    {G, G, G, W, W, W, B, B, B, B, W, W, W},
    {G, G, G, W, W, W, B, B, B, B, W, W, W},
    {G, G, G, W, W, W, B, B, B, B, W, W, W},
};

const cell_t Cell_MB4 = { // MB4
    {W, W, W, B, B, B, W, W, W, W, G, G, G},
    {W, W, W, B, B, B, W, W, W, W, G, G, G},
    {W, W, W, B, B, B, W, W, W, W, G, G, G},
    {W, W, W, B, B, B, W, W, W, W, G, G, G},
    {W, W, W, B, B, B, W, W, W, W, G, G, G},
    {W, W, W, B, B, B, W, W, W, W, G, G, G},
    {W, W, W, B, B, B, W, W, W, W, G, G, G},
    {W, W, W, B, B, B, W, W, W, W, G, G, G},
    {W, W, W, B, B, B, W, W, W, W, G, G, G},
    {W, W, W, B, B, B, W, W, W, W, G, G, G},
    {W, W, W, B, B, B, W, W, W, W, B, B, G},
    {W, W, W, B, B, B, W, W, W, W, B, B, G},
    {W, W, W, B, B, B, W, W, W, W, G, G, G},
};

const cell_t Cell_MB5 = { // MB5
    {G, G, G, W, W, W, B, B, B, B, W, W, W},
    {G, B, B, W, W, W, B, B, B, B, W, W, W},
    {G, B, B, W, W, W, B, B, B, B, W, W, W},
    {G, G, G, W, W, W, B, B, B, B, W, W, W},
    {G, G, G, W, W, W, B, B, B, B, W, W, W},
    {G, G, G, W, W, W, B, B, B, B, W, W, W},
    {G, G, G, W, W, W, B, B, B, B, W, W, W},
    {G, G, G, W, W, W, B, B, B, B, W, W, W},
    {B, B, G, W, W, W, B, B, B, B, W, W, W},
    {B, B, G, W, W, W, B, B, B, B, W, W, W},
    {G, G, G, W, W, W, B, B, B, B, W, W, W},
    {G, G, G, W, W, W, B, B, B, B, W, W, W},
    {G, G, G, W, W, W, B, B, B, B, W, W, W},
};

const cell_t Cell_MB6 = { // MB6
    {W, W, W, B, B, B, W, W, W, W, G, G, G},
    {W, W, W, B, B, B, W, W, W, W, G, G, G},
    {W, W, W, B, B, B, W, W, W, W, G, G, G},
    {W, W, W, B, B, B, W, W, W, W, W, W, W},
    {W, W, W, B, B, B, W, W, W, W, W, W, W},
    {W, W, W, B, B, B, W, W, W, W, W, W, W},
    {W, W, W, B, B, B, B, B, B, B, B, B, B},
    {W, W, W, B, B, B, B, B, B, B, B, B, B},
    {W, W, W, B, B, B, B, B, B, B, B, B, B},
    {W, W, W, B, B, B, B, B, B, B, B, B, B},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_MB7 = { // MB7
    {G, G, G, G, G, G, G, G, B, B, G, G, G},
    {G, G, B, B, G, G, G, G, B, B, G, G, G},
    {G, G, B, B, G, G, G, G, G, G, G, G, G},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_MB8 = { // MB8
    {G, G, G, W, W, W, B, B, B, B, W, W, W},
    {G, B, B, W, W, W, B, B, B, B, W, W, W},
    {G, B, B, W, W, W, B, B, B, B, W, W, W},
    {W, W, W, W, W, W, B, B, B, B, W, W, W},
    {W, W, W, W, W, W, B, B, B, B, W, W, W},
    {W, W, W, W, W, W, B, B, B, B, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_RB1 = { // RB1
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, B, B, G},
    {G, G, B, B, G, G, G, G, G, G, B, B, G},
    {G, G, B, B, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, B, B, G, G, G, G, G},
    {G, G, G, G, G, G, B, B, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, B, B},
    {G, G, G, G, G, G, G, G, G, G, B, B, B},
    {G, G, B, B, G, G, G, G, G, B, B, B, B},
    {G, G, B, B, G, G, G, G, B, B, B, B, B},
    {G, G, G, G, G, G, G, G, B, B, B, B, W},
};

const cell_t Cell_RB2 = { // RB2
    {G, G, G, G, G, G, G, G, B, B, G, G, G},
    {G, G, B, B, G, G, G, G, B, B, G, G, G},
    {G, G, B, B, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, B, B, G, G},
    {G, G, G, G, G, G, G, G, G, B, B, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_RB3 = { // RB3
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, B, B, G, G, G, G, G, G, G, G, G},
    {G, G, B, B, G, G, G, G, G, G, B, B, G},
    {G, G, G, G, G, G, G, G, G, G, B, B, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, B, B, G, G, G, G, G, G},
    {G, G, G, G, G, B, B, G, G, G, G, G, G},
    {B, B, G, G, G, G, G, G, G, G, G, G, G},
    {B, B, B, G, G, G, G, G, G, G, G, G, G},
    {B, B, B, B, G, G, G, G, G, G, B, B, G},
    {B, B, B, B, B, G, G, G, G, G, B, B, G},
    {W, B, B, B, B, G, G, G, G, G, G, G, G},
};

const cell_t Cell_RB4 = { // RB4
    {G, G, G, G, G, G, G, G, B, B, B, W, W},
    {G, G, G, G, G, G, G, G, B, B, B, W, W},
    {G, G, B, B, G, G, G, G, B, B, B, W, W},
    {G, G, B, B, G, G, G, G, B, B, B, W, W},
    {G, G, G, G, G, G, G, G, B, B, B, W, W},
    {G, G, G, G, G, G, G, G, B, B, B, W, W},
    {G, G, G, G, G, B, B, G, B, B, B, W, W},
    {G, G, G, G, G, B, B, G, B, B, B, W, W},
    {B, B, G, G, G, G, G, G, B, B, B, W, W},
    {B, B, G, G, G, G, G, G, B, B, B, W, W},
    {G, G, G, G, G, G, G, G, B, B, B, W, W},
    {G, G, G, G, G, G, G, G, B, B, B, W, W},
    {G, G, G, G, G, G, G, G, B, B, B, W, W},
};

const cell_t Cell_RB5 = { // RB5
    {W, W, B, B, B, G, G, G, B, B, G, G, G},
    {W, W, B, B, B, G, G, G, B, B, G, G, G},
    {W, W, B, B, B, G, G, G, G, G, G, G, G},
    {W, W, B, B, B, G, G, G, G, G, B, B, G},
    {W, W, B, B, B, G, G, G, G, G, B, B, G},
    {W, W, B, B, B, G, G, G, G, G, G, G, G},
    {W, W, B, B, B, G, G, G, G, G, G, G, G},
    {W, W, B, B, B, G, G, G, G, G, G, G, G},
    {W, W, B, B, B, G, B, B, G, G, G, G, G},
    {W, W, B, B, B, G, B, B, G, G, G, G, G},
    {W, W, B, B, B, G, G, G, G, G, B, B, G},
    {W, W, B, B, B, G, G, G, G, G, B, B, G},
    {W, W, B, B, B, G, G, G, G, G, G, G, G},
};

const cell_t Cell_RB6 = { // RB6
    {G, G, G, G, G, G, G, G, B, B, B, B, W},
    {G, G, G, G, G, G, G, G, B, B, B, B, B},
    {G, G, G, G, G, B, B, G, G, B, B, B, B},
    {G, G, G, G, G, B, B, G, G, G, B, B, B},
    {G, G, G, G, G, G, G, G, G, G, G, B, B},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, B, B, G, G, G, G, G, G, G, G, G},
    {G, G, B, B, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_RB7 = { // RB7
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, B, B, G, G},
    {G, G, G, G, G, G, G, G, G, B, B, G, G},
    {G, G, G, B, B, G, G, G, G, G, G, G, G},
    {G, G, G, B, B, G, G, G, G, G, G, G, G},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_RB8 = { // RB8
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, B, B, G, G},
    {G, G, G, G, G, G, G, G, G, B, B, G, G},
    {G, G, G, B, B, G, G, G, G, G, G, G, G},
    {G, G, G, B, B, G, G, G, G, G, G, G, G},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_RB9 = { // RB9
    {W, B, B, B, B, G, G, G, G, G, G, G, G},
    {B, B, B, B, B, G, G, G, G, G, G, G, G},
    {B, B, B, B, G, G, B, B, G, G, G, G, G},
    {B, B, B, G, G, G, B, B, G, G, G, G, G},
    {B, B, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, B, B, G},
    {G, G, G, G, G, G, G, G, G, G, B, B, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_R10 = { // R10
    {G, G, G, G, G, G, G, G, B, B, B, B, W},
    {G, G, G, G, G, G, G, G, B, B, B, B, B},
    {G, G, G, G, G, B, B, G, G, B, B, B, B},
    {G, G, G, G, G, B, B, G, G, G, B, B, B},
    {G, G, G, G, G, G, G, G, G, G, G, B, B},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, B, B, G, G, G, G, G, G, G, G, G},
    {G, G, B, B, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, W, W, W, W, B, B, W, W, W, W, W},
};

const cell_t Cell_R11 = { // R11
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, B, B, G, G},
    {G, G, G, G, G, G, G, G, G, B, B, G, G},
    {G, G, G, B, B, G, G, G, G, G, G, G, G},
    {G, G, G, B, B, G, G, G, G, G, G, G, G},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, W, W, W, W, B, B, W, W, W, W, W},
};

const cell_t Cell_R12 = { // R12
    {W, B, B, B, B, G, G, G, G, G, G, G, G},
    {B, B, B, B, B, G, G, G, G, G, G, G, G},
    {B, B, B, B, G, G, B, B, G, G, G, G, G},
    {B, B, B, G, G, G, B, B, G, G, G, G, G},
    {B, B, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, B, B, G},
    {G, G, G, G, G, G, G, G, G, G, B, B, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, W, W, W, W, B, B, W, W, W, W, W},
};

const cell_t Cell_SB1 = { // SB1
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, B, B, G},
    {G, G, B, B, G, G, G, G, G, G, B, B, G},
    {G, G, B, B, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, B, B, G, G, G, G, G},
    {G, G, G, G, G, G, B, B, G, G, G, G, G},
    {B, B, G, G, G, G, G, G, G, G, G, G, G},
    {B, B, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, B, B, B, B, B, B, B, B},
    {G, G, G, G, G, B, B, B, B, B, B, B, B},
    {G, G, G, G, G, B, B, W, W, W, W, W, W},
};

const cell_t Cell_SB2 = { // SB2
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, B, B, G},
    {G, G, G, B, B, G, G, G, G, G, B, B, G},
    {G, G, G, B, B, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, B, B, G, G, G},
    {G, G, G, G, G, G, G, G, B, B, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_SB3 = { // SB3
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, B, B, G},
    {G, G, B, B, G, G, G, G, G, G, B, B, G},
    {G, G, B, B, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, B, B, G},
    {G, G, G, G, G, G, G, G, G, G, B, B, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {B, B, B, B, B, B, B, B, G, G, G, G, G},
    {B, B, B, B, B, B, B, B, G, G, G, G, G},
    {W, W, W, W, W, W, B, B, G, G, G, G, G},
};

const cell_t Cell_SB4 = { // SB4
    {G, G, G, G, G, B, B, W, W, W, W, W, W},
    {G, G, G, G, G, B, B, W, W, W, W, W, W},
    {G, G, G, G, G, B, B, W, W, W, W, W, W},
    {G, G, G, G, G, B, B, W, W, W, W, W, W},
    {G, G, G, G, G, B, B, W, W, W, W, W, W},
    {G, G, B, B, G, B, B, W, W, W, W, W, W},
    {G, G, B, B, G, B, B, W, W, W, W, W, W},
    {G, G, G, G, G, B, B, W, W, W, W, W, W},
    {G, G, G, G, G, B, B, W, W, W, W, W, W},
    {G, G, G, G, G, B, B, W, W, W, W, W, W},
    {G, G, G, G, G, B, B, W, W, W, W, W, W},
    {G, G, G, G, G, B, B, W, W, W, W, W, W},
    {G, G, G, G, G, B, B, W, W, W, W, W, W},
};

const cell_t Cell_SB5 = { // SB5
    {W, W, W, W, W, W, B, B, G, G, G, G, G},
    {W, W, W, W, W, W, B, B, G, G, G, G, G},
    {W, W, W, W, W, W, B, B, G, G, B, B, G},
    {W, W, W, W, W, W, B, B, G, G, B, B, G},
    {W, W, W, W, W, W, B, B, G, G, G, G, G},
    {W, W, W, W, W, W, B, B, G, G, G, G, G},
    {W, W, W, W, W, W, B, B, G, G, G, G, G},
    {W, W, W, W, W, W, B, B, G, G, G, G, G},
    {W, W, W, W, W, W, B, B, G, G, G, G, G},
    {W, W, W, W, W, W, B, B, G, G, G, G, G},
    {W, W, W, W, W, W, B, B, G, G, G, B, B},
    {W, W, W, W, W, W, B, B, G, G, G, B, B},
    {W, W, W, W, W, W, B, B, G, G, G, G, G},
};

const cell_t Cell_SB6 = { // SB6
    {G, G, G, G, G, B, B, W, W, W, W, W, W},
    {G, G, G, G, G, B, B, B, B, B, B, B, B},
    {G, G, G, G, G, B, B, B, B, B, B, B, B},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, B, B, G, G, G, G, G, G, G, G, G},
    {G, G, B, B, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, B, B, G},
    {G, G, G, G, G, G, G, G, G, G, B, B, G},
    {G, G, B, B, G, G, G, G, G, G, G, G, G},
    {G, G, B, B, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
};

const cell_t Cell_SB7 = { // SB7
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, B, B, G},
    {G, G, G, G, G, G, G, G, G, G, B, B, G},
    {G, G, G, B, B, G, G, G, G, G, G, G, G},
    {G, G, G, B, B, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, B, B, G, G, G},
    {G, G, G, G, G, G, G, G, B, B, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
};

const cell_t Cell_SB8 = { // SB8
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, B, B, G},
    {G, G, G, G, G, G, G, G, G, G, B, B, G},
    {G, G, G, B, B, G, G, G, G, G, G, G, G},
    {G, G, G, B, B, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
};

const cell_t Cell_SB9 = { // SB9
    {W, W, W, W, W, W, B, B, G, G, G, G, G},
    {B, B, B, B, B, B, B, B, G, G, G, G, G},
    {B, B, B, B, B, B, B, B, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, B, B, G},
    {G, G, G, G, G, G, G, G, G, G, B, B, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, B, B, G, G, G, G, G, G, G, G, G},
    {G, G, B, B, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, B, B, G},
    {G, G, G, G, G, G, G, G, G, G, B, B, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
};

const cell_t Cell_S10 = { // S10
    {W, W, W, W, W, W, B, B, W, W, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {G, G, G, G, G, G, G, G, G, G, B, B, G},
    {G, G, G, G, G, G, G, G, G, G, B, B, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, B, B, G, G, G, G, G, G, G, G},
    {G, G, G, B, B, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, B, B, G},
    {G, G, G, G, G, G, G, G, G, G, B, B, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
};

const cell_t Cell_S11 = { // S11
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, B, B, G},
    {G, G, G, B, B, G, G, G, G, G, B, B, G},
    {G, G, G, B, B, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, B, B, G, G, G},
    {G, G, G, G, G, G, G, G, B, B, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, W, W, W, W, B, B, W, W, W, W, W},
};

const cell_t Cell_GB1 = { // GB1
    {G, G, G, G, G, B, B, W, W, W, W, W, W},
    {G, G, G, G, G, B, B, B, B, B, B, B, B},
    {G, G, G, G, G, B, B, B, B, B, B, B, B},
    {G, G, G, G, G, B, B, D, D, D, D, D, D},
    {G, G, G, G, G, B, B, D, D, D, D, D, D},
    {G, G, G, G, G, B, B, D, D, D, D, D, D},
    {G, G, G, G, G, B, B, D, D, D, D, D, D},
    {G, G, G, G, G, B, B, D, D, D, D, D, D},
    {G, G, G, G, G, B, B, D, D, D, D, D, D},
    {G, G, G, G, G, B, B, D, D, D, D, D, D},
    {G, G, B, B, G, B, B, B, B, B, B, B, B},
    {G, G, B, B, G, B, B, B, B, B, B, B, B},
    {G, G, G, G, G, B, B, W, W, W, W, W, W},
};

const cell_t Cell_GB2 = { // GB2
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_GB3 = { // GB3
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_GB4 = { // GB4
    {W, W, W, W, W, W, B, B, G, G, G, G, G},
    {B, B, B, B, B, B, B, B, G, G, G, G, G},
    {B, B, B, B, B, B, B, B, G, G, G, G, G},
    {D, D, D, D, D, D, B, B, G, G, G, G, G},
    {D, D, D, D, D, D, B, B, G, G, G, G, G},
    {D, D, D, D, D, D, B, B, G, G, G, G, G},
    {D, D, D, D, D, D, B, B, G, G, G, G, G},
    {D, D, D, D, D, D, B, B, G, G, G, G, G},
    {D, D, D, D, D, D, B, B, G, G, G, G, G},
    {D, D, D, D, D, D, B, B, G, G, B, B, G},
    {B, B, B, B, B, B, B, B, G, G, B, B, G},
    {B, B, B, B, B, B, B, B, G, G, G, G, G},
    {W, W, W, W, W, W, B, B, G, G, G, G, G},
};

const cell_t Cell_GB5 = { // GB5
    {W, W, W, W, W, W, B, B, W, W, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, W, W, W, W, B, B, W, W, W, W, W},
};

const cell_t Cell_TI1 = { // TI1
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, G, D, D, G, G, G, D, D, G, G, G},
    {B, B, G, D, D, G, G, G, D, D, G, G, G},
    {B, B, G, G, G, G, G, G, G, G, G, G, G},
    {B, B, D, D, G, G, D, D, G, G, D, D, G},
    {B, B, D, D, G, G, D, D, G, G, D, D, G},
    {B, B, G, G, G, G, G, G, G, G, G, G, G},
    {B, B, G, D, D, G, G, G, G, D, D, G, G},
    {B, B, G, D, D, G, G, G, G, D, D, G, G},
    {B, B, G, G, G, G, D, D, G, G, G, G, G},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
};

const cell_t Cell_TI2 = { // TI2
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {D, D, G, D, D, G, D, D, G, G, G, G, G},
    {D, D, G, D, D, G, D, D, G, G, D, D, G},
    {G, G, G, G, G, G, G, G, G, G, D, D, G},
    {G, G, G, D, D, G, G, G, G, G, G, G, G},
    {D, D, G, D, D, G, G, G, D, D, G, G, G},
    {D, D, G, G, G, G, G, G, D, D, G, G, G},
    {G, G, G, G, G, D, D, G, G, G, G, D, D},
    {G, G, D, D, G, D, D, G, D, D, G, D, D},
    {G, G, D, D, G, G, G, G, D, D, G, G, G},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
};

const cell_t Cell_TI3 = { // TI3
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {D, D, G, G, G, G, D, D, G, G, G, B, B},
    {D, D, G, D, D, G, D, D, G, G, G, B, B},
    {G, G, G, D, D, G, G, G, G, G, G, B, B},
    {G, G, G, G, G, G, G, G, D, D, G, B, B},
    {G, D, D, G, G, D, D, G, D, D, G, B, B},
    {G, D, D, G, G, D, D, G, G, G, G, B, B},
    {G, G, G, G, G, G, G, G, G, D, D, B, B},
    {G, G, G, D, D, G, D, D, G, D, D, B, B},
    {G, G, G, D, D, G, D, D, G, G, G, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
};

const cell_t Cell_TI4 = { // TI4
    {B, B, G, G, G, G, G, G, G, D, D, B, B},
    {B, B, G, G, G, D, D, G, G, D, D, B, B},
    {B, B, G, G, G, D, D, G, G, G, G, B, B},
    {B, B, D, D, G, G, G, G, D, D, G, B, B},
    {B, B, D, D, G, G, G, G, D, D, G, B, B},
    {B, B, G, G, G, D, D, G, G, G, G, B, B},
    {B, B, D, D, G, D, D, G, G, D, D, B, B},
    {B, B, D, D, G, G, G, G, G, D, D, B, B},
    {B, B, G, G, G, G, D, D, G, G, G, B, B},
    {B, B, G, D, D, G, D, D, G, G, G, B, B},
    {B, B, G, D, D, G, G, G, G, G, G, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
};

const cell_t Cell_TI5 = { // TI5
    {B, B, G, G, G, D, D, G, G, D, D, B, B},
    {B, B, G, G, G, D, D, G, G, D, D, B, B},
    {B, B, D, D, G, G, G, G, G, G, G, B, B},
    {B, B, D, D, G, G, D, D, G, D, D, B, B},
    {B, B, G, G, G, G, D, D, G, D, D, B, B},
    {B, B, G, D, D, G, G, G, G, G, G, B, B},
    {B, B, G, D, D, G, G, G, G, D, D, B, B},
    {B, B, G, G, G, G, G, G, G, D, D, B, B},
    {B, B, D, D, G, D, D, G, G, G, G, B, B},
    {B, B, D, D, G, D, D, G, G, G, G, B, B},
    {B, B, G, G, G, G, G, G, D, D, G, B, B},
    {B, B, G, D, D, G, G, G, D, D, G, B, B},
    {B, B, G, D, D, G, G, G, G, G, G, B, B},
};

const cell_t Cell_TI6 = { // TI6
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, G, G, G, G, D, D, G, G, G, B, B},
    {B, B, G, D, D, G, D, D, G, D, D, B, B},
    {B, B, G, D, D, G, G, G, G, D, D, B, B},
    {B, B, G, G, G, G, G, G, G, G, G, B, B},
    {B, B, D, G, G, G, D, D, G, G, G, B, B},
    {B, B, D, G, G, G, D, D, G, G, G, B, B},
    {B, B, G, G, G, G, G, G, G, D, D, B, B},
    {B, B, G, D, D, G, G, G, G, D, D, B, B},
    {B, B, G, D, D, G, D, D, G, G, G, B, B},
    {B, B, G, G, G, G, D, D, G, G, G, B, B},
    {B, B, G, G, G, G, G, G, G, G, G, B, B},
};

const cell_t Cell_TMJ = { // TMJ
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, G, G, G, G, G, G, G, G, G, B, B},
    {B, B, G, B, B, B, B, B, B, B, G, B, B},
    {B, B, G, B, B, B, B, B, B, B, G, B, B},
    {B, B, G, B, B, W, W, W, B, B, G, B, B},
    {B, B, G, B, B, W, W, W, B, B, G, B, B},
    {B, B, G, B, B, W, W, W, B, B, G, B, B},
    {B, B, G, B, B, B, B, B, B, B, G, B, B},
    {B, B, G, B, B, B, B, B, B, B, G, B, B},
    {B, B, G, G, G, G, G, G, G, G, G, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
};

const cell_t Cell_TML = { // TML
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, D, D, D, D, D, D, D, D, D, B, B},
    {B, B, D, D, D, D, D, D, D, D, D, B, B},
    {B, B, D, D, D, D, D, D, D, D, D, B, B},
    {B, B, D, D, D, D, D, D, D, D, D, B, B},
    {B, B, D, D, D, D, D, D, D, D, D, B, B},
    {B, B, D, D, D, D, D, D, D, D, D, B, B},
    {B, B, D, D, D, D, D, D, D, D, D, B, B},
    {B, B, D, D, D, D, D, D, D, D, D, B, B},
    {B, B, D, D, D, D, D, D, D, D, D, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
};

const cell_t Cell_TMO = { // TMO
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, W, W, W, W, W, W, W, W, W, B, B},
    {B, B, W, B, B, B, B, B, B, B, W, B, B},
    {B, B, W, B, B, B, B, B, B, B, W, B, B},
    {B, B, W, B, B, B, B, B, B, B, W, B, B},
    {B, B, W, B, B, B, B, B, B, B, W, B, B},
    {B, B, W, B, B, B, B, B, B, B, W, B, B},
    {B, B, W, B, B, B, B, B, B, B, W, B, B},
    {B, B, W, B, B, B, B, B, B, B, W, B, B},
    {B, B, W, W, W, W, W, W, W, W, W, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
};

const cell_t Cell_TMS = { // TMS
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, D, D, D, D, D, D, D, D, D, B, B},
    {B, B, D, B, B, B, B, B, B, B, D, B, B},
    {B, B, D, B, B, B, B, B, B, B, D, B, B},
    {B, B, D, B, B, W, W, W, B, B, D, B, B},
    {B, B, D, B, B, W, W, W, B, B, D, B, B},
    {B, B, D, B, B, W, W, W, B, B, D, B, B},
    {B, B, D, B, B, B, B, B, B, B, D, B, B},
    {B, B, D, B, B, B, B, B, B, B, D, B, B},
    {B, B, D, D, D, D, D, D, D, D, D, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
};

const cell_t Cell_TMT = { // TMT
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, G, G, G, G, G, G, G, G, G, B, B},
    {B, B, G, W, W, W, W, W, W, W, G, B, B},
    {B, B, G, W, W, W, W, W, W, W, G, B, B},
    {B, B, G, W, W, G, G, G, B, B, G, B, B},
    {B, B, G, W, W, G, G, G, B, B, G, B, B},
    {B, B, G, W, W, G, G, G, B, B, G, B, B},
    {B, B, G, B, B, B, B, B, B, B, G, B, B},
    {B, B, G, B, B, B, B, B, B, B, G, B, B},
    {B, B, G, G, G, G, G, G, G, G, G, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
};

const cell_t Cell_TMZ = { // TMZ
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, G, G, G, G, G, G, G, G, G, B, B},
    {B, B, G, G, G, G, G, G, G, G, G, B, B},
    {B, B, G, G, G, G, G, G, G, G, G, B, B},
    {B, B, G, G, G, B, B, B, G, G, G, B, B},
    {B, B, G, G, G, B, B, B, G, G, G, B, B},
    {B, B, G, G, G, B, B, B, G, G, G, B, B},
    {B, B, G, G, G, G, G, G, G, G, G, B, B},
    {B, B, G, G, G, G, G, G, G, G, G, B, B},
    {B, B, G, G, G, G, G, G, G, G, G, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
};

const cell_t Cell_BK1 = { // BK1
    {G, G, B, W, W, G, G, G, B, W, W, G, G},
    {G, G, B, G, G, G, G, G, B, G, G, G, G},
    {G, G, B, G, G, G, G, G, B, G, G, G, G},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, G, G, G, B, W, W, G, G, G, B, W},
    {G, G, G, G, G, B, G, G, G, G, G, B, G},
    {G, G, G, G, G, B, G, G, G, G, G, B, G},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {G, G, B, W, W, G, G, G, B, W, W, G, G},
    {G, G, B, G, G, G, G, G, B, G, G, G, G},
    {G, G, B, G, G, G, G, G, B, G, G, G, G},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, G, G, G, B, W, W, G, G, G, B, W},
};

const cell_t Cell_BK2 = { // BK2
    {G, G, G, G, G, B, G, G, G, G, G, B, G},
    {G, G, G, G, G, B, G, G, G, G, G, B, G},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {G, G, B, W, W, G, G, G, B, W, W, G, G},
    {G, G, B, G, G, G, G, G, B, G, G, G, G},
    {G, G, B, G, G, G, G, G, B, G, G, G, G},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, G, G, G, B, W, W, G, G, G, B, W},
    {G, G, G, G, G, B, G, G, G, G, G, B, G},
    {G, G, G, G, G, B, G, G, G, G, G, B, G},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {G, G, B, W, W, G, G, G, B, W, W, G, G},
    {G, G, B, G, G, G, G, G, B, G, G, G, G},
};

const cell_t Cell_BK3 = { // BK3
    {G, G, B, G, G, G, G, G, B, G, G, G, G},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, G, G, G, B, W, W, G, G, G, B, W},
    {G, G, G, G, G, B, G, G, G, G, G, B, G},
    {G, G, G, G, G, B, G, G, G, G, G, B, G},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {G, G, B, W, W, G, G, G, B, W, W, G, G},
    {G, G, B, G, G, G, G, G, B, G, G, G, G},
    {G, G, B, G, G, G, G, G, B, G, G, G, G},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, G, G, G, B, W, W, G, G, G, B, W},
    {G, G, G, G, G, B, G, G, G, G, G, B, G},
    {G, G, G, G, G, B, G, G, G, G, G, B, G},
};

const cell_t Cell_BK4 = { // BK4
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {G, G, B, W, W, G, G, G, B, W, W, G, G},
    {G, G, B, G, G, G, G, G, B, G, G, G, G},
    {G, G, B, G, G, G, G, G, B, G, G, G, G},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, G, G, G, B, W, W, G, G, G, B, W},
    {G, G, G, G, G, B, G, G, G, G, G, B, G},
    {G, G, G, G, G, B, G, G, G, G, G, B, G},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {G, G, B, W, W, G, G, G, B, W, W, G, G},
    {G, G, B, G, G, G, G, G, B, G, G, G, G},
    {G, G, B, G, G, G, G, G, B, G, G, G, G},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
};

const cell_t Cell_BK5 = { // BK5
    {W, W, G, G, G, B, W, W, G, G, G, B, W},
    {G, G, G, G, G, B, G, G, G, G, G, B, G},
    {G, G, G, G, G, B, G, G, G, G, G, B, G},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {G, G, B, W, W, G, G, G, B, W, W, G, G},
    {G, G, B, G, G, G, G, G, B, G, G, G, G},
    {G, G, B, G, G, G, G, G, B, G, G, G, G},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, G, G, G, B, W, W, G, G, G, B, W},
    {G, G, G, G, G, B, G, G, G, G, G, B, G},
    {G, G, G, G, G, B, G, G, G, G, G, B, G},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {G, G, B, W, W, G, G, G, B, W, W, G, G},
};

const cell_t Cell_BK6 = { // BK6
    {G, G, B, G, G, G, G, G, B, G, G, G, G},
    {G, G, B, G, G, G, G, G, B, G, G, G, G},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, G, G, G, B, W, W, G, G, G, B, W},
    {G, G, G, G, G, B, G, G, G, G, G, B, G},
    {G, G, G, G, G, B, G, G, G, G, G, B, G},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {G, G, B, W, W, G, G, G, B, W, W, G, G},
    {G, G, B, G, G, G, G, G, B, G, G, G, G},
    {G, G, B, G, G, G, G, G, B, G, G, G, G},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, G, G, G, B, W, W, G, G, G, B, W},
    {G, G, G, G, G, B, G, G, G, G, G, B, G},
};

const cell_t Cell_BK7 = { // BK7
    {G, G, G, G, G, B, G, G, G, G, G, B, G},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {G, G, B, W, W, G, G, G, B, W, W, G, G},
    {G, G, B, G, G, G, G, G, B, G, G, G, G},
    {G, G, B, G, G, G, G, G, B, G, G, G, G},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, G, G, G, B, W, W, G, G, G, B, W},
    {G, G, G, G, G, B, G, G, G, G, G, B, G},
    {G, G, G, G, G, B, G, G, G, G, G, B, G},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {G, G, B, W, W, G, G, G, B, W, W, G, G},
    {G, G, B, G, G, G, G, G, B, G, G, G, G},
    {G, G, B, G, G, G, G, G, B, G, G, G, G},
};

const cell_t Cell_BK8 = { // BK8
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, G, G, G, B, W, W, G, G, G, B, W},
    {G, G, G, G, G, B, G, G, G, G, G, B, G},
    {G, G, G, G, G, B, G, G, G, G, G, B, G},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {G, G, B, W, W, G, G, G, B, W, W, G, G},
    {G, G, B, G, G, G, G, G, B, G, G, G, G},
    {G, G, B, G, G, G, G, G, B, G, G, G, G},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, G, G, G, B, W, W, G, G, G, B, W},
    {G, G, G, G, G, B, G, G, G, G, G, B, G},
    {G, G, G, G, G, B, G, G, G, G, G, B, G},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
};

const cell_t Cell_DB1 = { // DB1
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, W, W, W},
    {W, W, B, B, B, B, B, B, B, W, W, W, W},
    {W, W, B, B, B, B, B, B, W, W, W, W, D},
    {W, W, B, B, B, B, B, B, W, W, W, D, D},
    {W, W, B, B, B, B, B, B, W, W, D, D, D},
};

const cell_t Cell_DB2 = { // DB2
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_DB3 = { // DB3
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, W, B, B, B, B, B, B, B, B, B, B},
    {W, W, W, W, B, B, B, B, B, B, B, B, B},
    {D, W, W, W, W, B, B, B, B, B, B, B, B},
    {D, D, W, W, W, B, B, B, B, B, B, B, B},
    {D, D, D, W, W, B, B, B, B, B, B, B, B},
};

const cell_t Cell_DB4 = { // DB4
    {W, W, B, B, B, B, B, B, W, W, D, D, W},
    {W, W, B, B, B, B, B, B, W, W, D, D, W},
    {W, W, B, B, B, B, B, B, W, W, D, D, W},
    {W, W, B, B, B, B, B, B, W, W, D, D, W},
    {W, W, B, B, B, B, B, B, W, W, D, D, W},
    {W, W, B, B, B, B, B, B, W, W, D, D, W},
    {W, W, B, B, B, B, B, B, W, W, D, D, W},
    {W, W, B, B, B, B, B, B, W, W, D, D, W},
    {W, W, B, B, B, B, B, B, W, W, D, D, W},
    {W, W, B, B, B, B, B, B, W, W, D, D, W},
    {W, W, B, B, B, B, B, B, W, W, D, D, W},
    {W, W, B, B, B, B, B, B, W, W, D, D, W},
    {W, W, B, B, B, B, B, B, W, W, D, D, W},
};

const cell_t Cell_DB5 = { // DB5
    {W, D, D, W, W, B, B, B, B, B, B, B, B},
    {W, D, D, W, W, B, B, B, B, B, B, B, B},
    {W, D, D, W, W, B, B, B, B, B, B, B, B},
    {W, D, D, W, W, B, B, B, B, B, B, B, B},
    {W, D, D, W, W, B, B, B, B, B, B, B, B},
    {W, D, D, W, W, B, B, B, B, B, B, B, B},
    {W, D, D, W, W, B, B, B, B, B, B, B, B},
    {W, D, D, W, W, B, B, B, B, B, B, B, B},
    {W, D, D, W, W, B, B, B, B, B, B, B, B},
    {W, D, D, W, W, B, B, B, B, B, B, B, B},
    {W, D, D, W, W, B, B, B, B, B, B, B, B},
    {W, D, D, W, W, B, B, B, B, B, B, B, B},
    {W, D, D, W, W, B, B, B, B, B, B, B, B},
};

const cell_t Cell_DB6 = { // DB6
    {W, W, B, B, B, B, B, B, W, W, D, D, D},
    {W, W, B, B, B, B, B, B, W, W, W, D, D},
    {W, W, B, B, B, B, B, B, W, W, W, W, D},
    {W, W, B, B, B, B, B, B, B, W, W, W, W},
    {W, W, B, B, B, B, B, B, B, B, W, W, W},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, W, W, W},
    {W, W, B, B, B, B, B, B, B, W, W, W, W},
    {W, W, B, B, B, B, B, B, W, W, W, W, D},
    {W, W, B, B, B, B, B, B, W, W, W, D, D},
    {W, W, B, B, B, B, B, B, W, W, D, D, D},
};

const cell_t Cell_DB7 = { // DB7
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_DB8 = { // DB8
    {D, D, D, W, W, B, B, B, B, B, B, B, B},
    {D, D, W, W, W, B, B, B, B, B, B, B, B},
    {D, W, W, W, W, B, B, B, B, B, B, B, B},
    {W, W, W, W, B, B, B, B, B, B, B, B, B},
    {W, W, W, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, W, B, B, B, B, B, B, B, B, B, B},
    {W, W, W, W, B, B, B, B, B, B, B, B, B},
    {D, W, W, W, W, B, B, B, B, B, B, B, B},
    {D, D, W, W, W, B, B, B, B, B, B, B, B},
    {D, D, D, W, W, B, B, B, B, B, B, B, B},
};

const cell_t Cell_DB9 = { // DB9
    {W, W, B, B, B, B, B, B, W, W, D, D, D},
    {W, W, B, B, B, B, B, B, W, W, W, D, D},
    {W, W, B, B, B, B, B, B, W, W, W, W, D},
    {W, W, B, B, B, B, B, B, B, W, W, W, W},
    {W, W, B, B, B, B, B, B, B, B, W, W, W},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
};

const cell_t Cell_D10 = { // D10
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
};

const cell_t Cell_D11 = { // D11
    {D, D, D, W, W, B, B, B, B, B, B, B, B},
    {D, D, W, W, W, B, B, B, B, B, B, B, B},
    {D, W, W, W, W, B, B, B, B, B, B, B, B},
    {W, W, W, W, B, B, B, B, B, B, B, B, B},
    {W, W, W, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
};

const cell_t Cell_PB1 = { // PB1
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, G, G, G, G, G},
    {B, B, B, B, B, B, B, G, W, W, W, W, W},
    {B, B, B, B, B, B, G, W, W, W, W, W, W},
    {B, B, B, B, B, G, W, W, W, W, G, G, D},
    {B, B, B, B, B, G, W, W, W, W, G, G, D},
    {B, B, B, B, B, G, W, W, G, G, D, D, B},
    {B, B, B, B, B, G, W, W, G, G, D, D, B},
    {B, B, B, B, B, G, W, W, D, D, B, B, W},
};

const cell_t Cell_PB2 = { // PB2
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_PB3 = { // PB3
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {G, G, G, G, G, B, B, B, B, B, B, B, B},
    {W, W, W, W, W, G, B, B, B, B, B, B, B},
    {W, W, W, W, W, W, G, B, B, B, B, B, B},
    {D, G, G, W, W, W, W, G, B, B, B, B, B},
    {D, G, G, W, W, W, W, G, B, B, B, B, B},
    {B, D, D, G, G, W, W, G, B, B, B, B, B},
    {B, D, D, G, G, W, W, G, B, B, B, B, B},
    {W, B, B, D, D, W, W, G, B, B, B, B, B},
};

const cell_t Cell_PB4 = { // PB4
    {B, B, B, B, B, G, W, W, D, D, B, B, W},
    {B, B, B, B, B, G, W, W, D, D, B, B, W},
    {B, B, B, B, B, G, W, W, D, D, B, B, W},
    {B, B, B, B, B, G, W, W, D, D, B, B, W},
    {B, B, B, B, B, G, W, W, D, D, B, B, W},
    {B, B, B, B, B, G, W, W, D, D, B, B, W},
    {B, B, B, B, B, G, W, W, D, D, B, B, W},
    {B, B, B, B, B, G, W, W, D, D, B, B, W},
    {B, B, B, B, B, G, W, W, D, D, B, B, W},
    {B, B, B, B, B, G, W, W, D, D, B, B, W},
    {B, B, B, B, B, G, W, W, D, D, B, B, W},
    {B, B, B, B, B, G, W, W, D, D, B, B, W},
    {B, B, B, B, B, G, W, W, D, D, B, B, W},
};

const cell_t Cell_PB5 = { // PB5
    {W, B, B, D, D, W, W, G, B, B, B, B, B},
    {W, B, B, D, D, W, W, G, B, B, B, B, B},
    {W, B, B, D, D, W, W, G, B, B, B, B, B},
    {W, B, B, D, D, W, W, G, B, B, B, B, B},
    {W, B, B, D, D, W, W, G, B, B, B, B, B},
    {W, B, B, D, D, W, W, G, B, B, B, B, B},
    {W, B, B, D, D, W, W, G, B, B, B, B, B},
    {W, B, B, D, D, W, W, G, B, B, B, B, B},
    {W, B, B, D, D, W, W, G, B, B, B, B, B},
    {W, B, B, D, D, W, W, G, B, B, B, B, B},
    {W, B, B, D, D, W, W, G, B, B, B, B, B},
    {W, B, B, D, D, W, W, G, B, B, B, B, B},
    {W, B, B, D, D, W, W, G, B, B, B, B, B},
};

const cell_t Cell_PB6 = { // PB6
    {B, B, B, B, B, G, W, W, D, D, B, B, W},
    {B, B, B, B, B, G, W, W, G, G, D, D, B},
    {B, B, B, B, B, G, W, W, G, G, D, D, B},
    {B, B, B, B, B, G, W, W, W, W, G, G, D},
    {B, B, B, B, B, G, W, W, W, W, G, G, D},
    {B, B, B, B, B, B, G, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, G, W, W, W, W, W},
    {B, B, B, B, B, B, B, B, G, G, G, G, G},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
};

const cell_t Cell_PB7 = { // PB7
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
};

const cell_t Cell_PB8 = { // PB8
    {W, B, B, D, D, W, W, G, B, B, B, B, B},
    {B, D, D, G, G, W, W, G, B, B, B, B, B},
    {B, D, D, G, G, W, W, G, B, B, B, B, B},
    {D, G, G, W, W, W, W, G, B, B, B, B, B},
    {D, G, G, W, W, W, W, G, B, B, B, B, B},
    {W, W, W, W, W, W, G, B, B, B, B, B, B},
    {W, W, W, W, W, G, B, B, B, B, B, B, B},
    {G, G, G, G, G, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
};

const cell_t Cell_SF1 = { // SF1
    {W, W, B, B, B, B, B, B, W, W, D, D, W},
    {W, W, B, B, B, B, B, B, W, W, D, D, W},
    {W, W, B, B, B, B, B, B, W, W, D, D, W},
    {W, W, B, B, B, B, B, B, W, W, D, D, W},
    {W, W, B, B, B, B, B, B, W, W, D, D, W},
    {W, W, B, B, B, B, B, B, W, W, D, D, W},
    {W, W, B, B, B, B, B, B, W, W, D, D, W},
    {W, W, B, B, B, B, B, B, W, W, D, D, W},
    {W, W, W, W, W, W, W, W, W, W, D, D, W},
    {W, W, W, W, W, W, W, W, W, W, D, D, W},
    {W, W, D, D, D, D, D, D, W, W, D, D, W},
    {W, W, D, D, D, D, D, D, W, W, D, D, W},
    {W, W, D, D, D, D, D, D, W, W, D, D, W},
};

const cell_t Cell_SF2 = { // SF2
    {W, D, D, W, W, B, B, B, B, B, B, B, B},
    {W, D, D, W, W, B, B, B, B, B, B, B, B},
    {W, D, D, W, W, B, B, B, B, B, B, B, B},
    {W, D, D, W, W, B, B, B, B, B, B, B, B},
    {W, D, D, W, W, B, B, B, B, B, B, B, B},
    {W, D, D, W, W, B, B, B, B, B, B, B, B},
    {W, D, D, W, W, B, B, B, B, B, B, B, B},
    {W, D, D, W, W, B, B, B, B, B, B, B, B},
    {W, D, D, W, W, W, W, W, W, W, W, W, W},
    {W, D, D, W, W, W, W, W, W, W, W, W, W},
    {W, D, D, W, W, D, D, D, D, D, D, D, D},
    {W, D, D, W, W, D, D, D, D, D, D, D, D},
    {W, D, D, W, W, D, D, D, D, D, D, D, D},
};

const cell_t Cell_SF3 = { // SF3
    {W, W, D, D, D, D, D, D, W, W, D, D, D},
    {W, W, D, D, D, D, D, D, W, W, W, D, D},
    {W, W, D, D, D, D, D, D, W, W, W, W, D},
    {W, W, D, D, D, D, D, D, D, W, W, W, W},
    {W, W, D, D, D, D, D, D, D, D, W, W, W},
    {W, W, D, D, D, D, D, D, D, D, D, D, D},
    {W, W, D, D, D, D, D, D, D, D, D, D, D},
    {W, W, D, D, D, D, D, D, D, D, D, D, D},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, D, D, D, D, D, D, D, D, D, D, D},
    {W, W, D, D, D, D, D, D, D, D, D, D, D},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_SF4 = { // SF4
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_SF5 = { // SF5
    {D, D, D, W, W, D, D, D, D, D, D, D, D},
    {D, D, W, W, W, D, D, D, D, D, D, D, D},
    {D, W, W, W, W, D, D, D, D, D, D, D, D},
    {W, W, W, W, D, D, D, D, D, D, D, D, D},
    {W, W, W, D, D, D, D, D, D, D, D, D, D},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {D, D, D, D, D, D, D, D, D, D, D, D, D},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_SF6 = { // SF6
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, D, D, D, D, D, D, D, D, D, D, D},
    {W, W, D, D, D, D, D, D, D, D, D, D, D},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
};

const cell_t Cell_TSN = { // TMO
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, W, W, W, W, W, W, W, W, W, B, B},
    {B, B, W, G, G, G, G, G, G, G, D, B, B},
    {B, B, W, G, G, G, G, G, G, G, D, B, B},
    {B, B, W, G, G, G, G, G, G, G, D, B, B},
    {B, B, W, G, G, G, G, G, G, G, D, B, B},
    {B, B, W, G, G, G, G, G, G, G, D, B, B},
    {B, B, W, G, G, G, G, G, G, G, D, B, B},
    {B, B, W, G, G, G, G, G, G, G, D, B, B},
    {B, B, D, D, D, D, D, D, D, D, D, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
};

const cell_t Cell_OB1 = { // OB1
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, B, B, B, B, B, B},
    {W, W, W, W, W, W, B, B, B, B, B, B, B},
    {W, W, W, W, W, B, B, B, B, B, B, B, B},
    {W, W, W, W, B, B, B, B, W, W, W, W, W},
    {W, W, W, B, B, B, B, W, W, W, W, W, W},
    {W, W, W, B, B, B, W, W, W, W, G, G, G},
    {W, W, W, B, B, B, W, W, W, G, G, G, G},
    {W, W, W, B, B, B, W, W, G, G, G, W, W},
    {W, W, W, B, B, B, W, W, G, G, W, W, W},
    {W, W, W, B, B, B, W, W, G, G, W, W, W},
};

const cell_t Cell_OB2 = { // OB2
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_OB3 = { // OB3
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, B, W, W, W, W, W},
    {W, W, W, W, W, B, B, B, B, W, W, W, W},
    {W, W, W, W, W, W, B, B, B, B, W, W, W},
    {G, G, G, W, W, W, W, B, B, B, W, W, W},
    {G, G, G, G, W, W, W, B, B, B, W, W, W},
    {W, W, G, G, G, W, W, B, B, B, W, W, W},
    {W, W, W, G, G, W, W, B, B, B, W, W, W},
    {W, W, W, G, G, W, W, B, B, B, W, W, W},
};

const cell_t Cell_OB4 = { // OB4
    {W, W, W, B, B, B, W, W, G, G, W, W, W},
    {W, W, W, B, B, B, W, W, G, G, W, W, W},
    {W, W, W, B, B, B, W, W, G, G, W, W, W},
    {W, W, W, B, B, B, W, W, G, G, W, W, W},
    {W, W, W, B, B, B, W, W, G, G, W, W, W},
    {W, W, W, B, B, B, W, W, G, G, W, W, W},
    {W, W, W, B, B, B, W, W, G, G, W, W, W},
    {W, W, W, B, B, B, W, W, G, G, W, W, W},
    {W, W, W, B, B, B, W, W, G, G, W, W, W},
    {W, W, W, B, B, B, W, W, G, G, W, W, W},
    {W, W, W, B, B, B, W, W, G, G, W, W, W},
    {W, W, W, B, B, B, W, W, G, G, W, W, W},
    {W, W, W, B, B, B, W, W, G, G, W, W, W},
};

const cell_t Cell_OB5 = { // OB5
    {W, W, W, G, G, W, W, B, B, B, W, W, W},
    {W, W, W, G, G, W, W, B, B, B, W, W, W},
    {W, W, W, G, G, W, W, B, B, B, W, W, W},
    {W, W, W, G, G, W, W, B, B, B, W, W, W},
    {W, W, W, G, G, W, W, B, B, B, W, W, W},
    {W, W, W, G, G, W, W, B, B, B, W, W, W},
    {W, W, W, G, G, W, W, B, B, B, W, W, W},
    {W, W, W, G, G, W, W, B, B, B, W, W, W},
    {W, W, W, G, G, W, W, B, B, B, W, W, W},
    {W, W, W, G, G, W, W, B, B, B, W, W, W},
    {W, W, W, G, G, W, W, B, B, B, W, W, W},
    {W, W, W, G, G, W, W, B, B, B, W, W, W},
    {W, W, W, G, G, W, W, B, B, B, W, W, W},
};

const cell_t Cell_OB6 = { // OB6
    {W, W, W, B, B, B, W, W, G, G, W, W, W},
    {W, W, W, B, B, B, W, W, G, G, W, W, W},
    {W, W, W, B, B, B, W, W, G, G, G, W, W},
    {W, W, W, B, B, B, W, W, W, G, G, G, G},
    {W, W, W, B, B, B, W, W, W, W, G, G, G},
    {W, W, W, B, B, B, B, W, W, W, W, W, W},
    {W, W, W, W, B, B, B, B, W, W, W, W, W},
    {W, W, W, W, W, B, B, B, B, B, B, B, B},
    {W, W, W, W, W, W, B, B, B, B, B, B, B},
    {W, W, W, W, W, W, W, B, B, B, B, B, B},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_OB7 = { // OB7
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_OB8 = { // OB8
    {W, W, W, G, G, W, W, B, B, B, W, W, W},
    {W, W, W, G, G, W, W, B, B, B, W, W, W},
    {W, W, G, G, G, W, W, B, B, B, W, W, W},
    {G, G, G, G, W, W, W, B, B, B, W, W, W},
    {G, G, G, W, W, W, W, B, B, B, W, W, W},
    {W, W, W, W, W, W, B, B, B, B, W, W, W},
    {W, W, W, W, W, B, B, B, B, W, W, W, W},
    {B, B, B, B, B, B, B, B, W, W, W, W, W},
    {B, B, B, B, B, B, B, W, W, W, W, W, W},
    {B, B, B, B, B, B, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_DL1 = { // DL1
    {B, B, W, B, B, W, B, B, W, B, B, W, B},
    {B, B, W, B, B, W, B, B, W, B, B, W, B},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_DL2 = { // DL2
    {B, W, B, B, W, B, B, W, B, B, W, B, B},
    {B, W, B, B, W, B, B, W, B, B, W, B, B},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_DL3 = { // DL3
    {W, B, B, W, B, B, W, B, B, W, B, B, W},
    {W, B, B, W, B, B, W, B, B, W, B, B, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
};

const cell_t Cell_HRT = { // HRT
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, B, B, B, B, W, B, B, B, B, W},
    {W, W, B, B, W, G, B, B, B, G, G, B, B},
    {W, W, B, W, W, G, G, B, G, G, G, G, B},
    {W, W, B, W, G, G, G, G, G, G, G, G, B},
    {W, W, B, G, G, G, G, G, G, G, G, G, B},
    {W, W, B, B, G, G, G, G, G, G, G, B, B},
    {W, W, W, B, B, G, G, G, G, G, B, B, W},
    {W, W, W, W, B, B, G, G, G, B, B, W, W},
    {W, W, W, W, W, B, B, G, B, B, W, W, W},
    {W, W, W, W, W, W, B, B, B, W, W, W, W},
    {W, W, W, W, W, W, W, B, W, W, W, W, W},
};

const cell_t Cell_BN1 = { // BN1
    {B, B, B, B, B, B, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, B, B, W},
    {B, B, B, B, B, B, B, B, B, B, B, B, W},
    {B, B, B, B, B, B, W, W, B, B, B, B, W},
    {B, B, B, B, B, B, W, W, B, B, B, B, W},
    {B, B, B, B, B, B, W, W, B, B, B, B, B},
};

const cell_t Cell_BN2 = { // BN2
    {W, W, W, B, B, B, B, B, B, W, W, W, W},
    {W, W, W, B, B, B, B, B, B, W, W, W, W},
    {W, W, W, B, B, B, B, B, B, W, W, W, W},
    {W, W, W, B, B, B, B, B, B, W, W, W, W},
    {W, W, W, B, B, B, B, B, B, W, W, W, W},
    {W, W, W, B, B, B, B, B, B, W, W, W, W},
    {W, W, W, B, B, B, B, B, B, W, W, W, W},
    {W, W, W, B, B, B, B, B, B, W, W, W, W},
    {W, W, W, B, B, B, B, B, B, W, W, W, W},
    {W, W, W, B, B, B, B, B, B, W, W, W, W},
    {W, W, W, B, B, B, B, B, B, W, W, W, W},
    {W, W, W, B, B, B, B, B, B, W, W, W, W},
    {B, W, W, B, B, B, B, B, B, W, W, W, W},
};

const cell_t Cell_BN3 = { // BN3
    {B, B, B, B, B, B, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, W, W, W, W, B, B, B},
    {B, B, B, B, B, B, W, W, W, W, B, B, B},
    {B, B, B, B, B, B, W, W, W, W, B, B, B},
};

const cell_t Cell_BN4 = { // BN4
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, B, W, W, W, W, B, B, B, B, B, B},
    {B, B, B, W, W, W, W, B, B, B, B, B, B},
    {B, B, B, W, W, B, B, B, B, B, B, B, B},
};

const cell_t Cell_BN5 = { // BN5
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, B, B, B, B, B, B, W},
    {W, W, W, W, W, W, B, B, B, B, B, B, W},
    {W, W, W, W, W, W, B, B, B, B, B, B, W},
    {W, W, W, W, W, W, B, B, B, B, B, B, W},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, B, B, B, B, B, B, B, B, B, B, B},
    {W, W, W, W, W, W, B, B, B, B, B, B, W},
    {W, W, W, W, W, W, B, B, B, B, B, B, W},
    {B, B, W, W, W, W, B, B, B, B, B, B, W},
};

const cell_t Cell_BN6 = { // BN6
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, B, W, W, W, W, W, W, W, W, W, W},
    {B, B, B, W, W, W, W, W, W, W, W, W, W},
    {B, B, B, W, W, W, W, W, W, W, W, W, W},
    {B, B, B, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, B, B, B, B, B, B},
    {W, W, W, W, W, W, W, B, B, B, B, B, B},
    {W, W, W, W, W, B, B, B, B, B, B, B, B},
};

const cell_t Cell_BN7 = { // BN7
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, B, W, W, W, W, W},
    {B, B, B, B, B, B, B, B, W, W, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, W, W, W},
};

const cell_t Cell_BN8 = { // BN8
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, B, B, B, B, B, B, W, W, W, W, B, B},
    {W, B, B, B, B, B, B, W, W, W, W, B, B},
    {W, B, B, B, B, B, B, W, W, B, B, B, B},
};

const cell_t Cell_BN9 = { // BN9
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, B, B, W, W, W, W, W, W, W, W, W},
    {B, B, B, B, W, W, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, W, W, W, W, W, W, B},
};

const cell_t Cell_B10 = { // B10
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, B, B, B, B},
    {W, W, W, W, W, W, W, W, W, B, B, B, B},
    {W, W, W, W, W, W, W, W, W, B, B, B, B},
    {W, W, W, W, W, W, W, W, W, B, B, B, B},
    {W, W, W, W, W, W, W, W, W, B, B, B, B},
    {W, W, W, W, W, W, W, W, W, B, B, B, B},
    {W, W, W, W, W, W, W, W, W, B, B, B, B},
    {W, W, W, W, W, W, W, W, W, B, B, B, B},
    {W, B, B, B, B, B, B, W, W, B, B, B, B},
    {W, B, B, B, B, B, B, W, W, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
};

const cell_t Cell_B11 = { // B11
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, W, W, W, W, W, W, W, W, B, B, B},
    {B, B, W, W, W, W, W, W, W, W, B, B, B},
    {B, B, W, W, W, W, W, W, B, B, B, B, B},
};

const cell_t Cell_B12 = { // B12
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, B, B, W, W, W, W},
    {B, B, B, B, B, B, B, B, B, W, W, W, W},
    {B, W, W, W, W, B, B, B, B, B, B, W, W},
};

const cell_t Cell_B13 = { // B13
    {B, B, B, B, B, B, W, W, B, B, B, B, B},
    {B, B, B, B, B, B, W, W, W, W, B, B, B},
    {B, B, B, B, B, B, W, W, W, W, B, B, B},
    {B, B, B, B, B, B, W, W, W, W, B, B, B},
    {B, B, B, B, B, B, W, W, W, W, B, B, B},
    {B, B, B, B, B, B, W, W, W, W, W, W, B},
    {B, B, B, B, B, B, W, W, W, W, W, W, B},
    {B, B, B, B, B, B, W, W, W, W, W, W, B},
    {B, B, B, B, B, B, W, W, W, W, W, W, B},
    {B, B, B, B, B, B, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, W, W, W, W, W, W, W},
};

const cell_t Cell_B14 = { // B14
    {B, W, W, B, B, B, B, B, B, W, W, W, W},
    {B, W, W, B, B, B, B, B, B, W, W, W, W},
    {B, W, W, B, B, B, B, B, B, W, W, W, W},
    {B, B, B, B, B, B, B, B, B, W, W, W, W},
    {B, B, B, B, B, B, B, B, B, W, W, W, W},
    {B, B, B, B, B, B, B, B, B, W, W, W, W},
    {B, B, B, B, B, B, B, B, B, W, W, W, W},
    {B, B, B, B, B, B, B, B, B, W, W, W, W},
    {B, B, B, B, B, B, B, B, B, W, W, W, W},
    {W, W, W, B, B, B, B, B, B, W, W, W, W},
    {W, W, W, B, B, B, B, B, B, W, W, W, W},
    {W, W, W, B, B, B, B, B, B, W, W, W, W},
    {W, W, W, B, B, B, B, B, B, W, W, W, W},
};

const cell_t Cell_B15 = { // B15
    {B, B, B, B, B, B, W, W, W, W, B, B, B},
    {B, B, B, B, B, B, W, W, W, W, B, B, B},
    {B, B, B, B, B, B, W, W, W, W, B, B, B},
    {B, B, B, B, B, B, W, W, W, W, B, B, B},
    {B, B, B, B, B, B, W, W, W, W, B, B, B},
    {B, B, B, B, B, B, W, W, W, W, B, B, B},
    {B, B, B, B, B, B, W, W, W, W, B, B, B},
    {B, B, B, B, B, B, W, W, W, W, B, B, B},
    {B, B, B, B, B, B, W, W, W, W, B, B, B},
    {B, B, B, B, B, B, W, W, W, W, B, B, B},
    {B, B, B, B, B, B, W, W, W, W, B, B, B},
    {B, B, B, B, B, B, W, W, W, W, B, B, B},
    {B, B, B, B, B, B, W, W, W, W, B, B, B},
};

const cell_t Cell_B16 = { // B16
    {B, B, B, W, W, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, W, W, B, B, B, B},
    {B, B, B, B, B, B, B, W, W, B, B, B, B},
    {B, B, B, B, B, W, W, W, W, B, B, B, B},
    {B, B, B, B, B, W, W, W, W, B, B, B, B},
    {B, B, B, W, W, W, W, W, W, B, B, B, B},
    {B, B, B, W, W, W, W, W, W, B, B, B, B},
    {B, B, B, W, W, W, W, W, W, B, B, B, B},
    {B, B, B, W, W, W, W, W, W, B, B, B, B},
    {B, B, B, W, W, W, W, W, W, B, B, B, B},
    {B, B, B, W, W, W, W, W, W, B, B, B, B},
    {B, B, B, W, W, W, W, W, W, B, B, B, B},
    {B, B, B, W, W, W, W, W, W, B, B, B, B},
};

const cell_t Cell_B17 = { // B17
    {B, B, W, W, W, W, B, B, B, B, B, B, W},
    {B, B, W, W, W, W, B, B, B, B, B, B, W},
    {B, B, W, W, W, W, B, B, B, B, B, B, W},
    {B, B, W, W, W, W, B, B, B, B, B, B, W},
    {B, B, W, W, W, W, B, B, B, B, B, B, W},
    {B, B, W, W, W, W, B, B, B, B, B, B, W},
    {B, B, W, W, W, W, B, B, B, B, B, B, W},
    {B, B, W, W, W, W, B, B, B, B, B, B, W},
    {B, B, W, W, W, W, B, B, B, B, B, B, W},
    {B, B, W, W, W, W, B, B, B, B, B, B, W},
    {B, B, W, W, W, W, B, B, B, B, B, B, W},
    {B, B, W, W, W, W, B, B, B, B, B, B, W},
    {B, B, W, W, W, W, B, B, B, B, B, B, W},
};

const cell_t Cell_B18 = { // B18
    {W, W, W, W, W, B, B, B, B, B, B, B, B},
    {W, W, W, B, B, B, B, B, B, B, B, W, W},
    {W, W, W, B, B, B, B, B, B, B, B, W, W},
    {W, W, W, B, B, B, B, B, B, W, W, W, W},
    {W, W, W, B, B, B, B, B, B, W, W, W, W},
    {W, W, W, B, B, B, B, B, B, B, B, B, B},
    {W, W, W, B, B, B, B, B, B, B, B, B, B},
    {W, W, W, B, B, B, B, B, B, W, W, W, W},
    {W, W, W, B, B, B, B, B, B, W, W, W, W},
    {W, W, W, W, W, B, B, B, B, B, B, B, B},
    {W, W, W, W, W, B, B, B, B, B, B, B, B},
    {W, W, W, W, W, W, W, B, B, B, B, B, B},
    {W, W, W, W, W, W, W, B, B, B, B, B, B},
};

const cell_t Cell_B19 = { // B19
    {B, B, B, B, B, B, B, B, B, B, W, W, W},
    {W, W, W, W, B, B, B, B, B, B, W, W, W},
    {W, W, W, W, B, B, B, B, B, B, W, W, W},
    {W, W, W, W, W, W, B, B, B, B, W, W, W},
    {W, W, W, W, W, W, B, B, B, B, W, W, W},
    {B, B, B, B, B, B, B, B, W, W, W, W, W},
    {B, B, B, B, B, B, B, B, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, W, W, W},
    {B, B, B, B, B, B, B, B, B, B, W, W, W},
};

const cell_t Cell_B20 = { // B20
    {W, B, B, B, B, B, B, W, W, B, B, B, B},
    {W, B, B, B, B, B, B, B, B, B, B, W, W},
    {W, B, B, B, B, B, B, B, B, B, B, W, W},
    {W, B, B, B, B, B, B, B, B, W, W, W, W},
    {W, B, B, B, B, B, B, B, B, W, W, W, W},
    {W, B, B, B, B, B, B, W, W, W, W, W, W},
    {W, B, B, B, B, B, B, W, W, W, W, W, W},
    {W, B, B, B, B, B, B, W, W, W, W, W, W},
    {W, B, B, B, B, B, B, W, W, W, W, W, W},
    {W, B, B, B, B, B, B, W, W, W, W, W, W},
    {W, B, B, B, B, B, B, W, W, W, W, W, W},
    {W, B, B, B, B, B, B, W, W, W, W, W, W},
    {W, B, B, B, B, B, B, W, W, W, W, W, W},
};

const cell_t Cell_B21 = { // B21
    {B, B, B, B, B, B, W, W, W, W, W, W, B},
    {B, B, B, B, B, B, W, W, W, W, B, B, B},
    {B, B, B, B, B, B, W, W, W, W, B, B, B},
    {B, B, B, B, B, B, W, W, W, W, B, B, B},
    {B, B, B, B, B, B, W, W, W, W, B, B, B},
    {B, B, B, B, B, B, W, W, W, W, B, B, B},
    {B, B, B, B, B, B, W, W, W, W, B, B, B},
    {B, B, B, B, B, B, W, W, W, W, B, B, B},
    {B, B, B, B, B, B, W, W, W, W, B, B, B},
    {B, B, B, B, B, B, W, W, W, W, W, W, B},
    {B, B, B, B, B, B, W, W, W, W, W, W, B},
    {B, B, B, B, B, B, W, W, W, W, W, W, W},
    {B, B, B, B, B, B, W, W, W, W, W, W, W},
};

const cell_t Cell_B22 = { // B22
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, W, W, W, W, B, B, B, B},
    {B, B, B, B, B, W, W, W, W, B, B, B, B},
    {B, B, B, W, W, W, W, W, W, B, B, B, B},
    {B, B, B, W, W, W, W, W, W, B, B, B, B},
    {B, B, B, W, W, W, W, W, W, B, B, B, B},
    {B, B, B, W, W, W, W, W, W, B, B, B, B},
    {B, B, B, B, B, W, W, W, W, B, B, B, B},
    {B, B, B, B, B, W, W, W, W, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, B, B, B, B, B, B, B, B, B},
    {W, B, B, B, B, B, B, W, W, B, B, B, B},
    {W, B, B, B, B, B, B, W, W, B, B, B, B},
};

const cell_t Cell_B23 = { // B23
    {B, B, W, W, W, W, W, W, B, B, B, B, B},
    {B, B, W, W, W, W, B, B, B, B, B, B, W},
    {B, B, W, W, W, W, B, B, B, B, B, B, W},
    {B, B, W, W, W, W, B, B, B, B, B, B, W},
    {B, B, W, W, W, W, B, B, B, B, B, B, W},
    {B, B, W, W, W, W, B, B, B, B, B, B, W},
    {B, B, W, W, W, W, B, B, B, B, B, B, W},
    {B, B, W, W, W, W, B, B, B, B, B, B, W},
    {B, B, W, W, W, W, B, B, B, B, B, B, W},
    {B, B, W, W, W, W, W, W, B, B, B, B, B},
    {B, B, W, W, W, W, W, W, B, B, B, B, B},
    {B, B, W, W, W, W, W, W, W, W, B, B, B},
    {B, B, W, W, W, W, W, W, W, W, B, B, B},
};

const cell_t Cell_B24 = { // B24
    {B, W, W, W, W, B, B, B, B, B, B, W, W},
    {W, W, W, W, W, W, W, B, B, B, B, B, B},
    {W, W, W, W, W, W, W, B, B, B, B, B, B},
    {W, W, W, W, W, W, W, B, B, B, B, B, B},
    {W, W, W, W, W, W, W, B, B, B, B, B, B},
    {W, W, W, W, W, W, W, B, B, B, B, B, B},
    {W, W, W, W, W, W, W, B, B, B, B, B, B},
    {W, W, W, W, W, W, W, B, B, B, B, B, B},
    {W, W, W, W, W, W, W, B, B, B, B, B, B},
    {B, W, W, W, W, B, B, B, B, B, B, W, W},
    {B, W, W, W, W, B, B, B, B, B, B, W, W},
    {B, B, B, B, B, B, B, B, B, W, W, W, W},
    {B, B, B, B, B, B, B, B, B, W, W, W, W},
};

const cell_t Cell_TDM = { // TDM
    {W, W, W, W, B, B, B, B, B, W, W, W, W},
    {W, W, B, B, B, W, W, W, B, B, B, W, W},
    {W, B, B, W, W, W, W, W, W, W, B, B, W},
    {W, B, W, B, B, B, B, B, B, W, W, B, W},
    {B, B, W, B, B, W, W, W, B, B, W, B, B},
    {B, W, W, B, B, W, W, W, B, B, W, W, B},
    {B, W, W, B, B, B, B, B, B, W, W, W, B},
    {B, W, W, B, B, B, B, B, W, W, W, W, B},
    {B, B, W, B, B, W, W, B, B, W, W, B, B},
    {W, B, W, B, B, W, W, W, B, B, W, B, W},
    {W, B, B, W, W, W, W, W, W, W, B, B, W},
    {W, W, B, B, B, W, W, W, B, B, B, W, W},
    {W, W, W, W, B, B, B, B, B, W, W, W, W},
};