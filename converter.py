import numpy as np

out = open('res/rnn_res', 'w')

def print_matrix(mat):
	for i in np.arange(mat.shape[0]):
		for j in np.arange(mat.shape[1]):
			out.write(str(float(mat[i][j])) + " ")
	out.write("\n")

npzfile = np.load(open('res/params.npz', 'r'))
Wxh, Whh, Why = npzfile['arr_0'], npzfile['arr_1'], npzfile['arr_2']
bh, by = npzfile['arr_3'], npzfile['arr_4']
ix_to_char = npzfile['arr_5']

hidden_size = bh.shape[0]
vocab_size = by.shape[0]

out.write(str(hidden_size) + ' ' + str(vocab_size) + '\n')
for i in range(vocab_size):
	out.write(chr(int(round(ix_to_char[i]))))
out.write('\n')


print_matrix(Wxh)
print_matrix(Whh)
print_matrix(Why)
print_matrix(bh)
print_matrix(by)
