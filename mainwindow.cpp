#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <cmath>
#include <QGraphicsDropShadowEffect>








MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    ui->userface->setText("0");

    calcVal = 0.0;
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
    powTrigger = false;
    userIsTypingSecondNumber = false;


    auto applyShadow = [](QWidget* widget) {
        QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect();
        shadow->setBlurRadius(15);
        shadow->setOffset(5, 5);
        shadow->setColor(QColor("#242526"));
        widget->setGraphicsEffect(shadow);
    };




    applyShadow(ui->userface);


    applyShadow(ui->buttplus);
    applyShadow(ui->buttminus);
    applyShadow(ui->buttstar);


    applyShadow(ui->butt1);
    applyShadow(ui->butt2);
    applyShadow(ui->butt3);
    applyShadow(ui->butt4);
    applyShadow(ui->butt5);
    applyShadow(ui->butt6);
    applyShadow(ui->butt7);
    applyShadow(ui->butt8);
    applyShadow(ui->butt9);
    applyShadow(ui->buttzero);
    applyShadow(ui->buttenter);




    applyShadow(ui->sinbutt);
    applyShadow(ui->cosbutt);
    applyShadow(ui->tanbutt);

    applyShadow(ui->delbuttn);
    applyShadow(ui->butt1overx);
    applyShadow(ui->buttpown);
    applyShadow(ui->buttback);
    applyShadow(ui->buttfrac);
    applyShadow(ui->buttroot);
    applyShadow(ui->buttsquar);
    applyShadow(ui->buttslash);
    applyShadow(ui->ansbutt);













    QPushButton *numButtons[10] = {
        ui->buttzero,
        ui->butt1,
        ui->butt2,
        ui->butt3,
        ui->butt4,
        ui->butt5,
        ui->butt6,
        ui->butt7,
        ui->butt8,
        ui->butt9
    };

    for(int i = 0; i < 10; ++i){
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }

    connect(ui->buttplus, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->buttminus, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->buttstar, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->buttslash, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->buttpown, SIGNAL(released()), this, SLOT(MathButtonPressed()));


    connect(ui->buttenter, SIGNAL(released()), this, SLOT(EqualButtonPressed()));
    connect(ui->buttfrac, SIGNAL(released()), this, SLOT(FractionButtonPressed()));
    connect(ui->buttback, SIGNAL(released()), this, SLOT(BackButtonPressed()));
    connect(ui->delbuttn, SIGNAL(released()), this, SLOT(ClearAllButtonPressed()));

    connect(ui->buttsquar, SIGNAL(released()), this, SLOT(UnaryButtonPressed()));
    connect(ui->buttroot, SIGNAL(released()), this, SLOT(UnaryButtonPressed()));
    connect(ui->butt1overx, SIGNAL(released()), this, SLOT(UnaryButtonPressed()));
    connect(ui->ansbutt, SIGNAL(released()), this, SLOT(AnsbuttonPressed()));


    connect(ui->sinbutt, SIGNAL(released()), this, SLOT(UnaryButtonPressed()));
    connect(ui->cosbutt, SIGNAL(released()), this, SLOT(UnaryButtonPressed()));
    connect(ui->tanbutt, SIGNAL(released()), this, SLOT(UnaryButtonPressed()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::NumPressed()
{
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->userface->text();

    if ((displayVal.toDouble() == 0 && !displayVal.contains(".")) || userIsTypingSecondNumber) {
        ui->userface->setText(butVal);
        userIsTypingSecondNumber = false;
    } else {
        QString newVal = displayVal + butVal;
        double dblNewVal = newVal.toDouble();
        ui->userface->setText(QString::number(dblNewVal, 'g', 16));
    }
}

void MainWindow::MathButtonPressed()
{
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
    powTrigger = false;

    QString displayVal = ui->userface->text();
    calcVal = displayVal.toDouble();

    QPushButton *button = (QPushButton *)sender();
    QString btnName = button->objectName();

    if (btnName == "buttslash") {
        divTrigger = true;
    } else if (btnName == "buttstar") {
        multTrigger = true;
    } else if (btnName == "buttplus") {
        addTrigger = true;
    } else if (btnName == "buttminus") {
        subTrigger = true;
    } else if (btnName == "buttpown") {
        powTrigger = true;
    }

    ui->userface->setText("");
}

void MainWindow::EqualButtonPressed()
{
    double solution = 0.0;
    QString displayVal = ui->userface->text();
    double dblDisplayVal = displayVal.toDouble();

    if (addTrigger || subTrigger || multTrigger || divTrigger || powTrigger) {
        if (addTrigger) {
            solution = calcVal + dblDisplayVal;
        } else if (subTrigger) {
            solution = calcVal - dblDisplayVal;
        } else if (multTrigger) {
            solution = calcVal * dblDisplayVal;
        } else if (divTrigger) {
            if (dblDisplayVal != 0.0) {
                solution = calcVal / dblDisplayVal;
            } else {
                ui->userface->setText("Error");
                return;
            }
        } else if (powTrigger) {
            solution = std::pow(calcVal, dblDisplayVal);
        }
    }

    ui->userface->setText(QString::number(solution, 'g', 16));
    userIsTypingSecondNumber = true;
    ansVal = solution;

    addTrigger = false;
    subTrigger = false;
    multTrigger = false;
    divTrigger = false;
    powTrigger = false;
}

void MainWindow::UnaryButtonPressed()
{
    QPushButton *button = (QPushButton *)sender();
    QString btnName = button->objectName();
    double displayVal = ui->userface->text().toDouble();
    double solution = 0.0;

    if (btnName == "buttsquar") {
        solution = std::pow(displayVal, 2);

    }
    else if (btnName == "buttroot") {
        if (displayVal < 0.0) {
            ui->userface->setText("Error");
            userIsTypingSecondNumber = true;
            return;
        }
        else {
            solution = std::sqrt(displayVal);
        }

    }
    else if (btnName == "butt1overx") {
        if (displayVal != 0.0) {
            solution = 1.0 / displayVal;

        } else {
            ui->userface->setText("Error");
            return;
        }


    } else if (btnName == "sinbutt" || btnName == "cosbutt" || btnName == "tanbutt") {
        const double PI = 3.14159265358979323846;
        double radians = displayVal * (PI / 180.0);

        if (btnName == "sinbutt") {
            solution = std::sin(radians);
        } else if (btnName == "cosbutt") {
            solution = std::cos(radians);
        } else if (btnName == "tanbutt") {
            solution = std::tan(radians);
        }

        if (std::abs(solution) < 1e-10) {
            solution = 0.0;
        }
    }

    ui->userface->setText(QString::number(solution, 'g', 16));
    userIsTypingSecondNumber = true;
}

void MainWindow::FractionButtonPressed()
{
    QString displayVal = ui->userface->text();
    if (!displayVal.contains(".")) {
        ui->userface->setText(displayVal + ".");
    }
}

void MainWindow::BackButtonPressed()
{
    QString displayVal = ui->userface->text();
    displayVal.chop(1);

    if (displayVal.isEmpty() || displayVal == "-") {
        displayVal = "0";
    }

    ui->userface->setText(displayVal);
}

void MainWindow::ClearAllButtonPressed()
{
    calcVal = 0.0;
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
    powTrigger = false;
    userIsTypingSecondNumber = false;

    ui->userface->setText("0");
}

void MainWindow::AnsbuttonPressed(){
    ui->userface->setText(QString::number(ansVal, 'g', 16));
    userIsTypingSecondNumber = false;
};





