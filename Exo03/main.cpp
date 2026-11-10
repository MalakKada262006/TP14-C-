#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

void lireFichier(const std::string& nomFichier) {
    std::ifstream fichier(nomFichier);

    if (!fichier.is_open()) {
        throw std::runtime_error("Erreur : Impossible d ouvrir le fichier \"" + nomFichier + "\". Fichier introuvable ou acces refuse.");
    }

    std::cout << "--- Contenu du fichier : " << nomFichier << " ---" << std::endl;
    std::string ligne;

    while (std::getline(fichier, ligne)) {
        std::cout << ligne << std::endl;
    }

    fichier.close();
}

int main() {
    std::cout << "Test 1 : Fichier inexistant" << std::endl;
    try {
        lireFichier("fichier_inexistant.txt");
    }
    catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    std::string nomFichierExemple = "exemple.txt";

    std::ofstream fichierTest(nomFichierExemple);
    if (fichierTest.is_open()) {
        fichierTest << "Ligne 1 : Bienvenue dans la gestion des fichiers C++ !" << std::endl;
        fichierTest << "Ligne 2 : Les exceptions permettent une gestion propre des erreurs." << std::endl;
        fichierTest.close();
    }

    std::cout << "Test 2 : Fichier existant" << std::endl;
    try {
        lireFichier(nomFichierExemple);
    }
    catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
