#pragma once





/* Bullet
 * 
 * 
 * 
*/
class Bullet{
		float _posX;
		float _posY;
		float _lastUpdate;
		bool  _draw;
		float _limit;
		float _speed;
public:
		Bullet();
		Bullet(float posX,float limit);
		Bullet(float posX, float posY, float limit, float speed);
		
		//Getters
		float getPosX(){return _posX;}
		float getPosY(){return _posY;}


		//Setters
		void death(){_draw=false;}


		//Main Fuctions
		void draw();
		void tick();
		bool isDrawing();
		void resetBullet(float xx, float yy);


};
