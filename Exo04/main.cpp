#include <iostream>
#include <string>
#include <exception>


class MontantInvalideException : public std::exception {
private:
    std::string message;

public:
    explicit MontantInvalideException(double montant) {
        message = "Erreur : Montant invalide (" + std::to_string(montant) + "). Le montant doit etre superieur a 0.";
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class SoldeInsuffisantException : public std::exception {
private:
    std::string message;

public:
    SoldeInsuffisantException(double retraitDemande, double soldeActuel) {
        message = "Erreur : Solde insuffisant ! Retrait demande : " +
                  std::to_string(retraitDemande) + " €, Solde disponible : " +
                  std::to_string(soldeActuel) + " €.";
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class Compte {
private:
    std::string titulaire;
    double solde;

public:
    Compte(const std::string& nom, double soldeInitial)
        : titulaire(nom), solde(soldeInitial) {}

    void deposer(double montant) {
        if (montant <= 0) {
            throw MontantInvalideException(montant);
        }
        solde += montant;
        std::cout << "Depot reussi de " << montant << " €. Nouveau solde : " << solde << " €." << std::endl;
    }

    void retirer(double montant) {
        if (montant <= 0) {
            throw MontantInvalideException(montant);
        }
        if (montant > solde) {
            throw SoldeInsuffisantException(montant, solde);
        }
        solde -= montant;
        std::cout << "Retrait reussi de " << montant << " €. Nouveau solde : " << solde << " €." << std::endl;
    }

    double getSolde() const {
        return solde;
    }
};

int main() {
    Compte monCompte("Alice", 100.0);

    std::cout << "--- Solde initial : " << monCompte.getSolde() << " € ---\n" << std::endl;

    struct Operation {
        char type;
        double montant;
    };

    Operation operations[] = {
        {'D', 40.0},
        {'R', 50.0},
        {'D', -10.0},
        {'R', 500.0},
        {'R', -15.0}
    };

    for (const auto& op : operations) {
        try {
            if (op.type == 'D') {
                std::cout << "[Tentative de depot de " << op.montant << " €]" << std::endl;
                monCompte.deposer(op.montant);
            } else if (op.type == 'R') {
                std::cout << "[Tentative de retrait de " << op.montant << " €]" << std::endl;
                monCompte.retirer(op.montant);
            }
        }
        catch (const MontantInvalideException& e) {
            std::cout << "  [Attrape] " << e.what() << std::endl;
        }
        catch (const SoldeInsuffisantException& e) {
            std::cout << "  [Attrape] " << e.what() << std::endl;
        }
        catch (const std::exception& e) {
            std::cout << "  [Erreur inattendue] " << e.what() << std::endl;
        }
        std::cout << std::endl;
    }

    std::cout << "--- Solde final : " << monCompte.getSolde() << " € ---" << std::endl;

    return 0;
}
