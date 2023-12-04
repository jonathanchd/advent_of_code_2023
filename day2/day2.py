def validate(line):
    splt = line.split(";")
    for game in splt:
        comp = game.split(",")
        for color in comp:
            color = color.strip()
            color = color.split(" ")
            if (color[1] == "red" and int(color[0]) > 12):
                return False
            if (color[1] == "green" and int(color[0]) > 13):
                return False
            if (color[1] == "blue" and int(color[0]) > 14):
                return False
    return True

def partTwo(line):
    red = 0
    green = 0
    blue = 0
    splt = line.split(";")
    for game in splt:
        comp = game.split(",")
        for color in comp:
            color = color.strip()
            color = color.split(" ")
            if (color[1] == "red"):
                red = max(red, int(color[0]))
            if (color[1] == "green"):
                green = max(green, int(color[0]))
            if (color[1] == "blue"):
                blue = max(blue, int(color[0]))
    return red * green * blue

ans = 0
anspt2 = 0
with open("day2input.txt", "r") as file:
    lines = file.readlines()
    ctr = 0
    for line in lines:
        ctr += 1
        line = line[line.find(":") + 1:]
        if validate(line):
            ans += ctr
        anspt2 += partTwo(line)
print(ans)
print(anspt2)