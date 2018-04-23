package com.android.raimy.utils.Module.task;


import com.android.clothingrecycle.tasks.Task;
import com.android.raimy.utils.CustMutex;
import com.android.raimy.utils.LogHelper;

/**
 * Created by raimy on 2018-04-19.
 */

public class TasksExcuteThread extends Thread{
    private boolean bRunning;
    private TaskMngBase mTaskMng;
    private TaskBase mCurTask;
    protected CustMutex mLock;

    public TasksExcuteThread(TaskMngBase taskMngBase){
        mTaskMng = taskMngBase;
        mLock = new CustMutex();
        mLock.SetLock(true);
    }

    @Override
    public void run() {
        super.run();

        while (bRunning){
            TaskBase task = mTaskMng.GetNextTask();
            if(task!=null){
                mCurTask = task;
                mTaskMng.SetCurTask(task);
                mCurTask.Execute();

                Task  task1 = (Task)task;
                LogHelper.logI(getClass().getSimpleName(), "task gridid="+task1.GetGridId()+"------begin");
                mLock.lock();

                LogHelper.logI(getClass().getSimpleName(), "task gridid="+task1.GetGridId()+"------do");

            }
            try {
                Thread.sleep(300);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    @Override
    public synchronized void start() {
        super.start();
        bRunning = true;
    }

    public void Stop(){
        bRunning = false;
        mLock.unlock();
        if(mCurTask!=null){
            mCurTask.StopTask();
        }
    }

    public void DoNextTask(){
        mLock.unlock();
    }
}
