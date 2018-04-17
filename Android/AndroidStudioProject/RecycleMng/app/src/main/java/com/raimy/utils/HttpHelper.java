package com.raimy.utils;
import com.squareup.okhttp.Call;
import com.squareup.okhttp.Callback;
import com.squareup.okhttp.OkHttpClient;
import com.squareup.okhttp.Request;
import com.squareup.okhttp.RequestBody;
import com.squareup.okhttp.Response;

import java.io.IOException;
import java.util.Iterator;
import java.util.LinkedHashMap;

/**
 * Created by raimy on 2018-03-20.
 */

public class HttpHelper {
    private final static String TAG="HttpHelper";

    public static String SyncGet(String strUrl){
        OkHttpClient client = new OkHttpClient();
        Request request = new Request.Builder().get().url(strUrl).build();

        Response response;
        String strRet = "";

        try {
            Call call = client.newCall(request);
            response = call.execute();
            strRet = response.body().toString();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return strRet;
    }

    public static void AsyncGet(String strUrl,  Callback callBack){
        OkHttpClient client = new OkHttpClient();

        Request.Builder builder = new Request.Builder().get().url(strUrl);
        Request  request = builder.build();

        Call call = client.newCall(request);

        call.enqueue(callBack);
    }

    public static void AsyncDownLoadFile(String strUrl, Callback callBack){
        AsyncGet(strUrl, callBack);
    }

    public static void Post(String strUrl, RequestBody body, Callback callBack){
        OkHttpClient client = new OkHttpClient();
        final Request request = new Request.Builder()
                .url(strUrl)
                .post(body)
                .build();

        Call call = client.newCall(request);
        call.enqueue(callBack);
    }

    public static String attachHttpGetParams(String url, LinkedHashMap<String,String> params){

        Iterator<String> keys = params.keySet().iterator();
        Iterator<String> values = params.values().iterator();
        StringBuffer stringBuffer = new StringBuffer();
        stringBuffer.append("?");

        for (int i=0;i<params.size();i++ ) {
            stringBuffer.append(keys.next()+"="+values.next());
            if (i!=params.size()-1) {
                stringBuffer.append("&");
            }
        }

        return url + stringBuffer.toString();
    }


    /**
     * 为HttpGet 的 url 方便的添加1个name value 参数。
     * @param url
     * @param name
     * @param value
     * @return
     */
    public static String attachHttpGetParam(String url, String name, String value){
        return url + "?" + name + "=" + value;
    }


}
