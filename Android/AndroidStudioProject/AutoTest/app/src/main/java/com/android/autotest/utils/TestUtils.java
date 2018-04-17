package com.android.autotest.utils;

import java.util.HashMap;
import java.util.Map;

/**
 * Created by raimy on 2018-04-10.
 */

public class TestUtils {
    //测试类型
    public static final int TEST_SERIAL = 0;//串口测试
    public static final int TEST_USB = 1;//测试
    public static final int TEST_CRASH = 2;//测试
    public static final int TEST_TRUMPET = 3;//测试
    public static final int TEST_HEADSET = 4;//测试
    public static final int TEST_NETWORK = 5;//测试
    public static final int TEST_WIFI = 6;//测试
    public static final int TEST_BT = 7;//测试

    public static Map<Integer, LogicParam.ELogicType> MapTypes;

    //测试状态
    public static final int TEST_STATE_FAIL = 0;
    public static final int TEST_STATE_SUC = 1;
    public static final int TEST_STATE_NOT = 2;

    public static final String STR_TEST = "123";

    //串口相关
    public static String Serial0_Ident = "/dev/ttyAMA0";
    public static String Serial1_Ident = "/dev/ttyAMA1";
    public static String Serial2_Ident = "/dev/ttyAMA2";
    public static String Serial3_Ident = "/dev/ttyAMA3";
    public static String Serial4_Ident = "/dev/ttyAMA4";

    public static String Usb2_Ident = "/storage/disk2";
    public static String Usb3_Ident = "/storage/disk3";
    public static String Usb4_Ident = "/storage/disk4";
    public static String Usb5_Ident = "/storage/disk5";

    public static String Usb_Test_file = "test.txt";
    public static String Usb_Test_Str = "test usb";

    public static int Serial_BaudRate = 115200;

    public static String Pad = "--------->";


    static {
        MapTypes = new HashMap<>();
        MapTypes.put(TEST_SERIAL, LogicParam.ELogicType.ETest_Serial);
        MapTypes.put(TEST_USB, LogicParam.ELogicType.ETest_USB);
        MapTypes.put(TEST_CRASH, LogicParam.ELogicType.ETest_Crash);
        MapTypes.put(TEST_TRUMPET, LogicParam.ELogicType.ETest_Trumpet);
        MapTypes.put(TEST_HEADSET, LogicParam.ELogicType.ETest_Headset);
    }

    public static LogicParam.ELogicType GetLogicType(int type){
        return MapTypes.get(type);
    }

    public static int GetTestType(LogicParam.ELogicType type){
        int nRet=-1 ;
        for (Map.Entry<Integer, LogicParam.ELogicType> entry : MapTypes.entrySet()) {
           if(type == entry.getValue()){
               nRet = entry.getKey();
           }
        }
        return nRet;
    }


}
