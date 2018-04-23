package com.android.raimy.utils.Module.task;

import com.android.clothingrecycle.tasks.Task;
import com.android.raimy.utils.AbstractSingleton;
import com.android.raimy.utils.CustMutex;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by raimy on 2018-04-18.
 */

public class TaskMngBase {
    protected List<TaskBase> mTasks;
    protected CustMutex mTaskMutex;
    protected TasksExcuteThread mTasksExcuteThread;
    protected Task mCurTask;

    public static AbstractSingleton<TaskMngBase> ObjCreater = new AbstractSingleton<TaskMngBase>() {
        @Override
        protected TaskMngBase NewObject() {
            return new TaskMngBase();
        }
    };

    protected TaskMngBase(){
        mTasks = new ArrayList<>();
        mTaskMutex = new CustMutex();
        mTasksExcuteThread = new TasksExcuteThread(this);
    }

    public void StartTasks(){
        mTasksExcuteThread.start();
    }

    public void AddTask(TaskBase task){
        mTaskMutex.lock();
        mTasks.add(task);
        mTaskMutex.unlock();
    }

    public TaskBase GetNextTask(){
        TaskBase ret=null;
        mTaskMutex.lock();
        if(mTasks.size()>0){
            ret = mTasks.get(0);
            mTasks.remove(0);
        }
        mTaskMutex.unlock();
        
        return ret;
    }

    public void DoNextTask(){
        mTasksExcuteThread.DoNextTask();
    }

    public void SetCurTask(TaskBase task){
        mCurTask = (Task)task;
    }

    public void CleanTasks(){
        mTaskMutex.lock();
        mTasks.clear();
        mTaskMutex.unlock();

        if(mCurTask!=null){
            mCurTask.NoticeTaskDone();
        }
    }
}
