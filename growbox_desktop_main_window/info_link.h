#ifndef INFO_LINK_H
#define INFO_LINK_H

#include <QDialog>

namespace Ui {
class info_link;
}

class info_link : public QDialog
{
    Q_OBJECT

public:
    explicit info_link(QWidget *parent = nullptr);
    ~info_link();

private slots:
    void on_pushButton_clicked();

private:
    Ui::info_link *ui;
};

#endif // INFO_LINK_H
