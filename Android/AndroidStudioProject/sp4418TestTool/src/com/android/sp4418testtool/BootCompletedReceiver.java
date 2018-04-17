package com.android.sp4418testtool;



import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.Environment;
import android.util.Log;

import java.io.File;

public class BootCompletedReceiver extends BroadcastReceiver {

    private final String ACTION_BOOT = "android.intent.action.BOOT_COMPLETED";
    private final String ACTION_MOUNT = "android.intent.action.MEDIA_MOUNTED";
    private final String ACTION_MEDIA_EJECT = "android.intent.action.MEDIA_EJECT";

    private final String CONFIG_PATH = "/storage/sdcard1/4418SpTestTool.xml";

    @Override
    public void onReceive(Context context, Intent intent) {
        // TODO: This method is called when the BroadcastReceiver is receiving
        // an Intent broadcast.
        Log.i("hujz", intent.getAction());
        if (ACTION_BOOT.equals(intent.getAction())) {
            // 开机广播， 读取配置文件

        } else if (ACTION_MOUNT.equals(intent.getAction())) {
            // SD 卡挂载， 读取配置文件

            File file = new File(CONFIG_PATH);
            if (file.exists()) {
                Intent main = new Intent(context, MainActivity.class);
                main.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                context.startActivity(main);
            }
        }
    }


}
