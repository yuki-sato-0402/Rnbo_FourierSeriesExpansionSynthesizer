#include "RNBO_Utils.h"
#include "RNBO.h"
#include "RNBO_JuceAudioProcessor.h"
#include "RNBO_BinaryData.h"
#include <json/json.hpp>

class CustomAudioProcessor : public RNBO::JuceAudioProcessor ,public juce::AudioProcessorValueTreeState::Listener{
public:
    static CustomAudioProcessor* CreateDefault();
    CustomAudioProcessor(const nlohmann::json& patcher_desc, const nlohmann::json& presets, const RNBO::BinaryData& data);
    ~CustomAudioProcessor()override;
    juce::AudioProcessorEditor* createEditor() override;
    // APVTS の参照を取得する関数を追加
    juce::AudioProcessorValueTreeState& getValueTreeState() 
    { 
        jassert(parameters != nullptr);  // parameters が nullptr でないかチェック
        return *parameters; 
    }
    
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void parameterChanged(const juce::String& parameterID, float newValue) override;
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
 //AudioProcessorValueTreeStateクラスとパラメータ値を格納するポインタを準備します。
    std::unique_ptr<juce::AudioProcessorValueTreeState> parameters;  // ✅ ポインタにする
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomAudioProcessor)
    RNBO::CoreObject rnboObject;
    std::atomic<float>* termsParameter  = nullptr;
    std::atomic<float>* filterOnOffParameter  = nullptr;
    std::atomic<float>* cutoffOvertoneParameter  = nullptr;
    std::atomic<float>* attenuationParameter  = nullptr;
    std::atomic<float>* ocillatorParameter  = nullptr;
    std::atomic<float>* attackParameter  = nullptr;
    std::atomic<float>* decayParameter  = nullptr;
    std::atomic<float>* sustainParameter  = nullptr;
    std::atomic<float>* releaseParameter  = nullptr;
    std::atomic<float>* ampParameter  = nullptr;

   
    RNBO::MidiEventList						_midiInput;
    RNBO::MidiEventList						_midiOutput;
};

