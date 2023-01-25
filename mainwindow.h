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

private Q_SLOTS:
    void startPulseAudio();
    void stopPulseAudio();
    void closeEvent(QCloseEvent*) override;

private:
    Ui::MainWindow *ui;
    QProcess* m_pulseProcessStart;
    QProcess* m_pulseProcessStop;
    QString m_enabledButtonStyle;
    QString m_disabledButtonStyle;

};
#endif // MAINWINDOW_H
