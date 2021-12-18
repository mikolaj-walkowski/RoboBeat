#include "Drawing.h"
#include "Pipeline.h"

DrawSimpleSquare::DrawSimpleSquare(glm::vec2* pos,glm::vec2 _dims, glm::vec4 _color):DrawingInterface(pos),color(_color)
{
	spName = "spFullColor";
	for (int i = 0; i < 24; i+=4)
	{
		verts[i] *= (_dims.x/2);
		verts[i + 1] *=(_dims.y/2);
	}
}

void DrawSimpleSquare::draw(bool flip)
{
	M = glm::translate(glm::mat4(1.0f), glm::vec3(*position, 0));
	auto sp = Pipeline::getInstance()->getSP(spName);
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));
	glUniform4fv(sp->u("color"),1,glm::value_ptr(color));

	glEnableVertexAttribArray(sp->a("vertex"));
	glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, verts);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	
	glDisableVertexAttribArray(sp->a("vertex"));
}

DrawingInterface::DrawingInterface(glm::vec2* pos):position(pos)
{
}

DrawTexturedSquare::DrawTexturedSquare(glm::vec2* pos,glm::vec2 _dims, std::string _texName):DrawSimpleSquare(pos,_dims,glm::vec4(0.0)),texName(_texName)
{
	spName = "spTextured";
}


void DrawTexturedSquare::draw(bool flip)
{
	M = glm::translate(glm::mat4(1.0f), glm::vec3(*position, 0));

	auto sp = Pipeline::getInstance()->getSP(spName);
//	printf("TextureHandle %d \n",);

	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));

	glUniform1i(sp->u("tex"), Pipeline::getInstance()->getTex(texName)-1);//TODO Why?
	glUniform1i(sp->u("flip"),flip);

	glEnableVertexAttribArray(sp->a("vertex"));
	glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, verts);

	glEnableVertexAttribArray(sp->a("texCoord"));
	glVertexAttribPointer(sp->a("texCoord"), 2, GL_FLOAT, false, 0, texCoords);


	glDrawArrays(GL_TRIANGLES, 0, 6);
	
	glDisableVertexAttribArray(sp->a("vertex"));
	glDisableVertexAttribArray(sp->a("texCoord"));

}
