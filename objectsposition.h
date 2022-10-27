#ifndef OBJECTSPOSITION_H
#define OBJECTSPOSITION_H


class ObjectsPosition
{
private:
    //Flottant contenant le rayon de l'objet
    float rayon;
    //Flottant contenant la coordonnée x de l'objet
    float x;
    //Flottant contenant la coordonnée y de l'objet
    float y;
    //Flottant contenant la coordonnée z de l'objet
    float z;
    int type;// 0 base, 1 asteroid
public:
    //Constructeur avec le rayon et les coordonnée et le type d'objet (Vaisseau, Asteroid, Base)
    ObjectsPosition(float rayon_,float x_,float y_,float z_,int type_=1);
    //Getter de la coordonnée x
    float getx();
    //Getter de la coordonnée y
    float gety();
    //Getter de la coordonnée z
    float getz();
    //Getter du rayon
    float getrayon();
    //Getter du type
    int gettype();
    //Setter de la coordonnée x
    void setx(float x_);
    //Setter de la coordonnée y
    void sety(float y_);
    //Setter de la coordonnée z
    void setz(float z_);
};

#endif // OBJECTSPOSITION_H
