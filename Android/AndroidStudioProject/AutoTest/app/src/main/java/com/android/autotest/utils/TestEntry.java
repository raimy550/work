package com.android.autotest.utils;

/**
 * Created by raimy on 2018-04-10.
 */

public class TestEntry {
    public int testType;//测试类型
    public String ident;//唯一标识
    public String name;//名称
    public int baudrate;//串口波特率
    public int testState;//测试状态

    public TestEntry(int testType){
        this.testType = testType;
        testState = TestUtils.TEST_STATE_NOT;
        ident ="";
        name="";
    }

    public TestEntry(int testType, String ident){
        this.testType = testType;
        testState = TestUtils.TEST_STATE_NOT;
        this.ident = ident;
        name="";
    }

    public TestEntry(TestEntry entry){
        testType = entry.testType;
        testState = entry.testState;
        ident =entry.ident;
        name=entry.name;
    }
}
