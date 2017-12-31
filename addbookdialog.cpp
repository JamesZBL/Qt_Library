#include "addbookdialog.h"
#include "ui_addbookdialog.h"

AddBookDialog::AddBookDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::AddBookDialog)
{
  ui->setupUi(this);
}

AddBookDialog::~AddBookDialog()
{
  delete ui;
}

void AddBookDialog::accept(){
  this->hide();
  emit addBook(ui->txtName->toPlainText(),ui->txtNumber->toPlainText());
}
