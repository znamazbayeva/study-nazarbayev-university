// Minimax algorithm
#Assignment 3
from as3_tree import Tree

class Result:
	def __init__(self, sol=[], val=-1000):
			self.solution = sol
			self.value = val
			
class MNX:
	def __init__(self, data_list):
		self.tree = Tree()	
		self.tree.init_tree(data_list)
		self.root = self.tree.root
		self.currentNode = None
		self.successors = []	
		return
        
	def terminalTest(self, node):
		assert node is not None
		return len(node.children) == 0

	def utilityChecking(self, node):
		assert node is not None
		return node.value

	def getChildren(self, node):
		assert node is not None
		return node.children

	def minimax(self):
		terminal_val = self.max_v(self.root)	
		res=Result();
		traversed = []
		solut = []
		queue = [[self.root]]
		while queue:
			sol = queue.pop(0)
			node = sol[-1]
			if node not in traversed:
				traversed.append(node)
				leaves = self.getChildren(node)
				leaves = list(leaves)
				leaves.reverse()
				for leaf in leaves:
					if leaf.value == terminal_val:
						path = list(sol)
						path.append(leaf)
						if self.terminalTest(leaf):
							solut = path
						queue.append(path)
		derive = []
		for sola in solut:
			derive.append(sola.Name)


#################  Return the solution here  #################
		res.value=terminal_val #you put the best terminal value for root node here
		res.solution=derive#you put the solution_array here
#################  Return the solution here  #################

		return res


	def max_v(self, node):
		self.currentNode = node		
		if self.terminalTest(node):
			return self.utilityChecking(node)		
		max_v = -1000 #we use 1000 as the initial_maximum value
		deeper_layer = self.getChildren(node)
		for deeper_node in deeper_layer:
			max_v = max(max_v, self.min_v(deeper_node))
			node.value = max_v
		return max_v

	def min_v(self, node):
		self.currentNode = node		
		if self.terminalTest(node):
			return self.utilityChecking(node)
		min_v = 1000 #we use -1000 as the initial_minimum value
		deeper_layer = self.getChildren(node)
		for deeper_node in deeper_layer:
			min_v = min(min_v, self.max_v(deeper_node))
			node.value = min_v
		return min_v
