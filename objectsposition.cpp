#include "objectsposition.h"

ObjectsPosition::ObjectsPosition(float rayon_,float x_,float y_,float z_,int type_)
{
    rayon=rayon_;
    x=x_;
    y=y_;
    z=z_;
    type=type_;
}
float ObjectsPosition::getx()
{
    return x;
}
float ObjectsPosition::gety()
{
    return y;
}
float ObjectsPosition::getz()
{
    return z;
}
float ObjectsPosition::getrayon()
{
    return rayon;
}
int ObjectsPosition::gettype()
{
    return type;
}

void ObjectsPosition::setx(float x_)
{
    x=x_;
}
void ObjectsPosition::sety(float y_)
{
    y=y_;
}void ObjectsPosition::setz(float z_)
{
    z=z_;
}
