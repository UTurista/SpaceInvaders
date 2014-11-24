/*
Classe: Camera
Facilita a criação de novas cameras no jogo. estas novas cameras são sempre
no modo de perspectiva

Os atributos da classe Camera representam respectivamente a localização da camera, localização do motivo
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
	




	//Getter dos atributos: Valores passados por referencia através de um vector
	//TODO: É necessário verificar se o vector de entrada é valido
	void getOffsets(double*);
	bool getType();
};
