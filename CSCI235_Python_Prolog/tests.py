from matrix import *
from vector import *
from rational import *

arg1 = Matrix(Rational(1, 2), Rational(1, 3), Rational(-2, 7), Rational(2, 8))
arg2 = Matrix(Rational(-1, 3), Rational(2, 7), Rational(2, 5), Rational(-1, 7))
print(arg1 @ arg2)
print(arg1.inverse())

arg3 = Matrix(Rational(-1, 5), Rational(2, 9), Rational(2, 6), Rational(-1, 8))

print("Matrix multiplication is associative:")
# (m1 ×m2)×m3 = m1 ×(m2 ×m3)
print((arg1 @ arg2) @ arg3 == arg1 @ (arg2 @ arg3))

print("Matrix multiplication with addition is distributive:")
# m1×(m2+m3) = m1×m2+m1×m3
print((arg1 @ arg2) + (arg1 @ arg3) == arg1 @ (arg2 + arg3))
#  (m1+m2)×m3 = m1×m3+m2×m3,
print((arg1 @ arg3) + (arg2 @ arg3) == (arg1 + arg2) @ arg3 )

v = Vector(1, 2)
# m1(m2(v)) = (m1 × m2)(v)
print("Matrix multiplication corresponds to composition of application")
print(arg1(arg2(v)) == (arg1 @arg2)(v))
# det(m1).det(m2) = det(m1 × m2)
if (Matrix.determinant(arg1) * Matrix.determinant(arg2) == Matrix.determinant((arg1 @ arg2))) == True:
    print("Determinant commutes over multiplication")
else:
    raise ValueError("results are different")
# m×inv(m)=I andinv(m)×m=I
ident_matr = Matrix(1, 0, 0, 1)
if arg1 @ arg1.inverse() == ident_matr and arg1.inverse() @ arg1 == ident_matr:
    print("The inverse of matrix is indeed its inverse")
else:
    raise ValueError("results are different")





