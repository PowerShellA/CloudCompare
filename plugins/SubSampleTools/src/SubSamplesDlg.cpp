#include "SubSamplesDlg.h"
#include <string>
#include <QFileDialog>
#include <iostream>
#include <QtGui>
#include <QApplication>
#include <QProgressDialog>
#include <QMainWindow>
#include <ccPointCloud.h>
#include <exception>
#include <BinFilter.h>

#include <QDir>
#include <QFileInfo>
#include <iostream>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QDebug>
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

//#include <afx.h>
//#include <afxcoll.h>

using namespace CCCoreLib;
using namespace std;

//SubSamplesDlg::SubSamplesDlg(ccMainAppInterface* m_appp, QWidget *parent=0): QDialog(parent){
//	this_parent = parent;
//	m_app = m_appp;
//	setupUi(this);
//	/*connect(selectionBtn, SIGNAL(clicked()), this, SLOT(on_selectionBtn_clicked()));
//	connect(OkBtn, SIGNAL(clicked()), this, SLOT(on_OkBtn_clicked()));
//	connect(CancelBtn, SIGNAL(clicked()), this, SLOT(on_CancelBtn_clicked()));*/
//}

SubSamplesDlg::SubSamplesDlg(ccMainAppInterface *m_appp, ccHObject::Container *selected_objss, QWidget *parent) : QDialog(parent)
{
    selected_objs = selected_objss;
    this_parent = parent;
    m_app = m_appp;
    setupUi(this);
    //SubSamplesDlg(m_appp, parent);
}

void SubSamplesDlg::setupUi(QDialog *Dialog)
{
    if (Dialog->objectName().isEmpty())
        Dialog->setObjectName(QStringLiteral("Dialog"));
    Dialog->resize(618, 96);
    label = new QLabel(Dialog);
    label->setObjectName(QStringLiteral("label"));
    label->setGeometry(QRect(10, 0, 191, 16));
    horizontalLayoutWidget_2 = new QWidget(Dialog);
    horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
    horizontalLayoutWidget_2->setGeometry(QRect(450, 60, 160, 31));
    horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
    horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
    horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
    OkBtn = new QPushButton(horizontalLayoutWidget_2);
    OkBtn->setObjectName(QStringLiteral("OkBtn"));
    horizontalLayout_2->addWidget(OkBtn);
    CancelBtn = new QPushButton(horizontalLayoutWidget_2);
    CancelBtn->setObjectName(QStringLiteral("CancelBtn"));
    horizontalLayout_2->addWidget(CancelBtn);
    horizontalLayoutWidget = new QWidget(Dialog);
    horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
    horizontalLayoutWidget->setGeometry(QRect(10, 20, 601, 31));
    horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
    horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
    horizontalLayout->setContentsMargins(0, 0, 0, 0);
    label_2 = new QLabel(horizontalLayoutWidget);
    label_2->setObjectName(QStringLiteral("label_2"));
    horizontalLayout->addWidget(label_2);
    pathEdit = new QLineEdit(horizontalLayoutWidget);
    pathEdit->setObjectName(QStringLiteral("pathEdit"));
    horizontalLayout->addWidget(pathEdit);
    selectionBtn = new QPushButton(horizontalLayoutWidget);
    selectionBtn->setObjectName(QStringLiteral("selectionBtn"));
    horizontalLayout->addWidget(selectionBtn);
    retranslateUi(Dialog);
    pathEdit->setText("D:/HJ/test");
    QMetaObject::connectSlotsByName(Dialog);
} // setupUi

void SubSamplesDlg::retranslateUi(QDialog *Dialog)
{
    Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", Q_NULLPTR));
    label->setText(QApplication::translate("Dialog", "\347\202\271\344\272\221\344\270\213\351\207\207\346\240\267\357\274\210\347\233\256\345\211\215\345\217\252\346\224\257\346\214\201.txt\346\226\207\344\273\266\357\274\211", Q_NULLPTR));
    OkBtn->setText(QApplication::translate("Dialog", "\347\241\256\345\256\232", Q_NULLPTR));
    CancelBtn->setText(QApplication::translate("Dialog", "\345\217\226\346\266\210", Q_NULLPTR));
    label_2->setText(QApplication::translate("Dialog", "\351\200\211\346\213\251\346\226\207\344\273\266\345\244\271\357\274\232", Q_NULLPTR));
    selectionBtn->setText(QApplication::translate("Dialog", "\351\200\211\346\213\251\346\226\207\344\273\266\345\244\271...", Q_NULLPTR));
} // retranslateUi

void SubSamplesDlg::on_selectionBtn_clicked()
{

    QString srcDirPath = QFileDialog::getExistingDirectory(this, "选择文件夹", "D:/GraduationProject/repos/modelnet40_normal_resampled");
    if (srcDirPath.length() > 0)
    {
        pathEdit->setText(srcDirPath);
    }
    //选择文件夹。。。。。。
}

void SubSamplesDlg::on_OkBtn_clicked()
{
    cout << pathEdit->text().toStdString();
    QString path = pathEdit->text();

    AsciiFilter loadf;
    AsciiFilter::SaveParameters savep;
    savep.alwaysDisplaySaveDialog = false;
    savep.parentWidget = this;

    for (unsigned int j = 0; j < selected_objs->size() / 2; j++)
    {
        ccHObject *ent = (*selected_objs)[j];
        QString *txtfile = new QString(path);
        if (txtfile->at(txtfile->size() - 1) != "/")
        {
            txtfile->append("/");
        }

        QString *txtfileSave2048 = new QString(*txtfile);
        QString *txtfileSave4096 = new QString(*txtfile);
        txtfileSave2048->append("2048/");
        txtfileSave4096->append("4096/");
        QDir txtfileSave2048dir(*txtfileSave2048);
        QDir txtfileSave4096dir(*txtfileSave4096);
        if (!txtfileSave2048dir.exists())
        {
            txtfileSave2048dir.mkdir(*txtfileSave2048);
        }
        if (!txtfileSave4096dir.exists())
        {
            txtfileSave4096dir.mkdir(*txtfileSave4096);
        }

        txtfileSave2048->append(selected_objs->at(j)->getName());
        txtfileSave4096->append(selected_objs->at(j)->getName());
        //txtfile->append(selected_objs->at(j)->getName());
        //m_app->dispToConsole(txtfile, ccMainAppInterface::STD_CONSOLE_MESSAGE);

        txtfileSave2048->append(".2048.txt");
        txtfileSave4096->append(".4096.txt");
        m_app->dispToConsole(*txtfileSave2048, ccMainAppInterface::STD_CONSOLE_MESSAGE);
        m_app->dispToConsole(*txtfileSave4096, ccMainAppInterface::STD_CONSOLE_MESSAGE);
        //m_app->dispToConsole(*txtfile, ccMainAppInterface::STD_CONSOLE_MESSAGE);
        //m_app->dispToConsole("Next", ccMainAppInterface::STD_CONSOLE_MESSAGE);

        //assert(ent);

        if (ent)
        {
            //m_app->dispToConsole("ININININININININI", ccMainAppInterface::STD_CONSOLE_MESSAGE);
            ccPointCloud *pc = static_cast<ccPointCloud *>(ent);
            ccPointCloud *pc4096 = new ccPointCloud("pc4096");
            ccPointCloud *pc2048 = new ccPointCloud("pc2048");
            ReferenceCloud *entss4096 = CloudSamplingTools::subsampleCloudRandomly(pc, (unsigned int)4096);
            ReferenceCloud *entss2048 = CloudSamplingTools::subsampleCloudRandomly(pc, (unsigned int)2048);

            for (unsigned int i = 0; i < entss4096->size(); i++)
            {
                pc4096->addPoint(CCVector3(entss4096->getPoint(i)->x, entss4096->getPoint(i)->y, entss4096->getPoint(i)->z));
            }
            for (unsigned int i = 0; i < entss2048->size(); i++)
            {
                pc2048->addPoint(CCVector3(entss2048->getPoint(i)->x, entss2048->getPoint(i)->y, entss2048->getPoint(i)->z));
            }
            //保存
            loadf.saveToFile(pc4096, *txtfileSave4096, savep);
            m_app->dispToConsole("save4096", ccMainAppInterface::STD_CONSOLE_MESSAGE);
            loadf.saveToFile(pc2048, *txtfileSave2048, savep);
            m_app->dispToConsole("save2048", ccMainAppInterface::STD_CONSOLE_MESSAGE);
        }
        else
        {
            m_app->dispToConsole("faillllllllllllllllllllll", ccMainAppInterface::STD_CONSOLE_MESSAGE);
        }
        //delete
    }
    this->close();
    //确定
}

// 遍历给定目录下所有子目录，查找*.txt，放入CStringArray中
unsigned int SubSamplesDlg::getFolderTxtFile(QString pathStr, QStringList &Filelist)
{
    QVector<QString> *folderList = new QVector<QString>;
    GetAllFileFolder(pathStr, *folderList);
    QString folder;
    for (unsigned int i = 0; i < folderList->size(); i++)
    {
        folder = folderList->at(i);
        //m_app->dispToConsole(folder, ccMainAppInterface::STD_CONSOLE_MESSAGE);
        Filelist.append(getFileNames(folder));
    }
    //Filelist.append(getFileNames(folder));
    return Filelist.count();
}

void SubSamplesDlg::on_CancelBtn_clicked()
{
    this->close();
    //取消
}

void SubSamplesDlg::GetAllFileFolder(QString dirPath, QVector<QString> &folderList)
{
    QDir dir(dirPath);
    folderList.push_back(dirPath);
    dir.setFilter(QDir::Dirs);
    foreach (QFileInfo fullDir, dir.entryInfoList(QDir::Dirs))
    {
        if (fullDir.fileName() == "." || fullDir.fileName() == "..")
            continue;
        folderList.push_back(fullDir.absoluteFilePath());
        GetAllFileFolder(fullDir.absoluteFilePath(), folderList);
    }
    //GetAllFileFolder(dirPath, folderList);
    return;
}
QStringList SubSamplesDlg::getFileNames(const QString &path)
{
    QDir dir(path);
    QStringList *list = new QStringList();
    QStringList filter;
    filter << "*.txt";
    QStringList files = dir.entryList(filter, QDir::Files);
    QString pa = path;
    for (unsigned int i = 0; i < files.size(); i++)
    {
        if (!pa.contains(".txt"))
        {
            pa.append("/");
            pa.append(files.at(i));
        }

        list->push_back(pa);
        pa = path;
        //list->push_back(files.at(i));
    }

    //dir.entryInfoList();
    //QString pa = path.append(files);
    //list->append(files);
    return *list;
}

// 原先方法：
//void SubSamplesDlg::on_OkBtn_clicked() {
//	cout << pathEdit->text().toStdString();
//	QString path = pathEdit->text();
//	//CStringArray *txtFiles = new CStringArray;
//	QStringList *txtFiles = new QStringList();
//	unsigned int txtNum = getFolderTxtFile(path, *txtFiles);
//	*txtFiles = txtFiles->toSet().toList();
//
//	QString txtfile;
//	QString txt = "";
//
//	AsciiFilter* loadf = new AsciiFilter();
//	AsciiFilter::LoadParameters loadp;
//	AsciiFilter::SaveParameters savep;
//	loadp.alwaysDisplayLoadDialog = true;
//	loadp.shiftHandlingMode = ccGlobalShiftManager::DIALOG_IF_NECESSARY;
//	loadp.autoComputeNormals = false;
//	loadp.parentWidget = this;
//	loadp.sessionStart = true;
//	loadp.coordinatesShiftEnabled = false;
//	CCVector3d loadCoordinatesShift(0, 0, 0);
//	loadp.coordinatesShift = &loadCoordinatesShift;
//
//	savep.alwaysDisplaySaveDialog = false;
//	CC_FILE_ERROR err = CC_FERR_NO_ERROR;
//
//	m_app->dispToConsole("over", ccMainAppInterface::STD_CONSOLE_MESSAGE);
//	//m_app->dispToConsole("遍历完", ccMainAppInterface::STD_CONSOLE_MESSAGE);
//	//QProgressBar *m_pConnectProBar = new QProgressBar(this_parent,0);
//
//	for (unsigned int j = 0; j < 1; j++) {
//		txtfile = txtFiles->at(j);
//		//m_app->dispToConsole(txtfile, ccMainAppInterface::STD_CONSOLE_MESSAGE);
//		QString *txtfileSave2048 = new QString(txtfile);
//		QString *txtfileSave4096 = new QString(txtfile);
//
//		txtfileSave2048->append(".2048.txt");
//		txtfileSave4096->append(".4096.txt");
//		m_app->dispToConsole(*txtfileSave2048, ccMainAppInterface::STD_CONSOLE_MESSAGE);
//		m_app->dispToConsole(*txtfileSave4096, ccMainAppInterface::STD_CONSOLE_MESSAGE);
//		m_app->dispToConsole(txtfile, ccMainAppInterface::STD_CONSOLE_MESSAGE);
//		m_app->dispToConsole("Next", ccMainAppInterface::STD_CONSOLE_MESSAGE);
//
//		//ccHObject* ent = loadf->LoadFromFile(txtfile, loadp, err, txt);
//		ccHObject* ent;
//		try {
//			ent = FileIOFilter::LoadFromFile(txtfile, loadp, err, QString());
//		}
//		catch (exception& e) {
//			m_app->dispToConsole(QString(e.what()), ccMainAppInterface::STD_CONSOLE_MESSAGE);
//		}
//
//		assert(ent);
//
//		if (ent && !err) {
//			m_app->dispToConsole("ININININININININI", ccMainAppInterface::STD_CONSOLE_MESSAGE);
//			ccPointCloud* pc = static_cast<ccPointCloud*>(ent);
//			ccPointCloud* pc4096 = new ccPointCloud("pc4096");
//			ccPointCloud* pc2048 = new ccPointCloud("pc2048");
//			ReferenceCloud* entss4096 = CloudSamplingTools::subsampleCloudRandomly(pc, (unsigned int)4096);
//			ReferenceCloud* entss2048 = CloudSamplingTools::subsampleCloudRandomly(pc, (unsigned int)2048);
//
//			for (unsigned int i = 0; i < entss4096->size(); ++i) {
//				pc4096->addPoint(CCVector3(entss4096->getPoint(i)->x, entss4096->getPoint(i)->y, entss4096->getPoint(i)->z));
//			}
//			for (unsigned int i = 0; i < entss2048->size(); ++i) {
//				pc2048->addPoint(CCVector3(entss2048->getPoint(i)->x, entss2048->getPoint(i)->y, entss2048->getPoint(i)->z));
//			}
//			//保存
//			loadf->saveToFile(pc4096, *txtfileSave4096, savep);
//			m_app->dispToConsole("save4096", ccMainAppInterface::STD_CONSOLE_MESSAGE);
//			loadf->saveToFile(pc2048, *txtfileSave2048, savep);
//			m_app->dispToConsole("save2048", ccMainAppInterface::STD_CONSOLE_MESSAGE);
//
//		}
//		else {
//			m_app->dispToConsole("faillllllllllllllllllllll", ccMainAppInterface::STD_CONSOLE_MESSAGE);
//		}
//	}
//	//this->close();
//	//确定
//}