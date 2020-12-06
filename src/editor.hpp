#pragma once
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
        std::vector<lastAction> saved;
        int page;
    public:
        Editor(): saved(), page(-1) {};
        ~Editor();
        void createNewDoc();
        bool loadDoc(std::ifstream& fs);
        bool saveDoc(std::ofstream& fs);   
        void createPrimitive(std::istream& is, char type);
        void deletePrimitive();
        void print();
        bool undo();
        void switchDoc(size_t newPage);
};
