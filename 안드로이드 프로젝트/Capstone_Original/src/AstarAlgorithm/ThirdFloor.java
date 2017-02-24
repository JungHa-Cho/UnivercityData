package AstarAlgorithm;
/**
 * Map 94m*32m True & False
 */

/**
 * 3, 20 301호 - 6, 20 302호  - 14, 20 303호 - 17, 20 304호 - 25, 20 305호 - 27, 20 306호	36, 20 307호 - 38,20 308호 - 43, 20 309호
 *46, 12 전기관 - 49, 20 중앙계단 - 53, 20 310호 - 57, 20 311호 - 61, 20 312호 - 65, 20 313호 - 68,20 314호 - 76,20 315호 - 76, 17 316호 
 *76, 13 317호  79, 10 318호 , 82, 13 319호 - 84, 16 320호 - 84, 18 321호 - 91, 22 우측 계단 - 81, 24 322호 - 71, 24 323호 - 67, 24 324호  
 * 63, 24 325호 - 60, 24 - 326호  56, 24 여화장실, 54, 24 남 화장실 - 48, 28 중앙 로비 - 38, 24 329호 - 34, 24 330호 - 31, 24 331호 - 27 , 24 332호
 * 24, 24 333호 - 20, 24 334호 - 17, 24 335호 - 13, 24 336호 - 9 , 24 337 호 - 6 , 24 338호 - 2 , 13 좌측 계단
 * 
 * 301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 311, 312, 313, 314, 315, 316, 317, 318, 319, 320, 321, 322, 333, 334, 335, 336
 * 337, 338, 전기관, 중앙계단 , 우측계단 , 여화장실, 남화장실 ,중앙로비 ,좌측계단
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






