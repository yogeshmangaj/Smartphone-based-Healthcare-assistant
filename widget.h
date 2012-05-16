#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtSql>
#include <QDataWidgetMapper>
#include <QApplication>
#include <QStringListModel>
#include <QtDebug>


namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void setupModel();
    QSqlRelationalTableModel *model, *modelCauses;
    QItemSelectionModel *selectionModel;
    QDataWidgetMapper *mapper;
    QSqlDatabase db;


    void setupDb();
private:
    Ui::Widget *ui;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_12_clicked();

};

#endif // WIDGET_H
