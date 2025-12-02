
#include "Core/Application.hpp"
#include "FractalLayer.hpp"


int main(int argc, char* argv[]) 
{
    Core::ApplicationSpecification appSpec;
    appSpec.Name = "Fractals Application";
    appSpec.WindowSpec.Width = 2560;
    appSpec.WindowSpec.Height = 1440;
    
    
    Core::Application appInstance(appSpec);
    appInstance.PushLayer<FractalLayer>(argv[1]);
    appInstance.Run();
}