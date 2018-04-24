package com.android.clothingrecycle.Data;

import android.support.annotation.NonNull;

import java.util.Comparator;

/**
 * Created by raimy on 2018-04-23.
 */

public class Grid implements Comparable<Grid>{
    //箱子型号小，中，大
    public final static int Grid_Type_None = -1;
    public final static int Grid_Type_small = 0;
    public final static int Grid_Type_normal = 1;
    public final static int Grid_Type_big = 2;

    //箱子状态
    public final static int Grid_State_None = -1;
    public final static int Grid_State_Empty = 0;
    public final static int Grid_State_Used = 1;
    //门状态
    public final static int Door_state_None = -1;
    public final static int Door_state_close = 0;
    public final static int Door_state_open = 1;
    public final static int Door_state_cleaning = 2;

    private int gridNo;//箱号
    private int gridType;//箱型号
    private int gridState;//箱状态
    private int doorState;//门状态

    public Grid(){
        gridNo = 0;
        gridType = Grid_Type_normal;
        gridState = Grid_State_Empty;
        doorState = Door_state_close;
    }

    public int getGridNo() {
        return gridNo;
    }

    public void setGridNo(int gridNo) {
        this.gridNo = gridNo;
    }

    public int getGridType() {
        return gridType;
    }

    public void setGridType(int gridType) {
        this.gridType = gridType;
    }

    public int getGridState() {
        return gridState;
    }

    public void setGridState(int gridState) {
        this.gridState = gridState;
    }

    public int getDoorState() {
        return doorState;
    }

    public void setDoorState(int doorState) {
        this.doorState = doorState;
    }

    @Override
    public int compareTo(@NonNull Grid o) {
        return this.gridNo - o.gridNo;
    }

}
