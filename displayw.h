#ifndef __displayw_h_
#define __displayw_h_
#include <QOpenGLWidget>
#include <QKeyEvent>
#include <QTimer>
#include <vector>
#include <stdlib.h>
#include <QElapsedTimer>
#include "spaceship.h"
#include "asteroid.h"
#include "spacestars.h"
#include "spacebase.h"
#include "objectsposition.h"
// Classe dediee a l'affichage d'une scene OpenGL
class displayW : public QOpenGLWidget
{
Q_OBJECT

public:

    // Constructeur
    displayW(QWidget * parent = nullptr);

    // Fonction de gestion d'interactions clavier
    void keyPressEvent(QKeyEvent* event);
    //Destructeur
    ~displayW();

    //Rechargement
    void reloadW(int level_);
signals:
    void loseS();
    void winS();

protected:

    // Fonction d'initialisation
    void initializeGL();

    // Fonction de redimensionnement
    void resizeGL(int width, int height);

    // Fonction d'affichage
    void paintGL();

    //Permet de facilement garder les coordonées où on se situe avec les translates
    void applyTranslateToCoordinates(float x,float y, float z);

    //Génère la position de chaque objets
    void generatePositions(int level);

    //Vérifie si il y a un colision retourne 0 si pas de colision 1 si arrimage à la base 2 si colision avec asteroid
    int checkColision();


private:
    //Objet vaisseau spatial
    Spaceship* mySpaceship = nullptr;
    //Objet ciel étoilé (le fond)
    Spacestars* mySky = nullptr;
    //Tableau d'objets asteroids
    Asteroid* myAsteroids[100];
    //Objet base spatiale
    Spacebase* mySpacebase=nullptr;
    //Set de coordonnée utilisé pour positionner la base spatiale
    float coordinates[3]={0.f,0.f,0.f};
    //Timer pour dessiner les objets
    float m_TimeElapsed { 0.0f };
    QTimer m_AnimationTimer;
    //Vecteur d'objet ObjectsPositions pour stocker les positions et rayon des objets de la scène
    std::vector<ObjectsPosition> positions;
    //Nombre d'astéroid des la scène
    int nb_asteroid;
    //Tableau contennat les angles de rotations et la translation en avant
    float placement[3];
    //Vecteur 3d avec les coordonées de la caméra
    QVector3D camera;
    //Compteur de fps
    float fps[10];
    int fpsCounter=0;
    QElapsedTimer frame;
    //Entier valant 1 en cas de victoire et 2 en cas de défaite
    int win_lose=0;
    //Entier avec le niveau de difficulté choisi par l'utilisateur
    int level;



};
#endif
