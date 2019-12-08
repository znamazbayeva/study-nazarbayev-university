from numbers import *

def gcd(n1, n2):
	if n1 == 0 and n2 == 0:
		raise ArithmeticError("gcd(0,0) does not exist")
	else:
		while (n2):
			n1, n2 = n2, n1 % n2
		if n1 < 0:
			n1 *= -1
		return n1

class Rational( Number ) :
	def __init__( self, num, denom = 1 ) :
		self. num = num 
		self. denom = denom

		self. normalize( )

	def normalize ( self ):
		if self.denom < 0:
			self.num, self.denom = -self.num, -self.denom
		numb = gcd( self.num, self.denom)
		if numb != 0:
			self.num = self.num // numb
			self.denom = self.denom // numb
		 #gcd 2/4 to 1/2

	def __repr__(self):
		repr1 = ""
		# if self.num < 0 or self.denom < 0:
		# 	repr1 += "-"
		if self.denom != 1:
			repr1 = repr1 + str(self.num) + "/" + str(self.denom)
		else:
			repr1 = repr1 + str(self.num)
		return repr1 # 3/1 

	def __neg__( self ) :
		return Rational(-self.num, self.denom)

	def __add__( self, other ) :
		if not isinstance(other, Rational):
			other = Rational(other, 1)
		return Rational((self.num * other.denom + self.denom * other.num), (self.denom * other.denom))

	def __sub__( self, other ) :
		if not isinstance(other, Rational):
			other = Rational(other, 1)
		other = other.__neg__()
		return self.__add__(other)
# For both methods holds: It must be possible to # add/subtract a number to a rational. Use
# isinstance( , ) for this purpose.
	def __radd__( self, other ) :
		return self.__add__(other)

	def __rsub__( self, other ) :
		return self.__sub__(other)
# # So that it will be possible to add/subtract a rational # to a number.

	def __mul__( self, other ) :
		if not isinstance(other, Rational):
			other = Rational(other, 1)
		# normalize
		return Rational((self.num * other.num), (self.denom * other.denom))

	def __truediv__( self, other ) :
		if not isinstance(other, Rational):
			other = Rational(other, 1)
		return Rational((self.num * other.denom), (self.denom * other.num))
		
	def __rmul__( self, other ) :
		return self.__mul__(other)

	def __rtruediv__( self, other ) :
		return self.__truediv__(other)

	def __eq__( self, other ) :
		if not isinstance(other, Rational):
			other = Rational(other, 1)
		return self.num == other.num and self.denom == other.denom

	def __ne__( self, other ) :
		if not isinstance(other, Rational):
			other = Rational(other, 1)
		# if self.num != other.num or self.denom != other.denom:
		# 	return True
		# else:
		# 	return False
		return not (self.__eq__(other))

	def __lt__( self, other ) : 
		if not isinstance(other, Rational):
			other = Rational(other, 1)
		return self.num*other.denom < other.num*self.denom

	def __gt__( self, other ) : 
		if not isinstance(other, Rational):
			other = Rational(other, 1)
		return other.__lt__(self)

	def __le__( self, other ) : 
		if not isinstance(other, Rational):
			other = Rational(other, 1)
		return not other.__lt__(self)

	def __ge__( self, other ) :
		if not isinstance(other, Rational):
			other = Rational(other, 1)
		return not self.__lt__(other)


def test():
	r = Rational(1, -3)
	r1 = Rational(0, 3)
	print(r != r1)
test()
