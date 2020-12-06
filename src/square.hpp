// Киреев Александр Константинович 206
#pragma once
#include "figure.hpp"
#include "dot.hpp"
#include <iostream>
#include <string>
#include <vector>

class Square: public Figure {
    public:
        Square() = default;
        Square(const Dot& center, const Dot& d);
        Square(const Square& s);
        Square(std::istream& is);
        void Input(std::istream& is) override;
        Dot getCenter() const override;
        void print(std::ostream& os) const override;
        double getArea() const override;
        std::string getType() const override;
        void getCoords(std::vector<Dot>& dots) const override;
        ~Square() = default;
    private:
        Dot _center, _d;
};

std::ostream& operator<<(std::ostream& os, const Square& s); 
