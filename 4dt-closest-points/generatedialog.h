#pragma once

#include <QDialog>

namespace Ui {
class GenerateDialog;
}

class GenerateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GenerateDialog(QWidget *parent = 0);
    int based_points() const;
    int routes_count() const;
    int route_points() const;

    ~GenerateDialog();

private:
    Ui::GenerateDialog *ui;
};
