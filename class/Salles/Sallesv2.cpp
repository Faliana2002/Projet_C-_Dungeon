#include "Sallesv2.hpp"
#include <stdlib.h>
#include <time.h>
#include <iostream>
std::string reference="../../0x72_DungeonTilesetII_v1.7/0x72_DungeonTilesetII_v1.7/frames/";
int valpix=48;
int widths=26;
int heights=14;
Salles::Salles(const Point& c, float w, float h, const Point& enter,const Point& out){
    //on fait une première série de if pour déterminer ou se situe l'entrée
    //coté gauche
    if (enter.getX()>0 && enter.getX()<1){
        contourList.push_back(enter);
        contourList.push_back(Point(c.getX(),enter.getY()));
        contourList.push_back(c);
        //on fait une seconde série de if pour déterminer comment compléter la sortie
        //coté droit
        if (out.getX()<widths && out.getX()>widths-1){
            contourList.push_back(Point(c.getX()+w,c.getY()));
            contourList.push_back(Point(c.getX()+w,out.getY()));
            contourList.push_back(Point(out.getX()+1,out.getY()));
            contourList.push_back(Point(out.getX()+1,out.getY()-1));
            contourList.push_back(Point(c.getX()+w,out.getY()-1));
            contourList.push_back(Point(c.getX()+w,c.getY()-h));
            contourList.push_back(Point(c.getX(),c.getY()-h));
            contourList.push_back(Point(c.getX(),enter.getY()-1));
            contourList.push_back(Point(enter.getX(),enter.getY()-1));
        }
        //coté haut
        else if (out.getY()<0 && out.getY()>-1){
            contourList.push_back(Point(out.getX(),c.getY()));
            contourList.push_back(Point(out.getX(),out.getY()));
            contourList.push_back(Point(out.getX()+1,out.getY()));
            contourList.push_back(Point(out.getX()+1,c.getY()));
            contourList.push_back(Point(c.getX()+w,c.getY()));
            contourList.push_back(Point(c.getX()+w,c.getY()-h));
            contourList.push_back(Point(c.getX(),c.getY()-h));
            contourList.push_back(Point(c.getX(),enter.getY()-1));
            contourList.push_back(Point(enter.getX(),enter.getY()-1));
        }
        //coté bas
        else if (out.getY()>-heights && out.getY()<-heights+1){
            contourList.push_back(Point(c.getX()+w,c.getY()));
            contourList.push_back(Point(c.getX()+w,c.getY()-h));
            contourList.push_back(Point(out.getX()+1,c.getY()-h));
            contourList.push_back(Point(out.getX()+1,out.getY()-1));
            contourList.push_back(Point(out.getX(),out.getY()-1));
            contourList.push_back(Point(out.getX(),c.getY()-h));
            contourList.push_back(Point(c.getX(),c.getY()-h));
            contourList.push_back(Point(c.getX(),enter.getY()-1));
            contourList.push_back(Point(enter.getX(),enter.getY()-1));
        }
    }
    //coté droit
    else if (enter.getX()<widths && enter.getX()>widths-1){
        contourList.push_back(Point(enter.getX()+1,enter.getY()));
        contourList.push_back(Point(enter.getX()+1,enter.getY()-1));
        contourList.push_back(Point(c.getX()+w,enter.getY()-1));
        contourList.push_back(Point(c.getX()+w,c.getY()-h));
        //coté gauche
        if (out.getX()>0 && out.getX()<1){
            contourList.push_back(Point(c.getX(),c.getY()-h));
            contourList.push_back(Point(c.getX(),out.getY()-1));
            contourList.push_back(Point(out.getX(),out.getY()-1));
            contourList.push_back(Point(out.getX(),out.getY()));
            contourList.push_back(Point(c.getX(),out.getY()));
            contourList.push_back(c);
        }
        //coté haut
        else if (out.getY()<0 && out.getY()>-1){
            contourList.push_back(Point(c.getX(),c.getY()-h));
            contourList.push_back(c);
            contourList.push_back(Point(out.getX(),c.getY()));
            contourList.push_back(Point(out.getX(),out.getY()));
            contourList.push_back(Point(out.getX()+1,out.getY()));
            contourList.push_back(Point(out.getX()+1,c.getY()));
        }
        //coté bas
        else if (out.getY()>-heights && out.getY()<-heights+1){
            contourList.push_back(Point(out.getX()+1,c.getY()-h));
            contourList.push_back(Point(out.getX()+1,out.getY()-1));
            contourList.push_back(Point(out.getX(),out.getY()-1));
            contourList.push_back(Point(out.getX(),c.getY()-h));
            contourList.push_back(Point(c.getX(),c.getY()-h));
            contourList.push_back(Point(c));
        }
        contourList.push_back(Point(c.getX()+w,c.getY()));
        contourList.push_back(Point(c.getX()+w,enter.getY()));
    }
    //coté haut
    else if (enter.getY()<0 && enter.getY()>-1){
        contourList.push_back(Point(enter.getX(),enter.getY()));
        contourList.push_back(Point(enter.getX()+1,enter.getY()));
        contourList.push_back(Point(enter.getX()+1,c.getY()));
        contourList.push_back(Point(c.getX()+w,c.getY()));
        //coté gauche
        if (out.getX()>0 && out.getX()<1){
            contourList.push_back(Point(c.getX()+w,c.getY()-h));
            contourList.push_back(Point(c.getX(),c.getY()-h));
            contourList.push_back(Point(c.getX(),out.getY()-1));
            contourList.push_back(Point(out.getX(),out.getY()-1));
            contourList.push_back(Point(out.getX(),out.getY()));
            contourList.push_back(Point(c.getX(),out.getY()));
        }
        //coté droit
        else if (out.getX()<widths && out.getX()>widths-1){
            contourList.push_back(Point(c.getX(),out.getY()));
            contourList.push_back(Point(out.getX()+1,out.getY()));
            contourList.push_back(Point(out.getX()+1,out.getY()-1));
            contourList.push_back(Point(c.getX()+w,out.getY()-1));
            contourList.push_back(Point(c.getX()+w,c.getY()-h));
            contourList.push_back(Point(c.getX(),c.getY()-h));
        }
        //coté bas
        else if (out.getY()>-heights && out.getY()<-heights+1){
            contourList.push_back(Point(c.getX()+w,c.getY()-h));
            contourList.push_back(Point(out.getX()+1,c.getY()-h));
            contourList.push_back(Point(out.getX()+1,out.getY()-1));
            contourList.push_back(Point(out.getX(),out.getY()-1));
            contourList.push_back(Point(out.getX(),c.getY()-h));
            contourList.push_back(Point(c.getX(),c.getY()-h));
        }
        contourList.push_back(c);
        contourList.push_back(Point(enter.getX(),c.getY()));
    }
    //coté bas
    else if (enter.getY()>-heights && enter.getY()<-heights+1){
        contourList.push_back(Point(enter.getX(),enter.getY()-1));
        contourList.push_back(Point(enter.getX(),c.getY()-h));
        contourList.push_back(Point(c.getX(),c.getY()-h));
        //coté gauche
        if (out.getX()>0 && out.getX()<1){
            contourList.push_back(Point(c.getX(),out.getY()-1));
            contourList.push_back(Point(out.getX(),out.getY()-1));
            contourList.push_back(Point(out.getX(),out.getY()));
            contourList.push_back(Point(c.getX(),out.getY()));
            contourList.push_back(Point(c));
            contourList.push_back(Point(c.getX()+w,c.getY()));
        }
        //coté droit
        else if (out.getX()<widths && out.getX()>widths-1){
            contourList.push_back(Point(c));
            contourList.push_back(Point(c.getX()+w,c.getY()));
            contourList.push_back(Point(c.getX()+w,out.getY()));
            contourList.push_back(Point(out.getX()+1,out.getY()));
            contourList.push_back(Point(out.getX()+1,out.getY()-1));
            contourList.push_back(Point(c.getX()+w,out.getY()-1));
        }
        //coté haut
        else if (out.getY()<0 && out.getY()>-1){
            contourList.push_back(Point(c));
            contourList.push_back(Point(out.getX(),c.getY()));
            contourList.push_back(Point(out.getX(),out.getY()));
            contourList.push_back(Point(out.getX()+1,out.getY()));
            contourList.push_back(Point(out.getX()+1,c.getY()));
            contourList.push_back(Point(c.getX()+w,c.getY()));
        }
        contourList.push_back(Point(c.getX()+w,c.getY()-h));
        contourList.push_back(Point(enter.getX()+1,c.getY()-h));
        contourList.push_back(Point(enter.getX()+1,enter.getY()-1));
    }
    door.push_back(enter);
    door.push_back(out);
}
//constructeur semi aléatoire permettant de creer une salle avec un rectangle et 2 portes sans obstacle
Salles::Salles(const Point& c, float w, float h){
//on initialise l'aléatoire
	srand (time(NULL));
	float x1,y1,x2,y2,posx,posy,debx,deby;
    //on positionne les 2 points imporatnat, celui en haut à gauche, et celui en bas à droite, cela nous permet de tracer un rectangle
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
//on défini le nombre de portion a ajouter en plus de la portion de base (entre 2 à 4)
    nbes=rand()%aleatoire +2;
//on stocke l'ensemble des point dans point map, cela va permettre de recréer la liste de point dans l'ordre à la fin
    pointMap[Point(x1,y1)]++;
    pointMap[Point(x1,y2)]++;
    pointMap[Point(x2,y2)]++;
    pointMap[Point(x2,y1)]++;
//si le rectangle est en bord d'écran, on ne crée que 2 couloirs, un entreé, un en sortie
    if (aleatoire==0)
        {
        //on détermine aléatoirement si la porte d'entré est à gauche ou au dessus de la porte principale
        deb=rand()%2;
        //on se place dans le cas ou la porte est placé au dessus
        if (deb==0){
            //on positionne le couloir menant à la porte d'entrée aléatoirement entre les 2 extrémités du rectangle initial
            posx=rand()%(int)(x2-x1-1.0)+x1;
            posy=0.0;
            pointMap[Point(posx,posy)]++;
            pointMap[Point(posx+1,posy)]++;
            pointMap[Point(posx,y1)]++;
            pointMap[Point(posx+1,y1)]++;
            //on positionne la porte
            setdoor(Point(posx,posy));
            debx=posx;
            deby=posy;
            //on positionne maintenant la position de la porte de sortie aléatoirement sur le coté gauche du rectangle d'origine
            posx=0.0;
            posy=-rand()%(int)(y1-y2-1.0)+y1;
            pointMap[Point(posx,posy)]++;
            pointMap[Point(x1,posy)]++;
            pointMap[Point(posx,posy-1)]++;
            pointMap[Point(x1,posy-1)]++;
            setdoor(Point(posx,posy));
            }
        //sinon on positionne la porte d'entrée à gauche du rectangle d'origine, et on place la sortie au dessus
        else{
            posx=0.0;
            posy=-rand()%(int)(y1-y2-1.0)+y1;
            pointMap[Point(posx,posy)]++;
            pointMap[Point(x1,posy)]++;
            pointMap[Point(posx,posy-1)]++;
            pointMap[Point(x1,posy-1)]++;
            setdoor(Point(posx,posy));
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
        }
        //sinon on peut créer entre 2 à 4 couloirs, placé aléatoirement
    else
        {
        //on détermine le positionnement de la porte de début, pour simplifier la chose, il n'y aura que 3 cotés d'entrés possible
        deb=rand()%3;
        //la première position d'entrée est sur le dessus du rectangle
        if (deb==0){
            //on positionne l'entrée aléatoirement en contact avec la section de base
            posx=rand()%(int)(x2-x1-1.0)+x1;
            posy=0.0;
            pointMap[Point(posx,posy)]++;
            pointMap[Point(posx+1,posy)]++;
            pointMap[Point(posx,y1)]++;
            pointMap[Point(posx+1,y1)]++;
            setdoor(Point(posx,posy));
            debx=posx;
            deby=posy;
            //on permet ensuite de placer la sortie sur l'un des coté restant
            fin=rand()%(nbes-1)+1;
            if (fin==1)
            //on positionne ici la sortie sur le coté gauche du carré d'origine
                {posx=0.0;
                posy=-rand()%(int)(y1-y2-1.0)+y1;
                pointMap[Point(posx,posy)]++;
                pointMap[Point(x1,posy)]++;
                pointMap[Point(posx,posy-1)]++;
                pointMap[Point(x1,posy-1)]++;
                setdoor(Point(posx,posy));
                //puis on positionne les coté restant en fonction du nombre de faux coté que l'on peut créer
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
            //on positionne ici sur le bas de la salle la sortie
                {posx=rand()%(int)(x2-x1-1.0)+x1;
                posy=-heights;
                pointMap[Point(posx,posy)]++;
                pointMap[Point(posx+1,posy)]++;
                pointMap[Point(posx,y2)]++;
                pointMap[Point(posx+1,y2)]++;
                setdoor(Point(posx,posy));
                // et on positionne potentiellement  des faux couloirs à droite et à gauche
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
            //on positionne ici la sortie sur le coté droit de la portion de base
            if (fin==3)
                {
                posx=widths;
                posy=-rand()%(int)(y1-y2-1.0)+y1;
                pointMap[Point(posx,posy)]++;
                pointMap[Point(x2,posy)]++;
                pointMap[Point(posx,posy-1)]++;
                pointMap[Point(x2,posy-1)]++;
                setdoor(Point(posx,posy));
                // et on positionne potentiellement des faux couloirs sur le dessous et sur la gauche de la portion de départ
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
        //on positionne ici l'entré sur le coté gauche de la portion d'origine
        else if (deb==1){
            posx=0.0;
            posy=-rand()%(int)(y1-y2-1.0)+y1;
            pointMap[Point(posx,posy)]++;
            pointMap[Point(x1,posy)]++;
            pointMap[Point(posx,posy-1)]++;
            pointMap[Point(x1,posy-1)]++;
            setdoor(Point(posx,posy));
            debx=posx;
            deby=posy;
            fin=rand()%(nbes-2)+2;
            //on peut alors poser la sortie sur le bas de la portion d'origine( pour des raisons de simpliciter je ne fais pas les 3 sorties possible à chaque entrée, mais une simple modification de la variable aléatoire suffirait à le permettre
            if (fin==2)
                {posx=rand()%(int)(x2-x1-1.0)+x1;
                posy=-heights;
                pointMap[Point(posx,posy)]++;
                pointMap[Point(posx+1,posy)]++;
                pointMap[Point(posx,y2)]++;
                pointMap[Point(posx+1,y2)]++;
                setdoor(Point(posx,posy));
                for (int k=2; k<(nbes-2);k++){
                //on peut alors poser les faux couloirs sur le coté droit de la portion d'origine
                    if (k==3){
                        posx=widths;
                        posy=-rand()%(int)(y1-y2-1.0)+y1;
                        pointMap[Point(posx,posy)]++;
                        pointMap[Point(x2,posy)]++;
                        pointMap[Point(posx,posy-1)]++;
                        pointMap[Point(x2,posy-1)]++;
                        }
                    //ou sur le haut de cette portion
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
            //on peut aussi positionner la sortie sur le coté droit de la portion d'origine
            if (fin==3)
                {posx=widths;
                posy=-rand()%(int)(y1-y2-1.0)+y1;
                pointMap[Point(posx,posy)]++;
                pointMap[Point(x2,posy)]++;
                pointMap[Point(posx,posy-1)]++;
                pointMap[Point(x2,posy-1)]++;
                setdoor(Point(posx,posy));
                //et positionner des faux couloirs sur le bas de la portion ou sur le coté gauche de cette dernière
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
        //on positionne l'entré ici sur le bas de la portion
        else if (deb==2){
            posx=rand()%(int)(x2-x1-1.0)+x1;
            posy=-heights;
            pointMap[Point(posx,posy)]++;
            pointMap[Point(posx+1,posy)]++;
            pointMap[Point(posx,y2)]++;
            pointMap[Point(posx+1,y2)]++;
            setdoor(Point(posx,posy));
            debx=posx;
            deby=posy;
            fin=rand()%(nbes-3)+3;
            //on positionne ici la sortie sur la droite de la section de base
            if (fin==3)
                {posx=widths;
                posy=-rand()%(int)(y1-y2-1.0)+y1;
                pointMap[Point(posx,posy)]++;
                pointMap[Point(x2,posy)]++;
                pointMap[Point(posx,posy-1)]++;
                pointMap[Point(x2,posy-1)]++;
                setdoor(Point(posx,posy));
                //on positionne alors des faux couloirs (potentiellement) sur le bas de la section d'origine et sur la gauche
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
    //de base, on se déplace vers la droite vers le haut
    int dirx=1;
    int diry=1;
    int i=0;
    int j=0;
    //si on est sur le bord droit de l'affichage, on se met à se déplacer vers la gauche
    if (debx+i==widths)
        {i--;
        dirx=0;}
    //sion on incrémente de 1 par rapport au point d'origine
    else
        {i++;}
    //si on est en bas de l'affichage, on inverse et on se déplace vers le haut
    if (deby+j==-heights)
        {diry=0;}
    Point P(debx+i,deby+j);
    //quand on tombe sur un point correspondant, on l'implémente dans la liste
    contourList.push_back(Point(debx,deby));
    val=1;
    //tant que l'on est pas revenu à notre pint de départ
    while (P!=Point(debx,deby))
        {
        //dans le cas 1 on se déplace vers la gauche ou la droite pour trouver le prochain point
        if (val==1)
            {while (pointMap[P]!=1)
            //on avance 1 par selon x dans les point jusqu'a arriver à un point connu
                {P=Point(debx+i,deby+j);
                if (dirx==1)
                    {i++;}
                else
                    {i--;}
                }
            //si on se retrouve sur l'un des bords de l'écran on change de sens
            if (debx+i==widths)
                {dirx=0;}
            else if (debx+i==0.0)
                {dirx=1;}
            //puis on ajoute le point à la liste
            contourList.push_back(Point(debx+i,deby+j));
            //et on se met dans le mode pour aller vers le haut ou le bas
            val=0;
            }
        else
            {while (pointMap[P]!=1)
            //on se déplace vers le haut ou le bas pour trouver le prochain point
                {P=Point(debx+i,deby+j);
                if (diry==1)
                    {j++;}
                else
                    {j--;}
            //on change de sens si on est sur un bord
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
    for (Point &O: obst){
        if (O==pos)
            {return (ans);}
	}
	ans=insalles(pos);
    obst.push_back(pos);
	return (ans);
}
//ajoute les portes, en vérifiant qu'elles sont dans une zone accesible
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

void Salles::init_texture() {
    srand (time(NULL));
    //on charge l'ensemble des textures
    texture[0].loadFromFile(reference + "floor_1.png");
    texture[1].loadFromFile(reference + "floor_2.png");
    texture[2].loadFromFile(reference + "floor_3.png");
    texture[3].loadFromFile(reference + "floor_4.png");
    texture[4].loadFromFile(reference + "floor_5.png");
    texture[5].loadFromFile(reference + "floor_6.png");
    texture[6].loadFromFile(reference + "floor_7.png");
    texture[7].loadFromFile(reference + "floor_8.png");
    wall[0].loadFromFile(reference + "wall_hole_1.png");
    wall[1].loadFromFile(reference + "wall_hole_2.png");
    wall[2].loadFromFile(reference + "wall_left.png");
    wall[3].loadFromFile(reference + "wall_mid.png");
    wall[4].loadFromFile(reference + "wall_right.png");
    wallsection[0].loadFromFile(reference + "wall_edge_bottom_left.png");
    wallsection[1].loadFromFile(reference + "wall_edge_bottom_right.png");
    wallsection[2].loadFromFile(reference + "wall_edge_mid_left.png");
    wallsection[3].loadFromFile(reference + "wall_edge_mid_right.png");
    wallsection[4].loadFromFile(reference + "wall_top_left.png");
    wallsection[5].loadFromFile(reference + "wall_top_right.png");
    wallsection[6].loadFromFile(reference + "wall_top_mid.png");
    int val;
    int pos;
    //on parcourt l'ensemble de l'écran pour savoir si on est dans ou a l'extérieur de la salle
    for (float x=0; x<widths;x++){
        for (float y=0; y<heights; y++){
            if (insalles(Point(x,-y))==true){
                val=rand()%8;
                pos=y*widths+x;
                sprite[pos].setTexture(texture[val]);
                sprite[pos].setScale(1,1);
                sprite[pos].setPosition(x*valpix,-y*valpix);
            }
            else {
                val=rand()%5;
                pos=y*widths+x;
                sprite[pos].setTexture(wall[val]);
                sprite[pos].setScale(1,1);
                sprite[pos].setPosition(x*valpix,-y*valpix);
            }
        }
    }
    //puis on fais la deuxième couche en faisant les murs
    Point P=contourList[0];
    float difx=0;
    float dify=0;
    int count=0;
    for (int k=1;k<=n;k++){
        if (k==n){
            difx=contourList[0].getX()-P.getX();
            dify=contourList[0].getY()-P.getY();
        }
        else{
            difx=contourList[k].getX()-P.getX();
            dify=contourList[k].getY()-P.getY();
        }
        if (difx<0){
            for (int i=0;i>(int)difx;i--){
                sprite2[count].setTexture(wallsection[6]);
                sprite2[count].setScale(1,1);
                sprite2[count].setPosition((P.getX()+i)*valpix+valpix,-P.getY()*valpix);
                count++;
            }
        }
        else if (difx>0){
            for (int i=0;i<(int)difx;i++){
                sprite2[count].setTexture(wallsection[5]);
                sprite2[count].setScale(1,1);
                sprite2[count].setPosition((P.getX()+i)-valpix,-P.getY()*valpix);
                count++;
            }
        }
        else if (dify>0){
            for (int i=0;i<(int)dify;i++){
                sprite2[count].setTexture(wallsection[2]);
                sprite2[count].setScale(1,1);
                sprite2[count].setPosition(P.getX()*valpix,(-P.getY()+i+1)*valpix);
                count++;
            }
        }
        else{
            for (int i=0;i>(int)dify;i--){
                sprite2[count].setTexture(wallsection[3]);
                sprite2[count].setScale(1,1);
                sprite2[count].setPosition(P.getX()*valpix,(-P.getY()+i)*valpix);
                count++;
            }
        }
    }
}
