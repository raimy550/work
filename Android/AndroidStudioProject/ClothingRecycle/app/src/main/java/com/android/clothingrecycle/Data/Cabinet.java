package com.android.clothingrecycle.Data;

import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.JSONObject;
import com.alibaba.fastjson.TypeReference;
import com.raimy.utils.CustMutex;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Created by raimy on 2018-04-23.
 */

public class Cabinet {
    private String mCarbinetIdent;
    private CustMutex mMutex;
    private ArrayList<Grid> mGrids;
    private boolean mBCleanning;

    public String getmCarbinetIdent() {
        return mCarbinetIdent;
    }

    public void setmCarbinetIdent(String mCarbinetIdent) {
        this.mCarbinetIdent = mCarbinetIdent;
    }

    public CustMutex getmMutex() {
        return mMutex;
    }

    public void setmMutex(CustMutex mMutex) {
        this.mMutex = mMutex;
    }

    public ArrayList<Grid> getmGrids() {
        return mGrids;
    }

    public void setmGrids(ArrayList<Grid> mGrids) {
        this.mGrids = mGrids;
    }

    public boolean ismBCleanning() {
        return mBCleanning;
    }

    public void setmBCleanning(boolean mBCleanning) {
        this.mBCleanning = mBCleanning;
    }


    public Cabinet(){
        mCarbinetIdent = "abc-001";
        mGrids = new ArrayList<>();
        mBCleanning = false;
        mMutex = new CustMutex();

    }

//Grid interface----------------------------
    public List<Grid> GetGridStates() {
        List<Grid> ret = new ArrayList<>(mGrids);
        SortDataByKey();
        return ret;
    }

    public void UpdateGridData(int gridNo, int gridState){
        mMutex.lock();
        for (int i=0; i<mGrids.size();i++){
            Grid grid = mGrids.get(i);
            if(grid.getGridNo() == gridNo){
                grid.setGridState(gridState);
            }
        }
        mMutex.unlock();
    }

    public String GetJsonData(){
        String ret =  JSON.toJSONString(this);
       // String ret = gridObj.toString();

        return ret;
    }

    public int GetEmptyGrid(int gridType){
        int nRet = -1;
        mMutex.lock();
        for (int i=0; i<mGrids.size();i++){
            Grid grid = mGrids.get(i);
            if(grid.getGridState() == Grid.Grid_State_Empty){
                if(gridType == Grid.Grid_Type_None){
                    nRet = grid.getGridNo();
                }else if(gridType == grid.getGridType()){
                    nRet = grid.getGridNo();
                }
                break;
            }
        }
        mMutex.unlock();
        return nRet;
    }

    public int GetEmptyGridCount(int gridType){
        int nRet = 0;
        mMutex.lock();
        for (int i=0; i<mGrids.size();i++){
            Grid grid = mGrids.get(i);
            if(grid.getGridState() == Grid.Grid_State_Empty){
                if(gridType == Grid.Grid_Type_None){
                    nRet++;
                }else if(gridType == grid.getGridType()){
                    nRet++;
                }
            }
        }
        mMutex.unlock();

        return nRet;
    }

    public int GetGridCount(int gridType){
        int nRet = 0;
        if(gridType == Grid.Grid_Type_None){
            nRet = mGrids.size();
        }else{
            mMutex.lock();
            for (int i=0; i<mGrids.size();i++){
                Grid grid = mGrids.get(i);
                if(gridType == grid.getGridType()){
                   nRet++;
                }
            }
            mMutex.unlock();
        }
        return nRet;
    }

    public int GetGridUsedCount(int gridType){
        int nRet = 0;
        mMutex.lock();
        for (int i=0; i<mGrids.size();i++){
            Grid grid = mGrids.get(i);
            if(grid.getGridState() == Grid.Grid_State_Used){
                if(gridType == Grid.Grid_Type_None){
                    nRet++;
                }else if(gridType == grid.getGridType()){
                    nRet++;
                }
            }
        }
        mMutex.unlock();
        return nRet;
    }


    public void SortDataByKey(){
        Collections.sort(mGrids);
    }



//Door interface-------------------------------
    public boolean GetChangedDoors(boolean[] bStates, Map<Integer, Integer> retInfo){
        boolean bRet = false;
        mMutex.lock();
        for (int i=0; i<mGrids.size();i++){
            Grid grid = mGrids.get(i);
            Integer gridNo = grid.getGridNo();
            Integer state = grid.getDoorState();
            Integer curState =  bStates[gridNo]? Grid.Door_state_open : Grid.Door_state_close;
            if(state != curState){
                bRet = true;
                retInfo.put(gridNo, state);
            }
        }
        mMutex.unlock();
        return bRet;
    }

    public void UpdateDoorState(int gridNo, int state){
        mMutex.lock();
        for (int i=0; i<mGrids.size();i++){
            Grid grid = mGrids.get(i);
            if(grid.getGridNo() == gridNo){
                grid.setDoorState(state);
            }
        }
        mMutex.unlock();
    }

    public boolean IsAllDoorsClosed(){
        boolean bRet = true;
        mMutex.lock();
        for (int i=0; i<mGrids.size();i++){
            Grid grid = mGrids.get(i);
            if(grid.getDoorState() != Grid.Door_state_close){
                bRet = false;
                break;
            }
        }
        mMutex.unlock();
        return bRet;
    }

//柜子接口
    @Override
    public String toString() {
        String strRet = GetJsonData();
        return strRet;
    }

    public boolean IsCleaning(){
        return mBCleanning;
    }

    public void SetCleaning(boolean bCleaning){
        mBCleanning = bCleaning;
    }


    public void AddGrid(Grid grid){
        mMutex.lock();
        mGrids.add(grid);
        mMutex.unlock();
    }

}
