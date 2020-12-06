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
bool Editor::loadDoc(std::ifstream& fs) {

}
bool Editor::saveDoc(std::ofstream& fs) {

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
