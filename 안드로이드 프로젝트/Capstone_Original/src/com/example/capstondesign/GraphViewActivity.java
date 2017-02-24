package com.example.capstondesign;

import java.text.SimpleDateFormat;
import java.util.Arrays;
import java.util.Date;

import math.Constants;
import math.FFT;
import android.app.Activity;
import android.content.pm.ActivityInfo;
import android.graphics.Color;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.Window;
import android.view.WindowManager;
import android.widget.LinearLayout;
import audio.record.AudioFeaturesExtractor;
import audio.record.FeaturesMatchFinderTask;
import audio.record.RecordThread;

import com.jjoe64.graphview.GraphView;
import com.jjoe64.graphview.GraphView.GraphViewData;
import com.jjoe64.graphview.BarGraphView;
import com.jjoe64.graphview.GraphViewSeries;
import com.jjoe64.graphview.LineGraphView;

public class GraphViewActivity extends Activity
{
	private final Handler mHandler = new Handler();
    private Runnable mTimer1;
    private Runnable mTimer2;
    GraphViewSeries exampleSeries;
    private RecordThread recordThread;
    private double graph2LastXValue = 5d;
    private AudioFeaturesExtractor featuresExtractor = new AudioFeaturesExtractor();
    double fftBufferR[] = new double[Constants.FFT_SIZE];
	double fftBufferI[] = new double[Constants.FFT_SIZE];
	public FFT featureFFT = new FFT(Constants.FFT_SIZE);
	
    private double getRandom() {
        double high = 3;
        double low = 0.5;
        return Math.random() * (high - low) + low;
    }
    
	@Override
	protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
		setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
		//getWindow().getDecorView().setBackgroundColor(Color.BLACK);
		
		setContentView(R.layout.graphs);
		recordThread = new RecordThread();
		// init example series data
		exampleSeries = new GraphViewSeries(new GraphViewData[] {
				new GraphViewData(1, 2.0d),
				new GraphViewData(2, 1.5d),
				new GraphViewData(3, 2.5d), 
				new GraphViewData(4, 1.0d)});
		 
		GraphView graphView = new BarGraphView(this, "GraphViewDemo");
		graphView.addSeries(exampleSeries); // data
		
		graphView.setViewPort(1, 1920);
        graphView.setScalable(true);
       
		
		LinearLayout layout = (LinearLayout) findViewById(R.id.graph1);
		layout.addView(graphView);
        // draw sin curve
	}

	@Override
	protected void onPause() 
	{
		mHandler.removeCallbacks(mTimer1);
		mHandler.removeCallbacks(mTimer2);
		super.onPause();
	}
	 

	@Override
	protected void onResume() {
		super.onResume();
		
		recordThread = new RecordThread()
		{
			int Index = 0;
			@Override
			protected void dataArrival(long timestamp, short[] data, int length, int frameLength) 
			{
				super.dataArrival(timestamp, data, length, frameLength);
				if (Index % 5 == 0)
				{	
					//featuresExtractor.extractFeatures(data);
					// Frequency analysis
					Arrays.fill(fftBufferR, 0);
					Arrays.fill(fftBufferI, 0);
					
					for (int i = 0; i < data.length; i++) 
					{
						fftBufferR[i] = data[i];
					}
					
					double[] window = new double[data.length];
					for(int i = 0; i < data.length; i++)
					{
						window[i] = 0.54 - 0.46*Math.cos(2*Math.PI*(double)i/((double)data.length-1));
					}
					
					for (int i = 0; i < data.length; i ++)
					{
						fftBufferR[i] *= window[i];
					}
					
	/*				String s = "";
					for(int i = 0; i < fftBufferR.length ; i++)
					{
						s = s + fftBufferR[i] + ", ";
					}
					Log.i("AudioFeaturesExtractor", s);*/
					
					featureFFT.fft(fftBufferR, fftBufferI);
/*					
					s = "";
					for(int i = 0; i < fftBufferR.length ; i++)
					{
						s = s + fftBufferR[i] + ", ";
					}
					Log.i("AudioFeaturesExtractor", s);*/
					
					Log.i("", ""+data.length);
				}
				if (Index == 100) {
					Index = 0;
				}
				Index++;
			}
		};
		recordThread.startRecord();
		
		
		mTimer1 = new Runnable() {
			@Override
			public void run() {
				exampleSeries.resetData
				(
						new GraphViewData[] 
						{
							new GraphViewData(1, getRandom()),
							new GraphViewData(2, getRandom()),
							new GraphViewData(3, getRandom()), 
							new GraphViewData(4, getRandom()),
							new GraphViewData(5, getRandom()),
							new GraphViewData(6, getRandom())
						}
				);
				mHandler.postDelayed(this, 300);
			}
		};
		mHandler.postDelayed(mTimer1, 300);

		
		mTimer2 = new Runnable() {
			@Override
			public void run() {
				graph2LastXValue += 1d;
				exampleSeries.appendData(new GraphViewData(graph2LastXValue, getRandom()), true, 10);
				mHandler.postDelayed(this, 200);
			}
		};
		mHandler.postDelayed(mTimer2, 1000);
	}
}
