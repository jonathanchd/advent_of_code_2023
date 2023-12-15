ans = 0
boxes = [[] for i in range(256)]
with open("day15input.txt", 'r') as file:
    s = file.readline().split(",")
    for inp in s:
        if '-' in inp:
            box = 0
            for char in inp.split('-')[0]:
                box += ord(char)
                box *= 17
                box = box % 256
            for i in range(len(boxes[box])):
                if boxes[box][i] == -1:
                    continue
                if inp.split('-')[0] in boxes[box][i][0]:
                    boxes[box][i] = -1
                    break
        else:
            box = 0
            for char in inp.split('=')[0]:
                box += ord(char)
                box *= 17
                box = box % 256
            found = False
            for i in range(len(boxes[box])):
                if boxes[box][i] == -1:
                    continue
                if inp.split('=')[0] in boxes[box][i][0]:
                    boxes[box][i][1] = int(inp.split('=')[1])
                    found = True
                    break
            if not found:
                boxes[box].append([inp.split('=')[0], int(inp.split('=')[1])])

for i in range(len(boxes)):
    if len(boxes[i]) == 0:
        continue
    slot = 1
    lenPower = 0
    for lens in boxes[i]:
        if lens == -1:
            continue
        lenPower += (i + 1) * slot * lens[1]
        slot += 1
    ans += lenPower
print(ans)