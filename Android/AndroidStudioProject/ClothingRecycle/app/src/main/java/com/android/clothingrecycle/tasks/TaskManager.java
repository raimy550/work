package com.android.clothingrecycle.tasks;

import android.app.Service;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.IBinder;

import com.peripheral.printer.api.IPrinterCallBack;
import com.peripheral.printer.api.PrinterLoaclService;
import com.peripheral.printer.api.PrinterParam;
import com.peripheral.printer.api.PrinterUtils;
import com.android.raimy.utils.Module.task.TaskMngBase;

/**
 * Created by raimy on 2018-04-19.
 */

public class TaskManager extends TaskMngBase implements IPrinterCallBack{
    private PrinterLoaclService mPrinterLoaclService=null;
    private ServiceConnection conn;
    private Context mAppContext;

    public TaskManager(Context context){
        mAppContext = context;
    }

    public void Init(){
        conn = new ServiceConnection() {
            @Override
            public void onServiceConnected(ComponentName name, IBinder service) {
                if (mPrinterLoaclService==null) {
                    PrinterLoaclService.PrinterLocalBinder binder =
                            (PrinterLoaclService.PrinterLocalBinder)service;
                    mPrinterLoaclService = binder.GetService();
                    mPrinterLoaclService.RegistCallBack(TaskManager.this);
                }
            }

            @Override
            public void onServiceDisconnected(ComponentName name) {

            }
        };

        final Intent intent = new Intent(mAppContext, PrinterLoaclService.class);
        mAppContext.bindService(intent, conn, Service.BIND_AUTO_CREATE);
    }

    public void DoGridDoorStateChange(int nGridId, int State){
        if(mCurTask!=null){
           mCurTask.DoGridDoorStateChange(nGridId, State);
        }
    }

    @Override
    public void OnCallBackFunc(PrinterParam printerParam) {

    }

    public void PrinterQrCode(String strQR){
        PrinterParam param = new PrinterParam(PrinterUtils.COMMU_SERIAL);
        param.mOpType = PrinterUtils.OpType_Connect;
        param.mIdent = "/dev/ttyS1";
        param.mStrParam1 = "/dev/ttyS1";
        param.mIntParam1 = 115200;

        int totalTime = 2000;
        int sum = 0;
        while (mPrinterLoaclService==null && sum<=totalTime){
            try {
                Thread.sleep(500);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            sum+=500;
        }

        mPrinterLoaclService.Operate(param);


        PrinterParam param1 = new PrinterParam(PrinterUtils.COMMU_SERIAL);
        param1.mOpType = PrinterUtils.OpType_PrintQR;
        param1.mIdent = "/dev/ttyS1";
        param1.mStrParam1 = strQR;
        mPrinterLoaclService.Operate(param1);

    }

}
