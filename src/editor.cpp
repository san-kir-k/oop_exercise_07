#include "editor.hpp"


Editor::~Editor() {
    for (auto s: saved) {
        if (s.type == 'd') {
            delete s.f;
        }
    }
    for (auto d : docs) {
        for (auto f: d) {
            delete f;
        }
    }
}
void Editor::createNewDoc() {
    docs.push_back(std::vector<Figure*>());
    saved.push_back({});
    page++;
}
void Editor::loadDoc(std::ifstream& fs) {
    Dot center;
    Dot node;
    char type;
    std::vector<Figure*> newDoc;
    while (true) {
        fs.read((char*)&type, sizeof(char));
        if (type == 'E') {
            break;
        }
        if (fs.bad()) {
            std::cerr << "Unable to read from file\n";
            return;
        } 
        fs.read((char*)&center, sizeof(Dot));
        if (fs.bad()) {
            std::cerr << "Unable to read from file\n";
            return;
        } 
        fs.read((char*)&node, sizeof(Dot));
        if (fs.bad()) {
            std::cerr << "Unable to read from file\n";
            return;
        } 
        Figure* f;
        if (type == 'S') {
            f = new Square(center, node);
        } else if (type == 'O') {
            f = new Octagon(center, node);
        } else {
            f = new Triangle(center, node);
        }
        newDoc.push_back(f);
    }
    createNewDoc();
    docs[page] = newDoc;
}
void Editor::saveDoc(std::ofstream& fs) {
    for (auto f: docs[page]) {
        std::vector<Dot> dots;
        f->getCoords(dots);
        Dot center = f->getCenter();
        std::string type = f->getType();
        char charType;
        if (type == "Triangle") {
            charType = 'T';
        } else if (type == "Square") {
            charType = 'S';
        } else {
            charType = 'O';
        }
        fs.write((char*)&charType, sizeof(char));
        if (fs.bad()) {
            std::cerr << "Unable to write in file\n";
            return;
        } 
        fs.write((char*)&center, sizeof(Dot));
        if (fs.bad()) {
            std::cerr << "Unable to write in file\n";
            return;
        }
        fs.write((char*)&dots[0], sizeof(Dot));
        if (fs.bad()) {
            std::cerr << "Unable to write in file\n";
            return;
        }   
    }
    char endOfFile = 'E';
    fs.write((char*)&endOfFile, sizeof(char));
    if (fs.bad()) {
        std::cerr << "Unable to write in file\n";
        return;
    } 
} 
void Editor::createPrimitive(std::istream& is, char type) {
    if (docs.empty()) {
        // ошибка
        return;
    }
    Figure* f;
    if (type == 'T') {
        f = new Triangle(is); 
    } else if (type == 'O') {
        f = new Octagon(is);
    } else {
        f = new Square(is);
    }
    docs[page].push_back(f);
    if (saved[page].type == 'd') {
        delete saved[page].f;
    }
    saved[page].type = 'c';
    saved[page].f = f;
}
void Editor::deletePrimitive() {
    if (docs.empty()) {
        // ошибка
        return;
    }
    size_t lastIdx = docs[page].size() - 1;
    if (lastIdx < 0) {
        // ошибка
        return;
    }
    Figure* f = docs[page][lastIdx];
    docs[page].pop_back();
    if (saved[page].type == 'd') {
        delete saved[page].f;
    }
    saved[page].type = 'd';
    saved[page].f = f;
}
void Editor::print() {
    if (docs.empty()) {
        std::cout << "There are no any documents\n";
        return;
    }
    std::cout << "=========================DOCUMENT===========================\n";
    for (auto f: docs[page]) { 
        std::cout << ">>Next figure is " << f->getType() << ": " << std::endl;
        std::cout << "Center coords is: " << f->getCenter() << "\n";
        f->print(std::cout);
        std::cout << "\n";
    }
    std::cout << "======================END=OF=DOCUMENT=======================\n";
}
bool Editor::undo() {
    if (saved[page].type == 'u') {
        return false;
    }
    if (saved[page].type == 'c') {
        docs[page].pop_back();
        delete saved[page].f;
        saved[page].f = nullptr;
        saved[page].type = 'u';
    } if (saved[page].type == 'd') {
        docs[page].push_back(saved[page].f);
        saved[page].f = nullptr;
        saved[page].type = 'u';
    }
    return true;
}
void Editor::switchDoc(size_t newPage) {
    if (newPage < 0 && newPage >= docs.size()) {
        // ошибка
        return;
    }
    page = newPage;
}
