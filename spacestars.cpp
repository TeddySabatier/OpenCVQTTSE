#include "spacestars.h"


Spacestars::Spacestars()
{
    spaceQ = gluNewQuadric();
}

Spacestars::~Spacestars()
{
    gluDeleteQuadric(spaceQ);
}

void Spacestars::Display(uint64_t iTimeElapsed) const
{
    glEnable(GL_TEXTURE_2D);
    QImage img (":/space.jpg");
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
    gluQuadricNormals(spaceQ,GLU_SMOOTH);
    gluQuadricTexture(spaceQ, TRUE);
    //roue arrière gauche
    glPushMatrix();
    gluSphere(spaceQ,50, 30,30);
    glPopMatrix();
    glDeleteTextures(1, &tex);
    glDisable(GL_TEXTURE_2D);


}
