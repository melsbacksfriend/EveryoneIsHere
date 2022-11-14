#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <cstring>
#include <cstdint>
#include <limits>

uint64_t process(std::string path, uint32_t count, uint32_t offset, uint32_t freq, uint32_t valSize)
{
    uint64_t size = 0;
    std::ifstream in(path, std::ios::binary);
    if (in.is_open())
    {
        in.seekg(0, std::ios::end);
        int fileSize = in.tellg();
        in.seekg(0, std::ios::beg);
        char* buf = new char[fileSize];
        in.read(buf, fileSize);
        for (uint32_t i = 0; i < count; i++)
        {
            char* temp = new char[8];
            memset(temp, 0, 8);
            for (int j = 0; j < valSize; j++)
            {
                temp[j] = buf[offset + (i * freq) + j];
            }
            size += *(reinterpret_cast<uint64_t*>(temp));
            delete[] temp;
        }
        delete[] buf;
    }
    in.close();
    return size;
}

int main(int argc, char* argv[])
{
    int baseIndex = 10;
    int countIndex = 10;
    uint32_t offset = std::numeric_limits<uint32_t>::max();
    uint32_t freq = 0;
    uint32_t count = 0;
    uint32_t valSize = 0;
    int valSizeIndex = 10;
    std::string filename;
    int filenameIndex = 10;
    int freqIndex = 10;
    if (argc != 10)
    {
        goto argError;
    }
    for (int i = 0; i < argc; i++)
    {
        if (!strcmp(argv[i], "-o") && i < (argc - 1) && strcmp(argv[i + 1], "-n") && strcmp(argv[i + 1], "-f") && strcmp(argv[i + 1], "-s"))
        {
            baseIndex = i + 1;
        }
        if (!strcmp(argv[i], "-n") && i < (argc - 1) && strcmp(argv[i + 1], "-o") && strcmp(argv[i + 1], "-f") && strcmp(argv[i + 1], "-s"))
        {
            countIndex = i + 1;
        }
        if (!strcmp(argv[i], "-f") && i < (argc - 1) && strcmp(argv[i + 1], "-o") && strcmp(argv[i + 1], "-n") && strcmp(argv[i + 1], "-s"))
        {
            freqIndex = i + 1;
        }
        if (!strcmp(argv[i], "-s") && i < (argc - 1) && strcmp(argv[i + 1], "-o") && strcmp(argv[i + 1], "-n") && strcmp(argv[i + 1], "-f"))
        {
            valSizeIndex = i + 1;
        }
        if (i > 0 && strcmp(argv[i], "-n") && strcmp(argv[i], "-o") && strcmp(argv[i], "-s") && strcmp(argv[i], "-f") && strcmp(argv[i - 1], "-n") && strcmp(argv[i - 1], "-o") && strcmp(argv[i - 1], "-f") && strcmp(argv[i - 1], "-s"))
        {
            filenameIndex = i;
        }
    }
    if (baseIndex == 10 || countIndex == 10 || filenameIndex == 10 || freqIndex == 10 || valSizeIndex == 10)
    {
        goto argError;
    }
    filename = argv[filenameIndex];
    offset = static_cast<uint32_t>(atoi(argv[baseIndex]));
    count = static_cast<uint32_t>(atoi(argv[countIndex]));
    freq = static_cast<uint32_t>(atoi(argv[freqIndex]));
    valSize = static_cast<uint32_t>(atoi(argv[valSizeIndex]));
    std::cout << process(filename, count, offset, freq, valSize) << "\n";
    return 0;
    argError:
        std::cout << "Usage:\n\tEveryoneIsHere -f <countFreq> -o <baseOffset> -n <count> -s <sizeInBytes> <filename>\n";
        return -1;
}
