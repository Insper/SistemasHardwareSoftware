import random
import sys

n = int(input())
print(n)
soma = 0
for i in range(n):
    r = random.random()
    print(r)
    soma += r

sys.stderr.write(str(soma) + '\n')
