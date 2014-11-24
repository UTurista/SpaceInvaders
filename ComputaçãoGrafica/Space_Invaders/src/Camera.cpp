#include <GL/glut.h>
#include "Camera.h"

/* Implementação de Camera
 */


/* Construtores
 *
 *
 *
 */
Camera::Camera():	_eyeX(0), _eyeY(0), _eyeZ(0),
					_atX(0), _atY(0), _atZ(0),
					_upX(0), _upY(0), _upZ(0){}


Camera::Camera(	double eyeX,	double eyeY,double eyeZ,
				double atX,		double atY,	double atZ,
				double upX,		double upY,	double upZ, bool isPerspective):
					_eyeX(eyeX),	_eyeY(eyeY) , _eyeZ(eyeZ),
					_atX(atX),		_atY(atY),	_atZ(atZ),
					_upX(upX),		_upY(upY),	_upZ(upZ), _isPerspective(isPerspective){}



/* getOffsets()
 *
 *
 *
 */
void Camera::getOffsets(double* vec){
	vec[0]=_eyeX;
	vec[1]=_eyeY;
	vec[2]=_eyeZ;

	vec[3]=_atX;
	vec[4]=_atY;
	vec[5]=_atZ;

	vec[6]=_upX;
	vec[7]=_upY;
	vec[8]=_upZ;
}

/* getType()
 *
 *
 *
 */
bool Camera::getType(){
	return _isPerspective;
}