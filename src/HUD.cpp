#include "HUD.h"

namespace Micromachines {

	HUD::HUD() : cg::Entity("HUD")
	{
	}

	HUD::~HUD()
	{
	}
	
	void HUD::init()
	{
		_car = (Car*) cg::Registry::instance()->get("Player1");
		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		_winWidth = win.width;
		_winHeight = win.height;
		_max = (_car->getLife()+10);
	}
	
	void HUD::drawLifeBar()
	{
		int life = _car->getLife()/10;
		int i, oneLife = (_max-10)/10;
		int inc = oneLife;
		
		
		glLineWidth(0);
		glColor3d(0.4, 1, 0.1);
		for (i = 0; i < life; i++, inc+= oneLife) {
			glBegin(GL_QUADS);
			glVertex2d(_winWidth-inc, _winHeight-10);
			glVertex2d(_winWidth-inc, _winHeight-30);
			glVertex2d(_winWidth-(inc+oneLife), _winHeight-30);
			glVertex2d(_winWidth-(inc+oneLife), _winHeight-10);
			glEnd();
		}
		
		glLineWidth(2);
		glColor3d(0, 0, 0);
		glBegin(GL_LINES);
		glVertex2d(_winWidth-10, _winHeight-10);
		glVertex2d(_winWidth-10, _winHeight-30);
		
		glVertex2d(_winWidth-10, _winHeight-30);
		glVertex2d(_winWidth-_max, _winHeight-30);
		
		glVertex2d(_winWidth-_max, _winHeight-30);
		glVertex2d(_winWidth-_max, _winHeight-10);
		
		glVertex2d(_winWidth-_max, _winHeight-10);
		glVertex2d(_winWidth-10, _winHeight-10);
		glEnd();
	}
	
	void HUD::drawOverlay()
	{
		std::string s = "1st";
		glColor3f(0.0f, 0.0f, 0.0f);
		glRasterPos2d(300, 450);
		
       		for (int i = 0; s[i] != '\0'; i++) {

        		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
        	}
        	
        	/********************OVERLAY ELAPSED TIME***********************/
        	int minutes = (glutGet(GLUT_ELAPSED_TIME)/60000)%60;
        	int seconds = (glutGet(GLUT_ELAPSED_TIME)/1000)%60;
        	int tenthsecs = (glutGet(GLUT_ELAPSED_TIME)/10) % 100;
        	
        	std::ostringstream time;
        	time << minutes << " : " << seconds;
        	time <<  " : " << tenthsecs;
        	
        	std::string strtime = time.str();
        	glRasterPos2d(20, 450);
        	for (int j = 0; strtime[j] != '\0'; j++) {

        		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, strtime[j]);
        	}
		/*******************************************************************/
		
		/************************ OVERLAY SPEED ****************************/
		std::ostringstream vel;
		vel << (int) (_car->getVelocity()*1200) << " km/h";
		std::string velocity = vel.str();
		glColor3f(0.3f, 1.0f, 1.0f);
		glRasterPos2d(50, 50);
		for(int k = 0; velocity[k] != '\0'; k++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, velocity[k]);
		
		/*******************************************************************/
		
		drawLifeBar();
	}
		

}
