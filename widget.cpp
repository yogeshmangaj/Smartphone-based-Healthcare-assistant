#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{   // Widget constructor
   //Auto-generated code, sets up the UI of the current Widget to the one defined in the "widget.ui" form
    ui->setupUi(this);
    //this->setAttribute(Qt::WA_Maemo5AutoOrientation,true);
    // visit http://doc.qt.nokia.com/qq/qq21-datawidgetmapper.html
    setupDb();
    setupModel();

    ui->listView->setModel(model);
    ui->listView->setModelColumn(1);

    // Set listview to read-only mode
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listView_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listView_4->setEditTriggers(QAbstractItemView::NoEditTriggers);


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
    modelCauses = new QSqlRelationalTableModel(this, db);
    modelCauses->setTable("causes");


    //qDebug() << model->relation(2);


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


void Widget::on_pushButton_8_clicked()
{
    int rsym = ui->listView->currentIndex().row();
    int i=0;
    QStringList strlist=model->record(rsym).value(2).toString().split(",");
    QList<int> integerList;
    QString idlist;
    foreach(QString inttemp,strlist) {
        if(i!=0) idlist.append(" OR ");
    idlist.append("id = ").append(inttemp);
    i++;
    }
    qDebug() << integerList << idlist;

    modelCauses->setFilter(idlist);
    modelCauses->select();
    ui->listView_4->setModel(modelCauses);
    ui->listView_4->setModelColumn(1);
    ui->stackedWidget->setCurrentIndex(4);
    qDebug() << modelCauses->record(0);

}

void Widget::on_pushButton_9_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
}

void Widget::on_pushButton_10_clicked()
{
    int rcause = ui->listView_4->currentIndex().row();
    QString strdesc = modelCauses->record(rcause).value(2).toString();
    ui->textBrowser->setText(strdesc);
    ui->stackedWidget->setCurrentIndex(5);
}

void Widget::on_pushButton_12_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);

}
