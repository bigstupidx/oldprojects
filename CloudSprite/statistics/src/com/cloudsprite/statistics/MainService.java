package com.cloudsprite.statistics;

import java.io.IOException;

import org.apache.http.HttpResponse;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.util.EntityUtils;

import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.IBinder;

public class MainService extends Service {
	final String pref_name = "statistics";
	final String uploaded_name = "uploaded";
	final String reg_url = "http://kofphptest.sinaapp.com/reg.php";

	@Override
	public IBinder onBind(Intent arg0) {
		return null;
	}

	@Override
	public void onCreate() {
		super.onCreate();
	}

	@Override
	public int onStartCommand(Intent intent, int flags, int startId) {
		// 检查是否已经上传过信息
		SharedPreferences setting = this.getSharedPreferences(pref_name,
				MODE_PRIVATE);
		boolean bUploaded = setting.getBoolean(uploaded_name, false);
		Logger.log("bUploaded = " + bUploaded);
		if (!bUploaded) {
			upload();
		}

		return super.onStartCommand(intent, flags, startId);
	}

	private void updateUploadFlag() {
		boolean ret;
		SharedPreferences setting = this.getSharedPreferences(pref_name,
				MODE_PRIVATE);
		ret = setting.edit().putBoolean(uploaded_name, true).commit();
		Logger.log("write preference ret " + ret);
	}

	private void upload() {
		// Can not access network in the main thread!
		new Thread() {
			public void run() {
				String urlParams = PhoneInfo.getUrlParams(MainService.this);
				String url = reg_url + urlParams;
				Logger.log("url = " + url);
				HttpClient httpClient = new DefaultHttpClient();
				HttpGet getMethod = new HttpGet(url);
				try {
					HttpResponse response = httpClient.execute(getMethod); // 发起GET请求
					int statusCode = response.getStatusLine().getStatusCode();
					Logger.log("resCode = " + statusCode); // 获取响应码
					Logger.log("result = "
							+ EntityUtils.toString(response.getEntity(),
									"utf-8"));// 获取服务器响应内容

					if (statusCode == 200) {
						updateUploadFlag();
					}
				} catch (ClientProtocolException e) {
					e.printStackTrace();
				} catch (IOException e) {
					e.printStackTrace();
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		}.start();
	}

	public static void startService(Context context) {
		Intent service = new Intent(context, MainService.class);
		context.startService(service);
	}
}