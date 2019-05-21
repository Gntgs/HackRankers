class DisjSet():
	"""docstring for DisjSet"""
	def __init__(self):
		self.list = list(range(pow(10,5)+1))
		self.map = {}

	def Merge(self,a,b):
		
		fathera = self.list[a]
		while fathera!= self.list[fathera]:
			fathera = self.list[fathera]
		fatherb = self.list[b]
		while fatherb!= self.list[fatherb]:
			fatherb = self.list[fatherb]
		if fathera == fatherb:
			return
		
		if not self.map.get(fathera):
			self.map[fathera] = 1
		if not self.map.get(fatherb):
			self.map[fatherb] = 1

		if self.map[fathera] > self.map[fatherb]:
			self.list[fatherb] = fathera
			self.map[fathera] += self.map[fatherb]
		else:
			self.list[fathera] = fatherb
			self.map[fatherb] += self.map[fathera]

	def Query(self,a):
		fathera = self.list[a]
		while fathera!= self.list[fathera]:
			fathera = self.list[fathera]
		if not self.map.get(fathera):
			self.map[fathera] = 1
		return self.map[fathera]


def Op(opData):
	if opData[0] == 'Q':
		print(ds.Query(int(opData[1])))
	else:
		ds.Merge(int(opData[1]),int(opData[2]))

if __name__ == "__main__":
	N,Q = input().split(" ")
	N = int(N)
	Q = int(Q)
	ds = DisjSet()
	for i in range(Q):
		Op(input().split(" "))