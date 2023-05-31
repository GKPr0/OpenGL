#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "../base/Texture.h"
#include "../base/Program.h"
#include "../renderable/Renderable.h"


namespace Engine {

	struct Particle{
		glm::vec3 Position, Velocity;
        glm::vec4 Color;

		Particle() : Position(0.0f), Velocity(0.0f), Color(1.0f) { }
	};
    
	class ParticleGenerator : public Renderable 
	{
    public:
        ParticleGenerator(Texture* texture, unsigned int amount);

        virtual void render(Program& program) override;
        void update(float dt, unsigned int newParticles, glm::vec3 offset = glm::vec3(0.0f));

    private:
        void init();
        unsigned int firstUnusedParticle();
        void respawnParticle(Particle& particle, glm::vec3 offset = glm::vec3(0.0f));

        std::vector<Particle> particles;
        unsigned int amount;
        unsigned int lastUsedParticle;

        Texture* texture;
    };  
}

