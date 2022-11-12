import os
import shutil

source_folder = r"data\\"
destination_folder = r"bin\data\\"

os.system("c++ src/*.cpp -o bin/Frostbite.exe -lmingw32 -lSDL2main -lSDL2_ttf -lSDL2 -lSDL2_image -lSDL2_mixer -lgdi32 -I include -I C:/SDL2-w64/include -L C:/SDL2-w64/lib")

for file_name in os.listdir(source_folder):
    source = source_folder + file_name
    destination = destination_folder + file_name

    if os.path.isfile(source):
        shutil.copy(source, destination)