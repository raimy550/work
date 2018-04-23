package com.android.clothingrecycle.tasks;

import com.android.clothingrecycle.Data.DoorState;
import com.android.clothingrecycle.Data.GridData;
import com.android.clothingrecycle.trans.TransManager;
import com.android.clothingrecycle.trans.TransParam;

/**
 * Created by raimy on 2018-04-19.
 */

public class TaskOpenGrid extends Task {

    public TaskOpenGrid(int gridId, TaskManager taskManager){
        super(gridId, taskManager);
    }

    @Override
    public void ExecuteImp() {
        TransManager.ObjCreater.GetInstance().PushCmd(new TransParam(TransParam.eCmd.Cmd_Open_Dor, 1, mGridId));

    }

    @Override
    protected void DoGridDoorStateChange(int nGridId, int State) {
        if(nGridId == mGridId && State == DoorState.Door_state_close){
            NoticeTaskDone();
        }
    }
}
