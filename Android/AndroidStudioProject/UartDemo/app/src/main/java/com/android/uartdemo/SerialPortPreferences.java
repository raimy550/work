/*
 * Copyright 2009 Cedric Priscal
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. 
 */

package com.android.uartdemo;

import java.io.File;
import java.util.Vector;

import com.android.uartdemo.R;

import android.os.Bundle;
import android.preference.ListPreference;
import android.preference.Preference;
import android.preference.Preference.OnPreferenceChangeListener;
import android.preference.PreferenceActivity;

public class SerialPortPreferences extends PreferenceActivity {


	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		 
	      String str;
	      Vector<String> uart_devices = new Vector<String>();
	      for(int i=0; i<10; i++) {
	    	  str = "/dev/ttyS"+i;
	    	  if(fileIsExists(str))
	    		  uart_devices.add(str);
	      }
	      String[]  entries =    uart_devices.toArray(new String[uart_devices.size()]);
	   
		addPreferencesFromResource(R.xml.serial_port_preferences);

		// Devices
		final ListPreference devices = (ListPreference)findPreference("DEVICE");
		devices.setEntries(entries);
        devices.setEntryValues(entries);
		devices.setSummary(devices.getValue());
		devices.setOnPreferenceChangeListener(new OnPreferenceChangeListener() {
			public boolean onPreferenceChange(Preference preference, Object newValue) {
				preference.setSummary((String)newValue);
				return true;
			}
		});

		// Baud rates
		final ListPreference baudrates = (ListPreference)findPreference("BAUDRATE");
		baudrates.setSummary(baudrates.getValue());
		baudrates.setOnPreferenceChangeListener(new OnPreferenceChangeListener() {
			public boolean onPreferenceChange(Preference preference, Object newValue) {
				preference.setSummary((String)newValue);
				return true;
			}
		});
		//Parity check
		final ListPreference odd_even = (ListPreference)findPreference("PARITY_CHECK");
		odd_even.setSummary(odd_even.getValue());
		odd_even.setOnPreferenceChangeListener(new OnPreferenceChangeListener() {
			public boolean onPreferenceChange(Preference preference, Object newValue) {
				preference.setSummary((String)newValue);
				return true;
			}
		});
	}
	public boolean fileIsExists(String path){
        try{
                File f=new File(path);
                if(!f.exists()){
                        return false;
                }
                
        }catch (Exception e) {
                // TODO: handle exception
                return false;
        }
        return true;
}
}
