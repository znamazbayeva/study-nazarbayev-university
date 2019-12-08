import random

def guess():
    upperbound = 10
    secret = random.randrange(upperbound)

    print( "hello, please guess my secret number" )
    print( f"it lies between 0 and {upperbound-1}\n" )
    #
    attempts = 1;
    mess = f"guess {attempts}: "
    inputstring = input( mess )
    guess = int( inputstring )
    if (guess > secret):
        print('Too high\n')
    if (guess < secret):
        print("Too low\n")
    attempts += 1
    # i copied the code above because of the secret!=while
    while secret != guess:
        try :
            mess = f"guess {attempts}: "
            inputstring = input( mess )
            guess = int( inputstring )
            attempts += 1
            if (guess > secret):
                print('Too high\n')
            if (guess < secret):
                print("Too low\n")
            
            # Transforms into int.
        except ValueError:
            print( "{inputstring} is not a number" )
    print( f"secret = {secret}" )    

guess()
