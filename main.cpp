#include <fstream>
#include <iostream>
#include <cmath>
#include <cstdlib>
int main(int argc, char *argv[]) {
    bool quit = false;
    int extensioncount;
    bool extensions = false;
    int rta = 0;
    int size;
    int screenx;
    int screeny;
    char enter;
    int* extensionflag;
    bool vstringisdefined = false;
    short int* extensionlength;
    int* extensiontype;
    int mainline;
    int* ext;
    int extlength;
    int code;
    std::string vstring;
    std::string* extensionplace;
    #if defined(_WIN32) || defined(_WIN64)
    std::ifstream checkfile("C:/Program Files/java/jdk-24/bin/javaw.exe");
    if (!checkfile.is_open()) {
        std::cout << "error 0x10" << std::endl;
        std::cin >> enter;
        return 10;
    }
    checkfile.close();
    #else
    std::ifstream checkfile("/bin/java");
    if (!checkfile.is_open()) {
        std::cout << "error 0x10" << std::endl;
        std::cin >> enter;
        return 10;
    }
    checkfile.close();
    #endif
    if (argc == 0) {
        std::cout << "error 0x00" << std::endl;
        std::cin >> enter;
        return 0;
    }
    if (argc > 1) {
        rta = argc - 1;
    }
    std::ifstream infile(argv[1]);
    if (!infile.is_open()) {
        std::cout << "error 0x01" << std::endl;
        std::cin >> enter;
        return 1;
    }
    infile >> extensioncount;
    infile >> size;
    infile >> screenx;
    infile >> screeny;
    if (extensioncount != 0) {
        if (extensioncount == -1) {
            std::cout << "error 0x01e" << std::endl;
            return -1;
        }
        extensions = true;
        extensionflag = new int[extensioncount];
        extensionlength = new short int[extensioncount];
        extensiontype = new int[extensioncount];
        for (int i = 0; i < extensioncount; i++) {
            extensionplace = new std::string[i];
            infile >> extensionflag[i];
            infile >> extensionlength[i];
            int* extensionchar = new int[extensionlength[i]];
            for (int j = 0; j < extensionlength[i]; j++) {
                infile >> extensionchar[i];
                extensionplace[i][j] = static_cast<char>(extensionchar[i]);
            }
            extensiontype[i] = 0;
            for (int p = 2; p < argc; p++) {
                if (argv[p] == extensionplace[i]) {
                    extensiontype[i] = 1;
                }
            }
            delete[] extensionchar;

        }
        
    }

    if (round(size / 4) != size / 4) {
        std::cout << "error 0x04" << std::endl;
        std::cin >> enter;
        return 4;
    }
    if (size / 4 < 256) {
        std::cout << "error 0x02" << std::endl;
        std::cin >> enter;
        return 2;
    }
    int* arr = new int[size];
    for (int i = 0; i < size / 4 - 1 && infile; ++i) {
        infile >> arr[i];
    }
    while(!quit) {
        for (int j = 3; j < size / 4 - 1; j = j + 2) {
            if (extensions) {
                for (int k = 0; k < extensioncount; k++) {
                    if (arr[j] == extensionflag[k]) {
                        if (extensiontype[k] == 0) {
                            mainline = j;
                            std::ifstream extensionfile(extensionplace[k]);
                            if (!extensionfile.is_open()) {
                                std::cout << "error 0x02e" << std::endl;
                                return -2;
                            }
                            extensionfile >> code;
                            if (code != -1) {
                                std::cout << "error 0x01e" << std::endl;
                                return -1;
                            }
                            extensionfile >> extlength;
                            if (round(extlength / 4) != extlength / 4) {
                                std::cout << "error 0x04e" << std::endl;
                                return -4;
                            }
                            ext = new int[extlength];
                            for (int c = 0; c < extlength; c++) {
                                extensionfile >> ext[c];
                            }
                            for (int z = 0; z < extlength; z += 2) {
                                if (ext[z] < extlength / 4 - 1) {
                                    if (ext[z + 1] > extlength) {
                                        std::cout << "error 0x03e" << std::endl;
                                        return -3;
                                    }
                                    ext[ext[z]] = ext[z + 1];
                                }
                                else if (ext[z] == extlength / 4) {
                                    if (ext[z + 1] > extlength) {
                                        std::cout << "error 0x03e" << std::endl;
                                        return -3;
                                    }
                                    z = ext[z + 1] - 2;
                                }
                                else {
                                    arr[ext[z] - extlength] = ext[z + 1];
                                }
                            }
                        continue;
                    }
                }
                    
                    else {
                        std::ifstream rtas(extensionplace[k]);
                        int rtasop;
                        rtas >> rtasop;
                        switch (rtasop) {
                            case (1): {
                                std::cout << static_cast<char>(arr[j+1]);
                                break;
                            }
                            case (2): {
                                std::cin >> enter;
                                arr[arr[j + 1]] = static_cast<int>(enter);
                                break;
                            }
                            case (3): {
                                for (int s = 0; s < arr[j + 1]; s++) {
                                    vstring[s] = static_cast<char>(arr[j + s + 2]);
                                }
                                vstringisdefined = true;
                                break;
                            }
                            case (4): {
                                if (vstringisdefined) {
                                    std::cout << vstring << std::endl;
                                }
                                break;
                                }
                            default: {
                                std::cout << "error 0x05e" << std::endl;
                                std::cin >> enter;
                                return -5;
                            }
                            }
                        }

                    
                    }
                }
            
            
            if (arr[j] < size / 4 - 1) {
                if (arr[j + 1] > size) {
                    std::cout << "error 0x03" << std::endl;
                    std::cin >> enter;
                    return 3;
                }
                arr[arr[j]] = arr[j + 1];
            }
            else if (arr[j] == size / 4) {
                if (arr[j + 1] > size) {
                    std::cout << "error 0x03" << std::endl;
                    std::cin >> enter;
                    return 3;
                }
                j = arr[j + 1] - 2;
            }
            else if (arr[j] < size / 2 - 1) {
                arr[j + 1] += (arr[j] - (size / 4));
            }
            else if (arr[j] < 3 * size / 4) {
                arr[j + 1] -= (arr[j] - (size / 2));
            }
            else if (arr[j] < size - 1) {
                if (arr[j] - (3 * size / 4) != arr[j + 1]) {
                    j += 2;
                }
            }
            else {
                quit = true;
                break;
            }
        }
        for (int k = 0; k < screeny; k++) {
            for (int l = 0; l < screenx; l++) {
                std::cout << static_cast<char>((arr[(screeny * k + l)]) % 256);
            }
        std::cout << std::endl;
        }
        std::cin >> arr[0];
    }
    delete[] extensiontype;
    delete[] arr;
    delete[] extensionflag;
    delete[] extensionlength;
    std::cin >> enter;
    return (0);
}