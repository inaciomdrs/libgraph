from random import choice

def generate_matrix(size=10):
	matrix = [[choice([0,1]) for i in range(size)] for i in range(size)]

	for i in range(size):
		matrix[i][i] = 0
		for j in range(i):
			matrix[i][j] = matrix[j][i]

	for line in matrix:
		print(*line)

size = int(input())
generate_matrix(size)