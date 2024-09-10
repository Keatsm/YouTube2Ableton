#include "YourPluginName/PluginEditor.h"
#include "YourPluginName/PluginProcessor.h"
#include <Python.h>

namespace audio_plugin {
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(
    AudioPluginAudioProcessor& p)
    : AudioProcessorEditor(&p), processorRef(p) {
  juce::ignoreUnused(processorRef);
  
  addAndMakeVisible(downloadButton);
  
  downloadButton.onClick = [this] { this->downloadAudio(); };

  addAndMakeVisible(webBrowserComponent);
  webBrowserComponent.goToURL("https://www.youtube.com/");
  
  setSize (1000, 1000);

  Py_Initialize();
  ytDlpModule = PyImport_ImportModule("yt_dlp");
}

void AudioPluginAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("Youtube2Ableton", getLocalBounds(), juce::Justification::centred, 1);
}

void AudioPluginAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds();
    webBrowserComponent.setBounds(bounds.removeFromBottom(bounds.getHeight() - 50));
    downloadButton.setBounds(bounds);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor() {
  Py_DECREF(ytDlpModule);
  Py_Finalize();
}

auto AudioPluginAudioProcessorEditor::downloadAudio() -> void {
  webBrowserComponent.evaluateJavascript("window.location.href", [this](const juce::WebBrowserComponent::EvaluationResult& result)
  {
    auto url = result.getResult()->toString();
    juce::Logger::writeToLog("Downloading MP3 from URL: " + url);
    PyObject* ytDlpMainFunc = PyObject_GetAttrString(ytDlpModule, "main");

    if (ytDlpMainFunc && PyCallable_Check(ytDlpMainFunc)) {
        PyObject* argsList = PyList_New(0);
        PyList_Append(argsList, PyUnicode_FromString(url.toStdString().c_str()));
        PyList_Append(argsList, PyUnicode_FromString("-x")); // extract audio
        PyList_Append(argsList, PyUnicode_FromString("--audio-format"));
        PyList_Append(argsList, PyUnicode_FromString("mp3"));
        // Call yt-dlp main function with arguments
        PyObject* ytDlpArgs = Py_BuildValue("(O)", argsList);
        PyObject_CallObject(ytDlpMainFunc, ytDlpArgs);
    }
  });
}
}  // namespace audio_plugin
