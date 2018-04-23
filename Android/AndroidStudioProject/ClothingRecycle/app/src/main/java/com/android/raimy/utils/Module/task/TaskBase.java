package com.android.raimy.utils.Module.task;

/**
 * Created by raimy on 2018-04-18.
 */

public abstract  class TaskBase {
    protected int mType; // 任务类型
    protected TaskMngBase mTaskMngBase;


    public TaskBase(TaskMngBase taskMngBase){
        mTaskMngBase = taskMngBase;
    }

    class TaskThread extends  Thread{
        @Override
        public void run() {
            super.run();
            ExecuteImp();
        }
    }

    public void Execute(){
        new TaskThread().start();
    }

    public abstract void ExecuteImp();

    public void StopTask(){
    }

    public void NoticeTaskDone(){
        mTaskMngBase.DoNextTask();
    }

    public int GetTaskType(){
        return mType;
    }
}
