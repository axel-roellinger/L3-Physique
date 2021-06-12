#ifndef DEF_MISSILE
#define DEF_MISSILE

#include <string>
#include <vector>

class Missile
{
	private:
	
	std::vector<double> x;    //Vecteurs contenant la position du missile
	std::vector<double> y;
	double theta;             //Angle de tir
	double v0;                //Vitesse initiale
    double hauteur;           //Dimensions du missile
    double largeur;
	
	public:
	
	Missile(double x0, double y0, double V0, double Theta, double H, double L); 
	~Missile();
	
	//Accesseurs
	double getXSize();
	double getX(int i);
	double getY(int i);
	double getV0();
	double getTheta();
    double getLargeur();
    double getHauteur();
    
    //Mutateurs
    void setHauteur(double);
    void setLargeur(double);
    void setX0(double);
    void setY0(double);
    void setV0(double a);
	void setTheta(double a);
    
    void Trajectoire();      //Points de mesure de la trajectoire du missile
};

#endif
