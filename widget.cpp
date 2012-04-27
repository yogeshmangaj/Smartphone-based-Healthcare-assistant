#include "widget.h"
#include "ui_widget.h"
#include <QStringListModel>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{   // Widget constructor
    ui->setupUi(this); //Auto-generated code, sets up the UI of the current Widget to the one defined in the "widget.ui" form
    QStringListModel* symptoms = new QStringListModel(); //Model for string list
/* Sample data for demonstration- to be replaced with SQL models */
    QStringList list;
    list << "Abdominal pain" << "Arm numbness (paresthesias)" << "Back pain" << "Bloody nose (Epistaxis)" << "Diarrhea" << "Difficulty breathing" << "Dysuria (Painful urination)" << "Elevated blood calcium" << "Facial pain" << "Fatigue" << "Fever and headache" << "Fever and rash" << "Foot cut (laceration)" << "Hair loss (Baldness)" << "Heart murmur (Abnormal heart sound)" << "Hematuria (Bloody urine)" << "Insomnia (Trouble sleeping)" << "Loss of consciousness (Passing out)";
    symptoms->setStringList(list);
    ui->listView->setModel(symptoms);
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
