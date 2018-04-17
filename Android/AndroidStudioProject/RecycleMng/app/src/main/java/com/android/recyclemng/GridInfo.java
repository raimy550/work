package com.android.recyclemng;

import java.io.Serializable;

/**
 * Created by raimy on 2018-03-26.
 */

public class GridInfo implements Serializable{
    private  String name;
    private  String number;
    private  String address;
    private  String boxCount;
    private  String usedCount;
    private  String status;
    private  String createdAt;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getNumber() {
        return number;
    }

    public void setNumber(String number) {
        this.number = number;
    }

    public String getAddress() {
        return address;
    }

    public void setAddress(String address) {
        this.address = address;
    }

    public String getBoxCount() {
        return boxCount;
    }

    public void setBoxCount(String boxCount) {
        this.boxCount = boxCount;
    }

    public String getUsedCount() {
        return usedCount;
    }

    public void setUsedCount(String usedCount) {
        this.usedCount = usedCount;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public String getCreatedAt() {
        return createdAt;
    }

    public void setCreatedAt(String createdAt) {
        this.createdAt = createdAt;
    }

    public String getModifiedAt() {
        return modifiedAt;
    }

    public void setModifiedAt(String modifiedAt) {
        this.modifiedAt = modifiedAt;
    }

    private  String modifiedAt;


}
