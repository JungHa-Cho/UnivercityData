package audio.record;

import java.text.SimpleDateFormat;
import java.util.LinkedList;

import android.media.AudioFormat;
import android.media.AudioRecord;
import android.media.MediaRecorder;
import android.util.Log;

public class RecordThread extends Thread
{	
	private AudioRecord recorder = null;
	private int bufferSizeInBytes = 0;
	private Object syncObject = new Object();
	private boolean isRecording = false;
	public static final int SAMPLING_FREQUENCY = 8000;
	private LinkedList<ReadResult> queue = new LinkedList<ReadResult>();
	
	private class ReadResult
	{
		public int sampleRead;
		public short[] buffer;
		public long timeStamp;
	}
	
	public void run()
	{
		SimpleDateFormat dayTime = new SimpleDateFormat("yyyy-mm-dd hh:mm:ss");
		consumerThread.start();
		Log.i("RecordThread", "Recorder Thread Start");
		while(isRecording && bufferSizeInBytes > 0) 
		{
			//Log.d("RecordThread", "RECORDING");
			if(recorder.getRecordingState() != AudioRecord.RECORDSTATE_RECORDING)
				break;
		
			try
			{
				short[] buffer = new short[bufferSizeInBytes / 2];
				//Log.i("buffersize",""+buffer.length);
				int numSamplesRead = recorder.read(buffer, 0, buffer.length);
				
				if(numSamplesRead == AudioRecord.ERROR_INVALID_OPERATION) 
				{
					continue;
				}
				else if(numSamplesRead == AudioRecord.ERROR_BAD_VALUE)
				{
					continue;
				}
				
				ReadResult result = new ReadResult();
				result.buffer = buffer;
				result.sampleRead = numSamplesRead;
				result.timeStamp = System.currentTimeMillis();
				
				synchronized(syncObject)
				{
					queue.add(result);
				}
				
				//Log.d("rrr",""+ queue.size());
				//Log.i("Audio", "hi");
			}
			catch(Exception recordException)
			{
				Log.d("RecordThread", recordException.toString());
				recordException.printStackTrace();
			}
		}
		recorder.stop();
		recorder.release();
	}
	
	private Thread consumerThread = new Thread()
	{
		public void run()
		{
			Log.i("RecordThread", "Consumer thread start");
			while(true)
			{
				//Log.d("RecordThread", "CONSUMMING");
				ReadResult top = null;
				synchronized(syncObject)
				{
					if(queue.size() > 0)
					{
						top = queue.poll();
					}
					else
					{
						if(!isRecording)
						{
							//onRecordEnded();
							Log.i("RecordThread", "Consumer thread ended.");
							break;
						}
					}
					//Log.d("consumer", ""+queue.size());
				}
				
				if(top != null)
				{
					dataArrival(top.timeStamp, top.buffer, top.sampleRead, top.buffer.length);
				}
				
				try 
				{
					sleep(50);//0.05√ 
				} 
				catch (InterruptedException e) 
				{
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				
			}
		}
	};
	
	protected void dataArrival(long timestamp, short[] data, int length, int frameLength)
	{
		/*String temp = "";
		for(int i = 0; i < data.length; i++)
		{
			temp = temp+data[i]+", ";
		}*/
		//Log.i("SampleSize", ""+temp);
		
		//Log.i("short[] data size", ""+data.length);
	}
	
	public void startRecord()
	{
		try
		{
			isRecording = false;
			if(recorder != null)
			{
				if(recorder.getRecordingState() == AudioRecord.RECORDSTATE_RECORDING)
				{
					return;
				}
			}
			else
			{
				if(initRecorder() == null)
					return;
			}
			recorder.startRecording();
			this.start();
			isRecording = true;
			
		}
		catch(Exception ex)
		{
			ex.printStackTrace();
			Log.d("RecordThread", ex.toString());
		}
	}
	
	private AudioRecord initRecorder()
	{
		try
		{
			bufferSizeInBytes = AudioRecord.getMinBufferSize(
					SAMPLING_FREQUENCY, 
	                AudioFormat.CHANNEL_IN_MONO, 
	                AudioFormat.ENCODING_PCM_16BIT);
			
			recorder = new AudioRecord(
					MediaRecorder.AudioSource.DEFAULT,
					SAMPLING_FREQUENCY,
					AudioFormat.CHANNEL_IN_MONO,
					AudioFormat.ENCODING_PCM_16BIT,
					bufferSizeInBytes * 4);
		}
		catch(IllegalArgumentException ex)
		{
			ex.printStackTrace();
			Log.d("RecordThread", ex.toString());
		}
		Log.i("RecordThread", "bufferSizeInBytes : "+bufferSizeInBytes+" \nSampleRate : "+recorder.getSampleRate() + "\nBufferSize : "+bufferSizeInBytes/2);
		return recorder;
	}
	
	public void stopRecord(){
		isRecording = false;
	}
}
