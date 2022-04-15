import subprocess
import sys
from termcolor import colored

x2 = []
expected = sys.argv[2]
for char in expected:
    x2.append(char)



a2 = []
a = sys.argv[1]

for char in a:
    a2.append(char)

badnum = 0
x = 0
check = []
good = []

for char in a2:
    if x2[x] == char:
        check.append(colored(char, "blue"))
    else:
        check.append(colored(char, "red"))
        badnum = x
    x = x + 1
x = 0
for char in x2:
    if a2[x] == char:
        good.append(colored(char, "blue"))
    else:
        good.append(colored(char, "green"))
    x = x + 1
    

bad = ''.join(check)
expected2 = ''.join(good)
spaces = " " * int(badnum - 1)
print("")
if a2 != x2:
    print(":(")
    print(bad)
    print(spaces + "/\\")
    spaces2 = " " * int(badnum - len("bad") / 3)
    print(spaces2 + "bad")
else:
    print(":)")
    print(bad)
    print("\n")



print(f"expected: \n{expected2}")