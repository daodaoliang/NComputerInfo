#include "ncomputerinfo.h"
#include <QDateTime>
#define MB (1024 * 1024)
#define KB (1024)

NComputerInfo::NComputerInfo(QObject *parent)
    :QObject(parent)
{
    mBegainTime = QDateTime::currentMSecsSinceEpoch();
}

bool NComputerInfo::getMAC(QString &param_mac, bool param_have_param_mac)
{
    foreach (QNetworkInterface temp_mac_info, QNetworkInterface::allInterfaces()) {
        if(!temp_mac_info.hardwareAddress().isEmpty()){
            param_mac = temp_mac_info.hardwareAddress();
            if(!param_have_param_mac){
                param_mac = param_mac.remove(':');
            }
            return true;
        }
    }
    param_mac = "00:00:00:00:00:00";
    if(!param_have_param_mac) param_mac = "000000000000";
    return false;
}

bool NComputerInfo::getVolumeSerialNumber(QString &param_serial)
{
    QString lpRootPathName = "C:\\";
    LPTSTR lpVolumeNameBuffer = new TCHAR[12];
    DWORD nVolumeNameSize=12;
    DWORD VolumeSerialNumber;
    DWORD MaximumComponentLength;
    LPTSTR lpFileSystemNameBuffer = new TCHAR[10];
    DWORD nFileSystemNameSize=10;
    DWORD FileSystemFlags;
    GetVolumeInformation((LPTSTR)lpRootPathName.utf16(),
                         lpVolumeNameBuffer, nVolumeNameSize,
                         &VolumeSerialNumber, &MaximumComponentLength,
                         &FileSystemFlags,
                         lpFileSystemNameBuffer, nFileSystemNameSize);
    param_serial = QString::number(VolumeSerialNumber,16).toUpper();
    return true;
}

bool NComputerInfo::getHardDiskSerialNumber(QString &param_serial)
{
    QLibrary tempLib("./getdiskinfo.dll");
    typedef diskInfo (*getDiskInfo)();
    getDiskInfo myFunction = (getDiskInfo) tempLib.resolve("getDiskInfo");
    if(myFunction){
        param_serial = QString(myFunction().serialNumber).trimmed();
        return true;
    }
    param_serial = "";
    return false;
}

bool NComputerInfo::getCPUCount(QString &param_count)
{
    //备用(2014年11月3日--daodaoliang)
    //systemInfo.dwActiveProcessorMask ---处理器掩码
    //systemInfo.dwNumberOfProcessors ---处理器个数
    //systemInfo.dwPageSize ---处理器分页大小
    //systemInfo.dwProcessorType ---处理器类型
    //systemInfo.lpMaximumApplicationAddress ---最大寻址单元
    //systemInfo.lpMinimumApplicationAddress ---最小寻址单元
    //systemInfo.wProcessorLevel ---处理器等级
    //systemInfo.wProcessorRevision ---处理器版本
    SYSTEM_INFO systemInfo;
    GetSystemInfo(&systemInfo);
    param_count = QString::number(systemInfo.dwNumberOfProcessors);
    qDebug()<<QString::number(systemInfo.wProcessorRevision,16).toUpper();
    return true;
}

bool NComputerInfo::getCPUVersion(QString &param_version)
{
    SYSTEM_INFO systemInfo;
    GetSystemInfo(&systemInfo);
    param_version = QString::number(systemInfo.wProcessorRevision,16).toUpper();
    return true;
}

bool NComputerInfo::getCPUArch(QString &param_cpu_arch)
{
    param_cpu_arch = QSysInfo::currentCpuArchitecture();
    return true;
}

bool NComputerInfo::getUsageRate(QString &param_rate)
{
    static FILETIME preidleTime;
    static FILETIME prekernelTime;
    static FILETIME preuserTime;
    FILETIME idleTime;
    FILETIME kernelTime;
    FILETIME userTime;
    // CPU
    GetSystemTimes(&idleTime, &kernelTime, &userTime);
    quint64 a, b;
    int idle, kernel, user;
    a = (preidleTime.dwHighDateTime << 31) | preidleTime.dwLowDateTime;
    b = (idleTime.dwHighDateTime << 31) | idleTime.dwLowDateTime;
    idle = b - a;
    a = (prekernelTime.dwHighDateTime << 31) | prekernelTime.dwLowDateTime;
    b = (kernelTime.dwHighDateTime << 31) | kernelTime.dwLowDateTime;
    kernel = b - a;
    a = (preuserTime.dwHighDateTime << 31) | preuserTime.dwLowDateTime;
    b = (userTime.dwHighDateTime << 31) | userTime.dwLowDateTime;
    user = b - a;
    int cpuPercent = (kernel + user - idle) * 100 / (kernel + user);
    // mem
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    GlobalMemoryStatusEx(&statex);
    int memoryPercent = statex.dwMemoryLoad;
    int memoryAll = statex.ullTotalPhys / MB;
    int memoryFree = statex.ullAvailPhys / MB;
    int memoryUse = memoryAll - memoryFree;

    preidleTime = idleTime;
    prekernelTime = kernelTime;
    preuserTime = userTime ;
    cpuPercent = (cpuPercent < 0 ? 0 : cpuPercent);
    param_rate = QString("CPU %1%  Mem %2% ( 已用 %3 MB / 共 %4 MB )")
            .arg(cpuPercent).arg(memoryPercent).arg(memoryUse).arg(memoryAll);
    return true;
}

bool NComputerInfo::getSysVersion(QString &param_version)
{
    param_version = QString::number((int)QSysInfo::windowsVersion(),16);
    return true;
}

bool NComputerInfo::getSysUserName(QString &param_version)
{
    param_version = QSysInfo::machineHostName();
    return true;
}

bool NComputerInfo::getDiskSize(int &param_total, int &param_available)
{
    long long freeBytesAvail=0,totalBytes=0,freeBytes=0;
    bool result_flag;
    result_flag=GetDiskFreeSpaceEx((LPCWSTR)QString("C:").utf16(),(PULARGE_INTEGER)&freeBytesAvail,
                                   (PULARGE_INTEGER)&totalBytes,(PULARGE_INTEGER)&freeBytes);
    if(result_flag)
    {
        param_total = totalBytes/(1024*1024);
        param_available = freeBytesAvail/(1024*1024);
        return true;
    } else {
        param_total = -1;
        param_available = -1;
        return false;
    }
}

quint64 NComputerInfo::getRuningTime()
{
    return QDateTime::currentMSecsSinceEpoch() - mBegainTime;
}

bool NComputerInfo::getMachineCode(QString &param_machine_code)
{
    /************************获取硬件信息**********************/
    // 获取mac
    QString param_mac;
    bool ret = getMAC(param_mac, false);
    if(!ret) return false;
    // 获取逻辑盘系列号
    QString param_serial;
    ret = getVolumeSerialNumber(param_serial);
    if(!ret) return false;
    // 获取CPU版本信息
    QString param_CPU_version;
    ret = getCPUVersion(param_CPU_version);
    if(!ret) return false;
    // 获取CPU架构
    QString param_CPU_arch;
    ret = getCPUArch(param_CPU_arch);
    if(!ret) return false;
    /*************************获取系统信息**********************/
    // 获取系统版本
    QString param_sys_verison;
    ret = getSysVersion(param_sys_verison);
    if(!ret) return false;
    // 获取系统登录用户名
    QString param_sys_user;
    ret = getSysUserName(param_sys_user);
    if(!ret) return false;
    /*************************封装成JSON串**********************/
    QJsonObject temp_json;
    temp_json.insert("mac", param_mac);
    temp_json.insert("disk_serial", param_serial);
    temp_json.insert("cpu_version", param_CPU_version);
    temp_json.insert("cpu_arch", param_CPU_arch);
    temp_json.insert("sys_version", param_sys_verison);
    temp_json.insert("sys_user", param_sys_user);
    QJsonDocument temp_document;
    temp_document.setObject(temp_json);
    /************************赋值返回***************************/
    param_machine_code = QString(temp_document.toJson(QJsonDocument::Compact));
    return true;
}

bool NComputerInfo::verifiMachineCode(const QString &param_machine_code, MACHINE_CODE_ERROR &param_error)
{
    QJsonParseError temp_json_error;
    QJsonDocument temp_json_document = QJsonDocument::fromJson(param_machine_code.toLocal8Bit(), &temp_json_error);
    QJsonObject temp_json_object;
    if(temp_json_error.error != QJsonParseError::NoError){
        param_error = PARSE_ERROR;
        return false;
    } else {
        if(temp_json_document.isObject()){
            temp_json_object = temp_json_document.object();
        } else {
            param_error = PARSE_ERROR;
            return false;
        }
    }
    // mac 校验
    QString param_mac;
    bool mac_verify = false;
    bool ret = getMAC(param_mac, false);
    if(temp_json_object.contains("mac")){
        QJsonValue temp_value = temp_json_object.take("mac");
        if(temp_value.isString()){
            if(temp_value.toString() == param_mac){
                mac_verify = true;
            }
        }
    }
    if(!ret || !mac_verify) {
        param_error = MAC_ERROR;
        return false;
    }
    // 逻辑盘序列号 校验
    QString param_serial;
    ret = getVolumeSerialNumber(param_serial);
    bool serial_verify = false;
    if(temp_json_object.contains("disk_serial")){
        QJsonValue temp_value = temp_json_object.take("disk_serial");
        if(temp_value.isString()){
            if(temp_value.toString() == param_serial){
                serial_verify = true;
            }
        }
    }
    if(!ret || !serial_verify) {
        param_error = SERIAL_ERROR;
        return false;
    }
    // CPU版本信息 校验
    QString param_CPU_version;
    ret = getCPUVersion(param_CPU_version);
    bool cpu_version_verify = false;
    if(temp_json_object.contains("cpu_version")){
        QJsonValue temp_value = temp_json_object.take("cpu_version");
        if(temp_value.isString()){
            if(temp_value.toString() == param_CPU_version){
                cpu_version_verify = true;
            }
        }
    }
    if(!ret || !cpu_version_verify){
        param_error = CPUV_ERROR;
        return false;
    }
    // CPU架构 校验
    QString param_CPU_arch;
    ret = getCPUArch(param_CPU_arch);
    bool cpu_arch_verify = false;
    if(temp_json_object.contains("cpu_arch")){
        QJsonValue temp_value = temp_json_object.take("cpu_arch");
        if(temp_value.isString()){
            if(temp_value.toString() == param_CPU_arch){
                cpu_arch_verify = true;
            }
        }
    }
    if(!ret || !cpu_arch_verify) {
        param_error = CPUA_ERROR;
        return false;
    }
    // 系统版本 校验
    QString param_sys_verison;
    ret = getSysVersion(param_sys_verison);
    bool sys_version_verify = false;
    if(temp_json_object.contains("sys_version")){
        QJsonValue temp_value = temp_json_object.take("sys_version");
        if(temp_value.isString()){
            if(temp_value.toString() == param_sys_verison){
                sys_version_verify = true;
            }
        }
    }
    if(!ret || !sys_version_verify){
        param_error = SYSV_ERROR;
        return false;
    }
    // 获取系统登录用户名
    QString param_sys_user;
    ret = getSysUserName(param_sys_user);
    bool sys_user_verufy = false;
    if(temp_json_object.contains("sys_user")){
        QJsonValue temp_value = temp_json_object.take("sys_user");
        if(temp_value.isString()){
            if(temp_value.toString() == param_sys_user){
                sys_user_verufy = true;
            }
        }
    }
    if(!ret || !sys_user_verufy){
        param_error = SYSU_ERROR;
        return false;
    }
    param_error = NOTHING_ERROR;
    return true;
}

QString NComputerInfo::getWlanIP()
{
    QString webCode = getHtml("http://whois.pconline.com.cn/");
    QString web = webCode.replace(" ", "");
    web = web.replace("\r", "");
    web = web.replace("\n", "");
    QStringList list = web.split("<br/>");
    if(list.length()>3){
        QString tar = list[3];
        QStringList ip = tar.split("=");
        return ip[1];
    } else {
        return "";
    }
}

QString NComputerInfo::getLocalIP()
{
    QString localHostName = QHostInfo::localHostName();
    QHostInfo info = QHostInfo::fromName(localHostName);
    foreach(QHostAddress address,info.addresses())
    {
        if(address.protocol() == QAbstractSocket::IPv4Protocol)
            return address.toString();
    }
}

bool NComputerInfo::isConnectedWlan()
{
    return ipLIve("111.13.101.208",80);
}

QString NComputerInfo::getHtml(const QString &param_html)
{
    try{
        QNetworkAccessManager *manager = new QNetworkAccessManager();
        QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(param_html)));
        QByteArray responseData;
        QEventLoop eventLoop;
        QObject::connect(manager, SIGNAL(finished(QNetworkReply *)), &eventLoop, SLOT(quit()));
        eventLoop.exec();
        responseData = reply->readAll();
        return QString(responseData);
    } catch(...){
        return "";
    }
}

bool NComputerInfo::ipLIve(const QString &param_ip, int port)
{
    QTcpSocket tcpClient;
    tcpClient.abort();
    tcpClient.connectToHost(param_ip, port);
    //100毫秒没有连接上则判断不在线
    return tcpClient.waitForConnected(100);
}
