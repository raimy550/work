package com.android.clothingrecycle.Data;

import android.content.Context;
import android.os.Environment;

import com.raimy.utils.AbstractSingleton;
import com.raimy.utils.LogHelper;

import java.io.File;
import java.util.HashMap;
import java.util.Map;

import javax.xml.transform.dom.DOMResult;

/**
 * Created by raimy on 2018-03-23.
 */

public class DataManager {
    private final static String TAG = "DataManager";
    private GridData mGridData;
    private DoorState mDoorStates;
    private FileSaver mSaver;
    private Context mAppContext;
    private String mDataSavePath;
    private final static String File_Name = "GridState.xml";

    public static AbstractSingleton<DataManager> ObjCreater = new AbstractSingleton<DataManager>() {
        @Override
        protected DataManager NewObject() {
            return new DataManager();
        }
    };

    private DataManager(){
    }

    public void Init(Context appContext){
        mAppContext = appContext;
        File file =  Environment.getExternalStorageDirectory();
        mDataSavePath = file.toString()+"/"+File_Name;
        mSaver = new FileSaver(mDataSavePath);
        mDoorStates = new DoorState();
        InitData();
    }

    public void InitData(){
        boolean bNewData = true;
        if(new File(mDataSavePath).exists()) {
            mGridData = mSaver.ParseFile();
            if (mGridData != null) {
                bNewData = false;
            }
        }
        if(bNewData)
        {
            mGridData = new GridData();
            mGridData.setGridIdent("abc-001");
            Map<Integer, Integer> map= new HashMap<Integer, Integer>();
            map.put(6, 0);
            map.put(7, 0);
            map.put(8, 0);
            mGridData.setGridStates(map);
            mSaver.SaveFile(mGridData);
        }

        LogHelper.logD(TAG, mGridData.toString());
    }

    public void ResetData(){
        File file = new File(mDataSavePath);
        if(file.exists()){
            file.delete();
        }
        InitData();
    }

    public void UpdateGridData(int doorID, int gridState){
        mGridData.UpdateGridData(doorID, gridState);
        mSaver.SaveFile(mGridData);
    }

    public boolean UpdateDoorsStates(boolean[] bStates, Map<Integer, Integer> retInfo){
        boolean bRet = false;
        bRet = mDoorStates.UpdateDoorsStates(bStates, retInfo);
        return bRet;
    }

    /**
     *获取状态改变的门
     * @param bStates in:门的当前状态
     * @param retInfo out:返回状态改变之前的门
     * @return 返回是否有门改变状态
     */
    public boolean GetChangedDoors(boolean[] bStates, Map<Integer, Integer> retInfo){
        return mDoorStates.GetChangedDoors(bStates, retInfo);
    }

    public int GetEmptyGrid(){
        int nRet = -1;
        nRet = mGridData.GetEmptyGrid();

        return nRet;
    }

    public int GetEmptyGridSize(){
        int nRet = 0;
        nRet = mGridData.GetEmptyGridSize();

        return nRet;
    }

    public int GetGridCount(){
        return mGridData.GetGridCount();
    }

    public int GetGridUsedCount(){
        return mGridData.GetGridUsedCount();
    }

    public Map<Integer, Integer> GetGridStates(){
        Map<Integer, Integer> map = mGridData.getGridStates();

        return map;
    }

    public int GetDoorState(int doorId){
        return mDoorStates.GetDoorState(doorId);
    }

    public void UpdateDoorState(int doorId, int state){
        mDoorStates.UpdateDoorState(doorId, state);
    }

    public boolean IsCleaning(){
        return mDoorStates.IsCleaning();
    }

    public void SetCleaning(boolean bCleaning){
       mDoorStates.SetCleaning(bCleaning);
    }

    public boolean IsAllDoorsClosed(){
        return mDoorStates.IsAllDoorsClosed();
    }
}
