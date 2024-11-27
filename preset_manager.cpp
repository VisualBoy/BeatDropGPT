#include <string>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>
#include <fstream>
#include <sstream>
#include <algorithm> // For std::transform

// Helper function for case-insensitive string comparison
bool iequals(const std::string& a, const std::string& b) {
    return std::equal(a.begin(), a.end(),
                      b.begin(), b.end(),
                      [](char a, char b) {
                          return tolower(a) == tolower(b);
                      });
}

struct Preset {
    // Motion Parameters
    float zoom = 1.0f;
    float zoomexp = 1.0f;
    float rot = 0.0f;
    float warp = 0.0f;
    float dx = 0.0f;
    float dy = 0.0f;
    float sx = 1.0f;
    float sy = 1.0f;

    // Waveform Parameters
    int wave_mode = 0;
    float wave_x = 0.5f;
    float wave_y = 0.5f;
    float wave_r = 1.0f;
    float wave_g = 1.0f;
    float wave_b = 1.0f;
    float wave_a = 1.0f;
    float wave_mystery = 0.0f;
    bool wave_usedots = false;
    bool wave_thick = false;
    bool wave_additive = false;
    bool wave_brighten = false;

    // Borders
    float ob_size = 0.0f;
    float ob_r = 1.0f;
    float ob_g = 1.0f;
    float ob_b = 1.0f;
    float ob_a = 1.0f;
    float ib_size = 0.0f;
    float ib_r = 1.0f;
    float ib_g = 1.0f;
    float ib_b = 1.0f;
    float ib_a = 1.0f;

    // Motion Vectors
    float mv_r = 1.0f;
    float mv_g = 1.0f;
    float mv_b = 1.0f;
    float mv_a = 1.0f;
    int mv_x = 0;
    int mv_y = 0;
    float mv_l = 0.0f;
    float mv_dx = 0.0f;
    float mv_dy = 0.0f;

    // Image Effects
    float decay = 0.98f;
    float gamma = 1.0f;
    float echo_zoom = 1.0f;
    float echo_alpha = 0.0f;
    int echo_orient = 0;
    bool darken_center = false;
    bool wrap = false;
    bool invert = false;
    bool brighten = false;
    bool darken = false;
    bool solarize = false;

    // Variables
    float q[32] = {0.0f};
    float blur1_min = 0.0f;
    float blur1_max = 1.0f;
    float blur2_min = 0.0f;
    float blur2_max = 1.0f;
    float blur3_min = 0.0f;
    float blur3_max = 1.0f;
    float blur1_edge_darken = 0.0f;
};

class PresetManager {
public:
    PresetManager() {
        // Initialize with default preset values
        Preset defaultPreset;
        presets.push_back(defaultPreset);
        currentPresetIndex = 0;
    }

    void ApplyChatGPTResponse(const std::string& response) {
        try {
            // Parse JSON metadata for the corresponding prompt
            auto metadata = parseMetadataForPrompt(response);

            // Use a switch statement or map for cleaner effect handling
            switch (getEffectType(metadata)) {
                case EffectType::Zoom:
                    applyZoomEffect(response, presets[currentPresetIndex]);
                    break;
                case EffectType::Waveform:
                    modifyWaveform(response, presets[currentPresetIndex]);
                    break;
                case EffectType::ColorAdjustment:
                    adjustColors(response, presets[currentPresetIndex]);
                    break;
                case EffectType::MotionVectors:
                    adjustMotionVectors(response, presets[currentPresetIndex]);
                    break;
                case EffectType::ImageEffects:
                    applyImageEffects(response, presets[currentPresetIndex]);
                    break;
                default:
                    logErrorAndInformUser("Unknown effect type received from ChatGPT.");
            }

            // Apply changes to the visualization
            UpdateVisualization();

        } catch (const std::exception& e) {
            logErrorAndInformUser("Error applying ChatGPT response: " + std::string(e.what()));
        }
    }

    void UpdateVisualization() {
        // Logic to update the visualization with the current preset
        std::cout << "Updating visualization with zoom: " << presets[currentPresetIndex].zoom
                  << " and rotation: " << presets[currentPresetIndex].rot << std::endl;
        // Here, connect to the actual rendering logic to apply these parameters
        // Example: renderer->update(presets[currentPresetIndex]);
    }

    void AddTemplatePreset(const Preset& preset) {
        presets.push_back(preset);
    }

    void SwitchPreset(size_t index) {
        if (index < presets.size()) {
            currentPresetIndex = index;
            UpdateVisualization();
        }
    }

private:
    std::vector<Preset> presets;
    size_t currentPresetIndex;

    // Enum for clearer effect categorization
    enum class EffectType {
        Unknown, Zoom, Waveform, ColorAdjustment, MotionVectors, ImageEffects,  // ... other types
    };

    EffectType getEffectType(const nlohmann::json& metadata) {
        if (metadata.contains("effect_type")) {
            std::string effectTypeString = metadata.value("effect_type", "unknown");
            if (iequals(effectTypeString, "zoom")) return EffectType::Zoom;
            if (iequals(effectTypeString, "waveform")) return EffectType::Waveform;
            if (iequals(effectTypeString, "color adjustment")) return EffectType::ColorAdjustment;
            if (iequals(effectTypeString, "motion vectors")) return EffectType::MotionVectors;
            if (iequals(effectTypeString, "image effects")) return EffectType::ImageEffects;
            // Add more checks for additional EffectTypes...
        }
        return EffectType::Unknown;
    }

    float extractFloatParameter(const std::string& prompt, const std::string& parameterName, float defaultValue) {
        std::string keyword = parameterName + ":";
        size_t pos = prompt.find(keyword);
        if (pos != std::string::npos) {
            std::stringstream ss(prompt.substr(pos + keyword.length()));
            float value;
            if (ss >> value) {
                return value;
            } else {
                logErrorAndInformUser("Invalid value for " + parameterName + " in prompt.");
            }
        }
        return defaultValue;
    }

    void applyZoomEffect(const std::string& prompt, Preset& preset) {
        float zoomChange = extractFloatParameter(prompt, "zoom", 0.0f);
        preset.zoom += zoomChange;

        if (prompt.find("negative") != std::string::npos && zoomChange > 0.0f) {
            logErrorAndInformUser("Conflicting instructions: Increase and Negative zoom.");
        }
    }

    void modifyWaveform(const std::string& prompt, Preset& preset) {
        if (prompt.find("sine wave") != std::string::npos) {
            preset.wave_mode = 0;  // Switch to sine wave
        } else if (prompt.find("thickness") != std::string::npos) {
            preset.wave_thick = true;
        }
    }

    void adjustColors(const std::string& prompt, Preset& preset) {
        if (prompt.find("replace green with blue") != std::string::npos) {
            preset.wave_g = 0.0f;
            preset.wave_b = 1.0f;
        }
        // More color adjustments...
    }

    void adjustMotionVectors(const std::string& prompt, Preset& preset) {
        if (prompt.find("increase length") != std::string::npos) {
            preset.mv_l += 0.5f;
        }
        if (prompt.find("align with bass") != std::string::npos) {
            preset.mv_x = 32;  // Example: Aligning with bass
        }
    }

    void applyImageEffects(const std::string& prompt, Preset& preset) {
        if (prompt.find("solarization") != std::string::npos) {
            preset.solarize = true;
        }
        if (prompt.find("invert colors") != std::string::npos) {
            preset.invert = true;
        }
    }

    void logErrorAndInformUser(const std::string& message) {
        std::cerr << "Error: " << message << std::endl;
        // More sophisticated user feedback methods...
    }

    nlohmann::json parseMetadataForPrompt(const std::string& prompt) {
        // Dummy implementation for parsing metadata
        nlohmann::json metadata;
        // Parse the JSONL file and find the matching prompt
        // Return the metadata for the prompt
        return metadata;
    }
};
