#pragma once

//#ifndef CCSAFDLG_H
//#define CCSAFDLG_H
#include <QDialog>
#include "ccStdPluginInterface.h"
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <QtGui>
#include <QApplication>
#include <QProgressDialog>
#include <QMainWindow>
#include <string>
#include <QComboBox>
#include <QCheckBox>
#include <QProgressBar>

//#include <afx.h>
//#include <afxcoll.h>

namespace Ui {
	class SubSamplesDlg;
}

class SubSamplesDlg :public QDialog { //public QDialog , 
	Q_OBJECT
public:
	explicit SubSamplesDlg(ccMainAppInterface* m_appp, QWidget  *parent = 0);
	explicit SubSamplesDlg(ccMainAppInterface* m_appp, ccHObject::Container* selected_objs, QWidget *parent = 0);
	QWidget *verticalLayoutWidget;
	QVBoxLayout *verticalLayout;
	QLabel *label;
	QHBoxLayout *horizontalLayout;
	QLabel *label_2;
	QLineEdit *pathEdit;
	QPushButton *selectionBtn;
	QHBoxLayout *horizontalLayout_5;
	QHBoxLayout *horizontalLayout_4;
	QLabel *label_4;
	QComboBox *SubSamplePointNumCbx;
	QHBoxLayout *horizontalLayout_3;
	QLabel *label_3;
	QLabel *SlelectedFileNumber;
	QHBoxLayout *horizontalLayout_6;
	QCheckBox *checkBox_LoadDlg;
	QCheckBox *checkBox_SaveDlg;
	QHBoxLayout *horizontalLayout_2;
	QPushButton *OkBtn;
	QPushButton *CancelBtn;
	QProgressBar *progressBar;
	QLabel *label_5;

	void setupUi(QDialog *Dialog);
	void retranslateUi(QDialog *Dialog);
	unsigned int SubSamplesDlg::getFolderTxtFile(QString pathStr, QStringList& Filelist);
	void GetAllFileFolder(QString dirPath, QVector<QString> &folderList);
	QStringList getFileNames(const QString &path);
	bool SubSamplesDlg::isInteger(const QString &str);

public slots:
	void on_selectionBtn_clicked();
	void on_OkBtn_clicked();
	void on_CancelBtn_clicked();
	void on_pathEdit_textChanged(const QString &arg1);
private:
	/*Ui::SubSamplesDlg *ui;*/
	SubSamplesDlg *ui;
	QWidget *this_parent;
	ccMainAppInterface* m_app;
	ccHObject::Container* selected_objs;
	bool isCanceled;
};

//#endif