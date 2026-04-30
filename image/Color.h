#pragma once

class Color {
public:
    double R = 0;
    double G = 0;
    double B = 0;

    Color(double R = 0, double G = 0, double B = 0);
    void Clamp();
};