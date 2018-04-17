package com.android.recyclemng;

import java.io.Serializable;
import java.util.Map;

/**业务参数，供界面与logic使用
 * Created by raimy on 2018-03-22.
 */

public class LogicParam implements Serializable{
    public final static int Update_GridInfo =1;

    interface LogicCallBack{
        void OnLogicCallBack(int eType);
    }
}
