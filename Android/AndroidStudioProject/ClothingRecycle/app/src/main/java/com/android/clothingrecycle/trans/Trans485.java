package com.android.clothingrecycle.trans;

import com.smatek.uart.UartComm;

/**
 * Created by raimy on 2018-03-16.
 */

public class Trans485 implements ITrans{
    private UartComm.Rs485 mRs485;

    public Trans485(){
        mRs485 = new UartComm().new Rs485();
    }

    @Override
    public boolean Init() {
        return mRs485.rs485Init();
    }

    @Override
    public boolean UnInit() {
        mRs485.rs485Destroy();
        return true;
    }

    @Override
    public int GetConnectedBoardAddr(int addrnum, int maxAddr, int[] retInfo) {
        return mRs485.rs485GetBoardAddress(addrnum, maxAddr, retInfo);
    }

    @Override
    public boolean OpenDoor(int boardID, int doorID, int[] retInfo) {
        return mRs485.rs485OpenGrid(boardID, doorID, retInfo)!=-1;
    }

    @Override
    public int GetDoorState(int boardID, int doorID, int[] retInfo) {
        return mRs485.rs485GetDoorState(boardID, doorID, retInfo);
    }

    @Override
    public boolean GetDoorsStates(int boardID, int[] retInfo) {
        int nRet = mRs485.rs485GetDoorState(boardID, 0, retInfo);
        return nRet!=-1;
    }

    @Override
    public int GetProtocalID(int boardID, int[] retInfo) {
        return mRs485.rs485GetProtocalID(boardID, retInfo);
    }
}
