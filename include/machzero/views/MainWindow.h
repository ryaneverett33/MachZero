#pragma once

#include <QMainWindow>
#include <QItemSelection>
#include <QStandardItemModel>
#include <QCloseEvent>

#include "machzero/models/MachObjectModel.h"

// LLVM includes
#include "llvm/Object/Binary.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setActiveBinary(std::unique_ptr<llvm::object::Binary>& binary, 
                         std::unique_ptr<llvm::WritableMemoryBuffer>& memoryBuffer);

private slots:
    void on_actionOpen_triggered();
    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;
    MachObjectModel* model;
    void on_machObjectsView_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void closeEvent (QCloseEvent *event) override;
};