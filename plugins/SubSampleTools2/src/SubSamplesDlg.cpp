#include "SubSamplesDlg.h"
#include <QFileDialog>
#include <iostream>
#include <QtGui>
#include <QApplication>
#include <QProgressDialog>
#include <QMainWindow>
#include <ccPointCloud.h>
#include <exception>
#include <BinFilter.h>
#include <QComboBox>
#include <QDir>
#include <QFileInfo>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QByteArray>
#include <QMap>
#include <QVector>
#include <string>
#include <AsciiFilter.h>
#include <CloudSamplingTools.h>
#include <DistanceComputationTools.h>
#include <Garbage.h>
#include <GenericProgressCallback.h>
#include <GeometricalAnalysisTools.h>
#include <Jacobi.h>
#include <KdTree.h>
#include <ManualSegmentationTools.h>
#include <NormalDistribution.h>
#include <ParallelSort.h>
#include <PointCloud.h>
#include <ReferenceCloud.h>
#include <ScalarFieldTools.h>
#include <ccHObjectCaster.h>
#include <QProgressDialog>
#include <QRegularExpression>
#include <QProgressBar>

using namespace CCCoreLib;

SubSamplesDlg::SubSamplesDlg(ccMainAppInterface* m_appp, QWidget *parent): QDialog(parent){
	this_parent = parent;
	m_app = m_appp;
	setupUi(this);
	/*connect(selectionBtn, SIGNAL(clicked()), this, SLOT(on_selectionBtn_clicked()));
	connect(OkBtn, SIGNAL(clicked()), this, SLOT(on_OkBtn_clicked()));
	connect(CancelBtn, SIGNAL(clicked()), this, SLOT(on_CancelBtn_clicked()));*/
}

SubSamplesDlg::SubSamplesDlg(ccMainAppInterface* m_appp, ccHObject::Container* selected_objss, QWidget  *parent): QDialog(parent) {
	selected_objs = selected_objss;
	this_parent = parent;
	m_app = m_appp;
	setupUi(this);
}

void SubSamplesDlg::setupUi(QDialog *Dialog){
	if (Dialog->objectName().isEmpty())
		Dialog->setObjectName(QString::fromUtf8("SubSampleTool"));
	Dialog->resize(602, 228);
	Dialog->setFocusPolicy(Qt::TabFocus);
	verticalLayoutWidget = new QWidget(Dialog);
	verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
	verticalLayoutWidget->setGeometry(QRect(20, 10, 563, 201));
	verticalLayout = new QVBoxLayout(verticalLayoutWidget);
	verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
	verticalLayout->setContentsMargins(0, 0, 0, 0);
	label = new QLabel(verticalLayoutWidget);
	label->setObjectName(QString::fromUtf8("label"));

	verticalLayout->addWidget(label);

	horizontalLayout = new QHBoxLayout();
	horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
	label_2 = new QLabel(verticalLayoutWidget);
	label_2->setObjectName(QString::fromUtf8("label_2"));

	horizontalLayout->addWidget(label_2);

	pathEdit = new QLineEdit(verticalLayoutWidget);
	pathEdit->setObjectName(QString::fromUtf8("pathEdit"));

	horizontalLayout->addWidget(pathEdit);

	selectionBtn = new QPushButton(verticalLayoutWidget);
	selectionBtn->setObjectName(QString::fromUtf8("selectionBtn"));

	horizontalLayout->addWidget(selectionBtn);


	verticalLayout->addLayout(horizontalLayout);

	horizontalLayout_5 = new QHBoxLayout();
	horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
	horizontalLayout_4 = new QHBoxLayout();
	horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
	label_4 = new QLabel(verticalLayoutWidget);
	label_4->setObjectName(QString::fromUtf8("label_4"));

	horizontalLayout_4->addWidget(label_4);

	SubSamplePointNumCbx = new QComboBox(verticalLayoutWidget);
	SubSamplePointNumCbx->setObjectName(QString::fromUtf8("SubSamplePointNumCbx"));
	SubSamplePointNumCbx->setEditable(true);

	horizontalLayout_4->addWidget(SubSamplePointNumCbx);

	horizontalLayout_3 = new QHBoxLayout();
	horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
	label_3 = new QLabel(verticalLayoutWidget);
	label_3->setObjectName(QString::fromUtf8("label_3"));

	horizontalLayout_3->addWidget(label_3);

	SlelectedFileNumber = new QLabel(verticalLayoutWidget);
	SlelectedFileNumber->setObjectName(QString::fromUtf8("SlelectedFileNumber"));
	SlelectedFileNumber->setMinimumSize(QSize(70, 0));

	horizontalLayout_3->addWidget(SlelectedFileNumber);


	horizontalLayout_4->addLayout(horizontalLayout_3);


	horizontalLayout_5->addLayout(horizontalLayout_4);


	verticalLayout->addLayout(horizontalLayout_5);

	horizontalLayout_6 = new QHBoxLayout();
	horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
	checkBox_LoadDlg = new QCheckBox(verticalLayoutWidget);
	checkBox_LoadDlg->setObjectName(QString::fromUtf8("checkBox_LoadDlg"));

	horizontalLayout_6->addWidget(checkBox_LoadDlg);

	checkBox_SaveDlg = new QCheckBox(verticalLayoutWidget);
	checkBox_SaveDlg->setObjectName(QString::fromUtf8("checkBox_SaveDlg"));

	horizontalLayout_6->addWidget(checkBox_SaveDlg);

	horizontalLayout_2 = new QHBoxLayout();
	horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
	OkBtn = new QPushButton(verticalLayoutWidget);
	OkBtn->setObjectName(QString::fromUtf8("OkBtn"));

	horizontalLayout_2->addWidget(OkBtn);

	CancelBtn = new QPushButton(verticalLayoutWidget);
	CancelBtn->setObjectName(QString::fromUtf8("CancelBtn"));

	horizontalLayout_2->addWidget(CancelBtn);


	horizontalLayout_6->addLayout(horizontalLayout_2);


	verticalLayout->addLayout(horizontalLayout_6);

	progressBar = new QProgressBar(verticalLayoutWidget);
	progressBar->setObjectName(QString::fromUtf8("progressBar"));
	progressBar->setValue(0);

	verticalLayout->addWidget(progressBar);

	label_5 = new QLabel(verticalLayoutWidget);
	label_5->setObjectName(QString::fromUtf8("label_5"));

	verticalLayout->addWidget(label_5);

	pathEdit->setText("D:/HJ/test");

	SlelectedFileNumber->setVisible(true);
	SlelectedFileNumber->setEnabled(true);

	SubSamplePointNumCbx->addItem(tr("1024"));
	SubSamplePointNumCbx->addItem(tr("2048"));
	SubSamplePointNumCbx->addItem(tr("4096"));

	retranslateUi(Dialog);
	QMetaObject::connectSlotsByName(Dialog);
} // setupUi

void SubSamplesDlg::retranslateUi(QDialog *Dialog){
	Dialog->setWindowTitle(QApplication::translate("Dialog", "SubSampleTool", nullptr));
	label->setText(QApplication::translate("Dialog", "\347\202\271\344\272\221\344\270\213\351\207\207\346\240\267\357\274\210\347\233\256\345\211\215\345\217\252\346\224\257\346\214\201.txt\346\226\207\344\273\266\357\274\211", nullptr));
	label_2->setText(QApplication::translate("Dialog", "\346\272\220\346\226\207\344\273\266\345\244\271\357\274\232", nullptr));
	selectionBtn->setText(QApplication::translate("Dialog", "\351\200\211\346\213\251\346\226\207\344\273\266\345\244\271...", nullptr));
	label_4->setText(QApplication::translate("Dialog", "\344\270\213\351\207\207\346\240\267\344\277\235\347\225\231\347\202\271\346\225\260\357\274\232", nullptr));
	SubSamplePointNumCbx->setCurrentText(QApplication::translate("Dialog", "1024", nullptr));
	label_3->setText(QApplication::translate("Dialog", "\351\200\211\344\270\255\346\226\207\344\273\266\346\225\260\357\274\232", nullptr));
	SlelectedFileNumber->setText(QApplication::translate("SubSamplesDlg", "\346\210\221\346\232\202\346\227\266\345\256\236\347\216\260\344\270\215\344\272\206", nullptr));
	checkBox_LoadDlg->setText(QApplication::translate("Dialog", "\346\230\276\347\244\272\346\211\223\345\274\200\345\257\271\350\257\235\346\241\206", nullptr));
	checkBox_SaveDlg->setText(QApplication::translate("Dialog", "\346\230\276\347\244\272\344\277\235\345\255\230\345\257\271\350\257\235\346\241\206", nullptr));
	OkBtn->setText(QApplication::translate("Dialog", "\347\241\256\345\256\232", nullptr));
	CancelBtn->setText(QApplication::translate("Dialog", "\345\217\226\346\266\210", nullptr));
	label_5->setText(QApplication::translate("Dialog", "\350\257\264\346\230\216\357\274\232\350\276\223\345\207\272\347\232\204\346\226\207\344\273\266\344\277\235\345\255\230\345\234\250\346\272\220\346\226\207\344\273\266\345\220\214\347\272\247\347\233\256\345\275\225\357\274\214TXT\346\240\274\345\274\217\343\200\202", nullptr));
} // retranslateUi

void SubSamplesDlg::on_selectionBtn_clicked(){
	QString srcDirPath = QFileDialog::getExistingDirectory(this, "选择文件夹", "D:/HJ/test");
	if (srcDirPath.length()>0) {
		pathEdit->setText(srcDirPath);
	}
	//选择文件夹。。。。。。
}

// 遍历给定目录下所有子目录，查找*.txt，放入CStringArray中
unsigned int SubSamplesDlg::getFolderTxtFile(QString pathStr, QStringList& Filelist){
	QVector<QString> *folderList = new QVector<QString>;
	GetAllFileFolder(pathStr, *folderList);
	QString folder;
	for (unsigned int i=0;i < folderList->size();i++) {
		folder = folderList->at(i);
		//m_app->dispToConsole(folder, ccMainAppInterface::STD_CONSOLE_MESSAGE);
		Filelist.append(getFileNames(folder));
	}
	return Filelist.count();
}

void SubSamplesDlg::on_CancelBtn_clicked(){
	isCanceled = true;
	this->close();
	//取消
}

void SubSamplesDlg::GetAllFileFolder(QString dirPath, QVector<QString> &folderList){
	QDir dir(dirPath);
	folderList.push_back(dirPath);
	dir.setFilter(QDir::Dirs);
	foreach(QFileInfo fullDir, dir.entryInfoList(QDir::Dirs)){
		if (fullDir.fileName() == "." || fullDir.fileName() == "..") 
			continue;
		folderList.push_back(fullDir.absoluteFilePath());
		GetAllFileFolder(fullDir.absoluteFilePath(), folderList);
	}
	return;
}
QStringList SubSamplesDlg::getFileNames(const QString &path){
	QDir dir(path);
	QStringList *list = new QStringList();
	QStringList filter;
	filter << "*.txt";
	QStringList files = dir.entryList(filter, QDir::Files);
	QString pa = path;
	for (unsigned int i = 0; i < files.size(); i++) {
		if (!pa.contains(".txt")) {
			pa.append("/");
			pa.append(files.at(i));
		}
		list->push_back(pa);
		pa = path;
	}
	return *list;
}

// 原先方法：
void SubSamplesDlg::on_OkBtn_clicked() {
	QString path = pathEdit->text();
	QStringList *txtFiles = new QStringList();
	unsigned int txtNum = getFolderTxtFile(path, *txtFiles);
	*txtFiles = txtFiles->toSet().toList();
	
	for (unsigned int i = 0; i < txtFiles->length(); i++) {
		if (txtFiles->at(i).contains("+")) {
			txtFiles->removeAt(i);
			i--;
		}
	}

	QString txtfile;
	AsciiFilter::SaveParameters savep;
	savep.alwaysDisplaySaveDialog = checkBox_SaveDlg->isChecked();
	AsciiFilter loadf;
	FileIOFilter::LoadParameters loadp;
	loadp.alwaysDisplayLoadDialog = checkBox_LoadDlg->isChecked();
	loadp.shiftHandlingMode = ccGlobalShiftManager::NO_DIALOG;
	loadp.autoComputeNormals = false;
	loadp.parentWidget = m_app->getMainWindow();
	loadp.sessionStart = true;
	CC_FILE_ERROR res;
	//m_app->dispToConsole("over", ccMainAppInterface::STD_CONSOLE_MESSAGE);
	
	QString PointNum = SubSamplePointNumCbx->currentText();
	if (!isInteger(PointNum)) { return; }
	long IntegerPointNum = PointNum.toLong();
	unsigned count = static_cast<unsigned>(IntegerPointNum);
	QRegularExpression *reFileName = new QRegularExpression();
	QRegularExpression *rePath = new QRegularExpression();

	reFileName->setPattern("([^<>/\\\\\\|:\"\"\\*\\?]+)\\.\\w+$");
	rePath->setPattern("^[a-zA-Z]:(/[\\w\\s]+)+/");
	//SlelectedFileNumber->setText(QString(txtFiles->length()));
	progressBar->setRange(0, txtFiles->length());
	progressBar->setValue(0);
	progressBar->setValue(true);
	progressBar->show();
	progressBar->setEnabled(true);
	isCanceled = false;
	for (unsigned int j = 0; j < txtFiles->length(); j++) {
		if (isCanceled) {
			break;
		}
		progressBar->setValue(j+1);
		txtfile = txtFiles->at(j);
		QRegularExpressionMatch matchFileName = reFileName->match(txtfile);
		QRegularExpressionMatch matchPath = rePath->match(txtfile);
		QString filename = matchFileName.captured(0);
		QString filePath = matchPath.captured(0);
		QString *txtfileSave = new QString(filePath);

		if(txtfileSave->at(txtfileSave->size()-1)!="/"){
			txtfileSave->append("/");
		}
		txtfileSave->append(PointNum);
		txtfileSave->append("+/");
		QDir txtfileSavedir(*txtfileSave);
		if (!txtfileSavedir.exists()) {
			txtfileSavedir.mkdir(*txtfileSave);
		}
		txtfileSave->append(filename);
		ccHObject *loadedObj = FileIOFilter::LoadFromFile(txtfile, loadp, res, AsciiFilter::GetFileFilter());
		if (res == CC_FERR_NO_ERROR) {
			//m_app->addToDB(loadedObj);
			ccHObject::Container clouds;
			loadedObj->filterChildren(clouds, true, CC_TYPES::POINT_CLOUD);
			ccPointCloud* cloud = static_cast<ccPointCloud*>(clouds[0]);
			//ccPointCloud* pcSubsampled = new ccPointCloud("pcSubsampled");
			if (!cloud || cloud->size() <= 0) {
				ccLog::Warning("[ccSubsamplingDlg::getSampledCloud] Invalid input cloud!");
				return;
			}
			/*unsigned count = static_cast<unsigned>(IntegerPointNum);*/
			CCCoreLib::ReferenceCloud* SubsampledEnt = CCCoreLib::CloudSamplingTools::subsampleCloudRandomly(cloud, count);
			int warnings = 0;
			ccPointCloud *pcSubsampled = cloud->partialClone(SubsampledEnt, &warnings);
			pcSubsampled->setName(QString("pcSubsampled"));
			pcSubsampled->copyGlobalShiftAndScale(*cloud);
			//保存
			loadf.saveToFile(pcSubsampled, *txtfileSave, savep);
			m_app->dispToConsole(QString("Saved file: %1").arg(*txtfileSave), ccMainAppInterface::STD_CONSOLE_MESSAGE);
			free(loadedObj); loadedObj = 0;
			free(cloud); cloud = 0;
			free(pcSubsampled); pcSubsampled = 0;
			free(SubsampledEnt); SubsampledEnt = 0;
		}
		else {
			ccLog::Error(QString("Failed to load file: %1, Error # = %2").arg(txtfile).arg(res));
			continue;
		}
	}
	//this->close();
	//确定
}

void SubSamplesDlg::on_pathEdit_textChanged(const QString &arg1) {
	/*QString path = pathEdit->text();
	QStringList *txtFiles = new QStringList();
	unsigned int txtNum = getFolderTxtFile(arg1, *txtFiles);*/
	
	//SlelectedFileNumber->setText(QString("实现不了"));
	;
}

bool SubSamplesDlg::isInteger(const QString &str){
	for (unsigned int i=0;i < str.length();i++) {
		if (!str.at(i).isDigit() || str.at(i)==".") {
			return false;
		}
	}
	if(str.toLong()<=0){ return false; }
	return true;
}