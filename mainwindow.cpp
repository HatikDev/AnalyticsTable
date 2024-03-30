#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "classesmodel.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_model = std::make_unique<ClassesModel>();
    m_model->loadEthalonData("C:/Users/Sergey/Documents/cpp/AnalyticsTable/build/Debug/ethalon_data");
    m_model->loadRealData("C:/Users/Sergey/Documents/cpp/AnalyticsTable/build/Debug/real_data");

    ui->mainTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->mainTableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->mainTableView->setModel(m_model.get());
}

MainWindow::~MainWindow()
{
    delete ui;
}
