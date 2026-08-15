// CajuOS health check: short, read-mostly diagnostics for GB300.
var ROOT = "/media/mmcblk0";
var REPORT = ROOT + "/Caju OS Data/logs/reports/cajuos-health-last.txt";
var lines = [];
var pass = 0;
var warn = 0;

function add(status, name, detail) {
  lines.push(status + "|" + name + "|" + detail);
  if (status === "PASS") pass++;
  if (status === "WARN") warn++;
}

function hasText(path, needle) {
  try {
    var text = JS2300.fs.readText(path) || "";
    return text.indexOf(needle) >= 0;
  } catch (e) {
    return false;
  }
}

function checkDir(path) {
  try {
    var items = JS2300.fs.list(path);
    add("PASS", "dir", path + " entries=" + (items ? items.length : 0));
  } catch (e) {
    add("WARN", "dir", path + " unavailable");
  }
}

function main() {
  var start = JS2300.now();
  lines.push("CAJUOS HEALTH CHECK");
  lines.push("started_ms=" + start);

  checkDir(ROOT + "/Caju OS");
  checkDir(ROOT + "/Caju OS Data");
  checkDir(ROOT + "/ROMS");
  checkDir(ROOT + "/Caju OS Data/scripts");

  if (hasText(ROOT + "/Caju OS/theme.ini", "accent="))
    add("PASS", "theme", "caju theme detected");
  else
    add("WARN", "theme", "caju theme not detected");

  if (hasText(ROOT + "/Caju OS Data/settings.ini", "storage_profile=boot"))
    add("PASS", "storage", "safe boot profile selected");
  else
    add("WARN", "storage", "safe boot profile not explicit");

  if (hasText(ROOT + "/Caju OS Data/languages/portugues.ini", "Default="))
    add("PASS", "language", "portuguese language pack present");
  else
    add("WARN", "language", "portuguese language pack missing");

  var battery = null;
  try { battery = JS2300.system.battery(); } catch (e) {}
  if (battery)
    add("PASS", "battery", JSON.stringify(battery));
  else
    add("WARN", "battery", "battery service unavailable");

  lines.push("summary=pass:" + pass + " warn:" + warn);
  lines.push("elapsed_ms=" + (JS2300.now() - start));
  try { JS2300.fs.writeText(REPORT, lines.join("\n") + "\n"); } catch (writeErr) {}
  try { JS2300.system.action("toast:CajuOS health " + (warn ? "com atenção" : "OK")); } catch (toastErr) {}
  return warn ? 1 : 0;
}

main();
