package audio.record;

import android.util.Log;
import audio.record.Feature;
import math.*;

import java.util.Arrays;

public class AudioFeaturesExtractor 
{
	private MFCC featureMFCC;
	public FFT featureFFT;
	private Window featureWin;
	private int bufferSamples;
	private static int[] freqBandIdx = null;

	public AudioFeaturesExtractor() 
	{
		Log.i("AudioFeaturesExtractor", "audio feature");
		featureMFCC = new MFCC(Constants.FFT_SIZE, Constants.MFCCS_VALUE,Constants.MEL_BANDS, Constants.RECORDER_SAMPLERATE);
		featureFFT = new FFT(Constants.FFT_SIZE);
		featureWin = new Window(bufferSamples);
		freqBandIdx = new int[Constants.FREQ_BANDEDGES.length];
		
		for (int i = 0; i < Constants.FREQ_BANDEDGES.length; i++) 
		{
			freqBandIdx[i] = Math.round((float) Constants.FREQ_BANDEDGES[i] * ((float) Constants.FFT_SIZE / (float) Constants.RECORDER_SAMPLERATE));
		}
	}

	public Feature extractFeatures(short [] data) 
	{
		//Log.i("AudioFeaturesExtractor", "extractFeatures");
		Feature feature = new Feature();
		bufferSamples = data.length;
		short data16bit[] = data;
		int readAudioSamples = data.length;
		byte data8bit[] = new byte[bufferSamples * 2];
		double fftBufferR[] = new double[Constants.FFT_SIZE];
		double fftBufferI[] = new double[Constants.FFT_SIZE];
		double featureCepstrum[] = new double[Constants.MFCCS_VALUE];

		if (readAudioSamples > 0) 
		{
			double fN = (double) readAudioSamples;

			// Convert shorts to 8-bit bytes for raw audio output
			for (int i = 0; i < bufferSamples; i++) 
			{
				data8bit[i * 2] = (byte) data16bit[i];
				data8bit[i * 2 + 1] = (byte) (data16bit[i] >> 8);
			}
			// writeLogTextLine("Read " + readAudioSamples + " samples");

			// L1-norm
			double accum = 0;
			for (int i = 0; i < readAudioSamples; i++) 
			{
				accum += Math.abs((double) data16bit[i]);
			}
			feature.setL1Norm((accum / fN));

			// L2-norm
			accum = 0;
			for (int i = 0; i < readAudioSamples; i++) 
			{
				accum += (double) data16bit[i] * (double) data16bit[i];
			}
			feature.setL2Norm(Math.sqrt(accum / fN));

			// Linf-norm
			accum = 0;
			for (int i = 0; i < readAudioSamples; i++) 
			{
				accum = Math.max(Math.abs((double) data16bit[i]), accum);
			}
			feature.setLinfNorm(Math.sqrt(accum));

			// Frequency analysis
			Arrays.fill(fftBufferR, 0);
			Arrays.fill(fftBufferI, 0);

			// Convert audio buffer to doubles
			for (int i = 0; i < readAudioSamples; i++) 
			{
				fftBufferR[i] = data16bit[i];
			}

			// In-place windowing
			featureWin.applyWindow(fftBufferR);
			
			/*String s = "";
			for(int i = 0; i < fftBufferR.length ; i++)
			{
				s = s + fftBufferR[i] + ", ";
			}
			Log.i("AudioFeaturesExtractor", s);*/
			
			// In-place FFT
			featureFFT.fft(fftBufferR, fftBufferI);

			/*String s = "";
			for(int i = 0; i < fftBufferR.length ; i++)
			{
				s = s + fftBufferI[i] + ", ";
			}
			Log.i("AudioFeaturesExtractor", s);*/
			
			// Get PSD across frequency band ranges
			double[] psdAcrossFrequencyBands = new double[Constants.FREQ_BANDEDGES.length - 1];
			
			for (int b = 0; b < (Constants.FREQ_BANDEDGES.length - 1); b++)
			{
				int j = freqBandIdx[b];
				int k = freqBandIdx[b + 1];
				accum = 0;
				for (int h = j; h < k; h++) 
				{
					accum += fftBufferR[h] * fftBufferR[h] + fftBufferI[h] * fftBufferI[h];
				}
				psdAcrossFrequencyBands[b] = accum / ((double) (k - j));
			}

			feature.setPsdAcrossFrequencyBands(psdAcrossFrequencyBands);

			// Get MFCCs
			featureCepstrum = featureMFCC.cepstrum(fftBufferR, fftBufferI);
			feature.setMfccs(featureCepstrum);
		}
		return feature;
	}

}
