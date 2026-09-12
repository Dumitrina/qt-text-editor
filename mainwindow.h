#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QTextEdit>

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
    QAction *newAct, *openAct, *saveAct, *saveAsAct,
            *printAct, *exitAct,
            *copyAct, *cutAct, *pasteAct,
            *fontAct, *colorAct;
    QTextEdit* editor;
};

#endif // MAINWINDOW_H
