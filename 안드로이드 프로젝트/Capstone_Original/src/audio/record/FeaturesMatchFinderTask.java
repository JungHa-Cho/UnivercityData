package audio.record;

import java.util.Comparator;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.PriorityQueue;

import android.os.AsyncTask;
import android.util.Log;
import android.widget.ArrayAdapter;
import android.widget.TextView;

//public class FeaturesMatchFinderTask extends AsyncTask<List<Feature>, Integer, String[]> {
public class FeaturesMatchFinderTask
{
	private String[] matches;
	private ArrayAdapter<String> adapter;
	private Feature feature;
	private PriorityQueue<Match> matchQueue;
	public LinkedList<Match> returnmatch;

	public FeaturesMatchFinderTask(int cnt, Feature feature)
	{
		//this.matches = matches;
		//this.adapter = adapter;
		matches = new String[cnt];
		returnmatch = new LinkedList<Match>();

		for (int i = 0; i < matches.length; i++) {
			matches[i] = "";
		}
		
		this.feature = feature;


		matchQueue = new PriorityQueue<FeaturesMatchFinderTask.Match>(new PriorityQueue<Match>(matches.length,new Comparator<Match>()
		{
				@Override
				public int compare(Match x, Match y) 
				{
					if (x.getMatchValue() < y.getMatchValue()) 
					{
						return -1;
					}
					if (x.getMatchValue() > y.getMatchValue()) 
					{
						return 1;
					}
					return 0;
				}
		}));
	}

	public String[] getPercent(List<Feature> params) 
	{
		try
		{
			List<Feature> features = params; // DB 저장된 MFCC Sample들 정보
			
			if (features == null || features.size() < 1)
				return null;

			HashMap<String, Double> map = new HashMap<String, Double>();

			double[] mfcc = feature.getMfccs(); // 현재 들어온 MFCC 정보

			for (Feature ft : features) // DB의 MFCC 정보들을  전부 다 검사
			{
				double[] spectrum = ft.getMfccs();
				double mse = 0;

				for (int i = 0; i < spectrum.length; i++) 
				{
					mse += Math.pow((spectrum[i] - mfcc[i]), 2); // MFCC들을 각각 12개의 개수들을 
				}
				
				mse /= spectrum.length; // 평균값 

				if (map.containsKey(ft.getName())) 
				{
					double closestVal = map.get(ft.getName()) < mse ? map.get(ft.getName()) : mse;
					map.put(ft.getName(), closestVal);
				} else {
					map.put(ft.getName(), mse);
				}

				// matchQueue.add( new Match(ft.getName(),0,
				// Math.abs(ft.getL1Norm() - feature.getL1Norm())));
			}

			double total = 0;
			
			for (String key : map.keySet()) 
			{
				total += map.get(key);
			}
			
			for (String key : map.keySet()) 
			{
				matchQueue.add(new Match(key, (map.get(key) * 100) / total, map.get(key)));
			}
			
			int size = matchQueue.size();
			
			for (int i = 0; i < size && i < matches.length; i++) 
			{
				Match match = matchQueue.poll();
				matches[i] = match.getName() + " : value = "+ String.format("%.2f", 100 - (match.getPercentage()))+ "%";
				match.setPercentage(100 - match.getPercentage());
				returnmatch.add(match);
			}

			//adapter.notifyDataSetChanged();
		} 
		catch (Exception e) 
		{
			Log.d(this.getClass().getName(), e.getMessage());
		}
		return matches;
	}

	public class Match 
	{
		public String name;
		public double percentage;
		public double matchValue;

		public Match(String name, double percentage, double matchValue) 
		{
			this.name = name;
			this.percentage = percentage;
			this.matchValue = matchValue;
		}

		String getName(){return name;}
		void setName(String name) {this.name = name;}
		double getPercentage() {return percentage;}
		void setPercentage(double percentage) {this.percentage = percentage;}
		double getMatchValue() {return matchValue;}
		void setMatchValue(double matchValue) {this.matchValue = matchValue;}
	}
}
