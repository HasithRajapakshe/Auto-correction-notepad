#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QScrollBar>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionCut_triggered();
    void on_actionCopy_triggered();
    void on_actionPaste_triggered();
    void on_actionNew_2_triggered();
    void on_actionOpen_2_triggered();
    void on_actionSave_2_triggered();
    void on_actionSave_as_2_triggered();
    void on_actionRedo_triggered();
    void on_actionUndo_triggered();
    void on_actionAbout_triggered();


private:
    Ui::MainWindow *ui;
    QTimer *autocorrectTimer;
    QString file_path_;

private slots:
    void autocorrectText();

    void autoCapitalizeAfterFullStop();


private:
    void applyAutocorrection();
};

#endif
