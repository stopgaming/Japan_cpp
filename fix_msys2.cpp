
#include <iostream>
#include <string>
#include <fstream> // for file operations, e.g., reading from a file
#include <string>  // for std::string

static int corrz=9;
int main() {
    std::string oldSubstr[corrz] =
    {
        " -lsfml-graphics ",
        " opengl32 ",
        " glu32 ",
        " -lsfml-window ",
        " -lsfml-system ",
        " -lsfml-audio ",
        " D:/a/msys64/mingw64/lib/libopenal.dll.a ",
        " D:/a/msys64/mingw32/lib/libopenal.dll.a ",
        " -lsfml-network ",
    };
    std::string newSubstr[corrz] =
    {
        " -lsfml-graphics-s ",
        " -lopengl32 ",
        " -lglu32 ",
        " -lsfml-window-s ",
        " -lsfml-system-s ",
        " -lsfml-audio-s ",
        " -lopenal ",
        " -lopenal ",
        " -lsfml-network-s ",
    };

    std::ifstream file("libsflags.tmp"); // replace "filename.txt" with your text file's name and path
    if (!file.is_open()) {
        return 1;   // handle error (e.g., print an error message, throw an exception)
    }
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    int i =0;
    while(1)
    {
        while(1)
        {
            size_t pos = content.find(oldSubstr[i]);
            if (pos != std::string::npos) {
                content.replace(pos, oldSubstr[i].length(), newSubstr[i]);
            }
            else break;
        }
        i++;
        if (i>=corrz) break;
    }


    std::ofstream out("libsflags.tmp");
    out << content;
    out.close();

    return 0;
}

