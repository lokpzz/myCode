a = 1
while a <= 9:
    b = 1
    while b <= a:
        print(f"{b} * {a} = {a*b}\t", end="")
        b += 1
    print()
    a += 1
