
#include "Core/Application.hpp"
#include "FractalLayer.hpp"


int main() 
{
    Core::ApplicationSpecification appSpec;
    appSpec.Name = "Fractals Application";
    appSpec.WindowSpec.Width = 2560;
    appSpec.WindowSpec.Height = 1440;
    
    
    Core::Application appInstance(appSpec);
    appInstance.PushLayer<FractalLayer>();
    appInstance.Run();
}