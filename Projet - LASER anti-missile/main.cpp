#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <random>
#include <iomanip>
#include "LASER.h"
#include "Missile.h"
#include <algorithm>
#include <numeric>
#include <iterator>
#include <string>
#include <sstream>

using namespace std;

int main()
{
    int choix; 
    cout << "Bienvenue dans la session du LASER anti-missile" << endl;
    cout << "Methode Monte-Carlo, variables pre-definies : entrez 1" << endl;
    cout << "Methode Monte-Carlo, variables que vous definissez : entrez 2" << endl;
    cout << "Missile unique, intercepte par un LASER, variables pre-definies : entrez 3" << endl;
    cout << "Missile unique, intercepte par un LASER, variables que vous definissez : entrez 4" << endl;
    cout << "---------------------------------------------------------------------------------" << endl;
    cout << "Votre choix : ";
    cin >> choix;
    
    double x0, y0, v0, ang, H, L, sX, sY;
    int kmax;
    if(choix == 1)
    {
        kmax = 500; //Nombre de tirs pour la méthode Monte-Carlo
        x0 = 25; //Position de la tête du missile, on peut imaginer pun point de lancement quelconque, le missile pouvant alors être sur une plate-forme
        y0 = 25;
        v0 = 100; //Vitesse initiale
        ang = M_PI/4;
        sX = 1.5;
        sY = 1.5;
        H = 12; //m, mensurations d'un missile M51
        L = 2.3; //m
        cout << "Les parametres du missile sont les suivants : " << endl << "x0 = " << x0 << " m" << endl << "y0 = " << y0 << " m" << endl << "v0 = " << v0 << " m/s" << endl << "angle de tir : " << ang << " rad" << endl;
        cout << "Les incertitudes de mesure : " << endl << "sigma X = " << sX << " m" << endl << "sigma Y : " << sY << " m" << endl;
        goto debut;
    }
    
    if(choix == 2)
    {
        cout << "Entrer les dimensions du missile (hauteur puis largeur) : ";
        cin >> H >> L;
        cout << "ses coordonnees (x puis y) : ";
        cin >> x0 >> y0;
        cout << "sa vitesse et l'angle de lancement (en radians, entre 0 et 1.57) : ";
        cin >> v0 >> ang;
        cout << "l'incertitude de mesure sur X et sur Y : ";
        cin >> sX >> sY;
        cout << "et le nombre de tirs effectues : ";
        cin >> kmax;
        goto debut;
    }
   
    if(choix == 3)
    {
        kmax = 1;
        x0 = 25;
        y0 = 25;
        v0 = 500;
        ang = M_PI/4;
        sX = 1.5;
        sY = 1.5;
        H = 12;
        L = 2.3;
        cout << "Les parametres du missile sont les suivants : " << endl << "x0 = " << x0 << " m" << endl << "y0 = " << y0 << " m" << endl << "v0 = " << v0 << " m/s" << endl << "angle de tir : " << ang << " rad" << endl;
        cout << "Les incertitudes de mesure : " << endl << "sigma X = " << sX << " m" << endl << "sigma Y : " << sY << " m" << endl;
        goto debut;
    }
   
    if(choix == 4)
    {
        kmax = 1;
        cout << "Entrer les dimensions du missile (hauteur puis largeur) : ";
        cin >> H >> L;
        cout << "ses coordonnees (x puis y) : ";
        cin >> x0 >> y0;
        cout << "sa vitesse et l'angle de lancement (en radians, entre 0 et 1.57) : ";
        cin >> v0 >> ang;
        cout << "et l'incertitude de mesure sur X et sur Y : ";
        cin >> sX >> sY;
        goto debut;
    }
    
    debut:
    
    vector <double> x_y0; //Vecteur recueillant les sites de crash pour le Monte-Carlo 

    Missile missile1(x0, y0-H/2, v0, ang, H, L); //Initialisation du missile avec les paramètres définis plus haut
    missile1.Trajectoire(); //Création des points de trajectoire du missile
    LASER laser1(sX, sY); //Initialisation du LASER, coordonnées du LASER prédéfinies en aval
        
    ofstream site_crash("y_0_laser.txt");
        
    for(int k = 0; k < kmax; k++)
    { 
        laser1.Detection(); //Détection aléatoire du missile    
        laser1.TraceMissile(missile1); //Mesure de la trajectoire pendant un temps donné

        int i = 0;
    
        //La partie suivante est essentiellement utile à la méthode Monte-Carlo
        while(laser1.getAY()*pow(double(i)/100,2) + laser1.getBY()*double(i)/100 + laser1.getCY() > -10)
        {        
            if(laser1.getAY()*pow(double(i)/100,2) + laser1.getBY()*double(i)/100 + laser1.getCY() < 0 && laser1.getAX()*double(i)/100 + laser1.getBX() > missile1.getX(missile1.getXSize()-1)/2) //Condition d'arrêt 
            {
                string str = to_string(int(laser1.getAX()*double(i)/100 + laser1.getBX()));  //Parseur, permet d'arrondir les vitesses à la dizaine voire centaine en-dessous pour obtenir des graphes exploitables
                int sLength = str.length();
                int len = sLength-3;
                string str2 = str.substr(0, str.length() - len);
                while(str2.length() < str.length()) //Arrondi
                {
                    str2.append("0");
                }
                double numBuffer = stod(str2);  //Reprend la valeur arrondie en double
                x_y0.push_back(numBuffer);  //On l'inclue dans le vecteur utilisé pour l'affichage de la courbe
                break;
            }
        i++;
        }
        laser1.XMClear(); //Vide les données de mesure du LASER
        laser1.YMClear();
    }
    
    sort(x_y0.begin(), x_y0.end());
   

    if(kmax > 1) //Affichage pour la méthoe Monte-Carlo
    {
        for(int i = 0; i < x_y0.size(); i++)
        {
            int res = count(x_y0.begin(), x_y0.end(), x_y0[i]);
            site_crash << x_y0[i] << " " << res << endl;
        }
            system("gnuplot script_MC.gnu");    
    }
    
    if(kmax == 1 && choix == 3 || kmax == 1 && choix == 4) //Affichage de la trajectoire du missile et du LASER
    {
        laser1.TirLaser(missile1);
        string xMax = to_string(missile1.getX(missile1.getXSize()-1)*1.1); //Taille du canvas Gnuplot
        string yMax = to_string(missile1.getY((missile1.getXSize()/2)-1)*1.1);
        
        string cmd("gnuplot -c script_tir_laser.gnu ");
        cmd += xMax;
        cmd += " ";
        cmd += yMax;
        
        const char* commande = cmd.c_str();
        
        system(commande);
    }
        
    cout << "Point de crash réel : " << missile1.getX(missile1.getXSize()-1) << endl; //Vérification de la justesse de la méthode Monte-Carlo
    
    return 0;
}
