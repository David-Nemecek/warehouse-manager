#ifndef DIALOGADDPRODUCT_H
#define DIALOGADDPRODUCT_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class DialogAddProduct;
}

class DialogAddProduct : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddProduct(QWidget *parent = nullptr, QSqlDatabase db = QSqlDatabase::database());
    ~DialogAddProduct();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogAddProduct *ui;
    QSqlDatabase m_db;
};

#endif // DIALOGADDPRODUCT_H
