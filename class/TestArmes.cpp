#define BOOST_TEST_MODULE ArmesTestModule
#include <boost/test/included/unit_test.hpp>
#include <memory>
#include <vector>

// Présumons que les classes Ennemi, Joueur, Projectile, et Point sont définies ailleurs
#include "Armes/Armes.hpp"
#include "Armes/CorpsaCorps.hpp"
#include "Armes/Distance.hpp"
#include "Personnages/Ennemi.hpp"
#include "Personnages/Joueurs.hpp"
#include "Armes/Projectile.cpp"
#include "declaration.hpp"

struct ArmesTestFixture {
    std::shared_ptr<CorpsaCorps> corpsACorps;
    std::shared_ptr<Distance> distance;
    std::vector<std::shared_ptr<Ennemi>> ennemis_shared;
    std::vector<std::shared_ptr<Joueur>> joueurs_shared;
    std::vector<Ennemi*> ennemis;  // Vecteur de pointeurs bruts pour les tests
    std::vector<Joueur*> joueurs;  // Vecteur de pointeurs bruts pour les tests
    std::vector<Projectile> projectiles;

    ArmesTestFixture() {
        // Initialisation des armes avec des paramètres fictifs
        corpsACorps = std::make_shared<CorpsaCorps>(1, Salles(), 0);
        distance = std::make_shared<Distance>(1, Salles(), 0);
        // Exemple d'initialisation fictive pour les vecteurs de pointeurs partagés
        ennemis_shared.push_back(std::make_shared<Ennemi>());
        joueurs_shared.push_back(std::make_shared<Joueur>());

        // Construction des vecteurs de pointeurs bruts
        for (auto& e : ennemis_shared) ennemis.push_back(e.get());
        for (auto& j : joueurs_shared) joueurs.push_back(j.get());
    }
};

BOOST_FIXTURE_TEST_SUITE(ArmesTestSuite, ArmesTestFixture)

BOOST_AUTO_TEST_CASE(TestDegats) {
    BOOST_CHECK_CLOSE(corpsACorps->getDegats(), 50.0, 0.01);
}

BOOST_AUTO_TEST_CASE(TestAttaqueCorpsACorps) {
    corpsACorps->attaque(ennemis, joueurs, *corpsACorps, projectiles);
    BOOST_CHECK_EQUAL(projectiles.size(), 1);
}

BOOST_AUTO_TEST_CASE(TestAttaqueDistance) {
    distance->attaque(ennemis, joueurs, *distance, projectiles);
    BOOST_CHECK_EQUAL(projectiles.size(), 1);
}

BOOST_AUTO_TEST_CASE(TestAjouterArmeInventaire) {
    corpsACorps->ajouterArmeInventaire(distance);
    BOOST_CHECK_EQUAL(corpsACorps->inventaire.size(), 1);
}

BOOST_AUTO_TEST_SUITE_END()