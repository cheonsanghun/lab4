#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_01_clicked()
{
    if(ui->label_2->text().isEmpty()){
                ui->lineEdit_first->setText(ui->lineEdit_first->text() + "1");
    }
    else{
        ui->lineEdit_second->setText(ui->lineEdit_second->text() + "1");
    }
}

void Dialog::on_pushButton_02_clicked()
{
    if(ui->label_2->text().isEmpty()){
                ui->lineEdit_first->setText(ui->lineEdit_first->text() + "2");
    }
    else{
        ui->lineEdit_second->setText(ui->lineEdit_second->text() + "2");
    }
}

void Dialog::on_pushButton_03_clicked()
{
    if(ui->label_2->text().isEmpty()){
                ui->lineEdit_first->setText(ui->lineEdit_first->text() + "3");
    }
    else{
        ui->lineEdit_second->setText(ui->lineEdit_second->text() + "3");
    }
}

void Dialog::on_pushButton_04_clicked()
{
    if(ui->label_2->text().isEmpty()){
                ui->lineEdit_first->setText(ui->lineEdit_first->text() + "4");
    }
    else{
        ui->lineEdit_second->setText(ui->lineEdit_second->text() + "4");
    }
}

void Dialog::on_pushButton_05_clicked()
{
    if(ui->label_2->text().isEmpty()){
                ui->lineEdit_first->setText(ui->lineEdit_first->text() + "5");
    }
    else{
        ui->lineEdit_second->setText(ui->lineEdit_second->text() + "5");
    }
}

void Dialog::on_pushButton_06_clicked()
{
    if(ui->label_2->text().isEmpty()){
                ui->lineEdit_first->setText(ui->lineEdit_first->text() + "6");
    }
    else{
        ui->lineEdit_second->setText(ui->lineEdit_second->text() + "6");
    }
}

void Dialog::on_pushButton_07_clicked()
{
    if(ui->label_2->text().isEmpty()){
                ui->lineEdit_first->setText(ui->lineEdit_first->text() + "7");
    }
    else{
        ui->lineEdit_second->setText(ui->lineEdit_second->text() + "7");
    }
}

void Dialog::on_pushButton_08_clicked()
{
    if(ui->label_2->text().isEmpty()){
                ui->lineEdit_first->setText(ui->lineEdit_first->text() + "8");
    }
    else{
        ui->lineEdit_second->setText(ui->lineEdit_second->text() + "8");
    }
}

void Dialog::on_pushButton_09_clicked()
{
    if(ui->label_2->text().isEmpty()){
                ui->lineEdit_first->setText(ui->lineEdit_first->text() + "9");
    }
    else{
        ui->lineEdit_second->setText(ui->lineEdit_second->text() + "9");
    }
}

void Dialog::on_pushButton_00_clicked()
{
    if(ui->label_2->text().isEmpty()){
                ui->lineEdit_first->setText(ui->lineEdit_first->text() + "0");
    }
    else{
        ui->lineEdit_second->setText(ui->lineEdit_second->text() + "0");
    }
}

void Dialog::on_pushButton_clear_clicked()
{
    ui->lineEdit_first->setText("");
    ui->label_2->setText("");
    ui->lineEdit_second->setText("");
    ui->lineEdit_result->setText("");

}

void Dialog::on_pushButton_eq_clicked()
{
    first = ui->lineEdit_first->text().toDouble();
    second = ui->lineEdit_second->text().toDouble();
    if(ui->label_2->text() == "+"){
        ui->lineEdit_result->setText(QString::number(first + second));
    }else if(ui->label_2->text() == "-"){
        ui->lineEdit_result->setText(QString::number(first - second));
    }else if(ui->label_2->text() == "*"){
        ui->lineEdit_result->setText(QString::number(first * second));
    }else if(ui->label_2->text() == "/"){
        ui->lineEdit_result->setText(QString::number(first / second));
    }

}

void Dialog::on_pushButton_plus_clicked()
{
    ui->label_2->setText("+");
}

void Dialog::on_pushButton_min_clicked()
{
    ui->label_2->setText("-");
}

void Dialog::on_pushButton_Div_clicked()
{
    ui->label_2->setText("/");
}

void Dialog::on_pushButton_sqrt_clicked()
{
    ui->label_2->setText("*");
}

void Dialog::on_pushButton_AC_clicked()
{
    ui->lineEdit_first->clear();
    ui->lineEdit_second->clear();
    ui->lineEdit_result->clear();
    ui->label_2->clear();
}
