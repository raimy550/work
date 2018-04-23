package com.android.clothingrecycle.Data;

import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.JSONObject;

import java.util.Comparator;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;

/**
 * Created by raimy on 2018-03-23.
 */

public class GridData {
    private String gridIdent;
    private Map<Integer, Integer> gridStates;

    public final static int State_Empty = 0;
    public final static int State_Not_Empty = 1;

    public GridData(){
        gridIdent = "abc-001";
        gridStates = new HashMap<Integer, Integer>();
    }

    public String getGridIdent() {
        return gridIdent;
    }

    public void setGridIdent(String gridIdent) {
        this.gridIdent = gridIdent;
    }

    public Map<Integer, Integer> getGridStates() {
        Map<Integer, Integer> map = new HashMap<>(gridStates);
        new HashMap<>();
        SortDataByKey();
        return map;
    }

    public void setGridStates(Map<Integer, Integer> gridStates) {
        this.gridStates = gridStates;
    }

    public void UpdateGridData(int doorID, int gridState){
       gridStates.put(doorID, gridState);
    }

    public String GetJsonData(){
        JSONObject gridObj = (JSONObject) JSON.toJSON(this);
        String ret = gridObj.toString();
        return ret;
    }

    private boolean IsExistDoor(int doorID){
        boolean bRet = false;
        Set entrys = gridStates.entrySet();
        Iterator it = entrys.iterator();
        while (it.hasNext()){
            Map.Entry entry = (Map.Entry) it.next();
            if((Integer)entry.getKey() == doorID){
                bRet = true;
                break;
            }
        }
        return bRet;
    }

    public boolean IsStatesChange(boolean[] bStates, int ret[]){
        boolean bRet = false;
        Set entrys = gridStates.entrySet();
        Iterator it = entrys.iterator();
        while (it.hasNext()){
            Map.Entry entry = (Map.Entry)it.next();
            Integer key = (Integer) entry.getKey();
            Integer value = (Integer)entry.getValue();
            Integer curValue =  bStates[key]? 1 : 0;
            if(value != curValue){
                bRet = true;
                ret[key] = curValue;
            }
        }
        return bRet;
    }

    public int GetEmptyGrid(){
        int nRet = -1;
        Set entrys = gridStates.entrySet();
        Iterator it = entrys.iterator();
        while (it.hasNext()){
            Map.Entry entry = (Map.Entry)it.next();
            Integer key = (Integer) entry.getKey();
            Integer value = (Integer)entry.getValue();
            if(value == State_Empty){
                nRet = key;
                break;
            }
        }
        
        return nRet;
    }

    public int GetEmptyGridSize(){
        int nRet = 0;
        Set entrys = gridStates.entrySet();
        Iterator it = entrys.iterator();
        while (it.hasNext()){
            Map.Entry entry = (Map.Entry)it.next();
            Integer key = (Integer) entry.getKey();
            Integer value = (Integer)entry.getValue();
            if(value == State_Empty){
                nRet++;
            }
        }

        return nRet;
    }

    public int GetGridCount(){
        return gridStates.size();
    }

    public int GetGridUsedCount(){
        int nRet = 0;
        Set entrys = gridStates.entrySet();
        Iterator it = entrys.iterator();
        while (it.hasNext()){
            Map.Entry entry = (Map.Entry)it.next();
            Integer key = (Integer) entry.getKey();
            Integer value = (Integer)entry.getValue();
            if(value == State_Not_Empty){
                nRet++;
            }
        }

        return nRet;
    }

    class MapKeyComparator implements Comparator<Integer>{
        @Override
        public int compare(Integer o1, Integer o2) {
            return o1-o2;
        }
    }

    public void SortDataByKey(){
       if(gridStates!=null && gridStates.size() >0){
           TreeMap<Integer, Integer> resultMap = new TreeMap<>(new MapKeyComparator());
           resultMap.putAll(gridStates);
           gridStates = resultMap;
       }
    }

    @Override
    public String toString() {
        String strRet = GetJsonData();
        return strRet;
    }
}
