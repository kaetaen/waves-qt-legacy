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

    connect(ui->startBtn, &QPushButton::clicked, this, &MainWindow::startPulseAudio);
    connect(ui->stopBtn, &QPushButton::clicked, this, &MainWindow::stopPulseAudio);

    // Verifica se o pulse audio está instalado
    if(!QFile::exists("/usr/bin/pactl")) {
        QMessageBox errorMessage;
        errorMessage.setIcon(QMessageBox::Critical);
        errorMessage.setText("Could not find PulseAudioCTL");
        errorMessage.setWindowTitle("Error");
        errorMessage.exec();
        close();
    }

    //For better stylization, consider using QML instead.
    m_enabledButtonStyle = "border-radius: 120;"
                           "margin: 20px;"
                           "background-color:green;"
                           "color: rgb(255, 255, 255);"
                           "text-align:center;"
                           "font-weight: bold;";

    m_disabledButtonStyle = "border-radius: 120;"
                           "margin: 20px;"
                           "background-color:green;"
                           "color: rgb(255, 255, 255);"
                           "text-align:center;"
                           "font-weight: bold;";
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::startPulseAudio()
{
    ui->statusIconLabel->setText(tr("Enabled"));
    ui->statusIconLabel->setStyleSheet(m_enabledButtonStyle);

    //consider using the pulseaudio libraries instead
    QString program = "/usr/bin/pactl";
    QStringList arguments;
    arguments << "load-module" << "module-loopback" << "latency_msec=1";

    if(!m_pulseProcessStart) {
        m_pulseProcessStart = new QProcess(this);
    }
    m_pulseProcessStart->start(program, arguments);
    ui->stopBtn->setEnabled(true);
    ui->startBtn->setEnabled(false);
}


void MainWindow::stopPulseAudio()
{
    ui->statusIconLabel->setText(tr("Disabled"));
    ui->statusIconLabel->setStyleSheet(m_disabledButtonStyle);
    m_pulseProcessStart->deleteLater();

    QString program = "/usr/bin/pactl";
    QStringList arguments;
    arguments << "unload-module" << "module-loopback";

    if(!m_pulseProcessStop){
        m_pulseProcessStop = new QProcess(this);
    }
    m_pulseProcessStop->start(program, arguments);
    ui->startBtn->setEnabled(true);
    ui->stopBtn->setEnabled(false);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
//    QString program = "/usr/bin/pactl";
//    QStringList arguments;
//    arguments << "unload-module" << "module-loopback";

    stopPulseAudio();

    event->accept();
}
