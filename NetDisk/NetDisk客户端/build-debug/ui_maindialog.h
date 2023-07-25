/********************************************************************************
** Form generated from reading UI file 'maindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINDIALOG_H
#define UI_MAINDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QWidget *wdg_left;
    QVBoxLayout *verticalLayout;
    QPushButton *pb_fillePage;
    QPushButton *pb_transmitPage;
    QPushButton *pb_sharePage;
    QSpacerItem *verticalSpacer;
    QPushButton *pb_user;
    QWidget *wdg_right;
    QVBoxLayout *verticalLayout_2;
    QStackedWidget *sw_right;
    QWidget *page_file;
    QVBoxLayout *verticalLayout_3;
    QWidget *wdg_fileTools;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pb_preDir;
    QPushButton *pb_nextDir;
    QPushButton *pb_filePath;
    QSpacerItem *horizontalSpacer;
    QPushButton *pb_search;
    QPushButton *pb_addFile;
    QTableWidget *tab_file;
    QWidget *page_transmit;
    QVBoxLayout *verticalLayout_4;
    QTabWidget *tw_transmit;
    QWidget *tab_upload;
    QVBoxLayout *verticalLayout_5;
    QTableWidget *table_upload;
    QWidget *tab_download;
    QVBoxLayout *verticalLayout_6;
    QTableWidget *table_download;
    QWidget *tab_complete;
    QVBoxLayout *verticalLayout_7;
    QTableWidget *table_complete;
    QWidget *page_share;
    QVBoxLayout *verticalLayout_8;
    QTabWidget *tw_share;
    QWidget *tab_share;
    QVBoxLayout *verticalLayout_9;
    QTableWidget *table_share;
    QGroupBox *groupBox;

    void setupUi(QDialog *MainDialog)
    {
        if (MainDialog->objectName().isEmpty())
            MainDialog->setObjectName(QString::fromUtf8("MainDialog"));
        MainDialog->resize(1000, 600);
        MainDialog->setMinimumSize(QSize(0, 0));
        MainDialog->setMaximumSize(QSize(16777215, 16777215));
        horizontalLayout = new QHBoxLayout(MainDialog);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(MainDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        wdg_left = new QWidget(widget);
        wdg_left->setObjectName(QString::fromUtf8("wdg_left"));
        wdg_left->setMinimumSize(QSize(240, 0));
        wdg_left->setMaximumSize(QSize(240, 16777215));
        wdg_left->setStyleSheet(QString::fromUtf8("background-color: rgb(214, 214, 214);"));
        verticalLayout = new QVBoxLayout(wdg_left);
        verticalLayout->setSpacing(7);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pb_fillePage = new QPushButton(wdg_left);
        pb_fillePage->setObjectName(QString::fromUtf8("pb_fillePage"));
        pb_fillePage->setMinimumSize(QSize(0, 40));
        pb_fillePage->setMaximumSize(QSize(16777215, 40));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/file.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_fillePage->setIcon(icon);
        pb_fillePage->setIconSize(QSize(40, 40));
        pb_fillePage->setFlat(true);

        verticalLayout->addWidget(pb_fillePage);

        pb_transmitPage = new QPushButton(wdg_left);
        pb_transmitPage->setObjectName(QString::fromUtf8("pb_transmitPage"));
        pb_transmitPage->setMinimumSize(QSize(0, 40));
        pb_transmitPage->setMaximumSize(QSize(16777215, 40));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/transmit.ico"), QSize(), QIcon::Normal, QIcon::Off);
        pb_transmitPage->setIcon(icon1);
        pb_transmitPage->setIconSize(QSize(40, 40));
        pb_transmitPage->setFlat(true);

        verticalLayout->addWidget(pb_transmitPage);

        pb_sharePage = new QPushButton(wdg_left);
        pb_sharePage->setObjectName(QString::fromUtf8("pb_sharePage"));
        pb_sharePage->setMinimumSize(QSize(0, 40));
        pb_sharePage->setMaximumSize(QSize(16777215, 40));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/share.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_sharePage->setIcon(icon2);
        pb_sharePage->setIconSize(QSize(40, 40));
        pb_sharePage->setFlat(true);

        verticalLayout->addWidget(pb_sharePage);

        verticalSpacer = new QSpacerItem(20, 409, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        pb_user = new QPushButton(wdg_left);
        pb_user->setObjectName(QString::fromUtf8("pb_user"));
        pb_user->setMinimumSize(QSize(0, 40));
        pb_user->setMaximumSize(QSize(16777215, 40));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/face/btn_avatar_a85.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_user->setIcon(icon3);
        pb_user->setIconSize(QSize(40, 40));
        pb_user->setFlat(true);

        verticalLayout->addWidget(pb_user);


        horizontalLayout_2->addWidget(wdg_left);

        wdg_right = new QWidget(widget);
        wdg_right->setObjectName(QString::fromUtf8("wdg_right"));
        verticalLayout_2 = new QVBoxLayout(wdg_right);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        sw_right = new QStackedWidget(wdg_right);
        sw_right->setObjectName(QString::fromUtf8("sw_right"));
        page_file = new QWidget();
        page_file->setObjectName(QString::fromUtf8("page_file"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        page_file->setFont(font);
        verticalLayout_3 = new QVBoxLayout(page_file);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        wdg_fileTools = new QWidget(page_file);
        wdg_fileTools->setObjectName(QString::fromUtf8("wdg_fileTools"));
        horizontalLayout_3 = new QHBoxLayout(wdg_fileTools);
        horizontalLayout_3->setSpacing(7);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        pb_preDir = new QPushButton(wdg_fileTools);
        pb_preDir->setObjectName(QString::fromUtf8("pb_preDir"));
        pb_preDir->setMinimumSize(QSize(20, 40));
        pb_preDir->setMaximumSize(QSize(20, 40));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(12);
        pb_preDir->setFont(font1);
        pb_preDir->setFlat(true);

        horizontalLayout_3->addWidget(pb_preDir);

        pb_nextDir = new QPushButton(wdg_fileTools);
        pb_nextDir->setObjectName(QString::fromUtf8("pb_nextDir"));
        pb_nextDir->setMinimumSize(QSize(20, 40));
        pb_nextDir->setMaximumSize(QSize(20, 40));
        pb_nextDir->setFont(font1);
        pb_nextDir->setFlat(true);

        horizontalLayout_3->addWidget(pb_nextDir);

        pb_filePath = new QPushButton(wdg_fileTools);
        pb_filePath->setObjectName(QString::fromUtf8("pb_filePath"));
        pb_filePath->setMinimumSize(QSize(80, 40));
        pb_filePath->setMaximumSize(QSize(16777215, 40));
        pb_filePath->setFont(font1);
        pb_filePath->setFlat(true);

        horizontalLayout_3->addWidget(pb_filePath);

        horizontalSpacer = new QSpacerItem(406, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        pb_search = new QPushButton(wdg_fileTools);
        pb_search->setObjectName(QString::fromUtf8("pb_search"));
        pb_search->setMinimumSize(QSize(40, 40));
        pb_search->setMaximumSize(QSize(40, 40));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/search.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_search->setIcon(icon4);
        pb_search->setIconSize(QSize(40, 40));
        pb_search->setFlat(true);

        horizontalLayout_3->addWidget(pb_search);

        pb_addFile = new QPushButton(wdg_fileTools);
        pb_addFile->setObjectName(QString::fromUtf8("pb_addFile"));
        pb_addFile->setMinimumSize(QSize(40, 40));
        pb_addFile->setMaximumSize(QSize(40, 40));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/addFile.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_addFile->setIcon(icon5);
        pb_addFile->setIconSize(QSize(40, 40));
        pb_addFile->setFlat(true);

        horizontalLayout_3->addWidget(pb_addFile);


        verticalLayout_3->addWidget(wdg_fileTools);

        tab_file = new QTableWidget(page_file);
        if (tab_file->columnCount() < 3)
            tab_file->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tab_file->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tab_file->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tab_file->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tab_file->setObjectName(QString::fromUtf8("tab_file"));
        tab_file->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tab_file->setSelectionBehavior(QAbstractItemView::SelectRows);
        tab_file->horizontalHeader()->setDefaultSectionSize(200);
        tab_file->horizontalHeader()->setStretchLastSection(true);
        tab_file->verticalHeader()->setVisible(false);

        verticalLayout_3->addWidget(tab_file);

        sw_right->addWidget(page_file);
        page_transmit = new QWidget();
        page_transmit->setObjectName(QString::fromUtf8("page_transmit"));
        verticalLayout_4 = new QVBoxLayout(page_transmit);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        tw_transmit = new QTabWidget(page_transmit);
        tw_transmit->setObjectName(QString::fromUtf8("tw_transmit"));
        tw_transmit->setFont(font1);
        tab_upload = new QWidget();
        tab_upload->setObjectName(QString::fromUtf8("tab_upload"));
        verticalLayout_5 = new QVBoxLayout(tab_upload);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        table_upload = new QTableWidget(tab_upload);
        if (table_upload->columnCount() < 4)
            table_upload->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        table_upload->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        table_upload->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        table_upload->setHorizontalHeaderItem(2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        table_upload->setHorizontalHeaderItem(3, __qtablewidgetitem6);
        table_upload->setObjectName(QString::fromUtf8("table_upload"));
        table_upload->setEditTriggers(QAbstractItemView::NoEditTriggers);
        table_upload->setSelectionBehavior(QAbstractItemView::SelectRows);
        table_upload->horizontalHeader()->setDefaultSectionSize(180);
        table_upload->horizontalHeader()->setStretchLastSection(true);
        table_upload->verticalHeader()->setVisible(false);

        verticalLayout_5->addWidget(table_upload);

        tw_transmit->addTab(tab_upload, QString());
        tab_download = new QWidget();
        tab_download->setObjectName(QString::fromUtf8("tab_download"));
        verticalLayout_6 = new QVBoxLayout(tab_download);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        table_download = new QTableWidget(tab_download);
        if (table_download->columnCount() < 4)
            table_download->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        table_download->setHorizontalHeaderItem(0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        table_download->setHorizontalHeaderItem(1, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        table_download->setHorizontalHeaderItem(2, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        table_download->setHorizontalHeaderItem(3, __qtablewidgetitem10);
        table_download->setObjectName(QString::fromUtf8("table_download"));
        table_download->setEditTriggers(QAbstractItemView::NoEditTriggers);
        table_download->setSelectionBehavior(QAbstractItemView::SelectRows);
        table_download->horizontalHeader()->setDefaultSectionSize(180);
        table_download->horizontalHeader()->setHighlightSections(true);
        table_download->horizontalHeader()->setStretchLastSection(true);
        table_download->verticalHeader()->setVisible(false);

        verticalLayout_6->addWidget(table_download);

        tw_transmit->addTab(tab_download, QString());
        tab_complete = new QWidget();
        tab_complete->setObjectName(QString::fromUtf8("tab_complete"));
        verticalLayout_7 = new QVBoxLayout(tab_complete);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        table_complete = new QTableWidget(tab_complete);
        if (table_complete->columnCount() < 4)
            table_complete->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        table_complete->setHorizontalHeaderItem(0, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        table_complete->setHorizontalHeaderItem(1, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        table_complete->setHorizontalHeaderItem(2, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        table_complete->setHorizontalHeaderItem(3, __qtablewidgetitem14);
        table_complete->setObjectName(QString::fromUtf8("table_complete"));
        table_complete->setEditTriggers(QAbstractItemView::NoEditTriggers);
        table_complete->setSelectionBehavior(QAbstractItemView::SelectRows);
        table_complete->horizontalHeader()->setDefaultSectionSize(180);
        table_complete->horizontalHeader()->setStretchLastSection(true);
        table_complete->verticalHeader()->setVisible(false);

        verticalLayout_7->addWidget(table_complete);

        tw_transmit->addTab(tab_complete, QString());

        verticalLayout_4->addWidget(tw_transmit);

        sw_right->addWidget(page_transmit);
        page_share = new QWidget();
        page_share->setObjectName(QString::fromUtf8("page_share"));
        verticalLayout_8 = new QVBoxLayout(page_share);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        tw_share = new QTabWidget(page_share);
        tw_share->setObjectName(QString::fromUtf8("tw_share"));
        tw_share->setFont(font1);
        tab_share = new QWidget();
        tab_share->setObjectName(QString::fromUtf8("tab_share"));
        verticalLayout_9 = new QVBoxLayout(tab_share);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        table_share = new QTableWidget(tab_share);
        if (table_share->columnCount() < 4)
            table_share->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        table_share->setHorizontalHeaderItem(0, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        table_share->setHorizontalHeaderItem(1, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        table_share->setHorizontalHeaderItem(2, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        table_share->setHorizontalHeaderItem(3, __qtablewidgetitem18);
        table_share->setObjectName(QString::fromUtf8("table_share"));
        table_share->setEditTriggers(QAbstractItemView::NoEditTriggers);
        table_share->setSelectionBehavior(QAbstractItemView::SelectRows);
        table_share->horizontalHeader()->setDefaultSectionSize(160);
        table_share->horizontalHeader()->setStretchLastSection(true);
        table_share->verticalHeader()->setVisible(false);

        verticalLayout_9->addWidget(table_share);

        groupBox = new QGroupBox(tab_share);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));

        verticalLayout_9->addWidget(groupBox);

        tw_share->addTab(tab_share, QString());

        verticalLayout_8->addWidget(tw_share);

        sw_right->addWidget(page_share);

        verticalLayout_2->addWidget(sw_right);


        horizontalLayout_2->addWidget(wdg_right);


        horizontalLayout->addWidget(widget);


        retranslateUi(MainDialog);

        sw_right->setCurrentIndex(1);
        tw_transmit->setCurrentIndex(1);
        tw_share->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainDialog);
    } // setupUi

    void retranslateUi(QDialog *MainDialog)
    {
        MainDialog->setWindowTitle(QApplication::translate("MainDialog", "MainDialog", nullptr));
        pb_fillePage->setText(QApplication::translate("MainDialog", "\346\226\207\344\273\266", nullptr));
        pb_transmitPage->setText(QApplication::translate("MainDialog", "\344\274\240\350\276\223", nullptr));
        pb_sharePage->setText(QApplication::translate("MainDialog", "\345\205\261\344\272\253", nullptr));
        pb_user->setText(QApplication::translate("MainDialog", "\346\210\221\347\232\204\345\220\215\345\255\227", nullptr));
        pb_preDir->setText(QApplication::translate("MainDialog", "<", nullptr));
        pb_nextDir->setText(QApplication::translate("MainDialog", ">", nullptr));
        pb_filePath->setText(QApplication::translate("MainDialog", "/", nullptr));
        pb_search->setText(QString());
        pb_addFile->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = tab_file->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainDialog", "\346\226\207\344\273\266", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tab_file->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainDialog", "\344\270\212\344\274\240\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tab_file->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainDialog", "\345\244\247\345\260\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = table_upload->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("MainDialog", "\346\226\207\344\273\266", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = table_upload->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QApplication::translate("MainDialog", "\345\244\247\345\260\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = table_upload->horizontalHeaderItem(2);
        ___qtablewidgetitem5->setText(QApplication::translate("MainDialog", "\350\277\233\345\272\246", nullptr));
        tw_transmit->setTabText(tw_transmit->indexOf(tab_upload), QApplication::translate("MainDialog", "\344\270\212\344\274\240", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = table_download->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QApplication::translate("MainDialog", "\346\226\207\344\273\266", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = table_download->horizontalHeaderItem(1);
        ___qtablewidgetitem7->setText(QApplication::translate("MainDialog", "\345\244\247\345\260\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = table_download->horizontalHeaderItem(2);
        ___qtablewidgetitem8->setText(QApplication::translate("MainDialog", "\350\277\233\345\272\246", nullptr));
        tw_transmit->setTabText(tw_transmit->indexOf(tab_download), QApplication::translate("MainDialog", " \344\270\213\350\275\275", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = table_complete->horizontalHeaderItem(0);
        ___qtablewidgetitem9->setText(QApplication::translate("MainDialog", "\346\226\207\344\273\266", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = table_complete->horizontalHeaderItem(1);
        ___qtablewidgetitem10->setText(QApplication::translate("MainDialog", "\345\244\247\345\260\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = table_complete->horizontalHeaderItem(2);
        ___qtablewidgetitem11->setText(QApplication::translate("MainDialog", "\346\227\266\351\227\264", nullptr));
        tw_transmit->setTabText(tw_transmit->indexOf(tab_complete), QApplication::translate("MainDialog", "\345\267\262\345\256\214\346\210\220", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = table_share->horizontalHeaderItem(0);
        ___qtablewidgetitem12->setText(QApplication::translate("MainDialog", "\346\226\207\344\273\266", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = table_share->horizontalHeaderItem(1);
        ___qtablewidgetitem13->setText(QApplication::translate("MainDialog", "\345\244\247\345\260\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = table_share->horizontalHeaderItem(2);
        ___qtablewidgetitem14->setText(QApplication::translate("MainDialog", "\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = table_share->horizontalHeaderItem(3);
        ___qtablewidgetitem15->setText(QApplication::translate("MainDialog", "\345\210\206\344\272\253\347\240\201", nullptr));
        groupBox->setTitle(QApplication::translate("MainDialog", "GroupBox", nullptr));
        tw_share->setTabText(tw_share->indexOf(tab_share), QApplication::translate("MainDialog", "\346\210\221\347\232\204\345\205\261\344\272\253", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainDialog: public Ui_MainDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINDIALOG_H
