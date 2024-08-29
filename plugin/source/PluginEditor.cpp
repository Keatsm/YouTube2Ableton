#include "YourPluginName/PluginEditor.h"
#include "YourPluginName/PluginProcessor.h"

namespace audio_plugin {
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(
    AudioPluginAudioProcessor& p)
    : AudioProcessorEditor(&p), processorRef(p) {
  juce::ignoreUnused(processorRef);
  addAndMakeVisible(webBrowserComponent);
  webBrowserComponent.goToURL("https://www.youtube.com/");
  addAndMakeVisible(downloadButton);
  
  downloadButton.onClick = [this] { this->downloadAudio(); };
  
  setSize (600, 400);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor() {}

auto AudioPluginAudioProcessorEditor::downloadAudio() -> void {
  webBrowserComponent.evaluateJavascript("window.location.href", [this](const juce::WebBrowserComponent::EvaluationResult& result)
  {
    auto url = result.getResult()->toString();
  });
}
}  // namespace audio_plugin
