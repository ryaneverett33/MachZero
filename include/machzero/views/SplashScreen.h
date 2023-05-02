#pragma once

#include <QMainWindow>
#include <QDropEvent>
#include <QMimeData>

QT_BEGIN_NAMESPACE
namespace Ui { class SplashScreen; }
QT_END_NAMESPACE

class SplashScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit SplashScreen(QWidget *parent = nullptr);
    ~SplashScreen();

    // Drag & Drop overrides
    void dragEnterEvent(QDragEnterEvent *e) override;
    void dropEvent(QDropEvent* e) override;

private slots:
    void on_actionOpen_triggered();

private:
    Ui::SplashScreen *ui;
};
