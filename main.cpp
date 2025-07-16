#include <fstream>
#include <iostream>
int main(int argc, char *argv[]) {
    bool quit = false;
    int size;
    int screenx;
    int screeny;
    char enter;
    std::ifstream infile(argv[1]);
    if (!infile) {
        std::cout << "error 0x01" << std::endl;
        std::cin >> enter;
        return 1;
    }
    infile >> size;
    infile >> screenx;
    infile >> screeny;
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
    delete[] arr;
    std::cin >> enter;
    return (0);
}