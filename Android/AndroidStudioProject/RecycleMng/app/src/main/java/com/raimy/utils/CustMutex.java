package com.raimy.utils;

public class CustMutex  
{  
    private boolean syncLock;  
      
    ////////////////////////////////////////////////  
    //  Constructor  
    ////////////////////////////////////////////////  
  
    public CustMutex()  
    {  
        syncLock = false;  
    }  
      
    ////////////////////////////////////////////////  
    //  lock  
    ////////////////////////////////////////////////  
      
    public synchronized void lock()  
    {  
        while(syncLock == true) {  
            try {  
                wait();  
            }  
            catch (Exception e) {  
            	e.printStackTrace();
            };  
        }  
        syncLock = true;  
    }  
  
    public synchronized void unlock()  
    {  
        syncLock = false;  
        notifyAll();  
    }  
  
}  