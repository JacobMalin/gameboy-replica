/* 
 * File:   cell.h
 * Author: Jacob Malin
 *
 * Created on November 14, 2024, 5:37 AM
 */

#ifndef CELL_H
#define	CELL_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <avr/io.h>

#include "sd.h"

#define CELL_WIDTH 13

#define CELLS_PER_BLOCK 12

    typedef enum {
        W, // White
        G, // Gray
        D, // Dark gray
        B, // Black
    } __attribute__((__packed__)) color_e;

    typedef color_e cell_t[CELL_WIDTH][CELL_WIDTH];

    typedef enum {
        /* Test */
        ___, // The test cell. A left dark gray line and a gray bottom line with 
        // a white background

        /* Solids */
        BK_, // A black cell
        WH_, // A white cell
        GY_, // A gray cell

        /* Lines */
        OVL, // A gray overline with a white background
        UDL, // A white underline with a black background
        LLN, // A black line on the left with a white background
        VLN, // A vertical black line in the center with a white background
        LWL, // A white left line with a black background

        /* Letters */
        // Black letters with a white background
        A__, B__, C__, D__, E__, F__, G__, H__, I__, J__, K__, L__, M__, N__,
        O__, P__, Q__, R__, S__, T__, U__, V__, W__, X__, Y__, Z__,
        // Gray letters with a white background
        A_G, B_G, C_G, E_G, F_G, O_G, P_G, T_G, Y_G,

        /* Symbols */
        // Black numbers with a white background
        NB0, NB1, NB2, NB3, NB4, NB5, NB6, NB7, NB8, NB9,
        // Gray numbers with a white background
        G_0, G_1, G_2, G_3, G_4, G_5, G_6, G_7, G_8, G_9,
        CPY, // A black copyright symbol with a white background
        PLY, // A black play symbol with a white background
        DSH, // A black dash with a white background
        DSG, // A gray dash with a white background
        DT1, DT2, DT3, // Black dots with a white background
        PRD, // A black period with a white background
        CMA, // A black comma with a white background
        QOT, // A black double quote with a white background
        PDQ, // A black double quote and a period with a white background
        XXX, // A black x symbol with a white background

        /* TETRIS title */
        FM1, FM2, FM3, FM4, FM5, FM6, FM7, FM8, // The tetris title frame
        // The tetris title
        TS1, TS2, TS3, TS4, TS5, TS6, TS7, TS8, TS9, T10, T11, T12, T13, T14,
        T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28,
        T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42,
        T43, T44, T45, T46, T47, T48,

        /* Moscow scene */
        SKY, // The sky of Moscow
        ST1, ST2, // A small and large star
        MN1, MN2, MN3, MN4, // The moon
        // Foreground Moscow
        MW1, MW2, MW3, MW4, MW5, MW6, MW7, MW8, MW9, M10, M11, M12, M13, M14,
        M15, M16, M17, M18, M19, M20, M21, M22,
        BG1, BG2, BG3, BG4, BG5, BG6, // Background Moscow buildings

        /* N*ntendo logo */
        ND1, ND2, ND3, ND4, ND5, ND6, // The N*ntendo logo

        /* Menu */
        MBG, // Menu background
        MB1, MB2, MB3, MB4, MB5, MB6, MB7, MB8, // Menu border
        // Round menu border
        RB1, RB2, RB3, RB4, RB5, RB6, RB7, RB8, RB9, R10, R11, R12,
        // Square menu border
        SB1, SB2, SB3, SB4, SB5, SB6, SB7, SB8, SB9, S10, S11,
        // Gray middle section of the square menu border
        GB1, GB2, GB3, GB4, GB5,

        /* Tetrominoes */
        TI1, TI2, TI3, TI4, TI5, TI6,
        TMJ, TML, TMO, TMS, TMT, TMZ,

        /* Game */
        BK1, BK2, BK3, BK4, BK5, BK6, BK7, BK8, // Bricks
        // Double border
        DB1, DB2, DB3, DB4, DB5, DB6, DB7, DB8, DB9, D10, D11,
        PB1, PB2, PB3, PB4, PB5, PB6, PB7, PB8, // Preview border
        SF1, SF2, SF3, SF4, SF5, SF6, // Score frame
                
        /* Game Over */
        TSN, // Transition block
        OB1, OB2, OB3, OB4, OB5, OB6, OB7, OB8, // Game over border
        DL1, DL2, DL3, // Dot overline
        HRT, // Heart
                
        /* N*ntendo Logo Screen */
        // Big N*ntendo logo
        BN1, BN2, BN3, BN4, BN5, BN6, BN7, BN8, BN9, B10, B11, B12, B13, B14, 
        B15, B16, B17, B18, B19, B20, B21, B22, B23, B24,
        TDM, // A black trademark symbol with a white background

        CELL_E_LEN, // Length of enum
    } __attribute__((__packed__)) cell_e;

    extern const cell_t Cell____, Cell_BK_, Cell_WH_, Cell_GY_, Cell_OVL,
            Cell_UDL, Cell_LLN, Cell_VLN, Cell_LWL, Cell_A__, Cell_B__,
            Cell_C__, Cell_D__, Cell_E__, Cell_F__, Cell_G__, Cell_H__,
            Cell_I__, Cell_J__, Cell_K__, Cell_L__, Cell_M__, Cell_N__,
            Cell_O__, Cell_P__, Cell_Q__, Cell_R__, Cell_S__, Cell_T__,
            Cell_U__, Cell_V__, Cell_W__, Cell_X__, Cell_Y__, Cell_Z__,
            Cell_A_G, Cell_B_G, Cell_C_G, Cell_E_G, Cell_F_G, Cell_O_G,
            Cell_P_G, Cell_T_G, Cell_Y_G, Cell_NB0, Cell_NB1, Cell_NB2,
            Cell_NB3, Cell_NB4, Cell_NB5, Cell_NB6, Cell_NB7, Cell_NB8,
            Cell_NB9, Cell_G_0, Cell_G_1, Cell_G_2, Cell_G_3, Cell_G_4,
            Cell_G_5, Cell_G_6, Cell_G_7, Cell_G_8, Cell_G_9, Cell_CPY,
            Cell_PLY, Cell_DSH, Cell_DSG, Cell_DT1, Cell_DT2, Cell_DT3,
            Cell_PRD, Cell_CMA, Cell_QOT, Cell_PDQ, Cell_XXX, Cell_FM1,
            Cell_FM2, Cell_FM3, Cell_FM4, Cell_FM5, Cell_FM6, Cell_FM7,
            Cell_FM8, Cell_TS1, Cell_TS2, Cell_TS3, Cell_TS4, Cell_TS5,
            Cell_TS6, Cell_TS7, Cell_TS8, Cell_TS9, Cell_T10, Cell_T11,
            Cell_T12, Cell_T13, Cell_T14, Cell_T15, Cell_T16, Cell_T17,
            Cell_T18, Cell_T19, Cell_T20, Cell_T21, Cell_T22, Cell_T23,
            Cell_T24, Cell_T25, Cell_T26, Cell_T27, Cell_T28, Cell_T29,
            Cell_T30, Cell_T31, Cell_T32, Cell_T33, Cell_T34, Cell_T35,
            Cell_T36, Cell_T37, Cell_T38, Cell_T39, Cell_T40, Cell_T41,
            Cell_T42, Cell_T43, Cell_T44, Cell_T45, Cell_T46, Cell_T47,
            Cell_T48, Cell_SKY, Cell_ST1, Cell_ST2, Cell_MN1, Cell_MN2,
            Cell_MN3, Cell_MN4, Cell_MW1, Cell_MW2, Cell_MW3, Cell_MW4,
            Cell_MW5, Cell_MW6, Cell_MW7, Cell_MW8, Cell_MW9, Cell_M10,
            Cell_M11, Cell_M12, Cell_M13, Cell_M14, Cell_M15, Cell_M16,
            Cell_M17, Cell_M18, Cell_M19, Cell_M20, Cell_M21, Cell_M22,
            Cell_BG1, Cell_BG2, Cell_BG3, Cell_BG4, Cell_BG5, Cell_BG6,
            Cell_ND1, Cell_ND2, Cell_ND3, Cell_ND4, Cell_ND5, Cell_ND6,
            Cell_MBG, Cell_MB1, Cell_MB2, Cell_MB3, Cell_MB4, Cell_MB5,
            Cell_MB6, Cell_MB7, Cell_MB8, Cell_RB1, Cell_RB2, Cell_RB3,
            Cell_RB4, Cell_RB5, Cell_RB6, Cell_RB7, Cell_RB8, Cell_RB9,
            Cell_R10, Cell_R11, Cell_R12, Cell_SB1, Cell_SB2, Cell_SB3,
            Cell_SB4, Cell_SB5, Cell_SB6, Cell_SB7, Cell_SB8, Cell_SB9,
            Cell_S10, Cell_S11, Cell_GB1, Cell_GB2, Cell_GB3, Cell_GB4,
            Cell_GB5, Cell_TI1, Cell_TI2, Cell_TI3, Cell_TI4, Cell_TI5,
            Cell_TI6, Cell_TMJ, Cell_TML, Cell_TMO, Cell_TMS, Cell_TMT,
            Cell_TMZ, Cell_BK1, Cell_BK2, Cell_BK3, Cell_BK4, Cell_BK5,
            Cell_BK6, Cell_BK7, Cell_BK8, Cell_DB1, Cell_DB2, Cell_DB3,
            Cell_DB4, Cell_DB5, Cell_DB6, Cell_DB7, Cell_DB8, Cell_DB9,
            Cell_D10, Cell_D11, Cell_PB1, Cell_PB2, Cell_PB3, Cell_PB4,
            Cell_PB5, Cell_PB6, Cell_PB7, Cell_PB8, Cell_SF1, Cell_SF2,
            Cell_SF3, Cell_SF4, Cell_SF5, Cell_SF6, Cell_TSN, Cell_OB1,
            Cell_OB2, Cell_OB3, Cell_OB4, Cell_OB5, Cell_OB6, Cell_OB7,
            Cell_OB8, Cell_DL1, Cell_DL2, Cell_DL3, Cell_HRT, Cell_BN1,
            Cell_BN2, Cell_BN3, Cell_BN4, Cell_BN5, Cell_BN6, Cell_BN7,
            Cell_BN8, Cell_BN9, Cell_B10, Cell_B11, Cell_B12, Cell_B13,
            Cell_B14, Cell_B15, Cell_B16, Cell_B17, Cell_B18, Cell_B19,
            Cell_B20, Cell_B21, Cell_B22, Cell_B23, Cell_B24, Cell_TDM;

    /**
     * Loads cells into SD memory.
     * @param sd_t *SD A pointer to the SD object.
     */
    void Cell(sd_t *SD);

    /**
     * Gets a cell from the SD card.
     * @param sd_t *SD A pointer to the SD object.
     * @param cell_e index The cell id.
     * @return A pointer to the start of the cell_t array.
     */
    const color_e *Cell_get(sd_t *SD, cell_e index);

    /**
     * Writes a list of cells to the SD card.
     * @param sd_t *SD A pointer to the SD object.
     * @param cell_e first_index The first cell id of the list of cells.
     * @param , const color_e *cells A list of cells to store
     */
    void Cell_set(sd_t *SD, cell_e first_index, const color_e *cells[]);

#ifdef	__cplusplus
}
#endif

#endif	/* CELL_H */

