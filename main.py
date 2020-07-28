def read_fasta(fp):
        name, seq = None, []
        for line in fp:
            line = line.rstrip()
            if line.startswith(">"):
                if name: yield (name, ''.join(seq))
                name, seq = line, []
            else:
                seq.append(line)
        if name: yield (name, ''.join(seq))

def given_matrices_inserter(filename):
	try:	
		data = open(filename, 'r')
		dimensions = data.readline()
		try:
			n = int(dimensions)
		except ValueError:
			print("Wrong file")
			exit()
		letters = data.readline()
		letters = letters.replace('\n', '')
		letters_arr = letters.split(' ')
		score_matrix = np.zeros((n,n))
		for i in range(0,n):
			arr = data.readline().split(" ")
			for j in range(0,n):
				score_matrix[i][j] = float(arr[j])
		return letters_arr, score_matrix
	except FileNotFoundError:
		print("There is no matrix file.")
		exit()		

import numpy as np

def write_to_file(filename, value):
    with open(filename, "w+") as f:
        f.write(value)

def match_score(c1, c2, m, mm, letters, score_matrix):
	mapped_values = {}
	for i, v in enumerate(letters):
		mapped_values[v] = i
	a = mapped_values[c1]
	b = mapped_values[c2]
	return score_matrix[a][b]

def global_alignment(first, second, letters, matrix, protein):
	match, mismatch, gap, ind = 1,-1,-1,-1
	if ind == 0 and protein == 0:
		letters, matrix = matrix_chooser(letters, match, mismatch)
	n = len(first)
	m = len(second)
	backtrack = [[(-1,1) for j in range(m+1)] for i in range(n+1)]
	s = [[0 for j in range(m+1)] for i in range(n+1)]

	for i in range(1, n+1):
		s[i][0] = s[i-1][0] + gap
		backtrack[i][0] = (i-1, 0)
	for j in range(1, m+1):
		s[0][j] = s[0][j-1] + gap
		backtrack[0][j] = (0, j-1)

	for i in range(1, n+1):
		for j in range(1, m+1):
			s[i][j] = max(s[i-1][j] + gap, s[i][j-1] + gap, s[i-1][j-1] + match_score(first[i-1], second[j-1], match, mismatch, letters, matrix))
			if s[i][j] == s[i-1][j] + gap:
				backtrack[i][j] = (i-1, j)
			elif s[i][j] == s[i][j-1] + gap:
				backtrack[i][j] = (i, j-1)
			else:
				backtrack[i][j] =  (i-1, j-1)

	first_p = ""
	second_p = ""
	i = n
	j = m
	while (i,j) != (0,0):
		if backtrack[i][j] == (i-1, j-1):
			first_p = first[i-1] + first_p
			second_p = second[j-1] + second_p
		elif backtrack[i][j] == (i-1, j):
			first_p = first[i-1] + first_p
			second_p = '-' + second_p
		else:
			first_p = '-' + first_p
			second_p = second[j-1] + second_p
		(i, j) = backtrack[i][j]

	return first_p, second_p, s[n][m]

file1 = 'AGP04929.1.fasta'
file2 = 'AYN64561.1.fasta'

with open(f'./data/protein/{file1}') as fp:
    A = ''
    for name, seq in read_fasta(fp):
        A += seq

with open(f'./data/protein/{file2}') as fp:
    B = ''
    for name, seq in read_fasta(fp):
        B += seq

protein = 1
letters, matrix = given_matrices_inserter('pam250.txt')
resA, resB, score = global_alignment(A, B, letters, matrix, protein)
write_to_file(f'./outputs/{file1}.txt', resA)
write_to_file(f'./outputs/{file2}.txt', resB)
print(f'Score: {score}')
