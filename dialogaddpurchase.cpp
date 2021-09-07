#include "dialogaddpurchase.h"
#include "ui_dialogaddpurchase.h"

DialogAddPurchase::DialogAddPurchase(QWidget *parent, QSqlDatabase db) :
    QDialog(parent),
    ui(new Ui::DialogAddPurchase)
{
    ui->setupUi(this);
    m_db = db;

    setDialogValues();
}

DialogAddPurchase::~DialogAddPurchase()
{
    delete ui;
}

void DialogAddPurchase::setDialogValues()
{
    ui->dateEdit_purchaseDate->setDate(QDate::currentDate());
    ui->dateEdit_purchaseDate->setCalendarPopup(true);

    QSqlQueryModel *model = new QSqlQueryModel();

    // fill combobox products
    model->setQuery("SELECT ProductName, id FROM products", m_db);
    for (int i = 0; i < model->rowCount();i++) {
        products[model->record(i).value(0).toString()] = model->record(i).value(1).toInt();
        ui->comboBox_purchaseProduct->addItem(model->record(i).value(0).toString());
    }

    // fill combobox suppliers
    model->setQuery("SELECT Supplier, id FROM suppliers", m_db);
    for (int i = 0; i < model->rowCount();i++) {
        suppliers[model->record(i).value(0).toString()] = model->record(i).value(1).toInt();
        ui->comboBox_suppliers->addItem(model->record(i).value(0).toString());
    }
}

void DialogAddPurchase::on_buttonBox_accepted()
{
    int supplierId = suppliers.find(ui->comboBox_suppliers->currentText())->second;
    int productId = products.find(ui->comboBox_purchaseProduct->currentText())->second;

    QSqlQuery q("INSERT INTO purchases (`SupplierId`, `ProductId`, `NumberReceived`, `PurchaseDate`) VALUES ("
                + QString::number(supplierId) + ", " + QString::number(productId) + ", " + ui->spinBox_numberReceived->text() + ", '" + ui->dateEdit_purchaseDate->date().toString("yyyy-MM-dd") + "')", m_db);
    q.exec("UPDATE products SET InventoryReceived = (SELECT InventoryReceived FROM products WHERE id = " + QString::number(productId) + ") + " + ui->spinBox_numberReceived->text() + ", "
           "InventoryOnHand = (SELECT InventoryOnHand FROM products WHERE id = " + QString::number(productId) + ") + " + ui->spinBox_numberReceived->text() + " WHERE id = " + QString::number(productId));
}
