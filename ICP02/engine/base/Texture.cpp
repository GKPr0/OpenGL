#include "Texture.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

namespace Engine 
{
	Texture::Texture(const std::string& file)
	{
		load(file);
	}

	void Texture::load(const std::string& file)
	{

		cv::Mat image = cv::imread(file, cv::IMREAD_UNCHANGED); // Read with (potential) Alpha
		if (image.empty())
		{
			std::cerr << "Error loading texture:" << file << std::endl;
			exit(EXIT_FAILURE);
		}

		// Generates an OpenGL texture object
		glGenTextures(1, &this->id);

		// Assigns the texture to a Texture Unit
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, this->id);

		// Texture data alignment for transfer (single byte = basic, slow, but safe option; usually not necessary) 
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// Assigns the image to the OpenGL Texture object
		int channels = image.channels();
		if (channels == 3)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.cols, image.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, image.data);

		}
		else if (channels == 4)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.cols, image.rows, 0, GL_BGRA, GL_UNSIGNED_BYTE, image.data);
		}
		else
		{
			std::cerr << "Unsupported number of channels " << channels << " in texture " << file << std::endl;
			exit(EXIT_FAILURE);
		}

		// MIPMAP filtering + automatic MIPMAP generation - nicest, needs more memory. Notice: MIPMAP is only for image minifying.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // bilinear magnifying
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // trilinear minifying
		glGenerateMipmap(GL_TEXTURE_2D);  //Generate mipmaps now.

		 // Configures the way the texture repeats
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Unbinds the OpenGL Texture object so that it can't accidentally be modified
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
}


