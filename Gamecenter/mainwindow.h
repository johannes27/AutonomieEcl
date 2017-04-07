#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QGraphicsItem>
#include <QMainWindow>
#include <QPushButton>
#include <QGraphicsScene>
#include "spider.h"
#include "game2048.h"
#include <QMediaPlayer>
#include <QLabel>
#include <vector>
#include <QSpinBox>
using namespace std;





namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //SPIDER GAME :
    void init_spider();
    void messageWhenGameFinished();
    void reinit();
    void whenSpiderButtonClicked(int a);
    void nextRound();

    //2048 GAME :
    void init_2048();
    void updateField();
    void changeDimension(int dimension);
    void addNumber();
    void messageWhen2048Finished();
    void moveField();


protected:
    void keyPressEvent(QKeyEvent *event);


public slots:
    void on_buttonSpiderGame_clicked();
    void on_button1_clicked();
    void on_button2_clicked();
    void on_button3_clicked();
    void on_button4_clicked();
    void on_button5_clicked();
    void on_button6_clicked();
    void on_button7_clicked();
    void on_button8_clicked();
    void on_button9_clicked();

    void newGame();





private slots:
    void on_buttonNewSpiderGame_clicked();

    void on_actionMusic_triggered();

    void on_actionMute_triggered();

    void on_button2048Game_clicked();

    void on_pushButton_clicked();

    void on_actionReturn_to_Center_triggered();

    void on_actionQuit_triggered();

    void on_action3_triggered();

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_buttonfor3_clicked();

private:
    // SPIDER GAME:
    QGraphicsRectItem *rect;
    QGraphicsEllipseItem *arrayOfEllipses [9];
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;
    QPushButton *button4;
    QPushButton *button5;
    QPushButton *button6;
    QPushButton *button7;
    QPushButton *button8;
    QPushButton *button9;
    Spider s;
    QGraphicsScene *scene;
    int sound = 1;
    QMediaPlayer *music;
    Ui::MainWindow *ui;

    //2048 GAME :
    Game2048 g;
    QVector<QVector<QLabel*> >labelField;
    QPushButton *buttonNewGame;
    QPushButton *buttonChangeDimension;
    QLabel * pointsLabel;
    QSpinBox *spinbox;
    bool dimensionChosen = false;









};

#endif // MAINWINDOW_H
