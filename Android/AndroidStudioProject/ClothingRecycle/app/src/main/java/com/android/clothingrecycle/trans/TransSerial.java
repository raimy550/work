package com.android.clothingrecycle.trans;

/**
 * Created by raimy on 2018-04-19.
 */

public class TransSerial implements  ITrans{
    @Override
    public boolean Init() {
        return false;
    }

    @Override
    public boolean UnInit() {
        return false;
    }

    @Override
    public int GetConnectedBoardAddr(int addrnum, int maxAddr, int[] retInfo) {
        return 0;
    }

    @Override
    public boolean OpenDoor(int boardID, int doorID, int[] retInfo) {
        return false;
    }

    @Override
    public int GetDoorState(int boardID, int doorID, int[] retInfo) {
        return 0;
    }

    @Override
    public boolean GetDoorsStates(int boardID, int[] retInfo) {
        return false;
    }

    @Override
    public int GetProtocalID(int boardID, int[] retInfo) {
        return 0;
    }
}
