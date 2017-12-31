#include "addreaderdialog.h"
#include "ui_addreaderdialog.h"

AddReaderDialog::AddReaderDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::AddReaderDialog)
{
  ui->setupUi(this);
}

AddReaderDialog::~AddReaderDialog()
{
  delete ui;
}

void AddReaderDialog::accept(){
  this->hide();
  emit addReader(ui->txtCode->toPlainText(),ui->txtName->toPlainText());
}
