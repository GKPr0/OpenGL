#include "ParticleGenerator.h"


namespace Engine {

	ParticleGenerator::ParticleGenerator(Texture* texture, unsigned int amount):  amount(amount) , texture(texture)
	{
		this->init();
	}

	void ParticleGenerator::init()
	{
        // First 3 col Positions, next 2 col TexCoords
        float particle_quad[] = {
            0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

            0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f, 0.0f
        };

        GLuint VBO;
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &VBO);

        glBindVertexArray(vao);

        // fill mesh buffer
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);

        // set mesh attributes
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); //Position
		glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); //TexCoords
        glEnableVertexAttribArray(1);
        
        glBindVertexArray(0);

        // create particle instances
        for (unsigned int i = 0; i < this->amount; ++i)
            this->particles.push_back(Particle());
	}

    void ParticleGenerator::render(Program& program)
    {
		program.setMat4("uM_m", getModelMatrix());

        //Set texture unit
        glActiveTexture(GL_TEXTURE0);
        program.setInt("tex0", 0);
        glBindTexture(GL_TEXTURE_2D, texture->getId());

        for (Particle particle : this->particles)
        {
            if (particle.Color.a > 0.0f)
            {
				program.setVec3("offset", particle.Position);
				program.setVec4("color", particle.Color);
				glBindVertexArray(vao);
				glDrawArrays(GL_TRIANGLES, 0, 6);
				glBindVertexArray(0);
			}
		}

        glBindTexture(GL_TEXTURE_2D, 0);
	}

    void ParticleGenerator::update(float dt, unsigned int newParticles, glm::vec3 offset)
    {
		// add new particles 
        for (unsigned int i = 0; i < newParticles; ++i)
        {
			int unusedParticle = this->firstUnusedParticle();
			this->respawnParticle(this->particles[unusedParticle], offset);
		}

        // update particles
        for (unsigned int i = 0; i < this->amount; ++i)
		{         
            Particle& p = particles[i];
            p.Color.a -= dt;
			if (p.Color.a > 0.0f)
			    p.Position -= p.Velocity * dt;
		}
	}

    unsigned int lastUsedParticle = 0;
	unsigned int ParticleGenerator::firstUnusedParticle()
	{
        // first search from last used particle
        for (unsigned int i = lastUsedParticle; i < this->amount; ++i) {
            if (this->particles[i].Color.a <= 0.0f) {
                lastUsedParticle = i;
                return i;
            }
        }
        // otherwise, do a linear search
        for (unsigned int i = 0; i < lastUsedParticle; ++i) {
            if (this->particles[i].Color.a <= 0.0f) {
                lastUsedParticle = i;
                return i;
            }
        }
        lastUsedParticle = 0;
        return 0;
	}

	void ParticleGenerator::respawnParticle(Particle& particle, glm::vec3 offset)
	{
		float rColor = ((rand() % 100) / 100.0f); // 0 - 1.0
	
		particle.Color = glm::vec4(rColor, rColor, rColor, 1.0f);
        particle.Position = offset;
		particle.Velocity = glm::vec3(((rand() % 100) - 50) / 10.0f, // -5 - 5
                                       ((rand() % 100) - 50) / 10.0f,
                                       ((rand() % 100) - 50) / 10.0f);
	}
}