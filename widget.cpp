#include "widget.h"
#include "ui_widget.h"
#include <QStringListModel>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QStringListModel* symptoms = new QStringListModel();
    QStringList list;
    list << "Abdominal pain" << "Arm numbness (paresthesias)" << "Back pain" << "Bloody nose (Epistaxis)" << "Diarrhea" << "Difficulty breathing" << "Dysuria (Painful urination)" << "Elevated blood calcium" << "Facial pain" << "Fatigue" << "Fever and headache" << "Fever and rash" << "Foot cut (laceration)" << "Hair loss (Baldness)" << "Heart murmur (Abnormal heart sound)" << "Hematuria (Bloody urine)" << "Insomnia (Trouble sleeping)" << "Loss of consciousness (Passing out)";
    symptoms->setStringList(list);
    ui->listView->setModel(symptoms);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
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
