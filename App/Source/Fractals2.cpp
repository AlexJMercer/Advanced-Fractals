
#include "Core/Application.hpp"

#include "FractalLayer.hpp"
#include "ControlLayer.hpp"


int main(int argc, char* argv[]) 
{
    Core::ApplicationSpecification appSpec;
    appSpec.Name = "Fractals Application";
    appSpec.WindowSpec.Width = 1920;
    appSpec.WindowSpec.Height = 1080;
    
    
    Core::Application appInstance(appSpec);
    appInstance.PushLayer<FractalLayer>(argv[1]);
    appInstance.PushLayer<ControlLayer>();
    appInstance.Run();
}