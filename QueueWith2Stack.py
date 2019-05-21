class Stack():
	def __init__(self):
		self.list = []
		self.top = 0
		self.base = 0
	def Pop(self):
		if self.top <= self.base :
			return None
		else:
			res = self.list[self.top-1]
			self.top -= 1
			return res
	def Push(self,data):
		if self.top >= len(self.list):
			self.list.append(None)
		self.list[self.top] = data
		self.top+=1

	def Top(self):
		return self.list[self.top-1]

	def IsEmpty(self):
		return self.top <= self.base
	def Size(self):
		return self.top - self.base
	def Dump(self):
		print("Dump-->:")
		for x in range(self.base,self.top):
			print(self.list[x])
class Queue():
	def __init__(self):
		self.s1 = Stack()
		self.s2 = Stack()
		# self.front = s2
		# self.tail  =  s1

	def Enqueue(self,data):
		self.s1.Push(data)
		
	def Dequeue(self):
		if not self.s2.IsEmpty():
			return self.s2.Pop()
		else:
			while (not self.s1.IsEmpty()):
				self.s2.Push(self.s1.Pop())
			return self.s2.Pop()
		# self.head = self.s2.Top()
		#return ret
	def Front(self):
		if not self.s2.IsEmpty():
			return self.s2.Top()
		else:
			while (not self.s1.IsEmpty()):
				self.s2.Push(self.s1.Pop())
			return self.s2.Top()

def Opera(opData):
	opType = opData[0]
	if opType == "1":
		q.Enqueue(opData[1])
	elif opType == "2":
		q.Dequeue()
	else:
		print(q.Front())
if __name__ == "__main__":
	q = Queue()
	N = int(input())
	for i in range(N):
		str_ = input()
		sl = str_.split(" ")
		Opera(sl)