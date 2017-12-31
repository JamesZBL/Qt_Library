#include "returnbookdialog.h"
#include "ui_returnbookdialog.h"

ReturnBookDialog::ReturnBookDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::ReturnBookDialog)
{
  ui->setupUi(this);
}

ReturnBookDialog::~ReturnBookDialog()
{
  delete ui;
}
