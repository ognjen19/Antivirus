#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <string>

#include <QMainWindow>
#include <QFileSystemModel>
#include <QtGui>
#include <QtCore>
#include <QDir>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);


    this->setFixedSize(802, 542);

    QString Qpath = "";
    filesistem = new QFileSystemModel(this);
    filesistem->setRootPath(Qpath);
    filesistem->setFilter(QDir::Drives);
    ui->treeView->setModel(filesistem);

    ui->label_number_dir->setStyleSheet("QLabel {color : green; }");
    ui->label_number_file->setStyleSheet("QLabel {color : green; }");
    ui->label_number_viruse->setStyleSheet("QLabel {color : red; }");

    ui->textEdit->setReadOnly(true);

    from_database_textEdit();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    QString path = filesistem->fileInfo(index).absoluteFilePath();/*.toStdString();*/
    if(path.contains("/")){
            path.replace("/", "\\");
    }
    ui->label_selected_drive->setText(path);

    int broj_direktorijuma = 0;
    int broj_fajlova = 0;

    traverse(path, broj_direktorijuma, broj_fajlova);


}


void MainWindow::traverse(QString path, int &broj_direktorijuma, int &broj_fajlova){
    QDir dir(path); //"Name"


    if (dir.exists())
    {
        foreach (QString file, dir.entryList(QDir::Files | QDir::Hidden)){
            broj_fajlova++;
            ui->progressBar->setValue(broj_fajlova);
            ui->label_number_file->setText(QString::number(broj_fajlova));

        }

        foreach (QString subDir, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)){
            //qDebug() << "DIR: " + QFileInfo(dir, subDir).absoluteFilePath() + "\n";
            broj_direktorijuma = broj_direktorijuma + 1;
            ui->label_number_dir->setText(QString::number(broj_direktorijuma));
            traverse(path + QDir::separator() + subDir, broj_direktorijuma, broj_fajlova);
        }
    }
}


/*insert hash viruses in list view*/

void MainWindow::from_database_textEdit(){

    QFile myFile("C://Users//MARKO//Desktop//3.godinaII//Razvoj_Softvera//VezbanjeKoll//av//virus_db_and_updater//viruslist.txt");
    myFile.open(QIODevice::ReadOnly);
    QTextStream textStream(&myFile);
    QString line = textStream.readAll();
    myFile.close();
    ui->textEdit->setPlainText(line);
}

/*end insert hash viruses in list view*/

void MainWindow::on_pushButton_7_clicked()
{
    QProcess::execute("C://Users//MARKO//Desktop//3.godinaII//Razvoj_Softvera//VezbanjeKoll//av//virus_db_and_updater//updater.exe");
    from_database_textEdit();
}
