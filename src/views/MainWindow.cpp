#include <QFileDialog>
#include <QPixmap>
#include <QLabel>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QModelIndex>
#include <QFileDialog>
#include <QStringList>

#include <string>
#include <iostream>

#include "machzero/views/MainWindow.h"
#include "./ui_mainwindow.h"
#include "machzero/models/ContentsModel.h"
#include "machzero/WindowManager.h"
#include "machzero/Utils.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setActiveBinary(std::unique_ptr<llvm::object::Binary>& binary, 
                                 std::unique_ptr<llvm::WritableMemoryBuffer>& memoryBuffer)
{
    model = MachObjectModel::FromBinary(binary, memoryBuffer);

    ui->machObjectsView->setModel(model);
    ui->machObjectsView->expand(model->index(0, 0));
    ui->machObjectsView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->machObjectsView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QObject::connect(ui->machObjectsView->selectionModel(), &QItemSelectionModel::selectionChanged,
                     this, &MainWindow::on_machObjectsView_selectionChanged);
}

void MainWindow::on_actionOpen_triggered()
{
    // TODO, don't duplicate this
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::FileMode::ExistingFile);
    dialog.setAcceptDrops(true);
    dialog.setNameFilter(tr("Binaries (*)"));
    if (dialog.exec()) {
        QStringList files = dialog.selectedFiles();
        Utils::LoadBinary(files[0]);
    }
}
void MainWindow::on_actionSave_triggered() {
    std::cout << "Clicked Save!\n";
    QUrl saveDestinationUrl = QFileDialog::getSaveFileUrl(this);
    if (!saveDestinationUrl.isEmpty()) {
        QString saveDestination = saveDestinationUrl.toLocalFile();
        Utils::SaveBinary(saveDestination, model->getMemory());
    }
}

void MainWindow::on_machObjectsView_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) {
    if (selected.indexes().empty()) {
        ui->valueView->setModel(nullptr);
        return;
    }
    QModelIndex idx = selected.indexes()[0];
    ContentsModel* contentsModel = dynamic_cast<ContentsModel*>(model);
    QAbstractItemModel* selectedModel = contentsModel->GetModelAtIndex(idx);
    ui->valueView->setModel(selectedModel);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    WindowManager::getInstance().windowDied(this);
    event->accept();
}