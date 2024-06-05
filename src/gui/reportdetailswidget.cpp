#include "reportdetailswidget.h"
#include "absenteescellwidget.h"
#include "ui_reportdetailswidget.h"
#include "calendardialog.h"
#include "groupscomboboxdelegate.h"
#include "absenteesitemdelegate.h"
#include "databasemanager.h"

#include <QMessageBox>

ReportDetailsWidget::ReportDetailsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ReportDetailsWidget)
{
    ui->setupUi(this);
    setupDelegates();

    connect(ui->celendarButton, &QPushButton::clicked,
            this, &ReportDetailsWidget::onCalendarButtonClicked);
    connect(ui->addRowButton, &QPushButton::clicked,
            this, &ReportDetailsWidget::insertRow);
    connect(ui->removeRowButton, &QPushButton::clicked,
            this, &ReportDetailsWidget::removeLastRow);
    connect(ui->saveButton, &QPushButton::clicked,
            this, &ReportDetailsWidget::onSaveClicked);
    connect(ui->tableWidget, &QTableWidget::cellDoubleClicked,
            this, &ReportDetailsWidget::onCellEdit);
    connect(this, &ReportDetailsWidget::rowInserted,
            this, &ReportDetailsWidget::onRowInserted);
}

ReportDetailsWidget::~ReportDetailsWidget()
{
    delete ui;
}

void ReportDetailsWidget::setupDelegates()
{
    GroupsComboBoxDelegate *comboBoxDelegate = new GroupsComboBoxDelegate(DatabaseManager::instance()->selectNamesFromGroups(),
                                                                          ui->tableWidget);
    ui->tableWidget->setItemDelegateForColumn(0, comboBoxDelegate);

    AbsenteesItemDelegate *absenteesDelegate = new AbsenteesItemDelegate(ui->tableWidget);
    ui->tableWidget->setItemDelegateForColumn(1, absenteesDelegate);
}

void ReportDetailsWidget::setupFromDatabase(const QDate &date)
{

}


void ReportDetailsWidget::onCalendarButtonClicked()
{
    CalendarDialog calendarDialog(this);
    connect(&calendarDialog, &CalendarDialog::dateSelected,
            this, &ReportDetailsWidget::onDateSelected);
    calendarDialog.exec();
}

void ReportDetailsWidget::onDateSelected(const QDate &date)
{
    m_date = date;
    ui->dateLabel->setText(date.toString("dd.MM.yyyy"));
    QLocale locale = QLocale(QLocale::Russian);
    QString localeDate = locale.toString(date, "dddd");
    ui->dayLabel->setText(localeDate);
}

void ReportDetailsWidget::insertRow()
{
    int newRowIndex = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(newRowIndex);
    emit rowInserted(newRowIndex);
}

void ReportDetailsWidget::removeLastRow()
{
    ui->tableWidget->removeRow(ui->tableWidget->rowCount() - 1);
}

QStringList ReportDetailsWidget::availableGroups(const QString &currentGroup) const
{
    QStringList groups = DatabaseManager::instance()->selectNamesFromGroups();
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        QString selectedGroup = ui->tableWidget->item(row, 0)->text();
        if (groups.contains(selectedGroup)
            && selectedGroup != currentGroup) {
            groups.removeOne(selectedGroup);
        }
    }
    return groups;
}

void ReportDetailsWidget::onRowInserted(int newRowIndex)
{
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(newRowIndex, 0, item);
}

void ReportDetailsWidget::onCellEdit(int row, int column)
{
    if (column == 1) {
        QString groupName = ui->tableWidget->item(row, 0)->text();
        int groupId = groupName.isEmpty() ? -1 : DatabaseManager::instance()->selectIdFromGroups(groupName);
        auto absenteesDelegate = static_cast<AbsenteesItemDelegate*>(ui->tableWidget->itemDelegateForColumn(1));
        absenteesDelegate->setGroupId(groupId);
    } else {
        auto comboBoxDelegate = static_cast<GroupsComboBoxDelegate*>(ui->tableWidget->itemDelegateForColumn(0));
        QString currentGroup = ui->tableWidget->item(row, column)->text();
        comboBoxDelegate->setAvailableGroups(availableGroups(currentGroup));
    }
}

void ReportDetailsWidget::onSaveClicked()
{
    if (m_date.isNull()) {
        QMessageBox::critical(this, "Ошибка", "Необходимо установить дату.");
        return;
    }
    emit saveClicked(m_date, AbsenteesCellWidget::absentees());
}
