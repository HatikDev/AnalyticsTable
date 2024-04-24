#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "classesmodel.h"

#include <memory>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    std::unique_ptr<ClassesModel> m_model;

private slots:
    void on_actionLoad_data_triggered();
};
#endif // MAINWINDOW_H
