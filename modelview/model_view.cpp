#include "model_view.h"

model_view::model_view(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    studentClass.setId("1");
    studentClass.setName("1 class");

    //为model设置标题
    QStringList headers;
    headers << "name" << "class";
    model = new QStandardItemModel;
    model->setHorizontalHeaderLabels(headers);

    //为view设置model
    ui.listView->setModel(model);
    ui.tableView->setModel(model);
    // ui->tableView->hide();
}

void model_view::on_pushButton_clicked()
{
    QString id = ui.lineedit_id->text();
    QString name = ui.lineedit_name->text();
    Student student;
    student.setId(id);
    student.setName(name);

    //if (studentClass.add(student))
    //{
    //    ui.listWidget->addItem(student.getName());
    //}

    if (studentClass.add(student))
    {
        //创建model对应的item
        QStandardItem* itemName = new QStandardItem(name);
        QStandardItem* itemStudentClass = new QStandardItem(studentClass.getName());

        QList<QStandardItem*> itemList;
        itemList << itemName << itemStudentClass;
        model->appendRow(itemList);
    }

}





