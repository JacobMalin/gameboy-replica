if __name__ == "__main__":
	max_value = 25
	code = "BN"

	l = []
	for i in range(1, max_value+1):
		if i < 10: l.append("{}{}".format(code, i))
		else: l.append("{}{}".format(code[:1], i))

	print(", ".join(l) + ",")

