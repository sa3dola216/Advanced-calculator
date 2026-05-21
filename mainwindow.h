#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void NumPressed();
    void MathButtonPressed();
    void EqualButtonPressed();
    void FractionButtonPressed();
    void BackButtonPressed();
    void UnaryButtonPressed();
    void ClearAllButtonPressed();
    void AnsbuttonPressed();

private:
    Ui::MainWindow *ui;
    double calcVal;
    double ansVal;

    bool divTrigger;
    bool multTrigger;
    bool addTrigger;
    bool subTrigger;
    bool powTrigger;

    bool userIsTypingSecondNumber;
};
#endif