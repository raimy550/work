package com.android.clothingrecycle.trans;

/**
 * Created by raimy on 2018-03-16.
 */

public interface ITrans {
    boolean Init();
    boolean UnInit();
    int GetConnectedBoardAddr(int addrnum, int maxAddr, int[] retInfo);
    boolean OpenDoor(int boardID, int doorID, int[] retInfo);
    int GetDoorState(int boardID, int doorID, int[] retInfo);
    boolean GetDoorsStates(int boardID, int[] retInfo);
    int GetProtocalID(int boardID, int[] retInfo);
}
