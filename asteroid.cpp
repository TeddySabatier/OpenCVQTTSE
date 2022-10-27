#include "asteroid.h"


Asteroid::Asteroid(float taille_asteroid_)
{
 //   srand ( time(NULL) );
    asteroidQ = gluNewQuadric();
    taille_asteroid=taille_asteroid_;
    nb_vertex=8+rand()%4;
}

Asteroid::~Asteroid()
{
    gluDeleteQuadric(asteroidQ);
}

void Asteroid::Display(uint64_t iTimeElapsed) const
{
    glEnable(GL_TEXTURE_2D);
    QImage img (":/asteroid.jpg");
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
    gluQuadricNormals(asteroidQ,GLU_SMOOTH);
    gluQuadricTexture(asteroidQ, TRUE);
    //Asteroid
    glPushMatrix();
    gluSphere(asteroidQ,taille_asteroid, nb_vertex,nb_vertex);
    glPopMatrix();
    glDeleteTextures(1, &tex);
    glDisable(GL_TEXTURE_2D);


}

Asteroid::Asteroid(const Asteroid &Copy){
    asteroidQ = gluNewQuadric();
    taille_asteroid=Copy.taille_asteroid;
}
