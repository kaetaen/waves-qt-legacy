#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void closeEvent(QCloseEvent *event)
    {
        QObject *parent;

        QString program = "/usr/bin/pactl";
        QStringList arguments;
        arguments << "unload-module" << "module-loopback";

        QProcess *myProcess = new QProcess(parent);
        myProcess->start(program, arguments);
        event->accept();
    }

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
