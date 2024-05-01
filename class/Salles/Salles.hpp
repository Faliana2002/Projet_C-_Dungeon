#ifndef SALLES_HPP
#define SALLES_HPP

#include "../point.hpp"
class Salles {
private:
	Point center;
	Rectangle & contour;
	
public:
    void waitForExit() =0;
    //on ajoute les 3 fonctions d'affichage, une pour chaque forme, qui seront hérité dans les 2 renderer
    void afficheLine(const Line& line) =0;
    void afficheCircle(const Circle& circle) =0;
    void afficheRectangle(const Rectangle& rectangle) =0;

};


#endif // SALLES_HPP
