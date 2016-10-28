#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QtGui>
#include <QtCore>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_treeView_doubleClicked(const QModelIndex &index);
    void traverse(QString path, int &broj_direktorijuma, int &broj_fajlova);
    void from_database_textEdit();

    void on_pushButton_7_clicked();

private:
    Ui::MainWindow *ui;
    QFileSystemModel * filesistem;
};

#endif // MAINWINDOW_H
