#ifndef SALLES_HPP
#define SALLES_HPP

#include "../point.hpp"
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>

class Salles {
//classe Salles, plusieurs chose à disposition
private:
//le vecteur de porte donne le point en haut à gauche de chacune des portes, la première etant l'entré, la seconde la sortie
	std::vector<Point> door;
	std::map<Point, int> pointMap;          // Map pour stocker les points avec leurs occurrences (l'entier associé)
	std::map<Point, int> pointMapInverted;  // Map inversée pour stocker les points avec leurs occurrences
	//chaque obstacle sera défini par son point en haut à gauche, et fera une taille 1 de large, 1 de haut
	std::vector<Point> obst;
//la liste contourList permet de fixer les points dans l'ordre du contour afin de tracer se dernier
	std::vector<Point> contourList;         // Points qui composent le contour
//la valeur n nous donne le nombre de point constituant le contour de la salle
	int n;
//les 3 tableaux textures permette de stocker dans l'ordre respectivement les dessins de sol accessible, les dessins de zones non accessibles, les délimitations de mur
    sf::Texture texture[8];
    sf::Texture wall[5];
    sf::Texture wallsection[8];

public:
//les sprite sont présente en 2 couche, la première pour le sol, la seconde pour les mur
    sf::Sprite sprite[26*14];
    sf::Sprite sprite2[26*14];
    //le générateur de base devrait créé une salle complétement aléatoirement, ainsi on aurait plusiseurs obstacles, une entré une sortie et plusieurs sections
	Salles();
	Salles(const Point& c, float w, float h, const Point& enter, const Point& out);
	//le constructeur de salle permettra d'initialiser les salles avec une section, pas d'obstacle, un placement des portes aléatoires
	Salles(const Point& c, float w, float h);
	Salles(const std::vector<Point> P){
		int t=P.size();
		float x;
		float y;
		for (int k=0; k<t; k++)
			{pointMap[P[k]]++;
			x=P[k].getX();
			y=P[k].getY();
			pointMapInverted[Point(y,x)]++;
			}
	}
	//la fonction addobs prend en entrée 1 point, les obstacles seront constitué d'un carré de taille 1,1, pour faciliter l'affichage, il suffira donc d'indiquer ou on veut ajouter l'obstacle et de combien de portions il doit être constitué, si l'obstacle n'est pas positionnable, il renvoit false, sinon il renvoit true
	bool addobst(Point pos);
	//la ou les fonction setdoor permet de positionner les portes d'une salle
	bool setdoor(Point pos);
	//les fonctions get permette de récupérer les informations d'une salle
	Point getobst(int i){return obst[i];};
	Point getsect(int i){return contourList[i];};
	Point getdoor(int i){return door[i];};
	int getnbsect(){return n;};
	void printPoints();     // Affichage des map pointMap et pointMapInverted (terminal)    Trié selon y
	//void contour();         // Calcul du contour de la salle
	void printContour();    // Affichage de contourList (terminal)
	//la fonction insalles permet d'indiquer si un point est contenu dans la salle ou non(par exemple il pourrait se trouver dans un mur)
	bool insalles(Point pos);
	//la fonction ini_texture permet de créer l'ensemble des sprites d'une salle afin qu'elle puisse s'afficher
    void init_texture();

};


#endif // SALLES_HPP
