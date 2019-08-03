#pragma once

/*
Classe: Camera
Facilita a cria��o de novas cameras no jogo. estas novas cameras s�o sempre
no modo de perspectiva

Os atributos da classe Camera representam respectivamente a localiza��o da camera, localiza��o do motivo
e o vector up da camera tudo em (x, y, z)  
*/


class Camera{
	double	_eyeX, _eyeY, _eyeZ,
			_atX, _atY, _atZ,
			_upX, _upY, _upZ;
	bool	_isPerspective;
public:
	//Construtores
	Camera();
	Camera(	double eyeX,	double eyeY,double eyeZ,
			double atX,		double atY,	double atZ,
			double upX,		double upY,	double upZ,
			bool _isPerspective);
	




	//Getter dos atributos: Valores passados por referencia atrav�s de um vector
	//TODO: � necess�rio verificar se o vector de entrada � valido
	void getOffsets(double*);
	bool getType();
};
