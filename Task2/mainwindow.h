#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QStack>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QLabel>
#include <QtXml>
#include <QXmlStreamReader>
#include "codeeditor.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void validationOfXMLTree(QXmlStreamReader* xmlReader);

private slots:
    void on_actionCreate_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_as_triggered();

    void on_actionExit_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionCut_triggered();

    void on_actionUnDo_triggered();

    void on_actionReDo_triggered();

    void on_actionSave_triggered();

    void on_actionShow_hide_lines_triggered();

    void showStatistics(CodeEditor *);

    void callerShowStatistic();

    void on_findNextBut_clicked();

    void on_cancelBut_clicked();

    void on_actionFind_triggered();

    void on_findPrevious_clicked();

private:
    Ui::MainWindow *ui;
    QString currentFile = "";
    CodeEditor* editor = new CodeEditor();
};

#endif // MAINWINDOW_H
