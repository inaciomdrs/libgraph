from random import choice, randint

def generate_matrix(size=10):
	print(size)

	matrix = [[choice([0,1]) for i in range(size)] for i in range(size)]

	for i in range(size):
		matrix[i][i] = 0
		for j in range(i):
			matrix[i][j] = matrix[j][i]

	for line in matrix:
		print(*line)
	
	u = randint(0,size)
	v = u
	while v == u:
		v = randint(0,size)

	print(u)
	print(v)


size = int(input())
generate_matrix(size)