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

//#include <afx.h>
//#include <afxcoll.h>

namespace Ui {
	class SubSamplesDlg;
}

class SubSamplesDlg :public QDialog { //public QDialog , 
	Q_OBJECT
public:
	//explicit SubSamplesDlg(ccMainAppInterface* m_appp, QWidget  *parent = 0);
	explicit SubSamplesDlg(ccMainAppInterface* m_appp, ccHObject::Container* selected_objs, QWidget *parent = 0);
	QLabel *label;
	QWidget *horizontalLayoutWidget_2;
	QHBoxLayout *horizontalLayout_2;
	QPushButton *OkBtn;
	QPushButton *CancelBtn;
	QWidget *horizontalLayoutWidget;
	QHBoxLayout *horizontalLayout;
	QLabel *label_2;
	QLineEdit *pathEdit;
	QPushButton *selectionBtn;

	void setupUi(QDialog *Dialog);
	void retranslateUi(QDialog *Dialog);
	unsigned int SubSamplesDlg::getFolderTxtFile(QString pathStr, QStringList& Filelist);
	void GetAllFileFolder(QString dirPath, QVector<QString> &folderList);
	QStringList getFileNames(const QString &path);

public slots:
	void on_selectionBtn_clicked();
	void on_OkBtn_clicked();
	void on_CancelBtn_clicked();
private:
	/*Ui::SubSamplesDlg *ui;*/
	SubSamplesDlg *ui;
	QWidget *this_parent;
	ccMainAppInterface* m_app;
	ccHObject::Container* selected_objs;
};

//#endif