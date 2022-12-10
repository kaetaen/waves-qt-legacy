#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QCloseEvent>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->geometry().width(),this->geometry().height());
    this->setWindowTitle("Waves");
    // Verifica se o pulse audio está instalado
    if(!QFile::exists("/usr/bin/pactl")) {
        QMessageBox::information(this, "Warning", "Pulse-audio is not installed");
    }
    connect(ui->activateBtn, SIGNAL(clicked()), SLOT(activateBtnClicked()));
    connect(ui->deactivateBtn, SIGNAL(clicked()), SLOT(deactivateBtnClicked()));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::activateBtnClicked()
{
    ui->soundIndicator->setText("ENABLED");
    ui->soundIndicator->setStyleSheet("border-radius: 120;margin: 20px;background-color:green ;color: rgb(255, 255, 255);text-align:center;font-weight: bold;");

    QObject *parent = nullptr;

    QString program = "/usr/bin/pactl";
    QStringList arguments;
    arguments << "load-module" << "module-loopback" << "latency_msec=1";

    QProcess *myProcess = new QProcess(parent);
    myProcess->start(program, arguments);
}


void MainWindow::deactivateBtnClicked()
{
    ui->soundIndicator->setText("DISABLED");
    ui->soundIndicator->setStyleSheet("border-radius: 120;margin: 20px;background-color:rgb(170, 0, 0) ;color: rgb(255, 255, 255);text-align:center;font-weight: bold;");

    QObject *parent = nullptr;

    QString program = "/usr/bin/pactl";
    QStringList arguments;
    arguments << "unload-module" << "module-loopback";

    QProcess *myProcess = new QProcess(parent);
    myProcess->start(program, arguments);
}

