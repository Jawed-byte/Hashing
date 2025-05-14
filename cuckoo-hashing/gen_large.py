from random import randint
from random import choice

chars = ''.join(chr(i) for i in range(ord('a'), ord('z') + 1))

def gen_rand_str(len):
    s = ""
    for _ in range(len):
        s += choice(chars)
    return s

tests = randint(1, 2)
print(tests)

for _ in range(tests):
    n = 42 * randint(1, 25_000)
    print(n)

    insertions = n // 42
    deletions = n // 42
    lookups = n - insertions - deletions

    for _ in range(n):
        op = randint(0, 2)
        if op == 0 and insertions > 0:
            insertions -= 1
            print(op, gen_rand_str(randint(1, 90)))
        else:
            if op == 0:
                op = randint(1, 2)

            if op == 2 and deletions > 0:
                deletions -= 1
                print(op, gen_rand_str(randint(1, 90)))
            else:
                op = 1
                print(op, gen_rand_str(randint(1, 90)))

