#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtSql>
#include <QDataWidgetMapper>
#include <QApplication>
#include <QStringListModel>
#include <QtDebug>
#include <QMessage>
#include <QMessageService>
#include <QMessageAddress>
#include <QMessageBox>

namespace Ui {
    class Widget;
}
// QtMobility namespace
QTM_USE_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void setupModel();
    int ralt;
    QSqlRelationalTableModel *model, *modelCauses, *modelPrev, *modelAlt, *modelPrevItems;
    QItemSelectionModel *selectionModel;
    QDataWidgetMapper *mapper;
    QSqlDatabase db;
    QMessage message;
    QMessageService* m_service;
    void setupDb();
    void updateAltDesc();
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

    void on_pushButton_13_clicked();
    void on_pushButton_15_sendsms_clicked();
    void on_pushButton_14_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_15_clicked();
    void on_pushButton_16_clicked();
    void on_pushButton_18_clicked();
    void on_pushButton_19_clicked();
    void on_pushButton_20_clicked();
    void on_pushButton_21_clicked();
    void on_pushButton_17_clicked();
    void on_pushButton_23_clicked();
    void on_pushButton_22_clicked();
    void on_pushButton_24_clicked();
    void on_listView_activated(const QModelIndex &index);
};

#endif // WIDGET_H
