#ifndef DIALOGADDORDER_H
#define DIALOGADDORDER_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class DialogAddOrder;
}

class DialogAddOrder : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddOrder(QWidget *parent = nullptr, QSqlDatabase db = QSqlDatabase::database());
    ~DialogAddOrder();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogAddOrder *ui;
    QSqlDatabase m_db;
    std::map<QString, int> products;
    std::map<QString, int> purchasers;

    void setDialogValues();
};

#endif // DIALOGADDORDER_H
