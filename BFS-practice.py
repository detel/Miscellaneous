from collections import deque

def limits(i, j, r, c):
	return i >= 0 and j >= 0 and i < r and j < c

if __name__ == '__main__':

	graph, queue = [], deque()
	dx, dy = [-1, 1, 0, 0], [0, 0, -1, 1]

	r,c = map(int,raw_input().split())
	for i in range(r):
		graph.append(list(raw_input()))

	
	for i in range(r):
		for j in range(c):
			if graph[i][j] == '.':
				queue.append((i,j))
				graph[i][j] = 'B'
				while queue:
					x,y = queue.pop()
					for k in range(4):
						if limits(x + dx[k], y + dy[k], r, c) and graph[x + dx[k]][y + dy[k]] == '.':
							if graph[x][y] == 'W':
								graph[x + dx[k]][y + dy[k]] = 'B'
							elif graph[x][y] == 'B':
								graph[x + dx[k]][y + dy[k]] = 'W'
							queue.append((x + dx[k], y + dy[k]))

	for i in range(r):
		print ''.join(graph[i])
