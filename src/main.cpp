// Киреев Александр Константинович 206
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

#include "editor.hpp"

// мануал
void help() {
    std::cout << "Command -- Description\n" <<
                "1 -- Create new document\n" <<
                "2 <filename> -- Load document from file\n" <<
                "3 <filename> -- Save document from file\n" <<
                "4 <type> -- Create new figure (1 -- Octagon, 2 -- Square, 3 -- Triangle)\n" << 
                "5 -- Delete last figure from vector\n" <<
                "6 -- Display document\n" << 
                "7 -- Undo last delete/create\n" <<
                "8 <num> -- Switch document to page <num>\n" <<
                "9 -- Display help\n" <<
                "10 -- End program" << std::endl;
}

void mainLoop() {
    int command = 0, idx = 0, type = 0;
    Editor ed;
    std::string s;
    std::string filename;
    std::ifstream ifs;
    std::ofstream ofs;
    while (std::cout << "Cmd: " && std::cin >> s) {
        if (s.length() > 2) {
            std::cout << "Invalid command." << std::endl;
            continue;
        }
        std::stringstream ss(s);
        ss >> command;
        if (command == 10)
            break;
        switch (command) {
            case 1:
                ed.createNewDoc();
                break;
            case 2:
                std::cin >> filename;
                ifs.open(filename, std::ios::binary);
                if (ifs.fail()) {
                    std::cerr << "ERROR: Unable to open file " << filename << " in read mode\n";
                    break;
                }
                ed.loadDoc(ifs);
            case 3:
                std::cin >> filename;
                ofs.open(filename, std::ios::binary);
                if (ofs.fail()) {
                    std::cerr << "ERROR: Unable to open file " << filename << " in write mode\n";
                    break;
                }
                ed.saveDoc(ofs);
                break;
            case 4:
                std::cin >> type;
                switch (type) {
                    case 1:
                        ed.createPrimitive(std::cin, 'O');
                        break;
                    case 2:
                        ed.createPrimitive(std::cin, 'S');
                        break;
                    case 3:
                        ed.createPrimitive(std::cin, 'T');
                        break;
                    default:
                        std::cout << "Invalid type." << std::endl;
                        break;
                }
                break;
            case 5:
                ed.deletePrimitive();
                break;
            case 6:
                ed.print();
                break;
            case 7:
                ed.undo();
                break;
            case 8:
                std::cin >> idx;
                ed.switchDoc(idx);
                break;
            case 9:
                help();
                break;
            default:
                std::cout << "Invalid command!" << std::endl; 
                break;
        }
    }
}

int main() {
    help();
    mainLoop();
    return 0;
}
