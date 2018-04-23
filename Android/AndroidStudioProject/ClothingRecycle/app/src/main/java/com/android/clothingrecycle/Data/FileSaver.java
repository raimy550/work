package com.android.clothingrecycle.Data;

import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.TypeReference;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;

/**
 * Created by raimy on 2018-03-23.
 */

public class FileSaver {
    private String mStrFilePath;

    public FileSaver(String filePath){
        mStrFilePath = filePath;
    }

    public boolean UpdateData(FileOutputStream outputStream){

        return true;
    }

    public Cabinet ParseFile(){
        Cabinet ret = null;
        File file = new File(mStrFilePath);
        String laststr="";
        BufferedReader reader=null;
        if(file.exists()){
            FileInputStream stream;
            try {
                FileInputStream in = new FileInputStream(file);
                reader=new BufferedReader(new InputStreamReader(in,"UTF-8"));// 读取文件
                String tempString=null;
                while((tempString=reader.readLine())!=null){
                    laststr=laststr+tempString;
                }
                reader.close();
            } catch (IOException e) {
                e.printStackTrace();
            }finally{
                if(reader!=null){
                    try{
                        reader.close();
                    }catch(IOException el){
                    }
                }
            }

            ret = JSON.parseObject(laststr, new TypeReference<Cabinet>() {});
            if(ret!=null){
                ret.SortDataByKey();
            }
        }
        return ret;
    }

    public void SaveFile(Cabinet cabinet){
        String str = cabinet.GetJsonData();
        try {
            File file = new File(mStrFilePath);
            if (!file.exists()) {
                File dir = new File(file.getParent());
                dir.mkdirs();
                file.createNewFile();
            }
            FileOutputStream outStream = new FileOutputStream(file);
            outStream.write(str.getBytes());
            outStream.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
