#pragma once

#include <QtWidgets/QMainWindow>
#include <QtGui/QStandardItemModel>
#include "ui_model_view.h"

// 学生类
class Student
{
public:
    QString getId() const { return id; }
    void setId(const QString& value) { id = value; }

    QString getName() const { return name; }
    void setName(const QString& value) { name = value; }

    //判断该学生是否有效,学号和姓名都不能为空
    bool isValid() const
    {
        return !id.isEmpty() && !name.isEmpty();
    }

private:
    QString id;     //学生学号
    QString name;   //姓名
};

//班级类
class StudentClass
{
public:
    QString getId() const { return id; }
    void setId(const QString& value) { id = value; }

    QString getName() const { return name; }
    void setName(const QString& value) { name = value; }

    //为班级添加一个新同学
    bool add(const Student& student)
    {
        bool success = false;

        if (student.isValid())
        {
            if (!studentMap.contains(student.getId()))
            {
                studentMap.insert(student.getId(), student);
                success = true;
            }
        }
        return success;
    }

    //获取学生列表
    QList<Student> getStudentList() const
    {
        return studentMap.values();
    }

private:
    QString id;  //班级id
    QString name;//班级名称
    QMap<QString, Student> studentMap;//key-学生学号
};

class model_view : public QMainWindow
{
    Q_OBJECT

public:
    model_view(QWidget *parent = Q_NULLPTR);

private slots:
    void on_pushButton_clicked();

private:
    Ui::model_viewClass ui;

    StudentClass studentClass;//保存有班级数据

    QStandardItemModel *model;
};

#include <QDebug>
#include <QPushButton>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QListView>
#include <QWidget>

class StandardItemModelWidget: public QWidget  
{
    Q_OBJECT

public:

explicit StandardItemModelWidget(QWidget* parent = nullptr) :
    QWidget(parent)
{
    //创建界面
    QVBoxLayout* layout = new QVBoxLayout(this);
    QStandardItemModel* model = new QStandardItemModel;
    QListView* view = new QListView;
    view->setModel(model);
    layout->addWidget(view);


    //向model中添加数据
    QStringList textList;
    textList << "apple 1" << "apple 2" << "orange" << "banana" << "apple 3" << "red apple";
    for (auto& text : textList)
    {
        QStandardItem* item = new QStandardItem(text);
        model->appendRow(item);
        item->setEditable(false);//设置每个item为不可编辑
    }

    //检索所有的包含apple的数据项
    const int customRole = Qt::UserRole;
    QList<QStandardItem*> appleItems = model->findItems("apple", Qt::MatchContains);
    foreach(QStandardItem * appleItem, appleItems)
    {
        //为apple项设置一个随机生成的颜色图标
        QPixmap pixmap(25, 25);
        QColor clr(qrand() % 255, qrand() % 255, qrand() % 255);
        pixmap.fill(clr);
        appleItem->setIcon(QIcon(pixmap));
        appleItem->setToolTip(clr.name());
        appleItem->setData(clr.name(), customRole);
    }

    //当点击item时，在控制台输出其保存的颜色值
    connect(view, &QListView::clicked, [=](const QModelIndex& index) {
        QStandardItem* item = model->itemFromIndex(index);
        qDebug() << item->data(customRole).toString();
        });

    //点击按钮删除所有apple项
    QPushButton* btn = new QPushButton("delete contain apple");
    layout->addWidget(btn);
    connect(btn, &QPushButton::clicked, [=]() {
        QList<QStandardItem*> appleItems = model->findItems("apple", Qt::MatchContains);
        for (int i = appleItems.size() - 1; i >= 0; --i)
        {
            model->removeRow(appleItems.at(i)->row());
        }
        });

    resize(200, 400);
}
};
