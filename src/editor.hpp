#include <iostream>
#include <vector>
#include <fstream>

#include "figure.hpp"
#include "octagon.hpp"
#include "square.hpp"
#include "triangle.hpp"

class Editor {
    private:
        std::vector<std::vector<Figure*>> docs;
        struct lastAction {
            char type;
            Figure* f;
            lastAction(): type('u'), f(nullptr) {};
            ~lastAction() = default;
        };
        lastAction saved;
        size_t page = 0;
    public:
        Editor() = default;
        ~Editor() {
            if (saved.type == 'd') {
                delete saved.f;
            }
            for (auto d : docs) {
                for (auto f: d) {
                    delete f;
                }
                d.~vector();
            }
            docs.~vector();
        }
        void createNewDoc() {
            docs.push_back(std::vector<Figure*>());
            page++;
        }
        bool loadDoc(std::vector<Figure*>& doc, std::ifstream& fs);
        bool saveDoc(const std::vector<Figure*>& doc, std::ofstream& fs);   
        void createPrimitive(std::istream& is, char type) {
            Figure* f;
            if (type == 'T') {
                f = new Triangle(is); 
            } else if (type == 'O') {
                f = new Octagon(is);
            } else {
                f = new Square(is);
            }
            docs[page].push_back(f);
            if (saved.type == 'd') {
                delete saved.f;
            }
            saved.type = 'c';
            saved.f = f;
        }
        void deletePrimitive() {
            size_t lastIdx = docs[page].size() - 1;
            if (lastIdx < 0) {
                // ошибка
            }
            Figure* f = docs[page][lastIdx];
            docs[page].pop_back();
            if (saved.type == 'd') {
                delete saved.f;
            }
            saved.type = 'd';
            saved.f = f;
        }
        void print() {
            for (auto f: docs[page]) { 
                std::cout << ">>Next figure is " << f->getType() << ": " << std::endl;
                std::cout << "Center coords is: " << f->getCenter() << "\n";
                f->print(std::cout);
            }
        }
        bool undo() {
            if (saved.type == 'u') {
                return false;
            }
            if (saved.type == 'c') {
                docs[page].pop_back();
                delete saved.f;
                saved.f = nullptr;
                saved.type = 'u';
            } if (saved.type == 'd') {
                docs[page].push_back(saved.f);
                saved.f = nullptr;
                saved.type = 'u';
            }
            return true;
        }
        void switchDoc(size_t newPage) {
            page = newPage;
        }
};
