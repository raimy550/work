package com.android.clothingrecycle.Data;

import android.content.Context;
import android.os.Environment;

import com.android.raimy.utils.AbstractSingleton;
import com.android.raimy.utils.LogHelper;

import java.io.File;
import java.util.List;
import java.util.Map;

/**
 * Created by raimy on 2018-03-23.
 */

public class DataManager {
    private final static String TAG = "DataManager";
    private Cabinet mCabinet;
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

        InitData();
    }

    public void InitData(){
        boolean bNewData = true;
        if(new File(mDataSavePath).exists()) {
            mCabinet = mSaver.ParseFile();
            if (mCabinet != null) {
                bNewData = false;
            }
        }
        if(bNewData)
        {
            mCabinet = new Cabinet();
            Grid grid= new Grid();
            grid.setGridNo(7);
            grid.setGridState(Grid.Grid_State_Empty);
            mCabinet.AddGrid(grid);

            grid= new Grid();
            grid.setGridNo(8);
            grid.setGridState(Grid.Grid_State_Empty);
            mCabinet.AddGrid(grid);

            mSaver.SaveFile(mCabinet);
        }

        LogHelper.logD(TAG, mCabinet.toString());
    }

    public void ResetData(){
        SetCleaning(false);
        File file = new File(mDataSavePath);
        if(file.exists()){
            file.delete();
        }
        InitData();
    }

    public void UpdateGridData(int gridNo, int gridState){
        mCabinet.UpdateGridData(gridNo, gridState);
        mSaver.SaveFile(mCabinet);
    }

    /**
     *获取状态改变的门
     * @param bStates in:门的当前状态
     * @param retInfo out:返回状态改变之前的门
     * @return 返回是否有门改变状态
     */
    public boolean GetChangedDoors(boolean[] bStates, Map<Integer, Integer> retInfo){
        return mCabinet.GetChangedDoors(bStates, retInfo);
    }

    public int GetEmptyGrid(){
        int nRet = -1;
        nRet = mCabinet.GetEmptyGrid();

        return nRet;
    }

    public int GetEmptyGridSize(){
        int nRet = 0;
        nRet = mCabinet.GetEmptyGridSize();

        return nRet;
    }

    public boolean IsAllGridEmpty(){
       return  GetEmptyGridSize() == GetGridCount();
    }

    public int GetGridCount(){
        return mCabinet.GetGridCount();
    }

    public int GetGridUsedCount(){
        return mCabinet.GetGridUsedCount();
    }

    public List<Grid> GetGridStates(){
        List<Grid> grids = mCabinet.GetGridStates();

        return grids;
    }

    public void UpdateDoorState(int gridNo, int state){
        mCabinet.UpdateDoorState(gridNo, state);
        mSaver.SaveFile(mCabinet);
    }

    public boolean IsCleaning(){
        return mCabinet.IsCleaning();
    }

    public void SetCleaning(boolean bCleaning){
        mCabinet.SetCleaning(bCleaning);
    }

    public boolean IsAllDoorsClosed(){
        return mCabinet.IsAllDoorsClosed();
    }
}
