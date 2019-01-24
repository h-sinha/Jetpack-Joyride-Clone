#include "functions.h"
#include "main.h"

std::string sevenSegment(char s)
{
	switch(s)
	{
		case '1':
			return "0011000";
		case '2':
			return "0110111";
		case '3':
			return "0111101";
		case '4':
			return "1011001";
		case '5':
			return "1101101";
		case '6':
			return "1101111";
		case '7':
			return "0111000";
		case '8':
			return "1111111";
		case '9':
			return "1111101";
		case '0':
			return "1111110";
		case 'S':
			return "1101101";
		case 'C':
			return "1100110";
		case 'O':
			return "1111110";
		case 'R':
			return "1100010";
		case 'E':
			return "1100111";
		case '-':
			return "0000001";
	}
}
bool on_line(float x1, float y1, float px, float py, float x2, float y2) 
{  
   if(px <= std::max(x1, x2) && px >= std::min(x1, x2) && (py <= std::max(y1, y2) && py >= std::min(y1, y2)))
	      return 1;
   return 0;
}
int direction(float ax, float ay, float bx, float by, float cx, float cy) 
{
   float val = (by-ay)*(cx-bx)-(bx-ax)*(cy-by);
   if (val == 0)
      return 0;     
   else if(val < 0)
      return 2;    
   return 1;    
}

bool check_intersection(glm::vec4 l1, glm::vec4 l2 ) 
{
   int dir1 = direction(l1[0], l1[1], l1[2], l1[3], l2[0], l2[1]);
   int dir2 = direction(l1[0], l1[1], l1[2], l1[3], l2[2], l2[3]);
   int dir3 = direction(l2[0], l2[1], l2[2], l2[3], l1[0], l1[1]);
   int dir4 = direction(l2[0], l2[1], l2[2], l2[3], l1[2], l1[3]);
   if(dir1 != dir2 && dir3 != dir4)
      return 1; 
   if(dir1 == 0 && on_line(l1[0], l1[1], l2[0], l2[1], l1[2], l1[3])) 
      return 1;
   if(dir2 == 0 && on_line(l1[0], l1[1], l2[2], l2[3], l1[2], l1[3])) 
      return 1;
   if(dir3 == 0 && on_line(l2[0], l2[1], l1[0], l1[1], l2[2], l2[3])) 
      return 1;
   if(dir4 == 0 && on_line(l2[0], l2[1], l1[2], l1[3], l2[2], l2[3])) 
      return 1;
   return 0;
}
