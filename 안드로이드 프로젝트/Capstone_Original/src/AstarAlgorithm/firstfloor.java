package AstarAlgorithm;

public class firstfloor {
	public firstfloor(){};
public int[][] getRoomCoordi(){return RoomCoordinate;}
	
	public enum RoomNumber { ThreeZeroOne, ThreeZeroTwo, ThreeZeroThree, ThreeZeroFour, ThreeZeroFive, ThreeZeroSix, ThreeZeroSeven, ThreeZeroEight, ThreeZeroNine, ThreeOneZero, 
						      ThreeOneOne, ThreeOneTwo,  ThreeOneThree,  ThreeOneFour,  ThreeOneFive,  ThreeOneSix,  ThreeOneSeven,  ThreeOneEight,  ThreeOneNine,  ThreeTwoZero,  
					          ThreeTwoOne,  ThreeTwoTow,  ThreeTwoThree,  ThreeTwoFour,  ThreeTwoFive,  ThreeTwoSix,  ThreeTwoSeven,  ThreeTwoEight,  ThreeTwoNine,  ThreeThreeZero,
					        ThreeThreeOne, ThreeThreeTwo,ThreeThreeThree,ThreeThreeFour,ThreeThreeFive,ThreeThreeSix,ThreeThreeSeven,ThreeThreeEight, Elec, CenterFloor, RightFloor, Women, Men, Robby, LeftFloor}
	public int[][] RoomCoordinate = {{47, 14}, {42, 6}, {43, 28}, {1, 18}, {95, 18}};
	public boolean[][] getMap(){return map;}
	public boolean[][] map = 
		{
			{	
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, 
			}
			,
			{
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, false, false, false, false, false, false, false, 
				false, false, true, false, false, false, false, false, false, false, 
				false, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, 
			}
			,
			{
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, false, false, false, false, false, false, false, 
				false, false, true, false, false, false, false, false, false, false, 
				false, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, 
			}
			,
			{
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, false, false, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, false, false, false, false, false, false, false, 
				false, false, true, false, false, false, false, false, false, false, 
				false, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, 
			}
			,
			{
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, false, false, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, false, false, false, false, false, false, false, 
				false, false, true, false, false, false, false, false, false, false, 
				false, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, 
			}
			,
			{
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, false, false, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, false, false, false, false, false, false, false, 
				false, false, true, false, false, false, false, false, false, false, 
				false, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, 
			}
			,
			{
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, false, false, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, false, false, false, false, false, false, false, 
				false, false, true, false, false, false, false, false, false, false, 
				false, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, 
			}
			,
			{
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, false, false, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, false, false, false, false, false, false, false, 
				false, false, true, false, false, false, false, false, false, false, 
				false, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, 
			}
			,
			{
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, false, false, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, false, false, false, false, false, false, false, 
				false, false, true, false, false, false, false, false, false, false, 
				false, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, 
			}
			,
			{
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, false, false, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, false, false, false, false, false, false, false, 
				false, false, true, false, false, false, false, false, false, false, 
				false, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, 
			}
			,
			{
				true, true, true, false, false, true, false, false, false, false, 
				false, false, true, false, false, true, true, true, true, true, 
				true, true, false, false, true, false, false, true, false, false, 
				false, false, false, false, false, false, false, false, false, false, 
				true, false, false, false, false, false, true, false, false, false, 
				false, false, false, true, false, false, false, false, false, false, 
				false, false, true, false, false, false, false, false, false, false, 
				false, false, true, false, false, false, false, false, false, false, 
				false, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, 
			}
			,
			{
				true, true, true, false, false, true, false, false, false, false, 
				false, false, true, false, false, true, true, true, true, true, 
				true, true, false, false, true, false, false, true, false, false, 
				false, false, false, false, false, false, false, false, false, false, 
				true, false, false, false, false, false, true, false, false, false, 
				false, false, false, true, false, false, false, false, false, false, 
				false, false, true, false, false, false, false, false, false, false, 
				false, false, true, false, false, false, false, false, false, false, 
				false, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, 
			}
			,
			{
				true, true, true, false, false, true, false, false, false, false, 
				false, false, true, false, false, true, true, true, true, true, 
				true, true, false, false, true, false, false, true, false, false, 
				false, false, false, false, false, false, false, false, false, false, 
				true, false, false, false, false, false, true, false, false, false, 
				false, false, false, true, false, false, false, false, false, false, 
				false, false, true, false, false, false, false, false, false, false, 
				false, false, true, false, false, false, false, false, false, false, 
				false, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, 
			}
			,
			{
				true, true, true, false, false, true, false, false, false, false, 
				false, false, true, false, false, true, true, true, true, true, 
				true, true, false, false, true, false, false, true, false, false, 
				false, false, false, false, false, false, false, false, false, false, 
				true, false, false, false, false, false, true, false, false, false, 
				false, false, false, true, false, false, false, false, false, false, 
				false, false, true, false, false, false, false, false, false, false, 
				false, false, true, false, false, false, false, false, false, false, 
				false, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, 
			}
			,
			{
				true, true, true, false, false, true, false, false, false, false, 
				false, false, true, false, false, true, true, true, true, true, 
				true, true, false, false, true, false, false, true, false, false, 
				false, false, false, false, false, false, false, false, false, false, 
				true, false, false, false, false, false, true, false, false, false, 
				false, false, false, true, false, false, false, false, false, false, 
				false, false, true, false, false, false, false, false, false, false, 
				false, false, true, false, false, false, false, false, false, false, 
				false, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, 
			}
			,
			{
				true, true, true, false, false, true, false, false, false, false, 
				false, false, true, false, false, true, true, true, true, true, 
				true, true, false, false, true, false, false, true, false, false, 
				false, false, false, false, false, false, false, false, false, false, 
				true, false, false, false, false, false, true, false, false, false, 
				false, false, false, true, false, false, false, false, false, false, 
				false, false, true, false, false, false, false, false, false, false, 
				false, false, true, false, false, false, false, false, false, false, 
				false, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, 
			}
			,
			{
				true, true, true, false, false, true, false, false, true, true, 
				true, true, true, true, false, true, true, true, true, true, 
				true, true, false, false, true, false, true, true, true, true, 
				true, true, false, false, false, false, true, true, true, false, 
				true, false, false, false, false, false, true, false, false, true, 
				true, true, true, true, false, false, true, true, true, true, 
				true, false, true, false, false, true, true, true, true, true, 
				false, false, true, false, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, 
			}
			,
			{
				false, false, false, false, false, false, false, false, false, false, 
				false, false, false, false, false, false, false, false, false, false, 
				false, false, false, false, false, false, false, false, false, false, 
				false, false, false, false, false, false, false, false, false, false, 
				false, false, false, false, false, false, false, false, false, false, 
				false, false, false, false, false, false, false, false, false, false, 
				false, false, false, false, false, false, false, false, false, false, 
				false, false, false, false, false, false, false, false, false, false, 
				false, false, false, false, false, false, false, false, false, false, 
				false, false, false, false, false, false, 
			}
			,
			{
				false, false, false, false, false, false, false, false, false, false, 
				false, false, false, false, false, false, false, false, false, false, 
				false, false, false, false, false, false, false, false, false, false, 
				false, false, false, false, false, false, false, false, false, false, 
				false, false, false, false, false, false, false, false, false, false, 
				false, false, false, false, false, false, false, false, false, false, 
				false, false, false, false, false, false, false, false, false, false, 
				false, false, false, false, false, false, false, false, false, false, 
				false, false, false, false, false, false, false, false, false, false, 
				false, false, false, false, false, false, 
			}
			,
			{
				true, true, true, false, false, true, false, false, true, true, 
				true, true, true, false, false, true, false, false, false, false, 
				false, false, false, false, true, false, false, true, true, true, 
				true, true, false, false, true, false, false, true, true, true, 
				true, false, false, false, false, false, true, true, true, true, 
				true, true, true, true, false, false, true, true, true, true, 
				true, false, true, false, false, true, true, true, true, true, 
				false, false, true, false, true, true, true, true, true, false, 
				false, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, 
			}
			,
			{
				true, true, true, false, false, true, false, false, false, false, 
				false, false, false, false, false, true, false, false, false, false, 
				false, false, false, false, true, false, false, false, false, false, 
				false, false, false, false, true, false, false, true, true, true, 
				true, false, false, false, false, false, true, true, true, true, 
				true, true, true, true, false, false, false, false, false, false, 
				false, false, true, false, false, false, false, false, false, false, 
				false, false, true, false, false, false, false, false, false, false, 
				false, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, 
			}
			,
			{
				true, true, true, false, false, true, false, false, false, false, 
				false, false, false, false, false, true, false, false, false, false, 
				false, false, false, false, true, false, false, false, false, false, 
				false, false, false, false, true, false, false, true, true, true, 
				true, false, false, false, false, false, true, true, true, true, 
				true, true, true, true, false, false, false, false, false, false, 
				false, false, true, false, false, false, false, false, false, false, 
				false, false, true, false, false, false, false, false, false, false, 
				false, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, 
			}
			,
			{
				true, true, true, false, false, true, false, false, false, false, 
				false, false, false, false, false, true, false, false, false, false, 
				false, false, false, false, true, false, false, false, false, false, 
				false, false, false, false, true, false, false, true, true, true, 
				true, false, false, false, false, false, true, true, true, true, 
				true, true, true, true, false, false, false, false, false, false, 
				false, false, true, false, false, false, false, false, false, false, 
				false, false, true, false, false, false, false, false, false, false, 
				false, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, 
			}
			,
			{
				true, true, true, false, false, true, false, false, false, false, 
				false, false, false, false, false, true, false, false, false, false, 
				false, false, false, false, true, false, false, false, false, false, 
				false, false, false, false, true, false, false, true, true, true, 
				true, false, false, false, false, false, true, true, true, true, 
				true, true, true, true, false, false, false, false, false, false, 
				false, false, true, false, false, false, false, false, false, false, 
				false, false, true, false, false, false, false, false, false, false, 
				false, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, 
			}
			,
			{
				true, true, true, true, true, true, false, false, false, false, 
				false, false, false, false, false, true, false, false, false, false, 
				false, false, false, false, true, false, false, false, false, false, 
				false, false, false, false, true, false, false, true, true, true, 
				true, false, false, false, false, false, true, true, true, true, 
				true, true, true, true, false, false, false, false, false, false, 
				false, false, true, false, false, false, false, false, false, false, 
				false, false, true, false, false, false, false, false, false, false, 
				false, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, 
			}
			,
			{
				true, true, true, true, true, true, false, false, false, false, 
				false, false, false, false, false, true, false, false, false, false, 
				false, false, false, false, true, false, false, false, false, false, 
				false, false, false, false, true, false, false, true, true, true, 
				true, false, false, false, false, false, true, true, true, true, 
				true, true, true, true, false, false, false, false, false, false, 
				false, false, true, false, false, false, false, false, false, false, 
				false, false, true, false, false, false, false, false, false, false, 
				false, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, 
			}
			,
			{
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, false, false, false, false, false, false, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, 
			}
			,
			{
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, false, false, false, false, false, false, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, 
			}
			,
			{
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, false, false, false, false, false, false, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, 
			}
			,
			{
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, false, false, false, false, false, false, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, 
			}
			,
			{
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, false, false, false, false, false, false, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, 
			}
			,
			{
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, false, false, false, false, false, false, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, 
			}
		};
}
