#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QTextEdit>
#include<QString>
#include <QCloseEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

    void SetCentralWidget();

    void SetActions();

    void CreateMenus();

signals:
private:
    void newFile();
    void openFile();
    void saveFile();
    void saveFileAs();
    void printFile();
    void chooseFont();
    void chooseColor();

    QAction *newAct, *openAct, *saveAct, *saveAsAct,
            *printAct, *exitAct,
            *copyAct, *cutAct, *pasteAct,
            *fontAct, *colorAct;

    QTextEdit* editor;

    QString currentFile; //retine ce fisier s-a deschis/salvat

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    bool maybeSave();

};

#endif // MAINWINDOW_H
