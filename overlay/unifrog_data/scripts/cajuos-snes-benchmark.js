// unifrog: mode=extension
// Runs on-device only. Each completed run emits unifrog perf, perf_cpu and
// perf_audio lines; collect those logs with the frontend-driver report.
load("frontend-driver/_fd-lib.js");

FD.main("cajuos_snes_benchmark", function() {
  FD.runSuite("cajuos_snes_benchmark", [
    { name: "snes2002_audio_on_frameskip_off", run: function() {
      return FD.runCore("snes2002_audio_on_frameskip_off", "SFC", "snes9x2002",
        [".zip", ".sfc", ".smc"], { audio: 1, frames: 180, frameskip: 0 });
    }},
    { name: "snes2002_audio_on_frameskip_auto", run: function() {
      return FD.runCore("snes2002_audio_on_frameskip_auto", "SFC", "snes9x2002",
        [".zip", ".sfc", ".smc"], { audio: 1, frames: 180, frameskip: 1 });
    }},
    { name: "snes2002_audio_off_frameskip_off", run: function() {
      return FD.runCore("snes2002_audio_off_frameskip_off", "SFC", "snes9x2002",
        [".zip", ".sfc", ".smc"], { audio: 0, frames: 180, frameskip: 0 });
    }},
    { name: "snes2002_audio_off_frameskip_auto", run: function() {
      return FD.runCore("snes2002_audio_off_frameskip_auto", "SFC", "snes9x2002",
        [".zip", ".sfc", ".smc"], { audio: 0, frames: 180, frameskip: 1 });
    }}
  ]);
});
