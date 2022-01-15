#include "info_link.h"
#include "ui_info_link.h"

#include <QDesktopServices>
#include <QUrl>
#include <QPixmap>

info_link::info_link(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::info_link)
{
    ui->setupUi(this);
    QPixmap pix("..\\growbox_desktop_main_window\\img\\Dead.png");
    ui->label_pic->setPixmap(pix.scaled(180,180,Qt::KeepAspectRatio));
    setWindowIcon(QIcon("..\\growbox_desktop_main_window\\img\\Gift_light_duotone.png"));
    setWindowTitle(tr("Дмитрий Валерьевич, ссылка на курсовую по ГОСТ)))"));
}


info_link::~info_link()
{
    delete ui;
}

void info_link::on_pushButton_clicked()
{
    QString link="https://docs.google.com/document/d/1riUCcy_DRPo4QCHqKomH8b4hof6V8YZtGa3Bdlc_ypQ/edit?usp=sharing";
    QDesktopServices::openUrl(QUrl(link));
}

