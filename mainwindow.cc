// TIE-02006 fall 2017
// Project 03
// Juha Suvanto 189427
// jsuvanto@iki.fi


#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include <QActionGroup>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    female_(true),
    bmi_(0.0)
{
    ui->setupUi(this);

    // I'm using helper functions to draw the menus. I could've done this in the Qt Designer but chose not to.
    createActions();
    createMenus();

    // Whenever the value in either spinbox changed, update the BMI.
    // Sliders and spinboxes are connected in Qt Designer's slot and signal editor.
    connect(ui->spinbox_height, SIGNAL(valueChanged(int)), this, SLOT(calculate_bmi()));
    connect(ui->spinbox_weight, SIGNAL(valueChanged(int)), this, SLOT(calculate_bmi()));

    // Default settings.
    reset_ui();

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::calculate_bmi() {
    // Get values from the UI.
    int weight = ui->spinbox_weight->value();
    double height = ui->spinbox_height->value();

    // Only calculate bmi if height and weight are nonzero.
    // This avoids division by zero error as well as displaying 0 bmi.
    if (weight > 0 && height > 0) {
        bmi_ = weight / (height/100) / (height/100);
        ui->text_bmi->setText(QString("%1").arg(bmi_)); // Convert BMI to QString and display on screen.
        interpret_bmi();
    }
}

void MainWindow::reset_ui() {
    setFemale();
    ui->spinbox_height->setValue(0); // Also sets slider to 0 through connection made in qt designer
    ui->spinbox_weight->setValue(0); // same as above
    ui->text_bmi->setText("-");
    ui->text_interpretation->setText("-");
    actionSetFemale->setChecked(true); // Select the Female menu item.
}

void MainWindow::setFemale() {
    female_ = true;
    ui->text_gender->setText("Female");
    calculate_bmi();
}

void MainWindow::setMale() {
    female_ = false;
    ui->text_gender->setText("Male");
    calculate_bmi();
}

void MainWindow::interpret_bmi() {
    if (female_) {
        // BMI interpretations for females.
        if (bmi_ <= 19.1) interpretation_ = "underweight";
        else if (bmi_ <= 25.8) interpretation_ = "normal";
        else if (bmi_ <= 27.3) interpretation_ = "slight overweight";
        else if (bmi_ <= 32.2) interpretation_ = "overweight";
        else interpretation_ = "much overweight";
    } else {
        // BMI interpretations for males.
        if (bmi_ <= 20.7) interpretation_ = "underweight";
        else if (bmi_ <= 26.4) interpretation_ = "normal";
        else if (bmi_ <= 27.8) interpretation_ = "slight overweight";
        else if (bmi_ <= 31.1) interpretation_ = "overweight";
        else interpretation_ = "much overweight";
    }
    ui->text_interpretation->setText(interpretation_); // Display on screen.
}

void MainWindow::createActions() {

    // Create menu items.
    actionReset = new QAction("Reset", this);
    actionQuit = new QAction("Quit", this);
    actionSetFemale = new QAction("Female", this);
    actionSetMale = new QAction("Male", this);

    // Connect menu items to slots.
    connect(actionReset, SIGNAL(triggered()), this, SLOT(reset_ui()));
    connect(actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(actionSetFemale, SIGNAL(triggered()), this, SLOT(setFemale()));
    connect(actionSetMale, SIGNAL(triggered()), this, SLOT(setMale()));

    // Make Female and Male selectable.
    actionSetFemale->setCheckable(true);
    actionSetMale->setCheckable(true);

    // Both cannot be selected at the same time.
    gendergroup = new QActionGroup(this);
    gendergroup->addAction(actionSetFemale);
    gendergroup->addAction(actionSetMale);
}

void MainWindow::createMenus() {

    // The Action menu.
    actionMenu = menuBar()->addMenu("Action");
    actionMenu->addAction(actionReset);
    actionMenu->addAction(actionQuit);

    // The Gender menu.
    genderMenu = menuBar()->addMenu("Gender");
    genderMenu->addAction(actionSetFemale);
    genderMenu->addAction(actionSetMale);

}
