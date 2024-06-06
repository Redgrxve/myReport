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

void ReportDetailsWidget::setDate(const QDate &date)
{
    m_date = date;
    ui->dateLabel->setText(date.toString("dd.MM.yyyy"));
    QLocale locale = QLocale(QLocale::Russian);
    QString localeDate = locale.toString(date, "dddd");
    ui->dayLabel->setText(localeDate);
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
    auto dbManager = DatabaseManager::instance();
    QHash<int, QStringList> absentees = dbManager->selectFromAbsentees(date);
    QVector<int> groupsId = absentees.keys();
    ui->tableWidget->setRowCount(0);
    setDate(date);
    AbsenteesCellWidget::absentees() = absentees;
    for (int groupId : groupsId) {
        int newRowIndex = insertRow();
        QString groupName = dbManager->selectNameFromGroups(groupId);
        QString absenteesString = absentees[groupId].join(", ");
        QTableWidgetItem *groupItem = ui->tableWidget->item(newRowIndex, 0);
        if (!groupItem) {
            groupItem = new QTableWidgetItem;
            ui->tableWidget->setItem(newRowIndex, 0, groupItem);
        }

        QTableWidgetItem *absenteesItem = ui->tableWidget->item(newRowIndex, 1);
        if (!absenteesItem) {
            absenteesItem = new QTableWidgetItem;
            ui->tableWidget->setItem(newRowIndex, 1, absenteesItem);
        }

        groupItem->setText(groupName);
        absenteesItem->setText(absenteesString);
    }
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
    setDate(date);
}

int ReportDetailsWidget::insertRow()
{
    int newRowIndex = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(newRowIndex);
    emit rowInserted(newRowIndex);
    return newRowIndex;
}

void ReportDetailsWidget::removeLastRow()
{
    if (ui->tableWidget->rowCount() == 0)
        return;

    int newRowIndex = ui->tableWidget->rowCount() - 1;
    QString group = ui->tableWidget->item(newRowIndex, 0)->text();
    int groupId = DatabaseManager::instance()->selectIdFromGroups(group);
    if (groupId != -1)
        AbsenteesCellWidget::absentees().remove(groupId);

    ui->tableWidget->removeRow(newRowIndex);
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

bool ReportDetailsWidget::saveToDatabase() const
{
    auto dbManager = DatabaseManager::instance();
    if (!dbManager->deleteFromAbsentees(m_date))
        return false;

    QHash<int, QStringList> absentees = AbsenteesCellWidget::absentees();

    QVector<int> indexes = absentees.keys();
    for (int index : indexes) {
        for (const QString &name : absentees[index]) {
            if (!dbManager->insertToAbsentees(index, m_date, name))
                return false;
        }
    }
    return true;
}

AbsenteesItemDelegate *ReportDetailsWidget::absenteesItemDelegate() const
{
    return static_cast<AbsenteesItemDelegate*>(ui->tableWidget->itemDelegateForColumn(1));
}

GroupsComboBoxDelegate *ReportDetailsWidget::groupsComboBoxDelegate() const
{
    return static_cast<GroupsComboBoxDelegate*>(ui->tableWidget->itemDelegateForColumn(0));
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
        auto absenteesDelegate = absenteesItemDelegate();
        absenteesDelegate->setGroupId(groupId);
    } else {
        auto comboBoxDelegate = groupsComboBoxDelegate();
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

    if (!saveToDatabase()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось сохранить таблицу"
                                              "\nПопробуйте еще раз");
        return;
    }
    emit saveClicked(m_date);
}
