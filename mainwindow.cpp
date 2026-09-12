#include "mainwindow.h"
#include <QMenu>
#include <QMenuBar>
#include <QVBoxLayout>

void MainWindow::SetCentralWidget()
{
    QWidget* centralWidget = new QWidget;
    setCentralWidget(centralWidget);
    int width = 1000, height = 800;
    resize(width, height);
    setWindowIcon(QIcon(":/Icons/bolt-icon.png"));
    setWindowTitle(tr("My Notepad"));
    QVBoxLayout *vbLay = new QVBoxLayout;
    vbLay->addWidget(editor);
    centralWidget->setLayout(vbLay);
}

void MainWindow::SetActions()
{
    newAct->setIcon(QIcon(":/Icons/new.png"));
    newAct->setText(tr("&New"));
    newAct->setToolTip(tr("Create New File"));

    openAct->setIcon(QIcon(":/Icons/open.png"));
    openAct->setText(tr("&Openw"));
    openAct->setToolTip(tr("Open a File"));

    saveAct->setIcon(QIcon(":/Icons/save.png"));
    saveAct->setText(tr("&Save"));
    saveAct->setToolTip(tr("Save Current Text"));

    saveAsAct->setIcon(QIcon(":/Icons/save.png"));
    saveAsAct->setText(tr("S&ave As"));
    saveAsAct->setToolTip(tr("Save Currnet Text As"));

    printAct->setIcon(QIcon(":/Icons/print.png"));
    printAct->setText(tr("&Print"));
    printAct->setToolTip(tr("Print Current Text"));

    exitAct->setIcon(QIcon(":/Icons/exit.png"));
    exitAct->setText(tr("E&xit"));
    exitAct->setToolTip(tr("Exit Application"));

    copyAct->setIcon(QIcon(":/Icons/copy.png"));
    copyAct->setText(tr("&Copy"));
    copyAct->setToolTip(tr("Copy Saved Text"));

    cutAct->setIcon(QIcon(":/Icons/cut.png"));
    cutAct->setText(tr("C&ut"));
    cutAct->setToolTip(tr("Cut Currnet Selected Text"));

    pasteAct->setIcon(QIcon(":/Icons/paste.png"));
    pasteAct->setText(tr("P&aste"));
    pasteAct->setToolTip(tr("Paste Selected Text"));

    fontAct->setIcon(QIcon(":/Icons/font.png"));
    fontAct->setText(tr("&Font"));
    fontAct->setToolTip(tr("Choose New Font"));

    colorAct->setIcon(QIcon(":/Icons/color.png"));
    colorAct->setText(tr("C&olor"));
    colorAct->setToolTip(tr("Choose New Color"));
}

void MainWindow::CreateMenus()
{
    QMenuBar * menuBar = new QMenuBar;
    QMenu* fileMenu = new QMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);
    menuBar->addMenu(fileMenu);

    QMenu* editMenu = new QMenu(tr("&Edit"));
    editMenu->addAction(copyAct);
    editMenu->addAction(cutAct);
    editMenu->addAction(pasteAct);
    menuBar->addMenu(editMenu);

    QMenu* windowMenu = new QMenu(tr("&Window"));
    windowMenu->addAction(colorAct);
    windowMenu->addAction(fontAct);
    menuBar->addMenu(windowMenu);

    this->setMenuBar(menuBar);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow {parent},
    newAct {new QAction},
    openAct {new QAction},
    saveAct {new QAction},
    saveAsAct {new QAction},
    printAct {new QAction},
    exitAct {new QAction},
    copyAct {new QAction},
    cutAct {new QAction},
    pasteAct {new QAction},
    fontAct {new QAction},
    colorAct {new QAction},
    editor {new QTextEdit}
{
    SetCentralWidget();
    SetActions();
    CreateMenus();
}
