#include "customwidget.h"
#include<QApplication>
#include<QDesktopWidget>
#include<QMessageBox>

// 可移动窗体
CustomMoveWidget::CustomMoveWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);

    max = false;
    m_mousePressed = false;
    location = this->geometry();

}

CustomMoveWidget::~CustomMoveWidget()
{

}

/*CustomMoveWidget::mouseMoveEvent 鼠标点击移动*/
void CustomMoveWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (m_mousePressed && (e->buttons() && Qt::LeftButton))
    {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void CustomMoveWidget::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        m_mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void CustomMoveWidget::mouseReleaseEvent(QMouseEvent *)
{
    m_mousePressed = false;
}

void CustomMoveWidget::slot_showMax()
{
    if (max) {
            this->setGeometry(location);
        } else {
            location = this->geometry();
            this->setGeometry(qApp->desktop()->availableGeometry());
        }
        max = !max;
}

void CustomMoveWidget::slot_showMin()
{
    this->showMinimized();
}

void CustomMoveWidget::slot_close()
{
    if( QMessageBox::question( this , "退出提示","确定退出?" ) == QMessageBox::Yes )
    {
         this->close();
    }
}



////////////////////
// 可移动对话框
CustomMoveDialog::CustomMoveDialog(QWidget *parent) :
    QDialog(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint); //去掉标题栏
    max = false;
    m_mousePressed = false;
    location = this->geometry();
}

CustomMoveDialog::~CustomMoveDialog()
{

}

/*CustomMoveWidget::mouseMoveEvent 鼠标点击移动*/
void CustomMoveDialog::mouseMoveEvent(QMouseEvent *e)
{
    if (m_mousePressed && (e->buttons() && Qt::LeftButton)&& !max )
    {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void CustomMoveDialog::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        m_mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void CustomMoveDialog::mouseReleaseEvent(QMouseEvent *)
{
    m_mousePressed = false;
}


void CustomMoveDialog::slot_showMax()
{
    if (max) {
            this->setGeometry(location);
        } else {
            location = this->geometry();
            this->setGeometry(qApp->desktop()->availableGeometry());
        }
        max = !max;
}

void CustomMoveDialog::slot_showMin()
{
    this->showMinimized();
}

void CustomMoveDialog::slot_close()
{
    if( QMessageBox::question( this , "退出提示","确定退出?" ) == QMessageBox::Yes )
    {
         this->close();
    }
}


////////////////////
// 可移动主窗口
CustomMoveMainWindow::CustomMoveMainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    max = false;
    m_mousePressed = false;
    location = this->geometry();
}

CustomMoveMainWindow::~CustomMoveMainWindow()
{

}

/*CustomMoveWidget::mouseMoveEvent 鼠标点击移动*/
void CustomMoveMainWindow::mouseMoveEvent(QMouseEvent *e)
{
    if (m_mousePressed && (e->buttons() && Qt::LeftButton)&& !max )
    {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void CustomMoveMainWindow::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        m_mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void CustomMoveMainWindow::mouseReleaseEvent(QMouseEvent *)
{
    m_mousePressed = false;
}


void CustomMoveMainWindow::slot_showMax()
{
    if (max) {
            this->setGeometry(location);
        } else {
            location = this->geometry();
            this->setGeometry(qApp->desktop()->availableGeometry());
        }
        max = !max;
}

void CustomMoveMainWindow::slot_showMin()
{
    this->showMinimized();
}

void CustomMoveMainWindow::slot_close()
{
    if( QMessageBox::question( this , "退出提示","确定退出?" ) == QMessageBox::Yes )
    {
         this->close();
    }
}
