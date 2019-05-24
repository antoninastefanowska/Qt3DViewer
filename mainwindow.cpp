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

void MainWindow::updateTree()
{
    treeViewModel = new QStandardItemModel(ui->objectTreeView);
    treeViewModel->setColumnCount(1);
    treeViewModel->setHorizontalHeaderLabels({"Obiekty"});

    Scene* scene = ui->myGLWidget->getScene();

    QStandardItem *itemScene = new QStandardItem;
    itemScene->setText(QString(scene->getName().c_str()));

    populateTree(scene, itemScene);

    treeViewModel->setItem(0, 0, itemScene);
    ui->objectTreeView->setModel(treeViewModel);
    ui->objectTreeView->expandAll();
}

void MainWindow::populateTree(Node* node, QStandardItem* parent)
{
    int i = 0;
    for (Node* child : node->getChildren())
    {
        QStandardItem *item = new QStandardItem;
        item->setText(QString(child->getName().c_str()));
        parent->setChild(i, 0, item);
        i++;
        populateTree(child, item);
    }
}
