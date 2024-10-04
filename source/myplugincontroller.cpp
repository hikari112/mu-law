//------------------------------------------------------------------------
// Copyright(c) 2024 Hikari Audio.
//------------------------------------------------------------------------

#include "myplugincontroller.h"
#include "myplugincids.h"


using namespace Steinberg;

namespace MyCompanyName {

//------------------------------------------------------------------------
// muLawController Implementation
//------------------------------------------------------------------------
tresult PLUGIN_API muLawController::initialize (FUnknown* context)
{
	// Here the Plug-in will be instantiated

	//---do not forget to call parent ------
	tresult result = EditControllerEx1::initialize (context);
	if (result != kResultOk)
	{
		return result;
	}

	parameters.addParameter(
							STR16("Gain")
						  , STR16("dB")
						  , 0
						  , 0.1
						  , Vst::ParameterInfo::kCanAutomate
						  , GainParams::kParamGainId
						  , 0);

	parameters.addParameter(
							STR16("Output Gain")
						  , STR16("dB")
						  , 0
						  , 0.5
						  , Vst::ParameterInfo::kCanAutomate
						  , GainParams::kParamOutGainId
						  , 1);
	parameters.addParameter(
							STR16("Mu")
						  , STR16("Mu")
						  , 0
						  , 0.5
						  , Vst::ParameterInfo::kCanAutomate
						  , muParams::kParamMuId
						  , 2);

	return result;
}

//------------------------------------------------------------------------
tresult PLUGIN_API muLawController::terminate ()
{
	// Here the Plug-in will be de-instantiated, last possibility to remove some memory!

	//---do not forget to call parent ------
	return EditControllerEx1::terminate ();
}

//------------------------------------------------------------------------
tresult PLUGIN_API muLawController::setComponentState (IBStream* state)
{
	// Here you get the state of the component (Processor part)
	if (!state)
		return kResultFalse;

	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API muLawController::setState (IBStream* state)
{
	// Here you get the state of the controller

	return kResultTrue;
}

//------------------------------------------------------------------------
tresult PLUGIN_API muLawController::getState (IBStream* state)
{
	// Here you are asked to deliver the state of the controller (if needed)
	// Note: the real state of your plug-in is saved in the processor

	return kResultTrue;
}

//------------------------------------------------------------------------
IPlugView* PLUGIN_API muLawController::createView (FIDString name)
{
	// Here the Host wants to open your editor (if you have one)
	if (FIDStringsEqual (name, Vst::ViewType::kEditor))
	{
		// create your editor here and return a IPlugView ptr of it
        return nullptr;
	}
	return nullptr;
}

//------------------------------------------------------------------------
} // namespace MyCompanyName
