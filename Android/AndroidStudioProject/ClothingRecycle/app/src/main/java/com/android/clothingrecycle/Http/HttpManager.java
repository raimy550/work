package com.android.clothingrecycle.Http;

import com.android.raimy.utils.HttpHelper;
import com.squareup.okhttp.Callback;
import com.squareup.okhttp.FormEncodingBuilder;
import com.squareup.okhttp.RequestBody;

import java.util.LinkedHashMap;

/**
 * Created by raimy on 2018-03-22.
 */

public class HttpManager {
    public final static String Http_Test = "http://192.168.7.150:5801";
    public final static String Http_Busi = "http://tsi.icarcloud.net:4500/iCabinet";
    public final static String Url_registerCabinet= Http_Busi+"/api/v1.0.0/registerCabinet";
    public final static String Url_openCabinetQRCodes=Http_Busi+"/api/v1.0.0/openCabinetQRCodes";
    public final static String Url_scanQRCodeOpenBox=Http_Busi+"/api/v1.0.0/scanQRCodeOpenBox";
    public final static String Url_openAllBoxes=Http_Busi+"/api/v1.0.0/openAllBoxes";
    public final static String Url_uploadCabinetStatus=Http_Busi+"/api/v1.0.0/uploadCabinetStatus";
    public final static String Url_cabinetsByUUid=Http_Busi+"/api/v1.0.0/users/:userUUID/cabinets";

    public final static String Rsp_openCabinetQRCodes_Key_QRUrl = "QRCodeUrl";

    public com.squareup.okhttp.Callback mCallback;

    public HttpManager(com.squareup.okhttp.Callback callBack){
        mCallback = callBack;
    }

    public void HttpGetQRCode(String cabinetNumber, int gridNumber){
        String strUrl = HttpManager.Url_openCabinetQRCodes;
        LinkedHashMap<String, String> headers = new LinkedHashMap<String, String>();
        headers.put("cabinetNumber", cabinetNumber);

        headers.put("boxNumber", Integer.toString(gridNumber));
        String str = HttpHelper.attachHttpGetParams(strUrl, headers);
        HttpHelper.AsyncDownLoadFile(str,mCallback);
    }

    public void HttpUploadGridStatus(String cabinetNumber, int boxCount, int usedCount){
        String strUrl = HttpManager.Url_uploadCabinetStatus;
        RequestBody body = new FormEncodingBuilder()
                .add("cabinetNumber", cabinetNumber)
                .add("boxCount", Integer.toString(boxCount))
                .add("usedCount",Integer.toString(usedCount))
                .build();

        HttpHelper.Post(strUrl, body, mCallback);
    }

    public void HttpRegisterCabinet(String cabinetNumber, String registrationId, int boxCount, int usedCount){
        String strUrl = HttpManager.Url_registerCabinet;
        RequestBody body = new FormEncodingBuilder()
                .add("cabinetNumber", cabinetNumber)
                .add("registrationId", registrationId)
                .add("boxCount", Integer.toString(boxCount))
                .add("usedCount",Integer.toString(usedCount))
                .build();

        HttpHelper.Post(strUrl, body, mCallback);
    }

    public void HttpDownloadQrCode(String Url, Callback callback){
        HttpHelper.AsyncDownLoadFile(Url, callback);
    }

}
