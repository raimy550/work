package com.android.clothingrecycle.tasks;

import com.android.raimy.utils.Module.task.TaskBase;
import com.android.raimy.utils.Module.task.TaskMngBase;

/**
 * Created by raimy on 2018-04-19.
 */

public  class Task extends TaskBase {
    protected int mGridId;

    protected Task(int gridId, TaskMngBase taskMngBase){
        super(taskMngBase);
        mGridId = gridId;
    }

    public int GetGridId(){
        return mGridId;
    }

    @Override
    public void ExecuteImp() {
    }

    protected void DoGridDoorStateChange(int nGridId, int State){

    }
}
