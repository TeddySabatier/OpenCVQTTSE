#include "myglwidget.h"
#include <QApplication>

// Declarations des constantes
const unsigned int WIN = (500);

// Constructeur
MyGLWidget::MyGLWidget(QWidget * parent) : QOpenGLWidget(parent)
{
    // Reglage de la taille/position
    setFixedSize(WIN, WIN);

    // Connexion du timer
    connect(&m_AnimationTimer,  &QTimer::timeout, [&] {
        m_TimeElapsed += 1.0f;
        update();
    });

    m_AnimationTimer.setInterval(20);
    m_AnimationTimer.start();
}


// Fonction d'initialisation
void MyGLWidget::initializeGL()
{
    maVoiture=new Car();
    maRoute=new Ground();
}


// Fonction de redimensionnement
void MyGLWidget::resizeGL(int width, int height)
{
    // Definition du viewport (zone d'affichage)
    glViewport(0, 0, width, height);
}

// Fonction d'affichage
void MyGLWidget::paintGL()
{
    // ...


    // Affichage de la route
    // Affichage de la voiture




    glEnable(GL_LIGHTING);
    if((int)(m_TimeElapsed/10) % 2 ==0){
        glEnable(GL_LIGHT1);
        glEnable(GL_LIGHT2);
    }else{
        glDisable(GL_LIGHT1);
        glDisable(GL_LIGHT2);
    }
    glEnable(GL_LIGHT0);

    maVoiture->Display(m_TimeElapsed);
    glDisable(GL_LIGHTING);
    maRoute->Display(m_TimeElapsed);


}


// Fonction de gestion d'interactions clavier
void MyGLWidget::keyPressEvent(QKeyEvent * event)
{
    switch(event->key())
    {
    // Cas par defaut
    case Qt::Key_Left:
    {
        maVoiture->setPosition(maVoiture->getPosition()-0.5);
    }
        break;
    case Qt::Key_Right:
    {
        maVoiture->setPosition(maVoiture->getPosition()+0.5);
    }
        break;
    default:
    {
        // Ignorer l'evenement
        event->ignore();
        return;
    }
    }

    // Acceptation de l'evenement et mise a jour de la scene
    event->accept();
    update();
}
