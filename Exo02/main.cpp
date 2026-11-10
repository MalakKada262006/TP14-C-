#include <iostream>
#include <string>
#include <exception>

class StockInsuffisantException : public std::exception {
private:
    std::string message;

public:
    StockInsuffisantException(int quantiteDemandee, int stockDisponible) {
        message = "Erreur : Stock insuffisant ! Demande : " +
                  std::to_string(quantiteDemandee) +
                  ", Disponible : " + std::to_string(stockDisponible);
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class Produit {
private:
    std::string nom;
    int stock;

public:
    Produit(const std::string& nomProduit, int stockInitial)
        : nom(nomProduit), stock(stockInitial) {}

    void vendre(int quantite) {
        if (quantite > stock) {
            throw StockInsuffisantException(quantite, stock);
        }
        stock -= quantite;
        std::cout << quantite << " x " << nom << " vendu(s). Stock restant : " << stock << std::endl;
    }

    int getStock() const {
        return stock;
    }
};

int main() {
    Produit ordinateur("Portable hp", 5);

    std::cout << "Stock initial : " << ordinateur.getStock() << std::endl;

    try {
        ordinateur.vendre(3);
    }
    catch (const StockInsuffisantException& e) {
        std::cout << e.what() << std::endl;
    }

    try {
        ordinateur.vendre(4);
    }
    catch (const StockInsuffisantException& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
