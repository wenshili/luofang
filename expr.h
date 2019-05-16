#ifndef EXPR_H
#define EXPR_H

#include <QDialog>
#include <QStack>

namespace Ui {
class expr;
}

class expr : public QDialog
{
    Q_OBJECT

public:
    explicit expr(QWidget *parent = 0);
    ~expr();

    void calculate();
    int  process(char a,char b);

private slots:
    void on_btn_0_clicked();

    void on_btn_1_clicked();

    void on_btn_2_clicked();

    void on_btn_3_clicked();

    void on_btn_4_clicked();

    void on_btn_5_clicked();

    void on_btn_6_clicked();

    void on_btn_7_clicked();

    void on_btn_8_clicked();

    void on_btn_9_clicked();

    void on_btn_plus_clicked();

    void on_btn_sub_clicked();

    void on_btn_mul_clicked();

    void on_btn_div_clicked();

    void on_btn_equ_clicked();

    void on_btn_point_clicked();

    void on_btn_left_clicked();

    void on_btn_right_clicked();

    void on_btn_delet_clicked();

    void on_btn_clear_clicked();

private:
    QString tmp;
    Ui::expr *ui;

};

#endif // EXPR_H
