#include "mainwindow.h"

#include <QMenu>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QFontDialog>
#include <QColorDialog>

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
    openAct->setText(tr("&Open"));
    openAct->setToolTip(tr("Open a File"));

    saveAct->setIcon(QIcon(":/Icons/save.png"));
    saveAct->setText(tr("&Save"));
    saveAct->setToolTip(tr("Save Current Text"));

    saveAsAct->setIcon(QIcon(":/Icons/save.png"));
    saveAsAct->setText(tr("S&ave As"));
    saveAsAct->setToolTip(tr("Save Current Text As"));

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
    cutAct->setToolTip(tr("Cut Current Selected Text"));

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

void MainWindow::newFile()
{
    editor->clear();
    currentFile.clear();
    setWindowTitle("My Notepad- New Files");

    editor->document()->setModified(false);
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Open File",
        "",
        "Text Files (*.txt);;All Files (*.*)"
        );

    if(fileName.isEmpty()) return;

    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(
            this,"Error","could nnot open the selected file..");
        return;
    }

    QTextStream in(&file);

    editor->setPlainText(in.readAll());

    file.close();

    currentFile = fileName;
    setWindowTitle("My notepad - " + currentFile);

    editor->document()->setModified(false);
}

void MainWindow::saveFileAs()
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Save File As",
        "",
        "Text Files (*.txt);;All Files (*.*)"
        );

    if(fileName.isEmpty()) return;

    QFile file(fileName);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(
            this,
            "Error",
            "Could not save the file."
            );
        return;
    }

    QTextStream out(&file);
    out << editor->toPlainText();

    file.close();

    currentFile=fileName;
    setWindowTitle("My Notepad - " + currentFile);
    editor->document()->setModified(false);
}

void MainWindow::saveFile()
{
    if (currentFile.isEmpty())
    {
        saveFileAs();
        return;
    }

    QFile file(currentFile);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(
            this,
            "Error",
            "Could not save the file."
            );
        return;
    }

    QTextStream out(&file);
    out << editor->toPlainText();

    file.close();
    editor->document()->setModified(false);
}

void MainWindow::printFile()
{
    QPrinter printer;

    QPrintDialog printDialog(&printer, this);

    if (printDialog.exec() == QDialog::Accepted)
    {
        editor->print(&printer);
    }
}

void MainWindow::chooseFont()
{
    bool ok;

    QFont font = QFontDialog::getFont(
        &ok,
        editor->currentFont(),
        this,
        "Choose Font"
        );

    if (ok)
        editor->setCurrentFont(font);
}

void MainWindow::chooseColor()
{
    QColor color = QColorDialog::getColor(
        editor->textColor(),
        this,
        "Choose Text Color"
        );

    if (color.isValid())
        editor->setTextColor(color);
}

bool MainWindow::maybeSave()
{
    if (!editor->document()->isModified())
        return true;

    QMessageBox::StandardButton result =
        QMessageBox::warning(
            this,
            "Unsaved Changes",
            "The document has unsaved changes.\nDo you want to save them?",
            QMessageBox::Save |
                QMessageBox::Discard |
                QMessageBox::Cancel
            );

    if (result == QMessageBox::Save)
    {
        saveFile();
        return !editor->document()->isModified();
    }

    if (result == QMessageBox::Cancel)
        return false;

    return true;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave())
        event->accept();
    else
        event->ignore();
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


    connect(newAct, &QAction::triggered,
            this, &MainWindow::newFile);

    connect(openAct, &QAction::triggered,
            this, &MainWindow::openFile);

    connect(saveAct, &QAction::triggered,
            this, &MainWindow::saveFile);

    connect(saveAsAct, &QAction::triggered,
            this, &MainWindow::saveFileAs);

    connect(copyAct, &QAction::triggered,
            editor, &QTextEdit::copy);

    connect(cutAct, &QAction::triggered,
            editor, &QTextEdit::cut);

    connect(pasteAct, &QAction::triggered,
            editor, &QTextEdit::paste);

    connect(exitAct, &QAction::triggered,
            this, &QWidget::close);

    connect(exitAct, &QAction::triggered,
            this, &QWidget::close);

    connect(printAct, &QAction::triggered,
            this, &MainWindow::printFile);

    connect(exitAct, &QAction::triggered,
            this, &QWidget::close);
    connect(fontAct, &QAction::triggered,
            this, &MainWindow::chooseFont);

    connect(colorAct, &QAction::triggered,
            this, &MainWindow::chooseColor);
}
