from random import randint
from random import choice

chars = [chr(o) for o in range(ord('a'), ord('z') + 1)]

def gen_rand_str(length):
    s = ""
    s += choice(chars)
    return s

tests = randint(5, 5)
print(tests)

for _ in range(tests):
    n = randint(20_000, 20_000)
    print(n)
    
    for _ in range(n):
        s = gen_rand_str(randint(1, 2_000))
        print(s)