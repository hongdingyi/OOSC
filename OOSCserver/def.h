#ifndef DEF_H
#define DEF_H

#define HC_SERVER_IP     "121.41.89.69 "   //������IP
#define HC_SERVER_PORT   8000              //�������˿�
#define HC_dbHost_IP    "127.0.0.1"        //���ݿ�����������ַ
#define HC_dbPort        3306              //���ݿ�˿�
#define HC_dbUserName   "root"             //���ݿ��û���
#define HC_dbPassWord   "root"	           //���ݿ�����
#define HC_dbName       "oosc"             //���ݿ���
#define HC_dbType       "QMYSQL"           
#define HC_CMD          "cmd"              //����
#define HC_REG          "reg"              //ע�Ṧ��
#define HC_LOGIN        "login"            //��¼����
#define HC_RESULT       "result"           //���
#define HC_OK           "ok"               //��ȷ
#define HC_ERR          "err"              //����
#define HC_REASON       "reason"           //ԭ��
#define HC_TELPHONE     "telphone"         //�绰����
#define HC_USERNAME     "username"         //�û���
#define HC_PASSWORD     "password"         //�û�����
#define HC_ROLE         "role"             //��ɫ��˾��driver,�˿�passenger)
#define HC_CARID        "carid"            //���ƺ�
#define HC_UPDATESTATUS "updatestatus"     //˾������״̬
#define HC_STATUS       "status"           //״̬(æbusy,��free)
#define HC_WAITORDER    "waitorder"        //�ȴ�����
#define HC_GEOHASH      "geohash"          //geo��ϣ
#define HC_LAT          "lat"              //γ��
#define HC_LNG          "lng"              //����
#define HC_GTEORDER     "getorder"         //�ж���
#define HC_WAITCAR      "waitcar"          //�ȳ�
#define HC_ORDERID      "orderid"          //������
#define HC_DPHONE       "dphone"           //˾���ֻ���
#define HC_PPHONE       "pphone"           //�˿��ֻ���
#define HC_SLAT         "slat"             //�˿����γ��
#define HC_SLNG         "slng"             //�˿���㾭��
#define HC_DLAT         "dlat"             //�˿��յ�γ��
#define HC_DLNG         "dlng"             //�˿��յ�γ��
#define HC_COAST        "coat"             //����
#define HC_ORDERTIME    "ordertime"        //���ս���ʱ��
#define HC_GETDRIVERINFO "getdriverinfo"   //��ȡ˾����Ϣ
#define HC_PAYEND        "payend"          //֧������
#define HC_UPDATEINFO    "updateinfo"      //�����Լ���λ��
#define  QS2CH(Qstr)      Qstr.toStdString().c_str()//QString==>char *
#define  Value(var)       query.value(var).toString()//mysql��ѯ���

#endif // DEF_H
