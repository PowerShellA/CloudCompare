//首先：替换所有“SubSampleTools”为自己的插件名，包括info.json
//其次：打开“SubSampleTools.qrc”，修改“prefix 前缀”和图标文件名为自己的插件名。然后改名为<yourPluginName>.qrc
//第三：打开info.json填写以下信息：
//	 "type" should be one of: "Standard", "GL", or "I/O" (required)
//	 "name" is the name of the plugin (required)
//	 "icon" is the Qt resource path to the plugin's icon (from the .qrc file)
//	 "description" is used as a tootip if the plugin has actions and is displayed in the plugin dialog
//	 "authors", "maintainers", and "references" show up in the plugin dialog as well

#include <QtGui>
#include <ccPointCloud.h>
#include "SubSampleTools.h"
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
#include <ScalarFieldTools.h>
#include <StatisticalTestingTools.h>
#include <WeibullDistribution.h>

//#include <QtGui>
#include <QApplication>
#include <QProgressDialog>
#include <QMainWindow>

using namespace CCCoreLib;

// Default constructor:
//	- pass the Qt resource path to the info.json file (from <yourPluginName>.qrc file)
//  - constructor should mainly be used to initialize actions and other members
SubSampleTools::SubSampleTools(QObject *parent)
    : QObject(parent), ccStdPluginInterface(":/CC/plugin/SubSampleTools/info.json"), m_action(nullptr)
{
}

// This method should enable or disable your plugin actions
// depending on the currently selected entities ('selectedEntities').
void SubSampleTools::onNewSelection(const ccHObject::Container &selectedEntities)
{
    if (m_action == nullptr)
    {
        return;
    }
    //For example - only enable our action if something is selected.
    m_action->setEnabled(!selectedEntities.empty());
    //m_action->setEnabled(true);
}

// This method returns all the 'actions' your plugin can perform.
// getActions() will be called only once, when plugin is loaded.
QList<QAction *> SubSampleTools::getActions()
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
        connect(m_action, &QAction::triggered, this, &SubSampleTools::doAction);
    }

    return {m_action};
}

// This is an example of an action's method called when the corresponding action
// is triggered (i.e. the corresponding icon or menu entry is clicked in CC's
// main interface). You can access most of CC's components (database,
// 3D views, console, etc.) via the 'm_app' variable (see the ccMainAppInterface
// class in ccMainAppInterface.h).
void SubSampleTools::doAction()
{
    if (m_app == nullptr)
    {
        // m_app should have already been initialized by CC when plugin is loaded
        Q_ASSERT(false);
        return;
    }

    /*********************************插入代码*****************************************/
    // 在这里插入需要的操作

    //SubSamplesDlg dlg(m_app, m_app->getMainWindow());
    //dlg.exec();
    //m_app->dispToConsole("已经呈现", ccMainAppInterface::STD_CONSOLE_MESSAGE);

    //QString txtfile="C:/Users/36392/Desktop/bak/girl-left.las";

    //原先测试代码：

    //QString txtfile = "D:/HJ/test/airplane_0001.txt"; //file_path
    ////Parameters:
    //AsciiFilter::SaveParameters savep;
    //savep.alwaysDisplaySaveDialog = false;
    //AsciiFilter::LoadParameters loadp;
    //loadp.alwaysDisplayLoadDialog = true;
    //loadp.shiftHandlingMode = ccGlobalShiftManager::DIALOG_IF_NECESSARY;
    //loadp.autoComputeNormals = false;
    //loadp.parentWidget = m_app->getMainWindow();
    //loadp.sessionStart = true;
    //CCVector3d loadCoordinatesShift(0, 0, 0);
    //bool loadCoordinatesTransEnabled = false;
    //loadp.coordinatesShift = &loadCoordinatesShift;
    //loadp.coordinatesShiftEnabled = &loadCoordinatesTransEnabled;
    //
    //AsciiFilter loadf;
    //ccHObject ent;

    //m_app->dispToConsole("loadf start", ccMainAppInterface::STD_CONSOLE_MESSAGE);
    ////CC_FILE_ERROR err = loadf.loadFile(txtfile, ent, loadp);//load the cloud, always crash here
    //CC_FILE_ERROR err;
    //ccHObject *en = FileIOFilter::LoadFromFile(txtfile, loadp, err, QString());

    //m_app->dispToConsole("loadf over", ccMainAppInterface::STD_CONSOLE_MESSAGE);

    //if (err == CC_FILE_ERROR::CC_FERR_NO_ERROR) {
    //	m_app->dispToConsole("enter if clause", ccMainAppInterface::STD_CONSOLE_MESSAGE);
    //	ccPointCloud* pc = static_cast<ccPointCloud*>(&ent);
    //	ccPointCloud* pc4096 = new ccPointCloud("pc4096");
    //	ReferenceCloud* entss4096 = CloudSamplingTools::subsampleCloudRandomly(pc, (unsigned int)4096);

    //	for (unsigned int i = 0; i < entss4096->size(); ++i) {
    //		pc4096->addPoint(CCVector3(entss4096->getPoint(i)->x, entss4096->getPoint(i)->y, entss4096->getPoint(i)->z));
    //	}
    //	//保存
    //	loadf.saveToFile(pc4096, QString("D:/HJ/save.txt"), savep);
    //	m_app->dispToConsole("save4096", ccMainAppInterface::STD_CONSOLE_MESSAGE);
    //
    //}

    //QString().

    ccHObject::Container selected_objs = m_app->getSelectedEntities(); // 获取选择的点云
    //m_app->dispToConsole(QString(selected_objs.size()), ccMainAppInterface::STD_CONSOLE_MESSAGE);
    if (selected_objs.size() == 0)
    {
        m_app->dispToConsole("请选择一个或多个点云!", ccMainAppInterface::ERR_CONSOLE_MESSAGE);
        return;
    }
    SubSamplesDlg dlg(m_app, &selected_objs, m_app->getMainWindow());
    dlg.exec();
	
	
	m_app->refreshAll();
    //ccHObject* ent = selected_objs[0];
    //assert(ent);
    //if (!ent || !ent->isA(CC_TYPES::POINT_CLOUD))//判断所选的对象是否为点云
    //{
    //	m_app->dispToConsole("请选择一个点云!您选择的不是点云！", ccMainAppInterface::ERR_CONSOLE_MESSAGE);
    //	return;
    //}

    //// 插件功能：把选择的点云的y坐标增加10
    //ccPointCloud* pc = static_cast<ccPointCloud*>(ent);
    //ccPointCloud* pc_new = new ccPointCloud("sssssssssss");

    //ReferenceCloud* entss = CloudSamplingTools::subsampleCloudRandomly(pc, (unsigned int)4096);
    //m_app->dispToConsole("已经执行过subsampleCloudRandomly", ccMainAppInterface::STD_CONSOLE_MESSAGE);

    //for (unsigned int i = 0; i < entss->size(); ++i){
    //	pc_new->addPoint(CCVector3(entss->getPoint(i)->x , entss->getPoint(i)->y, entss->getPoint(i)->z));
    //}

    //AsciiFilter* loadf = new AsciiFilter();
    //AsciiFilter::SaveParameters savep;
    //QString savepath = "D:/HJ/save.txt";
    ////保存
    //loadf->saveToFile(pc_new, savepath, savep);

    //ccHObject* cc_containers = new ccHObject("subsample4096");
    //cc_containers->addChild(pc_new);

    //m_app->addToDB(cc_containers, true, true);
    //m_app->refreshAll();

    ///*********************************插入代码*****************************************/

    //// This is how you can output messages
    //// Display a standard message in the console
    //m_app->dispToConsole("[SubSampleTools] plugin run successfully!", ccMainAppInterface::STD_CONSOLE_MESSAGE);

    //Display a warning message in the console
    //m_app->dispToConsole( "[SubSampleTools] Warning: example plugin shouldn't be used as is", ccMainAppInterface::WRN_CONSOLE_MESSAGE );

    //Display an error message in the console AND pop - up an error box
    //m_app->dispToConsole( "Example plugin shouldn't be used - it doesn't do anything!", ccMainAppInterface::ERR_CONSOLE_MESSAGE );
}