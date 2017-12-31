#include "lendbookdialog.h"
#include "ui_lendbookdialog.h"

LendBookDialog::LendBookDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::LendBookDialog)
{
  ui->setupUi(this);
}

LendBookDialog::~LendBookDialog()
{
  delete ui;
}
