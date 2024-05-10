#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "classesmodel.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_model = std::make_unique<ClassesModel>();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionLoad_data_triggered()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
        ".",
        QFileDialog::ShowDirsOnly
        | QFileDialog::DontResolveSymlinks);

    if (dir.isEmpty())
        return;

    m_model->loadEthalonData((dir + "/ethalon_data/").toStdString());
    m_model->loadRealData((dir + "/real_data/").toStdString());

    ui->mainTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->mainTableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->mainTableView->setModel(m_model.get());
}
