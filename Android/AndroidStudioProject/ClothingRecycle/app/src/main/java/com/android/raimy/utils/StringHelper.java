/**
 * 
 */
package com.android.raimy.utils;

/**
 * @author Administrator
 *
 */
public class StringHelper {
	
	/** 
     * Converts a byte array into hexadecimal string. 
     *  
     * @param bArray the byte array to be convert.
     * @return the hexadecimal string
     */  
	public static final String bytesToHexString(byte[] bArray) {  
        StringBuffer sb = new StringBuffer(bArray.length);  
        String sTemp;  
        for (int i = 0; i < bArray.length; i++) {  
            sTemp = Integer.toHexString(0xFF & bArray[i]);  
            if (sTemp.length() < 2) {
                sb.append("+" + 0);  
                sb.append(sTemp.toUpperCase());
            } else {
            	sb.append("+" + sTemp.toUpperCase());  
			}
        }  
        return sb.toString().replaceFirst("\\+", "");  
    }
	
	/** 
     * Converts a byte array into hexadecimal string. 
     *  
     * @param bArray the byte array to be convert.
     * @return the hexadecimal string
     */  
	public static final String bytesToHexString(byte[] bArray, int nLen) {  
        StringBuffer sb = new StringBuffer(nLen);  
        String sTemp;  
        for (int i = 0; i < nLen; i++) {  
            sTemp = Integer.toHexString(0xFF & bArray[i]);  
            if (sTemp.length() < 2) {
                sb.append("+" + 0);  
                sb.append(sTemp.toUpperCase());
            } else {
            	sb.append("+" + sTemp.toUpperCase());  
			}
        }  
        return sb.toString().replaceFirst("\\+", "");  
    }
	
	public static String byteToHexString(byte b) {
		StringBuilder stringBuilder = new StringBuilder("");
		int v = b & 0xFF;
		String hv = Integer.toHexString(v);
		if (hv.length() < 2) {
			stringBuilder.append(0);
		}
		stringBuilder.append(hv);
		return stringBuilder.toString();
	}
	
	public static byte[] hexStringToBytes(String hexString) {    
        if (hexString == null || hexString.equals("")) {    
            return null;    
        }    
        hexString = hexString.toUpperCase();    
        int length = hexString.length() / 2;    
        char[] hexChars = hexString.toCharArray();    
        byte[] d = new byte[length];    
        for (int i = 0; i < length; i++) {    
            int pos = i * 2;    
            d[i] = (byte) (charToByte(hexChars[pos]) << 4 | charToByte(hexChars[pos + 1]));    
        }    
        return d;    
    }    
	
	 public static byte charToByte(char c) {    
	    	return (byte) "0123456789ABCDEF".indexOf(c);     
	    } 
	
	public static int byteToIntForHigh(byte[] b, int digit) {

		int mask = 0xff;
		int temp = 0;
		int n = 0;
		for (int i = 0; i < digit; i++) {
			n <<= 8;
			temp = b[i] & mask;
			n |= temp;
		}
		return n;
	}
	
}
