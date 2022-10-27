#ifndef CIRCLE_H
#define CIRCLE_H

#include<QPoint>

class Circle
{
    QPoint center_;
    int radius_;
public:
    Circle(const QPoint &center=QPoint(0,0),int radius=0);
    const QPoint &getCenter() {return center_;}
    int getRadius() {return radius_;}
};

#endif // CIRCLE_H
