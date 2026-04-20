import random

bomb = random.randint(1,100)
guess = int(input())
while guess != bomb:
    if guess < bomb:
        print("small")
    else:
        print("Big")
    guess = int(input())
if guess == bomb:
    print("good job")

