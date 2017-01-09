#ifndef DEF_H
#define DEF_H

#define HC_SERVER_IP     "121.41.89.69 "   //服务器IP
#define HC_SERVER_PORT   8000              //服务器端口
#define HC_dbHost_IP    "127.0.0.1"        //数据库所在主机地址
#define HC_dbPort        3306              //数据库端口
#define HC_dbUserName   "root"             //数据库用户名
#define HC_dbPassWord   "root"	           //数据库密码
#define HC_dbName       "oosc"             //数据库名
#define HC_dbType       "QMYSQL"           
#define HC_CMD          "cmd"              //命令
#define HC_REG          "reg"              //注册功能
#define HC_LOGIN        "login"            //登录功能
#define HC_RESULT       "result"           //结果
#define HC_OK           "ok"               //正确
#define HC_ERR          "err"              //错误
#define HC_REASON       "reason"           //原因
#define HC_TELPHONE     "telphone"         //电话号码
#define HC_USERNAME     "username"         //用户名
#define HC_PASSWORD     "password"         //用户密码
#define HC_ROLE         "role"             //角色（司机driver,乘客passenger)
#define HC_CARID        "carid"            //车牌号
#define HC_UPDATESTATUS "updatestatus"     //司机更新状态
#define HC_STATUS       "status"           //状态(忙busy,闲free)
#define HC_WAITORDER    "waitorder"        //等待订单
#define HC_GEOHASH      "geohash"          //geo哈希
#define HC_LAT          "lat"              //纬度
#define HC_LNG          "lng"              //经度
#define HC_GTEORDER     "getorder"         //有订单
#define HC_WAITCAR      "waitcar"          //等车
#define HC_ORDERID      "orderid"          //订单号
#define HC_DPHONE       "dphone"           //司机手机号
#define HC_PPHONE       "pphone"           //乘客手机号
#define HC_SLAT         "slat"             //乘客起点纬度
#define HC_SLNG         "slng"             //乘客起点经度
#define HC_DLAT         "dlat"             //乘客终点纬度
#define HC_DLNG         "dlng"             //乘客终点纬度
#define HC_COAST        "coat"             //经费
#define HC_ORDERTIME    "ordertime"        //最终交易时间
#define HC_GETDRIVERINFO "getdriverinfo"   //获取司机信息
#define HC_PAYEND        "payend"          //支付结束
#define HC_UPDATEINFO    "updateinfo"      //更新自己的位置
#define  QS2CH(Qstr)      Qstr.toStdString().c_str()//QString==>char *
#define  Value(var)       query.value(var).toString()//mysql查询结果

#endif // DEF_H
