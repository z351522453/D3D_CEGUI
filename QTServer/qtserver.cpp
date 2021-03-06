#include "qtserver.h"
#include "QTableWidget.h"
#include "atlconv.h"
#include "caddaccount.h"
#include "coption.h"
#include "CMartin.h"
#include "QMessageBox"
#include "Xml.h"
#include "QFileDialog"
#include <process.h>
#include "DataType.h"
#include "cthreadinjectdll.h"


QTServer::QTServer(QWidget *parent)
    : QMainWindow(parent) {
    ui.setupUi(this);

    //
    GlobalAddAtom("shitnow");

    //设置表头及大小
    QStringList header;
    header << QStringLiteral("账号") << QStringLiteral("大区") << QStringLiteral("服务器") << QStringLiteral("脚本")
        << QStringLiteral("角色") << QStringLiteral("金币") << QStringLiteral("地图") << QStringLiteral("状态");
    ui.tableWidget->setColumnCount(header.count());
    ui.tableWidget->setHorizontalHeaderLabels(header);
    //ui.tableWidget->setRowCount(20); // 设置行数
    ui.tableWidget->horizontalHeader()->setDefaultSectionSize(150);
    //ui.tableWidget->setColumnWidth(0, 150); //设置第一列宽度
    //ui.tableWidget->setColumnWidth(1, 150); //设置第二列宽度
    //ui.tableWidget->setColumnWidth(2, 150); //设置第三列宽度
    //ui.tableWidget->setColumnWidth(3, 150);
    //ui.tableWidget->setColumnWidth(4, 150);
    //ui.tableWidget->setColumnWidth(5, 150);
    //ui.tableWidget->setColumnWidth(6, 150);
    //ui.tableWidget->horizontalHeader()->setStretchLastSection(true); //将最后一列延伸到整个列表全满
    ui.tableWidget->horizontalHeader()->setSectionsClickable(false); //设置表头不可点击（默认点击后进行排序）
    ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // 所有列自适应窗口宽度

    //设置隔一行变一颜色，即：一灰一白
    ui.tableWidget->setAlternatingRowColors(true);

    //控件刚开始的时候左边默认自带序列号，如果想去掉左边的行号，加上下面的代码
    QHeaderView* headerView = ui.tableWidget->verticalHeader();
    headerView->setHidden(true);
    //设置默认行高
    //headerView->setDefaultSectionSize(30);

    //整行选中的方式
    ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    //不能对表格内容进行修改
    ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_tcpServer = new QTcpServer(this);
    m_tcpServer->listen(QHostAddress::Any, 12589); //监听任何连上12589端口的ip
    connect(m_tcpServer, SIGNAL(newConnection()), this, SLOT(SlotNewConnect()));

    //菜单栏关联
    connect(ui.actionAddAccount, SIGNAL(triggered()), this, SLOT(SlotAddAccount()));
    connect(ui.actionOption, SIGNAL(triggered()), this, SLOT(SlotOptionSet()));
    connect(ui.actionExportAcc, SIGNAL(triggered()), this, SLOT(SlotExportAcc()));
    connect(ui.actionImportAcc, SIGNAL(triggered()), this, SLOT(SlotImportAcc()));
    connect(ui.tableWidget, &CMyTableWidget::SignalSendAddAcc, this, &QTServer::SlotAddAcc);

    // 以下为设置游戏路径
    SlotInitGamePath();

    // 列表框關聯
    QObject::connect(ui.tableWidget, &CMyTableWidget::SignalStartNewGame, this, &QTServer::SlotStartNewGame);
    QObject::connect(ui.tableWidget, &CMyTableWidget::SignalStopScript, this, &QTServer::SlotStopScript);
    QObject::connect(ui.tableWidget, &CMyTableWidget::SignalStartScript, this, &QTServer::SlotStartScript);
}

QTServer::~QTServer() {

}

void QTServer::SlotNewConnect() {
    QTcpSocket* pTcpSocket = m_tcpServer->nextPendingConnection(); // 得到每个连进来的socket
    //pTcpSocket->waitForConnected();
    //martin->Debug("State:%d ", pTcpSocket->state());
    m_tcpSocketList.append(pTcpSocket);
    connect(pTcpSocket, SIGNAL(disconnected()), this, SLOT(SlotClientClosed()));
    connect(pTcpSocket, SIGNAL(disconnected()), pTcpSocket, SLOT(deleteLater()));
    connect(pTcpSocket, SIGNAL(readyRead()), this, SLOT(SlotMessageRead()));
}

void QTServer::SlotMessageRead() {
    for (int i = 0; i < m_tcpSocketList.length(); i++) {
        if (m_tcpSocketList[i]->bytesAvailable() > 0) {
            QByteArray qba = m_tcpSocketList[i]->readAll(); // 收取m_tcpSocket中的所有数据
            PSOCKET_INFO data = (PSOCKET_INFO)qba.data();
            int nCount = ui.tableWidget->rowCount();
            if (nCount) {
                for (int nCurrentRow = 0; nCurrentRow < nCount; nCurrentRow++) {
                    QTableWidgetItem* pItemAcc = ui.tableWidget->item(nCurrentRow, 0);
                    QString qstrAcc = pItemAcc->data(Qt::DisplayRole).toString(); //账号
                    std::string strAcc = std::string((const char*)qstrAcc.toLocal8Bit());

                    if (strAcc == std::string(data->szAccOrScript)) {
                        pItemAcc->setData(Qt::UserRole + 0x200, (int)m_tcpSocketList[i]);

                        switch (data->message) {
                        case SOCKET_MESSAGE::GetScript:
                            SOCKET_INFO socket_info;
                            RtlZeroMemory(&socket_info, sizeof(SOCKET_INFO));
                            socket_info.message = SOCKET_MESSAGE::GetScript;
                            QTableWidgetItem* pItemScript = ui.tableWidget->item(nCurrentRow, 3);
                            QString qstrScript = pItemScript->data(Qt::DisplayRole).toString(); // 脚本
                            std::string strScript = std::string((const char*)qstrScript.toLocal8Bit());
                            strcpy_s(socket_info.szAccOrScript, strScript.c_str());
                            QByteArray datasend;
                            datasend.append((const char*)&socket_info);
                            m_tcpSocketList[i]->write((const char*)&socket_info, sizeof(SOCKET_INFO));
                            //m_tcpSocketList[i]->waitForBytesWritten();
                            //martin->Debug("State:%d ", m_tcpSocketList[i]->state());
                            m_tcpSocketList[i]->flush();

                            QTableWidgetItem* pItemStatus = ui.tableWidget->item(nCurrentRow, 7);
                            pItemStatus->setData(Qt::DisplayRole, QStringLiteral("挂机中")); // 脚本
                            break;
                        }
                        break;
                    }
                }
            }
        }
    }
}

void QTServer::SlotClientClosed() {
    for (int i = 0; i < m_tcpSocketList.length(); i++) {
        if (m_tcpSocketList[i]->state() == QAbstractSocket::UnconnectedState) {
            m_tcpSocketList.removeAt(i);
        }
    }
}

void QTServer::SlotAddAccount() {
    CAddAccount* a = new CAddAccount;
    a->setAttribute(Qt::WA_DeleteOnClose);
    QObject::connect(a, &CAddAccount::SignalNewAcc, this, &QTServer::SlotAddAcc);
    a->show();
}

void QTServer::SlotAddAcc(const QString &strAcc, const QString &strPsw, const QString &strArea, const QString &strServer, const QString &strScript) {
    QTableWidgetItem* _strAcc = new QTableWidgetItem(strAcc);
    //_strAcc->setText(QString::fromWCharArray(A2W(data)));
    _strAcc->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    _strAcc->setData(Qt::UserRole, strPsw); //关联数据, 类似 MFC 中的 SetItemData

    QTableWidgetItem* _strArea = new QTableWidgetItem(strArea);
    _strArea->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    QTableWidgetItem* _strServer = new QTableWidgetItem(strServer);
    _strServer->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    QTableWidgetItem* _strScript = new QTableWidgetItem(strScript);
    _strScript->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    QTableWidgetItem* _strStatus = new QTableWidgetItem(QStringLiteral("空闲"));
    _strStatus->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    //首先rowCount()得到当前中的行数，然后在调用insertRow(row);即可
    int nIndex = ui.tableWidget->rowCount();
    ui.tableWidget->insertRow(nIndex);
    ui.tableWidget->setItem(nIndex, 0, _strAcc);
    ui.tableWidget->setItem(nIndex, 1, _strArea);
    ui.tableWidget->setItem(nIndex, 2, _strServer);
    ui.tableWidget->setItem(nIndex, 3, _strScript);
    ui.tableWidget->setItem(nIndex, 7, _strStatus);
}

void QTServer::SlotOptionSet() {
    COption* a = new COption(this, m_gamePath);
    QObject::connect(a, &COption::SignalNewGamePath, this, &QTServer::SlotInitGamePath);
    a->setAttribute(Qt::WA_DeleteOnClose);
    a->show();
}

void QTServer::SlotInitGamePath() {
    std::string strPath = martin->GetModulePath(NULL);
    strPath += "\\Config.ini";

    //-----------------------------------------------------------
    //    获取配置文件信息
    //-----------------------------------------------------------
    martin->SetPathName(strPath.c_str());
    m_gamePath = QString::fromLocal8Bit(martin->GetString("Path", "Game").c_str());
}

void QTServer::SlotStartNewGame(const int &nRow) {
    QString gamePath = m_gamePath;
    std::string QxDllpath = (const char*)(gamePath.replace("/", "\\").toLocal8Bit());
    QxDllpath += "\\TCLS\\Tenio.ini";
    WritePrivateProfileString("DefaultValue", "Dlls", "TCLS.dll,TenBase.dll,Dir.dll,TenTPF.dll,MemoryAlloctor.dll,June.dll,log.dll,qxpatch.dll", QxDllpath.c_str());
    HANDLE hMapping = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 0x255, "GW_APSInfo");

    DWORD dwMyPid = ::GetCurrentProcessId();
    PShareLoginInfo pLogMsg = (PShareLoginInfo)MapViewOfFile(hMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);
    RtlZeroMemory(pLogMsg, sizeof(PShareLoginInfo));
    pLogMsg->cmdtype = SHARELGOININFOSTATE_INFO;
    pLogMsg->dwRet = 0;
    pLogMsg->Key = (dwMyPid * 22) >> 2;
    pLogMsg->DatiType = 0;
    pLogMsg->DatiErrorCode = 0;

    USES_CONVERSION;
    QTableWidgetItem* _strAcc = ui.tableWidget->item(nRow, 0);
    QString strAcc = _strAcc->data(Qt::DisplayRole).toString();
    QString strPsw = _strAcc->data(Qt::UserRole).toString();

    QTableWidgetItem* _strArea = ui.tableWidget->item(nRow, 1);
    QString strArea = _strArea->data(Qt::DisplayRole).toString();

    QTableWidgetItem* _strServer = ui.tableWidget->item(nRow, 2);
    QString strServer = _strServer->data(Qt::DisplayRole).toString();

    QTableWidgetItem* _strScript = ui.tableWidget->item(nRow, 3);
    //QString strScript = _strScript->data(Qt::DisplayRole).toString();

    QTableWidgetItem* _strStatus = ui.tableWidget->item(nRow, 7);
    //QString strStatus = _strStatus->data(Qt::DisplayRole).toString();

    std::string acc = ((const char*)strAcc.toLocal8Bit());
    std::string psw = ((const char*)strPsw.toLocal8Bit());
    wcscpy_s(pLogMsg->acc, (acc.length() + 1) * 2, A2W(acc.c_str()));
    wcscpy_s(pLogMsg->psw, (psw.length() + 1) * 2, A2W(psw.c_str()));

    std::string area = ((const char*)strArea.toLocal8Bit());
    std::string server = ((const char*)strServer.toLocal8Bit());
    wcscpy_s(pLogMsg->area, (area.length() + 1) * 2, A2W(area.c_str()));
    wcscpy_s(pLogMsg->server, (server.length() + 1) * 2, A2W(server.c_str()));

    //wcscpy_s(pLogMsg->DatiAcc, wcslen(cwDatiAcc) + 1, cwDatiAcc);
    //wcscpy_s(pLogMsg->DatiPwd, wcslen(cwDatiPwd) + 1, cwDatiPwd);

    std::vector<DWORD> processVec = martin->GetProcessIdVec("CryENGINE");
    g_processVec.swap(QVector<DWORD>());
    for (auto v : processVec) {
        g_processVec.append(v);
    }

    g_bInjectDll = TRUE;
    //::CloseHandle((HANDLE)_beginthreadex(NULL, 0, ThreadFun_InsertDLL, NULL, 0, NULL));
    CThreadInjectDll* thread = new CThreadInjectDll(this);
    thread->pItem = _strAcc;
    connect(thread, &CThreadInjectDll::SignalDone, this, &QTServer::SlotGuardDog);
    connect(thread, &CThreadInjectDll::finished, thread, &CThreadInjectDll::deleteLater);
    thread->start();

    QString loginPath = m_gamePath;
    std::string strLoginPath = (const char*)(loginPath.replace("/", "\\").toLocal8Bit());
    strLoginPath += "\\TCLS\\Client.exe";
    STARTUPINFO StartupInfo = { sizeof(STARTUPINFO) }; // 第一个参数是 STARTUPINFO.cb
    StartupInfo.dwFlags = STARTF_USESHOWWINDOW;
    StartupInfo.wShowWindow = TRUE;
    PROCESS_INFORMATION ProcessInformation;
    BOOL bRet = ::CreateProcess(
        strLoginPath.c_str(),
        NULL,
        NULL,
        NULL,
        FALSE,
        CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT | CREATE_DEFAULT_ERROR_MODE,
        NULL,
        NULL,
        &StartupInfo,
        &ProcessInformation);
    if (bRet == 0) {
        g_bInjectDll = FALSE;
        QMessageBox::about(this, QStringLiteral("提示"), QStringLiteral("启动游戏失败! 请检查控制台属性设置!"));
        return;
    }

    ::CloseHandle(ProcessInformation.hThread);
    ::CloseHandle(ProcessInformation.hProcess);

    int RunTimeout = 0;
    while (pLogMsg->cmdtype == SHARELGOININFOSTATE_INFO) { //等待更改状态
        Sleep(1000);
        RunTimeout += 1000;

        if (RunTimeout >= 5000) {
            if (WhetherIsUpdated()) { // 检查游戏是否更新
                g_bInjectDll = FALSE;
                QMessageBox::about(this, QStringLiteral("提示"), QStringLiteral("游戏有更新! 请更新软件!"));
                return;
            }
        }

        if (RunTimeout > 180000) {
            g_bInjectDll = FALSE;
            _strStatus->setData(Qt::DisplayRole, QStringLiteral("登录超时"));
            QMessageBox::about(this, QStringLiteral("提示"), QStringLiteral("登录超时! 请检查账号信息!!"));
            return;
        }
    }

    switch (pLogMsg->cmdtype) {
    case SHARELGOININFOSTATE_SUCCEED: // 成功登陆
        _strStatus->setData(Qt::DisplayRole, QStringLiteral("启动游戏"));
        //QMessageBox::about(this, QStringLiteral("提示"), QStringLiteral("启动游戏!"));
        // 开启软件看门狗
        return;
    case SHARELGOINRET_ERROR_ACCDONGJIE:
        g_bInjectDll = FALSE;
        _strStatus->setData(Qt::DisplayRole, QStringLiteral("账号冻结"));
        QMessageBox::about(this, QStringLiteral("提示"), QStringLiteral("账号被冻结!"));
        return;
    case SHARELGOINRET_ERROR_PSWWRONG://密码错误
        g_bInjectDll = FALSE;
        _strStatus->setData(Qt::DisplayRole, QStringLiteral("密码错误"));
        QMessageBox::about(this, QStringLiteral("提示"), QStringLiteral("密码错误!"));
        return;
    }

    CloseHandle(hMapping);
}

//void QTServer::SlotStartNewGame(const QString &strAcc, const QString &strPsw, const QString &strArea, const QString &strServer) {
//    //if (martin->CreatProcessInsertDLL("F:\\ty\\bootloader.exe", "\"F:\\ty\\bootloader.exe\"  0", "Q:\\Ty\\TyInject\\Debug\\Inject.dll", "F:\\ty/")) {
//    //    // 如果返回成功, 就開啟 DLL 注入線程
//    //}
//
//    QString gamePath = m_gamePath;
//    std::string QxDllpath = (const char*)(gamePath.replace("/", "\\").toLocal8Bit());
//    QxDllpath += "\\TCLS\\Tenio.ini";
//    WritePrivateProfileString("DefaultValue", "Dlls", "TCLS.dll,TenBase.dll,Dir.dll,TenTPF.dll,MemoryAlloctor.dll,June.dll,log.dll,qxpatch.dll", QxDllpath.c_str());
//    HANDLE hMapping = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 0x255, "GW_APSInfo");
//
//    DWORD dwMyPid = ::GetCurrentProcessId();
//    PShareLoginInfo pLogMsg = (PShareLoginInfo)MapViewOfFile(hMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);
//    RtlZeroMemory(pLogMsg, sizeof(PShareLoginInfo));
//    pLogMsg->cmdtype = SHARELGOININFOSTATE_INFO;
//    pLogMsg->dwRet = 0;
//    pLogMsg->Key = (dwMyPid * 22) >> 2;
//    pLogMsg->DatiType = 0;
//    pLogMsg->DatiErrorCode = 0;
//
//    USES_CONVERSION;
//
//    std::string acc = ((const char*)strAcc.toLocal8Bit());
//    std::string psw = ((const char*)strPsw.toLocal8Bit());
//    wcscpy_s(pLogMsg->acc, (acc.length() + 1) * 2, A2W(acc.c_str()));
//    wcscpy_s(pLogMsg->psw, (psw.length() + 1) * 2, A2W(psw.c_str()));
//
//    std::string area = ((const char*)strArea.toLocal8Bit());
//    std::string server = ((const char*)strServer.toLocal8Bit());
//    wcscpy_s(pLogMsg->area, (area.length() + 1) * 2, A2W(area.c_str()));
//    wcscpy_s(pLogMsg->server, (server.length() + 1) * 2, A2W(server.c_str()));
//
//    //wcscpy_s(pLogMsg->DatiAcc, wcslen(cwDatiAcc) + 1, cwDatiAcc);
//    //wcscpy_s(pLogMsg->DatiPwd, wcslen(cwDatiPwd) + 1, cwDatiPwd);
//
//    QString loginPath = m_gamePath;
//    std::string strLoginPath = (const char*)(loginPath.replace("/", "\\").toLocal8Bit());
//    strLoginPath += "\\TCLS\\Client.exe";
//    STARTUPINFO StartupInfo = { sizeof(STARTUPINFO) }; // 第一个参数是 STARTUPINFO.cb
//    StartupInfo.dwFlags = STARTF_USESHOWWINDOW;
//    StartupInfo.wShowWindow = TRUE;
//    PROCESS_INFORMATION ProcessInformation;
//    BOOL bRet = ::CreateProcess(
//        strLoginPath.c_str(),
//        NULL,
//        NULL,
//        NULL,
//        FALSE,
//        CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT | CREATE_DEFAULT_ERROR_MODE,
//        NULL,
//        NULL,
//        &StartupInfo,
//        &ProcessInformation);
//    if (bRet == 0) {
//        QMessageBox::about(this, QStringLiteral("提示"), QStringLiteral("启动游戏失败! 请稍后再试!"));
//        return;
//    }
//
//    ::CloseHandle(ProcessInformation.hThread);
//    ::CloseHandle(ProcessInformation.hProcess);
//
//    int RunTimeout = 0;
//    while (pLogMsg->cmdtype == SHARELGOININFOSTATE_INFO) { //等待更改状态
//        Sleep(1000);
//        RunTimeout += 1000;
//
//        if (RunTimeout >= 5000) {
//            if (WhetherIsUpdated()) { // 检查游戏是否更新
//                QMessageBox::about(this, QStringLiteral("提示"), QStringLiteral("游戏有更新! 请更新软件!"));
//                return;
//            }
//        }
//
//        if (RunTimeout > 180000) {
//            QMessageBox::about(this, QStringLiteral("提示"), QStringLiteral("登录超时! 请检查账号信息!!"));
//            return;
//        }
//    }
//
//    switch (pLogMsg->cmdtype) {
//    case SHARELGOININFOSTATE_SUCCEED: // 成功登陆
//        QMessageBox::about(this, QStringLiteral("提示"), QStringLiteral("成功登录!"));
//        break;
//    case SHARELGOINRET_ERROR_ACCDONGJIE:
//        QMessageBox::about(this, QStringLiteral("提示"), QStringLiteral("账号被冻结!"));
//        return;
//    case SHARELGOINRET_ERROR_PSWWRONG://密码错误
//        QMessageBox::about(this, QStringLiteral("提示"), QStringLiteral("密码错误!"));
//        return;
//    }
//}

BOOL QTServer::WhetherIsUpdated() {
    std::list<_Xml> lAllVal;
    std::vector<std::string> arrFindXmlKeyName;
    arrFindXmlKeyName.swap(std::vector<std::string>());
    arrFindXmlKeyName.push_back("VersionDemoStr");

    QString gamePath = m_gamePath;
    std::string strVer = (const char*)(gamePath.replace("/", "\\").toLocal8Bit());
    strVer += "\\TCLS\\mmog_data.xml";

    CXml::DeadXml(lAllVal, arrFindXmlKeyName, strVer);
    if (lAllVal.front().Val != g_strVersion) {
        //MessageBox(NULL, "游戏有更新! 请更新软件!", "提示", MB_OK);
        //ExitProcess(0);
        return TRUE;
    }
    return FALSE;
}

void QTServer::SlotExportAcc() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save File", "user.ini");

    if (!fileName.isEmpty()) {
        std::string strUser = (const char*)(fileName.replace("/", "\\").toLocal8Bit());
        martin->SetPathName(strUser.c_str());
        martin->DeleteSection("user");

        int nCount = ui.tableWidget->rowCount();
        if (nCount) {
            for (int nCurrentRow = 0; nCurrentRow < nCount; nCurrentRow++) {
                std::vector<std::string> userVector;
                QTableWidgetItem* pItem = ui.tableWidget->item(nCurrentRow, 0);
                QString strAcc = pItem->data(Qt::DisplayRole).toString(); //账号
                QString strPsw = pItem->data(Qt::UserRole).toString(); //密码
                userVector.push_back((const char*)strPsw.toLocal8Bit());

                pItem = ui.tableWidget->item(nCurrentRow, 1);
                QString strArea = pItem->data(Qt::DisplayRole).toString(); // 大区
                userVector.push_back((const char*)strArea.toLocal8Bit());

                pItem = ui.tableWidget->item(nCurrentRow, 2);
                QString strServer = pItem->data(Qt::DisplayRole).toString(); // 服
                userVector.push_back((const char*)strServer.toLocal8Bit());

                pItem = ui.tableWidget->item(nCurrentRow, 3);
                QString strScript = pItem->data(Qt::DisplayRole).toString(); // 脚本
                userVector.push_back((const char*)strScript.toLocal8Bit());

                pItem = ui.tableWidget->item(nCurrentRow, 7);
                QString strStatus = pItem->data(Qt::DisplayRole).toString(); // 状态
                userVector.push_back((const char*)strStatus.toLocal8Bit());

                martin->WriteArray("user", (const char*)strAcc.toLocal8Bit(), &userVector);
            }
        }
    }
}

void QTServer::SlotImportAcc() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "user.ini", "ini (*.ini)");

    if (!fileName.isEmpty()) {
        std::string strUser = (const char*)(fileName.replace("/", "\\").toLocal8Bit());
        martin->SetPathName(strUser.c_str());

        std::vector<std::string> strFilterName;
        std::vector<std::string> strContent;
        martin->GetKeyNames("user", &strFilterName);
        for (auto& v : strFilterName) {
            QTableWidgetItem* _strAcc = new QTableWidgetItem(QString::fromLocal8Bit(v.c_str()));
            _strAcc->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

            martin->GetArray("user", v.c_str(), &strContent);
            _strAcc->setData(Qt::UserRole, QString::fromLocal8Bit(strContent[0].c_str()));

            QTableWidgetItem* _strArea = new QTableWidgetItem(QString::fromLocal8Bit(strContent[1].c_str()));
            _strArea->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

            QTableWidgetItem* _strServer = new QTableWidgetItem(QString::fromLocal8Bit(strContent[2].c_str()));
            _strServer->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

            QTableWidgetItem* _strScript = new QTableWidgetItem(QString::fromLocal8Bit(strContent[3].c_str()));
            _strScript->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

            if (strContent[4] != "账号冻结") {
                if (strContent[4] != "密码错误") {
                    strContent[4] = "空闲";
                }
            }

            QTableWidgetItem* _strStatus = new QTableWidgetItem(QString::fromLocal8Bit(strContent[4].c_str()));
            _strStatus->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            //首先rowCount()得到当前中的行数，然后在调用insertRow(row);即可
            int nIndex = ui.tableWidget->rowCount();
            ui.tableWidget->insertRow(nIndex);
            ui.tableWidget->setItem(nIndex, 0, _strAcc);
            ui.tableWidget->setItem(nIndex, 1, _strArea);
            ui.tableWidget->setItem(nIndex, 2, _strServer);
            ui.tableWidget->setItem(nIndex, 3, _strScript);
            ui.tableWidget->setItem(nIndex, 7, _strStatus);
        }
    }
}

void QTServer::SlotGuardDog(QTableWidgetItem* pItem) {
    // 收到这条信息, 说明注入成功了, 开启开门狗
    int nCount = ui.tableWidget->rowCount();
    if (nCount) {
        for (int nCurrentRow = 0; nCurrentRow < nCount; nCurrentRow++) {
            QTableWidgetItem* pItemAcc = ui.tableWidget->item(nCurrentRow, 0);
            if (pItemAcc == pItem) {
                HWND hGameWnd = (HWND)(pItemAcc->data(Qt::UserRole + 0x100)).toInt();
                QTableWidgetItem* _strStatus = ui.tableWidget->item(nCurrentRow, 7);
                _strStatus->setData(Qt::DisplayRole, QStringLiteral("成功登陆"));
                break;
            }
        }
    }
}

void QTServer::SlotStopScript(const int &nRow) {
    QTableWidgetItem* pItemAcc = ui.tableWidget->item(nRow, 0);
    QTcpSocket* pTcpSocket = (QTcpSocket*)(pItemAcc->data(Qt::UserRole + 0x200)).toInt();
    if (pTcpSocket) {
        SOCKET_INFO socket_info;
        RtlZeroMemory(&socket_info, sizeof(SOCKET_INFO));
        socket_info.message = SOCKET_MESSAGE::StopScript;
        QByteArray datasend;
        datasend.append((const char*)&socket_info);
        pTcpSocket->write((const char*)&socket_info, sizeof(SOCKET_INFO));
        pTcpSocket->flush();
        QTableWidgetItem* pItemStatus = ui.tableWidget->item(nRow, 7);
        pItemStatus->setData(Qt::DisplayRole, QStringLiteral("成功登陆"));
    }
}

void QTServer::SlotStartScript(const int &nRow) {
    QTableWidgetItem* pItemAcc = ui.tableWidget->item(nRow, 0);
    QTcpSocket* pTcpSocket = (QTcpSocket*)(pItemAcc->data(Qt::UserRole + 0x200)).toInt();
    if (pTcpSocket) {
        SOCKET_INFO socket_info;
        RtlZeroMemory(&socket_info, sizeof(SOCKET_INFO));
        socket_info.message = SOCKET_MESSAGE::StartScript;
        QTableWidgetItem* pItemScript = ui.tableWidget->item(nRow, 3);
        QString qstrScript = pItemScript->data(Qt::DisplayRole).toString(); // 脚本
        std::string strScript = std::string((const char*)qstrScript.toLocal8Bit());
        strcpy_s(socket_info.szAccOrScript, strScript.c_str());
        QByteArray datasend;
        datasend.append((const char*)&socket_info);
        pTcpSocket->write((const char*)&socket_info, sizeof(SOCKET_INFO));
        pTcpSocket->flush();
        QTableWidgetItem* pItemStatus = ui.tableWidget->item(nRow, 7);
        pItemStatus->setData(Qt::DisplayRole, QStringLiteral("挂机中"));
    }
}

//std::string QTServer::GetGetCurentModulePath() {
//    //-----------------------------------------------------------
//    //    獲取當前程序全路徑
//    //-----------------------------------------------------------
//    char dllname[MAX_PATH];
//    GetModuleFileName(NULL, dllname, MAX_PATH);
//
//    //-----------------------------------------------------------
//    //    轉換成 QString, 然後去掉路徑中的文件名, 保留當前目錄
//    //-----------------------------------------------------------
//    std::string strDll = dllname;
//    //QString qstrDll = QString::fromStdString(strDll); // 此用法会造成中文乱码
//    QString qstrDll = QString::fromLocal8Bit(strDll.c_str());
//    QString strSplit = "\\";
//    int index = qstrDll.lastIndexOf(strSplit);
//    qstrDll = qstrDll.left(index);
//    //strDll = qstrDll.toStdString(); // 此用法会造成程序崩溃
//    strDll = std::string((const char*)qstrDll.toLocal8Bit());
//    return strDll;
//}