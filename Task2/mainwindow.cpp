#include "mainwindow.h"
#include "ui_mainwindow.h"

static QColor colours[7] = {QColor(255,0,0), QColor(255,130,0), QColor(255,255,0),
                  QColor(0,255,0), QColor(0,255,255),
                  QColor(0,0,255), QColor(255,0,255)};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->horizontalLayout_3->addWidget(editor);
    editor->show();
    ui->treeWidget->hide();
    ui->label_5->hide();
    ui->lineEdit->hide();
    ui->findNextBut->hide();
    ui->cancelBut->hide();
    ui->findPrevious->hide();

    connect(editor, SIGNAL(textChanged()), this, SLOT(callerShowStatistic()));

    showStatistics(editor);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::validationOfXMLTree(QXmlStreamReader* xmlReader)
{
    if(xmlReader->hasError()){
        QMessageBox::warning(this,"Warning","Error in parsing XML file"+xmlReader->errorString());
        ui->treeWidget->clear();
    }
}

void MainWindow::on_actionCreate_triggered()
{
    currentFile="";
    editor->show();
    editor->setEnabled(1);
    ui->treeWidget->hide();
    ui->label->show();
    ui->label_2->show();
    ui->label_3->show();
    ui->label_4->show();
    //clear qplaintextedit
    editor->setPlainText(QString(""));
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open");
    QFile file(filename);
    currentFile = filename;
    if(!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,"Warning","Cannot open file:"+file.errorString());
        return;
    }
    setWindowTitle(filename);
    QTextStream in(&file);
    QString text = in.readAll();
    if(filename.endsWith(".xml",Qt::CaseSensitive))  //if xml file type need open qtreeview
    {
        ui->treeWidget->show();
        editor->setEnabled(0);
        editor->hide();
        ui->label->hide();
        ui->label_2->hide();
        ui->label_3->hide();
        ui->label_4->hide();
        ui->treeWidget->clear();
        QStack<QTreeWidgetItem*> widgetStack;
        int i=0;
        QXmlStreamReader xmlReader;
        xmlReader.addData(text);
        while(!xmlReader.atEnd()){
            if(xmlReader.isStartElement()){
                QStringList sl;
                sl << xmlReader.name().toString();
                QTreeWidgetItem *item = new QTreeWidgetItem(sl);
                i>6?i=0:i;                                      //background color
                item->setBackgroundColor(0, colours[i++]);
                if(widgetStack.count() == 0)
                ui->treeWidget->addTopLevelItem(item);
                else{
                   widgetStack.top()->addChild(item);
                }
                widgetStack.push(item);

                }
            if(xmlReader.isEndElement()){
                widgetStack.pop();
            }
            xmlReader.readNext();
        }
        validationOfXMLTree(&xmlReader);
    }

    else                            //else qplaintexteditor
    {
        editor->setEnabled(1);
        ui->label->show();
        ui->label_2->show();
        ui->label_3->show();
        ui->label_4->show();
        ui->treeWidget->hide();
        editor->show();
        editor->setPlainText(text);
    }
    file.close();
}

void MainWindow::on_actionSave_as_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this,"Save as");
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this,"Warning","Cannot save file:"+file.errorString());
        return;
    }
    currentFile = filename;
    setWindowTitle(filename);
    QTextStream out(&file);
    QString text = editor->toPlainText();
    out<<text;
    file.close();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionCopy_triggered()
{
    editor->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    editor->paste();
}

void MainWindow::on_actionCut_triggered()
{
    editor->cut();
}

void MainWindow::on_actionUnDo_triggered()
{
    editor->undo();
}

void MainWindow::on_actionReDo_triggered()
{
    editor->redo();
}

void MainWindow::on_actionSave_triggered()
{
    QFile file(currentFile);
    if(!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        this->on_actionSave_as_triggered();
    }
    QTextStream out(&currentFile);
    out<<editor->toPlainText();

    file.flush();
    file.close();
}

void MainWindow::on_actionShow_hide_lines_triggered()
{
    if(editor->getLineFlag())
        editor->hideLineNumber();
    else editor->showLineNumber();
}

void MainWindow::showStatistics(CodeEditor *p)
{
    ui->label_2->setNum(static_cast<int>(p->getWordNumber()));
    ui->label_4->setNum(static_cast<int>(p->getCharNumber()));
}

void MainWindow::callerShowStatistic()
{
    showStatistics(editor);             //addition slot to access lineEdit
}


void MainWindow::on_findNextBut_clicked()
{
    editor->find(ui->lineEdit->text());
}

void MainWindow::on_cancelBut_clicked()
{
    ui->label_5->hide();
    ui->lineEdit->hide();
    ui->findNextBut->hide();
    ui->cancelBut->hide();
    ui->findPrevious->hide();
    ui->lineEdit->setEnabled(0);
}

void MainWindow::on_actionFind_triggered()
{

    if(editor->isEnabled()){
        ui->label_5->show();
        ui->lineEdit->show();
        ui->findNextBut->show();
        ui->cancelBut->show();
        ui->findPrevious->show();
        ui->lineEdit->setEnabled(1);
    }
    else{
        QMessageBox::warning(this,"Warning","Can't find text in XML files.");
    }
}

void MainWindow::on_findPrevious_clicked()
{
        editor->find(ui->lineEdit->text(),QTextDocument::FindBackward);
}
