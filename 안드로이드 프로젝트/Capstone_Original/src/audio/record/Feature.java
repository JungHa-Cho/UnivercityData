package audio.record;

import java.util.Arrays;

public class Feature {
	//private variables
    int id;
    private String name;
    private double l1Norm;
    private double l2Norm;
    private double linfNorm;
    private double [] mfccs;
    private String mfccsAsString;
    private double [] psdAcrossFrequencyBands;
    private String psdAcrossFrequencyBandsAsString;
    private double timestamp;
    private double diffSecs;
    
	public Feature() 
	{   // TODO Auto-generated constructor stub
		mfccs = new double[12];
		psdAcrossFrequencyBands = new double[4];
	}

    public int getID(){return this.id;}
    public void setID(int id){this.id = id;}
    public String getName(){return this.name;}
    public void setName(String name){this.name = name;}
    public double getL1Norm() {return l1Norm;}
    public void setL1Norm(double l1Norm) {this.l1Norm = l1Norm;}
    public double getL2Norm() {return l2Norm;}
    public void setL2Norm(double l2Norm) {this.l2Norm = l2Norm;}
    public double getLinfNorm() {return linfNorm;}
    public void setLinfNorm(double linfNorm) {this.linfNorm = linfNorm;}
    public double [] getMfccs() {return mfccs;}
    public void setMfccs(double [] mfccs) {this.mfccs = mfccs;}
    public double [] getPsdAcrossFrequencyBands() {return psdAcrossFrequencyBands;}
    public void setPsdAcrossFrequencyBands(double [] psdAcrossFrequencyBands) {this.psdAcrossFrequencyBands = psdAcrossFrequencyBands;}
    public double getTimestamp() {return timestamp;}
    public void setTimestamp(double timestamp) {this.timestamp = timestamp;}
    public double getDiffSecs() {return diffSecs;}
    public void setDiffSecs(double diffSecs) {this.diffSecs = diffSecs;}
	public String getPsdAcrossFrequencyBandsAsString() {return psdAcrossFrequencyBandsAsString;}
	public void setPsdAcrossFrequencyBandsAsString(String psdAcrossFrequencyBandsAsString) {this.psdAcrossFrequencyBandsAsString = psdAcrossFrequencyBandsAsString;}
    
    public String getMfccsAsString() 
    {
    	if(mfccsAsString==null)
    	{
    		mfccsAsString = Arrays.toString(mfccs);
    	}
		return mfccsAsString;
	}

    public void setMfccsAsString(String mfccsAsString) 
    {
    	String cleanString = mfccsAsString.replace("[", "").replace("]", ""); //remove the right bracket
    	String[] ary = cleanString.split(",");
    	
    	for (int i = 0; i < ary.length; i++) 
    	{
			mfccs[i] = Double.parseDouble(ary[i]);
		}
    	
		this.mfccsAsString = mfccsAsString;
	}
}
