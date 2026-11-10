#include <iostream>
#include <stdexcept>

double diviser(int a, int b) {
    if (b == 0) {
        throw std::runtime_error("Erreur : Division par zero impossible !");
    }
    return static_cast<double>(a) / b;
}

int main() {
    int casDeTest[][2] = {
        {16, 2},
        {5, 0},
        {30, 3}
    };

    for (const auto& test : casDeTest) {
        int a = test[0];
        int b = test[1];

        try {
            double resultat = diviser(a, b);
            std::cout << a << " / " << b << " = " << resultat << std::endl;
        }
        catch (const std::runtime_error& e) {
            std::cout << e.what() << std::endl;
        }
    }

    return 0;
}
