#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QTextEdit>
#include <QTextCursor>
#include <QRegExp>
#include <QDebug>
#include <QTimer>
#include <QRegularExpression>
#include <QTextCharFormat>
#include <QStandardPaths>
#include <QStringList>
#include <QSet>
#include <QMouseEvent>
#include <QAction>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);

    autocorrectTimer = new QTimer(this);
    autocorrectTimer->setInterval(200);


    connect(ui->actionCut, &QAction::triggered, this, &MainWindow::on_actionCut_triggered);
    connect(ui->actionCopy, &QAction::triggered, this, &MainWindow::on_actionCopy_triggered);
    connect(ui->actionPaste, &QAction::triggered, this, &MainWindow::on_actionPaste_triggered);
    connect(ui->actionUndo, &QAction::triggered, this, &MainWindow::on_actionUndo_triggered);
    connect(ui->actionRedo, &QAction::triggered, this, &MainWindow::on_actionRedo_triggered);
    connect(ui->actionNew_2, &QAction::triggered, this, &MainWindow::on_actionNew_2_triggered);
    connect(ui->actionOpen_2, &QAction::triggered, this, &MainWindow::on_actionOpen_2_triggered);
    connect(ui->actionSave_2, &QAction::triggered, this, &MainWindow::on_actionSave_2_triggered);
    connect(ui->actionSave_as_2, &QAction::triggered, this, &MainWindow::on_actionSave_as_2_triggered);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::on_actionAbout_triggered);
    connect(autocorrectTimer, &QTimer::timeout, this, &MainWindow::autocorrectText);
    connect(ui->textEdit, &QTextEdit::textChanged, autocorrectTimer, static_cast<void (QTimer::*)()>(&QTimer::start));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::autocorrectText() {
    qDebug() << "autocorrectText called";


    QTextCursor savedCursor = ui->textEdit->textCursor();

    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.beginEditBlock();


    QString text = ui->textEdit->toPlainText();


    QString correctedText;
    bool capitalizeNext = true;

    for (int i = 0; i < text.length(); ++i) {
        QChar currentChar = text.at(i);


        if (capitalizeNext && currentChar.isLetter()) {
            correctedText += currentChar.toUpper();
            capitalizeNext = false;
        } else {
            correctedText += currentChar;

            if (currentChar == '.' || currentChar == '!' || currentChar == '?') {
                capitalizeNext = true;

                if (i + 1 < text.length() && !text.at(i + 1).isSpace()) {

                    correctedText += "<span style='text-decoration: underline; color: red;'>";



                    while (i + 1 < text.length() && !text.at(i + 1).isSpace()) {
                        correctedText += text.at(++i);
                    }
                    correctedText += "</span>";

                }
            }
        }
    }


    ui->textEdit->setHtml(correctedText);


    ui->textEdit->setTextCursor(savedCursor);

    cursor.endEditBlock();
}

void MainWindow::autoCapitalizeAfterFullStop() {

    QTextCursor savedCursor = ui->textEdit->textCursor();

    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.beginEditBlock();


    QString text = ui->textEdit->toPlainText();

    QString correctedText;
    bool capitalizeNext = true;

    for (int i = 0; i < text.length(); ++i) {
        QChar currentChar = text.at(i);


        if (capitalizeNext && currentChar.isLetter()) {
            correctedText += currentChar.toUpper();
            capitalizeNext = false;
        } else {
            correctedText += currentChar;

            if (currentChar == '.' || currentChar == '!' || currentChar == '?') {
                capitalizeNext = true;
            }
        }
    }


    ui->textEdit->setPlainText(correctedText);


    ui->textEdit->setTextCursor(savedCursor);

    cursor.endEditBlock();


}
void MainWindow::on_actionCut_triggered()
{
    qDebug() << "Cut action triggered";
    ui->textEdit->cut();
}


void MainWindow::on_actionCopy_triggered()
{
    qDebug() << "Copy action triggered";
    ui->textEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    qDebug() << "Paste action triggered";
    ui->textEdit->paste();
}


void MainWindow::on_actionNew_2_triggered()
{
    file_path_="";
    ui->textEdit->setText("");
}


void MainWindow::on_actionOpen_2_triggered()
{
    QString file_name= QFileDialog::getOpenFileName(this,"open the file");
    QFile file (file_name);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"..","file not open");
        return;
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}




void MainWindow::on_actionSave_2_triggered()
{

    QFile file (file_path_);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"..","file not open");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out<< text;
    file.flush();
    file.close();


}


void MainWindow::on_actionSave_as_2_triggered()
{
    QString file_name=QFileDialog::getSaveFileName(this,"open the file");
    QFile file (file_name);
    file_path_ =file_name;

    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"..","file not open");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out<< text;
    file.flush();
    file.close();

}


void MainWindow::on_actionUndo_triggered()
{
    qDebug() << "Undo action triggered";
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    qDebug() << "Redo action triggered";
    ui->textEdit->redo();
}



void MainWindow::on_actionAbout_triggered()
{


    QString about_text;
    about_text = "Auther :Hasith H Rajapakshe"
                 "Reg_NO:ICT/2021/094"
                 "Faculty Of Applied Sciences"
                 "Rajarata University Of Sri Lanka";
    about_text +="Date   : 26/01/2024";
    about_text +="(c++) Notepad (R)";

    QMessageBox::about(this,"About Notepad",about_text);

}







