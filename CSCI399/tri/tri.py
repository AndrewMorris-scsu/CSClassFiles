import math

a = int(math.pow(2,14))
asqrd = math.pow(a,2)
count = 0

for b in range(int(a), int((int(math.pow(a,2)-1)/2))):
    bsqrd = math.pow(b,2)
    csqrd = bsqrd + asqrd
    if int(math.sqrt(csqrd)) == math.sqrt(csqrd):
        count = count + 1

print(str(count))

