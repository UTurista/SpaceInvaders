#pragma once

/* BackGround
 * 
 * 
 * 
*/
class BackGround {

public:
    /* BackGround::BackGround()
	 * >Construtor do BackGround;
	*/
    BackGround();

    /* 
	 * BackGround::draw()
	 * >Envia as ordens de desenho para o OpenGl
     * >Nao desenha, ou seja, não faz GlFlush()
	*/
    void draw();

    void LoadTexture(const char* bitmap_file);
};