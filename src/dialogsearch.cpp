#include "dialogsearch.h"
#include "ui_dialogsearch.h"

DialogSearch::DialogSearch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSearch)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    ui->lineEditTextToSearch->paste();
    connect (ui->pushButtonClose,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect (ui->pushButtonSearch,SIGNAL(clicked(bool)),this,SLOT(Search()));
    connect (ui->pushButtonPrevious,SIGNAL(clicked(bool)),this,SLOT(BackwardSearch()));

}

DialogSearch::~DialogSearch()
{
    delete ui;
}


void DialogSearch::Search()
{
    if (! ui->lineEditTextToSearch->text().isEmpty() )
    {
        emit Search (ui->lineEditTextToSearch->text(),ui->checkBoxCaseSenstitve->isChecked(),ui->checkBoxWordONly->isChecked());
    }
}

void DialogSearch::BackwardSearch()
{
    if (! ui->lineEditTextToSearch->text().isEmpty() )
    {
        emit SearchBack(ui->lineEditTextToSearch->text(),ui->checkBoxCaseSenstitve->isChecked(),ui->checkBoxWordONly->isChecked());
    }
}
