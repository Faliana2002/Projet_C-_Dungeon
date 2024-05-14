#include "Sallesv2.hpp"
#include <stdlib.h>
#include <time.h>
#include <iostream>

int valpix=48;
int widths=26;
int heights=14;
//constructeur créant une salle avec un rectangle (dont on place le coin en haut à gauche, la taille) et créant la salle avec les couloirs d'entré et sorti
Salles::Salles(const Point& c, float w, float h){
	srand (time(NULL));
	float a=w-(w/2.0)*2.0;
	float x1,y1,x2,y2,posx,posy,debx,deby,finx,finy;
    x1=c.getX();
    x2=c.getX()+w;
	y1=c.getY();
    y2=c.getY()-h;
    int aleatoire=3;
    int nbes;
    int deb;
    int fin;
    int val;
    //on vérifie si le point de création est dans l'écran ou pas
    if (x1>=widths || y1<=-heights)
        {printf("t'as donné des valeurs foireuses, fait controle c vite ou ca va planté");}
    //on vérifie si les dimensions sont dans le cadre
    if (x2>widths || y2<-heights)
        {x2=26.0;
        y2=14.0;
        aleatoire=0;}
    nbes=rand()%aleatoire +2;
//on stocke l'ensemble des point dans point map, cela va permettre de recréer la liste de point dans l'ordre à la fin
    pointMap[Point(x1,y1)]++;
    pointMap[Point(x1,y2)]++;
    pointMap[Point(x2,y2)]++;
    pointMap[Point(x2,y1)]++;
//si le rectangle est en bord d'écran, on ne crée que 2 couloirs, un entreé, un en sortie
    if (aleatoire==0)
        {
        deb=rand()%2;
        if (deb==0){
            posx=rand()%(int)(x2-x1-1.0)+x1;
            posy=0.0;
            pointMap[Point(posx,posy)]++;
            pointMap[Point(posx+1,posy)]++;
            pointMap[Point(posx,y1)]++;
            pointMap[Point(posx+1,y1)]++;
            setdoor(Point(posx,posy));
            debx=posx;
            deby=posy;
            posx=0.0;
            posy=-rand()%(int)(y1-y2-1.0)+y1;
            pointMap[Point(posx,posy)]++;
            pointMap[Point(x1,posy)]++;
            pointMap[Point(posx,posy-1)]++;
            pointMap[Point(x1,posy-1)]++;
            setdoor(Point(posx,posy));
            //    {return false;}
            }
        else{
            posx=0.0;
            posy=-rand()%(int)(y1-y2-1.0)+y1;
            pointMap[Point(posx,posy)]++;
            pointMap[Point(x1,posy)]++;
            pointMap[Point(posx,posy-1)]++;
            pointMap[Point(x1,posy-1)]++;
            setdoor(Point(posx,posy));
            //    {return false;}
            }
            debx=posx;
            deby=posy;
            posx=rand()%(int)(x2-x1-1.0)+x1;
            posy=0.0;
            pointMap[Point(posx,posy)]++;
            pointMap[Point(posx+1,posy)]++;
            pointMap[Point(posx,y1)]++;
            pointMap[Point(posx+1,y1)]++;
            setdoor(Point(posx,posy));
            //    {return false;}
        }
        //sinon on peut créer entre 2 à 4 couloirs, placé aléatoirement
    else
        {
        deb=rand()%3;
        if (deb==0){
            posx=rand()%(int)(x2-x1-1.0)+x1;
            posy=0.0;
            pointMap[Point(posx,posy)]++;
            pointMap[Point(posx+1,posy)]++;
            pointMap[Point(posx,y1)]++;
            pointMap[Point(posx+1,y1)]++;
            setdoor(Point(posx,posy));
            //    {return false;}
            debx=posx;
            deby=posy;
            fin=rand()%(nbes-1)+1;
            if (fin==1)
                {posx=0.0;
                posy=-rand()%(int)(y1-y2-1.0)+y1;
                pointMap[Point(posx,posy)]++;
                pointMap[Point(x1,posy)]++;
                pointMap[Point(posx,posy-1)]++;
                pointMap[Point(x1,posy-1)]++;
                setdoor(Point(posx,posy));
                //    {return false;}
                for (int k=2; k<nbes;k++){
                    if (k==3){
                        posx=widths;
                        posy=-rand()%(int)(y1-y2-1.0)+y1;
                        pointMap[Point(posx,posy)]++;
                        pointMap[Point(x2,posy)]++;
                        pointMap[Point(posx,posy-1)]++;
                        pointMap[Point(x2,posy-1)]++;
                        }
                    if (k==2){
                        posx=rand()%(int)(x2-x1-1.0)+x1;
                        posy=-heights;
                        pointMap[Point(posx,posy)]++;
                        pointMap[Point(posx+1,posy)]++;
                        pointMap[Point(posx,y2)]++;
                        pointMap[Point(posx+1,y2)]++;
                        }

                    }
                }
            if (fin==2)
                {posx=rand()%(int)(x2-x1-1.0)+x1;
                posy=-heights;
                pointMap[Point(posx,posy)]++;
                pointMap[Point(posx+1,posy)]++;
                pointMap[Point(posx,y2)]++;
                pointMap[Point(posx+1,y2)]++;
                setdoor(Point(posx,posy));
                //    {return false;}
                for (int k=2; k<nbes;k++){
                    if (k==3){
                        posx=widths;
                        posy=-rand()%(int)(y1-y2-1.0)+y1;
                        pointMap[Point(posx,posy)]++;
                        pointMap[Point(x2,posy)]++;
                        pointMap[Point(posx,posy-1)]++;
                        pointMap[Point(x2,posy-1)]++;
                        }
                    if (k==2){
                        posx=0.0;
                        posy=-rand()%(int)(y1-y2-1.0)+y1;
                        pointMap[Point(posx,posy)]++;
                        pointMap[Point(x1,posy)]++;
                        pointMap[Point(posx,posy-1)]++;
                        pointMap[Point(x1,posy-1)]++;
                        }

                    }
                }
            if (fin==3)
                {
                posx=widths;
                posy=-rand()%(int)(y1-y2-1.0)+y1;
                pointMap[Point(posx,posy)]++;
                pointMap[Point(x2,posy)]++;
                pointMap[Point(posx,posy-1)]++;
                pointMap[Point(x2,posy-1)]++;
                setdoor(Point(posx,posy));
                //    {return false;}
                for (int k=2; k<nbes;k++){
                    if (k==3){
                        posx=rand()%(int)(x2-x1-1.0)+x1;
                        posy=-heights;
                        pointMap[Point(posx,posy)]++;
                        pointMap[Point(posx+1,posy)]++;
                        pointMap[Point(posx,y2)]++;
                        pointMap[Point(posx+1,y2)]++;
                        }
                    if (k==2){
                        posx=0.0;
                        posy=-rand()%(int)(y1-y2-1.0)+y1;
                        pointMap[Point(posx,posy)]++;
                        pointMap[Point(x1,posy)]++;
                        pointMap[Point(posx,posy-1)]++;
                        pointMap[Point(x1,posy-1)]++;
                        }
                    }
                }
            }
        else if (deb==1){
            posx=0.0;
            posy=-rand()%(int)(y1-y2-1.0)+y1;
            pointMap[Point(posx,posy)]++;
            pointMap[Point(x1,posy)]++;
            pointMap[Point(posx,posy-1)]++;
            pointMap[Point(x1,posy-1)]++;
            setdoor(Point(posx,posy));
            //    {return false;}
            debx=posx;
            deby=posy;
            fin=rand()%(nbes-2)+2;
            if (fin==2)
                {posx=rand()%(int)(x2-x1-1.0)+x1;
                posy=-heights;
                pointMap[Point(posx,posy)]++;
                pointMap[Point(posx+1,posy)]++;
                pointMap[Point(posx,y2)]++;
                pointMap[Point(posx+1,y2)]++;
                setdoor(Point(posx,posy));
                //    {return false;}
                for (int k=2; k<(nbes-2);k++){
                    if (k==3){
                        posx=widths;
                        posy=-rand()%(int)(y1-y2-1.0)+y1;
                        pointMap[Point(posx,posy)]++;
                        pointMap[Point(x2,posy)]++;
                        pointMap[Point(posx,posy-1)]++;
                        pointMap[Point(x2,posy-1)]++;
                        }
                    if (k==2){
                        posx=rand()%(int)(x2-x1-1.0)+x1;
                        posy=0.0;
                        pointMap[Point(posx,posy)]++;
                        pointMap[Point(posx+1,posy)]++;
                        pointMap[Point(posx,y1)]++;
                        pointMap[Point(posx+1,y1)]++;
                        }

                    }
                }
            if (fin==3)
                {posx=widths;
                posy=-rand()%(int)(y1-y2-1.0)+y1;
                pointMap[Point(posx,posy)]++;
                pointMap[Point(x2,posy)]++;
                pointMap[Point(posx,posy-1)]++;
                pointMap[Point(x2,posy-1)]++;
                setdoor(Point(posx,posy));
                //    {return false;}
                for (int k=2; k<nbes;k++){
                    if (k==3){
                        posx=rand()%(int)(x2-x1-1.0)+x1;
                        posy=-heights;
                        pointMap[Point(posx,posy)]++;
                        pointMap[Point(posx+1,posy)]++;
                        pointMap[Point(posx,y2)]++;
                        pointMap[Point(posx+1,y2)]++;
                        }
                    if (k==2){
                        posx=0.0;
                        posy=-rand()%(int)(y1-y2-1.0)+y1;
                        pointMap[Point(posx,posy)]++;
                        pointMap[Point(posx+1,posy)]++;
                        pointMap[Point(posx,y1)]++;
                        pointMap[Point(posx+1,y1)]++;
                        }

                    }
                }
            }
        else if (deb==2){
            posx=rand()%(int)(x2-x1-1.0)+x1;
            posy=-heights;
            pointMap[Point(posx,posy)]++;
            pointMap[Point(posx+1,posy)]++;
            pointMap[Point(posx,y2)]++;
            pointMap[Point(posx+1,y2)]++;
            setdoor(Point(posx,posy));
            //    {return false;}
            debx=posx;
            deby=posy;
            fin=rand()%(nbes-3)+3;
            if (fin==3)
                {posx=widths;
                posy=-rand()%(int)(y1-y2-1.0)+y1;
                pointMap[Point(posx,posy)]++;
                pointMap[Point(x2,posy)]++;
                pointMap[Point(posx,posy-1)]++;
                pointMap[Point(x2,posy-1)]++;
                setdoor(Point(posx,posy));
                //    {return false;}
                for (int k=2; k<nbes;k++){
                    if (k==3){
                        posx=rand()%(int)(x2-x1-1.0)+x1;
                        posy=0.0;
                        pointMap[Point(posx,posy)]++;
                        pointMap[Point(posx+1,posy)]++;
                        pointMap[Point(posx,y1)]++;
                        pointMap[Point(posx+1,y1)]++;
                        setdoor(Point(posx,posy));
                        }
                    if (k==2){
                        posx=0.0;
                        posy=-rand()%(int)(y1-y2-1.0)+y1;
                        pointMap[Point(posx,posy)]++;
                        pointMap[Point(x1,posy)]++;
                        pointMap[Point(posx,posy-1)]++;
                        pointMap[Point(x1,posy-1)]++;
                        }

                    }
                }
            }
    }
    //on parcourt ensuite la liste en faisant des déplacement haut, bas alternés avec gauche, droite
    n=0;
    int dirx=1;
    int diry=1;
    int i=0;
    int j=0;
    if (debx+i==widths)
        {i--;
        dirx=0;}
    else
        {i++;}
    if (deby+j==-heights)
        {diry=0;}
    Point P(debx+i,deby+j);
    //quand on tombe sur un point correspondant, on l'implémente dans la liste
    contourList.push_back(Point(debx,deby));
    val=1;
    while (P!=Point(debx,deby))
        {
        if (val==1)
            {while (pointMap[P]!=1)
                {P=Point(debx+i,deby+j);
                if (dirx==1)
                    {i++;}
                else
                    {i--;}
                }
            if (debx+i==widths)
                {dirx=0;}
            else if (debx+i==0.0)
                {dirx=1;}
            contourList.push_back(Point(debx+i,deby+j));
            val=0;
            }
        else
            {while (pointMap[P]!=1)
                {P=Point(debx+i,deby+j);
                if (diry==1)
                    {j++;}
                else
                    {j--;}
                }
            if (deby+j==heights)
                {diry=0;}
            else if (deby+j==0.0)
                {diry=1;}
            contourList.push_back(Point(debx+i,deby+j));
            val=1;
            }
        n++;
        }
}

Salles::Salles(){
//on intialise le random
	srand (time(NULL));
    float start=rand()%4;
    float x;
    float y;
    if (start==0){
        x=-widths/2;
        y=rand()%heights -heights/2;
    }
    else if (start==1){
        y=heights/2;
        x=rand()%widths -widths/2;
    }
    else if (start==2){
        x=widths/2;
        y=rand()%heights -heights/2;
    }
    else{
        x=-heights/2;
        y=rand()%widths -widths/2;
    }
    contourList.push_back(Point(x,y));
    pointMap[Point(x,y)]++;
    pointMapInverted[Point(y,x)]++;
    setdoor(Point(x,y));
}

bool Salles::insalles(Point pos){
    bool ans=false;
    float distyh=1.0;
    float distyl=-heights-1;
    for (Point &P: contourList){
        if (P.getX()<=pos.getX() && P.getX()+1>=pos.getX()  && P.getY()-pos.getY()<distyh && P.getY()-pos.getY()>0)
            {distyh=P.getY()-pos.getY();}
        if (P.getX()<=pos.getX() && P.getX()+1>=pos.getX() && P.getY()-pos.getY()>distyl && P.getY()-pos.getY()<0)
            {distyl=P.getY()-pos.getY();}
    }
    if (distyh!=1.0 && distyl!=-heights-1){
        ans=true;
    }
    return(ans);
}
//ajoute les obstacles de taille 1,1 en vérifiant qu'ils sont bien contenu dans la salle
bool Salles::addobst(Point pos){
	bool ans=false;
	float ymax=30,ymin=-30;
    for (Point &O: obst){
        if (O==pos)
            {return (ans);}
	}
	ans=insalles(pos);
    obst.push_back(pos);
	return (ans);
}
//ajoute les portes, en vérifiant quelles sont dans une zone accesible
bool Salles::setdoor(Point pos){
    printf("test");
	Point p1(pos.getX(), pos.getY());
	Point p2(pos.getX(), pos.getY()-1.0);
	Point p3(pos.getX() +1.0,pos.getY()-1.0);
	Point p4(pos.getX() +1.0,pos.getY());
	if (pos.getX()!=0.0 && pos.getX()!=widths && pos.getY()!=0.0 && pos.getY()!=heights)
		{return false;}
	if (insalles(pos)==true){
        door.push_back(pos);
        return true;
        }
	return false;
	}

// Affichage des map pointMap et pointMapInverted
void Salles::printPoints() {
	std::cout << "Vertical : " << std::endl;
	for (const auto& pair : pointMap) {
		if (pair.second == 1) // Si l'occurrence du point est égale à 1, imprimez le point
			std::cout << pair.first.getX() << " : " << pair.first.getY() << std::endl;
	}
	std::cout << std::endl << "horizontal : " << std::endl;
	for (const auto& pair : pointMapInverted) {
		if (pair.second == 1) // Si l'occurrence du point est égale à 1, imprimez le point
			std::cout << pair.first.getY() << " : " << pair.first.getX() << std::endl;
	}
}

// Affichage du vector contourList
void Salles::printContour() {
	std::cout << "\nContour : " << std::endl;
	for (const Point& point : contourList) {
		std::cout << point.getX() << " : " << point.getY() << std::endl;
	}
}
