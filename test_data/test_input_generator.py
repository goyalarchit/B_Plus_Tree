import numpy as np

l = []

with open('input.txt','w') as o:

	l = [int(np.random.randint(low = -1000000000, high = 1000000001, size = 1)) for i in range(10)]

	for i in l:
		o.write('INSERT '+str(i)+'\n')

	queries = ['INSERT', 'FIND', 'COUNT', 'RANGE']

	for i in range(100000):

		num = int(np.random.randint(low = 0, high = 4, size = 1))

		if num == 0:
			c = int(np.random.randint(low = -1000000000, high = 1000000001, size = 1))
			if c not in l:
				o.write(queries[num]+' '+str(c)+'\n')

		elif num == 1:
			c = int(np.random.randint(low = 0, high = 101, size = 1))
			if c > 50:
				c = int(np.random.randint(low = -1000000000, high = 1000000001, size = 1))
			else:
				c = l[int(np.random.randint(low = 0, high = len(l), size = 1))]

			o.write(queries[num]+' '+str(c)+'\n')

		elif num == 2:
			c = int(np.random.randint(low = 0, high = 101, size = 1))
			if c > 50:
				c = int(np.random.randint(low = -1000000000, high = 1000000001, size = 1))
			else:
				c = l[int(np.random.randint(low = 0, high = len(l), size = 1))]

			o.write(queries[num]+' '+str(c)+'\n')

		else:
			lo = int(np.random.randint(low = -1000000000, high = 1000000001, size = 1))
			h = int(np.random.randint(low = lo, high = 1000000001, size = 1))

			o.write(queries[num]+' '+str(lo)+' '+str(h)+'\n')