#include "mainwindow.h"
#include "spider.h"
#include "ui_mainwindow.h"
#include "game2048.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QtCore>
#include <QtGui>
#include <QBrush>
#include <QMessageBox>
#include <QtAlgorithms>
#include <QMediaPlayer>
#include <iostream>
#include <QKeyEvent>
#include <vector>
using namespace std;




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    //mediaplayer
    music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sounds/music1.mp3"));
    music->play();

    //----------STARTMENU : -------------//

    ui->setupUi(this);
    this->setWindowTitle("ECL Gamecenter by Johannes");
    this->resize(1000,1000);
    QPixmap bkgnd(":/icons/background.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    //palette.setBrush(QPalette::Background, bkgnd);
    //this->setPalette(palette);


    ui->page_3->setFocusPolicy(Qt::StrongFocus); // only 2048 has to wait for input

    init_spider();
}
    // -------------GUI FOR SPIDER GAME : ---------------//

void MainWindow::init_spider()  {

    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);

    // lines between circles :
    QPen pen;
    pen.setColor(Qt::red);
    scene->addLine(0,0,400,400,pen);
    scene->addLine(0,0,0,400,pen);
    scene->addLine(0,0,400,0,pen);
    scene->addLine(0,400,400,400,pen);
    scene->addLine(400,0,400,400,pen);
    scene->addLine(0,400,400,0,pen);
    scene->addLine(0,200,400,200,pen);
    scene->addLine(200,0,200,400,pen);

    // Circles :

    for(int i=0;i<9;i++) {
        arrayOfEllipses[i] = new QGraphicsEllipseItem();
        arrayOfEllipses[i]->setBrush(* new QBrush(Qt::gray));
    }

    arrayOfEllipses[0]->setRect(-20,-20,40,40);
    arrayOfEllipses[1]->setRect(180,-20,40,40);
    arrayOfEllipses[2]->setRect(380,-20,40,40);
    arrayOfEllipses[3]->setRect(-20,180,40,40);
    arrayOfEllipses[4]->setRect(180,180,40,40);
    arrayOfEllipses[5]->setRect(380,180,40,40);
    arrayOfEllipses[6]->setRect(-20,380,40,40);
    arrayOfEllipses[7]->setRect(180,380,40,40);
    arrayOfEllipses[8]->setRect(380,380,40,40);


    // Buttons behind circles that can be clicked by user to play :

    // Initialisation :
    button1 = new QPushButton();
    button2 = new QPushButton();
    button3 = new QPushButton();
    button4 = new QPushButton();
    button5 = new QPushButton();
    button6 = new QPushButton();
    button7 = new QPushButton();
    button8 = new QPushButton();
    button9 = new QPushButton();

    // Positionning :
    button1->setGeometry(QRect(-20,-20,40,40));
    button7->setGeometry(QRect(-20,380,40,40));
    button3->setGeometry(QRect(380,-20,40,40));
    button9->setGeometry(QRect(380,380,40,40));
    button5->setGeometry(QRect(180,180,40,40));
    button4->setGeometry(QRect(-20,180,40,40));
    button8->setGeometry(QRect(180,380,40,40));
    button2->setGeometry(QRect(180,-20,40,40));
    button6->setGeometry(QRect(380,180,40,40));

    // Buttons behind circles shouldn't be visible
    QBrush tb(Qt::transparent); // Transparent brush, solid pattern
    button1->setPalette(QPalette(tb, tb, tb, tb, tb, tb, tb, tb, tb));
    button2->setPalette(QPalette(tb, tb, tb, tb, tb, tb, tb, tb, tb));
    button3->setPalette(QPalette(tb, tb, tb, tb, tb, tb, tb, tb, tb));
    button4->setPalette(QPalette(tb, tb, tb, tb, tb, tb, tb, tb, tb));
    button5->setPalette(QPalette(tb, tb, tb, tb, tb, tb, tb, tb, tb));
    button6->setPalette(QPalette(tb, tb, tb, tb, tb, tb, tb, tb, tb));
    button7->setPalette(QPalette(tb, tb, tb, tb, tb, tb, tb, tb, tb));
    button8->setPalette(QPalette(tb, tb, tb, tb, tb, tb, tb, tb, tb));
    button9->setPalette(QPalette(tb, tb, tb, tb, tb, tb, tb, tb, tb));
    button1->setFlat(true);
    button2->setFlat(true);
    button3->setFlat(true);
    button4->setFlat(true);
    button5->setFlat(true);
    button6->setFlat(true);
    button7->setFlat(true);
    button8->setFlat(true);
    button9->setFlat(true);

    // connect buttons to functions :
    QObject::connect(button1,SIGNAL(clicked()),this,SLOT(on_button1_clicked()));
    QObject::connect(button2,SIGNAL(clicked()),this,SLOT(on_button2_clicked()));
    QObject::connect(button3,SIGNAL(clicked()),this,SLOT(on_button3_clicked()));
    QObject::connect(button4,SIGNAL(clicked()),this,SLOT(on_button4_clicked()));
    QObject::connect(button5,SIGNAL(clicked()),this,SLOT(on_button5_clicked()));
    QObject::connect(button6,SIGNAL(clicked()),this,SLOT(on_button6_clicked()));
    QObject::connect(button7,SIGNAL(clicked()),this,SLOT(on_button7_clicked()));
    QObject::connect(button8,SIGNAL(clicked()),this,SLOT(on_button8_clicked()));
    QObject::connect(button9,SIGNAL(clicked()),this,SLOT(on_button9_clicked()));

    // add all Items created to scene, otherwise not visible :
    scene->addWidget(button1);
    scene->addWidget(button2);
    scene->addWidget(button3);
    scene->addWidget(button4);
    scene->addWidget(button5);
    scene->addWidget(button6);
    scene->addWidget(button7);
    scene->addWidget(button8);
    scene->addWidget(button9);

    for(int i=0;i<9;i++) {
        scene->addItem(arrayOfEllipses[i]);
    }

    ui->label_5->setText(QString::number(0));
    ui->label_6->setText(QString::number(0));

}

    //------------- GUI FOR 2048 GAME :------------//

void MainWindow::init_2048() {

    // create Matrix [dim]X[dim] of Labels :
    for(int i = 0; i < g.getDimension(); i++)  {
        QVector <QLabel*> temp;
        for(int j = 0; j < g.getDimension(); j++)  {
            temp.push_back(new QLabel("",this));
        }
        labelField.push_back(temp);
    }

    // set properties of labels (font,style) :
    for(int i=0;i<g.getDimension();i++) {
        for(int j=0;j<g.getDimension();j++) {
            labelField[i][j]->setStyleSheet("border:20px solid grey");
            labelField[i][j]->setAlignment(Qt::AlignCenter);
            labelField[i][j]->setStyleSheet("QLabel { background-color : beige;  }");
            QFont f("Arial",40,QFont::Bold);
            labelField[i][j]->setFont(f);
            ui->gridLayout->addWidget(labelField[i][j],i+1,j);
        }
    }

    // create button for starting a new game :
    buttonNewGame = new QPushButton("NEW GAME");
    buttonNewGame->setStyleSheet("QPushButton { background-color: yellow; }");
    ui->gridLayout->addWidget(buttonNewGame,0,0);
    QObject::connect(buttonNewGame,SIGNAL(clicked()),this,SLOT(newGame()));

    // create Label to show points of each player :
    QPalette* palettePoints = new QPalette();
    palettePoints->setColor(QPalette::WindowText,Qt::yellow);
    pointsLabel = new QLabel();
    pointsLabel->setText("Points : " + QString::number(0));
    pointsLabel->setPalette(*palettePoints);
    pointsLabel->setAlignment(Qt::AlignCenter);
    QFont f("Arial",16,QFont::Bold);
    pointsLabel->setFont(f);
    ui->gridLayout->addWidget(pointsLabel,0,1);

    // update field
    updateField();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//------------FONCTIONALITIES FOR SPIDER GAME :-----------//

// function is appealed when a round has been finished
// fields have to be resetted (attributes AND interface) :
void MainWindow::nextRound() {
    for (int i=1;i<=9;i++) {
        s.setField(i,0);
        s.setFieldPlayed(i,false);
    }
    s.setWinner(0);
    s.setCurrentPlayer(1);
    s.setGameFinished(false);
    for (int i=0;i<9;i++) {
    arrayOfEllipses[i]->setBrush(* new QBrush(Qt::gray));
    }

}

// function is appealed to start a new Game :
void MainWindow::reinit() {
    for (int i=1;i<=9;i++) {
        s.setField(i,0);
        s.setFieldPlayed(i,false);
    }
    s.setWinner(0);
    s.setCurrentPlayer(1);
    s.setGameFinished(false);
    for (int i=0;i<9;i++) {
    arrayOfEllipses[i]->setBrush(* new QBrush(Qt::gray));
    }
    s.resetWinsOfPlayer();
    ui->label_5->setText(QString::number(0));
    ui->label_6->setText(QString::number(0));
}

// when a round is finished, a window pops up and show whether
// it's a win for player 1 or 2 or a draw :
void MainWindow::messageWhenGameFinished() {

    QPalette palette;
    palette.setColor(QPalette::Background, Qt::cyan);
    s.printBoard();
    switch(s.checkWin()) {
        case 1 :
            {
            QString win = "The winner is : " + QString::number(s.getWinner());
            QMessageBox::information(this,"Game finished",win);
            ui->label_5->setText(QString::number(s.getWinsOfPlayer(1)));
            ui->label_6->setText(QString::number(s.getWinsOfPlayer(2)));
            nextRound();
            break;
            }
        case 0 :
            QMessageBox::information(this,"Game finished","DRAW!");
            nextRound();
            break;
        default : break;
    };
}

// connect buttons of cercles to the whenSpiderButtonClicked method
// that executes a move :
void MainWindow::on_button1_clicked() {
    whenSpiderButtonClicked(1);
    cout<<"Button 1 clicked"<<endl;
}
void MainWindow::on_button2_clicked() {
    whenSpiderButtonClicked(2);
    cout<<"Button 2 clicked"<<endl;
}
void MainWindow::on_button3_clicked() {
    whenSpiderButtonClicked(3);
    cout<<"Button 3 clicked"<<endl;
}
void MainWindow::on_button4_clicked() {
    whenSpiderButtonClicked(4);
    cout<<"Button 4 clicked"<<endl;
}
void MainWindow::on_button5_clicked() {
    whenSpiderButtonClicked(5);
    cout<<"Button 5 clicked"<<endl;
}
void MainWindow::on_button6_clicked() {
    whenSpiderButtonClicked(6);
    cout<<"Button 6 clicked"<<endl;

}
void MainWindow::on_button7_clicked() {
    whenSpiderButtonClicked(7);
    cout<<"Button 7 clicked"<<endl;

}
void MainWindow::on_button8_clicked() {
    whenSpiderButtonClicked(8);
    cout<<"Button 8 clicked"<<endl;

}
void MainWindow::on_button9_clicked() {
   whenSpiderButtonClicked(9);
   cout<<"Button 9 clicked"<<endl;

}

// when player clicks a circle button, the move fonction of the spider class is executed
// and the circle has to be filled with the color of the current player :
void MainWindow::whenSpiderButtonClicked(int a) {
    s.move(a);
    if (s.getField(a)==1) arrayOfEllipses[a-1]->setBrush(* new QBrush(Qt::blue));
    else if(s.getField(a)==2) arrayOfEllipses[a-1]->setBrush(* new QBrush(Qt::yellow));
    else if(s.getField(a)==0) qDebug("DOESNT WORK");
    messageWhenGameFinished();
    s.switchPlayer();
}

// Menu -> Spider Game
void MainWindow::on_buttonSpiderGame_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_actionMusic_triggered()
{
    if (sound == 1) {
        sound = 2;
        music->setMedia(QUrl("qrc:/sounds/music2.mp3"));
    }
    else if(sound == 2) {
        sound = 1;
        music->setMedia(QUrl("qrc:/sounds/music1.mp3"));
    }

    qDebug("change music!");
    music->play();

}

// ----------MENU FONCTIONALITIES :---------------//

// pause music :
void MainWindow::on_actionMute_triggered()
{
    music->pause();
}

// start spider Game :
void MainWindow::on_buttonNewSpiderGame_clicked()
{
    qDebug("new Game");
    reinit();
}

// restart 2048 Game
// first time : chose dimension
// after that : returning = continuing old game
void MainWindow::on_button2048Game_clicked()
{
    if(dimensionChosen == false) {
    ui->stackedWidget->setCurrentIndex(1);
    } else {
        ui->stackedWidget->setCurrentIndex(3);
    }
}

//reinitialisation of Game Spider :
void MainWindow::on_pushButton_clicked()
{
    reinit();

}
 // return to main menu :
void MainWindow::on_actionReturn_to_Center_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
}

// quit the program :
void MainWindow::on_actionQuit_triggered()
{
    close();
}


//------------FONCTIONALITIES 2048 GAME :----------------//

// update colors and text of label matrix by connecting 2048 game attributes
// to the interface :
void MainWindow::updateField() {

    cout<<"UPDATE FIELD"<<endl;
    QPalette* paletteLabels = new QPalette();
    paletteLabels->setColor(QPalette::WindowText,Qt::black);

    for(int i=0;i<g.getDimension();i++) {
        for(int j=0;j<g.getDimension();j++) {
            switch (g.getField(i,j)) {
                case 2 :
                    cout<<"getField = "<<g.getField(i,j)<<"i="<<i<<"j="<<j<<endl;
                    labelField[i][j]->setStyleSheet("QLabel { background-color : beige;  }");
                    labelField[i][j]->setPalette(*paletteLabels);
                    labelField[i][j]->setText(QString::number(2));
                    break;
                case 4 :
                    labelField[i][j]->setStyleSheet("QLabel { background-color : palegoldenrod;  }");
                    labelField[i][j]->setPalette(*paletteLabels);
                    labelField[i][j]->setText(QString::number(4));
                    break;
                case 8 :
                    labelField[i][j]->setStyleSheet("QLabel { background-color : lightcoral;  }");
                    labelField[i][j]->setPalette(*paletteLabels);
                    labelField[i][j]->setText(QString::number(g.getField(i,j)));
                    break;
                case 16 :
                    labelField[i][j]->setStyleSheet("QLabel { background-color : coral;  }");
                    labelField[i][j]->setPalette(*paletteLabels);
                    labelField[i][j]->setText(QString::number(g.getField(i,j)));
                    break;
                case 32 :
                    labelField[i][j]->setStyleSheet("QLabel { background-color : lightsalmon;  }");
                    labelField[i][j]->setPalette(*paletteLabels);
                    labelField[i][j]->setText(QString::number(g.getField(i,j)));
                    break;
                case 64 :
                    labelField[i][j]->setStyleSheet("QLabel { background-color : salmon;  }");
                    labelField[i][j]->setPalette(*paletteLabels);
                    labelField[i][j]->setText(QString::number(g.getField(i,j)));
                    break;
                case 128 :
                    labelField[i][j]->setStyleSheet("QLabel { background-color : darksalmon;  }");
                    labelField[i][j]->setPalette(*paletteLabels);
                    labelField[i][j]->setText(QString::number(g.getField(i,j)));
                    break;
                case 256 :
                    labelField[i][j]->setStyleSheet("QLabel { background-color : chocolate;  }");
                    labelField[i][j]->setPalette(*paletteLabels);
                    labelField[i][j]->setText(QString::number(g.getField(i,j)));
                    break;
                case 512 :
                    labelField[i][j]->setStyleSheet("QLabel { background-color : tomato;  }");
                    labelField[i][j]->setPalette(*paletteLabels);
                    labelField[i][j]->setText(QString::number(g.getField(i,j)));
                    break;
                case 1024 :
                    labelField[i][j]->setStyleSheet("QLabel { background-color : orangered;  }");
                    labelField[i][j]->setPalette(*paletteLabels);
                    labelField[i][j]->setText(QString::number(g.getField(i,j)));
                    break;
                case 2048 :
                    labelField[i][j]->setStyleSheet("QLabel { background-color : red;  }");
                    labelField[i][j]->setPalette(*paletteLabels);
                    labelField[i][j]->setText(QString::number(g.getField(i,j)));
                    break;
                case 4096 :
                    labelField[i][j]->setStyleSheet("QLabel { background-color : darkred;  }");
                    labelField[i][j]->setPalette(*paletteLabels);
                    labelField[i][j]->setText(QString::number(g.getField(i,j)));
                    break;
                default :
                    labelField[i][j]->setStyleSheet("QLabel { background-color : beige;  }");
                    labelField[i][j]->setText("");
                    break;

            }
            }
        }

    g.getPoints();
    pointsLabel->setText("Points : " + QString::number(g.getPoints()));
}

// start the game (MENU->2048 window) :
void MainWindow::newGame() {
    cout<<"NEW GAME 2048 FONCTION RUNS"<<endl;
    g.reinit();
    ui->page_3->setFocusPolicy(Qt::StrongFocus);
    updateField();
}

// get users input of arrow keys to do a move :
/*
 * Here is a little error : in line 48 the 2048 game window was focused to
 * receive users input. When you click new game, you have to click on
 * the game window afterwards to refocus the window, otherwise the program
 * does not get your key input.
 *
 */
void MainWindow::keyPressEvent(QKeyEvent *event) {

    switch(event->key()) {
        case Qt::Key_Right :
            messageWhen2048Finished();
            g.moveRight();
            moveField();
            break;

        case Qt::Key_Left :
            messageWhen2048Finished();
            g.moveLeft();
            moveField();
            break;

        case Qt::Key_Up :
            messageWhen2048Finished();
            g.moveUp();
            moveField();
            break;

        case Qt::Key_Down :
            messageWhen2048Finished();
            g.moveDown();
            moveField();
            break;

        default : break;

    };
    g.setCounterPossibleMoves(0);
}

void MainWindow::addNumber() {

    //decide if add number or not after move
    if(g.getCounterPossibleMoves() > 0) {
        g.addNumber();
    }
}

void MainWindow::moveField() {
    cout<<"bool gameover ?"<<g.checkForGameOver()<<endl;
    addNumber();
    updateField();
    g.printField();
}

// change dimension of the matrix :
void MainWindow::changeDimension(int dimension) {
    g.setDimension(dimension);
}


// if dimension choosed = 4 :
void MainWindow::on_pushButton_6_clicked()
{
    g.setDimension(4);
    cout<<"Dimension choosen 4, dim = "<<g.getDimension()<<endl;
    dimensionChosen = true;
    g.init(4);
    init_2048();
    ui->stackedWidget->setCurrentIndex(3);
}

// if dimension choosed = 5 :
void MainWindow::on_pushButton_5_clicked()
{
    g.setDimension(5);
    cout<<"Dimension choosen 5, dim = "<<g.getDimension()<<endl;
    dimensionChosen = true;
    g.init(5);
    init_2048();
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::messageWhen2048Finished() {
    QPalette palette;
    palette.setColor(QPalette::Background, Qt::cyan);
    if (g.checkForGameOver() == true) {
            QString gameover = "GAMEOVER ! Your score : " + QString::number(g.getPoints());
            QMessageBox::information(this,"Game finished",gameover);
     }

}









