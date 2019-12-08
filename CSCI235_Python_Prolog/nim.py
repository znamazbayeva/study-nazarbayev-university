
import random
import time

class CantMove( Exception ) :

   def __init__( self, reason ) : 
      self. __reason = reason

   def __repr__( self ) :
      return "unable to find a move: {}". format( self.__reason )


class Nim :
   def __init__( self, startstate ) :
      self. state = startstate


   # Goal is to be unambiguous : 

   def __repr__( self ) :
      printing = ""
      incr = 1
      for x in (self.state):
         printing = printing + str(incr)
         printing = printing + "      : " 
         for i in range(x):
            printing = printing + "1 "
         incr +=1
         printing = printing + "\n"
      return printing


   # Return sum of all rows:

   def sum( self ) :
      sum1 = 0
      for x in (self.state):
         sum1 = sum1 + x
      return sum1


   # Return nimber (xor of all rows): 

   def nimber( self ) :
      sum2 = 0
      for x in (self.state):
         sum2 = sum2 ^ x
      return sum2 #not a binary



   # Make a random move, raise a CantMove if
   # there is nothing left to remove. 

   def randommove( self ) :
      numb = self.sum()
      if numb == 0:
         raise CantMove("no sticks left")
      else:
         rand = random.randrange(0, len(self.state))
         while self.state[rand] == 0:
            rand = random.randrange(0, len(self.state))      
         rand1 = random.randrange(0, self.state[rand])
         self.state[rand] = rand1


   # Try to force a win with misere strategy.
   # This functions make a move, if there is exactly
   # one row that contains more than one stick.
   # In that case, it makes a move that will leave
   # an odd number of rows containing 1 stick.
   # This will eventually force the opponent to take the
   # last stick.
   # If it cannot obtain this state, it should raise
   # CantMove( "more than one row has more than one stick" )

   def removelastmorethantwo( self ) :
      count = 0
      count1 = 0
      c1 = 1
      for x in self.state:
         if x > 1:
            count += 1
            c1 = x
         if x == 1:
            count1 += 1
      if count > 1 or count < 1:
         raise CantMove("more than one row has more than one stick")
      else:
         if (count1 + 1) % 2 == 1:
            self.state[self.state.index(c1)] = 1
         else:
            self.state[self.state.index(c1)] = 0


   # Try to find a move that makes the nimber zero.
   # Raise CantMove( "nimber is already zero" ), if the
   # nimber is zero already.

   def makenimberzero( self ) :
      la = []
      num_ha = self.nimber()
      if num_ha == 0:
         raise CantMove("nimber is already zero")
      else:
         for x in range(0, len(self.state)):
            if (self.state[x] ^ num_ha) < self.state[x]:
               la.append(x)
         rand_number1 = random.choice(la)
         self.state[rand_number1] = self.state[rand_number1] ^ num_ha

         # while True:
         #    rand_number2 = random.randrange(0, len(self.state))
         #    if self.state[rand_number2] ^ num_ha < self.state[rand_number2]:
         #       self.state[rand_number2] = 0
         #       break
  
 
   def optimalmove( self ) :
      count2 = 0
      # while True:
      for x in self.state:
         if x > 1:
            count2 += 1
      if count2 == 1:
         self.removelastmorethantwo( )
      elif self.nimber() != 0:
         self.makenimberzero( )
      else:
         self.randommove( )


   # Let the user make a move. Make sure that the move
   # is correct. This function never crashes, not
   # even with the dumbest user in the world. 
           
   def usermove( self ) : 
      state1 = 1
      state2 = 1
      while state1 or state2:
         var1 = int(input("Select a row: "))
         if type(var1) != int or var1 <= 0 or var1 > len(self.state):
            print("Please type again: ")
         else:
            state1 = False
         var2 = int(input("Select a number of sticks: "))
         if type(var2) != int or var2 > self.state[var1-1] or var2 < 0 or var2 == self.state[var1-1]:
            print("Please type again: ")
         else:
            state2 = False
            self.state[var1 - 1] = var2

 
def play( ) :
   st = Nim( [ 1, 2, 3, 4, 5, 6 ] )
   turn = "user"
   while st. sum( ) > 1 :
      if turn == "user" :
         print( "\n" )
         print( st )
         print( "hello, user, please make a move" ) 
         st. usermove( )
         turn = "computer"
      else :
         print( "\n" )
         print( st )
         print( "now i will make a move\n" ) 
         print( "thinking" )
         for r in range( 15 ) :
            print( ".", end = "", flush = True )
            time. sleep( 0.1 ) 
         print( "\n" )
           
         st. optimalmove( ) 
         turn = "user"

   print( "\n" )
   if turn == "user" : 
      print( "you lost\n" )
   else :
      print( "you won\n" )
play()