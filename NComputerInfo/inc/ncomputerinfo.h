#ifndef NCOMPUTERINFO_H
#define NCOMPUTERINFO_H

#include <Windows.h>
#include <WinIoCtl.h>
#include <QHostInfo>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QLibrary>
#include <QSysInfo>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QtNetwork>
#include "getdiskinfo.h"
#include "ncomputerinfo_global.h"

/**
 * @brief The NComputerInfo class 获取程序运行期间的电脑硬件信息
 */
class NCOMPUTERINFOSHARED_EXPORT NComputerInfo: public QObject
{
    Q_OBJECT
public:
    explicit NComputerInfo(QObject *parent = NULL);
    enum MACHINE_CODE_ERROR{
        NOTHING_ERROR,
        MAC_ERROR,
        SERIAL_ERROR,
        CPUV_ERROR,
        CPUA_ERROR,
        SYSV_ERROR,
        SYSU_ERROR,
        PARSE_ERROR
    };

    /*******************************电脑硬件信息****************************/
public:
    /**
     * @brief getMAC 获取MAC地址
     * @param param_mac mac地址
     * @param param_have_param_mac 是否有分号
     * @return 是否获取成功
     */
    bool getMAC(QString &param_mac, bool param_have_param_mac);

    /**
     * @brief getVolumeSerialNumber 获取C盘逻辑序列号
     * @param param_serial 序列号
     * @return 是否获取成功
     */
    bool getVolumeSerialNumber(QString &param_serial);

    /**
     * @brief getHardDiskSerialNumber 获取硬盘的物理序列号
     * @param param_serial
     * @return
     */
    bool getHardDiskSerialNumber(QString &param_serial);

    /**
     * @brief getCPUCount 获取CPU个数
     * @param param_count CPU个数
     * @return 是否获取成功
     */
    bool getCPUCount(QString &param_count);

    /**
     * @brief getCPUVersion 获取CPU版本信息
     * @param param_version 版本
     * @return 是否获取成功
     */
    bool getCPUVersion(QString &param_version);

    /**
     * @brief getCPUArch 获取CPU架构
     * @param param_cpu_arch
     * @return
     */
    bool getCPUArch(QString &param_cpu_arch);

    /**
     * @brief getDiskSize 获取系统硬盘容量
     * @param param_total 总容量
     * @param param_available 可用容量
     * @return 是否获取成功
     */
    bool getDiskSize(int &param_total,int &param_available);

    /*******************************电脑系统信息****************************/
public:
    /**
     * @brief getCPUUsageRate 获取资源使用率
     * @param param_rate 使用率
     * @return
     */
    bool getUsageRate(QString &param_rate);

    /**
     * @brief getSysVersion 获取系统版本信息
     * @param param_version 版本
     * @return 是否获取成功
     */
    bool getSysVersion(QString &param_version);

    /**
     * @brief getSysUserName 获取当前系统登录名字
     * @param param_version
     * @return
     */
    bool getSysUserName(QString &param_version);

    /**
     * @brief getRuningTime 获取程序当前运行时间
     * @return
     */
    quint64 getRuningTime();

    /*******************************电脑唯一机器码****************************/
public:

    /**
     * @brief getMachineCode 获取本机机器码
     * @param param_machine_code 机器码
     * @return 是否获取成功
     */
    bool getMachineCode(QString &param_machine_code);

    /**
     * @brief verifiMachineCode 验证机器码是否和本机匹配
     * @param param_machine_code 机器码
     * @return 是否验证成功
     */
    bool verifiMachineCode(const QString &param_machine_code, MACHINE_CODE_ERROR &param_error);

    /*******************************电脑网络信息****************************/
public:

    /**
     * @brief getWlanIP 获取外网地址
     * @return 外网IP
     */
    QString getWlanIP();

    /**
     * @brief getLocalIP 获取本机IP地址
     * @return 本地IP
     */
    QString getLocalIP();

    /**
     * @brief isConnectedWlan 是否联通外网
     * @return 是否联通外网
     */
    bool isConnectedWlan();

private:
    /**
     * @brief getHtml 获取指定网页的源码
     * @param param_html 指定的地址
     * @return 网页源码
     */
    QString getHtml(const QString &param_html);

    bool ipLIve(const QString &param_ip, int port);
public:
    quint64 mBegainTime;
};

#endif // NCOMPUTERINFO_H
