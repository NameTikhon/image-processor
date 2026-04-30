#include "image/Color.h"
#include <algorithm>

Color::Color(double R, double G, double B) : R(R), G(G), B(B) {}

void Color::Clamp() {
    R = std::clamp(R, 0.0, 1.0);
    G = std::clamp(G, 0.0, 1.0);
    B = std::clamp(B, 0.0, 1.0);
}