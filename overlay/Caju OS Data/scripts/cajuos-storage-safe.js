// CajuOS safe storage probe. No runtime UHS or aggressive stress profiles.
var ROOT = "/media/mmcblk0";
var REPORT = ROOT + "/Caju OS Data/logs/reports/cajuos-storage-safe-last.txt";
var started = JS2300.now();
var recovery = -1;
var benchmark = -1;
var lines = [
  "CAJUOS SAFE STORAGE PROBE",
  "profile=boot",
  "policy=no_uhs_no_runtime_switch"
];

try { recovery = JS2300.system.action("storage:recover"); } catch (e) {}
lines.push("storage_recover_ret=" + recovery);

try { benchmark = JS2300.system.action("developer:storage_quick_benchmark"); } catch (e2) {}
lines.push("storage_quick_benchmark_ret=" + benchmark);

lines.push("result=" + (recovery > 0 && benchmark > 0 ? "PASS" : "WARN"));
lines.push("elapsed_ms=" + (JS2300.now() - started));
try { JS2300.fs.writeText(REPORT, lines.join("\n") + "\n"); } catch (writeErr) {}
try { JS2300.system.action("toast:Teste SD seguro " + (recovery > 0 && benchmark > 0 ? "OK" : "verifique o relatorio")); } catch (toastErr) {}
