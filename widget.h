#ifndef WIDGET_H
#define WIDGET_H

#include "opencv2/opencv.hpp"
#include <QWidget>
#include <QTimer>
#include <string>


namespace Ui {
class Widget;
}

//classe qui gère l'interface utilisateur et qui affiche au joueur son retour vidéo, l'écran de jeu et les informations de la partie
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();


private:
    Ui::Widget *ui; //interface graphique de la page principale
    cv::VideoCapture * webCam_; //objet de capture vidéo
    QTimer *timer_; //timer qui déclenche la lecture des frames de la webcam
    QTimer *chrono_; //timer qui déclenche le chrono lors des parties
    int score_; //score du joueur actualisé en fin de partie
    int difficulty_; //difficulté à partir de laquelle le joueur lance une nouvelle partie
    bool comboLoaded_; //booléen qui passe à true une fois la combobox chargée
    int comboIndex_; //indice de l'item de la combobox sélectionné par le joueur
    int top1_; //score top 1
    int top2_; //score top 2
    int top3_; //score top 3
    int valChrono_; //valeur temporelle du chrono

private slots:
    void display(); //détecte une frame de la webcam, la traite et affiche les résultat au joueur
    void on_asteroidComboBox_currentIndexChanged(int index); //change la difficulté de jeu lorsqu'un joueur sélectionne un nouveau mode
    void win(); //déclenche une victoire
    void lose(); //déclenche une défaite
    void on_pushButton_clicked(); //lancement d'une nouvelle partie
    void timeout(); //incrémentation du chrono et gestion de la limite de temps

public:
    void keyPressEvent(QKeyEvent* event);
    void NewGame(std::string message); //propose au joueur de relancer une nouvelle partie
    void calculateScore(int time); //calcule le score en fonction du temps mis par le joueur pour gagner
    void refreshScoreTab();// raffraichis le tableau des meilleurs scores
};

#endif // WIDGET_H
