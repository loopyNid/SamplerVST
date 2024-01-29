# https://github.com/juce-framework/JUCE/blob/master/docs/CMake%20API.md

cmake_minimum_required(VERSION 3.15)

project(SamplerVST VERSION 0.0.1)

set(TargetName SamplerVST)

add_subdirectory(../JUCE JUCE)

juce_add_plugin(
    ${TargetName}
    PRODUCT_NAME "Nikk's SamplerVST"
    # VERSION ...
    # DESCRIPTION ...
    # ICON_BIG ...
    # ICON_SMALL ...
    # COMPANY_NAME ...
    # COMPANY_EMAIL ...
    # COMPANY_WEBSITE ...
    # COMPANY_COPYRIGHT ...
    IS_SYNTH TRUE
    # EDITOR_WANTS_KEYBOARD_FOCUS TRUE/FALSE
    # IS_MIDI_EFFECT TRUE/FALSE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT TRUE
    # VST_NUM_MIDI_INS #
    # VST_NUM_MIDI_OUTS #
    # VST3_CATEGORIES ...
    # PLUGIN_MANUFACTURER_CODE Code
    # PLUGIN_CODE Code
    FORMATS VST3 Standalone
)

juce_generate_juce_header(${TargetName})

set(src
    PluginEditor.cpp
    PluginProcessor.cpp
    SampleThumbnail.cpp
)
list(TRANSFORM src PREPEND "Source/")

target_sources(
    ${TargetName}
    PRIVATE
        ${src}
)

target_compile_definitions(
    ${TargetName}
    PUBLIC
    JUCE_MODAL_LOOPS_PERMITTED=1 # ADDED BY NIKK => because of juce 6.1 - breaking change https://forum.juce.com/t/solved-juce-filechooser-has-no-member-browseforfiletoopen/47793/2
	JUCER_ENABLE_GPL_MODE=1
        JUCE_DISPLAY_SPLASH_SCREEN=0
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
)

target_link_libraries(
    ${TargetName}
    PRIVATE
        juce::juce_audio_utils
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)