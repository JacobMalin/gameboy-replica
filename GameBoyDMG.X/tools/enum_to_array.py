if __name__ == '__main__':
	with open("tools/enum.txt", "r") as enum:
		text = enum.read()
	
	ls = text.split(',')
	ls = list(map(lambda n: "Cell_" + n[-3:], ls))

	with open("tools/array.txt", "w") as array:
		count = 0
		for item in ls[:-1]:
			if count == 0: array.write('    cell_e first = {}; const color_e *cells[] = {{'.format(item[-3:]))
			array.write("*")
			array.write(item)
			array.write(",")
			count += 1
			if count == 12:
				count = 0
				array.write('};\n')
			else:
				array.write(' ')
		array.write('};')