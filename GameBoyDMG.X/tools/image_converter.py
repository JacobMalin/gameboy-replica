#!/usr/bin/env python

"""
File:   image_converter.py
Author: Jacob Malin

Created on October 31, 2024, 1:22 PM
"""

from PIL import Image
import numpy as np
from pprint import pprint

__author__ = "Jacob Malin"

WARNING = '\033[31m'
ENDC = '\033[0m'

CELL_WIDTH = 13
GRID_ROWS = 18
GRID_COLS = 20

COLORS = {
	(248, 248, 248, 255): "W",
	(168, 168, 168, 255): "G",
	(96, 96, 96, 255): "D",
	(0, 0, 0, 255): "B",
}

CODE_LIST = [
	"BK_",
	"FM1",
	"FM2",
	"FM3",
	"FM4",
	"TS1",
	"TS2",
	"TS3",
	"TS4",
	"TS5",
	"TS6",
	"TS7",
	"TS8",
	"TS9",
	"T10",
	"T11",
	"T12",
	"T13",
	"T14",
	"FM5",
	"T15",
	"T16",
	"T17",
	"T18",
	"T19",
	"T20",
	"T21",
	"T22",
	"T23",
	"T24",
	"T25",
	"T26",
	"T27",
	"WH_",
	"T28",
	"T29",
	"T30",
	"T31",
	"T32",
	"T33",
	"T34",
	"T35",
	"T36",
	"T37",
	"T38",
	"T39",
	"T40",
	"T41",
	"T42",
	"T43",
	"T44",
	"T45",
	"T46",
	"T47",
	"T48",
	"FM6",
	"FM7",
	"FM8",
	"SKY",
	"MW1",
	"MW2",
	"GY_",
	"MN1",
	"MN2",
	"ST1",
	"MW3",
	"MW4",
	"ST2",
	"MN3",
	"MN4",
	"MW5",
	"MW6",
	"MW7",
	"MW8",
	"MW9",
	"M10",
	"M11",
	"M12",
	"BG1",
	"BG2",
	"M13",
	"M14",
	"M15",
	"M16",
	"M17",
	"BG3",
	"BG4",
	"BG5",
	"BG6",
	"M18",
	"M19",
	"M20",
	"M21",
	"M22",
	"UDL",
	"PLY",
	"NB1",
	"P__",
	"L__",
	"A__",
	"Y__",
	"E__",
	"R__",
	"NB2",
	"OVL",
	"CPY",
	"NB9",
	"NB8",
	"ND1",
	"ND2",
	"ND3",
	"ND4",
	"ND5",
	"ND6",
	"MB1",
	"MB2",
	"MB3",
	"MB4",
	"MBG",
	"MB5",
	"RB1",
	"RB2",
	"RB3",
	"RB4",
	"G__",
	"M__",
	"T__",
	"RB5",
	"SB1",
	"SB2",
	"RB6",
	"RB7",
	"RB8",
	"RB9",
	"SB3",
	"SB4",
	"DSH",
	"LLN",
	"B_G",
	"DSG",
	"T_G",
	"Y_G",
	"P_G",
	"E_G",
	"SB5",
	"SB6",
	"SB7",
	"SB8",
	"SB9",
	"U__",
	"S__",
	"I__",
	"C__",
	"GB1",
	"GB2",
	"GB3",
	"GB4",
	"C_G",
	"O_G",
	"F_G",
	"MB6",
	"MB7",
	"MB8",
	"V__",
	"R10",
	"R11",
	"R12",
	"NB0",
	"VLN",
	"G_1",
	"G_2",
	"G_3",
	"G_4",
	"GB5",
	"G_5",
	"G_6",
	"G_7",
	"G_8",
	"G_9",
	"S10",
	"O__",
	"S11",
	"DT1",
	"DT2",
	"DT3",
	"NB3",
	"BK1",
	"DB1",
	"DB2",
	"DB3",
	"BK2",
	"DB4",
	"DB5",
	"BK3",
	"BK4",
	"DB6",
	"DB7",
	"DB8",
	"BK5",
	"H__",
	"BK6",
	"BK7",
	"DB9",
	"D10",
	"D11",
	"BK8",
	"LWL",
	"TI1",
	"TI2",
	"TI3",
	"N__",
	"TI4",
	"TMJ",
	"TML",
	"TI5",
	"TMO",
	"PB1",
	"PB2",
	"PB3",
	"TI6",
	"PB4",
	"PB5",
	"TMT",
	"TMS",
	"TMZ",
	"PB6",
	"PB7",
	"PB8",
	"SF1",
	"SF2",
	"SF3",
	"SF4",
	"SF5",
	"SF6",
	"OB1",
	"OB2",
	"OB3",
	"OB4",
	"OB5",
	"OB6",
	"OB7",
	"OB8",
	"DL1",
	"DL2",
	"DL3",
	"HRT",
	"BN1",
	"BN2",
	"BN3",
	"BN4",
	"BN5",
	"BN6",
	"BN7",
	"BN8",
	"BN9",
	"B10",
	"B11",
	"B12",
	"TDM",
	"B13",
	"B14",
	"B15",
	"B16",
	"B17",
	"B18",
	"B19",
	"B20",
	"B21",
	"B22",
	"B23",
	"B24",
]

def process_row(a, row_index):
	cells = [[[] for i in range(CELL_WIDTH)] for i in range(GRID_COLS)]

	i_start = row_index * CELL_WIDTH
	for i in range(i_start, i_start + CELL_WIDTH):
		for col_index in range(GRID_COLS):
			j_start = col_index * CELL_WIDTH
			for j in range(j_start, j_start + CELL_WIDTH):
				# print(i, j)
				color = tuple(map(int, a[i][j]))
				cells[col_index][i - i_start].append(COLORS[color])

	return cells

def unspool(path, cells):
	new_cells = {}
	cell_count = 0
	with Image.open(path) as im:
		a = np.asarray(im)
		output = [[] for i in range(GRID_ROWS)]
		
		for i in range(GRID_ROWS):
			row_cells = process_row(a, i)
			for cell in row_cells:
				tupled_cell = tuple(map(tuple,cell))
				if tupled_cell not in cells:
					cells[tupled_cell] = len(cells)
				if tupled_cell not in new_cells:
					cell_count += 1
					new_cells[tupled_cell] = len(new_cells)
				output[i].append(cells[tupled_cell])

		print("count: " + str(cell_count))
		return output
	
def to_code(num):
	if num < len(CODE_LIST) and CODE_LIST[num] != '___':
		return CODE_LIST[num]
	return str(num).rjust(3, "_")

	
def to_code_with_warn(num):
	if num < len(CODE_LIST) and CODE_LIST[num] != '___':
		return CODE_LIST[num]
	return warn(str(num).rjust(3, "_"))

def warn(s):
	return WARNING + s + ENDC

def image_write(images, cells):
	with open("tools/screen.txt", "w") as fp:
		for image in images:
			converted = unspool(image, cells)
			print('screen_t {} = {{'.format(image))
			fp.write('screen_t {} = {{\n'.format(image))
			for i in range(GRID_ROWS):
				str_list = ",".join(map(to_code,converted[i]))
				warn_str_list = ",".join(map(to_code_with_warn,converted[i]))
				print("    {{{}}},".format(warn_str_list))
				fp.write("    {{{}}},\n".format(str_list))
			print('};\n')
			fp.write('};\n\n')

def cell_write(cells):
	with open("tools/cell.txt", "w") as fp:
		for i, cell in enumerate(cells):
			code = to_code(i)

			fp.write('const cell_t Cell_{0} = {{ // {0}\n'.format(code))
			for j in range(CELL_WIDTH):
				str_list = ", ".join(cell[j])
				fp.write("    {{{}}},\n".format(str_list))
			fp.write('};\n\n')

if __name__ == "__main__":
	images = [
		"images/scaled-Tetris-title.png",
		"images/scaled-Tetris-select.png",
		"images/scaled-Tetris-a-type-select.png",
		"images/scaled-Tetris-b-type-game.png",
		"images/scaled-Tetris-a-type-game.png",
		"images/scaled-Tetris-game-over.png",
		"images/scaled-N*ntendo-logo.png",
	]
	cells = {}

	image_write(images, cells)
	cell_write(cells)