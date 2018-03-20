/**
 * 
 */
package com.peripheral.printer.commu;

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
