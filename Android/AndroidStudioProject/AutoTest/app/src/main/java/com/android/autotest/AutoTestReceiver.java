package com.android.autotest;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

import java.io.File;

/**
 * Created by raimy on 2018-04-10.
 */

public class AutoTestReceiver extends BroadcastReceiver{
    private final String ACTION_BOOT = "android.intent.action.BOOT_COMPLETED";
    private final String ACTION_MOUNT = "android.intent.action.MEDIA_MOUNTED";
    private final String ACTION_MEDIA_EJECT = "android.intent.action.MEDIA_EJECT";
    private final String CONFIG_PATH = "/storage/sdcard1/4418SpTestTool.xml";

    @Override
    public void onReceive(Context context, Intent intent) {
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
