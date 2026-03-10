#ifndef PARTICLE_TOOL_APP_HPP
#define PARTICLE_TOOL_APP_HPP

#include "System/HybridApp.hpp"
#include "ParticleToMyAodApp.hpp"
#include "MyAodToParticleApp.hpp"

class ParticleToolApp : public HybridApp
{
public:

    ParticleToolApp()
    {}

protected:

    void ShowStartScreen() override
    {
        CONSOLE_OUT.PrintLn("*********************************", Mess::endl,
                            "|ParticleTool BY ATLAS AND IMBEE|", Mess::endl,
                            "***************2026**************");
    }

    void RunExporter(int my_argc, char* my_argv[]) override
    {
        ParticleToMyAodApp().Run(my_argc, my_argv);
    }

    void RunImporter(int my_argc, char* my_argv[]) override
    {
        MyAodToParticleApp().Run(my_argc, my_argv);
    }



};



#endif // !PARTICLE_TOOL_APP_HPP
