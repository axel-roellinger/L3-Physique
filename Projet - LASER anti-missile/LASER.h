#ifndef DEF_LASER
#define DEF_LASER

#include <string>
#include <vector>
#include "Missile.h"
class LASER
{
private:
    //Position du LASER
    double xLaser; 
    double yLaser;
    double angle;
    
    //Incertitudes
    double sigmaX;
    double sigmaY;
    
    //Points de mesure "erronés" du missile
    std::vector<double> xM;
    std::vector<double> yM;
    
    //Temps de détection du missile
    double tps_detect;
    
    std::vector<double> x;
    std::vector<double> y;
    
    //Points servant à la trace complète du missile une fois les paramètres du modèle établis
    std::vector<double> xL;
    std::vector<double> yL;
    
    
    //Paramètre du modèle balistique
    double aX;
    double bX;
    double aY;
    double bY;
    double cY;
    
    int rate;   //Tir raté
    
public:
    LASER();
    LASER(double, double);
    ~LASER();
    
    //Accesseurs
    double getAngle();
    double getSigmaX();
    double getSigmaY();
    double getTpsDetect();
    double getXM(int);
    double getYM(int);
    double getXL(int);
    double getYL(int);
    double getAX();
    double getBX();
    double getAY();
    double getBY();
    double getCY();
    
    //Mutateurs
    void setSigmaX(double);
    void setSigmaY(double);
    void setAngle(double);
    void setXL(double, int);
    void setYL(double, int);
    void setXM(double, int);
    void setYM(double, int);
    
    //Fonctions nécessaires pour le Chi-2
    double SSig(double, int);
    double XN(std::vector<double>, double, int);
    double XNY(std::vector<double>, std::vector<double>, double, int);
    void X(std::vector<double>, std::vector<double>, double, int);  
    void Y(std::vector<double>, std::vector<double>, double, int);
    
    //Méthodes de trajectoire : 
    
    void Detection();  //Temps de détection (généré aléatoirement suivant une loi uniforme)
    
    void TirLaser(Missile);  //Méthode pour initier le tir du LASER, affichant la trajectoire de ce dernier et du missile (trace réelle et extrapolée)
    
    void TraceMissile(Missile); //Mesure de la trajectoire du missile pendant un court laps de temps pour créer le modèle d'extrapolation
    
    //Vide les vecteurs xM et yM
    void XMClear(); 
    void YMClear();
    
    void pushbackYM(double); //Sert à ajouter une ordonnée nulle lorsque celle du missile devient négative, pour interrompre le calcul
    double getXMSize();
    
};

#endif
