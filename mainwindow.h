#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>
#include "dialogaddpurchase.h"
#include "dialogaddorder.h"
#include "dialogaddproduct.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addConnection();
private slots:

    void on_pushButton_currentInventory_clicked();

    void on_pushButton_incomingPurchases_clicked();

    void on_pushButton_outgoingOrders_clicked();

    void on_pushButton_addPurchase_clicked();

    void on_pushButton_addOrder_clicked();

    void on_pushButton_addProduct_clicked();

    void on_pushButton_filterProducts_clicked();

    void on_pushButton_reverseFilter_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;

    void showCurrentInventory();
    void showIncomingPurchases();
    void showOutgoingOrders();
    void highlightNewActiveMenuButton(QPushButton *b);
    void initUI();

};

class CustomModel: public QSqlTableModel
{
    Q_OBJECT
public:
    explicit CustomModel(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase())
        : QSqlTableModel(parent, db) {}

    QVariant data(const QModelIndex &idx, int role) const override
    {
        if (role == Qt::BackgroundRole && isDirty(idx))
            return QBrush(QColor(Qt::yellow));
        return QSqlTableModel::data(idx, role);
    }
};

#endif // MAINWINDOW_H
