#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setGLWidget(MyGLWidget* glWidget) {
    this->glWidget = glWidget;
}

void MainWindow::generateObjectTree()
{
    treeViewModel = new QStandardItemModel(ui->objectTreeView);
    treeViewModel->setColumnCount(1);
    treeViewModel->setHorizontalHeaderLabels({"Obiekty"});

    Scene* scene = ui->myGLWidget->getScene();

    QStandardItem *itemScene = new QStandardItem;
    itemScene->setText(QString(scene->getName().c_str()));

    glWidget->setTreeControl(itemScene);
    glWidget->populateObjectTree(scene, itemScene);

    treeViewModel->setItem(0, 0, itemScene);
    ui->objectTreeView->setModel(treeViewModel);
    ui->objectTreeView->expandAll();
}

void MainWindow::setTimer()
{
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(frame()));
    timer->start(10);
}

void MainWindow::frame()
{
    ui->myGLWidget->update();
}
