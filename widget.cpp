#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{   // Widget constructor
   //Auto-generated code, sets up the UI of the current Widget to the one defined in the "widget.ui" form
    ui->setupUi(this);

    // visit http://doc.qt.nokia.com/qq/qq21-datawidgetmapper.html
    setupDb();
    setupModel();

    ui->listView->setModel(model);
    ui->listView->setModelColumn(1);
//    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

void Widget::setupDb()
{
    db = QSqlDatabase::addDatabase("QSQLITE");


    QDir dir(QApplication::applicationDirPath());
    db.setDatabaseName(dir.filePath("health.db3"));
    if (!db.open())
        qDebug() << db.lastError();
    qDebug() << db.tables();

}
void Widget::setupModel()
{
    model = new QSqlRelationalTableModel(this, db);
    model->setTable("symptoms");
    model->select();
    qDebug() << model->tableName();

}


Widget::~Widget()
{   //Widget destructor
    delete ui;
}


/* Stacked widget indices-
    0- homescreen
    1- symptoms widget
    2- Preventive education
    3- Alternative medecines
*/

void Widget::on_pushButton_clicked()
{   // Symptoms onclick slot
    ui->stackedWidget->setCurrentIndex(1);

}

void Widget::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void Widget::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void Widget::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Widget::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Widget::on_pushButton_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

