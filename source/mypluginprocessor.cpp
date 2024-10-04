//------------------------------------------------------------------------
// Copyright(c) 2024 Hikari Audio.
//------------------------------------------------------------------------

#include "mypluginprocessor.h"
#include "myplugincids.h"

#include "base/source/fstreamer.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"

#include "public.sdk/source/vst/vstaudioprocessoralgo.h"
#include "effects.h"

using namespace Steinberg;

namespace MyCompanyName {
//------------------------------------------------------------------------
// muLawProcessor
//------------------------------------------------------------------------
muLawProcessor::muLawProcessor ()
{
	//--- set the wanted controller for our processor
	setControllerClass (kmuLawControllerUID);
}

//------------------------------------------------------------------------
muLawProcessor::~muLawProcessor ()
{}

//------------------------------------------------------------------------
tresult PLUGIN_API muLawProcessor::initialize (FUnknown* context)
{
	// Here the Plug-in will be instantiated
	
	//---always initialize the parent-------
	tresult result = AudioEffect::initialize (context);
	// if everything Ok, continue
	if (result != kResultOk)
	{
		return result;
	}

	//--- create Audio IO ------
	addAudioInput (STR16 ("Stereo In"), Steinberg::Vst::SpeakerArr::kStereo);
	addAudioOutput (STR16 ("Stereo Out"), Steinberg::Vst::SpeakerArr::kStereo);

	/* If you don't need an event bus, you can remove the next line */
	// addEventInput (STR16 ("Event In"), 1);

	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API muLawProcessor::terminate ()
{
	// Here the Plug-in will be de-instantiated, last possibility to remove some memory!
	
	//---do not forget to call parent ------
	return AudioEffect::terminate ();
}

//------------------------------------------------------------------------
tresult PLUGIN_API muLawProcessor::setActive (TBool state)
{
	//--- called when the Plug-in is enable/disable (On/Off) -----
	return AudioEffect::setActive (state);
}

//------------------------------------------------------------------------
tresult PLUGIN_API muLawProcessor::process (Vst::ProcessData& data)
{

	{
		int32 numParamsChanged = data.inputParameterChanges->getParameterCount ();
		for (int32 index = 0; index < numParamsChanged; index++)
		{
			if (auto* paramQueue = data.inputParameterChanges->getParameterData (index))
			{
				Vst::ParamValue value;
				int32 sampleOffset;
				int32 numPoints = paramQueue->getPointCount ();
				switch (paramQueue->getParameterId ())
				{
					case GainParams::kParamGainId:
						if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultTrue)
							mGain = value;
							break;
					case GainParams::kParamOutGainId:
						if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) ==  kResultTrue)
							oGain = value;
							break;
					case muParams::kParamMuId:
						if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultTrue)
							mu = value; // no idea if we need a break statement
							break;
				}
			}
		}
	}
	
	//--- Here you have to implement your processing

	/*
	Would be worth having an input gain, an output gain, a control for the mu.
	*/

	if (data.numInputs == 0 || data.numSamples == 0)
		return kResultOk;

	int32 numChannels = data.inputs[0].numChannels;

	uint32 sampleFramesSize = getSampleFramesSizeInBytes(processSetup, data.numSamples);
	void** in = getChannelBuffersPointer(processSetup, data.inputs[0]);
	void** out = getChannelBuffersPointer(processSetup, data.outputs[0]);

	data.outputs[0].silenceFlags = 0;

	for (int32 i = 0; i < numChannels; i++)
	{
		int32 samples = data.numSamples;
		Vst::Sample32* ptrIn = (Vst::Sample32*)in[i];
		Vst::Sample32* ptrOut = (Vst::Sample32*)out[i];
		Vst::Sample32 currentSample;

		while (--samples >= 0)
		{
			currentSample = (*ptrIn++);
			currentSample = Effects::gain(currentSample, mGain, 1.0f);
			currentSample = Effects::muLaw(currentSample, mu);
			currentSample = Effects::gain(currentSample, oGain, 8.0f);

			(*ptrOut++) = currentSample;

		}
	}

	if (data.inputs[0].silenceFlags != 0)
	{
		data.outputs[0].silenceFlags = data.inputs[0].silenceFlags;

		for (int32 i = 0; i < numChannels; i++)
		{
			if (in[i] != out[i])
			{
				memset (out[i], 0, sampleFramesSize);
			}
		}
		return kResultOk;
	}

	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API muLawProcessor::setupProcessing (Vst::ProcessSetup& newSetup)
{
	//--- called before any processing ----
	return AudioEffect::setupProcessing (newSetup);
}

//------------------------------------------------------------------------
tresult PLUGIN_API muLawProcessor::canProcessSampleSize (int32 symbolicSampleSize)
{
	// by default kSample32 is supported
	if (symbolicSampleSize == Vst::kSample32)
		return kResultTrue;

	// disable the following comment if your processing support kSample64
	/* if (symbolicSampleSize == Vst::kSample64)
		return kResultTrue; */

	return kResultFalse;
}

//------------------------------------------------------------------------
tresult PLUGIN_API muLawProcessor::setState (IBStream* state)
{
	// float toSaveParam1 = mGain;
	// float toSaveParam2 = oGain;
	// float toSaveParam3 = mu;

	IBStreamer streamer (state, kLittleEndian);

	// streamer.writeFloat(toSaveParam1);						// ok lets make this an array lmfao
	// streamer.writeFloat(toSaveParam2);
	// streamer.writeFloat(toSaveParam3);
	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API muLawProcessor::getState (IBStream* state)
{
	// if (!state)
	// 	return kResultFalse;

	IBStreamer streamer (state, kLittleEndian);
	// float savedParam1 = 0.f;
	// float savedParam2 = 0.f;
	// float savedParam3 = 0.f;
	// if (streamer.readFloat(savedParam1) == false)
	// 	return 

	return kResultOk;
}

//------------------------------------------------------------------------
} // namespace MyCompanyName
