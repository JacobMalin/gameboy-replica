/* 
 * File:   screen.c
 * Author: Jacob Malin
 *
 * Created on November 14, 2024, 5:37 AM
 */

#include "screen.h"

static screen_e last = SCREEN_E_LEN;
static screen_t buf;

void Screen(sd_t *SD) {
    // Load cells into SD memory.
    Cell(SD);
    
    // Must stay commented out, as these are all already loaded in SD memory
//    Screen_set(SD, SCREEN_COPYRIGHT, Screen_copyright);
//    Screen_set(SD, SCREEN_TITLE, Screen_title);
//    Screen_set(SD, SCREEN_SELECT, Screen_select);
//    Screen_set(SD, SCREEN_A_TYPE_SELECT, Screen_a_type_select);
//    Screen_set(SD, SCREEN_A_TYPE_GAME, Screen_a_type_game);
//    Screen_set(SD, SCREEN_GAME_OVER, Screen_game_over);
//    Screen_set(SD, SCREEN_PAUSED, Screen_paused);
//    Screen_set(SD, SCREEN_LOGO, Screen_logo);
}

const cell_e *Screen_get(sd_t *SD, screen_e index) {
    if (index != last) { // Check cache
        uint32_t block_index = FIRST_SCREEN_BLOCK + index * 2;

        SD_read_block(SD, block_index, (uint8_t *)buf, BLOCK_SIZE);
        SD_read_block(SD, block_index + 1, (uint8_t *)buf + BLOCK_SIZE, 
                sizeof(screen_t) - BLOCK_SIZE);

        last = index;
    }
    
    return *buf;
}

void Screen_set(sd_t *SD, screen_e index, const screen_t screen) {
    uint32_t block_index = FIRST_SCREEN_BLOCK + index * 2;
    
    SD_write_block(SD, block_index, (uint8_t *)screen, BLOCK_SIZE);
    SD_write_block(SD, block_index + 1, (uint8_t *)screen + BLOCK_SIZE, 
            sizeof(screen_t) - BLOCK_SIZE);
}

const screen_t Screen_copyright = {
    {WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_},
    {QOT,T__,M__,WH_,A__,N__,D__,WH_,CPY,NB1,NB9,NB8,NB7,WH_,E__,L__,O__,R__,G__,CMA},
    {WH_,T__,E__,T__,R__,I__,S__,WH_,L__,I__,C__,E__,N__,S__,E__,D__,WH_,T__,O__,WH_},
    {WH_,WH_,WH_,WH_,B__,U__,L__,L__,E__,T__,DSH,P__,R__,O__,O__,F__,WH_,WH_,WH_,WH_},
    {WH_,WH_,WH_,WH_,S__,O__,F__,T__,W__,A__,R__,E__,WH_,A__,N__,D__,WH_,WH_,WH_,WH_},
    {WH_,WH_,WH_,S__,U__,B__,DSH,L__,I__,C__,E__,N__,S__,E__,D__,WH_,T__,O__,WH_,WH_},
    {WH_,WH_,WH_,WH_,WH_,WH_,N__,I__,N__,T__,E__,N__,D__,O__,PRD,WH_,WH_,WH_,WH_,WH_},
    {WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_},
    {WH_,CPY,NB1,NB9,NB8,NB9,WH_,B__,U__,L__,L__,E__,T__,DSH,P__,R__,O__,O__,F__,WH_},
    {WH_,WH_,WH_,WH_,WH_,WH_,S__,O__,F__,T__,W__,A__,R__,E__,PRD,WH_,WH_,WH_,WH_,WH_},
    {WH_,WH_,WH_,CPY,NB1,NB9,NB8,NB9,WH_,ND1,ND2,ND3,ND4,ND5,ND6,WH_,WH_,WH_,WH_,WH_},
    {WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_},
    {A__,L__,L__,WH_,R__,I__,G__,H__,T__,S__,WH_,R__,E__,S__,E__,R__,V__,E__,D__,PRD},
    {WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_},
    {WH_,WH_,O__,R__,I__,G__,I__,N__,A__,L__,WH_,C__,O__,N__,C__,E__,P__,T__,CMA,WH_},
    {WH_,D__,E__,S__,I__,G__,N__,WH_,A__,N__,D__,WH_,P__,R__,O__,G__,R__,A__,M__,WH_},
    {B__,Y__,WH_,A__,L__,E__,X__,E__,Y__,WH_,P__,A__,Z__,H__,I__,T__,N__,O__,V__,PDQ},
    {WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_},
};

const screen_t Screen_title = {
    {BK_,BK_,BK_,BK_,BK_,BK_,BK_,BK_,BK_,BK_,BK_,BK_,BK_,BK_,BK_,BK_,BK_,BK_,BK_,BK_},
    {FM1,FM2,FM2,FM2,FM2,FM2,FM2,FM2,FM2,FM2,FM2,FM2,FM2,FM2,FM2,FM2,FM2,FM2,FM2,FM3},
    {FM4,TS1,TS2,TS3,TS4,TS5,TS6,TS7,TS2,TS3,TS4,TS5,TS8,TS9,T10,T11,T12,T13,T14,FM5},
    {FM4,T15,T16,T17,T18,T19,T20,T21,T16,T17,T18,T19,T22,T23,T24,T25,T26,T27,WH_,FM5},
    {FM4,WH_,T28,T29,WH_,T30,T31,T32,T28,T29,WH_,T30,T33,T34,T35,T36,T37,T38,WH_,FM5},
    {FM4,WH_,T39,T40,WH_,BK_,T41,T42,T39,T40,WH_,BK_,T43,T44,T45,T46,T47,T48,WH_,FM5},
    {FM6,FM7,FM7,FM7,FM7,FM7,FM7,FM7,FM7,FM7,FM7,FM7,FM7,FM7,FM7,FM7,FM7,FM7,FM7,FM8},
    {BK_,SKY,SKY,SKY,SKY,SKY,SKY,SKY,SKY,SKY,SKY,SKY,SKY,SKY,MW1,MW2,SKY,SKY,SKY,BK_},
    {BK_,GY_,GY_,MN1,MN2,GY_,GY_,ST1,GY_,GY_,GY_,GY_,GY_,ST1,MW3,MW4,ST2,GY_,GY_,BK_},
    {BK_,ST1,GY_,MN3,MN4,GY_,GY_,GY_,GY_,ST2,GY_,GY_,GY_,GY_,MW5,MW6,GY_,GY_,GY_,BK_},
    {BK_,GY_,GY_,GY_,GY_,GY_,GY_,GY_,GY_,GY_,GY_,GY_,GY_,MW7,MW8,MW9,M10,M11,M12,BK_},
    {BK_,GY_,GY_,GY_,GY_,ST1,GY_,GY_,GY_,GY_,BG1,BG2,M13,M14,M15,M16,M17,MW3,MW4,BK_},
    {BK_,GY_,GY_,GY_,GY_,GY_,GY_,GY_,GY_,BG2,BG3,BG4,BG5,BG6,M18,M19,M20,M21,M22,BK_},
    {UDL,UDL,UDL,UDL,UDL,UDL,UDL,UDL,UDL,UDL,UDL,UDL,UDL,UDL,UDL,UDL,UDL,UDL,UDL,UDL},
    {WH_,WH_,NB1,P__,L__,A__,Y__,E__,R__,WH_,WH_,WH_,NB2,P__,L__,A__,Y__,E__,R__,WH_},
    {WH_,WH_,OVL,OVL,OVL,OVL,OVL,OVL,OVL,WH_,WH_,WH_,OVL,OVL,OVL,OVL,OVL,OVL,OVL,WH_},
    {WH_,WH_,WH_,WH_,CPY,NB1,NB9,NB8,NB9,WH_,ND1,ND2,ND3,ND4,ND5,ND6,WH_,WH_,WH_,WH_},
    {WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_},
};

const screen_t Screen_select = {
    {MB1,MB2,MB2,MB2,MB2,MB2,MB2,MB2,MB2,MB2,MB2,MB2,MB2,MB2,MB2,MB2,MB2,MB2,MB2,MB3},
    {MB4,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MB5},
    {MB4,MBG,MBG,MBG,RB1,RB2,RB2,RB2,RB2,RB2,RB2,RB2,RB2,RB2,RB3,MBG,MBG,MBG,MBG,MB5},
    {MB4,MBG,MBG,MBG,RB4,G__,A__,M__,E__,WH_,T__,Y__,P__,E__,RB5,MBG,MBG,MBG,MBG,MB5},
    {MB4,MBG,SB1,SB2,RB6,RB7,RB7,RB7,RB7,RB7,RB8,RB7,RB7,RB7,RB9,SB2,SB2,SB3,MBG,MB5},
    {MB4,MBG,SB4,A_G,DSG,T_G,Y_G,P_G,E_G,WH_,LLN,B_G,DSG,T_G,Y_G,P_G,E_G,SB5,MBG,MB5},
    {MB4,MBG,SB6,SB7,SB7,SB7,SB7,SB7,SB7,SB7,SB8,SB7,SB7,SB7,SB7,SB7,SB7,SB9,MBG,MB5},
    {MB4,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MB5},
    {MB4,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MB5},
    {MB4,MBG,MBG,MBG,RB1,RB2,RB2,RB2,RB2,RB2,RB2,RB2,RB2,RB2,RB2,RB3,MBG,MBG,MBG,MB5},
    {MB4,MBG,MBG,MBG,RB4,M__,U__,S__,I__,C__,WH_,T__,Y__,P__,E__,RB5,MBG,MBG,MBG,MB5},
    {MB4,MBG,SB1,SB2,RB6,RB7,RB7,RB7,RB7,RB7,RB8,RB7,RB7,RB7,RB7,RB9,SB2,SB3,MBG,MB5},
    {MB4,MBG,SB4,A_G,DSG,T_G,Y_G,P_G,E_G,WH_,LLN,B_G,DSG,T_G,Y_G,P_G,E_G,SB5,MBG,MB5},
    {MB4,MBG,GB1,GB2,GB2,GB2,GB2,GB2,GB2,GB2,GB3,GB2,GB2,GB2,GB2,GB2,GB2,GB4,MBG,MB5},
    {MB4,MBG,SB4,C_G,DSG,T_G,Y_G,P_G,E_G,WH_,LLN,WH_,O_G,F_G,F_G,WH_,WH_,SB5,MBG,MB5},
    {MB4,MBG,SB6,SB7,SB7,SB7,SB7,SB7,SB7,SB7,SB8,SB7,SB7,SB7,SB7,SB7,SB7,SB9,MBG,MB5},
    {MB4,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MB5},
    {MB6,MB7,MB7,MB7,MB7,MB7,MB7,MB7,MB7,MB7,MB7,MB7,MB7,MB7,MB7,MB7,MB7,MB7,MB7,MB8},
};

const screen_t Screen_a_type_select = {
    {MB1,MB2,MB2,MB2,MB2,MB2,MB2,MB2,MB2,MB2,MB2,MB2,MB2,MB2,MB2,MB2,MB2,MB2,MB2,MB3},
    {MB4,WH_,A__,DSH,T__,Y__,P__,E__,WH_,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MB5},
    {MB4,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MBG,MB5},
    {MB4,MBG,MBG,MBG,MBG,MBG,RB1,RB2,RB2,RB2,RB2,RB2,RB3,MBG,MBG,MBG,MBG,MBG,MBG,MB5},
    {MB4,MBG,MBG,MBG,MBG,MBG,RB4,L__,E__,V__,E__,L__,RB5,MBG,MBG,MBG,MBG,MBG,MBG,MB5},
    {MB4,MBG,MBG,MBG,SB1,SB2,R10,RB7,R11,RB7,R11,RB7,R12,SB2,SB3,MBG,MBG,MBG,MBG,MB5},
    {MB4,MBG,MBG,MBG,SB4,G_0,VLN,G_1,VLN,G_2,VLN,G_3,VLN,G_4,SB5,MBG,MBG,MBG,MBG,MB5},
    {MB4,MBG,MBG,MBG,GB1,GB2,GB5,GB2,GB5,GB2,GB5,GB2,GB5,GB2,GB4,MBG,MBG,MBG,MBG,MB5},
    {MB4,MBG,MBG,MBG,SB4,G_5,VLN,G_6,VLN,G_7,VLN,G_8,VLN,G_9,SB5,MBG,MBG,MBG,MBG,MB5},
    {MB4,MBG,MBG,MBG,SB6,SB7,S10,SB7,S10,SB7,S10,SB7,S10,SB7,SB9,MBG,MBG,MBG,MBG,MB5},
    {MB4,MBG,MBG,MBG,RB1,RB2,RB2,RB2,RB2,RB2,RB2,RB2,RB2,RB2,RB3,MBG,MBG,MBG,MBG,MB5},
    {MB4,MBG,MBG,MBG,RB4,T__,O__,P__,DSH,S__,C__,O__,R__,E__,RB5,MBG,MBG,MBG,MBG,MB5},
    {MB4,SB1,SB2,S11,RB6,RB7,RB7,RB7,RB7,RB7,RB7,RB7,RB7,RB7,RB9,SB2,SB2,SB2,SB3,MB5},
    {MB4,SB4,NB1,VLN,DT1,DT2,DT3,DT1,DT2,DT3,WH_,WH_,DT1,DT2,DT3,DT1,DT2,DT3,SB5,MB5},
    {MB4,SB4,NB2,VLN,DT1,DT2,DT3,DT1,DT2,DT3,WH_,WH_,DT1,DT2,DT3,DT1,DT2,DT3,SB5,MB5},
    {MB4,SB4,NB3,VLN,DT1,DT2,DT3,DT1,DT2,DT3,WH_,WH_,DT1,DT2,DT3,DT1,DT2,DT3,SB5,MB5},
    {MB4,SB6,SB7,S10,SB7,SB7,SB7,SB7,SB7,SB7,SB7,SB7,SB7,SB7,SB7,SB7,SB7,SB7,SB9,MB5},
    {MB6,MB7,MB7,MB7,MB7,MB7,MB7,MB7,MB7,MB7,MB7,MB7,MB7,MB7,MB7,MB7,MB7,MB7,MB7,MB8},
};

const screen_t Screen_a_type_game = {
    {T45,BK1,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,BK1,DB1,DB2,DB2,DB2,DB2,DB2,DB3},
    {T45,BK2,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,BK2,SF1,S__,C__,O__,R__,E__,SF2},
    {T45,BK3,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,BK3,SF3,SF4,SF4,SF4,SF4,SF4,SF5},
    {T45,BK4,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,BK4,WH_,WH_,WH_,WH_,WH_,NB0,WH_},
    {T45,BK5,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,BK5,SF6,D10,D10,D10,D10,D10,D10},
    {T45,BK6,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,BK6,DB1,DB2,DB2,DB2,DB2,DB2,DB3},
    {T45,BK7,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,BK7,DB4,L__,E__,V__,E__,L__,DB5},
    {T45,BK8,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,BK8,DB4,WH_,WH_,WH_,NB0,WH_,DB5},
    {T45,BK1,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,BK1,DB6,DB7,DB7,DB7,DB7,DB7,DB8},
    {T45,BK2,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,BK2,DB4,L__,I__,N__,E__,S__,DB5},
    {T45,BK3,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,BK3,DB4,WH_,WH_,WH_,NB0,WH_,DB5},
    {T45,BK4,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,BK4,DB9,D10,D10,D10,D10,D10,D11},
    {T45,BK5,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,BK5,LWL,PB1,PB2,PB2,PB2,PB2,PB3},
    {T45,BK6,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,BK6,LWL,PB4,WH_,WH_,WH_,WH_,PB5},
    {T45,BK7,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,BK7,LWL,PB4,WH_,WH_,WH_,WH_,PB5},
    {T45,BK8,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,BK8,LWL,PB4,WH_,WH_,WH_,WH_,PB5},
    {T45,BK1,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,BK1,LWL,PB4,WH_,WH_,WH_,WH_,PB5},
    {T45,BK2,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,BK2,LWL,PB6,PB7,PB7,PB7,PB7,PB8},
};

const screen_t Screen_game_over = {
    {___,___,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,___,___,___,___,___,___,___,___},
    {___,___,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,___,___,___,___,___,___,___,___},
    {___,___,WH_,OB1,OB2,OB2,OB2,OB2,OB2,OB2,OB3,WH_,___,___,___,___,___,___,___,___},
    {___,___,WH_,OB4,WH_,WH_,WH_,WH_,WH_,WH_,OB5,WH_,___,___,___,___,___,___,___,___},
    {___,___,WH_,OB4,WH_,G__,A__,M__,E__,WH_,OB5,WH_,___,___,___,___,___,___,___,___},
    {___,___,WH_,OB4,WH_,OVL,OVL,OVL,OVL,WH_,OB5,WH_,___,___,___,___,___,___,___,___},
    {___,___,WH_,OB4,WH_,O__,V__,E__,R__,WH_,OB5,WH_,___,___,___,___,___,___,___,___},
    {___,___,WH_,OB4,WH_,OVL,OVL,OVL,OVL,WH_,OB5,WH_,___,___,___,___,___,___,___,___},
    {___,___,WH_,OB6,OB7,OB7,OB7,OB7,OB7,OB7,OB8,WH_,___,___,___,___,___,___,___,___},
    {___,___,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,___,___,___,___,___,___,___,___},
    {___,___,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,___,___,___,___,___,___,___,___},
    {___,___,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,___,___,___,___,___,___,___,___},
    {___,___,WH_,P__,L__,E__,A__,S__,E__,WH_,WH_,WH_,___,___,___,___,___,___,___,___},
    {___,___,WH_,DL1,DL2,DL3,DL1,DL2,DL3,WH_,WH_,WH_,___,___,___,___,___,___,___,___},
    {___,___,WH_,WH_,T__,R__,Y__,WH_,WH_,WH_,WH_,WH_,___,___,___,___,___,___,___,___},
    {___,___,WH_,WH_,DL1,DL2,DL3,WH_,WH_,WH_,WH_,WH_,___,___,___,___,___,___,___,___},
    {___,___,WH_,WH_,WH_,A__,G__,A__,I__,N__,HRT,WH_,___,___,___,___,___,___,___,___},
    {___,___,WH_,WH_,WH_,DL1,DL2,DL3,DL1,DL2,WH_,WH_,___,___,___,___,___,___,___,___},
};

const screen_t Screen_paused = {
    {___,___,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,___,___,___,___,___,___,___,___},
    {___,___,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,___,___,___,___,___,___,___,___},
    {___,___,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,___,___,___,___,___,___,___,___},
    {___,___,WH_,WH_,WH_,H__,I__,T__,WH_,WH_,WH_,WH_,___,___,___,___,___,___,___,___},
    {___,___,WH_,WH_,WH_,DL1,DL2,DL3,WH_,WH_,WH_,WH_,___,___,___,___,___,___,___,___},
    {___,___,WH_,WH_,S__,T__,A__,R__,T__,WH_,WH_,WH_,___,___,___,___,___,___,___,___},
    {___,___,WH_,WH_,DL1,DL2,DL3,DL1,DL2,WH_,WH_,WH_,___,___,___,___,___,___,___,___},
    {___,___,WH_,WH_,WH_,WH_,T__,O__,WH_,WH_,WH_,WH_,___,___,___,___,___,___,___,___},
    {___,___,WH_,WH_,WH_,WH_,DL1,DL2,WH_,WH_,WH_,WH_,___,___,___,___,___,___,___,___},
    {___,___,WH_,C__,O__,N__,T__,I__,N__,U__,E__,WH_,___,___,___,___,___,___,___,___},
    {___,___,WH_,DL1,DL2,DL3,DL1,DL2,DL3,DL1,DL2,WH_,___,___,___,___,___,___,___,___},
    {___,___,WH_,WH_,WH_,G__,A__,M__,E__,WH_,WH_,WH_,___,___,___,___,___,___,___,___},
    {___,___,WH_,WH_,WH_,DL1,DL2,DL3,DL1,WH_,WH_,WH_,___,___,___,___,___,___,___,___},
    {___,___,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,___,___,___,___,___,___,___,___},
    {___,___,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,___,___,___,___,___,___,___,___},
    {___,___,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,___,___,___,___,___,___,___,___},
    {___,___,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,___,___,___,___,___,___,___,___},
    {___,___,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,___,___,___,___,___,___,___,___},
};

const screen_t Screen_b_type_game = {
    {T45,BK1,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,BK1,DB1,DB2,DB2,DB2,DB2,DB2,DB3},
    {T45,BK2,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,BK2,DB4,L__,E__,V__,E__,L__,DB5},
    {T45,BK3,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,BK3,DB4,WH_,WH_,NB0,WH_,WH_,DB5},
    {T45,BK4,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,BK4,DB6,DB7,DB7,DB7,DB7,DB7,DB8},
    {T45,BK5,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,BK5,DB4,H__,I__,G__,H__,WH_,DB5},
    {T45,BK6,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,BK6,DB4,WH_,WH_,NB0,WH_,WH_,DB5},
    {T45,BK7,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,BK7,DB9,D10,D10,D10,D10,D10,D11},
    {T45,BK8,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,BK8,LWL,BK_,BK_,BK_,BK_,BK_,BK_},
    {T45,BK1,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,BK1,DB1,DB2,DB2,DB2,DB2,DB2,DB3},
    {T45,BK2,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,BK2,DB4,L__,I__,N__,E__,S__,DB5},
    {T45,BK3,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,BK3,DB4,WH_,WH_,WH_,NB0,WH_,DB5},
    {T45,BK4,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,BK4,DB9,D10,D10,D10,D10,D10,D11},
    {T45,BK5,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,BK5,LWL,PB1,PB2,PB2,PB2,PB2,PB3},
    {T45,BK6,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,BK6,LWL,PB4,WH_,WH_,WH_,WH_,PB5},
    {T45,BK7,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,BK7,LWL,PB4,WH_,WH_,WH_,WH_,PB5},
    {T45,BK8,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,BK8,LWL,PB4,WH_,WH_,WH_,WH_,PB5},
    {T45,BK1,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,BK1,LWL,PB4,WH_,WH_,WH_,WH_,PB5},
    {T45,BK2,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,BK2,LWL,PB6,PB7,PB7,PB7,PB7,PB8},
};

const screen_t Screen_logo = {
    {WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_},
    {WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_},
    {WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_},
    {WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_},
    {WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_},
    {WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_},
    {WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_},
    {WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_},
    {WH_,WH_,WH_,WH_,BN1,BN2,BN3,BN4,BN5,BN6,BN7,BN8,BN9,B10,B11,B12,TDM,WH_,WH_,WH_},
    {WH_,WH_,WH_,WH_,B13,B14,B15,B16,B17,B18,B19,B20,B21,B22,B23,B24,WH_,WH_,WH_,WH_},
    {WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_},
    {WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_},
    {WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_},
    {WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_},
    {WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_},
    {WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_},
    {WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_},
    {WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_,WH_},
};