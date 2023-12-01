//首先：替换所有“SubSampleTools2”为自己的插件名，包括info.json
//其次：打开“SubSampleTools2.qrc”，修改“prefix 前缀”和图标文件名为自己的插件名。然后改名为<yourPluginName>.qrc
//第三：打开info.json填写以下信息：
//	 "type" should be one of: "Standard", "GL", or "I/O" (required)
//	 "name" is the name of the plugin (required)
//	 "icon" is the Qt resource path to the plugin's icon (from the .qrc file)
//	 "description" is used as a tootip if the plugin has actions and is displayed in the plugin dialog
//	 "authors", "maintainers", and "references" show up in the plugin dialog as well

#include <QtGui>
#include <ccPointCloud.h>
#include "SubSampleTools2.h"
#include "SubSamplesDlg.h"
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
#include <CloudSamplingTools.h>
#include <Delaunay2dMesh.h>
#include <Jacobi.h>
#include <MeshSamplingTools.h>
#include <NormalDistribution.h>
#include <ParallelSort.h>
#include <PointCloud.h>
//#include <ScalarFieldTools.h>
#include <StatisticalTestingTools.h>
#include <WeibullDistribution.h>
#include <QApplication>
#include <QProgressDialog>
#include <QMainWindow>

using namespace CCCoreLib;

// Default constructor:
//	- pass the Qt resource path to the info.json file (from <yourPluginName>.qrc file) 
//  - constructor should mainly be used to initialize actions and other members
SubSampleTools2::SubSampleTools2(QObject *parent)
	: QObject(parent)
	, ccStdPluginInterface(":/CC/plugin/SubSampleTools2/info.json")
	, m_action(nullptr)
{
}

// This method should enable or disable your plugin actions
// depending on the currently selected entities ('selectedEntities').
void SubSampleTools2::onNewSelection(const ccHObject::Container &selectedEntities){
	/*if (m_action == nullptr){
		return;
	}*/
	 //For example - only enable our action if something is selected.
	//m_action->setEnabled(!selectedEntities.empty());
	m_action->setEnabled(true);
}

// This method returns all the 'actions' your plugin can perform.
// getActions() will be called only once, when plugin is loaded.
QList<QAction *> SubSampleTools2::getActions()
{
	// default action (if it has not been already created, this is the moment to do it)
	if (!m_action)
	{
		// Here we use the default plugin name, description, and icon,
		// but each action should have its own.
		m_action = new QAction(getName(), this);
		m_action->setToolTip(getDescription());
		m_action->setIcon(getIcon());

		// Connect appropriate signal
		connect(m_action, &QAction::triggered, this, &SubSampleTools2::doAction);
	}

	return{ m_action };
}

// This is an example of an action's method called when the corresponding action
// is triggered (i.e. the corresponding icon or menu entry is clicked in CC's
// main interface). You can access most of CC's components (database,
// 3D views, console, etc.) via the 'm_app' variable (see the ccMainAppInterface
// class in ccMainAppInterface.h).
void SubSampleTools2::doAction(){
	if (m_app == nullptr){
		// m_app should have already been initialized by CC when plugin is loaded
		Q_ASSERT(false);
		return;
	}

	/*********************************插入代码*****************************************/
	// 在这里插入需要的操作

	SubSamplesDlg dlg(m_app, m_app->getMainWindow());
	dlg.show();
	dlg.exec();

	//原先测试代码：
	
	//QString txtfile = "D:/HJ/test/airplane_0001.txt"; //file_path
	//////Parameters:
	//AsciiFilter::SaveParameters savep;
	//savep.alwaysDisplaySaveDialog = false;	
	//AsciiFilter loadf;
	//FileIOFilter::LoadParameters loadp;
	//loadp.alwaysDisplayLoadDialog = false;
	//loadp.autoComputeNormals = true;
	//loadp.shiftHandlingMode = ccGlobalShiftManager::NO_DIALOG_AUTO_SHIFT;
	//loadp.autoComputeNormals = false;
	//loadp.parentWidget = m_app->getMainWindow();
	//loadp.sessionStart = true;
	//CC_FILE_ERROR res;
	//for (int y = 0; y < 1; y++) {
		//m_app->dispToConsole("loadf start", ccMainAppInterface::STD_CONSOLE_MESSAGE);
		//ccHObject *loadedObj = FileIOFilter::LoadFromFile(txtfile, loadp, res, AsciiFilter::GetFileFilter());
		////ccHObject *loadedObj = m_app->getSelectedEntities()[0];
		//if (res == CC_FERR_NO_ERROR && loadedObj){
		//	//m_app->addToDB(loadedObj);
		//	ccHObject::Container clouds;
		//	loadedObj->filterChildren(clouds, true, CC_TYPES::POINT_CLOUD);
		//	ccPointCloud* cloud = static_cast<ccPointCloud*>(clouds[0]);
		//	ccPointCloud* pcSubsampled = new ccPointCloud("pcSubsampled");
		//	if (!cloud || cloud->size() <= 0){
		//		ccLog::Warning("[ccSubsamplingDlg::getSampledCloud] Invalid input cloud!");
		//		return;
		//	}
		//	unsigned count = static_cast<unsigned>(1024);
		//	CCCoreLib::ReferenceCloud* SubsampledEnt = CCCoreLib::CloudSamplingTools::subsampleCloudRandomly(cloud, count);
		//	for (unsigned int i = 0; i < SubsampledEnt->size(); i++) {
		//		pcSubsampled->addPoint(CCVector3(SubsampledEnt->getPoint(i)->x, SubsampledEnt->getPoint(i)->y, SubsampledEnt->getPoint(i)->z));
		//	}
		//	//保存
		//	loadf.saveToFile(pcSubsampled, *txtfileSave, savep);
		//	m_app->dispToConsole(QString("Saved file: %1").arg(*txtfileSave), ccMainAppInterface::STD_CONSOLE_MESSAGE);
		//}
		//else{
		//	ccLog::Error(QString("Failed to load file: %1, Error # = %2").arg(txtfile).arg(res));
		//}
	//}
}