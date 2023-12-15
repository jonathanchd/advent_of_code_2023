ans = 0
with open("day15input.txt", 'r') as file:
    s = file.readline().split(",")
    for inp in s:
        hash = 0
        for char in inp:
            hash += ord(char)
            hash *= 17
            hash = hash % 256
        ans += hash

print(ans)
