# TODO
import cs50
import math

while True:
    change = cs50.get_float("Enter Change Amount:")
    if change >= 0:
        break

coins = 0
values = [0.25, 0.10, 0.05, 0.01]

for i in values:
    coins += math.trunc(change / i)
    change = round(change % i, 2)

print(coins)