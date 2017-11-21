#include <iostream>
#include <string>
#include "Manager.h"

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        std::cout << "Usage: run {# of threads}" << std::endl;
		return 0;
    }
    int threadCount = std::stoi(argv[1]);

    Manager manager(threadCount);
    int totalUpdate = manager.join();
    std::cout << "update : " << totalUpdate << std::endl;

    return 0;
}
