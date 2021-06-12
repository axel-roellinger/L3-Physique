#include <iostream>
#include <random>
#include <vector>
#include "Missile.h"
#include "LASER.h"
#include <cmath>
#include <fstream>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif


using namespace std;

LASER::LASER(){}

LASER::LASER(double a, double b)
{
    sigmaX = a;
    sigmaY = b;
}

LASER::~LASER(){}

double LASER::getAngle()
{
	return angle;
}

double LASER::getSigmaX()
{
	return sigmaX;
}

double LASER::getSigmaY()
{
	return sigmaY;
}

double LASER::getTpsDetect()
{
    return tps_detect;
}

double LASER::getXM(int i)
{
	return xM[i];
}

double LASER::getYM(int i)
{
	return yM[i];
}

double LASER::getXL(int i)
{
    return xL[i];
}

double LASER::getYL(int i)
{
    return yL[i];
}

double LASER::getAX()
{
    return aX;
}

double LASER::getBX()
{
    return bX;
}

double LASER::getAY()
{
    return aY;
}

double LASER::getBY()
{
    return bY;
}

double LASER::getCY()
{
    return cY;
}

void LASER::setSigmaX(double a)
{
	sigmaX = a;
}

void LASER::setSigmaY(double a)
{
	sigmaY = a;
}


void LASER::setAngle(double a)
{
	angle = a;
}

void LASER::setXL(double a, int i)
{
    xL[i] = a;
}

void LASER::setYL(double a, int i)
{
    yL[i] = a;
}

void LASER::setXM(double a, int i)
{
	xM[i] = a;
    if(xM.size() < i)
    {
        xM.push_back(a);
    }

}

void LASER::setYM(double a, int i)
{
	yM[i] = a;
    if(xM.size() < i)
    {
        yM.push_back(a);
    }
}

//Fonctions requises pour le Chi-2

double LASER::SSig(double sigma, int N)
{
    double sum = 0;
    for(int i = 0; i < N; i++)
    {
        sum += pow(1/sigma, 2);
    }
    return sum;
}

double LASER::XN(vector<double> X, double sigma, int N)
{
    double sum = 0;
    for(int i = 0; i < X.size(); i++)
    {
        sum += pow(X[i],N)/pow(sigma,2);
    }
    return sum;
}

double LASER::XNY(vector<double> X, vector<double> Y, double sigma, int N)
{
    double sum = 0;
    for(int i = 0; i< X.size(); i++)
    {
        sum += pow(X[i],N)*Y[i]/pow(sigma,2);
    }
    return sum;
}

/*
 Les fonctions X et Y définissent le Chi-2 selon l'axe X et l'axe Y, une minimisation est effectuée sur les points de mesure "erronés"
*/

void LASER::X(vector<double> I, vector<double> xM, double sigmaX, int NbPoints) //Minimisation sur X
{
    int N = NbPoints; //Nombre de points de mesure : 200 points <=> 2 secondes de mesure
    double S = SSig(sigmaX,N);
    double A = XN(I,sigmaX,1);
    double B = XN(xM, sigmaX,1);
    double C = XN(I,sigmaX,2);
    double D = XNY(I,xM,sigmaX,1);

    double a = (S*D - A*B)/(S*C - A*A); //Facteurs issus du Chi2 pour un polynôme de degré 2
    double b = (C*B - A*D)/(S*C - A*A);

    aX = a;
    bX = b;
}

void LASER::Y(vector<double> I, vector<double> yM, double sigmaY, int NbPoints)
{
    int N = NbPoints;
    double A = XN(I,sigmaY,1);
    double B = XN(I,sigmaY,2);
    double C = XN(I,sigmaY,3);
    double D = XN(I,sigmaY,4);
    double E = XNY(I,yM,sigmaY,2); 
    double F = XNY(I,yM,sigmaY,1);
    double G = XNY(I,yM,sigmaY,0);
    double S = SSig(sigmaY,N);

    double a = - (B*(-S*E - A*F) + A*A*E + C*(F*S - A*G) + B*B*G)/(D*(B*S-A*A) - C*C*S + 2*A*B*C - B*B*B); //Facteurs issus du Chi2 pour un polynôme de degré 3
    
    double b = (C*(B*G - S*E) + A*B*E + D*(F*S - A*G) - B*B*F)/(D*(B*S - A*A) - C*C*S + 2*A*B*C - B*B*B);  
    
    double c = (C*(A*E + B*F) - B*B*E + D*(B*G - A*F) - C*C*G)/(D*(B*S - A*A) - C*C*S + 2*A*B*C - B*B*B); 
    
    aY = a; //Attribution des valeurs de coefficients résultant du Chi2 à des variables exploitables dans toute la classe
    bY = b;
    cY = c;
    
    //cout << "Pour y, a vaut : " << a << ", b vaut : " << b << " et c vaut : " << c << endl;
}

void LASER::Detection()
{
	static random_device rd;
	uniform_real_distribution<float> dist(2,12);
	tps_detect = int(dist(rd));
}

void LASER::TirLaser(Missile missile)
{
    ofstream laser_track("laser_track.txt");    //Recueille les données pour l'affichage de la courbe
    
    xLaser = 10*aX; //On imagine que le LASER peut se déplacer, mais reste à une altitude fixe
    yLaser = 10;
    int tps_tir = tps_detect + 5; //Temps pour faire les calculs et tirer : 5 secondes environ
    cout << "Temps  de tir : " << tps_tir << endl;
    double tangente = (yL[tps_tir*100]-yLaser)/(xL[tps_tir*100] - xLaser);
    double angle = atan(tangente);
    cout << "Angle de tir : " << angle << " radians" << endl;
    double norme = sqrt(pow(yL[tps_tir*100]-yLaser,2) + pow(xM[tps_tir*100] - xLaser,2));
    double tps_propag = norme/3E8;
    cout << "Cible atteinte en "<< tps_propag << " secondes." << endl; //Négligeable
    
    int i = 0;
    
    double ang_missile = atan((missile.getX(tps_tir*100 + 2) - missile.getX(tps_tir*100 - 2))/(missile.getY(tps_tir*100 + 2) - missile.getY(tps_tir*100 - 2)));
    cout << endl;
    
    //Intervalles dans lesquels doit se trouver le LASER pour abattre le missile
    double deltaX = abs((missile.getLargeur()/2)*cos(ang_missile) + (missile.getHauteur()/2)*sin(ang_missile)); 
    double deltaY = abs((missile.getHauteur()/2)*cos(ang_missile) + (missile.getLargeur()/2)*sin(ang_missile));

    if(yL[tps_tir*100] - yLaser > 0)
    {
        int abattu = 0;
        while(i < missile.getXSize())
        {
            laser_track << xL[i] << " " << yL[i] << " " << missile.getX(i) << " " << missile.getY(i) << " " << xLaser << " " << yLaser << endl;
            i++;
            
            if(yL[i] >= yLaser)// && xL[i] >= xLaser)
            {
                laser_track << xL[i] << " " << yL[i] << " " << missile.getX(i) << " " << missile.getY(i) << " " << xL[i] << " " << tangente*xL[i] + (yLaser - xLaser*tangente) << endl;
                i++;
            }            
            
            if(abs(tangente*xL[tps_tir*100] + (yLaser - xLaser*tangente) - missile.getY(tps_tir*100)) < deltaY && abattu == 0 || abs(xL[tps_tir*100] - missile.getX(tps_tir*100)) < deltaX && abattu == 0)
            {
                cout << "Missile abattu ! " << endl;
                cout << "Delta sur Y : " << abs(tangente*xL[tps_tir*100] + (yLaser - xLaser*tangente) - missile.getY(tps_tir*100)) << endl;
                cout << "Delta sur X : " << abs(xL[tps_tir*100] - missile.getX(tps_tir*100)) << endl;
                abattu = 1;
            }
            
            if(i == missile.getXSize() - 1 && abattu == 0)
            {
                cout << "Rate, le missile est passe." << endl;
                cout << "Delta sur X : " << abs(xL[tps_tir*100] - missile.getX(tps_tir*100)) << endl; 
                cout << "Delta sur Y : " << abs(tangente*xL[tps_tir*100] + (yLaser - xLaser*tangente) - missile.getY(tps_tir*100)) << endl;
            }            
        }
    }
    
    if(yL[tps_tir*100] - yLaser < 0)
    {
        for(int i = 0; i < xL.size(); i++)
        {
            laser_track << xL[i] << " " << yL[i] << " " << missile.getX(i) << " " << missile.getY(i) << " " << xL[i] << " " << tangente*xL[i] + (yLaser - xLaser*tangente) << endl;
            
        }
        xL.clear();
        yL.clear();
        cout << "Trop tard, le missile a atteint sa cible." << endl;
        rate = 1;
    }
}

void LASER::TraceMissile(Missile missile)
{       
        vector<double> I; //Vecteur pour le Chi2, servant à minimiser les coeffs en comportant les différents intervalles temporels, tous espacés de 1/100 (un centième de seconde)
    
        //Création des coordonnées erronées
    int NbPoints = 200;
   for(int i = tps_detect*100; i < 200 + tps_detect*100; i++)
    {
        
        double errorX;
        double errorY;
        static random_device rd; 
        normal_distribution<double> distX(0, sigmaX); //Distribution normale pour générer l'erreur
        normal_distribution<double> distY(0, sigmaY);
        errorX = distX(rd);
        errorY = distY(rd);
        
        double x = errorX;
        
        xM.push_back(missile.getX(i) + x);
        
        double y = errorY;
        
        yM.push_back(missile.getY(i) + y);
        
        I.push_back(double(i)/100);
    }
    X(I, xM, sigmaX, NbPoints);
    Y(I, yM, sigmaY, NbPoints);
        
    int i = 0;
    while(aY*pow((double(i)/100),2) + (bY*double(i))/100 + cY >= 0)
    {
        xL.push_back((aX*double(i)/100) + bX);
        yL.push_back(aY*pow((double(i)/100),2) + (bY*double(i))/100 + cY);
        i++;
        if(aY*pow(double(i)/100,2) + bY*double(i)/100 + cY < 0)
        {
            xL.push_back((aX*double(i))/100 + bX);
            yL.push_back(0);
            break;
        }
    }
}

void LASER::XMClear()
{
    xM.clear();
}

void LASER::YMClear()
{
    yM.clear();
}

void LASER::pushbackYM(double a) 
{
    yM.push_back(a);
}

double LASER::getXMSize()
{
    return xM.size();
}
