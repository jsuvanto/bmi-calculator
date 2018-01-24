// TIE-02006 fall 2017
// Project 03
// Juha Suvanto 189427
// jsuvanto@iki.fi

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QActionGroup>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

    // Calculates the BMI and shows it on screen.
    void calculate_bmi();

    // Resets the UI.
    void reset_ui();

    // Sets gender to female.
    void setFemale();

    // Sets gender to male.
    void setMale();

    // Interprets the BMI and shows it on screen.
    void interpret_bmi();

private:
    Ui::MainWindow *ui;
    bool female_;   // Gender is female if true, male if false.
    double bmi_;
    QString interpretation_;    // Stores the verbal interpretation of BMI. QString type because it's easier to use with Qt.
    void createActions();   // Helper function to create actions.
    void createMenus();     // Helper function to create and populate menus.

    // Menu items. These are declared because I didn't use Qt Designer to make the menus.
    // Also gets rid of having to use "ui->" when connecting etc.
    QMenu *actionMenu;
    QMenu *genderMenu;
    QAction *actionReset;
    QAction *actionQuit;
    QAction *actionSetFemale;
    QAction *actionSetMale;
    QActionGroup *gendergroup;

};

#endif // MAINWINDOW_HH
