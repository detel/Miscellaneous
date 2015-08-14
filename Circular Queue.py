size = input()
for x in xrange(size):
    amountOfPetrol,distance = map(int,raw_input().split())
    data.append(amountOfPetrol-distance)

fuel = data[0]
start,end = 0,1

while end != start or fuel < 0:
    while end != start and fuel < 0:
        fuel -= data[start]
        start = (start+1)%size
    fuel += data[end]
    end = (end+1)%size

print start
