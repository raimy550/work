package com.android.clothingrecycle.tasks;


import com.android.clothingrecycle.Data.DoorState;
import com.android.clothingrecycle.trans.TransManager;
import com.android.clothingrecycle.trans.TransParam;
import com.android.raimy.utils.Module.task.TaskMngBase;

/**
 * Created by raimy on 2018-04-19.
 */

public class TaskCleaningOpenGrid extends Task{

    public TaskCleaningOpenGrid(int gridId, TaskMngBase taskManager){
        super(gridId, taskManager);
    }

    @Override
    public void ExecuteImp() {
        //
        TaskManager taskManager = (TaskManager)mTaskMngBase;
        taskManager.PrinterQrCode("123456789");
        TransManager.ObjCreater.GetInstance().PushCmd(new TransParam(TransParam.eCmd.Cmd_Open_Dor, 1, mGridId+1));


    }

    @Override
    protected void DoGridDoorStateChange(int nGridId, int State) {
        if(nGridId == mGridId && State == DoorState.Door_state_close) {
            NoticeTaskDone();
        }
    }
}
