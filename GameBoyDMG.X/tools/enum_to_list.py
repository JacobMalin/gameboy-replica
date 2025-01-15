if __name__ == '__main__':
	with open("tools/enum.txt", "r") as enum:
		text = enum.read()
	
	ls = text.split(',')
	ls = list(map(lambda n: "Cell_" + n[-3:], ls))

	with open("tools/list.txt", "w") as out:
		count = 1
		out.write('    extern const cell_t ')
		for item in ls[:-1]:
			if count == 0: out.write('')
			out.write(item)
			count += 1
			if count == 6:
				count = 0
				out.write(',\n            ')
			elif item is not ls[-2]:
				out.write(', ')
		out.write(';')