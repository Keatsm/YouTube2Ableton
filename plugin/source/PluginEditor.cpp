#include "YourPluginName/PluginEditor.h"
#include "YourPluginName/PluginProcessor.h"

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
}

void AudioPluginAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("Web Browser Plugin", getLocalBounds(), juce::Justification::centred, 1);
}

void AudioPluginAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds();
    webBrowserComponent.setBounds(bounds.removeFromBottom(bounds.getHeight() - 50));
    downloadButton.setBounds(bounds);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor() {}

auto AudioPluginAudioProcessorEditor::downloadAudio() -> void {
  webBrowserComponent.evaluateJavascript("window.location.href", [this](const juce::WebBrowserComponent::EvaluationResult& result)
  {
    auto url = result.getResult()->toString();
    juce::Logger::writeToLog("Downloading MP3 from URL: " + url);
  });
}
}  // namespace audio_plugin
