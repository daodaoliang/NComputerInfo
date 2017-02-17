#include <QCoreApplication>
#include "ncomputerinfo.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug()<<"**************************************获取电脑信息测试开始*************************************";
    NComputerInfo test_case_instance;

    qDebug()<<"---------------------获取MAC用例开始------------------------";
    QString test_case_001_mac;
    bool ret = test_case_instance.getMAC(test_case_001_mac, false);
    qDebug()<<"是否获取成功:"<<ret<<" MAC:"<<test_case_001_mac;
    qDebug()<<"---------------------获取MAC用例结束------------------------\r\n";

    qDebug()<<"---------------------获取C盘逻辑序列号用例开始-----------------";
    QString test_case_002_serial;
    ret = test_case_instance.getVolumeSerialNumber(test_case_002_serial);
    qDebug()<<"是否获取成功:"<<ret<<" serial:"<<test_case_002_serial;
    qDebug()<<"---------------------获取C盘逻辑序列号用例结束-----------------\r\n";

    qDebug()<<"---------------------获取硬盘物理序列号用例开始-----------------";
    QString test_case_003_serial;
    ret = test_case_instance.getHardDiskSerialNumber(test_case_003_serial);
    qDebug()<<"是否获取成功:"<<ret<<" serial:"<<test_case_003_serial;
    qDebug()<<"---------------------获取硬盘物理序列号用例结束-----------------\r\n";

    qDebug()<<"---------------------获取CPU个数用例开始----------------------";
    QString test_case_004_count;
    ret = test_case_instance.getCPUCount(test_case_004_count);
    qDebug()<<"是否获取成功:"<<ret<<" count:"<<test_case_004_count;
    qDebug()<<"---------------------获取CPU个数用例结束----------------------\r\n";

    qDebug()<<"---------------------获取硬盘尺寸用例开始----------------------";
    int test_case_006_total_size;
    int test_case_006_ava_size;
    ret = test_case_instance.getDiskSize(test_case_006_total_size, test_case_006_ava_size);
    qDebug()<<"是否获取成功:"<<ret<<" total:"<<test_case_006_total_size<<" available:"<<test_case_006_ava_size;
    qDebug()<<"---------------------获取硬盘尺寸用例结束----------------------\r\n";

    qDebug()<<"---------------------获取系统版本用例开始----------------------";
    QString test_case_005_version;
    ret = test_case_instance.getSysVersion(test_case_005_version);
    qDebug()<<"是否获取成功:"<<ret<<" version:"<<test_case_005_version;
    qDebug()<<"---------------------获取系统版本用例结束----------------------\r\n";

    qDebug()<<"---------------------获取使用率用例开始------------------------";
    QString test_case_007_rate;
    ret = test_case_instance.getUsageRate(test_case_007_rate);
    qDebug()<<"是否获取成功:"<<ret<<" rate:"<<test_case_007_rate;
    qDebug()<<"---------------------获取使用率用例结束------------------------\r\n";

    qDebug()<<"---------------------获取CPU版本用例开始----------------------";
    QString test_case_008_version;
    ret = test_case_instance.getCPUVersion(test_case_008_version);
    qDebug()<<"是否获取成功:"<<ret<<" cpu version:"<<test_case_008_version;
    qDebug()<<"---------------------获取CPU版本用例结束----------------------\r\n";

    qDebug()<<"---------------------获取运行用例开始-------------------------";
    qDebug()<<"系统当前运行时间:"<<test_case_instance.getRuningTime();
    qDebug()<<"---------------------获取运行用例结束-------------------------\r\n";

    qDebug()<<"---------------------获取CPU架构用例开始-----------------------";
    QString test_case_009_arch;
    ret = test_case_instance.getCPUArch(test_case_009_arch);
    qDebug()<<"是否获取成功:"<<ret<<" 架构:"<<test_case_009_arch;
    qDebug()<<"---------------------获取CPU架构用例结束-----------------------\r\n";

    qDebug()<<"---------------------获取系统登录用户用例开始--------------------";
    QString test_case_010_user;
    ret = test_case_instance.getSysUserName(test_case_010_user);
    qDebug()<<"是否获取成功:"<<ret<<" 架构:"<<test_case_010_user;
    qDebug()<<"---------------------获取系统登录用户用例开始--------------------\r\n";

    qDebug()<<"---------------------获取机器码用例开始-------------------------";
    QString test_case_011_machine_code;
    ret = test_case_instance.getMachineCode(test_case_011_machine_code);
    qDebug()<<"是否获取成功:"<<ret<<" 机器码:"<<test_case_011_machine_code;
    qDebug()<<"---------------------获取机器码用例结束-------------------------\r\n";

    qDebug()<<"---------------------验证机器码用例开始-------------------------";
    NComputerInfo::MACHINE_CODE_ERROR test_case_012_machine_code;
    ret = test_case_instance.verifiMachineCode(test_case_011_machine_code, test_case_012_machine_code);
    qDebug()<<"是否验证成功:"<<ret<<" 错误代码:"<<test_case_012_machine_code;
    qDebug()<<"---------------------验证机器码用例结束-------------------------\r\n";

    qDebug()<<"---------------------验证外网地址用例开始------------------------";
    qDebug()<<"外网地址为:"<<test_case_instance.getWlanIP();
    qDebug()<<"---------------------验证外网地址用例结束------------------------\r\n";

    qDebug()<<"---------------------验证本地地址用例开始------------------------";
    qDebug()<<"本地地址为:"<<test_case_instance.getLocalIP();
    qDebug()<<"---------------------验证本地地址用例结束------------------------\r\n";

    qDebug()<<"---------------------验证联通外网用例开始------------------------";
    qDebug()<<"是否联通外网:"<<test_case_instance.isConnectedWlan();
    qDebug()<<"---------------------验证联通外网用例开始------------------------\r\n";


    qDebug()<<"**************************************获取电脑信息测试结束*************************************";
    return a.exec();
}
