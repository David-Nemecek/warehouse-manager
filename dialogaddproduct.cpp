#include "dialogaddproduct.h"
#include "ui_dialogaddproduct.h"

DialogAddProduct::DialogAddProduct(QWidget *parent,  QSqlDatabase db) :
    QDialog(parent),
    ui(new Ui::DialogAddProduct)
{
    ui->setupUi(this);
    m_db = db;
}

DialogAddProduct::~DialogAddProduct()
{
    delete ui;
}

void DialogAddProduct::on_buttonBox_accepted()
{
    QSqlQuery q("INSERT INTO products (`ProductName`, `StartingInventory`, `InventoryReceived`, `InventoryShipped`, `InventoryOnHand`, `MinimumRequired`) VALUES ('"
                + ui->lineEdit_productName->text() + "', " + ui->spinBox_startingInventory->text() + ", 0, 0, " + ui->spinBox_startingInventory->text() + ", " + ui->spinBox_minimumRequired->text() + ")", m_db);
}
