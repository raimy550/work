package com.raimy.utils;
import com.squareup.okhttp.Call;
import com.squareup.okhttp.Callback;
import com.squareup.okhttp.OkHttpClient;
import com.squareup.okhttp.Request;

import java.io.IOException;
/**
 * Created by raimy on 2018-03-20.
 */

public class HttpHelper {
    public static void SyncGet(String strUrl){
        OkHttpClient client = new OkHttpClient();
        Request request = new Request.Builder().get().url(strUrl).build();

        try {
            Call call = client.newCall(request);
            call.execute();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void AsyncGet(String strUrl, Callback callBack){
        OkHttpClient client = new OkHttpClient();
        Request request = new Request.Builder().get().url(strUrl).build();

        Call call = client.newCall(request);

        call.enqueue(callBack);
    }

    public static void AsyncDownLoadFile(String strUrl, Callback callBack){
        AsyncGet(strUrl, callBack);
    }


}
