from itertools import count
import os

files = os.listdir(path="/home/gleb/CXX/BotDialog")
count_strings = 0
import os
import os.path

for dirpath, dirnames, filenames in os.walk("."):
    for filename in [f for f in filenames if f.endswith(".cpp") or f.endswith(".h")]:
        with open(os.path.join(dirpath, filename), "r") as file:
            if("build" not in dirpath):
                print(os.path.join(dirpath, filename))
                count_strings += len(file.readlines())
print("Количество строк в проекте:", count_strings)