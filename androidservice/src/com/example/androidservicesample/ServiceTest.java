package com.example.androidservicesample;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;


public class ServiceTest extends Service {

	@Override
	public IBinder onBind(Intent intent) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public int onStartCommand(Intent intent, int flags, int startId) {
		// TODO Auto-generated method stub
		System.out.println("Service Start");
		return super.onStartCommand(intent, flags, startId);
	}

	@Override
	public void onDestroy() {
		// TODO Auto-generated method stub
		System.out.println("Service Finish");
		super.onDestroy();
	}

}
