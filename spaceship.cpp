#include "spaceship.h"


Spaceship::Spaceship()
{
    mySpaceship = gluNewQuadric();
}

Spaceship::~Spaceship()
{
    gluDeleteQuadric(mySpaceship);
}

void Spaceship::Display(uint64_t iTimeElapsed) const
{
    float taille_vaisseau=1;//Rayon de la sphère dans laquelle est contenue le vaisseau

    glEnable(GL_TEXTURE_2D);
    QImage img (":/spaceship.jpg");
    QImage imgOpenGl=img.convertToFormat(QImage::Format_RGBA8888);
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width(), img.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, imgOpenGl.bits());
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, tex);
    gluQuadricNormals(mySpaceship,GLU_SMOOTH);
    gluQuadricTexture(mySpaceship, TRUE);
    //mySpaceship
    glBegin(GL_QUADS);
    //face dessus gauche
    glNormal3f(0.f, 1.f, 0.f);// vers les +y
    glTexCoord3f(-taille_vaisseau, 0.f, -taille_vaisseau);
    glVertex3f(-taille_vaisseau, 0.f, -taille_vaisseau);
    glTexCoord3f(0.f, taille_vaisseau/2, -taille_vaisseau);
    glVertex3f(0.f, taille_vaisseau/2, -taille_vaisseau);
    glTexCoord3f(0.f,0.f, taille_vaisseau);
    glVertex3f(0.f,0.f, taille_vaisseau);
    glTexCoord3f(-taille_vaisseau, 0.f, -taille_vaisseau);
    glVertex3f(-taille_vaisseau, 0.f, -taille_vaisseau);
    glEnd();
    glBegin(GL_QUADS);
    //face dessus droite
    glNormal3f(0.f, 1.f, 0.f);// vers les +y
    glTexCoord3f(taille_vaisseau, 0.f, -taille_vaisseau);
    glVertex3f(taille_vaisseau, 0.f, -taille_vaisseau);
    glTexCoord3f(0.f, taille_vaisseau/2, -taille_vaisseau);
    glVertex3f(0.f, taille_vaisseau/2, -taille_vaisseau);
    glTexCoord3f(0.f,0.f, taille_vaisseau);
    glVertex3f(0.f,0.f, taille_vaisseau);
    glTexCoord3f(taille_vaisseau, 0.f, -taille_vaisseau);
    glVertex3f(taille_vaisseau, 0.f, -taille_vaisseau);
    glEnd();
    glBegin(GL_QUADS);
    //face dessous gauche
    glNormal3f(0.f, -1.f, 0.f);// vers les -y
    glTexCoord3f(-taille_vaisseau, 0.f, -taille_vaisseau);
    glVertex3f(-taille_vaisseau, 0.f, -taille_vaisseau);
    glTexCoord3f(0.f, -taille_vaisseau/2, -taille_vaisseau);
    glVertex3f(0.f, -taille_vaisseau/2, -taille_vaisseau);
    glTexCoord3f(0.f,0.f, taille_vaisseau);
    glVertex3f(0.f,0.f, taille_vaisseau);
    glTexCoord3f(-taille_vaisseau, 0.f, -taille_vaisseau);
    glVertex3f(-taille_vaisseau, 0.f, -taille_vaisseau);
    glEnd();
    glBegin(GL_QUADS);
    //face dessous droite
    glNormal3f(0.f, -1.f, 0.f);// vers les -y
    glTexCoord3f(taille_vaisseau, 0.f, -taille_vaisseau);
    glVertex3f(taille_vaisseau, 0.f, -taille_vaisseau);
    glTexCoord3f(0.f, -taille_vaisseau/2, -taille_vaisseau);
    glVertex3f(0.f, -taille_vaisseau/2, -taille_vaisseau);
    glTexCoord3f(0.f,0.f, taille_vaisseau);
    glVertex3f(0.f,0.f, taille_vaisseau);
    glTexCoord3f(taille_vaisseau, 0.f, -taille_vaisseau);
    glVertex3f(taille_vaisseau, 0.f, -taille_vaisseau);
    glEnd();
    glBegin(GL_QUADS);
    //face arrière
    glNormal3f(0.f, 0.f, 1.f);// vers les -z
    glTexCoord3f(0.f, taille_vaisseau/2, -taille_vaisseau+0.000001f);
    glVertex3f(0.f, taille_vaisseau/2, -taille_vaisseau+0.000001f);
    glTexCoord3f(taille_vaisseau, 0.f, -taille_vaisseau+0.000001f);
    glVertex3f(taille_vaisseau, 0.f, -taille_vaisseau+0.000001f);
    glTexCoord3f(0.f, -taille_vaisseau/2, -taille_vaisseau+0.000001f);
    glVertex3f(0.f, -taille_vaisseau/2, -taille_vaisseau+0.000001f);
    glTexCoord3f(-taille_vaisseau, 0.f, -taille_vaisseau+0.000001f);
    glVertex3f(-taille_vaisseau, 0.f, -taille_vaisseau+0.000001f);

    glEnd();
    glPushMatrix();
    glTranslatef(-taille_vaisseau/4,0,-taille_vaisseau-taille_vaisseau/5);
    gluCylinder(mySpaceship,taille_vaisseau/8,taille_vaisseau/6,taille_vaisseau/5,1000,1000);
    glTranslatef(taille_vaisseau/2,0,0);
    gluCylinder(mySpaceship,taille_vaisseau/8,taille_vaisseau/6,taille_vaisseau/5,1000,1000);
    glPopMatrix();

    glDeleteTextures(1, &tex);
    glDisable(GL_TEXTURE_2D);


}
