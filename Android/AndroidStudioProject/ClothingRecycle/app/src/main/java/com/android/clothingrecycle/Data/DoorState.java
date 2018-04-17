package com.android.clothingrecycle.Data;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

/**
 * Created by raimy on 2018-03-23.
 */

public class DoorState {
    private Map<Integer, Integer> doorStates;
    String gridIdent = "abc-001";
    public final static int Door_state_close = 0;
    public final static int Door_state_open = 1;
    public final static int Door_state_cleaning = 2;
    public final static int Door_state_None = 10;
    private boolean mBCleanning;

    public DoorState(){
        gridIdent = "abc-001";
        doorStates = new HashMap<Integer, Integer>();
        doorStates.put(6, Door_state_close);
        doorStates.put(7, Door_state_close);
        doorStates.put(8, Door_state_close);
        mBCleanning = false;
    }

    public boolean UpdateDoorsStates(boolean[] bStates, Map<Integer, Integer> retInfo){
        boolean bRet = false;
        Set entrys = doorStates.entrySet();
        Iterator it = entrys.iterator();
        while (it.hasNext()){
            Map.Entry entry = (Map.Entry)it.next();
            Integer key = (Integer) entry.getKey();
            Integer value = (Integer)entry.getValue();
            Integer curValue =  bStates[key]? Door_state_open : Door_state_close;
            if(value != curValue){
                bRet = true;
                doorStates.put(key, curValue);
                retInfo.put(key, curValue);
            }
        }
        return bRet;
    }

    public boolean GetChangedDoors(boolean[] bStates, Map<Integer, Integer> retInfo){
        boolean bRet = false;
        Set entrys = doorStates.entrySet();
        Iterator it = entrys.iterator();
        while (it.hasNext()){
            Map.Entry entry = (Map.Entry)it.next();
            Integer key = (Integer) entry.getKey();
            Integer value = (Integer)entry.getValue();
            Integer curValue =  bStates[key]? Door_state_open : Door_state_close;
            if(value != curValue){
                bRet = true;
                retInfo.put(key, value);
            }
        }
        return bRet;
    }

    public int GetDoorState(int doorId){
        int nRet = Door_state_None;
        if(doorStates.containsKey(doorId)){
            nRet = doorStates.get(doorId);
        }
       return nRet;
    }

    public void UpdateDoorState(int doorId, int state){
        if(doorStates.containsKey(doorId)){
            doorStates.put(doorId, state);
        }
    }

    public boolean IsCleaning(){
        return mBCleanning;
    }

    public void SetCleaning(boolean bCleaning){
        mBCleanning = bCleaning;
    }

    public boolean IsAllDoorsClosed(){
        boolean bRet = true;
        Set entrys = doorStates.entrySet();
        Iterator it = entrys.iterator();
        while (it.hasNext()){
            Map.Entry entry = (Map.Entry)it.next();
            Integer key = (Integer) entry.getKey();
            Integer value = (Integer)entry.getValue();
            if(value != Door_state_close){
                bRet = false;
                break;
            }
        }
        return bRet;
    }

}
