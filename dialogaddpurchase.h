#ifndef DIALOGADDPURCHASE_H
#define DIALOGADDPURCHASE_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class DialogAddPurchase;
}

class DialogAddPurchase : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddPurchase(QWidget *parent = nullptr, QSqlDatabase db = QSqlDatabase::database());
    ~DialogAddPurchase();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogAddPurchase *ui;
    QSqlDatabase m_db;
    std::map<QString, int> products;
    std::map<QString, int> suppliers;

    void setDialogValues();
};

#endif // DIALOGADDPURCHASE_H
