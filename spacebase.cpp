#include "spacebase.h"


Spacebase::Spacebase(float coordinates_[3])
{
    mySpacebase = gluNewQuadric();
    coordinates[0]=coordinates_[0];//x
    coordinates[1]=coordinates_[1];//y
    coordinates[2]=coordinates_[2];//z
    rotation[0]=0.5f;//Angle
    rotation[1]=1.f;//x
    rotation[2]=0.f;//y
    rotation[3]=1.f;//z
}

Spacebase::~Spacebase()
{
    gluDeleteQuadric(mySpacebase);
}

void Spacebase::Display(uint64_t iTimeElapsed) const
{

    GLfloat chrome_ambiante[] = {0.25, 0.25, 0.25, 1.0};
    GLfloat chrome_diffuse[] = {0.4, 0.4, 0.4, 1.0};
    GLfloat chrome_speculaire[] = {0.774597, 0.774597, 0.774597, 1.0};
    GLfloat chrome_emission[] = {0.0, 0.0, 0.0, 1.0};
    float shininess = 76.8f;
    glMaterialfv(GL_FRONT, GL_AMBIENT, chrome_ambiante);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, chrome_diffuse);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, chrome_speculaire);
    glMaterialfv(GL_FRONT, GL_EMISSION, chrome_emission);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    float rayon_base=1.f;
   // glTranslatef(coordinates[0],coordinates[1],coordinates[2]);
    glRotatef(rotation[0]*iTimeElapsed,rotation[1],rotation[2],rotation[3]);
    //Base pricipale
    glPushMatrix();
    gluSphere(mySpacebase,rayon_base, 20,20);

    glTranslatef(rayon_base,0,0);
    glRotatef(90,0,1,0);
    gluCylinder(mySpacebase,rayon_base/4,rayon_base/4,rayon_base*2,20,20);
    glRotatef(-90,0,1,0);
    glTranslatef(rayon_base*2,0,0);
    gluSphere(mySpacebase,rayon_base/2, 20,20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-rayon_base,0,0);
    glRotatef(270,0,1,0);
    gluCylinder(mySpacebase,rayon_base/4,rayon_base/4,rayon_base*2,20,20);
    glRotatef(-270,0,1,0);
    glTranslatef(-rayon_base*2,0,0);
    gluSphere(mySpacebase,rayon_base/2, 20,20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,rayon_base,0);
    glRotatef(90,0,1,0);
    glRotatef(270,1,0,0);
    gluCylinder(mySpacebase,rayon_base/4,rayon_base/4,rayon_base*2,20,20);
    glRotatef(-270,1,0,0);
    glRotatef(-90,0,1,0);
    glTranslatef(0,rayon_base*2,0);
    gluSphere(mySpacebase,rayon_base/2, 20,20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-rayon_base,0);
    glRotatef(270,0,1,0);
    glRotatef(90,1,0,0);
    gluCylinder(mySpacebase,rayon_base/4,rayon_base/4,rayon_base*2,20,20);
    glRotatef(-90,1,0,0);
    glRotatef(-270,0,1,0);
    glTranslatef(0,-rayon_base*2,0);
    gluSphere(mySpacebase,rayon_base/2, 20,20);
    glPopMatrix();

    glPushMatrix();
    double rayon_cylindre=rayon_base*3.5+rayon_base*0.2;
    double hauteur_cylindre=rayon_cylindre/10;
    glTranslatef(0.f,0.f,-hauteur_cylindre/2);
    gluCylinder(mySpacebase,rayon_cylindre , rayon_cylindre,hauteur_cylindre , 30, 30);
    gluDisk(mySpacebase, 0, 0.4, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.f, 0.f, -rayon_base*2.5/2);
    gluCylinder(mySpacebase,rayon_base/2, rayon_base/2,rayon_base*2.5 , 20, 20);
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    QImage img (":/logo.png");
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

    glPushMatrix();
    gluQuadricNormals(mySpacebase,GLU_SMOOTH);
    gluQuadricTexture(mySpacebase, TRUE);
    glTranslatef(0.f, 0.f, -rayon_base*2.5/2);
    gluDisk(mySpacebase,0.f,rayon_base/2,20,20);
   // glTranslatef(0.f, 0.f, rayon_base*2.5);
    //gluDisk(mySpacebase,0.f,rayon_base/2,1000,1000);
    glPopMatrix();
    glPushMatrix();
    glDeleteTextures(1, &tex);
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);// on désactive pour ne pas gérer la lumière sur les plans


    GLfloat light_tab[] = {0.0, -200.0, 0.0, 0.0}; // directionnelle vers les -Y (du haut vers le bas)
    GLfloat lum_ambianteO[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat lum_diffuseO[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat lum_speculaireO[] = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_tab);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lum_ambianteO);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lum_diffuseO);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lum_speculaireO);
    glEnable(GL_LIGHT0);

    float x=((float) coordinates[0])+rayon_base*cos(45+rotation[0]*iTimeElapsed);
    float y=((float) coordinates[1])+rayon_base*sin(45+rotation[0]*iTimeElapsed);
    float z=(float)coordinates[2]+rayon_base*2.5/2;
    GLfloat light_tab_1[] = {x, y, z, 1.0};//Lumiere 1
    GLfloat lum_ambiante[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat lum_diffuse[] = {1.0, 1.0, 0.5, 1.0};
    GLfloat lum_speculaire[] = {1.0, 1.0, 0.5, 1.0};
    glLightfv(GL_LIGHT1, GL_POSITION, light_tab_1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, lum_ambiante);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lum_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lum_speculaire);
//    x=((float) coordinates[0])+rayon_base*cos(135+rotation[0]*iTimeElapsed);
//    y=((float) coordinates[1])+rayon_base*sin(135+rotation[0]*iTimeElapsed);
//    GLfloat light_tab_2[] = {x, y, (float)coordinates[2], 1.0};//Lumiere 2

//    glLightfv(GL_LIGHT2, GL_POSITION, light_tab_2);
//    glLightfv(GL_LIGHT2, GL_AMBIENT, lum_ambiante);
//    glLightfv(GL_LIGHT2, GL_DIFFUSE, lum_diffuse);
//    glLightfv(GL_LIGHT2, GL_SPECULAR, lum_speculaire);


//    x=((float) coordinates[0])+rayon_base*cos(225+rotation[0]*iTimeElapsed);
//    y=((float) coordinates[1])+rayon_base*sin(225+rotation[0]*iTimeElapsed);
//    GLfloat light_tab_3[] = {x, y, (float)coordinates[2], 1.0};//Lumiere 3

//    glLightfv(GL_LIGHT3, GL_POSITION, light_tab_3);
//    glLightfv(GL_LIGHT3, GL_AMBIENT, lum_ambiante);
//    glLightfv(GL_LIGHT3, GL_DIFFUSE, lum_diffuse);
//    glLightfv(GL_LIGHT3, GL_SPECULAR, lum_speculaire);

//    x=((float) coordinates[0])+rayon_base*cos(315+rotation[0]*iTimeElapsed);
//    y=((float) coordinates[1])+rayon_base*sin(315+rotation[0]*iTimeElapsed);
//    GLfloat light_tab_4[] = {x, y, (float)coordinates[2], 1.0};//Lumiere 4

//    glLightfv(GL_LIGHT4, GL_POSITION, light_tab_4);
//    glLightfv(GL_LIGHT4, GL_AMBIENT, lum_ambiante);
//    glLightfv(GL_LIGHT4, GL_DIFFUSE, lum_diffuse);
//    glLightfv(GL_LIGHT4, GL_SPECULAR, lum_speculaire);

    GLfloat plastic_ambiante[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat plastic_diffuse[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat plastic_speculaire[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat plastic_emission_yellow[] = {1., 1., 0., 1.0};

    float shininess2 = 32.f;

    glMaterialfv(GL_FRONT, GL_AMBIENT, plastic_ambiante);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, plastic_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, plastic_speculaire);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess2);

    if((iTimeElapsed/10)%2 == 0){
        glDisable(GL_LIGHT1);
//        glDisable(GL_LIGHT2);
//        glDisable(GL_LIGHT3);
//        glDisable(GL_LIGHT4);
    }
    else {
        glMaterialfv(GL_FRONT, GL_EMISSION, plastic_emission_yellow);
        glEnable(GL_LIGHT1);
//        glEnable(GL_LIGHT2);
//        glEnable(GL_LIGHT3);
//        glEnable(GL_LIGHT4);
    }



    //Lampes
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.f, 0.f, rayon_base*2.5/2);
    gluSphere(mySpacebase, rayon_base/3, 20, 20);

//    glPopMatrix();
//    glPushMatrix();
//    glRotatef(135.f,0.,0.,1.);
//    glTranslatef(rayon_base, 0.f, 0.f);
//    gluSphere(mySpacebase, 1, 20, 20);

//    glPopMatrix();
//    glPushMatrix();
//    glRotatef(225.f,0.,0.,1.);
//    glTranslatef(rayon_base, 0.f, 0.f);
//    gluSphere(mySpacebase, 1, 20, 20);

//    glPopMatrix();
//    glPushMatrix();
//    glRotatef(315.f,0.,0.,1.);
//    glTranslatef(rayon_base, 0.f, 0.f);
//    gluSphere(mySpacebase, 1, 20, 20);

    glDisable(GL_LIGHTING);
}
void Spacebase::updateCoordinates(float coordinates_[3]){
    coordinates[0]=coordinates_[0];//x
    coordinates[1]=coordinates_[1];//y
    coordinates[2]=coordinates_[2];//z
}
