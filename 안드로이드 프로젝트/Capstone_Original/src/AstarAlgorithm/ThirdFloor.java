package AstarAlgorithm;
/**
 * Map 94m*32m True & False
 */

/**
 * 3, 20 301ȣ - 6, 20 302ȣ  - 14, 20 303ȣ - 17, 20 304ȣ - 25, 20 305ȣ - 27, 20 306ȣ	36, 20 307ȣ - 38,20 308ȣ - 43, 20 309ȣ
 *46, 12 ����� - 49, 20 �߾Ӱ�� - 53, 20 310ȣ - 57, 20 311ȣ - 61, 20 312ȣ - 65, 20 313ȣ - 68,20 314ȣ - 76,20 315ȣ - 76, 17 316ȣ 
 *76, 13 317ȣ  79, 10 318ȣ , 82, 13 319ȣ - 84, 16 320ȣ - 84, 18 321ȣ - 91, 22 ���� ��� - 81, 24 322ȣ - 71, 24 323ȣ - 67, 24 324ȣ  
 * 63, 24 325ȣ - 60, 24 - 326ȣ  56, 24 ��ȭ���, 54, 24 �� ȭ��� - 48, 28 �߾� �κ� - 38, 24 329ȣ - 34, 24 330ȣ - 31, 24 331ȣ - 27 , 24 332ȣ
 * 24, 24 333ȣ - 20, 24 334ȣ - 17, 24 335ȣ - 13, 24 336ȣ - 9 , 24 337 ȣ - 6 , 24 338ȣ - 2 , 13 ���� ���
 * 
 * 301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 311, 312, 313, 314, 315, 316, 317, 318, 319, 320, 321, 322, 333, 334, 335, 336
 * 337, 338, �����, �߾Ӱ�� , ������� , ��ȭ���, ��ȭ��� ,�߾ӷκ� ,�������
 */
public class ThirdFloor 
{
	public ThirdFloor(){};
	public boolean[][] getMap(){return map;}
	public int[][] getRoomCoordi(){return RoomCoordinate;}
	
	public enum RoomNumber { ThreeZeroOne, ThreeZeroTwo, ThreeZeroThree, ThreeZeroFour, ThreeZeroFive, ThreeZeroSix, ThreeZeroSeven, ThreeZeroEight, ThreeZeroNine, ThreeOneZero, 
						      ThreeOneOne, ThreeOneTwo,  ThreeOneThree,  ThreeOneFour,  ThreeOneFive,  ThreeOneSix,  ThreeOneSeven,  ThreeOneEight,  ThreeOneNine,  ThreeTwoZero,  
					          ThreeTwoOne,  ThreeTwoTow,  ThreeTwoThree,  ThreeTwoFour,  ThreeTwoFive,  ThreeTwoSix,  ThreeTwoSeven,  ThreeTwoEight,  ThreeTwoNine,  ThreeThreeZero,
					        ThreeThreeOne, ThreeThreeTwo,ThreeThreeThree,ThreeThreeFour,ThreeThreeFive,ThreeThreeSix,ThreeThreeSeven,ThreeThreeEight, Elec, CenterFloor, RightFloor, Women, Men, Robby, LeftFloor};
					        
	public int[][] RoomCoordinate = {
			{ 3, 20 } , { 6, 20 } , { 14, 20 } , { 17, 20 } , { 25, 20 } , { 27, 20 } , { 36, 20 } , { 38, 20 } , { 43, 20 } , { 53, 20 } , 
			{ 57, 20} , { 61, 20 } , { 65, 20 } , { 68, 20 } , { 76, 20 } , { 76, 17 } , { 76, 13 } , { 79, 10 } , { 82, 13 } , { 84, 16 } , 
			{ 84, 18} , { 81, 24 } , { 71, 24 } , { 67, 24 } , { 63, 24 } , { 60, 24 } , { 38, 24 } , { 34, 24 } , { 31, 24 } , { 27, 24 } , 
			{ 24, 24 } , { 20, 24 } , { 17, 24 } , { 13, 24 } , { 9, 24 } , { 6, 24 } , { 46, 12 } , { 45, 4 } , { 48, 16 } , { 91, 22 } , 
			{ 56, 22 } , { 53, 22 } , { 48, 28 } , { 2, 24 }
	};
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
				true, true, true, true
			}
			,
			{
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, false,
				false,false,false,false,false,false,false,false,false,true, 
				false,false,false,false,false,false,false,false,false,false,
				true, true, true, true
			}
			,
			{
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, false,
				false,false,false,false,false,false,false,false,false,true, 
				false,false,false,false,false,false,false,false,false,false,
				true, true, true, true
			}
			,
			{
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, false,
				false,false,false,false,false,false,false,false,false,true, 
				false,false,false,false,false,false,false,false,false,false,
				true, true, true, true
			}
			,
			{
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, false,false,false,true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, false,
				false,false,false,false,false,false,false,false,false,true, 
				false,false,false,false,false,false,false,false,false,false,
				true, true, true, true,
			}
			,
			{
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, false,false,false,true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, false,
				false,false,false,false,false,false,false,false,false,true, 
				false,false,false,false,false,false,false,false,false,false,
				true, true, true, true,
			}
			,
			{
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, false,false,false,true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, false,
				false,false,false,false,false,false,false,false,false,true, 
				false,false,false,false,false,false,false,false,false,false,
				true, true, true, true,
			}
			,
			{
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, false,false,false,true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, false,
				false,false,false,false,false,false,false,false,false,true, 
				false,false,false,false,false,false,false,false,false,false,
				true, true, true, true,
			}
			,
			{
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, false,false,false,true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, false,
				false,false,false,false,false,false,false,false,false,true, 
				false,false,false,false,false,false,false,false,false,false,
				true, true, true, true,
			}
			,
			{
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, false,false,false,true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, false,
				false,false,false,false,false,false,false,false,false,true, 
				false,false,false,false,false,false,false,false,false,false,
				true, true, true, true,
			}
			,
			{
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, false,false,false,true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, false,false,true, 
				false,false,false,false,false,false,false,false,false,false,
				true, true, true, true,
			}
			,
			{
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, true, true, true, true, true, true, 
				true, true, true, true, false,false,false,true, false,false,
				true, false,false,false,true, false,false,true, false,false,
				false,true, false,false,false,true, true, true, true, true, 
				false,false,false,false,false,true, false,false,false,true, 
				false,false,false,false,false,false,false,false,false,false,
				true, true, true, true,
			}
			,
			{
				true, false,false,false,true, false,false,true, false,false,
				false,false,false,false,true, false,false,false,false,false,
				false,false,false,false,false,true, false,false,false,true, 
				false,false,false,false,false,false,true, false,false,true, 
				false,false,false,true, false,false,false,true, false,false,
				true, false,false,false,true, false,false,true, false,false,
				false,true, false,false,false,true, false,false,false,true, 
				false,false,false,false,false,false,false,false,false,true, 
				false,false,false,false,false,false,false,false,false,false,
				true, true, true, true,
			}
			,
			{
				true, false,false,false,true, false,false,true, false,false,
				false,false,false,false,true, false,false,false,false,false,
				false,false,false,false,false,true, false,false,false,true, 
				false,false,false,false,false,false,true, false,false,true, 
				false,false,false,true, false,false,false,true, false,false,
				true, false,false,false,true, false,false,true, false,false,
				false,true, false,false,false,true, false,false,false,true, 
				false,false,false,false,false,true, false,false,false,true, 
				false,false,true, true, true, true, true, true, true, true, 
				true, true, true, true,
			}
			,
			{
				true, false,false,false,true, false,false,true, false,false,
				false,false,false,false,true, false,false,false,false,false,
				false,false,false,false,false,true, false,false,false,true, 
				false,false,false,false,false,false,true, false,false,true, 
				false,false,false,true, false,false,false,true, false,false,
				true, false,false,false,true, false,false,true, false,false,
				false,true, false,false,false,true, false,false,false,true, 
				false,false,false,false,false,true, false,false,false,false,
				false,false,false,true, false,false,false,false,false,false,
				true, true, true, true,
			}
			,
			{
				true, false,false,false,true, false,false,true, false,false,
				false,false,false,false,true, false,false,false,false,false,
				false,false,false,false,false,true, false,false,false,true, 
				false,false,false,false,false,false,true, false,false,true, 
				false,false,false,true, false,false,false,true, false,false,
				true, false,false,false,true, false,false,true, false,false,
				false,true, false,false,false,true, false,false,false,true, 
				false,false,false,false,false,true, false,false,false,false,
				false,false,false,false,false,false,false,false,false,false,
				true, true, true, true,
			}
			,
			{
				true, false,false,false,true, false,false,true, false,false,
				false,false,false,false,true, false,false,false,false,false,
				false,false,false,false,false,true, false,false,false,true, 
				false,false,false,false,false,false,true, false,false,true, 
				false,false,false,true, false,false,false,true, false,false,
				true, false,false,false,true, false,false,true, false,false,
				false,true, false,false,false,true, false,false,false,true, 
				false,false,false,false,false,false,false,false,false,false,
				false,false,false,true, true, true, true, true, true, true, 
				true, true, true, true,
			}
			,
			{
				true, false,false,false,true, false,false,true, false,false,
				false,false,false,false,true, false,false,false,false,false,
				false,false,false,false,false,true, false,false,false,true, 
				false,false,false,false,false,false,true, false,false,true, 
				false,false,false,true, false,false,false,true, false,false,
				true, false,false,false,true, false,false,true, false,false,
				false,true, false,false,false,true, false,false,false,true, 
				false,false,false,false,false,true, false,false,false,false,
				false,false,false,false,false,false,false,false,false,false,
				true, true, true, true,
			}
			,
			{
				true, false,false,false,true, false,false,true, false,false,
				false,false,false,false,true, false,false,false,false,false,
				false,false,false,false,false,true, false,false,false,true, 
				false,false,false,false,false,false,true, false,false,true, 
				false,false,false,true, false,false,false,false,false,false,
				true, false,false,false,true, false,false,true, false,false,
				false,true, false,false,false,true, false,false,false,true, 
				false,false,false,false,false,true, false,false,false,false,
				false,false,false,true, false,false,false,false,false,false,
				true, true, true, true,
			}
			,
			{
				true, true, false,true, true, false,true, true, true, true, 
				true, true, true, false,true, false,false,true, true, true, 
				true, true, true, true, false,true, false,false,true, true, 
				true, true, true, true, false,false,true, false,true, true, 
				true, true, false,true, false,false,false,false,false,false,
				true, false,false,true, true, true, false,true, true, true, 
				false,true, true, true, false,true, true, false,true, true, 
				true, true, true, true, false,false,false,false,false,false,
				false,false,false,true, true, true, true, true, true, true, 
				true, true, true, true,
			}
			,
			{
				true, false,false,false,false,false,false,false,false,false,
				false,false,false,false,false,false,false,false,false,false,
				false,false,false,false,false,false,false,false,false,false,
				false,false,false,false,false,false,false,false,false,false,
				false,false,false,false,false,false,false,false,false,false,
				false,false,false,false,false,false,false,false,false,false,
				false,false,false,false,false,false,false,false,false,false,
				false,false,false,false,false,false,false,false,false,false,
				false,false,false,false,false,false,false,false,false,false,
				false,false,false,false
			}
			,
			{
				true, false,false,false,false,false,false,false,false,false,
				false,false,false,false,false,false,false,false,false,false,
				false,false,false,false,false,false,false,false,false,false,
				false,false,false,false,false,false,false,false,false,false,
				false,false,false,false,false,false,false,false,false,false,
				false,false,false,false,false,false,false,false,false,false,
				false,false,false,false,false,false,false,false,false,false,
				false,false,false,false,false,false,false,false,false,false,
				false,false,false,false,false,false,false,false,false,false,
				false,false,false,false
			}
			,
			{
				true, false,false,false,false,false,false,false,false,false,
				false,false,false,false,false,false,false,false,false,false,
				false,false,false,false,false,false,false,false,false,false,
				false,false,false,false,false,false,false,false,false,false,
				false,false,false,false,false,false,false,false,false,false,
				false,false,false,false,false,false,false,false,false,false,
				false,false,false,false,false,false,false,false,false,false,
				false,false,false,false,false,false,false,false,false,false,
				false,false,false,false,false,false,false,false,false,false,
				false,false,false,false
			}
			,
			{
				true, false,false,true, true, false,true, true, false,true, 
				true, true, false,true, true, false,false,true, true, false,
				true, true, false,true, true, true, false,false,true, true, 
				false,true, true, false,true, true, true, false,true, true, 
				true, true, true, true, false,false,false,false,false,false,
				true, false,false,false,false,true, true, true, true, false,
				true, true, false,true, true, false,false,false,true, false,
				false,true, true, true, true, true, true, false,false,true, 
				false,false,true, true, true, true, true, false,false,true, 
				true, false,false,false
			}
			,
			{
				true, false,false,true, false,false,false,true, false,false,
				false,true, false,false,true, false,false,false,true, false,
				false,true, false,false,false,true, false,false,false,true, 
				false,false,true, false,false,false,true, false,false,false,
				false,false,true, true, false,false,false,false,false,false,
				true, false,false,true, true, false,false,false,true, false,
				false,true, false,false,true, false,false,false,true, false,
				false,false,false,false,false,false,false,false,false,true, 
				false,false,false,false,false,false,false,false,false,false,
				true, false,false,false
			}
			,
			{
				true, false,false,true, false,false,false,true, false,false,
				false,true, false,false,true, false,false,false,true, false,
				false,true, false,false,false,true, false,false,false,true, 
				false,false,true, false,false,false,true, false,false,false,
				false,false,true, true, false,false,false,false,false,false,
				true, false,false,true, true, false,false,false,true, false,
				false,true, false,false,true, false,false,false,true, false,
				false,false,false,false,false,false,false,false,false,true, 
				false,false,false,false,false,false,false,false,false,false,
				true, false,false,false
			}
			,
			{
				true, false,false,true, false,false,false,true, false,false,
				false,true, false,false,true, false,false,false,true, false,
				false,true, false,false,false,true, false,false,false,true, 
				false,false,true, false,false,false,true, false,false,false,
				false,false,true, true, false,false,false,false,false,false,
				true, false,false,true, true, false,false,false,true, false,
				false,true, false,false,true, false,false,false,true, false,
				false,false,false,false,false,false,false,false,false,true, 
				false,false,false,false,false,false,false,false,false,false,
				true, true, true, true,
			}
			,
			{
				true, false,false,true, false,false,false,true, false,false,
				false,true, false,false,true, false,false,false,true, false,
				false,true, false,false,false,true, false,false,false,true, 
				false,false,true, false,false,false,true, false,false,false,
				false,false,true, true, false,false,false,false,false,false,
				true, false,false,true, true, false,false,false,true, false,
				false,true, false,false,true, false,false,false,true, false,
				false,false,false,false,false,false,false,false,false,true, 
				false,false,false,false,false,false,false,false,false,false,
				true, true, true, true,
			}
			,
			{
				true, false,false,true, false,false,false,true, false,false,
				false,true, false,false,true, false,false,false,true, false,
				false,true, false,false,false,true, false,false,false,true, 
				false,false,true, false,false,false,true, false,false,false,
				false,false,true, true, false,false,false,false,false,false,
				true, false,false,true, true, false,false,false,true, false,
				false,true, false,false,true, false,false,false,true, false,
				false,false,false,false,false,false,false,false,false,true, 
				false,false,false,false,false,false,false,false,false,false,
				true, true, true, true,
			}
			,
			{
				true, true, true, true, false,false,false,true, false,false,
				false,true, false,false,true, false,false,false,true, false,
				false,true, false,false,false,true, false,false,false,true, 
				false,false,true, false,false,false,true, false,false,false,
				false,false,true, true, false,false,false,false,false,false,
				true, false,false,true, true, false,false,false,true, false,
				false,true, false,false,true, false,false,false,true, false,
				false,false,false,false,false,false,false,false,false,true, 
				false,false,false,false,false,false,false,false,false,false,
				true, true, true, true,
			}
			,
			{
				true, true, true, true, false,false,false,true, false,false,
				false,true, false,false,true, false,false,false,true, false,
				false,true, false,false,false,true, false,false,false,true, 
				false,false,true, false,false,false,true, false,false,false,
				false,false,true, true, false,false,false,false,false,false,
				true, false,false,true, true, false,false,false,true, false,
				false,true, false,false,true, false,false,false,true, false,
				false,false,false,false,false,false,false,false,false,true, 
				false,false,false,false,false,false,false,false,false,false,
				true, true, true, true,
			}
			,
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
				true, true, true, true,
			}
		};
}






