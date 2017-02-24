package AstarAlgorithm;

public class Node {
	int x, y;
	
	public Node(int i, int j)
	{
		x = i;
		y = j;
	}
	
	public boolean equals(Object obj) 
	{
		if(obj instanceof Node) 
		{
			Node n = (Node) obj;
			return (x == n.x && y == n.y);
		}
		else return false;
	}
	
	public int getX(){return x;}
	public int getY(){return y;}
}
