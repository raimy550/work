/**
 * 
 */
package com.android.autotest.comm;

/**
 * @author raimy
 *
 */
public abstract class CommuBase {
	public abstract boolean Connect();
	public abstract boolean DisConnect();
	public abstract boolean Write(String data);
	public abstract boolean Write(byte[] data);
	public abstract byte[] Read();
}
