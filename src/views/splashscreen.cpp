#include <QFileDialog>
#include <QStringList>

#include <iostream>
#include <system_error>

#include "ui_splashscreen.h"
#include "machzero/views/SplashScreen.h"
#include "machzero/WindowManager.h"
#include "machzero/Utils.h"

SplashScreen::SplashScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SplashScreen)
{
    ui->setupUi(this);
    setAcceptDrops(true);
    QPixmap image("/Users/reverett/MachOViewer/images/logo.png");
    ui->imageLabel->setPixmap(image);
    ui->imageLabel->resize(128, 150);
}

SplashScreen::~SplashScreen()
{
    delete ui;
}
/*void SplashScreen::loadFile(QString file) {
    std::cout << "Opening file: " << file.toStdString() << std::endl;
    llvm::Expected<llvm::object::OwningBinary<llvm::object::Binary>> OBinary = llvm::object::createBinary(file.toStdString());
    if (OBinary) {
        std::pair<std::unique_ptr<llvm::object::Binary>, std::unique_ptr<llvm::WritableMemoryBuffer>> data =
            OBinary->takeBinary();

        // Set the active binary to the one we just opened
        // Release the memory buffer from the smart pointer so it doesn't
        // get deallocated.
        WindowManager::getInstance().showBinaryWindow(data.first.release());
        data.second.release();
    }
    else {
        std::error_code ec = errorToErrorCode(OBinary.takeError());
        Utils::showError("Encountered an error opening file: " + ec.message());
    }
}*/
void SplashScreen::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
}

void SplashScreen::dropEvent(QDropEvent *e)
{
    // make sure only one file is dropped
    if (e->mimeData()->urls().length() > 1) {
        Utils::showError("Tried to load more than one binary");
        return;
    }

    for (const QUrl &url: e->mimeData()->urls()) {
        QString fileName = url.toLocalFile();
        Utils::LoadBinary(fileName);
    }
}

void SplashScreen::on_actionOpen_triggered()
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

