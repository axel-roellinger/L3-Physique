#include <iostream>
#include <vector>
#include <cmath>
#include "Missile.h"
#include "LASER.h"

using namespace std;

Missile::Missile(double x0, double y0, double V0, double Theta, double H, double L) //Constructeur
{
	x.push_back(x0);
	y.push_back(y0);
	v0 = V0;
	theta = Theta;
    hauteur = H;
    largeur = L;
}

Missile::~Missile(){}

double Missile::getX(int i)
{
	return x[i];
}	

double Missile::getY(int i)
{
	return y[i];
}

double Missile::getV0()
{
	return v0;
}

double Missile::getTheta()
{
	return theta;
}

double Missile::getXSize()
{
	return x.size();
}

double Missile::getHauteur()
{
    return hauteur;
}

double Missile::getLargeur()
{
    return largeur;
}

void Missile::setX0(double a)
{
    x[0] = a;
}

void Missile::setY0(double a)
{
    y[0] = a;
}

void Missile::setV0(double a)
{
	v0 = a;
}

void Missile::setTheta(double a)
{
	theta = a;
}

void Missile::setHauteur(double a)
{
    hauteur = a;
}

void Missile::setLargeur(double a)
{
    largeur = a;
}

void Missile::Trajectoire()
{
    int i = 0;
    
    double aX = v0*cos(theta); //Pour clarifier la boucle for, modèle parabolique idéal
    double bX = x[0];
    double aY = -0.5*9.81;
    double bY = v0*sin(theta);
    double cY = y[0];
    
    for(i = 0; i < 1E12; i++) //Grande limite pour permettre des valeurs importantes de vitesse
	{
        double X = aX*double(i)*0.01 + bX;
        double Y = aY*pow(double(i)/100,2) + bY*double(i)/100 + cY;
		x.push_back(X);
        y.push_back(Y);
        
        if(Y <= 0) //Si le missile atteint le sol
        {
            break;
        }
    }
}
