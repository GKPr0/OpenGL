#include "SkyBox.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>


namespace Engine 
{
	SkyBox::SkyBox(const std::vector<std::string> faces)
	{
        create();
		loadTexture(faces);
        
	}
	
    void SkyBox::create()
    {
        static float skybox[] = {
              -1.0f,  1.0f, -1.0f,
              -1.0f, -1.0f, -1.0f,
               1.0f, -1.0f, -1.0f,
               1.0f, -1.0f, -1.0f,
               1.0f,  1.0f, -1.0f,
              -1.0f,  1.0f, -1.0f,

              -1.0f, -1.0f,  1.0f,
              -1.0f, -1.0f, -1.0f,
              -1.0f,  1.0f, -1.0f,
              -1.0f,  1.0f, -1.0f,
              -1.0f,  1.0f,  1.0f,
              -1.0f, -1.0f,  1.0f,

               1.0f, -1.0f, -1.0f,
               1.0f, -1.0f,  1.0f,
               1.0f,  1.0f,  1.0f,
               1.0f,  1.0f,  1.0f,
               1.0f,  1.0f, -1.0f,
               1.0f, -1.0f, -1.0f,

              -1.0f, -1.0f,  1.0f,
              -1.0f,  1.0f,  1.0f,
               1.0f,  1.0f,  1.0f,
               1.0f,  1.0f,  1.0f,
               1.0f, -1.0f,  1.0f,
              -1.0f, -1.0f,  1.0f,

              -1.0f,  1.0f, -1.0f,
               1.0f,  1.0f, -1.0f,
               1.0f,  1.0f,  1.0f,
               1.0f,  1.0f,  1.0f,
              -1.0f,  1.0f,  1.0f,
              -1.0f,  1.0f, -1.0f,

              -1.0f, -1.0f, -1.0f,
              -1.0f, -1.0f,  1.0f,
               1.0f, -1.0f, -1.0f,
               1.0f, -1.0f, -1.0f,
              -1.0f, -1.0f,  1.0f,
               1.0f, -1.0f,  1.0f
        };

        GLuint vbo;

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(skybox), &skybox, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);

        // Bind VBO and VAO to 0 to prevent unintended modification 
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
	
	void SkyBox::loadTexture(const std::vector<std::string> faces)
	{
		glGenTextures(1, &textureId);
        glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

        // Texture data alignment for transfer (single byte = basic, slow, but safe option; usually not necessary) 
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		for (unsigned int i = 0; i < faces.size(); i++)
		{
			cv::Mat image = cv::imread(faces[i], cv::IMREAD_UNCHANGED);
			if (image.empty())
			{
				std::cerr << "Error loading skybox texture:" << faces[i] << std::endl;
				exit(EXIT_FAILURE);
			}

			glTexImage2D(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, image.cols, image.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, image.data
			);
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        // Unbinds the OpenGL Texture object so that it can't accidentally be modified
        glBindTexture(GL_TEXTURE_2D, 0);
	}
	
    void SkyBox::render(Program& program)
    {
        glActiveTexture(GL_TEXTURE1);
        program.setInt("skybox", 1);
        program.setMat4("uM_m", getModelMatrix());

        glDepthMask(GL_FALSE);
		
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
		
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        glDepthMask(GL_TRUE);
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }
}

