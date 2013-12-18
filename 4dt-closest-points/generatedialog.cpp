#include "generatedialog.h"
#include "ui_generatedialog.h"

GenerateDialog::GenerateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GenerateDialog)
{
    ui->setupUi(this);
}

int GenerateDialog::based_points() const
{
    return ui->basedpoints_spin->value();
}

int GenerateDialog::routes_count() const
{
    return ui->routescount_spin->value();
}

int GenerateDialog::route_points() const
{
    return ui->routepoints_spin->value();
}

GenerateDialog::~GenerateDialog()
{
    delete ui;
}
