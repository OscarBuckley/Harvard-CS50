# TODO
import cs50

height = 0

while not (height <= 8 and height >= 1):
    height = int(cs50.get_int("Height:"))

for i in range(1, height + 1):
    for g in range(i, height):
        print(" ", end="")
    for j in range(0, i):
        print("#", end="")
    print("  ", end="")
    for k in range(0, i):
        print("#", end="")
    print("\n", end="")