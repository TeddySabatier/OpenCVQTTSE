
#include "opencv2/opencv.hpp"
#include "widget.h"
#include "ui_widget.h"
#include <QString>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/objdetect/objdetect.hpp>
#include <QMessageBox>
#include "displayw.h"

#include <cstdio>
#include <iostream>
#include <string>
#include <QTime>
#include <QKeyEvent>

using namespace std;

#include<Qpainter>

//constructeur de la fenêtre
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //connection des slots avec les signaux émis par une partie
    connect(ui->drawAreaSpace,SIGNAL(loseS()),this, SLOT(lose()));
    connect(ui->drawAreaSpace,SIGNAL(winS()),this, SLOT(win()));

    //initialisation des membres
    this->comboLoaded_=false;
    this->comboIndex_=0;
    this->score_=0;
    this->difficulty_=0;
    this->top1_ = -1;
    this->top2_ = -1;
    this->top3_ = -1;
    this->valChrono_=0;

    //ajout des modes de difficulté dans la combobox
    ui->asteroidComboBox->addItem("Difficulty 1 : 10 small asteroids");
    ui->asteroidComboBox->addItem("Difficulty 2 : 20 medium asteroids");
    ui->asteroidComboBox->addItem("Difficulty 3 : 15 large asteroids");

    comboLoaded_ = true;

    ui->score1label->setText("Top 1 : -");
    ui->score2label->setText("Top 2 : -");
    ui->score3label->setText("Top 3 : -");

    //initialisation de la webcam
    webCam_=new cv::VideoCapture(0);
    int width=webCam_->get(cv::CAP_PROP_FRAME_WIDTH);
    int height=webCam_->get(cv::CAP_PROP_FRAME_HEIGHT);

    if(!webCam_->isOpened())  // check if we succeeded
    {
        ui->infoLabel_->setText("Error openning the default camera !");
    }
    else
    {
        //lancement des timers d'affichage vidéo et du chrono

        ui->infoLabel_->setText(QString("Video ok, image size is %1x%2 pixels").arg(width).arg(height));
        timer_=new QTimer(this);
        connect(timer_, SIGNAL(timeout()), this, SLOT(display()));
        timer_->start(100);


        chrono_ = new QTimer;
        connect(chrono_,SIGNAL(timeout()),this,SLOT(timeout()));
        chrono_->start(1000);
    }
}

//destructeur de la fenêtre
Widget::~Widget()
{
    delete ui;
    delete webCam_;
}

//slot d'affichage d'une frame
void Widget::display(){

    cv::Mat frame,frame_gray;
    std::vector<cv::Rect> facesFist;
    std::vector<cv::Rect> facesFace;
    //Position of the head on X axis
    float faceX=0;
    //Positon of the right fist on Y axis
    float fistRY=-1;
    //Positon of the left fist on Y axis
    float fistLY=-1;
    //treshold for the app to detect if the ship need to turn or stay still
    float yTreshold=50;

    bool detectFists = false;
    bool detectPalm = false;


    if (webCam_->isOpened()) {
        if (webCam_->read(frame)) {   // Capture a frame

            // Mirror effect
            cv::flip(frame,frame,1);
            // Convert to gray
            cv::cvtColor(frame,frame_gray,cv::COLOR_BGR2GRAY);
            // Equalize graylevels
            //        equalizeHist( frame_gray, frame_gray );
            cv::CascadeClassifier face_cascadeFist;
            cv::CascadeClassifier face_cascadePalm;
            cv::CascadeClassifier face_cascadeFace;
            if(face_cascadePalm.load( "../projet-opencv/open_palm.xml" )){
            if( face_cascadeFist.load( "../projet-opencv/closed_frontal_palm.xml" ) )
            {


                //-- Detect open palm
                face_cascadePalm.detectMultiScale( frame_gray, facesFace, 1.1, 4, 0, cv::Size(60, 60) );
                if (facesFace.size()>0)
                {
                    // Draw Blue rectangle
                    for (int i=0;i<(int)facesFace.size();i++){
                        rectangle(frame,facesFace[i],cv::Scalar(255,0,0),2);
                    }

                    //déclenche un mouvement en avant si la webcam détecte deux mains ouvertes
                    if(facesFace.size() == 2){
                        detectPalm = true;
                        ui->infoLabel_->setText("Moving forward");
                        QKeyEvent* e = new QKeyEvent(QEvent::KeyPress,Qt::Key_Space,Qt::NoModifier,"");
                        ui->drawAreaSpace->keyPressEvent(e);
                    }else{
                        detectPalm = false;
                   }

                }


                //-- Detect Fists
                face_cascadeFist.detectMultiScale( frame_gray, facesFist, 1.1, 4, 0|cv::CASCADE_SCALE_IMAGE, cv::Size(60, 60) );
                if (facesFist.size()>0)
                {
                    float fist1x = -1;
                    float fist1y = -1;
                    float fist2x = -1;
                    float fist2y = -1;
                    // Draw green rectangle and gather fists coordinates
                    for (int i=0;i<(int)facesFist.size();i++){
                        rectangle(frame,facesFist[i],cv::Scalar(0,255,0),2);
                        if(fist1x == -1 && fist1y == -1){
                            fist1x=facesFist[i].x;
                            fist1y=facesFist[i].y;
                        }else{
                            fist2x=facesFist[i].x;
                            fist2y=facesFist[i].y;
                        }
                    }
                    if (fist1x < fist2x){
                        fistLY = fist1y;
                        fistRY = fist2y;
                    }else{
                        fistRY = fist1y;
                        fistLY = fist2y;
                    }
                }

                //if we detect 2 fists and their coordinates are valids
                if(fistRY != -1 && fistLY != -1 && facesFist.size() == 2){

                    detectFists = true;

                    //if the tow fists are detected
                    if((fistLY < fistRY + yTreshold) && ( fistLY>fistRY - yTreshold)){
                        //if the tow fists are at the same level

                        int h = frame.size().height/1.2;
                        int h_moy = (fistLY + fistRY)/2;



                        if( h_moy < h/3){
                            //déclenche un mouvement vers le haut
                            ui->infoLabel_->setText("Going up");
                            QKeyEvent* e = new QKeyEvent(QEvent::KeyPress,Qt::Key_Up,Qt::NoModifier,"");
                            ui->drawAreaSpace->keyPressEvent(e);
                        }else if(h_moy > 2*h/3){
                            //déclenche un mouvement vers le bas
                            ui->infoLabel_->setText("Going down");
                            QKeyEvent* e = new QKeyEvent(QEvent::KeyPress,Qt::Key_Down,Qt::NoModifier,"");
                            ui->drawAreaSpace->keyPressEvent(e);
                        }else{
                            //ne déclenche aucun mouvement
                            ui->infoLabel_->setText("Staying still");
                        }

                    }else if(fistLY > fistRY + yTreshold){
                        //if the right fist is higher than the left one : the ship turn left
                        ui->infoLabel_->setText("turn left");
                        QKeyEvent* e = new QKeyEvent(QEvent::KeyPress,Qt::Key_Left,Qt::NoModifier,"");
                        ui->drawAreaSpace->keyPressEvent(e);
                    }else if( fistLY<fistRY - yTreshold){
                        //if the right fist is lower than the left one : the ship turn right
                        ui->infoLabel_->setText("turn right");
                        QKeyEvent* e = new QKeyEvent(QEvent::KeyPress,Qt::Key_Right,Qt::NoModifier,"");
                        ui->drawAreaSpace->keyPressEvent(e);
                    }
                }else{
                     detectFists = false;
                }

                if( !detectFists && !detectPalm)
                    ui->infoLabel_->setText(" to many or to few fists are detected");

            }
            }
            // Invert Blue and Red color channels
            cvtColor(frame,frame,cv::COLOR_BGR2RGB);
            // Convert to Qt image
            QImage img= QImage((const unsigned char*)(frame.data),frame.cols,frame.rows,QImage::Format_RGB888);
            // Display on label
            ui->imageLabel_->setPixmap(QPixmap::fromImage(img));
            // Resize the label to fit the image
            //ui->imageLabel_->resize(ui->imageLabel_->pixmap().size());
            ui->imageLabel_->setScaledContents( true );


        }
        else {
            ui->infoLabel_->setText("Error capturing the frame");
        }
    }
}

void Widget::on_asteroidComboBox_currentIndexChanged(int index)
{
    int diff=0;
    switch(index){
    case 0:
        ui->comboBoxLabel->setText("Number of asteroids : " + QString::fromStdString(to_string(10)));
        diff=0;
        break;
    case 1:
        diff=1;
        break;
    case 2:
        diff=2;
        break;
    }

   if(comboLoaded_){
       QMessageBox::StandardButton reply;
         reply = QMessageBox::question(this, "Number of asteroids modified", "Modify the amount of asteroids in the scene will reaload the map,<br> are you sure you want to restart your game ?",
                                       QMessageBox::Yes|QMessageBox::No);
         if (reply == QMessageBox::Yes) {
           qDebug() << "Yes was clicked";
           difficulty_ = diff;
           this->comboIndex_ = index;
           switch(difficulty_){
           case 0:
               ui->comboBoxLabel->setText("Number of asteroids : " + QString::fromStdString(to_string(10)));
               break;
           case 1:
               ui->comboBoxLabel->setText("Number of asteroids : " + QString::fromStdString(to_string(20)));
               break;
           case 2:
               ui->comboBoxLabel->setText("Number of asteroids : " + QString::fromStdString(to_string(15)));
               break;
           }

           //redraw the QOpenGLWidget
           ui->drawAreaSpace->reloadW(diff);
           valChrono_ = 0;
           chrono_->start();

         } else {

           this->comboLoaded_ = false;
           ui->asteroidComboBox->setCurrentIndex(this->comboIndex_);
           this->comboLoaded_ = true;
         }
   }

}

//slot qui déclenche une victoire du joueur et calcule son score
void Widget::win(){

    calculateScore(valChrono_);
    refreshScoreTab();
    NewGame("You won !");
}

//slot qui déclenche une défaite du joueur et lui attribue le score 0
void Widget::lose(){
    score_ = 0;
    refreshScoreTab();
    NewGame("You lose !");
}

//déclenche une nouvelle partie sans victoire / défaite et ne raffraichis pas le score
void Widget::on_pushButton_clicked()
{
    NewGame("New game");
}

// Fonction de gestion d'interactions clavier
void Widget::keyPressEvent(QKeyEvent * e)
{
    qDebug()<<("Appui");
    ui->drawAreaSpace->keyPressEvent(e);
}

//fonction qui gère la fin d'une partie et propose au joueur d'en relancer une nouvelle
void Widget::NewGame(string message){

    //stope le chrono en cours
    chrono_->stop();

    if(message == "You lose !" || message == "You won !")
        message = message + "     Score : " + to_string(score_);

    //on récupère le niveau de difficulté sélectionné
    int diff=0;
    int index=ui->asteroidComboBox->currentIndex();
    switch(index){
    case 0:
        ui->comboBoxLabel->setText("Number of asteroids : " + QString::fromStdString(to_string(10)));
        diff=0;
        break;
    case 1:
        diff=1;
        break;
    case 2:
        diff=2;
        break;
    }


   if(comboLoaded_){
       QMessageBox::StandardButton reply;
         reply = QMessageBox::question(this, QString::fromStdString(message), "Would you like to restart a new game ?",
                                       QMessageBox::Yes|QMessageBox::No);
         if (reply == QMessageBox::Yes) {

           //redraw the QOpenGLWidget and restart the chrono
           ui->drawAreaSpace->reloadW(diff);
           valChrono_ = 0;
           chrono_->start();

         } else {
           // restart the chrono for the current game
           if(message == "New game")
               chrono_->start();
         }
   }

}

//incrémente le chrono du joueur toutes les secondes et affiche son temps au joueur
void Widget::timeout(){
    valChrono_++;
    int m = valChrono_/60;
    int s = valChrono_%60;
    std::stringstream label;
    label << "Chrono : " << std::setfill('0') << std::setw(2) << to_string(m)
          <<  ":" << std::setfill('0') << std::setw(2) << to_string(s);
    ui->chronoLabel->setText(QString::fromStdString(label.str()));

    //déclenche une défaite si le joueur ne gagne pas en 5 minutes
    if(valChrono_ > 300)
        lose();
}

//calcule le score en fonction du temps
void Widget::calculateScore(int time){
    int max = 300;
    if(time > max)
        score_ = 0;
    else
        score_ = (max - time)*3.33;
}

//raffraichis le tableau des scores du joueur
void Widget::refreshScoreTab(){
    int s1, s2, s3;
    s1 = top1_;
    s2 = top2_;
    s3 = top3_;

    if(score_ > s1){
        s3 = s2;
        s2 = s1;
        s1 = score_;
    }else if(score_ <= s1 && score_ > s2){
        s3 = s2;
        s2 = score_;
    }else if(score_ <= s2 && score_ > s3){
        s3 = score_;
    }

    top1_ = s1;
    top2_ = s2;
    top3_ = s3;

    if(score_ != 0){
        if(top1_ != -1)
           ui->score1label->setText("Top 1 : " + QString::fromStdString(to_string(top1_)));
        if(top2_ != -1)
           ui->score2label->setText("Top 2 : " + QString::fromStdString(to_string(top2_)));
        if(top3_ != -1)
           ui->score3label->setText("Top 3 : " + QString::fromStdString(to_string(top3_)));
    }
}
