#include "expr.h"
#include "ui_expr.h"
#include "floatnumber.h"
#include <QPushButton>
#include <QTextEdit>
#include <QString>
#include <QDialog>
#include <QDebug>

typedef struct node _tNode;
#define NUM_OF_NUMBER 20
#define KIND_NUMBER  0
#define KIND_OPERATOR 1

expr::expr(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::expr)
{
    ui->setupUi(this);
    this->tmp = "";
}

expr::~expr()
{
    delete ui;
}

void expr::on_btn_0_clicked()
{
    if(this->tmp != " ")
    {
        this->tmp += this->ui->btn_0->text();
        this->ui->lbl_display->setText(this->tmp);
    }
    }

void expr::on_btn_1_clicked()
{
     this->tmp += this->ui->btn_1->text();
      this->ui->lbl_display->setText(this->tmp);
}

void expr::on_btn_2_clicked()
{
     this->tmp += this->ui->btn_2->text();
    this->ui->lbl_display->setText(this->tmp);
}

void expr::on_btn_3_clicked()
{
     this->tmp += this->ui->btn_3->text();
     this->ui->lbl_display->setText(this->tmp);
}

void expr::on_btn_4_clicked()
{
    this->tmp += this->ui->btn_4->text();
    this->ui->lbl_display->setText(this->tmp);
}


void expr::on_btn_5_clicked()
{
    this->tmp += this->ui->btn_5->text();
    this->ui->lbl_display->setText(this->tmp);
}

void expr::on_btn_6_clicked()
{
    this->tmp += this->ui->btn_6->text();
    this->ui->lbl_display->setText(this->tmp);
}

void expr::on_btn_7_clicked()
{
    this->tmp += this->ui->btn_7->text();
    this->ui->lbl_display->setText(this->tmp);
}

void expr::on_btn_8_clicked()
{
    this->tmp += this->ui->btn_8->text();
    this->ui->lbl_display->setText(this->tmp);
}

void expr::on_btn_9_clicked()
{
    this->tmp += this->ui->btn_9->text();
    this->ui->lbl_display->setText(this->tmp);
}

void expr::on_btn_plus_clicked()
{
    if(tmp != " ")
    {
        this->tmp += this->ui->btn_plus->text();
        this->ui->lbl_display->setText(this->tmp);
    }
  }

void expr::on_btn_sub_clicked()
{
    if(tmp != " ")
    {
        this->tmp += this->ui->btn_sub->text();
        this->ui->lbl_display->setText(this->tmp);
       }
}

void expr::on_btn_mul_clicked()
{
    if(tmp != " ")
    {
        this->tmp += this->ui->btn_mul->text();
        this->ui->lbl_display->setText(this->tmp);
    }
}

void expr::on_btn_div_clicked()
{
    if(tmp != " ")
    {
        this->tmp += this->ui->btn_div->text();
        this->ui->lbl_display->setText(this->tmp);

    }
}

void expr::on_btn_equ_clicked()
{
    if(tmp != " ")
    {
           expr::calculate();
         this->ui->lbl_display->setText(this->tmp);
    }

}

void expr::on_btn_point_clicked()
{
    if(tmp != " ")
    {
        this->tmp += this->ui->btn_point->text();
        this->ui->lbl_display->setText(this->tmp);
    }
}

void expr::on_btn_left_clicked()
{
    if(tmp != " ")
    {
        this->tmp += this->ui->btn_left->text();
        this->ui->lbl_display->setText(this->tmp);
    }
}

void expr::on_btn_right_clicked()
{
    if(tmp != " ")
    {
        this->tmp += this->ui->btn_right->text();
        this->ui->lbl_display->setText(this->tmp);
      }
}

void expr::on_btn_delet_clicked()
{
    if(tmp != " ")
    {
        tmp = tmp.left(tmp.length()-1);
        this->ui->lbl_display->setText(this->tmp);
    }
}

void expr::on_btn_clear_clicked()
{
    if(tmp != " ")
    {
        tmp.clear();
        this->ui->lbl_display->clear();
        this->ui->lbl_display->setText("0");
    }
}



void expr::calculate()
{
    _tNode Node[NUM_OF_NUMBER];
    double num = 0;
    int   i = 0;                         //字符串的位置
    int num_of_point = 0;      //小数点后数字的个数
    int num_or_op = 0;         //浮点数和操作符个数
    int isfloat = 0;                 //小数点
    int len = tmp.length();   //字符串长度

    while(i < len)
    {
        if(tmp[i] >= '0' && tmp[i] <= '9')
        {
            if(!isfloat)   //整数部分
            {
                num = num*10 + (tmp[i].toLatin1()-'0');   //tmp[i].toLatin1()将字符i转换为ASCII码
                ++i;
            }
            else   //小数部分
            {
                double per = 1;
                for(int k = 0;k < num_of_point;k++)
                    per *= 0.1;
                num +=  (tmp[i].toLatin1()-'0') * per;
                num_of_point++;
                ++i;
            }
        }
        else if(tmp[i] == '.')   //读到小数点
        {
            isfloat = 1;
            num_of_point = 1;
           ++i;
        }
        else  //读到操作符
        {
            if(num) //读到操作符后说明一个完整的数字输入完毕，要将数字、小数点等清零
            {
                Node[num_or_op].flag = KIND_NUMBER;
                Node[num_or_op].num.a = num;
                num = 0;
                ++num_or_op;
                isfloat= 0;
                num_of_point = 0;
            }
            Node[num_or_op].flag = KIND_OPERATOR;
            Node[num_or_op].num.op = tmp[i].toLatin1();
            ++num_or_op;
            ++i;
        }
    }
    if(num)   //最后一个操作数
    {
        Node[num_or_op].flag = KIND_NUMBER;
        Node[num_or_op].num.a = num;
        ++num_or_op;
        num = 0;
    }

   QStack<_tNode>pNode;  //构建一个_tNode类型的栈pNode，是一个保存操作符栈
    _tNode _Node[NUM_OF_NUMBER];
    int j = 0;
    for(int m = 0;m< num_or_op;)
    {
        if(Node[m].flag)  //符号入栈
        {
            if(pNode.isEmpty())
            {
                pNode.push(Node[m++]);

            }
            else
            {
                _tNode tem = pNode.top();
                int ret = process(tem.num.op,Node[m].num.op);
                switch(ret)
                {
                    case -1:
                        pNode.push(Node[m++]);
                        break;
                     case 1:
                          _Node[j++] = pNode.top();
                          pNode.pop();
                          break;
                       default:
                             pNode.pop();
                            m++;
                            break;
            }
            }
        }
    else
    {
        _Node[j++] = Node[m++];
    }
    }
while(!pNode.isEmpty()) //弹出栈中剩余的元素
{
    _tNode tem = pNode.top();
    if(tem.num.op != '(' &&tem.num.op != ')')
        _Node[j++] = tem;
     pNode.pop();
}

QStack<double> last;  //构建一个数据栈
double d1,d2;
for(int n = 0;n < j;n++)
{
    if(_Node[n].flag) //遇到符号弹出数字进行计算
    {
        d2 = last.top();
        last.pop();
        d1 = last.top();
        last.pop();
        switch(_Node[n].num.op)
        {
            case '+':
                   d1 += d2;
                    break;
        case '-':
            d1 -= d2;
            break;
        case '*':
            d1 *= d2;
            break;
        case '/':
            d1 /= d2;
            break;
        default:
            break;
        }
        last.push(d1);
    }
    else
    {
        last.push(_Node[n].num.a);
    }
}
qDebug() << d1;
tmp += '=';
tmp += QString::number(d1);
}

int expr::process(char a,char b)
{
    char aim[7][8] = {{ ">><<<>>" },{ ">><<<>>" },{ ">>>><>>" },{ ">>>><>>" },{ "<<<<<=1" },{ ">>>>1>>" },{ "<<<<<1=" }};
    char sta[7] = { '+','-','*','/','(',')','#' };
    char result;
    int i,pa,pb;
    for (i = 0; i<6; i++)
          {
             if (a == sta[i])
             {
                 pa = i;
             }
             if (b == sta[i])
             {
                 pb = i;
             }
          }
    result = aim[pa][pb];
    if(result == '>')return 1;
    else if(result == '<')return -1;
    else return 0;
  }

