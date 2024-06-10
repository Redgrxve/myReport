#include "reportdetailswidget.h"
#include "ui_reportdetailswidget.h"
#include "calendardialog.h"
#include "groupscomboboxdelegate.h"
#include "absenteesitemdelegate.h"
#include "databasemanager.h"
#include "grouptablewidgetitem.h"
#include "absenteestablewidgetitem.h"

#include <QMessageBox>

ReportDetailsWidget::ReportDetailsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ReportDetailsWidget)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(0);
    ui->saveButton->setEnabled(false);

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
    if (date.isNull()) {
        ui->dateLabel->setText("Выберите дату");
        ui->dayLabel->clear();
        return;
    }
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
    if (!m_isSaved) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,
                              tr("Рапортичка не сохранена"),
                              tr("Вы не сохранили рапортичку."
                                 "\nВы хотите переключиться на другую?"));
        if (reply == QMessageBox::StandardButton::No)
            return;
    }

    setDate(date);
    ui->tableWidget->setRowCount(0);

    auto dbManager = DatabaseManager::instance();
    QHash<int, QStringList> absentees = dbManager->selectFromAbsentees(date);
    QVector<int> groupsId = absentees.keys();
    for (int groupId : groupsId) {
        int newRowIndex = insertRow();
        auto groupItem = groupTableItem(newRowIndex, 0);
        auto absenteesItem = absenteesTableItem(newRowIndex, 1);

        QString groupName = dbManager->selectNameFromGroups(groupId);
        QString absenteesStr = absentees[groupId].join(", ");

        groupItem->setGroupId(groupId);
        absenteesItem->setAbsentees(absentees[groupId]);
        groupItem->setText(groupName);
        absenteesItem->setText(absenteesStr == "null" ? "" : absenteesStr);
    }
    m_isSaved = true;
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
    GroupTableWidgetItem* groupsItem = new GroupTableWidgetItem;
    AbsenteesTableWidgetItem* absenteesItem = new AbsenteesTableWidgetItem;
    ui->tableWidget->setItem(newRowIndex, 0, groupsItem);
    ui->tableWidget->setItem(newRowIndex, 1, absenteesItem);
    emit rowInserted(newRowIndex);
    ui->saveButton->setEnabled(true);
    return newRowIndex;
}

void ReportDetailsWidget::removeLastRow()
{
    int newRowIndex = ui->tableWidget->rowCount() - 1;
    ui->tableWidget->removeRow(newRowIndex);

    if (ui->tableWidget->rowCount() == 0) {
        ui->saveButton->setEnabled(false);
    }
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

bool ReportDetailsWidget::saveToDatabase()
{
    int rowCount = ui->tableWidget->rowCount();
    if (!rowCount)
        return false;

    auto dbManager = DatabaseManager::instance();
    if (!dbManager->deleteFromAbsentees(m_date))
        return false;

    for (int row = 0; row < rowCount; ++row) {
        auto groupItem = groupTableItem(row, 0);
        auto absenteesItem = absenteesTableItem(row, 1);
        if (absenteesItem->absentees().isEmpty()) {
            absenteesItem->setAbsentees({"null"});
        }
        for (const QString &name : absenteesItem->absentees()) {
            if (!dbManager->insertToAbsentees(groupItem->groupId(), m_date, name))
                return false;
        }
    }
    m_isSaved = true;
    return true;
}

void ReportDetailsWidget::onRowInserted(int newRowIndex)
{
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(newRowIndex, 0, item);
}

void ReportDetailsWidget::onCellEdit(int row, int column)
{
    if (column == 0) {
        auto item = ui->tableWidget->item(row, column);
        auto groupsDelegate = groupsComboBoxDelegate();
        groupsDelegate->setAvailableGroups(availableGroups(item->text()));
    }
    m_isSaved = false;
}

void ReportDetailsWidget::onSaveClicked()
{
    if (m_date.isNull()) {
        QMessageBox::critical(this, "Ошибка", "Необходимо установить дату.");
        return;
    }

    if (!saveToDatabase()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось сохранить таблицу."
                                              "\nВозможно, таблица пустая, или вы не заполнили строки."
                                              "\nПопробуйте еще раз");
        return;
    }
    emit saveClicked(m_date);
}

AbsenteesItemDelegate *ReportDetailsWidget::absenteesItemDelegate() const
{
    return static_cast<AbsenteesItemDelegate*>(ui->tableWidget->itemDelegateForColumn(1));
}

GroupsComboBoxDelegate *ReportDetailsWidget::groupsComboBoxDelegate() const
{
    return static_cast<GroupsComboBoxDelegate*>(ui->tableWidget->itemDelegateForColumn(0));
}

GroupTableWidgetItem *ReportDetailsWidget::groupTableItem(int row, int column) const
{
    return static_cast<GroupTableWidgetItem*>(ui->tableWidget->item(row, column));
}

AbsenteesTableWidgetItem *ReportDetailsWidget::absenteesTableItem(int row, int column) const
{
    return static_cast<AbsenteesTableWidgetItem*>(ui->tableWidget->item(row, column));
}
