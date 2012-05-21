#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{   // Widget constructor
   //Auto-generated code, sets up the UI of the current Widget to the one defined in the "widget.ui" form
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    //Screen orientation
//    this->setAttribute(Qt::WA_Maemo5AutoOrientation,true);
    this->setWindowTitle("Health Assistant");
    setupDb();
    setupModel();
    //Set model of listview to "model" (symptoms view)
    ui->listView->setModel(model);
    ui->listView->setModelColumn(1);
    ui->listView_2->setModel(modelPrev);
    ui->listView_2->setModelColumn(1);
    ui->listView_3->setModel(modelAlt);
    ui->listView_3->setModelColumn(1);
    // Set listview to read-only mode
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listView_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listView_4->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

void Widget::setupDb()
{
    // Declare and import the SqLite Database- health.db3
    db = QSqlDatabase::addDatabase("QSQLITE");
    QDir dir(QApplication::applicationDirPath());
    db.setDatabaseName(dir.filePath("health.db3"));
    // Debug stuff
    if (!db.open())
        qDebug() << db.lastError();


}
void Widget::setupModel()
{
    //Setup models
    model = new QSqlRelationalTableModel(this, db);
    model->setTable("symptoms");
    modelCauses = new QSqlRelationalTableModel(this, db);
    modelCauses->setTable("causes");
    model->select();

    modelPrev = new QSqlRelationalTableModel(this, db);
    modelPrev->setTable("preventive");
    modelPrev->select();

    modelPrevItems = new QSqlRelationalTableModel(this, db);
    modelPrevItems->setTable("previtems");
    modelAlt = new QSqlRelationalTableModel(this, db);
    modelAlt->setTable("alternative");
    modelAlt->select();
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
  this->setWindowTitle("Symptoms");

}

void Widget::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    this->setWindowTitle("Preventive education");
}

void Widget::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    this->setWindowTitle("Alternative Medecines");
}

void Widget::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    this->setWindowTitle("Health Assistant");
}

void Widget::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    this->setWindowTitle("Health Assistant");
}

void Widget::on_pushButton_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    this->setWindowTitle("Health Assistant");
}


void Widget::on_pushButton_8_clicked()
{   //On "GO" button press in Symptoms window
    // Get the index of currently highlighted row in the listview
    int rsym = ui->listView->currentIndex().row();
    int i=0;
    // Convert CSV to String List
//    ui->label_5->setText(model->record(rsym).value(1).toString().append(" Causes"));
    this->setWindowTitle(model->record(rsym).value(1).toString().append(" Causes"));
//    QList<int>
//    QStringList strlist=model->record(rsym).value(2).toString().split(",");
    QStringList strlist=model->record(rsym).value(2).toString().split("-");
    QString idlist; //Where-clause used in filter for modelCauses

    /*
    foreach(QString inttemp,strlist) {
        if(i!=0) idlist.append(" OR "); //Do not insert "OR" before first element
        idlist.append("id = ").append(inttemp);
        i++;
    }
    */
    int k=strlist[0].toInt();
    int j=strlist[1].toInt();
    qDebug() << k << j;
    for(i=k;i<=j;i++)
    {
        if(i!=k) idlist.append(" OR "); //Do not insert "OR" before first element
        idlist.append("id = ").append(QString::number(i));
//        i++;
//        qDebug() << i;
    }

//    qDebug() << idlist;

    //Set modelCauses model to listView_4
    modelCauses->setFilter(idlist);
    modelCauses->select();
    ui->listView_4->setModel(modelCauses);
    ui->listView_4->setModelColumn(1);
    ui->stackedWidget->setCurrentIndex(4);


}

void Widget::on_pushButton_9_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
     this->setWindowTitle(model->record(ui->listView->currentIndex().row()).value(1).toString().append(" Causes"));
}

void Widget::on_pushButton_10_clicked()
{   //"Go" button pressed in Causes window
    //Get index of highlighted cause
    int rcause = ui->listView_4->currentIndex().row();
    //Convert to Qstring the value for display
//    ui->label_6->setText(modelCauses->record(rcause).value(1).toString());
    this->setWindowTitle(modelCauses->record(rcause).value(1).toString());
    QString strdesc = modelCauses->record(rcause).value(2).toString();
    ui->textBrowser->setText(strdesc);
    ui->stackedWidget->setCurrentIndex(5);
}

void Widget::on_pushButton_12_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    this->setWindowTitle(modelCauses->record(ui->listView_4->currentIndex().row()).value(1).toString());


}

void Widget::on_pushButton_13_clicked()
{
//    ui->label_7->setText("Share by SMS");
    this->setWindowTitle("Share by SMS");
    ui->pushButton_15_sendsms->setText("Send SMS");
    ui->label_9->setVisible(0);
    ui->lineEdit_3->setVisible(0);
    ui->stackedWidget->setCurrentIndex(7);
    m_service = new QMessageService(this);
    message.setType(QMessage::Sms);
    message.setTo(QMessageAddress(QMessageAddress::Phone, ui->lineEdit_2->text()));
    ui->plainTextEdit->setPlainText(ui->textBrowser->toPlainText().append("\n-Source: Health Assistant App"));
    message.setBody(ui->plainTextEdit->toPlainText());
}



void Widget::on_pushButton_15_sendsms_clicked()
{
    if (m_service->send(message)) {
        QMessageBox::information(this, tr("Message sent"),
                                 "The message was sent successfully.");
    } else {
        QMessageBox::information(this, tr("Message was not sent"),
                                 "The message was not sent.");
    }
}

void Widget::on_pushButton_14_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void Widget::on_pushButton_11_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void Widget::on_pushButton_15_clicked()
{
    ui->label_9->setVisible(1);
    ui->lineEdit_3->setVisible(1);
    ui->label_7->setText("Share by E-Mail");
    ui->pushButton_15_sendsms->setText("Send Mail");
    ui->stackedWidget->setCurrentIndex(7);
    m_service = new QMessageService(this);
    message.setType(QMessage::Email);
    message.setTo(QMessageAddress(QMessageAddress::Email, ui->lineEdit_2->text()));
    message.setSubject(QString("Information on ").append(modelCauses->record(ui->listView_4->currentIndex().row()).value(1).toString()).append(" -generated by Health Assistant"));
    ui->plainTextEdit->setPlainText(ui->textBrowser->toPlainText());
    message.setBody(ui->plainTextEdit->toPlainText());
}

void Widget::on_pushButton_16_clicked()
{
     ui->stackedWidget->setCurrentIndex(5);
     this->setWindowTitle(modelCauses->record(ui->listView_4->currentIndex().row()).value(1).toString());

}

void Widget::on_pushButton_18_clicked()
{
    //Preventive widget Go button onclick
    int rprv = ui->listView_2->currentIndex().row();
    int i=0;
    // Convert CSV to String List
//    ui->label_5->setText(model->record(rsym).value(1).toString().append(" Causes"));
    this->setWindowTitle(modelPrev->record(rprv).value(1).toString());
    QStringList strlist=modelPrev->record(rprv).value(2).toString().split("-");
    QString idlist; //Where-clause used in filter for modelCauses
  /*  foreach(QString inttemp,strlist) {
        if(i!=0) idlist.append(" OR "); //Do not insert "OR" before first element
        idlist.append("id = ").append(inttemp);
        i++;
    }
    */

    int k=strlist[0].toInt();
    int j=strlist[1].toInt();
    qDebug() << k << j;
    for(i=k;i<=j;i++)
    {
        if(i!=k) idlist.append(" OR "); //Do not insert "OR" before first element
        idlist.append("id = ").append(QString::number(i));
//        i++;
//        qDebug() << i;
    }

    //Set modelCauses model to listView_4
    modelPrevItems->setFilter(idlist);
    modelPrevItems->select();
    ui->listView_5->setModel(modelPrevItems);
    ui->listView_5->setModelColumn(1);
    ui->stackedWidget->setCurrentIndex(8);

}

void Widget::on_pushButton_19_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void Widget::on_pushButton_20_clicked()
{
    int rprev = ui->listView_5->currentIndex().row();
    //Convert to Qstring the value for display
//    ui->label_6->setText(modelCauses->record(rcause).value(1).toString());
    this->setWindowTitle(modelPrevItems->record(rprev).value(1).toString());
    QString strdesc = modelPrevItems->record(rprev).value(2).toString();
    ui->textBrowser_2->setText(strdesc);
    ui->stackedWidget->setCurrentIndex(9);
}

void Widget::on_pushButton_21_clicked()
{
      ui->stackedWidget->setCurrentIndex(8);
}

void Widget::on_pushButton_17_clicked()
{
    ralt = ui->listView_3->currentIndex().row();
    //Convert to Qstring the value for display
//    ui->label_6->setText(modelCauses->record(rcause).value(1).toString());
    updateAltDesc();
    ui->stackedWidget->setCurrentIndex(10);

}

void Widget::updateAltDesc()
{
    this->setWindowTitle(modelAlt->record(ralt).value(1).toString());
    QString strdesc = modelAlt->record(ralt).value(2).toString();
    ui->textBrowser_3->setText(strdesc);
    if(ralt==0)
        ui->pushButton_23->setEnabled(0);
    else if(ralt==modelAlt->rowCount()-1)
        ui->pushButton_24->setEnabled(0);
    else {
        ui->pushButton_23->setEnabled(1);
        ui->pushButton_24->setEnabled(1);
    }
}

void Widget::on_pushButton_23_clicked()
{
    if(ralt!=0)
        ralt--;
    updateAltDesc();
}

void Widget::on_pushButton_22_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void Widget::on_pushButton_24_clicked()
{
    if(ralt!=modelAlt->rowCount()-1)
        ralt++;
    updateAltDesc();
}

void Widget::on_listView_activated(const QModelIndex &index)
{
    ui->pushButton_8->setEnabled(1);
}
