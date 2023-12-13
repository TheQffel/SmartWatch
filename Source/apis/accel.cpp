#include "accel.h"

#include "apis/console.h"

namespace Api_Accel
{
    void Setup()
    {
        struct bma423_axes_remap AxelData;
        AxelData.x_axis = 0; AxelData.x_axis_sign = 1;
        AxelData.y_axis = 1; AxelData.y_axis_sign = 1;
        AxelData.z_axis = 2; AxelData.z_axis_sign = 1;

        bool Result = SmartWatch->bma->begin();
        Result = Result && SmartWatch->bma->enableAccel();
        Result = Result && SmartWatch->bma->enableFeature(BMA423_STEP_CNTR, true);
        Result = Result && SmartWatch->bma->enableFeature(BMA423_TILT, true);
        Result = Result && SmartWatch->bma->resetStepCounter();
        Result = Result && SmartWatch->bma->enableTiltInterrupt();
        Result = Result && SmartWatch->bma->set_remap_axes(&AxelData);

        if(Result)
        {
            Api_Console::Log(Api_Console::LogType::Ok, "Accel initialized sucessfully.");
        }
        else
        {
            Api_Console::Log(Api_Console::LogType::Error, "Failed to initialize accel.");
        }
    }
}