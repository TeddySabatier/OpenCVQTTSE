#include "displayw.h"
#include <QApplication>
#include <GL/glu.h>
#include <math.h>

// Declarations des constantes
const unsigned int WIN = 900;
const double pi = std::acos(-1);
// Constructeur
displayW::displayW(QWidget * parent) : QOpenGLWidget(parent)
{
    // Reglage de la taille/position
    setFixedSize(WIN, WIN);

    // Connexion du timer
    connect(&m_AnimationTimer,  &QTimer::timeout, [&] {
        m_TimeElapsed += 1.0f;
        update();
    });

    m_AnimationTimer.setInterval(2);
    m_AnimationTimer.start();
}


// Fonction d'initialisation
void displayW::initializeGL()
{

    frame.start();


    switch(level){
    case 0:nb_asteroid=10;
        break;
    case 1:nb_asteroid=20;
        break;
    case 2: nb_asteroid=15;
        break;
    default:
        nb_asteroid=10;
    }

    generatePositions(level);
    mySky = new Spacestars();
    mySpaceship = new Spaceship();
    applyTranslateToCoordinates(positions.at(1).getx(), positions.at(1).gety(),positions.at(1).getz());
    mySpacebase = new Spacebase(coordinates);
    for(int i=2;i<nb_asteroid+2;i++){
        Asteroid *temp=new Asteroid(positions.at(i).getrayon());
        myAsteroids[i-2]=temp;

    }

    placement[0]=0.f;
    placement[1]=0.f;
    placement[2]=0.f;
    camera.setX(positions.at(0).getx());
    camera.setY(positions.at(0).gety());
    camera.setZ(positions.at(0).getz()-5);


}


// Fonction de redimensionnement
void displayW::resizeGL(int width, int height)
{
    // Definition du viewport (zone d'affichage)
    glViewport(0, 0, width, height);
}

// Fonction d'affichage
void displayW::paintGL()
{
    //Taille de la map un cube d'arrete 50.

    glEnable(GL_TEXTURE_2D);
    // activation du z_buffer
    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_TEST);
    // positionnement de la caméra
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.f, 1.f, 0.1f, 5000.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    int verticale=1;
    if(placement[1]>=90 || placement[1]<=-90){
        verticale=-1;
        if(placement[1]>=270 || placement[1]<=-270){
            verticale=1;
        }
        if(placement[1]>=360 || placement[1]<=-360){
            placement[1]=0;
        }
    }
    QVector3D vecteurCameraVaisseau;
    vecteurCameraVaisseau.setX(camera.x()-positions.at(0).getx());
    vecteurCameraVaisseau.setY(camera.y()-positions.at(0).gety());
    vecteurCameraVaisseau.setZ(camera.z()-positions.at(0).getz());
    if(win_lose==0){//Animation quand on gagne our quand on perd
        gluLookAt(camera.x(),camera.y(),camera.z(),positions.at(0).getx(),positions.at(0).gety(),positions.at(0).getz(), 0., verticale, 0.);
    }
    else{
        gluLookAt(camera.x()+10*cos(m_TimeElapsed/100),camera.y()+10*sin(m_TimeElapsed/100),camera.z(),positions.at(0).getx(),positions.at(0).gety(),positions.at(0).getz(), 0., verticale, 0.);

    }
    glPushMatrix();
    glTranslatef(positions.at(0).getx(),positions.at(0).gety(),positions.at(0).getz());
    glRotatef(placement[0],0.f,1.f,0.f);
    glRotatef(placement[1],1.f,0.f,0.f);
    mySpaceship->Display(m_TimeElapsed);
    glPopMatrix();
    glPushMatrix();
    mySky->Display(m_TimeElapsed);
    glPopMatrix();
    for(int i=2;i<nb_asteroid+2;i++){
        QVector3D vecteurCameraObjet;
        vecteurCameraObjet.setX(camera.x()-positions.at(i).getx());
        vecteurCameraObjet.setY(camera.y()-positions.at(i).gety());
        vecteurCameraObjet.setZ(camera.z()-positions.at(i).getz());
        float angleAlpha=(vecteurCameraObjet.x()*vecteurCameraVaisseau.x()+vecteurCameraObjet.y()*vecteurCameraVaisseau.y()+vecteurCameraObjet.z()*vecteurCameraVaisseau.z())/(vecteurCameraObjet.length()*vecteurCameraVaisseau.length());
        if(angleAlpha>0){
            glPushMatrix();
            glTranslatef(positions.at(i).getx(),positions.at(i).gety(),positions.at(i).getz());
            myAsteroids[i-2]->Display(m_TimeElapsed);
            glPopMatrix();
        }
    }
    QVector3D vecteurCameraObjet;
    vecteurCameraObjet.setX(camera.x()-positions.at(1).getx());
    vecteurCameraObjet.setY(camera.y()-positions.at(1).gety());
    vecteurCameraObjet.setZ(camera.z()-positions.at(1).getz());
    float angleAlpha=(vecteurCameraObjet.x()*vecteurCameraVaisseau.x()+vecteurCameraObjet.y()*vecteurCameraVaisseau.y()+vecteurCameraObjet.z()*vecteurCameraVaisseau.z())/(vecteurCameraObjet.length()*vecteurCameraVaisseau.length());
    if(angleAlpha>0){
        glEnable(GL_LIGHTING);
        glTranslatef(positions.at(1).getx(),positions.at(1).gety(),positions.at(1).getz());
        mySpacebase->Display(m_TimeElapsed);
        glPopMatrix();
        glDisable(GL_LIGHTING);
    }


    if(fpsCounter<=9){
        if(frame.elapsed()!=0){
            fps[fpsCounter]=1.f/(frame.elapsed()/1000.f);
            fpsCounter++;
        }
    }
    else{
        fpsCounter=0;
    }
    float moyenne=0;
    for(int i=0;i<10;i++){

        moyenne+=fps[i];
    }

    moyenne=moyenne/10;
    qDebug()<<moyenne;
    frame.restart();
}


// Fonction de gestion d'interactions clavier
void displayW::keyPressEvent(QKeyEvent * event)
{
    int vitesse_rotation=2;
    int verticale=1;
    if(placement[1]>=90 || placement[1]<=-90){
        verticale=-1;
        if(placement[1]>=270 || placement[1]<=-270){
            verticale=1;
        }
        if(placement[1]>=360 || placement[1]<=-360){
            placement[1]=0;
        }
    }

    placement[2]=0;
    if(win_lose==0){
        switch(event->key())
        {
        // Cas par defaut
        default:
        {
            // Ignorer l'evenement
            event->ignore();
            return;
        }
        case Qt::Key_Right:
        {
            if(verticale==1){
                placement[0]=placement[0]-vitesse_rotation;
            }
            else{
                placement[0]=placement[0]+vitesse_rotation;
            }

            break;
        }
        case Qt::Key_Left:
        {
            if(verticale==1){
                placement[0]=placement[0]+vitesse_rotation;
            }
            else{
                placement[0]=placement[0]-vitesse_rotation;
            }
            break;
        }
        case Qt::Key_Up:
        {
            placement[1] = placement[1]-vitesse_rotation;

            break;
        }
        case Qt::Key_Down:
        {
            placement[1] = placement[1]+vitesse_rotation;

            break;
        }
        case Qt::Key_Space:
        {
            placement[2]=0.5;
            float x=cos(qDegreesToRadians(placement[1]))*sin(qDegreesToRadians(placement[0]));
            float y=-sin(qDegreesToRadians(placement[1]));
            float z=cos(qDegreesToRadians(placement[1]))*cos(qDegreesToRadians(placement[0]));
            float posX=positions.at(0).getx()+placement[2]*x;
            float posY=positions.at(0).gety()+placement[2]*y;
            float posZ=positions.at(0).getz()+placement[2]*z;
            if(10>posX||posX>30||10>posY||posY>30||10>posZ||posZ>30){//Red Zone
                if(8>posX||posX>32||8>posY||posY>32||8>posZ||posZ>32){
                    placement[2]=0;
                    qDebug()<<"Out";
                }
            }

            break;
        }
        }
    }
    float x=cos(qDegreesToRadians(placement[1]))*sin(qDegreesToRadians(placement[0]));
    float y=-sin(qDegreesToRadians(placement[1]));
    float z=cos(qDegreesToRadians(placement[1]))*cos(qDegreesToRadians(placement[0]));

    positions.at(0).setx(positions.at(0).getx()+placement[2]*x);
    positions.at(0).sety(positions.at(0).gety()+placement[2]*y);
    positions.at(0).setz(positions.at(0).getz()+placement[2]*z);

    float cameraPosition=5;

    camera.setX(positions.at(0).getx()-cameraPosition*x);
    camera.setY(positions.at(0).gety()-cameraPosition*y);
    camera.setZ(positions.at(0).getz()-cameraPosition*z);
    win_lose=checkColision();
    if(win_lose==1){
        emit winS();
    }else{if(win_lose==2){
            emit loseS();
        }
    }
    // Acceptation de l'evenement et mise a jour de la scene
    event->accept();

    update();
}
void displayW::applyTranslateToCoordinates(float x,float y, float z){
    coordinates[0]=coordinates[0]+x;
    coordinates[1]=coordinates[1]+y;
    coordinates[2]=coordinates[2]+z;
}

void displayW::generatePositions(int level){
    srand ( time(NULL) );
    //Level 0 easy
    //10 asteroids
    //size between 1-2
    //Level 1 normal
    //20 asteroids
    //size between 1-2
    //Level 2 hard
    //15 asteroids
    //size between 1-3
    bool superposition=true;
    int x,y,z;
    int rayon=1;
    x=20;
    y=20;
    z=20;
    ObjectsPosition Vaisseau(rayon,x,y,z,0);
    positions.push_back(Vaisseau);

    do{//base
        rayon=1*3.5+1*0.2;
        x=10+rand()%20;
        y=10+rand()%20;
        z=10+rand()%20;
        foreach (ObjectsPosition temp, positions) {
            if(sqrtf((x-temp.getx())*(x-temp.getx())+(y-temp.gety())*(y-temp.gety())+(z-temp.getz())*(z-temp.getz()))<10+rayon+temp.getrayon()){// Si la distance entre les points est inférieur a la somme des rayon il y a superposition
                superposition=true;
                break;
            }
            else{
                superposition=false;
            }
        }
    }while(superposition);
    ObjectsPosition Base(rayon,x,y,z,2);
    positions.push_back(Base);

    if(level==0){
        for(int i=0;i<10;i++){ //10 astéroids
            do{
                rayon=(5+rand()%5)/5.f;
                x=10+rand()%20;
                y=10+rand()%20;
                z=10+rand()%20;
                foreach (ObjectsPosition temp, positions) {
                    if(sqrtf((x-temp.getx())*(x-temp.getx())+(y-temp.gety())*(y-temp.gety())+(z-temp.getz())*(z-temp.getz()))<rayon+temp.getrayon()){
                        superposition=true;
                        break;
                    }
                    else{
                        superposition=false;
                    }
                }
            }while(superposition);
            ObjectsPosition Asteroid(rayon,x,y,z,1);
            positions.push_back(Asteroid);
        }
    }
    if(level==1){
        for(int i=0;i<20;i++){ //20 astéroids
            do{
                rayon=(5+rand()%5)/5.f;
                x=10+rand()%20;
                y=10+rand()%20;
                z=10+rand()%20;
                foreach (ObjectsPosition temp, positions) {
                    if(sqrtf((x-temp.getx())*(x-temp.getx())+(y-temp.gety())*(y-temp.gety())+(z-temp.getz())*(z-temp.getz()))<rayon+temp.getrayon()){
                        superposition=true;
                        break;
                    }
                    else{
                        superposition=false;
                    }
                }
            }while(superposition);
            ObjectsPosition Asteroid(rayon,x,y,z,1);
            positions.push_back(Asteroid);
        }
    }
    if(level==2){
        for(int i=0;i<15;i++){ //20 astéroids
            do{
                rayon=(10+rand()%5)/5.f;
                x=10+rand()%20;
                y=10+rand()%20;
                z=10+rand()%20;
                foreach (ObjectsPosition temp, positions) {
                    if(sqrtf((x-temp.getx())*(x-temp.getx())+(y-temp.gety())*(y-temp.gety())+(z-temp.getz())*(z-temp.getz()))<rayon+temp.getrayon()){
                        superposition=true;
                        break;
                    }
                    else{
                        superposition=false;
                    }
                }
            }while(superposition);
            ObjectsPosition Asteroid(rayon,x,y,z,1);
            positions.push_back(Asteroid);
        }
    }
}
int displayW::checkColision(){
    int i=0;
    foreach (ObjectsPosition temp, positions) {
        if(i!=0){//Vaisseau donc on ne le vérifie pas
            if(i==1){//Base donc c'est gagner
                if(sqrtf((positions.at(0).getx()-temp.getx())*(positions.at(0).getx()-temp.getx())+(positions.at(0).gety()-temp.gety())*(positions.at(0).gety()-temp.gety())+(positions.at(0).getz()-temp.getz())*(positions.at(0).getz()-temp.getz()))<positions.at(0).getrayon()+temp.getrayon()){
                    return 1;
                }
            }else{//asteroid
                if(sqrtf((positions.at(0).getx()-temp.getx())*(positions.at(0).getx()-temp.getx())+(positions.at(0).gety()-temp.gety())*(positions.at(0).gety()-temp.gety())+(positions.at(0).getz()-temp.getz())*(positions.at(0).getz()-temp.getz()))<positions.at(0).getrayon()+temp.getrayon()){
                    return 2;
                }
            }
        }
        i++;
    }
    return 0;
}
displayW::~displayW(){
    free(mySpaceship);
    free(mySky);
    free(myAsteroids);
    free(mySpacebase);

}

void displayW::reloadW(int level_){
    level=level_;
    positions.clear();
    coordinates[0]=0.f;
    coordinates[1]=0.f;
    coordinates[2]=0.f;

    m_TimeElapsed=0.0f ;
    nb_asteroid=0;
    placement[0]=0.f;
    placement[1]=0.f;
    placement[2]=0.f;
    camera.setX(0.f);
    camera.setY(0.f);
    camera.setZ(0.f);

    fpsCounter=0;
    win_lose=0;

    initializeGL();
    update();
}


