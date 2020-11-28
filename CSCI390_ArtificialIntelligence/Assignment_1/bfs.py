#Author: Dinh-Mao Bui, Anh-Tu Nguyen
#Rule of traversing: Alphabetical ordered, then left to right, 
#Points: 2
def traverse(tree, init):    	
	queue = [init]
	traversed = []
	while queue:
		'''
			Student fixes the loopy path from here to the end of this function
		'''

		node = queue.pop(0)
		if node not in traversed:
			traversed.append(node)
			leaves = tree[node]

			for leaf in leaves:
				queue.append(leaf)
		# traversed.append(node)
		# leaves = tree[node]
		# for leaf in leaves:
		# 	if leaf not in traversed:
		# 		queue.append(leaf)
		# 		traversed.append(leaf)
	return traversed

#Points: 3
def pathfinder(tree, init, goal):
	traversed = []
	queue = [[init]]
	if init == goal:
		return "No kidding, pls"
	while queue:
		sol = queue.pop(0)
		node = sol[len(sol)-1]

		if node not in traversed:

			traversed.append(node)
			leaves = tree[node]
			for leaf in leaves:

				path = list(sol)
				path.append(leaf)
				if leaf == goal:
					return path
				queue.append(path)
				# print(queue)
	return "No such path exists"
 
