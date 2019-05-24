#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QStandardItemModel>

#include "viewer/node.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateTree();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *treeViewModel;

    void populateTree(Node* node, QStandardItem* parent);
};

#endif // MAINWINDOW_HPP
